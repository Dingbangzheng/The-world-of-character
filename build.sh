# /bin/bash
rm -rf ./game/.gitkeep
g++ -std=c++17 launcher.cpp -o launcher -O3 -Wall
mv launcher ./game/
