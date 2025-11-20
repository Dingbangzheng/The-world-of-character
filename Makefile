all:
	$(MAKE) launcher
launcher: launcher.cpp
ifeq ($(OS),Windows_NT)
	g++ launcher.cpp -o launcher.exe -static -std=c++14
	mv ./launcher.exe ./game/
else
	g++ launcher.cpp -o launcher
	mv ./launcher ./game/
endif
