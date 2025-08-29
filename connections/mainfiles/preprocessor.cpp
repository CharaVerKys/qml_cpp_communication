#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::string onInsertBackNotify(fs::path&& parent_path);

std::string onInsertNotifyConnections(fs::path&& parent_path);
std::string onInsertFrontConnections(fs::path&& parent_path);

bool onInclude(std::ostringstream& out, std::string const& line, std::vector<std::string_view>const& includes){
    for(auto const& include_to_change : includes){
        if(auto res = line.find(include_to_change); res not_eq std::string::npos){
            out << line.substr(0,res) << "cvk_" << line.substr(res) << "\n";
            return true;
            break;
        }
    }
    return false;
}

fs::path findFileInPasteString(std::string const& line, fs::path const& file){
    if(auto res = line.find("<"); res not_eq std::string::npos){throw std::runtime_error("<> not supported, supposed to use \"\"");}
    auto start = line.find('"');
    auto end   = line.find_last_of('"');
    if (start == std::string::npos || end <= start){
        throw std::runtime_error("Malformed #paste directive in " + file.string());
    }

    fs::path sub = file.parent_path() / line.substr(start + 1, end - start - 1);
    return sub;
}

std::string preprocess_file(const fs::path &file, std::unordered_set<std::string> &seen, std::vector<std::string_view> const& includes_to_change) {
    if (seen.count(file.string())) {
        throw std::runtime_error("Recursive inclusion loop: " + file.string());
    }
    seen.insert(file.string());

    std::ifstream in(file);
    if (!in) throw std::runtime_error("Cannot open file: " + file.string());

    std::ostringstream out;
    std::string line;

    while (std::getline(in, line)) {
        if(line.starts_with("#include")){
            if(onInclude(out, line, includes_to_change)){
                continue;
            }
        }
        if (line.find("#paste") not_eq std::string::npos){
            // ? recursion
            out << preprocess_file(
                        findFileInPasteString(line, file),
                        seen, includes_to_change
                    ); 
        }else
        if(line.find("#insert backend emits") not_eq std::string::npos){
            out << onInsertBackNotify(file.parent_path());
        }else
        if(line.find("#insert frontend connections") not_eq std::string::npos){
            out << onInsertFrontConnections(file.parent_path());
        }else
        if(line.find("#insert notify connections") not_eq std::string::npos){
            out << onInsertNotifyConnections(file.parent_path());
        }
        else {
            out << line << "\n";
        }
    }
    seen.erase(file.string());
    return out.str();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>\n";
        return 1;
    }


    fs::path in_file = argv[1];
    std::unordered_set<std::string> seen;


    std::vector<std::string_view> includes_to_change;
    for(int i = 2; i < argc; ++i){
        includes_to_change.emplace_back(argv[i]);
    }

    try {
        std::string result = preprocess_file(in_file, seen, includes_to_change);
        std::string out_name = in_file.c_str();
        fs::path out_file = in_file.parent_path() /
                        ("cvk_" + in_file.filename().string());

        std::ofstream out(out_file);
        out << result;

        std::cout << "Preprocessed file written to: " << out_file << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
    return 0;
} // main

std::string namelessLogicFunc(std::string::iterator begin, std::string::iterator end, int& openBrackets,bool& allTextProcessed){
    std::string::iterator& it = begin;
    std::ostringstream out;
    while(it not_eq end){
        if(*it == '{'){
            if(openBrackets /*not_eq 0*/){
                out << *it;
            }
            openBrackets++;
        }else
        if(*it == '}'){
            if(not openBrackets){
                out << *it;
            }else{
                allTextProcessed = true;
            }
            openBrackets--;
        }else{
            if(openBrackets){
                out << *it;
            }
        }
      ++it; // while ++
    }
    return out.str();
}

