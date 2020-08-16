
#include "delay.h"


uint16_t	psc_ms, psc_us;


void	delay_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR1 |= TIM_CR1_OPM;
	SystemCoreClockUpdate();
	psc_ms = SystemCoreClock/10/1000 - 1;			//system clock must be < 650MHz
	psc_us = SystemCoreClock/1000000 - 1;
	TIM2->EGR |= TIM_EGR_UG;
	while( !(TIM2->SR & TIM_SR_UIF) )
		;
	TIM2->SR &= ~TIM_SR_UIF;
	while( TIM2->SR & TIM_SR_UIF )
		;
}

void	delay_ms(uint16_t ms)
{
	TIM2->PSC = psc_ms;
	TIM2->EGR |= TIM_EGR_UG;
	while( !(TIM2->SR & TIM_SR_UIF) )
		;
	TIM2->SR &= ~TIM_SR_UIF;
	while( TIM2->SR & TIM_SR_UIF )
		;
	TIM2->ARR = ms*10;
	TIM2->CR1 |= TIM_CR1_CEN;
	while( !(TIM2->SR & TIM_SR_UIF) )
		;
	TIM2->SR &= ~TIM_SR_UIF;
}

void 	delay_us(uint16_t us)
{
	TIM2->PSC = psc_us;
	TIM2->EGR |= TIM_EGR_UG;
	while( !(TIM2->SR & TIM_SR_UIF) )
		;
	TIM2->SR &= ~TIM_SR_UIF;
	while( TIM2->SR & TIM_SR_UIF )
		;
	TIM2->ARR = us;
	TIM2->CR1 |= TIM_CR1_CEN;
	while( !(TIM2->SR & TIM_SR_UIF) )
		;
	TIM2->SR &= ~TIM_SR_UIF;
}


