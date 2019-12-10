################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c2000_6.1.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./app/SCHEDULER.obj" \
"./app/INIT_APP.obj" \
"./app/I2T_APP.obj" \
"./app/GPIO_APP.obj" \
"./app/ECAN_APP.obj" \
"./app/COMMON.obj" \
"./app/CBIT_APP.obj" \
"./app/CAN_BUF.obj" \
"./app/ARG_MAIN.obj" \
"./dsp/WDG.obj" \
"./dsp/TLV5638.obj" \
"./dsp/SYS_CTRL.obj" \
"./dsp/SPI.obj" \
"./dsp/SCI.obj" \
"./dsp/PIE_VECT.obj" \
"./dsp/PIE_CTRL.obj" \
"./dsp/MCU.obj" \
"./dsp/I2C.obj" \
"./dsp/GPIO.obj" \
"./dsp/EEPROM.obj" \
"./dsp/ECAN.obj" \
"./dsp/DEVICE.obj" \
"./dsp/DEFAULT_ISR.obj" \
"./dsp/ADC.obj" \
"./l_div.obj" \
"./fs_toul.obj" \
"./fs_mpy.obj" \
"./dsp2833x_usdelay.obj" \
"./dsp2833x_codestartbranch.obj" \
"./dsp2833x_adc_cal.obj" \
"./cinit.obj" \
"./boot_def.obj" \
"../dsp2833x_headers_nonbios.cmd" \
"../f28335_release.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include dsp/subdir_vars.mk
-include app/subdir_vars.mk
-include subdir_rules.mk
-include dsp/subdir_rules.mk
-include app/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MA700_SPDS.out

# Tool invocations
MA700_SPDS.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" -z --stack_size=0x400 -m"MA700_SPDS.map" --warn_sections -i"D:/MA 700/MA700-SPDS-A(19_11_26)/head" -i"D:/MA 700/MA700-SPDS-A(19_11_26)/lru" -i"D:/MA 700/MA700-SPDS-A(19_11_26)/config" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --reread_libs --disable_auto_rts --rom_model -o "MA700_SPDS.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QUOTED) "MA700_SPDS.out"
	-$(RM) "dsp\ADC.pp" "dsp\DEFAULT_ISR.pp" "dsp\DEVICE.pp" "dsp\ECAN.pp" "dsp\EEPROM.pp" "dsp\GPIO.pp" "dsp\I2C.pp" "dsp\MCU.pp" "dsp\PIE_CTRL.pp" "dsp\PIE_VECT.pp" "dsp\SCI.pp" "dsp\SPI.pp" "dsp\SYS_CTRL.pp" "dsp\TLV5638.pp" "dsp\WDG.pp" "app\ARG_MAIN.pp" "app\CAN_BUF.pp" "app\CBIT_APP.pp" "app\COMMON.pp" "app\ECAN_APP.pp" "app\GPIO_APP.pp" "app\I2T_APP.pp" "app\INIT_APP.pp" "app\SCHEDULER.pp" 
	-$(RM) "boot_def.obj" "cinit.obj" "dsp2833x_adc_cal.obj" "dsp2833x_codestartbranch.obj" "dsp2833x_usdelay.obj" "fs_mpy.obj" "fs_toul.obj" "l_div.obj" "dsp\ADC.obj" "dsp\DEFAULT_ISR.obj" "dsp\DEVICE.obj" "dsp\ECAN.obj" "dsp\EEPROM.obj" "dsp\GPIO.obj" "dsp\I2C.obj" "dsp\MCU.obj" "dsp\PIE_CTRL.obj" "dsp\PIE_VECT.obj" "dsp\SCI.obj" "dsp\SPI.obj" "dsp\SYS_CTRL.obj" "dsp\TLV5638.obj" "dsp\WDG.obj" "app\ARG_MAIN.obj" "app\CAN_BUF.obj" "app\CBIT_APP.obj" "app\COMMON.obj" "app\ECAN_APP.obj" "app\GPIO_APP.obj" "app\I2T_APP.obj" "app\INIT_APP.obj" "app\SCHEDULER.obj" 
	-$(RM) "boot_def.pp" "cinit.pp" "dsp2833x_adc_cal.pp" "dsp2833x_codestartbranch.pp" "dsp2833x_usdelay.pp" "fs_mpy.pp" "fs_toul.pp" "l_div.pp" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: Intel-HEX'
	-"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/hex2000" -i "MA700_SPDS.out" -o "MA700_SPDS.hex" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
