cmake_minimum_required(VERSION 3.16)
project(YourLauncher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -Wextra -Wconversion -Wsign-conversion")

find_package(CURL REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
find_library(LIBZIP_LIBRARY zip REQUIRED)

add_subdirectory(connections/mainfiles)

set(APP_SOURCES
    "launcher.cpp"
    "application/control.cpp"
)
set(MISC_SOURCES
    "log/write.cpp"
    "misc/boolproxy.hpp" # for meta object compiler
)
set(RESOURCE_FILES
    "qml/launcher.qrc"
)

set_source_files_properties(
    "connections/mainfiles/cvk_backendconnectionside.cpp"
    "connections/mainfiles/cvk_frontendconnectionside.cpp"
    PROPERTIES GENERATED TRUE
)

add_executable(YourLauncher
    ${APP_SOURCES}
    ${CON_SOURCES}
    ${MISC_SOURCES}
    ${RESOURCE_FILES}
)
add_dependencies(YourLauncher generate_connections)

include_directories(
    "misc"
    "./"
)

target_link_libraries(YourLauncher
PRIVATE
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    CURL::libcurl
    zip
)
