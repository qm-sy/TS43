#include "modbus_rtu.h"

MODBIS_INFO modbus;

/**
 * @brief	modbus_rtu  无奇偶校验
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Event( void )
{
    uint16_t crc,rccrc;
    
    /*1.接收完毕                                           */
    if( rs485.RX4_rev_end_Flag == 1 )
    {

        /*2.清空接收完毕标志位                              */    
        rs485.RX4_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485.RX4_buf, rs485.RX4_rev_cnt-2);
        rccrc = (rs485.RX4_buf[rs485.RX4_rev_cnt-1]) | (rs485.RX4_buf[rs485.RX4_rev_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485.RX4_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485.RX4_buf[0] == ADDR_EB )
            {
                switch ( rs485.RX4_buf[1] )
                {
                    case 0x03:
                        Modbus_Fun3();
                        break;

                    case 0x04:
                        Modbus_Fun4();
                        break;

                    case 0x06:
                        Modbus_Fun6();
                        break;  

                    case 0x10:  
                        Modbus_Fun16();

                    default:
                        break;
                }
            }
        }
    }
}


/**
 * @brief	读输入寄存器  03
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun3( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                //DATA1 H 位置
    modbus.byte_cnt   = (rs485.RX4_buf[4]<<8 | rs485.RX4_buf[5]) *2;
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    rs485.TX4_buf[0]  = ADDR_EB;                //Addr
    rs485.TX4_buf[1]  = 0x03;                   //Fun
    rs485.TX4_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {   
            /*  40001 风速查询                     */
            case 0x00:


                break;

            /*  40002 LED开关状态查询                     */    
            case 0x01:

                break;

            /*  40003 3路220V开关使能查询                         */
            case 0x02:    

                break;

            /*  40004 同步状态查询              */
            case 0x03:    


                break;

            /*  40005 工作模式查询                     */
            case 0x04:   

                break;

            /*  40006 报警温度查询                     */
            case 5:   
        

                break;
            default:
                break;
        }
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master(0x03,3 + modbus.byte_cnt);
}


/**
 * @brief	读输出寄存器  04
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun4( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                 //DATA1 H 位置
    modbus.byte_cnt   = (rs485.RX4_buf[4]<<8 | rs485.RX4_buf[5]) *2;
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    rs485.TX4_buf[0]  = ADDR_EB;                //Addr
    rs485.TX4_buf[1]  = 0x04;                   //Fun
    rs485.TX4_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {
            /*  30001  1~7通道液位信息                        */
            case 0x00:
                ink_scan();
                modbus.byte_info_H = level.level_info_H;
                modbus.byte_info_L = level.level_info_L;
                break;

            /*  30002                 */
            case 0x01:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = 0x00;

                break;

            /*  30003 温湿度                   */
            case 0x02:
                modbus.byte_info_H = temp.dht11_humidity;
                modbus.byte_info_L = temp.dht11_temp;
                break;

            /*  30004 NTC1 温度                   */
            case 0x03:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = temp.temp_value1;
                break;

            default:
                break;
        }
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master(0x04,3 + modbus.byte_cnt);
}


/**
 * @brief	写单个输出寄存器  06
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun6( void )
{
    switch (rs485.RX4_buf[3])
    {
        /*  40001                        */
        case 0x00:                  

            break;

        /*  40002                                   */
        case 0x01:                                         


            break;

        /*  40003                             */
        case 0x02:                                         

            break;  
            
        /*  40004  底板加热                   */
        case 0x03:   
            dc_ctrl.board_alarm_temp = rs485.RX4_buf[4];                                   
            dc_ctrl.board_out_allow = rs485.RX4_buf[5];

            break;

        /*  40005  墨囊加热                   */
        case 0x04:                                         
            inksac_ctrl(rs485.RX4_buf[5]);

            break;

        /*  40006  循环控制                  */
        case 0x05:                  
            dc_ctrl.cir_start_time = ((rs485.RX4_buf[5] >> 3) | ((rs485.RX4_buf[4] & 0x01) << 5)) * 100;     
            dc_ctrl.cir_stop_time  = ((rs485.RX4_buf[4] & 0x7F) >> 1) * 100;  
            dc_ctrl.cir_level = rs485.RX4_buf[5]&0x07;   
            dc_ctrl.cir_switch = rs485.RX4_buf[4] >> 7;
            if(dc_ctrl.cir_switch == 1)
            {
                pwm_ctrl(CIR_CTRL,dc_ctrl.cir_level);
            }else
            {
                pwm_ctrl(CIR_CTRL,0);
            }
            
            break;

        /*  40007  搅拌控制                   */
        case 0x06:  
            dc_ctrl.stir_start_time = ((rs485.RX4_buf[5] >> 3) | ((rs485.RX4_buf[4] & 0x01) << 5)) * 100;     
            dc_ctrl.stir_stop_time  = ((rs485.RX4_buf[4] & 0x7F) >> 1) * 100;   
            dc_ctrl.stir_level = rs485.RX4_buf[5]&0x07;  
            dc_ctrl.stir_switch = rs485.RX4_buf[4] >> 7;
            if(dc_ctrl.stir_switch == 1)
            {
                pwm_ctrl(STIR_CTRL,dc_ctrl.stir_level);
            }else
            {
                pwm_ctrl(STIR_CTRL,0);
            }
  
            break;

        /*  40007  缺墨延时时间                   */
        case 0x07:  
            level.level_delay = rs485.RX4_buf[5] * 100;

            break;    

        default:
            break;   
    }
    slave_to_master(0x06,8);
}



