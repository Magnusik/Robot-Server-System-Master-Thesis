#ifndef _ENCODER_COUNTER_H_
#define _ENCODER_COUNTER_H_
#include "nrfx_gpiote.h"
#include "nrfx_timer.h"
/*
typedef struct {
    long int left;
    long int right;
}encoderTicks; */
#include "encoder.h"


void encoder_with_counter_init();

encoderTicks encoder_with_counter_get_ticks_since_last_time();
encoderTicks encoder_with_counter_get_all_ticks();
#endif /* _ENCODER_H_ */