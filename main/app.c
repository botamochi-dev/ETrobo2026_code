#include "app.h"
#include "kernel_cfg.h"
#include <t_syslog.h>
#include "debug_log.h"

#include <spike/hub/button.h>
#include <spike/hub/display.h>
#include <spike/hub/speaker.h>
#include <spike/hub/system.h>

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    hub_speaker_set_volume(50);
    hub_display_char('B');
    hub_speaker_play_tone(NOTE_A4, 300);
    dly_tsk(3 * 1000 * 1000); /* BLE接続待ち */

    /* センサー・モーター初期化 */
    debug_sensors_t sensors = {
        .color = pup_color_sensor_get_device(PBIO_PORT_ID_E),
        .left_motor = pup_motor_get_device(PBIO_PORT_ID_B),
        .right_motor = pup_motor_get_device(PBIO_PORT_ID_A),
        .ultrasonic = pup_ultrasonic_sensor_get_device(PBIO_PORT_ID_F),
        .force = pup_force_sensor_get_device(PBIO_PORT_ID_D),
    };
    if(sensors.left_motor)
        pup_motor_setup(sensors.left_motor, PUP_DIRECTION_COUNTERCLOCKWISE, true);
    if(sensors.right_motor)
        pup_motor_setup(sensors.right_motor, PUP_DIRECTION_CLOCKWISE, true);
    debug_log_init(&sensors);

    int count = 0;
    hub_button_t pressed;

    while(1) {
        /* センターボタンで停止 */
        hub_button_is_pressed(&pressed);
        if(pressed & HUB_BUTTON_CENTER) {
            break;
        }

        debug_log_all(&sensors, count);

        count++;
        dly_tsk(100 * 1000); /* 100ms周期 */
    }

    syslog(LOG_NOTICE, "stopped");
    dly_tsk(500 * 1000);

    ext_tsk();
}
