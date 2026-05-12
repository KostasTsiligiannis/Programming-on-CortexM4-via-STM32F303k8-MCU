CC = arm-none-eabi-gcc
MACH = cortex-m4

CFLAGS = -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 -g
#LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft \
#          --specs=nano.specs \
#          -T stm32_ls.ld \
#          -Wl,-Map=final.map

LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft \
          --specs=rdimon.specs \
          -T stm32_ls.ld \
          -Wl,-Map=final.map
		  
		  
all: final.elf

semi: final_sh.elf

main.o: main.c
	$(CC) $(CFLAGS) -o $@ $<

led.o: led.c
	$(CC) $(CFLAGS) -o $@ $<

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $<

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) -o $@ $<

final.elf: main.o led.o stm32_startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: main.o led.o stm32_startup.o 
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f board/st_nucleo_f3.cfg