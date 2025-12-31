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
    #define PING_CMD "ping -n 1 8.8.8.8 > nul"
#else
    #include <unistd.h>
    #include <dlfcn.h>
    #define PING_CMD "ping -c 1 8.8.8.8 > /dev/null 2>&1"
#endif
int x = 0;
int y = 0;
int z = 1;
int ly = 0 , lz = 0;
std::string server = "http://dingbangzheng.cn/twoc/";
int check_network_connection() {
    int result = std::system(PING_CMD);
    return (result == 0) ? 1 : 0;
}
int main(){
    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    hidecursor();
    std::ofstream logs("./logs" , std::ios::app);
    std::time_t timestamp = std::time(nullptr);
    logs << timestamp << "-INFO[From=launcher,ID=un]:Game is start.Version:\"" << x << "." << y << "." << z << "\"." << std::endl;
    logs.close();
    cls();
    std::cout << "The world of character Launcher" << std::endl;
    std::cout << "Check network connection..." << std::endl;
    if (std::filesystem::exists("./data_server.conf")) {
        std::ifstream data_server("./data_server.conf");
        std::getline(data_server , server);
        data_server.close();
    } else {
        std::ofstream data_server("./data_server.conf");
        data_server << server;
        data_server.close();
    }
    if (check_network_connection()) {
        std::cout << "Pass and check for updates..." << std::endl;
        std::filesystem::remove("./last_version_y");
        std::filesystem::remove("./last_version_z");
        if (std::filesystem::exists("./version")){
            std::ifstream file_version("./version");
            std::string string_version;
            std::getline(file_version , string_version);
            file_version.close();
            std::sscanf(string_version.c_str() , ".%d.%d" , &y , &z);
        } else {
            std::ofstream version("./version");
            version << "." << y << "." << z;
            version.close();
        }
        std::string get = std::string("curl -s -L -O " + server) + std::to_string(x) + std::string(".y.z/last_version_y");
        std::system(get.c_str());
        if (std::filesystem::exists("./last_version_y")) {
            std::ifstream file_last_version_y("./last_version_y");
            std::string string_last_version_y;
            std::getline(file_last_version_y , string_last_version_y);
            file_last_version_y.close();
            std::sscanf(string_last_version_y.c_str() , "%d" , &ly);
            std::filesystem::remove("./last_version_y");
            get = std::string("curl -s -L -O " + server) + std::to_string(x) + std::string(".y.z/.") + std::to_string(y) + std::string(".z/last_version_z");
            std::system(get.c_str());
            if (std::filesystem::exists("./last_version_z")) {
                std::ifstream file_last_version_z("./last_version_z");
            std::string string_last_version_z;
            std::getline(file_last_version_z , string_last_version_z);
            file_last_version_z.close();
            std::sscanf(string_last_version_z.c_str() , "%d" , &lz);
            std::filesystem::remove("./last_version_z");
            }
        } else {
            std::ofstream logs("./logs",std::ios::app);
            timestamp = std::time(nullptr);
            logs << timestamp << "-ERROR[From=launcher,ID=1]:Can not find \"latest_version_y\" or there is no \"curl\" command." << std::endl;
            logs.close();
            std::cout << "ERROR[From=launcher,ID=1]:Can not find \"latest_version_y\" or there is no \"curl\" command." << std::endl;
        }
        if (ly > y || lz > z) {
            std::filesystem::remove("./updatedata");
            std::cout << "Download updatedata..." << std::endl;
            //todo
        }
    } 
    showcursor();
    return 0;
}
