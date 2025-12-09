/***
 * Name:cls.h
 * Version(TWOC):0.0.1
 * Copyleft (C)2025 The TWOC Team*,License under GNU General Public License version 3.0 or later.
 * By:
 *     Dingbangzheng <1596664178@qq.com>
 * Introduce:
 *     This is the header file of the TWOC screen clearing function.
 * *The TWOC Team is a non-profit organization.TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 ***/
#include <iostream>
void cls() {
    std::cout << "\033[2J\033[H";
    return;
}
