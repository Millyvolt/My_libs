
#ifndef DELAY_H_
#define DELAY_H_


#include "stm32f1xx.h"


void	delay_init(TIM_TypeDef * tim);
void	delay_ms(uint16_t ms);
void	delay_us(uint16_t us);


#endif /* DELAY_H_ */
