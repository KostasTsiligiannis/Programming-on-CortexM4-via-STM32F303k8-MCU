/*
 * stm32_startup.c
 * Startup file for STM32F303K8 (STM32F303x8)
 */

#include <stdint.h>

/*--------------------------------------------------------------------
 * SRAM definitions
 * STM32F303K8 has 12 KB SRAM
 *-------------------------------------------------------------------*/
#define SRAM_START      0x20000000U
#define SRAM_SIZE       (9U * 1024U)
#define SRAM_END        (SRAM_START + SRAM_SIZE)

#define STACK_START     SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;


int main(void);
void __libc_init_array(void);

/*--------------------------------------------------------------------
 * Function prototypes
 *-------------------------------------------------------------------*/
void Reset_Handler(void);
void Default_Handler(void);

/* Cortex-M4 core exception handlers */
void NMI_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)        __attribute__((weak, alias("Default_Handler")));

/* Device specific IRQ handlers for STM32F303x8 */
void WWDG_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void EXTI2_TS_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN_RX1_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void CAN_SCE_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM15_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM16_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM17_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));

/*--------------------------------------------------------------------
 * Vector table
 *-------------------------------------------------------------------*/
uint32_t vectors[] __attribute__((section(".isr_vector"))) =
{
    /* Cortex-M4 core handlers */
    STACK_START,                                   // 0 Initial Stack Pointer
    (uint32_t)Reset_Handler,                       // 1 Reset
    (uint32_t)NMI_Handler,                         // 2 NMI
    (uint32_t)HardFault_Handler,                   // 3 HardFault
    (uint32_t)MemManage_Handler,                   // 4 MemManage
    (uint32_t)BusFault_Handler,                    // 5 BusFault
    (uint32_t)UsageFault_Handler,                  // 6 UsageFault
    0,                                             // 7 Reserved
    0,                                             // 8 Reserved
    0,                                             // 9 Reserved
    0,                                             // 10 Reserved
    (uint32_t)SVC_Handler,                         // 11 SVCall
    (uint32_t)DebugMon_Handler,                    // 12 Debug Monitor
    0,                                             // 13 Reserved
    (uint32_t)PendSV_Handler,                      // 14 PendSV
    (uint32_t)SysTick_Handler,                     // 15 SysTick

    /* External Interrupts */
    (uint32_t)WWDG_IRQHandler,                     // 16
    (uint32_t)PVD_IRQHandler,                      // 17
    (uint32_t)TAMP_STAMP_IRQHandler,               // 18
    (uint32_t)RTC_WKUP_IRQHandler,                 // 19
    (uint32_t)FLASH_IRQHandler,                    // 20
    (uint32_t)RCC_IRQHandler,                      // 21
    (uint32_t)EXTI0_IRQHandler,                    // 22
    (uint32_t)EXTI1_IRQHandler,                    // 23
    (uint32_t)EXTI2_TS_IRQHandler,                 // 24
    (uint32_t)EXTI3_IRQHandler,                    // 25
    (uint32_t)EXTI4_IRQHandler,                    // 26
    (uint32_t)DMA1_Channel1_IRQHandler,            // 27
    (uint32_t)DMA1_Channel2_IRQHandler,            // 28
    (uint32_t)DMA1_Channel3_IRQHandler,            // 29
    (uint32_t)DMA1_Channel4_IRQHandler,            // 30
    (uint32_t)DMA1_Channel5_IRQHandler,            // 31
    (uint32_t)DMA1_Channel6_IRQHandler,            // 32
    (uint32_t)DMA1_Channel7_IRQHandler,            // 33
    (uint32_t)ADC1_2_IRQHandler,                   // 34
    (uint32_t)USB_HP_CAN_TX_IRQHandler,            // 35
    (uint32_t)USB_LP_CAN_RX0_IRQHandler,           // 36
    (uint32_t)CAN_RX1_IRQHandler,                  // 37
    (uint32_t)CAN_SCE_IRQHandler,                  // 38
    (uint32_t)EXTI9_5_IRQHandler,                  // 39
    (uint32_t)TIM1_BRK_TIM15_IRQHandler,           // 40
    (uint32_t)TIM1_UP_TIM16_IRQHandler,            // 41
    (uint32_t)TIM1_TRG_COM_TIM17_IRQHandler,       // 42
    (uint32_t)TIM1_CC_IRQHandler,                  // 43
    (uint32_t)TIM2_IRQHandler,                     // 44
    (uint32_t)TIM3_IRQHandler,                     // 45
    (uint32_t)TIM6_DAC_IRQHandler,                 // 46
    (uint32_t)TIM7_IRQHandler,                     // 47
    (uint32_t)TIM14_IRQHandler,                    // 48
    (uint32_t)TIM15_IRQHandler,                    // 49
    (uint32_t)TIM16_IRQHandler,                    // 50
    (uint32_t)TIM17_IRQHandler,                    // 51
    (uint32_t)I2C1_EV_IRQHandler,                  // 52
    (uint32_t)I2C1_ER_IRQHandler,                  // 53
    (uint32_t)I2C2_EV_IRQHandler,                  // 54
    (uint32_t)I2C2_ER_IRQHandler,                  // 55
    (uint32_t)SPI1_IRQHandler,                     // 56
    (uint32_t)SPI2_IRQHandler,                     // 57
    (uint32_t)USART1_IRQHandler,                   // 58
    (uint32_t)USART2_IRQHandler,                   // 59
    (uint32_t)USART3_IRQHandler,                   // 60
    (uint32_t)EXTI15_10_IRQHandler,                // 61
    (uint32_t)RTC_Alarm_IRQHandler,                // 62
    (uint32_t)USBWakeUp_IRQHandler                 // 63
};

/*--------------------------------------------------------------------
 * Reset handler
 *-------------------------------------------------------------------*/
void Reset_Handler(void)
{
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	uint8_t *pDst = (uint8_t*)&_sdata;
	uint8_t *pSrc = (uint8_t*)&_la_data;

	for(uint32_t i=0; i<size; i++){
		*pDst++ = *pSrc++;
	}
	
	size = &_ebss - &_sbss;
	pDst = (uint8_t*)&_sbss;
	for(uint32_t i=0; i<size; i++){
		*pDst++ = 0;
	}
	__libc_init_array();
	main();
}

/*--------------------------------------------------------------------
 * Default handler
 *-------------------------------------------------------------------*/
void Default_Handler(void)
{
    while (1);
}