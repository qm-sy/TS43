#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sys.h"
#include "gpio.h"

typedef struct 
{
    uint8_t  level17_info_L;                //DATA_H
    uint8_t  level17_info_H;                //DATA_L       
    uint8_t  level814_info_L;                //DATA_H
    uint8_t  level814_info_H;                //DATA_L         
    uint16_t level_delay;
    uint8_t  level1_down_flag;
    uint8_t  level2_down_flag;
    uint8_t  level3_down_flag;
    uint8_t  level4_down_flag;
    uint8_t  level5_down_flag;
    uint8_t  level6_down_flag;
    uint8_t  level7_down_flag;
    uint8_t  level8_down_flag;
    uint8_t  level9_down_flag;
    uint8_t  level10_down_flag;
    uint8_t  level11_down_flag;
    uint8_t  level12_down_flag;
    uint8_t  level13_down_flag;
    uint8_t  level14_down_flag;
}LEVEL;


extern LEVEL level;

void ink_scan( void );
void level_info_init( void );

#endif