# STM32F411CEU6_Project
Project using STM32F411CEU6 micro controller on Black Pill board. Bare metal programming. 

Developed the bare metal firmware for STM32F411CEU6 controller.

For learning purpose experimenting with the limited GPIOS in various versions listed on this repository.

version 001 : 
1. Developed the bare metal drivers for USART peripheral.
2. Developed the driver for SYSTICK Timer to synchronize various tasks. In this project included two tasks task50 and task100 which will be triggered by the SysTick Interrupt.
3. Developed modular functions to utilise various USART functionalities such as transmitting data and receiving data. No need to write the additional code for every USART peripheral. All the 3 USART peripherals are managed by same function acheiving modularity. Efficient Buffer management for the received Data by improvising a Ring Buffer.

What this version does ?
Transmits data over USART2 TX line to USART1 RX line of the same micro controller. Checks if the received data matches the static password assigned in the software. If does then turns on the LED present in Black Pill board PC13.
