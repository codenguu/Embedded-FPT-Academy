################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Assignment_03_Integration_Application.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/Assignment_03_Integration_Application.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/Assignment_03_Integration_Application.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\source" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\LIB" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\CMSIS" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/CMSIS\Include" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/CMSIS" -I"D:\EmbeddedDevFA\EMBEDDED\KL46\Workspace\Assignment_03_Integration Application\startup" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/devices\MKL46Z4" -I"C:\Users\SF\mcuxpresso\02\SDKPackages\SDK_2_4_1_FRDM-KL46Z/devices" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Assignment_03_Integration_Application.d ./source/Assignment_03_Integration_Application.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

