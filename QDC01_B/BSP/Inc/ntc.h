#ifndef _NTC_H_
#define _NTC_H_

#include "sys.h"
#include "adc.h"
#include "power_crl.h"
#include "stdio.h"

#define NTC1        4
#define NTC2        5
#define NTC3        6

typedef struct 
{
    uint8_t  temp_value1;   
    uint8_t  temp_value2;  
    uint8_t  temp_value3;  
    uint8_t  temp_alarm_value;
    uint8_t  temp_scan_flag;

    uint8_t  dht11_temp;
    uint8_t  dht11_humidity;
}TEMP;

extern TEMP temp;

static uint16_t LookupTable( uint16_t *temp_tab, uint8_t tab_num, uint16_t adc_val );
uint16_t get_temp( uint8_t channle_x );

#endif