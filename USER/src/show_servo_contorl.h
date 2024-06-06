#ifndef __SHOW_SERVO_CONTORL_H_
#define __SHOW_SERVO_CONTORL_H_

#include "uart.h"
#include "fashion_star_uart_servo.h"
#include "key_and_led.h"


int check_servo_connect(void);

void servo_do(void);
void key_control_do(void);


#endif 
