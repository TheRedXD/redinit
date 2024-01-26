#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "scripts/cppconancmake.hpp"
#include "scripts/cppconan.hpp"

int main(int argc, char** argv) {
    // timestamp
    auto start = std::chrono::high_resolution_clock::now();
    std::string COLOR_RED = "\x001b[0;31m";
    std::string COLOR_GREEN = "\x001b[0;32m";
    std::string COLOR_YELLOW = "\x001b[0;33m";
    std::string COLOR_BLUE = "\x001b[0;34m";
    std::string COLOR_MAGENTA = "\x001b[0;35m";
    std::string COLOR_CYAN = "\x001b[0;36m";
    std::string COLOR_WHITE = "\x001b[0;37m";
    std::string COLOR_RESET = "\x001b[0m";

    // print version
    std::cout << COLOR_WHITE << "RedInit v1.0, © TheRed.SH 2024\nTool by TheRed.SH for quickly generating various projects." << COLOR_RESET << std::endl;
    // check system type
    std::string system;
    #ifdef __linux__
    system = "linux";
    std::cout << COLOR_WHITE << "System is detected as: linux" << COLOR_RESET << std::endl;
    #elif _WIN32
    system = "windows";
    std::cout << COLOR_WHITE << "System is detected as: windows" << COLOR_RESET << std::endl;
    #elif __APPLE__
    system = "macos";
    std::cout << COLOR_WHITE << "System is detected as: macos" << COLOR_RESET << std::endl;
    #else
    system = "unknown";
    std::cout << COLOR_WHITE << "System is detected as: unknown" << COLOR_RESET << std::endl;
    #endif

    if(system == "windows" || system == "macos" || system == "unknown") {
        std::cout << COLOR_RED << "Error: System is not supported at this time. We're sorry." << COLOR_RESET << std::endl;
        return 1;
    }

    bool ignoreDepends = true;
    // don't check depends if --ignore-depends is in args
    // if (argc > 2) {
    //     if (argv[1] == "--ignore-depends") {
    //         ignoreDepends = true;
    //         // strip away --ignore-depends
    //         std::vector<std::string> newArgs;
    //         for (int i = 2; i < argc; i++) {
    //             newArgs.push_back(argv[i]);
    //         }
    //         argc = newArgs.size();
    //         // turn newArgs into argv char**
    //         char** newArgv = new char*[argc];
    //     }
    // }
    // we care about first arg
    std::vector<std::string> possibleArgs;
    possibleArgs.push_back("cppconancmake");
    possibleArgs.push_back("cppconan");
    // make sure there's at least 1 arg
    if (argc < 2) {
        std::cout << COLOR_RED << "Error: No argument provided." << COLOR_RESET << std::endl;
        std::cout << COLOR_BLUE << "Possible arguments: " << COLOR_RESET;
        for (int i = 0; i < possibleArgs.size(); i++) {
            std::cout << COLOR_YELLOW << possibleArgs[i] << COLOR_RESET;
            if (i != possibleArgs.size() - 1) {
                std::cout << COLOR_BLUE << ", " << COLOR_RESET;
            }
        }
        std::cout << COLOR_RESET << std::endl;
        return 1;
    }
    // get project name
    std::string defaultProjectName = "helloworld";
    if (argc < 3) {
        std::cout << COLOR_YELLOW << "No project name provided. Using default \"" + defaultProjectName + "\"" << COLOR_RESET << std::endl;
    }
    std::string name = (argc < 3) ? defaultProjectName : argv[2];

    // get first arg
    std::string arg = argv[1];

    // check if arg is in possibleArgs
    if (std::find(possibleArgs.begin(), possibleArgs.end(), arg) != possibleArgs.end()) {
        // arg is in possibleArgs
        if(arg == "cppconancmake") {
            std::cout << COLOR_BLUE << "Creating C++ project with Conan and CMake... (Using script CPPConanCMake)" << COLOR_RESET << std::endl;
            if (!ignoreDepends) {
                if(!CPPConanCMake::satisfiesDepends()) {
                    std::cout << COLOR_RED << "[CPPConanCMake] " << "Error: Depends are not satisfied." << COLOR_RESET << std::endl;
                    return 1;
                }
            }
            CPPConanCMake::create(name);
        } else if (arg == "cppconan") {
            std::cout << COLOR_BLUE << "Creating C++ project with Conan... (Using script CPPConan)" << COLOR_RESET << std::endl;
            if (!ignoreDepends) {
                if (!CPPConan::satisfiesDepends()) {
                    std::cout << COLOR_RED << "[CPPConan] " << "Error: Depends are not satisfied." << COLOR_RESET << std::endl;
                    return 1;
                }
            }
            CPPConan::create(name);
        }
    } else {
        // arg is not in possibleArgs
        std::cout << COLOR_RED << "Error: Invalid argument \"" << arg << "\"." << COLOR_RESET << std::endl;
        std::cout << COLOR_BLUE << "Possible arguments: " << COLOR_RESET;
        for (int i = 0; i < possibleArgs.size(); i++) {
            std::cout << COLOR_YELLOW << possibleArgs[i] << COLOR_RESET;
            if (i != possibleArgs.size() - 1) {
                std::cout << COLOR_BLUE << ", " << COLOR_RESET;
            }
        }
        std::cout << COLOR_RESET << std::endl;
    }
    // timestamp
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << COLOR_GREEN << "Done in " << duration << "ms." << COLOR_RESET << std::endl;
    return 0;
}
