#include "key_and_bee.h"
#include "gec_gpio.h"
#include "gec_time.h"
#include "gec_int.h"


int Flag=0;


void key_and_bee_init(void)
{
    //将PB2设置为推挽输出
	Gec_GPIO_Init(GPIOB,GPIO_Pin_2,GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_10,GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB,GPIO_Pin_11,GPIO_MODE_OUT_PP);
	
	//将PB14设置为上拉输入
	Gec_GPIO_Init(GPIOB,GPIO_Pin_14,GPIO_MODE_IN_PULLUP);
	
	//将bee置于高电平
	Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_2, 0);
	Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_10, 1);
	Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_11, 1);
}

/*KEY_control_BEE:按下开关，蜂鸣器响
  Param:key_num,开关key3
  Retval：
         None
*/

void KEY3_control_BEE(void)
{

	if(Gec_GPIO_Get_ITFlag(EXTI_Line14)==1)//判断中断是否响应
	{

/*		
		 if(Gec_GPIO_Get_Value(GPIOB,key3)==0)
         {
			 if(Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_2)==0)
			 {
				 Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_2,1);
			 }
			 else
			 {
				 Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_2,0);
			 }
	
		 }	
		 while(Gec_GPIO_Get_Value(GPIOB,key3)==0);
*/
		

			 
	}
}


void KEY_Int_Init(void)
{
	Gec_GPIO_Init(GPIOB,GPIO_Pin_14,GPIO_MODE_EXTI_Falling);//中断初始化
	Gec_Int_Register(BSP_INT_ID_EXTI15_10,KEY3_control_BEE);//中断申请
	Gec_Int_Enable(BSP_INT_ID_EXTI15_10);//中断开始
}





/*
void KEY_control_BEE(int key_num)
{
if(Gec_GPIO_Get_Value(GPIOB,key_num)==0)         //判断开关是否按下
  {
	  mdelay(8);                                     //延时8毫秒
	  if(Gec_GPIO_Get_Value(GPIOB,key_num)||Flag==0) //再次判断开关是否按下
	  {
		  mdelay(8);                                 //延时8毫秒
	      while(Gec_GPIO_Get_Value(GPIOB,key_num)==1)//判断开关是否松手
		  {
			  Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_2,1);//蜂鸣器响
		      Flag=1;
			  break;                                 //跳出循环
		  }		  
	  }
  }
    if(Gec_GPIO_Get_Value(GPIOB,key_num)==0)         //判断开关是否按下
  {
	  mdelay(8);                                     //延时8毫秒
	  if(Gec_GPIO_Get_Value(GPIOB,key_num)||Flag==1) //再次判断开关是否按下
	  {
		  mdelay(8);                                 //延时8毫秒
		  while(Gec_GPIO_Get_Value(GPIOB,key_num)==1)//判断开关是否松手
		  {
			  Gec_GPIO_Set_Value(GPIOB,GPIO_Pin_2,0);//蜂鸣器停
		      Flag=0;
			  break;                                 //跳出循环
		  }			  
	  }
  }

}
*/
