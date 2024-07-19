//
// Created by 11797 on 2024/7/2.
//

#include "Userapp.h"
#include <stdio.h>
#include "time.h"
#include "gpio.h"
#include "usart.h"
#include "dma.h"
#include "tim.h"

uint8_t TransferStatus;
uint32_t aSRC_Const_Buffer[32]= {
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
uint32_t aSRC_Const_Buffer_err[32]= {
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F81};
uint32_t aDST_Buffer[32];
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);
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
    // if (g_usart1_rx_flag == 1) {
    //     HAL_UART_Transmit(&huart1, (uint8_t *)g_rx_buf, 1, 100);
    //     while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) != 1)
    //     printf("\r\n");
    //     delay_ms(10);
    //     g_usart1_rx_flag = 0;
    // } else {
    //     delay_ms(50);
    // }
    while(__HAL_DMA_GET_FLAG(&hdma_memtomem_dma1_channel1,DMA_FLAG_TC1)==RESET)
    {
    }

    TransferStatus=Buffercmp(aSRC_Const_Buffer_err, aDST_Buffer, 32);

    if(TransferStatus==0)
    {
        MX_TIM6_Init(7199, 499);
    }
    else
    {
        MX_TIM6_Init(7199, 4999);
    }
}

uint8_t Buffercmp(const uint32_t* pBuffer,
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
    while(BufferLength--)
    {
        if(*pBuffer != *pBuffer1)
        {
            return 0;
        }
        pBuffer++;
        pBuffer1++;
    }
    return 1;
}