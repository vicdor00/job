#include "show_servo_contorl.h"
#include "key_and_led.h"


/*
	check_servo_connect: 舵机的连接函数
	param: None
	Retval: 
		返回1，表示全部舵机链接成功
*/
int check_servo_connect(void)
{
	uart2_init(115200);		//初始化串口2
	
	//建立舵机1~4的通信
	while(1)
	{
		if(FSUS_Ping(&usart2, 1) == FSUS_STATUS_SUCCESS)	//判断舵机通信是否成功
		{
			if(FSUS_Ping(&usart2, 2) == FSUS_STATUS_SUCCESS)	//判断舵机通信是否成功
			{
				if(FSUS_Ping(&usart2, 3) == FSUS_STATUS_SUCCESS)	//判断舵机通信是否成功
				{
					if(FSUS_Ping(&usart2, 4) == FSUS_STATUS_SUCCESS)	//判断舵机通信是否成功
					{
						return 1;
					}
				}  
				
			}
			
		}
	}                                                                                                             
	return 0;
}

/*
    servo_do: 舵机复位
	param:  None
	Retval: None
*/
void servo_do(void)
{
	//让舵机1 从当前位置在1.5s内 移动到 0°，阻塞模式
	FSUS_SetServoAngle(&usart2, 1, 0, 1500, 0, 1);
	
	//其余同理
	FSUS_SetServoAngle(&usart2, 2, 0, 1500, 0, 1);
	
	FSUS_SetServoAngle(&usart2, 3, -46, 1500, 0, 1);
	
	FSUS_SetServoAngle(&usart2, 4, 45, 1500, 0, 1);
}

/*
    key_control_do:开关控制舵机行动
	param:  None
	Retval: None
*/
void key_control_do(void)
{
	static int Flag1;//用来判断舵机的编号
	if(Get_key_stata(key1)==0)//获取开关1状态，按下开关为0
		{
			//防抖
			mdelay(10);
			if(Get_key_stata(key1)==0)
			{
				while(!Get_key_stata(key1));//开关1松开跳出循环
				servo_do();//舵机复位
				Flag1=0;		
			}
		
		}
		
   if(Get_key_stata(key3)==0)//获取开关3状态，按下开关为0
		{
			//防抖
			mdelay(20);
			if(Get_key_stata(key3)==0)
			{
				while(!Get_key_stata(key3));//开关1松开跳出循环
				Flag1++;
		
				if(Flag1==5)//重置舵机编号
					Flag1=1;    			
			}
		
		}

		
  if(Get_key_stata(key2)==0)//获取开关2状态，按下开关为0
		{
			//防抖
			mdelay(8);
			if(Get_key_stata(key2)==0)
			{
				while(!Get_key_stata(key2));//开关2松开跳出循环
				switch(Flag1)//根据Flag：来选择控制几号舵机，1，2，3，4。5,6,7,8为每个舵机的反状态
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
		}
				
  if(Get_key_stata(key4)==0)//获取开关4状态，按下开关为0
       {
		   //防抖
		  mdelay(10);
		  if(Get_key_stata(key4)==0)
			{
				while(!Get_key_stata(key4));//开关4松开跳出循环
				//舵机完整的一套动作
			FSUS_SetServoAngle(&usart2, 1, 60, 500, 0, 1);
			FSUS_SetServoAngle(&usart2, 2, 60, 500, 0, 1);	
			FSUS_SetServoAngle(&usart2, 3, -100, 500, 0, 1);	
			FSUS_SetServoAngle(&usart2, 4, 0, 500, 0, 1);
				mdelay(1500);
			FSUS_SetServoAngle(&usart2, 1, -60, 500, 0, 1);
			FSUS_SetServoAngle(&usart2, 4, 20, 500, 0, 1);
			
			}
      }
}



