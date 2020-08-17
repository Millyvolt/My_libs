
#include "delay.h"


uint16_t	psc_ms, psc_us;
TIM_TypeDef	*timx;


void	delay_init(TIM_TypeDef * tim)
{
	timx = tim;
	if(timx==TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	timx->CR1 |= TIM_CR1_OPM;
	SystemCoreClockUpdate();
	psc_ms = SystemCoreClock/10/1000 - 1;			//system clock must be < 650MHz
	psc_us = SystemCoreClock/1000000 - 1;
	timx->EGR |= TIM_EGR_UG;
	while( !(timx->SR & TIM_SR_UIF) )
		;
	timx->SR &= ~TIM_SR_UIF;
	while( timx->SR & TIM_SR_UIF )
		;
}

void	delay_ms(uint16_t ms)
{
	timx->PSC = psc_ms;
	timx->EGR |= TIM_EGR_UG;
	while( !(timx->SR & TIM_SR_UIF) )
		;
	timx->SR &= ~TIM_SR_UIF;
	while( timx->SR & TIM_SR_UIF )
		;
	timx->ARR = ms*10;
	timx->CR1 |= TIM_CR1_CEN;
	while( !(timx->SR & TIM_SR_UIF) )
		;
	timx->SR &= ~TIM_SR_UIF;
}

void 	delay_us(uint16_t us)
{
	timx->PSC = psc_us;
	timx->EGR |= TIM_EGR_UG;
	while( !(timx->SR & TIM_SR_UIF) )
		;
	timx->SR &= ~TIM_SR_UIF;
	while( timx->SR & TIM_SR_UIF )
		;
	timx->ARR = us;
	timx->CR1 |= TIM_CR1_CEN;
	while( !(timx->SR & TIM_SR_UIF) )
		;
	timx->SR &= ~TIM_SR_UIF;
}


