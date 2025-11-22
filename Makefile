all:
ifeq ($(OS),Windows_NT)
	del ./game/.gitkeep /f /q
else
	rm -rf ./game/.gitkeep
endif
	$(MAKE) launcher

launcher: launcher.cpp
	g++ launcher.cpp -o launcher.exe -std=c++17
ifeq ($(OS),Windows_NT)
	xcopy ./VC_redist.x86.exe ./game/ /e /h /y
	move ./launcher.exe ./game/
else
	mv ./launcher ./game/
endif
