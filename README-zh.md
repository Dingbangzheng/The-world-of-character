# The-world-of-character
The-world-of-character是一个开放世界2D字符游戏，支持热更新。  
# 兼容性
[Windows]支持ANSI转译序列的Windows，需要系统有curl(C:\Windows\System32\curl.exe)  
[Linux]支持ANSI转译序列的终端，需要系统有curl  
[MacOS]目前不提供官方支持。  
# Q&A
F:Windows端提示无法启动程序？  
A:运行自带的VC_redist.x86.exe安装必须的运行库(Microsoft Visual C++ Redistributable)即可。  
# 备注
[Windows开发必备软件]  
https://github.com/niXman/mingw-builds-binaries/releases  
https://www.7-zip.org/a/7z2501-x64.exe  
本仓库自带的VC_redist.x86.exe是Windows开发必须的运行库(Microsoft Visual C++ Redistributable)。  
[Linux开发必备软件]  
g++  
make
# 编译
在源码根目录执行""make help""或""make""来查看编译提示，按照提示按需编译。编译成功后游戏在"./game/"中。  
