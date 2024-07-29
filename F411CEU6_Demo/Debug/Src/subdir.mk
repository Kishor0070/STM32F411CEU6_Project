################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/custom_systick.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/task100_pou.c \
../Src/task50_pou.c \
../Src/usart_lib.c 

OBJS += \
./Src/custom_systick.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/task100_pou.o \
./Src/task50_pou.o \
./Src/usart_lib.o 

C_DEPS += \
./Src/custom_systick.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/task100_pou.d \
./Src/task50_pou.d \
./Src/usart_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"C:/Users/bhadula.kishor/BACKUP_DATA/Personal/STM32_TUTS/PROJECTS/PROJECT_2/CHIP_Headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/bhadula.kishor/BACKUP_DATA/Personal/STM32_TUTS/PROJECTS/PROJECT_2/CHIP_Headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/custom_systick.cyclo ./Src/custom_systick.d ./Src/custom_systick.o ./Src/custom_systick.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/task100_pou.cyclo ./Src/task100_pou.d ./Src/task100_pou.o ./Src/task100_pou.su ./Src/task50_pou.cyclo ./Src/task50_pou.d ./Src/task50_pou.o ./Src/task50_pou.su ./Src/usart_lib.cyclo ./Src/usart_lib.d ./Src/usart_lib.o ./Src/usart_lib.su

.PHONY: clean-Src

