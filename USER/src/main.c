#include "exit.h"
#include <stdio.h>
#include "gec_gpio.h"
#include "gec_int.h"
#include "gec_time.h"
#include "gec_uart.h"
#include "gec_init.h"
#include "key_and_led.h"
#include "show_servo_contorl.h"
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
#include "uart.h"


/*李政明专属代码，不可盗用，若经发现，严惩不贷*/
int main()
{	
	key_and_led_init();//开关和灯初始化
	Gec_Lib_Init();	   
	int Flag;
	Flag=check_servo_connect();
	uart_init(9600);
	

	while(1)
	{	
	   if(Flag==1)
	 {
		 Set_led_stata(led1,led_on);
	 }
    }
	

		

}

