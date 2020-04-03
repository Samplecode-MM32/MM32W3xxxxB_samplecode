#include "RF_IRQ.h"
#include "mg_api.h"

/********************************************************************************************************
**function: IsIrqEnabled
**@brief    This function is used to determine whether a Bluetooth interrupt is generated
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
char IsIrqEnabled(void) //porting api
{
  return (!(GPIO_ReadInputData(GPIOC) & 0x1000));
}

/********************************************************************************************************
**function: IRQ_RF
**@brief    This function is the IRQ initialization function.  Configure Clock GPIO and NVIC in this function.
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void IRQ_RF(void)//PC12 Wake UP MCU from STOP Mode
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  //IRQ - PC12
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource12);

  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_SetPriority(EXTI15_10_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
}

/********************************************************************************************************
**function: EXTI15_10_IRQHandler
**@brief    Bluetooth interrupt handler
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line12);
  ble_run(0);
}
