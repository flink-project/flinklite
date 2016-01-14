################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../flinklib


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../board.c \
../flinklib/ain.c \
../flinklib/aout.c \
../flinklib/base.c \
../flinklib/counter.c \
../flinklib/dio.c \
../flinklib/flink_core.c \
../flinklib/flink_spi.c \
../flinklib/hal.c \
../flinklib/info.c \
../flinklib/ppwa.c \
../flinklib/pwm.c \
../flinklib/subdevtypes.c \
../flinklib/valid.c \
../flinklib/wd.c \
../main.c \
../SPI.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
board.o \
flinklib/ain.o \
flinklib/aout.o \
flinklib/base.o \
flinklib/counter.o \
flinklib/dio.o \
flinklib/flink_core.o \
flinklib/flink_spi.o \
flinklib/hal.o \
flinklib/info.o \
flinklib/ppwa.o \
flinklib/pwm.o \
flinklib/subdevtypes.o \
flinklib/valid.o \
flinklib/wd.o \
main.o \
SPI.o

OBJS_AS_ARGS +=  \
board.o \
flinklib/ain.o \
flinklib/aout.o \
flinklib/base.o \
flinklib/counter.o \
flinklib/dio.o \
flinklib/flink_core.o \
flinklib/flink_spi.o \
flinklib/hal.o \
flinklib/info.o \
flinklib/ppwa.o \
flinklib/pwm.o \
flinklib/subdevtypes.o \
flinklib/valid.o \
flinklib/wd.o \
main.o \
SPI.o

C_DEPS +=  \
board.d \
flinklib/ain.d \
flinklib/aout.d \
flinklib/base.d \
flinklib/counter.d \
flinklib/dio.d \
flinklib/flink_core.d \
flinklib/flink_spi.d \
flinklib/hal.d \
flinklib/info.d \
flinklib/ppwa.d \
flinklib/pwm.d \
flinklib/subdevtypes.d \
flinklib/valid.d \
flinklib/wd.d \
main.d \
SPI.d

C_DEPS_AS_ARGS +=  \
board.d \
flinklib/ain.d \
flinklib/aout.d \
flinklib/base.d \
flinklib/counter.d \
flinklib/dio.d \
flinklib/flink_core.d \
flinklib/flink_spi.d \
flinklib/hal.d \
flinklib/info.d \
flinklib/ppwa.d \
flinklib/pwm.d \
flinklib/subdevtypes.d \
flinklib/valid.d \
flinklib/wd.d \
main.d \
SPI.d

OUTPUT_FILE_PATH +=Flink.elf

OUTPUT_FILE_PATH_AS_ARGS +=Flink.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG -DF_CPU=8000000UL  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -mmcu=at90usb1287 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\at90usb1287" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

flinklib/%.o: ../flinklib/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG -DF_CPU=8000000UL  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -mmcu=at90usb1287 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\at90usb1287" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Flink.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=at90usb1287 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\at90usb1287"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Flink.elf" "Flink.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Flink.elf" "Flink.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Flink.elf" > "Flink.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Flink.elf" "Flink.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Flink.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Flink.elf" "Flink.a" "Flink.hex" "Flink.lss" "Flink.eep" "Flink.map" "Flink.srec" "Flink.usersignatures"
	