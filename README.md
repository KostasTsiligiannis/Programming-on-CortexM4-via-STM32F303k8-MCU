# Programming-on-CortexM4-via-STM32F303k8-MCU
# STM32F303K8 Cooperative Task Scheduler (Cortex-M4)

A simple cooperative task scheduler implementation for the STM32F303K8 Cortex-M4 MCU.

This project demonstrates:

- Manual task stack creation
- PSP/MSP switching
- PendSV-based context switching
- SysTick scheduling
- Semihosting `printf`
- Custom startup code
- Custom linker script
- Bare-metal ARM Cortex-M4 development without HAL/CMSIS RTOS

---

# MCU

- STM32F303K8
- Cortex-M4
- 64KB Flash
- 12KB SRAM

---

# Toolchain

Required tools:

- `arm-none-eabi-gcc`
- `make`
- `openocd`
- `PuTTY` (or telnet client)
- `Git Bash` / Linux shell

---

# Build Instructions

## Clean build files

```bash
make clean
```

---

## Build semihosting version

```bash
make semi
```

This generates:

```text
final_sh.elf
```

---

# Flashing & Running

## Start OpenOCD

```bash
make load
```

Expected output:

```text
Info : Listening on port 4444 for telnet connections
Info : Listening on port 3333 for gdb connections
```

Keep this terminal OPEN.

---

# Connect using PuTTY

Open PuTTY:

- Connection type: `Telnet`
- Host: `localhost`
- Port: `4444`

---

# OpenOCD Commands

Inside the PuTTY/OpenOCD console execute:

```tcl
reset halt
stm32f3x.cpu configure -work-area-phys 0 -work-area-size 0
flash write_image erase final_sh.elf
arm semihosting enable
resume
```

---

# IMPORTANT NOTE ABOUT WORK AREA

This project uses:

- custom PSP task stacks
- custom scheduler stack
- semihosting
- a small SRAM MCU (12KB)

Because of this, OpenOCD RAM work-area allocation conflicts with the scheduler memory layout.

Therefore this command is REQUIRED:

```tcl
stm32f3x.cpu configure -work-area-phys 0 -work-area-size 0
```

This disables OpenOCD RAM work-area usage and prevents SRAM collisions.

Without this command the MCU may:

- HardFault
- DoubleFault
- Lockup
- Fail during flashing

---

# Expected Output

After `resume`:

```text
Implementation of simple task scheduler
Task1 running
Task2 running
Task3 running
Task4 running
```

---

# Project Structure

```text
.
├── main.c
├── main.h
├── led.c
├── led.h
├── stm32_startup.c
├── stm32_ls.ld
├── Makefile
└── README.md
```

---

# Scheduler Architecture

The scheduler uses:

- SysTick for time base
- PendSV for context switching
- PSP for task execution
- MSP for exception handling

Tasks are stored inside:

```c
TCB_t user_tasks[MAX_TASKS];
```

Each task contains:

- PSP value
- block delay counter
- state
- handler function

---

# Memory Layout

The project manually manages SRAM:

```text
+----------------------+
| Task1 Stack          |
+----------------------+
| Task2 Stack          |
+----------------------+
| Task3 Stack          |
+----------------------+
| Task4 Stack          |
+----------------------+
| Idle Task Stack      |
+----------------------+
| Scheduler Stack      |
+----------------------+
```

---

# Semihosting Notes

This project uses:

```c
printf()
```

through ARM semihosting (`rdimon.specs`).

Semihosting is useful for debugging but:

- slow
- debugger dependent
- stack intensive
- not ideal for production RTOS systems

Production-grade systems should use:

- UART logging
or
- SWO/ITM tracing

instead.

---


---

# Author

Bare-metal Cortex-M4 scheduler implementation for educational and embedded systems learning purposes.
