#include "ntc.h"
#include "MATH.H"

TEMP temp;

void bubble_sort(uint16_t arr[], uint16_t n) 
{
    uint8_t i, j;
    uint16_t temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换元素
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/**
 * @brief 取10次adc_val均值对应的temp
 *
 * @param[in] channle_x ntc通道1~4
 * 
 * @return  temp :最终温度
 * 
**/
uint16_t get_temp( uint8_t channle_x )
{
    uint8_t i,t;
    uint16_t adc_val = 0;
	uint16_t temp_val;
    uint16_t adc_tab[24];
    /* 1, 取10次adc_val                           */
    for( t = 0; t < 24; t++ )
	{
		adc_tab[t] = Get_ADC_12bit(channle_x);
	}	       
    bubble_sort(adc_tab,24);
    for(i = 6; i < 18; i++)
    {
      adc_val += adc_tab[i];
    }
    adc_val = adc_val/12;

    if( adc_val >= 1156 )
    {
      temp_val = ((adc_val - 1156) * 100 )/ 623;
    }else
    {
      temp_val = 0;
    }

    return temp_val;
}
