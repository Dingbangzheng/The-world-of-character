@echo off
mkdir .\game
mkdir .\game\data
g++ -std=c++17 .\src\launcher.cpp -o .\game\launcher.exe -ldl
g++ -shared -o .\game\data\game.dll .\src\game.cpp
