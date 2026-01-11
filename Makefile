help:
	@echo "Help"
	@echo "make -- Help menu."
	@echo "make help -- Help menu."
	@echo "make all -- Compile all projects."
	@echo "make launcher -- Only compile launcher."
	@echo "make library -- Only compile the dynamic link library."
	@echo "make clean -- Clean up the compiled files(./build/*)."
	@echo "PS:The compiled files are placed in the "./build/" directory."

all:
	$(MAKE) launcher
	$(MAKE) library

launcher: ./src/screen.h ./src/launcher.cpp
ifeq ($(OS),Windows_NT)
	@if not exist .\build mkdir .\build
	g++ -std=c++17 -lpsapi .\src\launcher.cpp -o .\build\launcher.exe
else
	@if [ ! -d ./build ]; then mkdir -p ./build; fi
	g++ -std=c++17 -rdynamic -ldl ./src/launcher.cpp -o ./build/launcher
endif

library: ./src/screen.h ./src/game.cpp
ifeq ($(OS),Windows_NT)
	@if not exist .\build\data mkdir .\build\data
	g++ -std=c++17 -shared -lpsapi -o .\build\data\game.dll .\src\game.cpp
else
	@if [ ! -d ./build/data ]; then mkdir -p ./build/data; fi
	g++ -std=c++17 -shared -ldl -fPIC -o ./build/data/game.so ./src/game.cpp
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist .\build rmdir /s /q .\build
else
	rm -rf ./build/
endif

.PHONY: help all launcher library clean
