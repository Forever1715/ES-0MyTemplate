#ifndef __DHT11_H
#define __DHT11_H

#include "Global.h"
#define DHT11_OUT 
#define DHT11_OUT_HIGH dht11_gpio_outhigh()
#define DHT11_OUT_LOW dht11_gpio_outlow()
#define DHT11_IN_HIGH dht11_gpio_inhigh()
#define DHT11_IN_LOW dht11_gpio_inlow()
#define DHT11_IN_LEVEL GPIO_ReadInputDataBit(DHT11_GPIOx,DHT11_Pin_x)
void DHT11_Init(void);
int DHT11_Read(void);

extern u8 g_TRHData[5];
#endif

