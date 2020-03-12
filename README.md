# stm32f4 on vscode

为了后面的内核学习先准备一下普通的stm32开发环境。

## 开发环境准备

### Jlink

[jlink](https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPackBeta)下载地址

用`dpkg -i xxx.deb`安装即可，安装完成后终端输入`JLinkExe`可以检查安装是否成功。

### gcc-arm

[gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

安装流程大致参考[这里](https://www.cnblogs.com/fymeng/p/11637642.html)即可

### 安装stm32cube-mx

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

**调试工具**：  

插件——————Cortex Debug  
GDB——————arm-none-eabi-gdb  
GDB Server————JLinkGDBServer  
仿真器——————Jlink  
MCU——————STM32F407VE  

在debug界面点击`RUN AND DEBUG`可以看到加载过程，会卡在

```
Please check OUTPUT tab (Adapter Output) for output from JLinkGDBServer
Launching server: "JLinkGDBServer" "-if" "jtag" "-port" "50000" "-swoport" "50001" "-telnetport" "50002" "-device" "STM32F407VE"
Launching GDB: "arm-none-eabi-gdb" "-q" "--interpreter=mi2"
Reading symbols from /home/yogurtsuee/stm32f4-vscode/cube/build/cube.elf...
0x08000f82 in HAL_GetTick () at Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c:325
325	  return uwTick;
Not implemented stop reason (assuming exception): undefined
Resetting target
Resetting target
```

这里点一下`Continue`或者`F5`就可以看到程序开始运行并且可以随时暂停，点灯成功。

## 移植ucos

[STM32 uCOS-III GCC移植说明](https://blog.csdn.net/Chuancey_CC/article/details/84844740)

[STM32 HAL库移植ucos](https://blog.csdn.net/lingsuifenfei123/article/details/66972711?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)

[STM32 HAL库移植ucos](https://blog.csdn.net/u014779536/article/details/104047851?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)

[STM32-MAKEFILE模板](https://blog.csdn.net/subfate/article/details/86268016)

[gcc-arm开发](https://www.mikrocontroller.net/attachment/92976/Porting_ucOSII_to_ARM.pdf)

主要修改两个地方：

**Makefile**-添加所有的`.c`文件，和`.s`文件，`include`路径，如果有遗漏可能会出现缺少依赖的情况（ld报错）

**启动文件**-将启动文件中的PendSV_Handler和SysTick_Handler 修改为OS_CPU_PendSVHandler和OS_CPU_SysTickHandler

此时`make`可以通过编译。

