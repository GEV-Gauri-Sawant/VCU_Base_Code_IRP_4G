################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Can_Devices/OBD_II.c \
../Can_Devices/can_matrix_bms.c \
../Can_Devices/can_matrix_bms_29bit.c \
../Can_Devices/can_matrix_cluster.c \
../Can_Devices/can_matrix_eps.c \
../Can_Devices/can_matrix_hvac.c \
../Can_Devices/can_matrix_mc_curtis.c \
../Can_Devices/can_matrix_mc_gtake.c \
../Can_Devices/can_matrix_mc_gtake_29bit.c \
../Can_Devices/can_matrix_mc_irp.c \
../Can_Devices/can_matrix_obc_madhura.c \
../Can_Devices/can_matrix_obc_triphase.c 

OBJS += \
./Can_Devices/OBD_II.o \
./Can_Devices/can_matrix_bms.o \
./Can_Devices/can_matrix_bms_29bit.o \
./Can_Devices/can_matrix_cluster.o \
./Can_Devices/can_matrix_eps.o \
./Can_Devices/can_matrix_hvac.o \
./Can_Devices/can_matrix_mc_curtis.o \
./Can_Devices/can_matrix_mc_gtake.o \
./Can_Devices/can_matrix_mc_gtake_29bit.o \
./Can_Devices/can_matrix_mc_irp.o \
./Can_Devices/can_matrix_obc_madhura.o \
./Can_Devices/can_matrix_obc_triphase.o 

C_DEPS += \
./Can_Devices/OBD_II.d \
./Can_Devices/can_matrix_bms.d \
./Can_Devices/can_matrix_bms_29bit.d \
./Can_Devices/can_matrix_cluster.d \
./Can_Devices/can_matrix_eps.d \
./Can_Devices/can_matrix_hvac.d \
./Can_Devices/can_matrix_mc_curtis.d \
./Can_Devices/can_matrix_mc_gtake.d \
./Can_Devices/can_matrix_mc_gtake_29bit.d \
./Can_Devices/can_matrix_mc_irp.d \
./Can_Devices/can_matrix_obc_madhura.d \
./Can_Devices/can_matrix_obc_triphase.d 


# Each subdirectory must supply rules for building sources it contributes
Can_Devices/%.o: ../Can_Devices/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

