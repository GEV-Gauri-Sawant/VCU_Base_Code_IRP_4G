################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../4g_module/4g_data_process.c \
../4g_module/GPS.c \
../4g_module/V26_10sec_fleet.pb.c \
../4g_module/at_handler.c \
../4g_module/comman.c \
../4g_module/mdm_handler.c \
../4g_module/pb_common.c \
../4g_module/pb_encode.c \
../4g_module/sd_card.c 

OBJS += \
./4g_module/4g_data_process.o \
./4g_module/GPS.o \
./4g_module/V26_10sec_fleet.pb.o \
./4g_module/at_handler.o \
./4g_module/comman.o \
./4g_module/mdm_handler.o \
./4g_module/pb_common.o \
./4g_module/pb_encode.o \
./4g_module/sd_card.o 

C_DEPS += \
./4g_module/4g_data_process.d \
./4g_module/GPS.d \
./4g_module/V26_10sec_fleet.pb.d \
./4g_module/at_handler.d \
./4g_module/comman.d \
./4g_module/mdm_handler.d \
./4g_module/pb_common.d \
./4g_module/pb_encode.d \
./4g_module/sd_card.d 


# Each subdirectory must supply rules for building sources it contributes
4g_module/%.o: ../4g_module/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

