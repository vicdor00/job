#include "exit.h"
#include "gec_gpio.h"
#include "gec_uart.h"
#include "gec_int.h"
#include <stdio.h>
#include "show_servo_contorl.h"
#include "key_and_led.h"

void uart_int_do(void)
{
	       static int Flag1;
	       int num;
				unsigned char data[20];
	             num=Gec_UART_Read(USART1,data,1);
	            if(num==1&&data[0]=='a')
				{
	            FSUS_SetServoAngle(&usart2, 1, 0, 1500, 0, 1);
	            FSUS_SetServoAngle(&usart2, 2, 0, 1500, 0, 1);	
	            FSUS_SetServoAngle(&usart2, 3, -46, 1500, 0, 1);	
	            FSUS_SetServoAngle(&usart2, 4, 45, 1500, 0, 1);
					printf("舵机复位\n");
				
				}
				
				if(num==1&&data[0]=='b')
				{
					printf("舵机调试\n");
				  switch(Flag1)
				{
					case 1:
						FSUS_SetServoAngle(&usart2, 1, 60, 500, 0, 1);FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 500, 0, 1);Flag1=5;break;
					case 2:
						FSUS_SetServoAngle(&usart2, 2, 60, 500, 0, 1);FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 1500, 0, 1);Flag1=6;break;
					case 3:
						FSUS_SetServoAngle(&usart2, 3, -100, 500, 0, 1);FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 500, 0, 1);Flag1=7;break;
					case 4:
						FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);Flag1=8;break;
					case 5:
						FSUS_SetServoAngle(&usart2, 1, 0, 500, 0, 1);Flag1=1;FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 500, 0, 1);break;
					case 6:
						FSUS_SetServoAngle(&usart2, 2, 0, 500, 0, 1);Flag1=2;FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 1500, 0, 1);break;
					case 7:
						FSUS_SetServoAngle(&usart2, 3, -46, 500, 0, 1);Flag1=3;FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
					    FSUS_SetServoAngle(&usart2, 4, 60, 500, 0, 1);break;
					case 8:
						FSUS_SetServoAngle(&usart2, 4, 60, 500, 0, 1);Flag1=4;break;
					default: break;
				}
				}
				
				if(num==1&&data[0]=='c')
				{
				Flag1++;
					
					printf("改变舵机\n");
				if(Flag1==1)
				{
					Set_led_stata(led1, led_on);
					Set_led_stata(led2, led_off);
				}
				if(Flag1==2)
				{
					Set_led_stata(led1, led_off);
					Set_led_stata(led2, led_on);
				}
				if(Flag1==3)
				{
					Set_led_stata(led1, led_on);
					Set_led_stata(led2, led_on);
				}
				
				if(Flag1==4)
				{
					Set_led_stata(led1, led_off);
					Set_led_stata(led2, led_off);
				}
				if(Flag1==5)
					Flag1=1;
				
				}
					
				
				
				if(num==1&&data[0]=='d')
				{
					printf("舵机启动\n");
				FSUS_SetServoAngle(&usart2, 1, 60, 500, 0, 1);
				FSUS_SetServoAngle(&usart2, 2, 60, 500, 0, 1);	
				FSUS_SetServoAngle(&usart2, 3, -100, 500, 0, 1);	
				FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
				   mdelay(1500);
				FSUS_SetServoAngle(&usart2, 1, -60, 500, 0, 1);
				FSUS_SetServoAngle(&usart2, 4, 20, 500, 0, 1);
					
				}
	            
	
}	


void uart_init(int baudrate)
			{
				//配置串口1 设置为9600波特率，无校验位，8bits 数据位 1bits停止位
				Gec_UART_Init(USART1, baudrate, USART_Parity_No, 8, USART_StopBits_1);
				Gec_Int_Register(BSP_INT_ID_USART1, uart_int_do);	//设置一个串口中断
				Gec_Int_Enable(BSP_INT_ID_USART1);		//使能串口1中断
			}
