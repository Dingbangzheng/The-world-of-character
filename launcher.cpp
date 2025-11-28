#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PING_CMD "ping -n 1 dingbangzheng.cn > nul"
#else
    #include <unistd.h>
    #define PING_CMD "ping -c 1 dingbangzheng.cn > /dev/null 2>&1"
#endif

int x = 0;
int y = 0;
int z = 1;
int ly, lz = 0;

void cls() {
    std::cout << "\033[2J\033[H";
    return;
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
    
    cls();
    std::cout << "The world of character Launcher" << std::endl;
    
    std::ofstream file("./logs.txt");
    std::time_t timestamp = std::time(nullptr);
    file << timestamp << "-Info[From=launcher]:Game is start." << std::endl;
    file.close();
    
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
            std::ofstream file("./logs.txt");
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
                    #else
                        std::cout << ".so\"." << std::endl;
                        std::filesystem::remove("./data/" + name + ".so");
                        std::cout << "Download and install \"" << name << ".so\"." << std::endl;
                        where = std::string("curl -s -L -o ./data/" + name + ".so dingbangzheng.cn/twoc/") + std::to_string(x) + std::string(".y.z/" + name + ".so");
                        std::system(where.c_str());
                    #endif
                }
                std::filesystem::remove("./updatedata.txt");
                y = ly;
                z = lz;
                std::ofstream file2("./version.txt");
                file2 << "." << y << "." << z << std::endl;
                file2.close();
            } else {
                std::ofstream file("./logs.txt");
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
        //todo
    #else
        std::cout << "Load and start game.so..." << std::endl;
        //todo
    #endif
    
    return 0;
}
