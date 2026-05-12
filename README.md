# ARM Cortex-M4 Bare-Metal & Scheduler Projects

This repository contains two embedded systems projects developed for the **STM32F303K8 (ARM Cortex-M4)** using low-level **bare-metal programming techniques**.

The projects focus on understanding how embedded systems and RTOS kernels work internally without using **HAL libraries** or an external **RTOS**.

---

# Topics Covered

- **ARM Cortex-M4 architecture**
- Bare-metal embedded programming
- GNU ARM Toolchain
- Startup code and vector tables
- Linker scripts and memory layout
- SysTick and PendSV exceptions
- MSP/PSP stack management
- Context switching
- Cooperative/preemptive scheduling
- Task blocking and delays
- Exception and fault handling
- Semihosting with `printf()`
- OpenOCD debugging and flashing

---

# Repository Structure

```text
Repository/
│
├── baremetal_embedded/
│   ├── main.c
│   ├── stm32_startup.c
│   ├── stm32_ls.ld
│   ├── Makefile
│   └── ...
│
├── scheduler_project/
│   ├── Inc/
│   │   ├── main.h
│   │   └── ...
│   │
│   ├── Src/
│   │   ├── main.c
│   │   ├── syscalls.c
│   │   ├── sysmem.c
│   │   └── ...
│   │
│   └── STM32CubeIDE project files
│
└── README.md
```

---

# MCU Information

- **MCU:** STM32F303K8
- **Core:** ARM Cortex-M4
- **Flash:** 64KB
- **SRAM:** 12KB

---

# Project 1 — Bare-Metal Embedded & Linker Scripts

A low-level Cortex-M4 bare-metal project demonstrating:

- custom startup code
- interrupt vector table creation
- linker script usage
- SRAM/Flash memory mapping
- manual stack initialization
- OpenOCD flashing/debugging
- semihosting support

This project explains what happens internally before `main()` executes on an ARM Cortex-M microcontroller.

---

# Project 2 — Cortex-M4 Task Scheduler

A lightweight embedded task scheduler implemented entirely from scratch without an RTOS.

### Features Implemented

- task scheduling
- task delays
- SysTick time base
- PendSV context switching
- PSP/MSP switching
- task stack initialization
- blocked/ready task states
- fault exception handling
- semihosting debugging with `printf()`

The scheduler manually manages task stacks inside SRAM and demonstrates the internal mechanisms commonly used by RTOS kernels.

---

# Scheduler Architecture

The scheduler uses:

- **SysTick** → periodic timing interrupt
- **PendSV** → context switching
- **PSP** → task execution stacks
- **MSP** → exception handling stack

Each task is represented using a **Task Control Block (TCB)**:

```c
typedef struct
{
    uint32_t psp_value;
    uint32_t block_count;
    uint8_t current_state;
    void (*task_handler)(void);

}TCB_t;
```

---

# Memory Layout

The scheduler manually allocates stack regions inside SRAM:

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

# Toolchain

Required tools:

- `arm-none-eabi-gcc`
- `make`
- `OpenOCD`
- `STM32CubeIDE`
- `PuTTY` / Telnet client

---

# Build Instructions

## Clean Build

```bash
make clean
```

## Build Semihosting Version

```bash
make semi
```

Generated output:

```text
final_sh.elf
```

---

# Flashing & Debugging

Start OpenOCD:

```bash
make load
```

Then connect through **PuTTY/Telnet** and execute:

```tcl
reset halt
stm32f3x.cpu configure -work-area-phys 0 -work-area-size 0
flash write_image erase final_sh.elf
arm semihosting enable
resume
```

---

# Important Note

Because the scheduler manually manages SRAM for PSP/MSP task stacks, OpenOCD work-area allocation may conflict with the memory layout.

This command disables OpenOCD SRAM work-area usage:

```tcl
stm32f3x.cpu configure -work-area-phys 0 -work-area-size 0
```

Without it the MCU may trigger:

- HardFault
- BusFault
- Lockup states

---

# Example Output

```text
Task1 running
Task2 running
Task3 running
Task4 running
```
