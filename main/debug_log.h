#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <spike/pup/colorsensor.h>
#include <spike/pup/motor.h>
#include <spike/pup/ultrasonicsensor.h>
#include <spike/pup/forcesensor.h>

/* 0 にするとログ出力がすべて無効化される */
#define DEBUG_LOG 1

typedef struct {
    pup_device_t *color;
    pup_motor_t  *left_motor;
    pup_motor_t  *right_motor;
    pup_device_t *ultrasonic;
    pup_device_t *force;
} debug_sensors_t;

#if DEBUG_LOG
void debug_log_init(debug_sensors_t *sensors);
void debug_log_all(const debug_sensors_t *sensors, int count);
#else
#define debug_log_init(sensors)        ((void)0)
#define debug_log_all(sensors, count)  ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_LOG_H */
