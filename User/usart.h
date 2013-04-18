#include "stm32f10x.h"
#include <stdio.h>
#include "stdarg.h"

void USART1_Config(void);
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
char *itoa(int value, char *string, int radix);
