#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"
#include "modbus_rtu.h"

#define POWER_ADDR          0x0000      //低字节：开关  
#define LED_ADDR            0x0001        //开关
#define FAN_ADDR            0x0002       //档位
#define CIR_ADDR1           0X0003        //level
#define CIR_ADDR2           0X0004      //启动时间
#define CIR_ADDR3           0X0005        //停止时间
#define CIR_ADDR4           0X0006        //开关
#define STIR_ADDR1          0X0007
#define STIR_ADDR2          0X0008
#define STIR_ADDR3          0X0009
#define STIR_ADDR4          0X000A
#define INK_OUT_ADDR        0X000B
#define ALARM_1_ADDR        0X000C
#define ALARM_2_ADDR        0X000D
#define ALARM_3_ADDR        0X000E

#define EEPROM_STATU_JUDGE    0X0015         

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif