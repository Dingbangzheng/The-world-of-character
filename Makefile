.SUFFIXES:
%:: %,v
%:: RCS/%,v
%:: RCS/%
%:: s.%
%:: SCCS/s.%
all:
ifeq ($(OS),Windows_NT)
	del .\game\.gitkeep /f /q
else
	rm -rf ./game/.gitkeep
endif
	$(MAKE) launcher
launcher: launcher.cpp
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 launcher.cpp -o launcher.exe
	xcopy .\VC_redist.x86.exe .\game\ /e /h /y
	move .\launcher.exe .\game\
else
	g++ -std=c++17 launcher.cpp -o launcher
	mv ./launcher ./game/
endif
