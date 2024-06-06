#ifndef __KEY_AND_BEE_H__
#define __KEY_AND_BEE_H__
#include "gec_gpio.h"
#include "gec_time.h"
#include "gec_int.h"
#include "key_and_led.h"




void key_and_bee_init(void);
void KEY_Int_Init(void);
void KEY3_control_BEE(void);
//void KEY_control_BEE(int key_num);
	
#endif

