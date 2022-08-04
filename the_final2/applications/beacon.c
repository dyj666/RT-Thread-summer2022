#include "beacon.h"

Beacon_P Beacon1_P;
Beacon_P Beacon2_P;

Car_P car1,car2;
float_t speed1, speed2;

rt_int8_t direction_count(rt_int8_t IMAGE_W, rt_int8_t IMAGE_H);
rt_int8_t distance1,distance2;


void beacon_param_init(void)
{
    Beacon1_P.w = 0;
    Beacon1_P.h = 0;
    Beacon1_P.status = 0;

    Beacon2_P.w = 0;
    Beacon2_P.h = 0;
    Beacon2_P.status = 0;
}

void move_param_init(void)
{
    car1.w = 60;
    car1.h = 30;
    car2.w = 50;
    car2.h = 60;
    speed1 = 1;
    speed2 = 1;
}


void beacon_control(void)
{
    beacon_param_init();
    Beacon1_P.w = rand() % 60 + 1;
    Beacon1_P.h = rand() % 80 + 1;
    Beacon1_P.status = 1;
    while((Beacon1_P.w != Beacon2_P.w) && (Beacon1_P.h != Beacon2_P.h))
    {
        Beacon2_P.w = rand() % 60 + 1;
        Beacon2_P.h = rand() % 80 + 1;
        Beacon2_P.status = 1;
    }

    while(1)
    {
        if(!Beacon1_P.status)
        {
            while((Beacon1_P.w != Beacon2_P.w) && (Beacon1_P.h != Beacon2_P.h))
            {
                Beacon1_P.w = rand() % 60 + 1;
                Beacon1_P.h = rand() % 80 + 1;
                Beacon1_P.status = 1;
            }
        }
        else continue;
        if(!Beacon2_P.status)
        {
            while((Beacon1_P.w != Beacon2_P.w) && (Beacon1_P.h != Beacon2_P.h))
            {
                Beacon2_P.w = rand() % 60 + 1;
                Beacon2_P.h = rand() % 80 + 1;
                Beacon2_P.status = 1;
            }
        }
        else continue;
    }
}


int beacon_control_thread(void)
{
    rt_thread_t beacon_thread = RT_NULL;
    beacon_thread = rt_thread_create("bct", (void *)beacon_control, RT_NULL, 2048, 10, 50);
    rt_thread_startup(beacon_thread);
    return 0;
}

INIT_APP_EXPORT(beacon_control_thread);

void move_control(void)
{
    move_param_init();
    while(1)
    {
        if(!direction_count(Beacon1_P.w,Beacon1_P.h))
        {
            car1.w += speed1 * cos(atan2(Beacon1_P.h - car1.h, Beacon1_P.w - car1.w));
            car1.h += speed1 * sin(atan2(Beacon1_P.h - car1.h, Beacon1_P.w - car1.w));
            car2.w += speed2 * cos(atan2(Beacon2_P.h - car2.h, Beacon2_P.w - car2.w));
            car2.h += speed2 * sin(atan2(Beacon2_P.h - car2.h, Beacon2_P.w - car2.w));
            if(Beacon1_P.h - car1.h > -2 && Beacon1_P.h - car1.h <2 && Beacon1_P.w - car1.w > -2 && Beacon1_P.w - car1.w < 2)
            {
                Beacon1_P.status = 0;
                rt_kprintf("beacon snuffed out\n");
            }
            if(Beacon2_P.h - car2.h > -2 && Beacon2_P.h - car2.h <2 && Beacon2_P.w - car2.w > -2 && Beacon2_P.w - car2.w < 2)
            {
                Beacon2_P.status = 0;
                rt_kprintf("beacon snuffed out\n");
            }

        }
        else
        {
            car2.w += speed2 * cos(atan2(Beacon1_P.h - car1.h, Beacon1_P.w - car1.w));
            car2.h += speed2 * sin(atan2(Beacon1_P.h - car1.h, Beacon1_P.w - car1.w));
            car1.w += speed1 * cos(atan2(Beacon2_P.h - car2.h, Beacon2_P.w - car2.w));
            car1.h += speed1 * sin(atan2(Beacon2_P.h - car2.h, Beacon2_P.w - car2.w));
            if(Beacon1_P.h - car2.h > -2 && Beacon1_P.h - car2.h <2 && Beacon1_P.w - car2.w > -2 && Beacon1_P.w - car2.w < 2)
            {
                Beacon1_P.status = 0;
                rt_kprintf("beacon snuffed out\n");
            }
            if(Beacon2_P.h - car1.h > -2 && Beacon2_P.h - car1.h <2 && Beacon2_P.w - car1.w > -2 && Beacon2_P.w - car1.w < 2)
            {
                Beacon2_P.status = 0;
                rt_kprintf("beacon snuffed out\n");
            }
        }
        rt_thread_mdelay(500);
        rt_kprintf("bencon1_position:%d, %d\n", Beacon1_P.w, Beacon1_P.h);
        rt_kprintf("bencon2_position:%d, %d\n", Beacon2_P.w, Beacon2_P.h);
        rt_kprintf("car_position:%d, %d\n", car1.w, car1.h);
    }
}




int move_control_thread(void)
{
    rt_thread_t move_thread = RT_NULL;
    move_thread = rt_thread_create("mct", (void *)move_control, RT_NULL, 1024, 15, 20);
    rt_thread_startup(move_thread);
    return 0;
}

INIT_APP_EXPORT(move_control_thread);

rt_int8_t direction_count(rt_int8_t IMAGE_W, rt_int8_t IMAGE_H)
{
    distance1 = (IMAGE_W - car1.w)*(IMAGE_W - car1.w) + (IMAGE_H - car1.h)*(IMAGE_H - car1.h);
    distance2 = (IMAGE_W - car2.w)*(IMAGE_W - car2.w) + (IMAGE_H - car2.h)*(IMAGE_H - car2.h);
    return distance1 > distance2 ? 0:1;
}


