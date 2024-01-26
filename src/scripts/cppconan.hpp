#include <string>

namespace CPPConan {
    bool satisfiesDepends();
    int createDirectory(std::string path);
    int createFile(std::string path, std::string contents);
    bool exists(std::string path);
    bool isDirectoryEmpty(std::string path);
    int create(std::string projectName);
}
