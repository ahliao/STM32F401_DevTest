################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PrintfTask.c \
../src/bsp_driver_sd.c \
../src/fatfs.c \
../src/main.c \
../src/sd_diskio.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/PrintfTask.o \
./src/bsp_driver_sd.o \
./src/fatfs.o \
./src/main.o \
./src/sd_diskio.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/PrintfTask.d \
./src/bsp_driver_sd.d \
./src/fatfs.d \
./src/main.d \
./src/sd_diskio.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/PrintfTask.o: ../src/PrintfTask.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc/Legacy" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src/option" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/NHD-24-240320_Driver" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/include" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/inc" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/device" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/core" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc/Legacy" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src/option" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/NHD-24-240320_Driver" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/include" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/inc" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/device" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/core" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


