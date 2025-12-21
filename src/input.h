/***
 * Name:input.h
 * Copyleft (C)2025 The TWOC Team**,License under GNU General Public License version 3.0 or later.
 * Authors:
 *     Dingbangzheng <1596664178@qq.com>
 * * TWOC means The world of character(https://github.com/Dingbangzheng/The-world-of-character).
 * ** The TWOC Team is a non-profit organization.
 ***/
#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif

class input {
private:
#ifdef _WIN32
    HANDLE hStdin;
    DWORD oldMode;
#else
    termios oldTermios;
#endif

public:
    input() {
#ifdef _WIN32
        hStdin = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hStdin, &oldMode);
        SetConsoleMode(hStdin, oldMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
#else
        tcgetattr(STDIN_FILENO, &oldTermios);
        termios newTermios = oldTermios;
        newTermios.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
#endif
    }

    ~input() {
#ifdef _WIN32
        SetConsoleMode(hStdin, oldMode);
#else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
    }

    static bool kbhit() {
#ifdef _WIN32
        return _kbhit() != 0;
#else
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        
        timeval timeout = {0, 0};
        return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout) > 0;
#endif
    }

    static char getch() {
#ifdef _WIN32
        if (_kbhit()) {
            return _getch();
        }
        return 0;
#else
        if (kbhit()) {
            char ch = 0;
            if (read(STDIN_FILENO, &ch, 1) == 1) {
                return ch;
            }
        }
        return 0;
#endif
    }

    static char getch_wait() {
#ifdef _WIN32
        return _getch();
#else
        char ch = 0;
        read(STDIN_FILENO, &ch, 1);
        return ch;
#endif
    }
};
#endif
