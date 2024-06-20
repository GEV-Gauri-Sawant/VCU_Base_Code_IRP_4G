################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VCU_PROCESS/Faults_Process.c \
../VCU_PROCESS/RTC.c \
../VCU_PROCESS/State1_Process.c \
../VCU_PROCESS/State2_Process.c \
../VCU_PROCESS/Vcu_Process.c \
../VCU_PROCESS/init_hw.c 

OBJS += \
./VCU_PROCESS/Faults_Process.o \
./VCU_PROCESS/RTC.o \
./VCU_PROCESS/State1_Process.o \
./VCU_PROCESS/State2_Process.o \
./VCU_PROCESS/Vcu_Process.o \
./VCU_PROCESS/init_hw.o 

C_DEPS += \
./VCU_PROCESS/Faults_Process.d \
./VCU_PROCESS/RTC.d \
./VCU_PROCESS/State1_Process.d \
./VCU_PROCESS/State2_Process.d \
./VCU_PROCESS/Vcu_Process.d \
./VCU_PROCESS/init_hw.d 


# Each subdirectory must supply rules for building sources it contributes
VCU_PROCESS/%.o: ../VCU_PROCESS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

