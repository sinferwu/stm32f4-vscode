# stm32f4 on vscode

为了后面的内核学习先准备一下普通的stm32开发环境。
 
## Jlink

[jlink](https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPackBeta)

用`dpkg -i xxx.deb`安装即可，安装完成后终端输入`JLinkExe`可以检查安装是否成功。

## gcc-arm

[gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

安装流程大致参考[这里](https://www.cnblogs.com/fymeng/p/11637642.html)即可

## 安装stm32cube-mx

主要临时生成一下makefile用。

竟然要先装jre，`sudo apt-get install default-jre`，顺便解压`.exe`文件

安装完成后创建一个工程。

随便配置一个[点灯](https://blog.csdn.net/Aa_lihua/article/details/88087202)的项目然后生成文件的`Makefile`

此时`cd cube`然后`make`已经可以编译成功

```bash
# 一大堆生成结果
   text    data     bss     dec     hex filename
   4164      20    1572    5756    167c build/cube.elf
arm-none-eabi-objcopy -O ihex build/cube.elf build/cube.hex
arm-none-eabi-objcopy -O binary -S build/cube.elf build/cube.bin
```

**主要参考**：
[用VS Code开发STM32（二）——编译](https://zhuanlan.zhihu.com/p/61538230)
[用VS Code开发STM32（三）——调试](https://zhuanlan.zhihu.com/p/61541590)