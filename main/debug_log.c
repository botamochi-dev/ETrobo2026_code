#include "debug_log.h"

#if DEBUG_LOG

#include <t_syslog.h>
#include <spike/hub/imu.h>
#include <spike/hub/battery.h>

void debug_log_init(debug_sensors_t *sensors) {
    if (sensors->color) pup_color_sensor_light_on(sensors->color);
    hub_imu_init();
}

void debug_log_all(const debug_sensors_t *sensors, int count) {
    /* 値が変化した時だけ送信（デルタ送信） */
    switch (count % 6) {
    case 0: {
        if (!sensors->color) break;
        pup_color_rgb_t rgb = pup_color_sensor_rgb(sensors->color);
        static int32_t pr = -1, pg = -1, pb = -1;
        if (rgb.r != pr || rgb.g != pg || rgb.b != pb) {
            syslog(LOG_NOTICE, "COLOR,%d,%d,%d,%d", count, rgb.r, rgb.g, rgb.b);
            pr = rgb.r; pg = rgb.g; pb = rgb.b;
        }
        break;
    }
    case 1: {
        if (!sensors->left_motor || !sensors->right_motor) break;
        int32_t lspd = pup_motor_get_speed(sensors->left_motor);
        int32_t rspd = pup_motor_get_speed(sensors->right_motor);
        int32_t lcnt = pup_motor_get_count(sensors->left_motor);
        int32_t rcnt = pup_motor_get_count(sensors->right_motor);
        static int32_t pls = -9999, prs = -9999, plc = -9999, prc = -9999;
        if (lspd != pls || rspd != prs || lcnt != plc || rcnt != prc) {
            syslog(LOG_NOTICE, "MOTOR,%d,%d,%d,%d,%d", count, lspd, rspd, lcnt, rcnt);
            pls = lspd; prs = rspd; plc = lcnt; prc = rcnt;
        }
        break;
    }
    case 2: {
        float angv[3];
        hub_imu_get_angular_velocity(angv);
        int heading = (int)hub_imu_get_heading();
        int av_z = (int)angv[2];
        static int ph = -9999, pav = -9999;
        if (heading != ph || av_z != pav) {
            syslog(LOG_NOTICE, "IMU,%d,%d,%d", count, heading, av_z);
            ph = heading; pav = av_z;
        }
        break;
    }
    case 3: {
        if (!sensors->ultrasonic) break;
        int32_t dist = pup_ultrasonic_sensor_distance(sensors->ultrasonic);
        static int32_t pd = -9999;
        if (dist != pd) {
            syslog(LOG_NOTICE, "ULTRA,%d,%d", count, dist);
            pd = dist;
        }
        break;
    }
    case 4: {
        if (!sensors->force) break;
        int touched = pup_force_sensor_touched(sensors->force) ? 1 : 0;
        int force_x100 = (int)(pup_force_sensor_force(sensors->force) * 100.0f);
        static int pt = -1, pf = -9999;
        if (touched != pt || force_x100 != pf) {
            syslog(LOG_NOTICE, "FORCE,%d,%d,%d", count, touched, force_x100);
            pt = touched; pf = force_x100;
        }
        break;
    }
    case 5: {
        int32_t volt = hub_battery_get_voltage();
        int32_t curr = hub_battery_get_current();
        static int32_t pv = -1, pc = -1;
        if (volt != pv || curr != pc) {
            syslog(LOG_NOTICE, "BAT,%d,%d,%d", count, volt, curr);
            pv = volt; pc = curr;
        }
        break;
    }
    }
}

#endif /* DEBUG_LOG */
