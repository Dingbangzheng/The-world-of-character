/***
 * Name:game.cpp(game.dll,game.so)
 * Copyleft (C)2025 The TWOC Team**,License under GNU General Public License version 3.0 or later.
 * Authors:
 *     Dingbangzheng <1596664178@qq.com>
 * * TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 * ** The TWOC Team is a non-profit organization.
 ***/
#include <iostream>
#include "tool.h"
#include "input.h"
extern "C"{
    #if defined(_WIN32) || defined(_WIN64)
        __declspec(dllexport)
    #endif
    input input_obj;
    void game(){
        cls();
        using namespace std;
        while(1){
            home();
            cout << "The world of character" << endl;
            cout << "1 -- Start single-player game" << endl;
            cout << "2 -- Connect servers" << endl;
            cout << "3 -- Exit" << endl;
            if(input::kbhit()){
                char ch = input::getch();
                if(ch == '1'){
                    //todo
		}else if(ch == '2'){
                    //todo
                }else if(ch == '3'){
                    return;
                }
            }
        }
    }
}