/**
 * @brief	写多个输出寄存器  16
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun16( void )
{
    uint16_t i;

    modbus.rcv_value_addr = 7;                  //DATA1 H位置
    modbus.byte_cnt   = rs485.RX4_buf[6];
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    
    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++)
    {
        modbus.byte_info_H = rs485.RX4_buf[modbus.rcv_value_addr];
        modbus.byte_info_L = rs485.RX4_buf[modbus.rcv_value_addr + 1];
        switch (i)
        {
                /*  40001  底板加热                      */
            case 0x00:                  
                dc_ctrl.board_alarm_temp = modbus.byte_info_H;                                   
                dc_ctrl.board_out_allow = modbus.byte_info_L;
                break;

            /*  40002     墨囊加热                              */
            case 0x01:                                         
                inksac_ctrl(modbus.byte_info_L);

                break;

            /*  40003    循环控制                         */
            case 0x02:                                         
                dc_ctrl.cir_start_time = ((modbus.byte_info_L >> 3) | ((modbus.byte_info_H & 0x01) << 5)) * 100;     
                dc_ctrl.cir_stop_time  = ((modbus.byte_info_H & 0x7F) >> 1) * 100;  
                dc_ctrl.cir_level = modbus.byte_info_L&0x07;   
                dc_ctrl.cir_switch = modbus.byte_info_H >> 7;
                if(dc_ctrl.cir_switch == 1)
                {
                    pwm_ctrl(CIR_CTRL,dc_ctrl.cir_level);
                }else
                {
                    pwm_ctrl(CIR_CTRL,0);
                }

                break;  
                
            /*  40004  搅拌控制                   */
            case 0x03:   
                dc_ctrl.stir_start_time = ((modbus.byte_info_L >> 3) | ((modbus.byte_info_H & 0x01) << 5)) * 100;     
                dc_ctrl.stir_stop_time  = ((modbus.byte_info_H & 0x7F) >> 1) * 100;  
                dc_ctrl.stir_level = modbus.byte_info_L&0x07;   
                dc_ctrl.stir_switch = modbus.byte_info_H >> 7;
                if(dc_ctrl.stir_switch == 1)
                {
                    pwm_ctrl(STIR_CTRL,dc_ctrl.stir_level);
                }else
                {
                    pwm_ctrl(STIR_CTRL,0);
                }

                break;

            /*  40005  缺墨延时时间                   */
            case 0x04:                                         
                level.level_delay = modbus.byte_info_L * 100;

                break;

            default:
                break;
        }
        modbus.rcv_value_addr += 2;         //从Value1_H →→ 从Value2_H
    }

    slave_to_master(0x10,8);
}



/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave_to_master(uint8_t code_num,uint8_t length)
{
    uint16_t crc;

    switch (code_num)
    {
        case 0x03:
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            break;
        case 0x04:
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            break;    

        case 0x06:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,8);

            rs485.TX4_send_bytelength = length;
            
            break;   

        case 0x10:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,6);
        
            crc = MODBUS_CRC16(rs485.TX4_buf,6);

            rs485.TX4_buf[7] = crc;                 //CRC H
            rs485.TX4_buf[6] = crc>>8;              //CRC L
        
            rs485.TX4_send_bytelength = length;
            
            break;         

        default:
            break;
    }

    DR4 = 1;                                 //485可以发送
    delay_ms(2);
    S4CON |= S4TI;                              //开始发送
    delay_ms(1);
}


/**
 * @brief	crc校验函数
 * 
 * @param   buf：  Address(1 byte) +Funtion(1 byte) ）+Data(n byte)   
 * @param   length:数据长度           
 * 
  @return  crc16:crc校验的值 2byte
 */
uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length)
{
	uint8_t	i;
	uint16_t	crc16;

    /* 1, 预置16位CRC寄存器为0xffff（即全为1）                          */
	crc16 = 0xffff;	

	do
	{
        /* 2, 把8位数据与16位CRC寄存器的低位相异或，把结果放于CRC寄存器     */        
		crc16 ^= (uint16_t)*buf;		//
		for(i=0; i<8; i++)		
		{
            /* 3, 如果最低位为1，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位 再异或0xA001    */
			if(crc16 & 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            /* 4, 如果最低位为0，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位                */
            else
            {
                crc16 >>= 1;
            }		
		}
		buf++;
	}while(--length != 0);

	return	(crc16);
}
