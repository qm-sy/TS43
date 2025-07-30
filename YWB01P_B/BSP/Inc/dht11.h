#ifndef __DHT11_H_
#define __DHT11_H_

#include "delay.h"
#include "sys.h"
#include "gpio.h"
#include "communication.h"

typedef struct 
{   uint8_t dht11_temp;
    uint8_t dht11_humidity;
    uint8_t temp_scan_flag;
}DHT11;

extern DHT11 dht11;

void DHT11_start( void );
void Read_DHT11( void );   

#endif