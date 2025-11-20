all:                                                                                                                            
	$(MAKE) launcher                                                                                                               
launcher: launcher.cpp
	rm -rf ./game/.gitkeep                                                                                                            
ifeq ($(OS),Windows_NT)                                                                                                                
	g++ launcher.cpp -o launcher.exe -std=c++14                                                                                    
	cp ./VC_redist.x86.exe ./game/                                                                                                 
	mv ./launcher.exe ./game/                                                                                                      
else                                                                                                                                   
	g++ launcher.cpp -o launcher                                                                                                   
	mv ./launcher ./game/                                                                                                          
endif
                                                                                             