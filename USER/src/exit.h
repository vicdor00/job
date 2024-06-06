#ifndef _EXIT_H_
#define _EXIT_H_
#include "gec_gpio.h"
#include "gec_uart.h"
#include "gec_int.h"
#include <stdio.h>
#include "show_servo_contorl.h"
#include "key_and_led.h"


void uart_int_do(void);
void uart_init(int baudrate);
#endif



