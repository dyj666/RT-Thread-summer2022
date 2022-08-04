#include "ch32v30x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"
#include <board.h>
#include <rtdevice.h>
#include "beacon.h"



int main(void)
{
    rt_kprintf("MCU: CH32V307\n");
	rt_kprintf("SysClk: %dHz\n",SystemCoreClock);
    rt_kprintf("www.wch.cn\n");


	while(1)
	{
//	    GPIO_SetBits(GPIOA,GPIO_Pin_0);
        rt_thread_mdelay(500);
//        GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//        rt_thread_mdelay(500);
	}

}



