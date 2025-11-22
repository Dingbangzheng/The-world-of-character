# The-world-of-character
The-world-of-character是一个开放世界2D字符游戏，支持热更新。
# 兼容性
[Windows]支持ANSI转译序列的Windows(Windows10的10周年纪念版及以上)，需要系统有curl  
[Linux]支持ANSI转译序列的终端，需要系统有curl  
[MacOS]目前不提供官方支持。  
# Q&A
F:Windows端提示无法启动程序？  
A:运行自带的VC_redist.x86.exe安装必须的运行库即可。  
F:在Windows的powershell中使用make来按照Makefile编译程序为什么会报错？程序代码没问题。  
A:因为Makefile中进行移动，拷贝，删除文件使用的是cmd的指令，所以请切换到cmd中再make。  
# 备注
[Windows开发必备软件]  
https://github.com/niXman/mingw-builds-binaries/releases  
https://www.7-zip.org/a/7z2501-x64.exe  
本仓库自带的VC_redist.x86.exe是Windows开发必须的运行库。  
[Linux开发必备软件]  
g++  
make  
