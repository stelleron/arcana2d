#include "res/Filesystem.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils/Logger.hpp"

namespace arcana {
    Filesystem::Filesystem() {
        currentWorkingDir = "";
    }

    void Filesystem::setDir(const std::string& dir) {
        currentWorkingDir = dir;
        if (dir[-1] != '/') {
            currentWorkingDir += '/';
        }
    }

    bool Filesystem::dirExists(const std::string& dir) {
        struct stat buffer;
        stat(dir.c_str(), &buffer);
        if (buffer.st_mode & S_IFDIR) {
            return true;
        }
        else {
            return false;
        }
    }

    bool Filesystem::fileExists(const std::string& path) {
        struct stat buffer;
        stat(path.c_str(), &buffer);
        if (buffer.st_mode & S_IFREG) {
            return true;
        }
        else {
            return false;
        }
    }

    std::string Filesystem::loadFileStr(const std::string& dir) {
        std::string path = currentWorkingDir;
        path += dir;
        std::ifstream fin(path, std::ios::in);
        std::stringstream buffer;
        buffer << fin.rdbuf() << '\0';
        return buffer.str();
    }

    char* Filesystem::loadFileText(const std::string& dir) {
        std::string source = loadFileStr(dir);
        char* buffer = new char[source.size()];
        memcpy( buffer, source.c_str(), source.size() );
        return buffer;
    }

    unsigned char* Filesystem::loadFileData(const std::string& dir) {
        std::string source = loadFileStr(dir);
        unsigned char* buffer = new unsigned char[source.size()];
        strcpy((char*)buffer, source.c_str());
        return buffer;
    }

    void Filesystem::unloadFileText(char* data) {
        delete[] data;
    }

    void Filesystem::unloadFileData(unsigned char* data) {
        delete[] data;
    }
    void Filesystem::saveFileStr(const std::string& path, const std::string& data) {
        std::string fpath = currentWorkingDir;
        fpath += path;
        std::ofstream output(fpath, std::ios::out);
        output << data;
    }
    void Filesystem::saveFileText(const std::string& path, char* data) {
        std::string fpath = currentWorkingDir;
        fpath += path;
        std::ofstream output(fpath, std::ios::out);
        output << data;
    }
    void Filesystem::saveFileData(const std::string& path, unsigned char* data) {
        std::string fpath = currentWorkingDir;
        fpath += path;
        std::ofstream output(fpath, std::ios::out);
        output << data;
    }
}