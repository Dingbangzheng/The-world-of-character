# The-world-of-character  
The-world-of-character is an open-world 2D character game that supports hot updates.  
# Compatibility  
[Windows] Windows with ANSI escape sequence support, requires curl (C:\Windows\System32\curl.exe) to be present on the system.  
[Linux] Terminals with ANSI escape sequence support, requires curl to be installed on the system.  
[MacOS] Official support is not currently provided.  
# Q&A  
Q: The Windows version prompts that the program cannot be started?  
A: Run the included VC_redist.x86.exe to install the necessary runtime libraries (Microsoft Visual C++ Redistributable).  
# Notes  
[Essential Software for Windows Development]  
https://github.com/niXman/mingw-builds-binaries/releases  
https://www.7-zip.org/a/7z2501-x64.exe  
The VC_redist.x86.exe included in this repository is the essential runtime library (Microsoft Visual C++ Redistributable) for Windows development.  
[Essential Software for Linux Development]  
g++  
make  
# Compilation  
Execute `make help` or `make` in the source code root directory to view compilation instructions. Compile as needed according to the prompts. After successful compilation, the game will be located in `./game/`.
