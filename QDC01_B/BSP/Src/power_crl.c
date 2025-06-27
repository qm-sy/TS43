#include "power_crl.h"

AC_DC ac_dc;

/**
 * @brief	24V LED开关控制函数
 *
 * @param   on_off：0：关闭 1：开启
 *
 * @return  void
**/
void led_ctrl( uint8_t on_off )
{
    if( on_off == FAN_ON )
    {
        LED = 0;
    }else
    {
        LED = 1;
    }
}

/**
 * @brief	24V PWM风扇档位控制函数
 *
 * @param   level :风扇档位 0~6档
 *
 * @return  void
**/
void fan_ctrl( uint8_t level )
{
    PWMB_CCR7= level * 184;
}

void power_ctrl()
{
    if( qdc_info.power_enable == 1 )
    {
        if( qdc_info.AC1_alarm_flag == 1)
        {
            AC_Out1 = 0;
        }else
        {
            AC_Out1 = 1;
        }
        if( qdc_info.AC2_alarm_flag == 1)
        {
            AC_Out2 = 0;
        }else
        {
            AC_Out2 = 1;
        }
        if( qdc_info.AC3_alarm_flag == 1)
        {
            AC_Out3 = 0;
        }else
        {
            AC_Out3 = 1;
        }  
    }else
    {
        AC_Out1 = AC_Out2 = AC_Out3 = 1; 
    }
}
/**
 * @brief 温度扫描，DHT11温湿度扫描 1s/次 控制220V输出使能
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void temp_scan( void )
{
    if( temp.temp_scan_flag == 1)
    {
        temp.temp_value1 = get_temp(NTC1);
        temp.temp_value2 = get_temp(NTC2);
        temp.temp_value3 = get_temp(NTC3);
        
        if( temp.temp_value1 >= qdc_info.F_alarm_temp )
        {
            qdc_info.AC1_alarm_flag = 0;
        }else
        {
            qdc_info.AC1_alarm_flag = 1;
        }

        if( temp.temp_value2 >= qdc_info.M_alarm_temp )
        {
            qdc_info.AC2_alarm_flag = 0;
        }else
        {
            qdc_info.AC2_alarm_flag = 1;
        }

        if( temp.temp_value3 >= qdc_info.R_alarm_temp )
        {
            qdc_info.AC3_alarm_flag = 0;
        }else
        {
            qdc_info.AC3_alarm_flag = 1;
        }
        power_ctrl();
        
        temp.temp_scan_flag = 0;
    }
}
