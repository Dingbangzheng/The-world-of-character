#ifndef INPUT_H
#define INPUT_H
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif
class input {
public:
    input() {
#ifndef _WIN32
        tcgetattr(STDIN_FILENO, &oldTermios);
        termios newTermios = oldTermios;
        newTermios.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
#endif
    }
    ~input() {
#ifndef _WIN32
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
    }
    static bool kbhit() {
#ifdef _WIN32
        return _kbhit() != 0;
#else
        int bytes = 0;
        ioctl(STDIN_FILENO, FIONREAD, &bytes);
        return bytes > 0;
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
            read(STDIN_FILENO, &ch, 1);
            return ch;
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
private:
#ifndef _WIN32
    termios oldTermios;
#endif
};
#endif
