//
// Created by 11797 on 2024/7/3.
//

#include "time.h"


uint16_t g_fac_us = 0;

void delay_init(uint16_t sys_clk) {
    SysTick->CTRL = 0;
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
    g_fac_us = sys_clk / 8;
}


void delay_us(uint32_t nus) {
    uint32_t ticks;
    SysTick->LOAD = nus * g_fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= 1<<0;
    do {
        ticks = SysTick->CTRL;
    } while ((ticks & 0x01) && !(ticks & (1<<16)));

    SysTick->CTRL &= 0;
    SysTick->VAL = 0x00;
}


void delay_ms(uint16_t nms) {
    uint32_t repeat = nms / 1000;
    uint32_t remain = nms % 1000;
    while (repeat) {
        delay_us(1000 * 1000);
        repeat--;
    }
    if (remain) {
        delay_us(remain * 1000);
    }
}