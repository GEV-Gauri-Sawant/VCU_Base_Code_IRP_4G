################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include timer_manager/subdir.mk
-include state_detect_action/subdir.mk
-include VCU_PROCESS/subdir.mk
-include VCU_OUT/subdir.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include InputCapture/subdir.mk
-include Dave/Generated/WATCHDOG/subdir.mk
-include Dave/Generated/UART/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/SYSTIMER/subdir.mk
-include Dave/Generated/SPI_MASTER/subdir.mk
-include Dave/Generated/SDMMC_BLOCK/subdir.mk
-include Dave/Generated/RTC/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/I2C_MASTER/subdir.mk
-include Dave/Generated/GLOBAL_DMA/subdir.mk
-include Dave/Generated/GLOBAL_CCU8/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_CAN/subdir.mk
-include Dave/Generated/FATFS/ff_Src/subdir.mk
-include Dave/Generated/FATFS/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/CAN_NODE/subdir.mk
-include Dave/Generated/subdir.mk
-include Can_Devices/subdir.mk
-include 4g_module/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.hex \

SECONDARY_LIST += \
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.lst \

SECONDARY_SIZE += \
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.map"

TOOLCHAIN_ROOT=C:/Infineon/Tools/DAVE IDE/4.5.0.202105191637/eclipse/ARM-GCC-49
PROJECT_LOC=D:/Projects/VCU Firmware Main/IRP/Git Repo/VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data

# All Target
all: VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf secondary-outputs

# Tool invocations
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.hex: VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf" "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.hex"
	@echo 'Finished building: $@'
	@echo.
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.lst: VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf" > "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.lst"
	@echo 'Finished building: $@'
	@echo.
VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.siz: VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) 4g_module/4g_data_process.o 4g_module/GPS.o 4g_module/V26_10sec_fleet.pb.o 4g_module/at_handler.o 4g_module/comman.o 4g_module/mdm_handler.o 4g_module/pb_common.o 4g_module/pb_encode.o 4g_module/sd_card.o Can_Devices/OBD_II.o Can_Devices/can_matrix_bms.o Can_Devices/can_matrix_bms_29bit.o Can_Devices/can_matrix_cluster.o Can_Devices/can_matrix_eps.o Can_Devices/can_matrix_hvac.o Can_Devices/can_matrix_mc_curtis.o Can_Devices/can_matrix_mc_gtake.o Can_Devices/can_matrix_mc_gtake_29bit.o Can_Devices/can_matrix_mc_irp.o Can_Devices/can_matrix_obc_madhura.o Can_Devices/can_matrix_obc_triphase.o Dave/Generated/CAN_NODE/can_node.o Dave/Generated/CAN_NODE/can_node_conf.o Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/FATFS/fatfs.o Dave/Generated/FATFS/fatfs_conf.o Dave/Generated/FATFS/sltha.o Dave/Generated/FATFS/ff_Src/ff.o Dave/Generated/FATFS/ff_Src/ffsystem.o Dave/Generated/FATFS/ff_Src/ffunicode.o Dave/Generated/GLOBAL_CAN/global_can.o Dave/Generated/GLOBAL_CAN/global_can_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/GLOBAL_CCU8/global_ccu8.o Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o Dave/Generated/GLOBAL_DMA/global_dma.o Dave/Generated/GLOBAL_DMA/global_dma_conf.o Dave/Generated/I2C_MASTER/i2c_master.o Dave/Generated/I2C_MASTER/i2c_master_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/RTC/rtc.o Dave/Generated/RTC/rtc_conf.o Dave/Generated/SDMMC_BLOCK/sdmmc_block.o Dave/Generated/SDMMC_BLOCK/sdmmc_block_conf.o Dave/Generated/SDMMC_BLOCK/sdmmc_block_private_spi.o Dave/Generated/SPI_MASTER/spi_master.o Dave/Generated/SPI_MASTER/spi_master_conf.o 
	-$(RM) Dave/Generated/SYSTIMER/systimer.o Dave/Generated/SYSTIMER/systimer_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Dave/Generated/UART/uart.o Dave/Generated/UART/uart_conf.o Dave/Generated/WATCHDOG/watchdog.o Dave/Generated/WATCHDOG/watchdog_conf.o InputCapture/IOExp_lib.o InputCapture/InputCapture.o InputCapture/State_1_InputCapture.o InputCapture/State_2_InputCapture.o InputCapture/temp_sensors.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Startup/startup_XMC4700.o Startup/system_XMC4700.o VCU_OUT/ADS7961_LIB_2.o VCU_OUT/State_1.o VCU_OUT/State_2.o VCU_OUT/Vcu_Out.o VCU_PROCESS/Faults_Process.o VCU_PROCESS/RTC.o VCU_PROCESS/State1_Process.o VCU_PROCESS/State2_Process.o VCU_PROCESS/Vcu_Process.o VCU_PROCESS/init_hw.o Vcu_Init.o main.o state_detect_action/state_IG1.o 
	-$(RM) timer_manager/timer_manager.o  VCU14_29bit_overCAN_withIRP_new4g_proto26_adding_All10sec_data.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
