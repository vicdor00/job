#include "key_and_led.h"
#include "gec_gpio.h"
#include "gec_time.h"
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
#include "uart.h"
#include "show_servo_contorl.h"


/*
    key_and_led_init：灯和开关初始化
	Param：
	    None
	Retval:	
	    None
*/
void key_and_led_init(void)
{
    //将PB10、PB11设置为推挽输出
	Gec_GPIO_Init(GPIOB,GPIO_Pin_10,GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_11,GPIO_MODE_OUT_PP);
	
	//将PB12、PB13设置为上拉输入
	Gec_GPIO_Init(GPIOB,GPIO_Pin_12,GPIO_MODE_IN_PULLUP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_13,GPIO_MODE_IN_PULLUP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_14,GPIO_MODE_IN_PULLUP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_15,GPIO_MODE_IN_PULLUP);

	//将led1，led2置于高电平
	Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_10, 1);
	Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_11, 1);
}

/*
   Get_key_stata:获得开关的状态
   Param:key_num为key1，key2，key3，key4
   Retval：1或0
*/
int Get_key_stata(int key_num)
  {
	  switch(key_num)
	  {
		  case key1:
			  return Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_12);//返回key1的状态1或0
		  case key2:
			  return Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_13);//返回key2的状态1或0
		  case key3:
			  return Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_14);//返回key3的状态1或0
		  case key4:
			  return Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_15);//返回key4的状态1或0
		  default:
			 return 2;  //开关无效，返回2
	  }
  }
 

/*
  Set_led_stata:获得灯的状态，亮或灭
  Param：led_num为led1，led2
         led_stata为led_on或led_off
  Retval:
      None  
*/  
void Set_led_stata(int led_num,int led_stata)
  {
	  switch(led_num)
	  {
		   case led1:
			  Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_10, led_stata);break;//获得led1的状态1或0
		   case led2:
			  Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_11, led_stata);break;//获得led2的状态1或0
	  }		 
  }

//key长按，led亮，key不按灯灭
void key_and_led_longcontrol(int key_num,int led_num)
{

    //获取key的值 
	if(Get_key_stata(key_num)==0)
	{
		servo_do();
       mdelay(50);
   //判断key的值，key为0，灯亮，否则灭
	if(Get_key_stata(key_num)==0) 
		 Set_led_stata(led_num, led_on);
	else
		 Set_led_stata(led_num, led_off);
    }
}

//key只要等到一次下降沿，灯改变一次状态
void key_and_led_control(int key_num,int led_num)
{
	//判断key的值，key为0，灯改变一次状态
	if(Get_key_stata(key_num)==0)
	{
		mdelay(8);
	 if(Get_key_stata(key_num)==0)
	 {
		 mdelay(50);
		//判断key是否松手
		while(Get_key_stata(key_num)==1)
		{
		Gec_GPIO_Toggle_Value(GPIOB,led_num);
		break;	
		}
	 }
	}
}

//int Flag1=0;
//void key_control_do(void)
//{
//	extern int Flag1;
//if(Get_key_stata(key1)==0)
//		{
//			mdelay(8);
//			if(Get_key_stata(key1)==0)
//			{
//				servo_do();
//				Set_led_stata(led1, led_on);
//              			
//			}
//		
//		}
//		
// if(Get_key_stata(key3)==0)
//		{
//			mdelay(8);
//			if(Get_key_stata(key3)==0)
//			{
//				Flag1++;
//				Gec_GPIO_Toggle_Value(GPIOB,GPIO_Pin_11);
//				if(Flag1==5)
//					Flag1=0;
//             			
//			}
//		
//		}
//if(Get_key_stata(key2)==0)
//				{
//					Set_led_stata(led2, led_on);
//					switch(Flag1)
//				{
//					case 1:FSUS_SetServoAngle(&usart2, 1, -12, 1500, 0, 1);Set_led_stata(led1, led_off);break;
//					case 2:FSUS_SetServoAngle(&usart2, 2, 10, 1500, 0, 1);Set_led_stata(led2, led_off);break;
//					case 3:FSUS_SetServoAngle(&usart2, 3, 44, 1500, 0, 1);Set_led_stata(led2, led_on);break;
//					case 4:FSUS_SetServoAngle(&usart2, 4, 15, 1500, 0, 1);Set_led_stata(led1, led_on);break;
//					default: break;
//				}
//				
//				
//				}
//				
//if(Get_key_stata(key4)==0)
//{
//	mdelay(8);
//	if(Get_key_stata(key4)==0)
//	{
//	
//	
//	}


//}

//}







