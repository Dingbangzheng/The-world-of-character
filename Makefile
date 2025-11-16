launcher: launcher.cpp
ifeq ($(OS),Windows_NT)
	g++ launcher.cpp -o launcher.exe -static -std=c++14
else
	g++ launcher.cpp -o launcher
endif
