#include <iostream>
using namespace std;
int x = 0;
int y = 0;
int z = 1;
int ly,lz = 0;
#include <cstdlib>
#include <string>
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PING_CMD "ping -n 1 dingbangzheng.cn > nul"
#else
    #include <unistd.h>
    #define PING_CMD "ping -c 1 dingbangzheng.cn > /dev/null 2>&1"
#endif
#include <filesystem>
#include <fstream>
#include <ctime>
int check_network_connection() {
    int result = system(PING_CMD);
    return (result == 0) ? 1 : 0;
}
int main(){
    #if defined(_WIN32)  ||  defined(_WIN64)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    cout  <<  "The world of character Launcher"  <<  endl;
    ofstream file("./logs.txt");
    time_t timestamp = time(nullptr);
    file <<  timestamp  <<  "-Info[From=launcher]:Game is start."  <<  endl;
    file.close();
    cout  <<  "Check network connection..."  <<  endl;
    if(check_network_connection()){
        cout  <<  "Pass and check for updates..."  <<  endl;
        filesystem::remove("./latest_version.txt");
        string where = string("curl -s -L -O dingbangzheng.cn/twoc/") + to_string(x) + string(".y.z/latest_version.txt");
        system(where.c_str());
        if(filesystem::exists("./version.txt")){
            ifstream file("./version.txt");
            string version;
            getline(file,version);
            file.close();
            sscanf(version.c_str(),".%d.%d",&y,&z);
        }else{
            ofstream file("./version.txt");
            file << "." << y << "." << z;
            file.close();
        }
        if(filesystem::exists("./latest_version.txt")){
            ifstream file("./latest_version.txt");
            string latest_version;
            getline(file,latest_version);
            file.close();
            sscanf(latest_version.c_str(),".%d.%d",&ly,&lz);
            filesystem::remove("./latest_version.txt");
        }else{
            ofstream file("./logs.txt");
            timestamp = time(nullptr);
            file <<  timestamp  <<  "-ERROR[From=launcher,ID=1]:Can not find \"latest_version.txt\" or there is no \"curl\" command."  <<  endl;
            file.close();
            cout << "ERROR[From=launcher,ID=1]:Can not find \"latest_version.txt\" or there is no \"curl\" command."  <<  endl;
        }
        if(ly > y || lz > z){
            filesystem::remove("./updatedata.txt");
            cout  <<  "Download updatedata..."  <<  endl;
            where = string("curl -s -L -O dingbangzheng.cn/twoc/") + to_string(x) + string(".y.z/updatedata.txt");
            system(where.c_str());
            if(filesystem::exists("./updatedata.txt")){
                ifstream file("./updatedata.txt");
                string name;
                while(getline(file,name)){
                    if(!name.empty()  &&  name.back()  ==  '\r'){
                        name.pop_back();
                    }
                    cout  <<  "Remove old \"" <<  name;
                    #if defined(_WIN32) || defined(_WIN64)
                    cout  <<  ".dll\"."  <<  endl;
                    filesystem::remove("./data/" + name + ".dll");
                    cout  <<  "Download and install \""  <<  name  <<  ".dll\"."  <<  endl;
                    where = string("curl -s -L -o ./data/" + name + ".dll dingbangzheng.cn/twoc/") + to_string(x) + string(".y.z/" + name + ".dll");
		    system(where.c_str());
                    #else
                    cout  <<  ".so\"."  <<  endl;
                    filesystem::remove("./data/" + name + ".so");
                    cout  <<  "Download and install \""  <<  name  <<  ".so\"."  <<  endl;
                    where = string("curl -s -L -o ./data/" + name + ".so dingbangzheng.cn/twoc/") + to_string(x) + string(".y.z/" + name + ".so");
                    system(where.c_str());
                    #endif
                }
                filesystem::remove("./updatedata.txt");
                y = ly;
                z = lz;
                ofstream file2("./version.txt");
                file2  <<  "."  <<  y  <<  "."  <<  z  <<endl;
                file2.close();
            }else{
                ofstream file("./logs.txt");
		timestamp = time(nullptr);
                file <<  timestamp  <<  "-ERROR[From=launcher,ID=2]:Can not find \"updatedata.txt\" or there is no \"curl\" command."  <<  endl;
                file.close();
                cout << "ERROR[From=launcher,ID=2]:Can not find \"updatedata.txt\" or there is no \"curl\" command."  <<  endl;
            }
        }else{
            cout  <<  "No updates."  <<  endl;
        }
    }else{
        cout << "Not pass."  <<  endl;
    }
    #if defined(_WIN32) || defined(_WIN64)
        cout  <<  "Load and start game.dll..."  <<  endl;
        //todo
    #else
        cout  <<  "Load and start game.so..."  <<  endl;
        //todo
    #endif
    return 0;
}
