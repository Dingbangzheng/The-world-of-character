/***
 * Name:launcher.cpp
 * Copyleft (C)2025 The TWOC Team**,License under GNU General Public License version 3.0 or later.
 * Authors:
 *     Dingbangzheng <1596664178@qq.com>
 * * TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 * ** The TWOC Team is a non-profit organization.
 ***/
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>
#include "screen.h"
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PING_CMD "ping -n 1 dingbangzheng.cn > nul"
#else
    #include <unistd.h>
    #include <dlfcn.h>
    #define PING_CMD "ping -c 1 dingbangzheng.cn > /dev/null 2>&1"
#endif
int x = 0;
int y = 0;
int z = 1;
int ly, lz = 0;
extern "C" {
    #if defined(_WIN32) || defined(_WIN64)
    __declspec(dllexport)
    #endif
    int* getversionx() {
        static int* ptr = &x;
        return ptr;
    }
    #if defined(_WIN32) || defined(_WIN64)
    __declspec(dllexport)
    #endif
    int* getversiony() {
        static int* ptr = &y;
        return ptr;
    }
    #if defined(_WIN32) || defined(_WIN64)
    __declspec(dllexport)
    #endif
    int* getversionz() {
        static int* ptr = &z;
        return ptr;
    }
}
int check_network_connection() {
    int result = std::system(PING_CMD);
    return (result == 0) ? 1 : 0;
}
int main() {
    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    hidecursor();
    std::ofstream file("./logs.txt",std::ios::app);
    std::time_t timestamp = std::time(nullptr);
    file << timestamp << "-INFO[From=launcher,ID=un]:Game is start.Version:\"" << x << "." << y << "." << z << "\"." << std::endl;
    file.close();
    cls();
    std::cout << "The world of character Launcher" << std::endl;
    std::cout << "Check network connection..." << std::endl;
    if (check_network_connection()) {
        std::cout << "Pass and check for updates..." << std::endl;
        std::filesystem::remove("./latest_version.txt");
        std::string where = std::string("curl -s -L -O dingbangzheng.cn/twoc/") + std::to_string(x) + std::string(".y.z/latest_version.txt");
        std::system(where.c_str());
        if (std::filesystem::exists("./version.txt")) {
            std::ifstream file("./version.txt");
            std::string version;
            std::getline(file, version);
            file.close();
            std::sscanf(version.c_str(), ".%d.%d", &y, &z);
        } else {
            std::ofstream file("./version.txt");
            file << "." << y << "." << z;
            file.close();
        }
        if (std::filesystem::exists("./latest_version.txt")) {
            std::ifstream file("./latest_version.txt");
            std::string latest_version;
            std::getline(file, latest_version);
            file.close();
            std::sscanf(latest_version.c_str(), ".%d.%d", &ly, &lz);
            std::filesystem::remove("./latest_version.txt");
        } else {
            std::ofstream file("./logs.txt",std::ios::app);
            timestamp = std::time(nullptr);
            file << timestamp << "-ERROR[From=launcher,ID=1]:Can not find \"latest_version.txt\" or there is no \"curl\" command." << std::endl;
            file.close();
            std::cout << "ERROR[From=launcher,ID=1]:Can not find \"latest_version.txt\" or there is no \"curl\" command." << std::endl;
        }
        if (ly > y || lz > z) {
            std::filesystem::remove("./updatedata.txt");
            std::cout << "Download updatedata..." << std::endl;
            where = std::string("curl -s -L -O dingbangzheng.cn/twoc/") + std::to_string(x) + std::string(".y.z/updatedata.txt");
            std::system(where.c_str());
            if (std::filesystem::exists("./updatedata.txt")) {
                std::ifstream file("./updatedata.txt");
                std::string name;
                while (std::getline(file, name)) {
                    if (!name.empty() && name.back() == '\r') {
                        name.pop_back();
                    }
                    std::cout << "Remove old \"" << name;
                    #if defined(_WIN32) || defined(_WIN64)
                        std::cout << ".dll\"." << std::endl;
                        std::filesystem::remove("./data/" + name + ".dll");
                        std::cout << "Download and install \"" << name << ".dll\"." << std::endl;
                        where = std::string("curl -s -L -o ./data/" + name + ".dll dingbangzheng.cn/twoc/") + std::to_string(x) + std::string(".y.z/" + name + ".dll");
                        std::system(where.c_str());
                        std::ofstream file2("./logs.txt",std::ios::app);
                        timestamp = std::time(nullptr);
                        file2 << timestamp << "-INFO[From=launcher,ID=un]:Update \"" << name << ".dll\"." << std::endl;
                        file2.close();
                    #else
                        std::cout << ".so\"." << std::endl;
                        std::filesystem::remove("./data/" + name + ".so");
                        std::cout << "Download and install \"" << name << ".so\"." << std::endl;
                        where = std::string("curl -s -L -o ./data/" + name + ".so dingbangzheng.cn/twoc/") + std::to_string(x) + std::string(".y.z/" + name + ".so");
                        std::system(where.c_str());
                        std::ofstream file2("./logs.txt",std::ios::app);
                        timestamp = std::time(nullptr);
                        file2 << timestamp << "-INFO[From=launcher,ID=un]:Update \"" << name << ".so\"." << std::endl;
                        file2.close();
                    #endif
                }
		file.close();
                std::filesystem::remove("./updatedata.txt");
                std::ofstream file2("./logs.txt",std::ios::app);
                timestamp = std::time(nullptr);
                file2 << timestamp << "-INFO[From=launcher,ID=un]:Game is update from \"" << x << "." << y << "." << z << "\" to \"" << x << "." << ly << "." << lz << "\"." << std::endl;
                file2.close();
                y = ly;
                z = lz;
                std::ofstream file3("./version.txt");
                file3 << "." << y << "." << z << std::endl;
                file3.close();
            } else {
                std::ofstream file("./logs.txt",std::ios::app);
                timestamp = std::time(nullptr);
                file << timestamp << "-ERROR[From=launcher,ID=2]:Can not find \"updatedata.txt\" or there is no \"curl\" command." << std::endl;
                file.close();
                std::cout << "ERROR[From=launcher,ID=2]:Can not find \"updatedata.txt\" or there is no \"curl\" command." << std::endl;
            }
        } else {
            std::cout << "No updates." << std::endl;
        }
    } else {
        std::cout << "Not pass." << std::endl;
    }
    #if defined(_WIN32) || defined(_WIN64)
        std::cout << "Load and start game.dll..." << std::endl;
        HINSTANCE hDll = LoadLibrary("./data/game.dll");
        if (!hDll){
            std::ofstream file("./logs.txt",std::ios::app);
            timestamp = std::time(nullptr);
            file << timestamp << "-ERROR[From=launcher,ID=3]:Can not find \"./data/game.dll\"." << std::endl;
            file.close();
            std::cout << "ERROR[From=launcher,ID=3]:Can not find \"./data/game.dll\"." << std::endl;
        }else{
            auto game = (void(*)())GetProcAddress(hDll, "game");
            if(game){
                game();
            }else{
                std::ofstream file("./logs.txt",std::ios::app);
                timestamp = std::time(nullptr);
                file << timestamp << "-ERROR[From=launcher,ID=4]:Can not find \"game();\" from \"./data/game.dll\"." << std::endl;
                file.close();
                std::cout << "ERROR[From=launcher,ID=4]:Can not find \"game();\" from \"./data/game.dll\"." << std::endl;
            }
        }
        FreeLibrary(hDll);
    #else
        std::cout << "Load and start game.so..." << std::endl;
        void* lib = dlopen("./data/game.so", RTLD_LAZY);
        if (!lib){
            std::ofstream file("./logs.txt",std::ios::app);
            timestamp = std::time(nullptr);
            file << timestamp << "-ERROR[From=launcher,ID=3]:Can not find \"./data/game.so\"." << std::endl;
            file.close();
            std::cout << "ERROR[From=launcher,ID=3]:Can not find \"./data/game.so\"." << std::endl;
        }else{
            auto game = (void(*)())dlsym(lib, "game");
            if(game){
                game();
            }else{
                std::ofstream file("./logs.txt",std::ios::app);
                timestamp = std::time(nullptr);
                file << timestamp << "-ERROR[From=launcher,ID=4]:Can not find \"game();\" from \"./data/game.so\"." << std::endl;
                file.close();
                std::cout << "ERROR[From=launcher,ID=4]:Can not find \"game();\" from \"./data/game.so\"." << std::endl;
            }
        }
        dlclose(lib);
    #endif
    showcursor();
    return 0;
}
