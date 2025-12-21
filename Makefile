help:
	@echo "Help"
	@echo "make -- Help menu."
	@echo "make help -- Help menu."
	@echo "make all -- Compile all projects."
	@echo "make launcher -- Only compile launcher."
	@echo "make library -- Only compile the dynamic link library."
	@echo "make clean -- Clean up the compiled files(./game/*)."
	@echo "PS:The compiled files are placed in the "./game/" directory."

all:
	$(MAKE) launcher
	$(MAKE) library

launcher:./src/cls.h ./src/launcher.cpp
ifeq ($(OS),Windows_NT)
	mkdir .\game
	g++ -std=c++17 -lpsapi .\src\launcher.cpp -o .\game\launcher.exe
else
	mkdir ./game/
	g++ -std=c++17 -ldl ./src/launcher.cpp -o ./game/launcher
endif

library:./src/cls.h ./src/game.cpp
ifeq ($(OS),Windows_NT)
	mkdir .\game\data
	g++ -std=c++17 -shared -lpsapi -o .\game\data\game.dll .\src\game.cpp
else
	mkdir ./game/data/
	g++ -std=c++17 -shared -ldl -fPIC -o ./game/data/game.so ./src/game.cpp
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q .\game
else
	rm -rf ./game/
endif
