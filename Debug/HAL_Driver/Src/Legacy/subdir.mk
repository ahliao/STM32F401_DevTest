################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c 

OBJS += \
./HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o 

C_DEPS += \
./HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/Legacy/%.o: ../HAL_Driver/Src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc/Legacy" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src/option" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/NHD-24-240320_Driver" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/include" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/inc" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/device" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/core" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


