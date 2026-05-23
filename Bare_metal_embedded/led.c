#include <stdint.h>
#include "led.h"

void led_init_all(void)
{
    // RCC AHBENR
    uint32_t *pRccAhbEnr = (uint32_t*)0x40021014;

    // GPIOB MODER
    uint32_t *pGpioBMode = (uint32_t*)0x48000400;

    // enable clock for GPIOB
    *pRccAhbEnr |= (1 << 18);

    // PB3 output mode (clear bit 6,7 & set bit 6)
    *pGpioBMode &= ~(3 << (2 * 3));
    *pGpioBMode |=  (1 << (2 * 3));
}

void led_on(uint8_t led_no)
{
    // GPIOB ODR 
    uint32_t *pOdr = (uint32_t*)0x48000414;
    *pOdr |= (1 << led_no);
}

void led_off(uint8_t led_no)
{
    uint32_t *pOdr = (uint32_t*)0x48000414;
    *pOdr &= ~(1 << led_no);
}
