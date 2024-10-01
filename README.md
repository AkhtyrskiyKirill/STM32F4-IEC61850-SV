# IEC 61850 Sampled Values publisher library for STM32

This code implements IEC 61850 Sampled Values protocol (publisher) ported to STM32 from https://github.com/mz-automation/libiec61850.
The demo project is created for STM32F429IGT6. It uses DP83848 Ethernet PHY.  
This implementation is based on LWIP stack with FreeRTOS. You can find the libiec61850 SV code in STM32F4_IEC61850_SV\Modules\libiec61850.  
The demo project code is located in STM32F4_IEC61850_SV\Core\Src\main.c and STM32F4_IEC61850_SV\Modules\SV.

## Demo project

The demo project implements 3-phase 50 Hz 230 V sine wave voltage simulation. The simulated signals are captured at 12800 Hz sample frequency 
(256 samples per period) and packed into IEC 61850 Sampled Values frames (8 ASDUs in one SV frame - 8 points in frame). There also are placeholders
for samples of current in frames. STM32 microcontroller uses this IEC61850 library to publish SV frames

## Project test

To test the project the STM32F429IGT6 dev board was connected directly to PC via ethernet cable. The SV frames were captured using Wireshark and
NetworkAnalyser (ПО "Сетевой анализатор", Динамика) software. 

![Screenshot](https://github.com/AkhtyrskiyKirill/STM32F4-IEC61850-SV/blob/main/imgs/SV_Wireshark.png)  

![Screenshot](https://github.com/AkhtyrskiyKirill/STM32F4-IEC61850-SV/blob/main/imgs/SV_frames_Info.png)

## Contact information

Authors of the project:  
Akhtyrskiy Kirill  
Kabirov Vagiz  

If you want to contribute to the improvement and development of the project please 
send comments, feature requests, bug reports, or patches.

Contact email: k.akhtirsky@gmail.com
