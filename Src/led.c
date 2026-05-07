#include <stdint.h>
#include "led.h"

void led_init_all(void)
{
    // RCC AHBENR
    uint32_t *pRccAhbEnr = (uint32_t*)0x40021014;

    // GPIOA MODER
    uint32_t *pGpioAMode = (uint32_t*)0x48000000;

    // enable clock for GPIOA
    *pRccAhbEnr |= (1 << 17);

    // PA9 output mode
    *pGpioAMode &= ~(3 << (2 * 9));
    *pGpioAMode |=  (1 << (2 * 9));
}

void led_on(uint8_t led_no)
{
    uint32_t *pOdr = (uint32_t*)0x48000014;
    *pOdr |= (1 << led_no);
}

void led_off(uint8_t led_no)
{
    uint32_t *pOdr = (uint32_t*)0x48000014;
    *pOdr &= ~(1 << led_no);
}
