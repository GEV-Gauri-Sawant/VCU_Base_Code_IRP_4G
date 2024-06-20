################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../InputCapture/IOExp_lib.c \
../InputCapture/InputCapture.c \
../InputCapture/State_1_InputCapture.c \
../InputCapture/State_2_InputCapture.c \
../InputCapture/temp_sensors.c 

OBJS += \
./InputCapture/IOExp_lib.o \
./InputCapture/InputCapture.o \
./InputCapture/State_1_InputCapture.o \
./InputCapture/State_2_InputCapture.o \
./InputCapture/temp_sensors.o 

C_DEPS += \
./InputCapture/IOExp_lib.d \
./InputCapture/InputCapture.d \
./InputCapture/State_1_InputCapture.d \
./InputCapture/State_2_InputCapture.d \
./InputCapture/temp_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
InputCapture/%.o: ../InputCapture/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

