# The-world-of-character
The-world-of-character is an open-world 2D character game that supports hot updates.  
# Compatibility
[Windows] Windows that supports ANSI escape sequences, and the system needs to have curl (C:\Windows\System32\curl.exe)  
[Linux] Terminals that support ANSI escape sequences, and the system needs to have curl  
[MacOS] Official support is not currently provided.  
# Q&A
F: Windows prompts that the program cannot be started?  
A: Just run the included VC_redist.x86.exe to install the necessary runtime library (Microsoft Visual C++ Redistributable).  
# Note
[Essential software for Windows development] https://github.com/niXman/mingw-builds-binaries/releases  
https://www.7-zip.org/a/7z2501-x64.exe  
The VC_redist.x86.exe included in this repository is the essential runtime library (Microsoft Visual C++ Redistributable) for Windows development.  
[Essential software for Linux development]
g++  
make  
To compile, run "make help" or "make" in the root directory of the source code to view the compilation instructions, and compile as needed according to the prompts. After successful compilation, the game will be in the "./game/" directory.
