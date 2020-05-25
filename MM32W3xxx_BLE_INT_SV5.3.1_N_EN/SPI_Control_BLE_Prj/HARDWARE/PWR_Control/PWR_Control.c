#include "pwr_control.h"

unsigned char SleepStop = 0x02;
unsigned char SleepStatus = 0;
extern  unsigned int SysTick_Count;
extern unsigned int RxTimeout, TxTimeout, SysTick_Count;
/********************************************************************************************************
**function: McuGotoSleepAndWakeup
**@brief    This function is the MCU auto goto sleep AND wakeup, porting api
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void McuGotoSleepAndWakeup(void) // auto goto sleep AND wakeup, porting api
{
  if ((SleepStop) &&
      (TxTimeout < SysTick_Count) &&
      (RxTimeout < SysTick_Count))
  {
    if (SleepStop == 1) //sleep
    {
      SCB->SCR &= 0xfb;
      __WFE();
    }
    else   //stop
    {
      SCB->SCR |= 0x4;
      __WFI();
      RCC->CR |= RCC_CR_HSION;
      RCC->CR |= RCC_CR_PLLON;
      RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
      GPIO_ResetBits(GPIOB, GPIO_Pin_7);
    }
  }
}

