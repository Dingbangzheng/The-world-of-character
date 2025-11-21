#include <iostream>
using namespace std;
int x = 0;
int y,ly,z,lz = 0;
#include <cstdlib>
#include <string>
#ifdef _WIN32
    #include <windows.h>
    #define PING_CMD "ping -n 1 dingbangzheng.cn > nul"
#else
    #include <unistd.h>
    #define PING_CMD "ping -c 1 dingbangzheng.cn > /dev/null 2>&1"
#endif
int check_network_connection() {
    int result = system(PING_CMD);
    return (result == 0) ? 1 : 0;
}
int main(){
    cout  <<  "The world of character Launcher"  <<  endl;
    cout  <<  "Checking network connection..."  <<  endl;
    if(check_network_connection()){
        cout  <<  "Checking for updates..."  <<  endl;
        string where = string("curl -s -L -O dingbangzheng.cn/twoc/") + to_string(x) + string(".y.z/latest_version.txt");
	    system(where.c_str());
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
