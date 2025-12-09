help:
	@echo "Help"
	@echo "make -- Help menu."
	@echo "make help -- Help menu."
	@echo "make all -- Compile all projects."
	@echo "make launcher -- Only compile launcher."
	@echo "make library -- Only compile the dynamic link library."
	@echo "make clean -- Clean up the compiled files(./game/*)."
	@echo "PS:The compiled files are placed in the "./game/" directory."

all:./src/cls.h ./src/launcher.cpp ./src/game.cpp
ifeq ($(OS),Windows_NT)
	mkdir .\game
	mkdir .\game\data
	g++ -std=c++17 .\src\launcher.cpp -o .\game\launcher.exe -lpsapi
	g++ -shared -o .\game\data\game.dll .\src\game.cpp
else
	mkdir ./game/
	mkdir ./game/data/
	g++ -std=c++17 ./src/launcher.cpp -o ./game/launcher -ldl
	g++ -shared -fPIC -o ./game/data/game.so ./src/game.cpp
endif

launcher:
	//todo

library:
	//todo

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q .\game
else
	rm -rf ./game/
endif
