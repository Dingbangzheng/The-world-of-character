/***
 * Name:game.cpp(game.dll,game.so)
 * Version(TWOC):0.0.1
 * Copyleft (C)2025 The TWOC Team*,License under GNU General Public License version 3.0 or later.
 * By:
 *     Dingbangzheng <1596664178@qq.com>
 * Introduce:
 *     This is the core function of TWOC.
 * *The TWOC Team is a non-profit organization.TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 ***/
#include <iostream>
#include "cls.h"
extern "C"{
    #if defined(_WIN32) || defined(_WIN64)
        __declspec(dllexport)
    #endif
    void game(){
        cls();
        //todo
    }
}
