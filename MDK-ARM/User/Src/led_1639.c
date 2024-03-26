#include "led_1639.h"

uint8_t digitToSegment[12] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x00, // ??
    0x80  // ?
};

void TM1639_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        TM1639_CLK_LOW();
        if (data & 0b1)
        {
            TM1639_DIO_HIGH();
        }
        else
        {
            TM1639_DIO_LOW();
        }
        data >>= 1;
        TM1639_CLK_HIGH();
    }
}

uint8_t TM1639_ReadByte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        data >>= 1;
        TM1639_CLK_LOW();
        if (HAL_GPIO_ReadPin(TMI1639_DIN_GPIO_Port, TMI1639_DIN_Pin) == GPIO_PIN_SET)
        {
            data |= 0x80;
        }
        TM1639_CLK_HIGH();
    }
    return data;
}

void TM1639_WriteData(uint8_t addr, uint8_t data)
{
    // 写数据命令
    TM1639_STB_LOW();
    TM1639_WriteByte(0x44);
    TM1639_STB_HIGH();

    // 写入低四位数据
    TM1639_STB_LOW();
    TM1639_WriteByte(0xC0 | (addr * 2));
    TM1639_WriteByte(data & 0x0F);
    TM1639_STB_HIGH();

    // 写入高四位数据
    TM1639_STB_LOW();
    TM1639_WriteByte(0xC0 | (addr * 2 + 1));
    TM1639_WriteByte((data & 0xF0) >> 4);
    TM1639_STB_HIGH();
}

uint8_t TM1639_ReadKey(void)
{
    uint8_t key = 0;
    TM1639_STB_LOW();
    TM1639_WriteByte(0x42); // 读键值命令
    key = TM1639_ReadByte();
    TM1639_STB_HIGH();
    return key;
}

void TM1639_Init(void)
{
    HAL_GPIO_WritePin(display_power_control_GPIO_Port, display_power_control_Pin, GPIO_PIN_RESET);
    TM1639_STB_LOW();
    TM1639_WriteByte(0x8f);
    TM1639_STB_HIGH();
    for (uint8_t i = 0; i < 16; i++)
    {
        TM1639_WriteData(5, 0x00);
    }
}
