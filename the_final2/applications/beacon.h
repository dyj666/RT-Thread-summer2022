#ifndef _MOVE_H_
#define _MOVE_H_

#include <rtthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    rt_int8_t w;
    rt_int8_t h;
    bool status;
}Beacon_P;

typedef struct {
    rt_int8_t w;
    rt_int8_t h;
}Car_P;

#define _H 60
#define _W 80


extern Beacon_P Beacon1_P;
extern Beacon_P Beacon2_P;
extern Car_P car1,car2;
#endif
