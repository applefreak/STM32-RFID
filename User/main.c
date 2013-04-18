/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart.h"
#include "hd44780.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBuffer1[]; 
extern uint8_t TxBuffer2[]; 
extern uint8_t RxBuffer1[];
extern uint8_t RxBuffer2[];
extern __IO uint8_t TxCounter1;
extern __IO uint8_t TxCounter2;
extern __IO uint8_t RxCounter1; 
extern __IO uint8_t RxCounter2;
extern uint8_t rec_f,tx_flag;

uint8_t xcard[]="2500ABCBDB9E";
uint8_t proc[16]="a";
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int strcmp(const uint8_t *s1, const uint8_t *s2);
void strproc(uint8_t *d, const uint8_t *s);
void id12init(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	USART1_Config();
	lcdInit();
	id12init();
	printf(" Configured...\r\n");
	USART_OUT(USART1,"***************************************************\r\n"); 
	printString("Please Swipe");
	toLine2();
	printString("Card.");
	while(1){
		if(rec_f==1){												  //判断是否收到一帧有效数据		
			rec_f=0;
			//USART_OUT(USART1,"Message: \r\n");    
			printf("%s",&TxBuffer1[0]);
			strproc(&proc[0],&TxBuffer1[0]);
			clearLCD();
			Delay(0xFFFF);
			printString(&proc[0]);
			toLine2();
			if(strcmp(&proc[0],&xcard[0]) == 0)
				printString("Authorized!");
			else
				printString("Unauthorized!");
			Delay(0xFFFFFF);
			clearLCD(); 
			printString("Please Swipe");
			toLine2();
	    printString("Card.");
		}
		
	}
}

int strcmp(const uint8_t *s1, const uint8_t *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	    return 0;
    return ((*(uint8_t *)s1 < *(uint8_t *)s2) ? -1 : +1);
}

void strproc(uint8_t *d, const uint8_t *s)
{
  while(*s != '\0'){
		if(((*s>=0x20)&&(*s<=0x7F)) || ((*s>=0xA0)&&(*s<=0xFF))) {
			*d++=*s;
		}
		*s++;
	}
	*d = '\0';
}

void id12init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	         		 //USART1 TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    		 //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	Delay(0xFFF);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	Delay(0xFFF);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
