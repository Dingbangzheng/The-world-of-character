/***
 * Name:tool.h
 * Copyleft (C)2025 The TWOC Team**,License under GNU General Public License version 3.0 or later.
 * Authors:
 *     Dingbangzheng <1596664178@qq.com>
 * * TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 * ** The TWOC Team is a non-profit organization.
 ***/
#include <iostream>
void cls(){
    std::cout << "\033[2J\033[H";
    return;
}
void home(){
    std::cout << "\033[H";
    return;
}
