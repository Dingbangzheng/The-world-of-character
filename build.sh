# /bin/bash
mkdir ./game/
mkdir ./game/data/
g++ -std=c++17 ./src/launcher.cpp -o ./game/launcher -ldl
g++ -shared -fPIC -o ./game/data/game.so ./src/game.cpp
