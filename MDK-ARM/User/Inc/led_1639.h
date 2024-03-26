#ifndef __LED_1639_H
#define __LED_1639_H
#include "gpio.h"

#define power_key_Pin GPIO_PIN_14
#define power_key_GPIO_Port GPIOC
#define TIM1639_CLK_Pin GPIO_PIN_3
#define TIM1639_CLK_GPIO_Port GPIOA
#define TMI1639_DIN_Pin GPIO_PIN_4
#define TMI1639_DIN_GPIO_Port GPIOA
#define TMI1639_STB_Pin GPIO_PIN_5
#define TMI1639_STB_GPIO_Port GPIOA
#define display_power_control_Pin GPIO_PIN_8
#define display_power_control_GPIO_Port GPIOA

#define TM1639_DIO_HIGH() HAL_GPIO_WritePin(TMI1639_DIN_GPIO_Port, TMI1639_DIN_Pin, GPIO_PIN_SET)
#define TM1639_DIO_LOW() HAL_GPIO_WritePin(TMI1639_DIN_GPIO_Port, TMI1639_DIN_Pin, GPIO_PIN_RESET)
#define TM1639_CLK_HIGH() HAL_GPIO_WritePin(TIM1639_CLK_GPIO_Port, TIM1639_CLK_Pin, GPIO_PIN_SET)
#define TM1639_CLK_LOW() HAL_GPIO_WritePin(TIM1639_CLK_GPIO_Port, TIM1639_CLK_Pin, GPIO_PIN_RESET)
#define TM1639_STB_HIGH() HAL_GPIO_WritePin(TMI1639_STB_GPIO_Port, TMI1639_STB_Pin, GPIO_PIN_SET)
#define TM1639_STB_LOW() HAL_GPIO_WritePin(TMI1639_STB_GPIO_Port, TMI1639_STB_Pin, GPIO_PIN_RESET)


// 显示数字和字符的查找表
extern uint8_t digitToSegment[12];

void TM1639_WriteData(uint8_t addr, uint8_t data);
uint8_t TM1639_ReadKey(void);
void TM1639_Init(void);
#endif /* __LED_H */
