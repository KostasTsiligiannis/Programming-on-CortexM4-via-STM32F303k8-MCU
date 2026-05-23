# ARM Cortex-M4 Bare-Metal & Scheduler Project

This project demonstrates low-level bare-metal programming on the STM32F303K8 microcontroller (ARM Cortex-M4) without using HAL libraries, CMSIS startup files, or any external RTOS.

The goal of this project is to provide a clear understanding of what happens internally from reset until `main()` is executed, including memory initialization, vector table setup, linker configuration, stack initialization, semihosting, and fault handling.

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

# MCU Information

- **MCU:** STM32F303K8
- **Core:** ARM Cortex-M4
- **Flash:** 64KB
- **SRAM:** 12KB

---

# Bare-Metal Embedded 

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

# Cortex-M4 Task Scheduler

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

# Important Notes

1) Because the scheduler manually manages SRAM for PSP/MSP task stacks, OpenOCD work-area allocation may conflict with the memory layout.

This command disables OpenOCD SRAM work-area usage:

```tcl
stm32f3x.cpu configure -work-area-phys 0 -work-area-size 0
```

Without it the MCU may trigger:

- HardFault
- BusFault
- Lockup states

---

2) "While this project utilizes ARM Semihosting for printf() output, it is important to note that semihosting is inherently slow as it relies on the debugger (OpenOCD/ST-Link) to halt the CPU to transfer data. In a real-time scheduler, this can cause significant 'jitter' or missed Systick beats if overused. We intentionally utilized this method for diagnostic and debugging purposes only, as it provides an easy-to-use console without the overhead of configuring a full UART peripheral driver, allowing us to focus on the core scheduler logic."

---

# Visual Task Demonstration

To visually verify the preemptive nature of the scheduler on the NUCLEO-F303K8 (which features a single User LED on **PB3**), we implemented a "Resource Contention" demo. Since all tasks share the same physical LED, their overlapping execution creates distinct visual patterns:

- **Task 1 (The Beacon):** Tries to keep the LED ON for 3s and OFF for 3s.
- **Task 2 (The Burst):** Interrupts every 6s with 5 rapid flashes (100ms).
- **Task 3 (The Signal):** Triggers a double-pulse pattern every 10s.
- **Task 4 (The Observer):** Runs in the background providing console telemetry.

This setup demonstrates **Task Preemption** in real-time: you can observe Task 2 or Task 3 "stealing" the LED control from Task 1 while Task 1 is still in its `task_delay` period.



```
