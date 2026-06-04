#include "app.h"
#include "kernel_cfg.h"

#include <spike/hub/button.h>
#include <spike/hub/display.h>
#include <spike/hub/speaker.h>
#include <spike/hub/system.h>
#include <spike/hub/battery.h>

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    hub_speaker_set_volume(50);
    hub_display_char('B');
    hub_speaker_play_tone(NOTE_A4, 300);
    dly_tsk(3 * 1000 * 1000);  /* BLE接続待ち */

    int count = 0;
    hub_button_t pressed;

    while (1) {
        /* センターボタンで停止 */
        hub_button_is_pressed(&pressed);
        if (pressed & HUB_BUTTON_CENTER) {
            break;
        }

        int voltage = hub_battery_get_voltage();
        int current = hub_battery_get_current();

        /* pybricks-ble-monitor で受信できるCSV形式で送信 */
        syslog(LOG_NOTICE, "%d,%d,%d", count, voltage, current);

        count++;
        dly_tsk(100 * 1000);  /* 100ms周期 */
    }

    syslog(LOG_NOTICE, "stopped");
    hub_system_shutdown();
    ext_tsk();
}
