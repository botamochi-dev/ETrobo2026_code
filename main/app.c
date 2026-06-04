#include "app.h"
#include "kernel_cfg.h"
#include <t_syslog.h>

#include <spike/hub/button.h>
#include <spike/hub/display.h>
#include <spike/hub/speaker.h>
#include <spike/hub/system.h>
#include <spike/pup/colorsensor.h>

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    hub_speaker_set_volume(50);
    hub_display_char('B');
    hub_speaker_play_tone(NOTE_A4, 300);
    dly_tsk(3 * 1000 * 1000); /* BLE接続待ち */

    pup_device_t* color_sensor = pup_color_sensor_get_device(PBIO_PORT_ID_E);

    int count = 0;
    hub_button_t pressed;

    while(1) {
        /* センターボタンで停止 */
        hub_button_is_pressed(&pressed);
        if(pressed & HUB_BUTTON_CENTER) {
            break;
        }

        pup_color_rgb_t rgb = pup_color_sensor_rgb(color_sensor);

        /* pybricks-ble-monitor で受信できるCSV形式で送信 */
        syslog(LOG_NOTICE, "%d,%d,%d,%d", count, rgb.r, rgb.g, rgb.b);

        count++;
        dly_tsk(100 * 1000); /* 100ms周期 */
    }

    syslog(LOG_NOTICE, "stopped");
    dly_tsk(500 * 1000);  // 500ms待ってBLE送信を完了させる
    hub_system_shutdown();
    ext_tsk();
}
