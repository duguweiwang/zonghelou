################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
dsp/ADC.obj: ../dsp/ADC.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/ADC.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/DEFAULT_ISR.obj: ../dsp/DEFAULT_ISR.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/DEFAULT_ISR.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/DEVICE.obj: ../dsp/DEVICE.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/DEVICE.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/ECAN.obj: ../dsp/ECAN.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/ECAN.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/EEPROM.obj: ../dsp/EEPROM.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/EEPROM.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/GPIO.obj: ../dsp/GPIO.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/GPIO.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/I2C.obj: ../dsp/I2C.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/I2C.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/MCU.obj: ../dsp/MCU.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/MCU.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/PIE_CTRL.obj: ../dsp/PIE_CTRL.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/PIE_CTRL.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/PIE_VECT.obj: ../dsp/PIE_VECT.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/PIE_VECT.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/SCI.obj: ../dsp/SCI.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/SCI.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/SPI.obj: ../dsp/SPI.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/SPI.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/SYS_CTRL.obj: ../dsp/SYS_CTRL.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/SYS_CTRL.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/TLV5638.obj: ../dsp/TLV5638.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/TLV5638.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp/WDG.obj: ../dsp/WDG.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp/WDG.pp" --obj_directory="dsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


