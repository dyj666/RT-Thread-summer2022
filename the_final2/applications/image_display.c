#include "image_display.h"


rt_uint8_t image[60][80];

ALIGN(8)
#define SAMPLE_UART_NAME       "uart7"    /* 串口设备名称 */
static rt_device_t serial;                /* 串口设备句柄 */
struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; /* 配置参数 */

void Image_Display_Init(void)
{
    for(int i = 0;i < 20; i++)
    {
        for(int j = 0; j < 80;j++)
            image[i][j] = 0;
    }
    serial = rt_device_find(SAMPLE_UART_NAME);

    config.baud_rate = BAUD_RATE_460800;        //修改波特率
    config.data_bits = DATA_BITS_8;           //数据位 8
    config.stop_bits = STOP_BITS_1;           //停止位 1
    config.bufsz     = 5000;                   //修改缓冲区 buff size 为 128
    config.parity    = PARITY_NONE;           //无奇偶校验位

    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);

}

Beacon_P Beacon1_P_last;
Beacon_P Beacon2_P_last;
Car_P car1_last,car2_last;
void image_update(void)
{
    Beacon1_P_last.w = Beacon1_P.w;
    Beacon1_P_last.h = Beacon1_P.h;
    Beacon2_P_last.w = Beacon2_P.w;
    Beacon2_P_last.h = Beacon2_P.h;
    car1_last.w = car1.w;
    car1_last.h = car1.h;
    car2_last.w = car2.w;
    car2_last.h = car2.h;
    image[Beacon1_P_last.w][Beacon1_P_last.h] = 0;
    image[Beacon1_P_last.w][Beacon1_P_last.h] = 0;
    image[Beacon2_P_last.w][Beacon2_P_last.h] = 0;
    image[Beacon2_P_last.w][Beacon2_P_last.h] = 0;
    image[car1_last.w][car1_last.h] = 0;
    image[car2_last.w][car2_last.h] = 0;

    image[Beacon2_P.w][Beacon2_P.h] = 255;
    image[Beacon2_P.w][Beacon2_P.h] = 255;
    image[car1.w][car1.h] = 255;
    image[car2.w][car2.h] = 255;

//    rt_device_write(serial, 0, "CSU", 3);
//    rt_device_write(serial, 0, image[0], 4800);
//    rt_device_write(serial, 0, "USC", 3);
    rt_kprintf("image_update_success\n");
}


int image_update_thread(void)
{
    rt_thread_t image_thread = RT_NULL;
    image_thread = rt_thread_create("image_update_thread", (void *)image_update, RT_NULL, 1024, 20, 50);
    rt_thread_startup(image_thread);
    return 0;
}

INIT_APP_EXPORT(image_update_thread);



