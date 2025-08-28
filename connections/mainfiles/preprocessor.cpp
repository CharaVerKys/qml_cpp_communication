


// ! gpt generated, right now not fully read



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// Recursive paste resolver
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
            bool cont = false;
            for(auto const& include_to_change : includes_to_change){
                if(auto res = line.find(include_to_change); res not_eq std::string::npos){
                    out << line.substr(0,res) << "cvk_" << line.substr(res) << "\n";
                    cont = true;
                    break;
                }
            }
            if(cont){continue;}
        }
        if (line.find("#paste")not_eq std::string::npos){
            if(auto res = line.find("<"); res not_eq std::string::npos){throw std::runtime_error("<> not supported, supposed to use \"\"");}
            auto start = line.find('"');
            auto end   = line.find_last_of('"');
            if (start == std::string::npos || end <= start){
                throw std::runtime_error("Malformed #paste directive in " + file.string());
            }

            fs::path sub = file.parent_path() / line.substr(start + 1, end - start - 1);
            out << preprocess_file(sub, seen,includes_to_change); // recursion
        } else {
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
}
