################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/ADC.c \
../LIB/Middleware.c \
../LIB/PIT.c \
../LIB/SysTick.c \
../LIB/UART.c \
../LIB/User_Clock.c \
../LIB/User_gpio.c \
../LIB/User_port.c 

C_DEPS += \
./LIB/ADC.d \
./LIB/Middleware.d \
./LIB/PIT.d \
./LIB/SysTick.d \
./LIB/UART.d \
./LIB/User_Clock.d \
./LIB/User_gpio.d \
./LIB/User_port.d 

OBJS += \
./LIB/ADC.o \
./LIB/Middleware.o \
./LIB/PIT.o \
./LIB/SysTick.o \
./LIB/UART.o \
./LIB/User_Clock.o \
./LIB/User_gpio.o \
./LIB/User_port.o 


# Each subdirectory must supply rules for building sources it contributes
LIB/%.o: ../LIB/%.c LIB/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\source" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\LIB" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\CMSIS" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/CMSIS\Include" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/CMSIS" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\startup" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/devices\MKL46Z4" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/devices" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-LIB

clean-LIB:
	-$(RM) ./LIB/ADC.d ./LIB/ADC.o ./LIB/Middleware.d ./LIB/Middleware.o ./LIB/PIT.d ./LIB/PIT.o ./LIB/SysTick.d ./LIB/SysTick.o ./LIB/UART.d ./LIB/UART.o ./LIB/User_Clock.d ./LIB/User_Clock.o ./LIB/User_gpio.d ./LIB/User_gpio.o ./LIB/User_port.d ./LIB/User_port.o

.PHONY: clean-LIB

