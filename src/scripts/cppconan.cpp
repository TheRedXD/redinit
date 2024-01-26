#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace CPPConan {
    std::string head = "[CPPConan] ";
    std::string COLOR_RED = "\x001b[0;31m";
    std::string COLOR_GREEN = "\x001b[0;32m";
    std::string COLOR_YELLOW = "\x001b[0;33m";
    std::string COLOR_BLUE = "\x001b[0;34m";
    std::string COLOR_MAGENTA = "\x001b[0;35m";
    std::string COLOR_CYAN = "\x001b[0;36m";
    std::string COLOR_WHITE = "\x001b[0;37m";
    std::string COLOR_RESET = "\x001b[0m";
    bool satisfiesDepends() {
        // check if has conan and cmake as well as make
        if (std::system("which conan > /dev/null") != 0) {
            std::cout << COLOR_RED << head << "Error: Conan is not installed." << COLOR_RESET << std::endl;
            return false;
        }
    }
    int createDirectory(std::string path) {
        std::cout << COLOR_YELLOW << head << "Creating directory " << path << COLOR_RESET << std::endl;
        std::filesystem::create_directory(path);
        std::cout << COLOR_YELLOW << head << "Created directory " << path << COLOR_RESET << std::endl;
        return 0;
    }
    int createFile(std::string path, std::string contents) {
        std::cout << COLOR_BLUE << head << "Creating file " << path << COLOR_RESET << std::endl;
        std::ofstream file(path);

        file << contents;

        file.close();
        std::cout << COLOR_BLUE << head << "Created file " << path << COLOR_RESET << std::endl;
        return 0;
    }
    bool exists(std::string path) {
        return std::filesystem::exists(path);
    }
    bool isDirectoryEmpty(std::string path) {
        return std::filesystem::is_empty(path);
    }
    int create(std::string projectName) {
        // make sure projectName is not empty and does not contain spaces
        if (projectName == "" || projectName.find(" ") != std::string::npos) {
            std::cout << COLOR_RED << head << "Error: Invalid project name \"" << projectName << "\"." << COLOR_RESET << std::endl;
            return 1;
        }
        if (!isDirectoryEmpty(".")) {
            std::cout << COLOR_RED << head << "Error: Directory is not empty." << COLOR_RESET << std::endl;
            return 1;
        }
        std::cout << COLOR_WHITE << head << "Creating project" << COLOR_RESET << std::endl;
        std::cout << COLOR_YELLOW << head << "Creating directories" << COLOR_RESET << std::endl;
        createDirectory("src");
        createDirectory("conan");
        createDirectory("conan/build");
        createDirectory("conan/deb");
        std::cout << COLOR_YELLOW << head << "Created directories" << COLOR_RESET << std::endl;
        std::cout << COLOR_BLUE << head << "Creating files" << COLOR_RESET << std::endl;
        createFile("src/main.cpp", "#include <iostream>\n\nint main() {\n    std::cout << \"Hello, world!\" << std::endl;\n    return 0;\n}");
        createFile("CMakeLists.txt", "cmake_minimum_required(VERSION 3.0.0)\nproject(" + projectName + " CXX)\n\nadd_executable(" + projectName + " src/main.cpp)");
        createFile("conanfile.txt", "[requires]\n[generators]\nCMakeToolchain\nCMakeDeps");
        createFile("rel.sh", "#!/bin/bash\n\nconan install . -sbuild_type=Release -of=conan/build --build=missing");
        createFile("dbg.sh", "#!/bin/bash\n\nconan install . -sbuild_type=Debug -of=conan/deb --build=missing");
        std::system("chmod +x rel.sh");
        std::system("chmod +x dbg.sh");
        std::cout << COLOR_BLUE << head << "Created files" << COLOR_RESET << std::endl;
        std::cout << COLOR_MAGENTA << head << "Creating Conan files" << COLOR_RESET << std::endl;
        std::system("conan install . -sbuild_type=Release -of=conan/build --build=missing");
        std::system("conan install . -sbuild_type=Debug -of=conan/deb --build=missing");
        std::cout << COLOR_MAGENTA << head << "Created Conan files" << COLOR_RESET << std::endl;
        std::cout << COLOR_WHITE << head << "Created project" << COLOR_RESET << std::endl;
        std::cout << COLOR_GREEN << head << "Done" << COLOR_RESET << std::endl;
        return 0;
    }
}
