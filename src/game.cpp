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
