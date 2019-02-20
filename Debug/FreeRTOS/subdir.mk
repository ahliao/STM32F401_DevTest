################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/event_groups.c \
../FreeRTOS/heap_4.c \
../FreeRTOS/list.c \
../FreeRTOS/port.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/event_groups.o \
./FreeRTOS/heap_4.o \
./FreeRTOS/list.o \
./FreeRTOS/port.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/event_groups.d \
./FreeRTOS/heap_4.d \
./FreeRTOS/list.d \
./FreeRTOS/port.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/%.o: ../FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DDEBUG -DSTM32F401xE -DUSE_HAL_DRIVER -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc/Legacy" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/Middlewares/Third_Party/FatFs/src/option" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/NHD-24-240320_Driver" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/include" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/FreeRTOS/" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/inc" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/device" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/CMSIS/core" -I"E:/STM32_Workbenches/STM32F401RE_FreeRTOS_SD/HAL_Driver/Inc" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


