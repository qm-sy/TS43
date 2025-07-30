#include "common.h"

/**
 * @brief	一些定时执行的事件   Timer3：10ms
 *
 * @param   
 *
 * @return  void
**/
void Tim3_ISR( void ) interrupt 19
{

    static uint16_t temp_scan_cnt = 0;
    static uint16_t level1_cnt = 0;
    static uint16_t level2_cnt = 0;
    static uint16_t level3_cnt = 0;
    static uint16_t level4_cnt = 0;
    static uint16_t level5_cnt = 0;
    static uint16_t level6_cnt = 0;
    static uint16_t level7_cnt = 0;
    static uint16_t level8_cnt = 0;
    static uint16_t level9_cnt = 0;
    static uint16_t level10_cnt = 0;
    static uint16_t level11_cnt = 0;
    static uint16_t level12_cnt = 0;
    static uint16_t level13_cnt = 0;
    static uint16_t level14_cnt = 0;
    static uint16_t cir_delay_cnt  = 0;
    static uint16_t stir_delay_cnt = 0;
    /* 1, temp 上报 1s/次                             */
    if( dht11.temp_scan_flag == 0 )
    {
        temp_scan_cnt++;
        if( temp_scan_cnt == 100 )
        {
            dht11.temp_scan_flag = 1;
            temp_scan_cnt = 0;
        }
    }
    /* 2, LEVEL Scan                            */
    /* 2.1, LEVEL   1                          */
    if( level1_H == 0 )
    {
        level1_cnt++;
        if( level1_cnt >= level.level_delay )
        {
            level1_cnt = 0;
            level.level1_down_flag = 1;
        }
    }else
    {
        level1_cnt = 0;
        level.level1_down_flag = 0;
    }

    /* 2.2, LEVEL   2                          */
    if( level2_H == 0 )
    {
        level2_cnt++;
        if( level2_cnt >= level.level_delay )
        {
            level2_cnt = 0;
            level.level2_down_flag = 1;
        }
    }else
    {
        level2_cnt = 0;
        level.level2_down_flag = 0;
    }

    /* 2.3, LEVEL   3                          */
    if( level3_H == 0 )
    {
        level3_cnt++;
        if( level3_cnt >= level.level_delay )
        {
            level3_cnt = 0;
            level.level3_down_flag = 1;
        }
    }else
    {
        level3_cnt = 0;
        level.level3_down_flag = 0;
    }

    /* 2.4, LEVEL   4                          */
    if( level4_H == 0 )
    {
        level4_cnt++;
        if( level4_cnt >= level.level_delay )
        {
            level4_cnt = 0;
            level.level4_down_flag = 1;
        }
    }else
    {
        level4_cnt = 0;
        level.level4_down_flag = 0;
    }

    /* 2.5, LEVEL   5                          */
    if( level5_H == 0 )
    {
        level5_cnt++;
        if( level5_cnt >= level.level_delay )
        {
            level5_cnt = 0;
            level.level5_down_flag = 1;
        }
    }else
    {
        level5_cnt = 0;
        level.level5_down_flag = 0;
    }

    /* 2.6, LEVEL   6                          */
    if( level6_H == 0 )
    {
        level6_cnt++;
        if( level6_cnt >= level.level_delay )
        {
            level6_cnt = 0;
            level.level6_down_flag = 1;
        }
    }else
    {
        level6_cnt = 0;
        level.level6_down_flag = 0;
    }

    /* 2.7, LEVEL   7                          */
    if( level7_H == 0 )
    {
        level7_cnt++;
        if( level7_cnt >= level.level_delay )
        {
            level7_cnt = 0;
            level.level7_down_flag = 1;
        }
    }else
    {
        level7_cnt = 0;
        level.level7_down_flag = 0;
    }

    /* 2.8, LEVEL   8                          */
    if( level8_H == 0 )
    {
        level8_cnt++;
        if( level8_cnt >= level.level_delay )
        {
            level8_cnt = 0;
            level.level8_down_flag = 1;
        }
    }else
    {
        level8_cnt = 0;
        level.level8_down_flag = 0;
    }

    /* 2.9, LEVEL   9                          */
    if( level9_H == 0 )
    {
        level9_cnt++;
        if( level9_cnt >= level.level_delay )
        {
            level9_cnt = 0;
            level.level9_down_flag = 1;
        }
    }else
    {
        level9_cnt = 0;
        level.level9_down_flag = 0;
    }

    /* 2.10, LEVEL   10                          */
    if( level10_H == 0 )
    {
        level10_cnt++;
        if( level10_cnt >= level.level_delay )
        {
            level10_cnt = 0;
            level.level10_down_flag = 1;
        }
    }else
    {
        level10_cnt = 0;
        level.level10_down_flag = 0;
    }

    /* 2.11, LEVEL   11                          */
    if( level11_H == 0 )
    {
        level11_cnt++;
        if( level11_cnt >= level.level_delay )
        {
            level11_cnt = 0;
            level.level11_down_flag = 1;
        }
    }else
    {
        level11_cnt = 0;
        level.level11_down_flag = 0;
    }

    /* 2.12, LEVEL   12                          */
    if( level12_H == 0 )
    {
        level12_cnt++;
        if( level12_cnt >= level.level_delay )
        {
            level12_cnt = 0;
            level.level12_down_flag = 1;
        }
    }else
    {
        level12_cnt = 0;
        level.level12_down_flag = 0;
    }

    /* 2.13, LEVEL   13                          */
    if( level13_H == 0 )
    {
        level13_cnt++;
        if( level13_cnt >= level.level_delay )
        {
            level13_cnt = 0;
            level.level13_down_flag = 1;
        }
    }else
    {
        level13_cnt = 0;
        level.level13_down_flag = 0;
    }

    /* 2.14, LEVEL   14                          */
    if( level14_H == 0 )
    {
        level14_cnt++;
        if( level14_cnt >= level.level_delay )
        {
            level14_cnt = 0;
            level.level14_down_flag = 1;
        }
    }else
    {
        level14_cnt = 0;
        level.level14_down_flag = 0;
    }

    /* 3. 循环和搅拌电机延时 */
    if( dc_ctrl.cir_switch == 1 )
    {
        cir_delay_cnt++;
        if( cir_delay_cnt <= dc_ctrl.cir_start_time )
        {
            pwm_ctrl(CIR_CTRL,dc_ctrl.cir_level);
        }
        if((cir_delay_cnt < (dc_ctrl.cir_start_time + dc_ctrl.cir_stop_time)) && ( cir_delay_cnt > dc_ctrl.cir_start_time ))
        {
            pwm_ctrl(CIR_CTRL,0);
        }
        if(cir_delay_cnt >= (dc_ctrl.cir_start_time + dc_ctrl.cir_stop_time))
        {
            cir_delay_cnt = 0;
        }
    }
    
    if( dc_ctrl.stir_switch == 1 )
    {
        stir_delay_cnt++;
        if( stir_delay_cnt <= dc_ctrl.stir_start_time )
        {
            pwm_ctrl(STIR_CTRL,dc_ctrl.stir_level);
        }
        if((stir_delay_cnt < (dc_ctrl.stir_start_time + dc_ctrl.stir_stop_time)) && ( stir_delay_cnt > dc_ctrl.stir_start_time ))
        {
            pwm_ctrl(STIR_CTRL,0);
        }
        if(stir_delay_cnt >= (dc_ctrl.stir_start_time + dc_ctrl.stir_stop_time))
        {
            stir_delay_cnt = 0;
        }
    }  
}
