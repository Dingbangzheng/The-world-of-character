launcher: launcher.cpp
ifeq ($(OS),Windows_NT)
	g++ launcher.cpp -o launcher.exe -static
else
	g++ launcher.cpp -o launcher
endif
