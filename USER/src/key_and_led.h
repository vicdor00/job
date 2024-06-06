#ifndef __KEY_AND_LED_H__
#define __KEY_AND_LED_H__
#include "gec_gpio.h"
#include "gec_time.h"
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
#include "uart.h"
#include "show_servo_contorl.h"
#define led1 1
#define led2 2
#define key1 1
#define key2 2
#define key3 3
#define key4 4
#define led_on 0
#define led_off 1




int Get_key_stata(int key_num);
void Set_led_stata(int led_num,int led_stata);
void key_and_led_init(void);
void key_and_led_longcontrol(int key_num,int led_num);
void key_and_led_control(int key_num,int led_num);
//void key_control_do(void);


	
#endif
