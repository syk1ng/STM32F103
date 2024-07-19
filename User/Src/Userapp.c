//
// Created by 11797 on 2024/7/2.
//

#include "Userapp.h"
#include <stdio.h>
#include "time.h"
#include "gpio.h"
#include "usart.h"


void UserApp() {
    // printf("123\r\n");
    // delay_ms(100);
    // LedOpen(D4);
    // LedClose(D5);
    // delay_ms(100);
    // LedClose(D4);
    // LedOpen(D5);
    // uint8_t tx_temp[1];
    // tx_temp[0] = 0x01;
    // LedToggle(D4);
    if (g_usart1_rx_flag == 1) {
        HAL_UART_Transmit(&huart1, (uint8_t *)g_rx_buf, 1, 100);
        while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) != 1)
        printf("\r\n");
        delay_ms(10);
        g_usart1_rx_flag = 0;
    } else {
        delay_ms(50);
    }
}