std::string onInsertBackNotify(fs::path&& parent_path){
    fs::path notifyDir = parent_path.parent_path() / "notifiable";

    if(notifyDir == "notifiable"){
        notifyDir = "../notifiable";
    }
    fs::recursive_directory_iterator notifies{notifyDir};

    std::ostringstream out;

    for(;notifies not_eq fs::recursive_directory_iterator{}; ++notifies){
        if(not notifies->is_regular_file()){continue;}
        if(notifies->path().filename() == "_types.hpp"){continue;}
        std::ifstream fstream{notifies->path()};
        // filename without extention
        const std::string filename_with_extention = notifies->path().filename().native();
        const std::string fn_wo_ext = filename_with_extention.substr(0,filename_with_extention.find_last_of('.'));

        bool found_connection = false;
        int openBrackets = 0;
        bool allTextProcessed = false;
        std::string line;
        bool success = (bool) std::getline(fstream,line);
        if(not success){
            std::cerr << "failed to read file: " << notifies->path() << ", aborting preprocess.";
            std::exit(1);
        }
        
        if(line.find("public") == std::string::npos){
            std::cerr << "on purpose to avoid issue with macros Q_PROPERTY, and paste logic in general, please write public: as first line in your notifiable property\n";
        }else{
            if(auto pos = line.find("private: struct backendemit_" + fn_wo_ext); pos not_eq std::string::npos){
                found_connection = true;
                auto it = line.begin() + (int)("private: struct backendemit_" + fn_wo_ext).size();
                out << namelessLogicFunc(it, line.end(), openBrackets, allTextProcessed);
                if(not line.empty()){out << '\n';}
            } // if contain connect on first line
        } // if public first

        while(not found_connection){
            bool success = (bool) std::getline(fstream,line);
            if(not success){
                std::cerr << "error in file " << notifies->path() << ": no `private: struct backendemit_<filename>` found.";
                std::exit(1);
            }
            if(auto pos = line.find("private: struct backendemit_" + fn_wo_ext); pos not_eq std::string::npos){
                found_connection = true;
                auto it = line.begin() + (int)("private: struct backendemit_" + fn_wo_ext).size();
                out << namelessLogicFunc(it, line.end(), openBrackets, allTextProcessed);
                if(not line.empty()){out << '\n';}
            } // if contain connect on first line
        }
        if(not openBrackets and found_connection and not allTextProcessed){
            for(;;){
                bool success = (bool) std::getline(fstream,line);
                if(not success){
                    std::cerr << "parsing error in file " << notifies->path() << ": no opening bracket for backend emit found.";
                    std::exit(1);
                }
                if(line.find('{') not_eq std::string::npos){
                    out << namelessLogicFunc(line.begin(), line.end(), openBrackets, allTextProcessed);
                    if(not line.empty()){out << '\n';}
                    break;
                }
            }// for (;;)
        } // if not brackets and found

        while(openBrackets > 0){
            bool success = (bool) std::getline(fstream,line);
            if(not success){
                std::cerr << "parsing error in file " << notifies->path() << ": no matching closing bracket for backend emit found.";
                std::exit(1);
            }
            out << namelessLogicFunc(line.begin(), line.end(), openBrackets, allTextProcessed);
            if(not line.empty() and not allTextProcessed){
                out << '\n';
            }
        }
    } // for all files
    // std::cout << out.str() <<std::endl;
    return out.str();
}// root func

std::string onInsertNotifyConnections(fs::path&& parent_path)
{
    fs::path notifyDir = parent_path.parent_path() / "notifiable";
    if(notifyDir == "notifiable"){
        notifyDir = "../notifiable";
    }
    fs::recursive_directory_iterator notifies{notifyDir};

    std::vector<std::string> found_functions;

    for(;notifies not_eq fs::recursive_directory_iterator{}; ++notifies){
        if(not notifies->is_regular_file()){continue;}
        if(notifies->path().filename() == "_types.hpp"){continue;}
        std::ifstream fstream{notifies->path()};
        
        // bool funcFound = false; // ? use break instead
        std::string line;

        while(std::getline(fstream,line)){
            if(auto pos = line.find("_connectNotifiableToBackend()"); pos not_eq std::string::npos){
                auto pos_com = line.find("//"); // ? c multi-lines comments not supported, sorry
                static_assert(std::string::npos == size_t(-1));
                if(pos_com < pos){continue;}
                pos_com = line.find("/*"); // ? c multi-lines comments not supported, sorry
                if(pos_com < pos){continue;}

                size_t nameSize = std::string{"_connectNotifiableToBackend()"}.size();
                while(line[pos] not_eq ' '){
                    nameSize++;
                    pos--;
                    if(pos == 0){throw std::runtime_error("parsing error, your functions is not a function");}
                }
                found_functions.push_back(line.substr(pos+1,nameSize-1));
                break;
            } // if contain connect on first line
        }
    } // for all files

    std::ostringstream oss;
    for(auto const& str : found_functions){
        oss << "    " << str << ';' << '\n';
    }

    // std::cout << oss.str() <<std::endl;
    return oss.str();
}

std::string onInsertFrontConnections(fs::path&& parent_path)
{
    fs::path notifyDir = parent_path.parent_path() / "signalslot";
    if(notifyDir == "signalslot"){
        notifyDir = "../signalslot";
    }
    fs::recursive_directory_iterator notifies{notifyDir};

    std::vector<std::string> found_functions;

    for(;notifies not_eq fs::recursive_directory_iterator{}; ++notifies){
        if(not notifies->is_regular_file()){continue;}
        if(notifies->path().filename() == "_types.hpp"){continue;}
        std::ifstream fstream{notifies->path()};
        
        // bool funcFound = false; // ? use break instead
        std::string line;

        while(std::getline(fstream,line)){
            if(auto pos = line.find("_connectBackendToSignals()"); pos not_eq std::string::npos){
                auto pos_com = line.find("//"); // ? c multi-lines comments not supported, sorry
                static_assert(std::string::npos == size_t(-1));
                if(pos_com < pos){continue;}
                pos_com = line.find("/*"); // ? c multi-lines comments not supported, sorry
                if(pos_com < pos){continue;}

                size_t nameSize = std::string{"_connectBackendToSignals()"}.size();
                while(line[pos] not_eq ' '){
                    nameSize++;
                    pos--;
                    if(pos == 0){throw std::runtime_error("parsing error, your functions is not a function");}
                }
                found_functions.push_back(line.substr(pos+1,nameSize-1));
                break;
            } // if contain connect on first line
        }
    } // for all files

    std::ostringstream oss;
    for(auto const& str : found_functions){
        oss << "    " << str << ';' << '\n';
    }

    // std::cout << oss.str() <<std::endl;
    return oss.str();
}
