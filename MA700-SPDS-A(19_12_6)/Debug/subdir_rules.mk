################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
boot_def.obj: ../boot_def.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="boot_def.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cinit.obj: ../cinit.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="cinit.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp2833x_adc_cal.obj: ../dsp2833x_adc_cal.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp2833x_adc_cal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp2833x_codestartbranch.obj: ../dsp2833x_codestartbranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp2833x_codestartbranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp2833x_usdelay.obj: ../dsp2833x_usdelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="dsp2833x_usdelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fs_mpy.obj: ../fs_mpy.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="fs_mpy.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fs_toul.obj: ../fs_toul.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="fs_toul.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

l_div.obj: ../l_div.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/head" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/lru" --include_path="D:/MA 700/MA700-SPDS-A(19_11_26)/config" --diag_warning=225 --check_misra="all,-1.1,-4.1,-5.6,-5.7,-6.3,-7.1,-8.6,-8.7,-10.1,-10.2,-10.3,-10.4,-10.6,-11.3,-11.4,-12.1,-12.3,-12.4,-12.5,-12.6,-12.10,-12.13,-13.2,-13.3,-13.6,-14.1,-14.2,-14.4,-14.6,-14.8,-14.9,-15.1,-15.4,-16.7,-16.9,-17.4,-17.5,-17.6,-18.4,-19,19.3,19.4,19.6,19.8,19.9,19.10,19.11,19.12,19.14,19.15,19.16,19.17,-20.4,-20.6,-20.8,-20.9,-20.10,-20.11,-20.12" --preproc_with_compile --preproc_dependency="l_div.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


