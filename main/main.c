/* LVGL Example project
 * 
 * Basic project to test LVGL on ESP32 based projects.
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include "sdkconfig.h"

#include <stdbool.h> // Newly Added
#include <stdio.h>
#include <stdlib.h> // Newly Added
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "screen_driver.h"
#include "../lvgl/include/lvgl_gui.h"
#include "qm_ui_entry.h"
#include "../lv_examples/lv_examples/src/lv_demo_widgets/lv_demo_widgets.h" // Newly Added
extern void lv_8ms_init(void);

#define LCD_WR_SCK 39
#define LCD_RS_DC 38
#define LCD_CS -1
#define LCD_RST 37
#define LCD_BL 0
#define LCD_D0 36
#define LCD_D1 35
#define LCD_D2 34
#define LCD_D3 33
#define LCD_D4 21
#define LCD_D5 18
#define LCD_D6 17
#define LCD_D7 16
#define SWAP_DATA 1
#define LCD_DRIVER SCREEN_CONTROLLER_ILI9488
#define SC_DIR SCR_DIR_RLTB

#define MAX_LOGO_TIME 20 // Duration of logo display

static const char *TAG = "main";

static scr_driver_t g_lcd;

void app_main(void)
{
    esp_err_t ret = ESP_OK;
    i2s_lcd_config_t i2s_lcd_cfg = {
        .data_width = 8,
        .pin_data_num = {
            LCD_D0,
            LCD_D1,
            LCD_D2,
            LCD_D3,
            LCD_D4,
            LCD_D5,
            LCD_D6,
            LCD_D7,
            // 1, 2, 3, 4, 5, 6, 7, 8,
        },
        .pin_num_cs = LCD_CS,
        .pin_num_wr = LCD_WR_SCK,
        .pin_num_rs = LCD_RS_DC,

        .clk_freq = 20000000,
        .i2s_port = I2S_NUM_0,
        .buffer_size = 32000,
        .swap_data = SWAP_DATA,
    };

    scr_interface_driver_t *iface_drv;
    scr_interface_create(SCREEN_IFACE_8080, &i2s_lcd_cfg, &iface_drv);
    ret = scr_find_driver(LCD_DRIVER, &g_lcd);
    if (ESP_OK != ret)
    {
        ESP_LOGE(TAG, "screen find failed");
        return;
    }
    scr_controller_config_t lcd_cfg = {
        .interface_drv = iface_drv,
        .pin_num_rst = LCD_RST,
        .pin_num_bckl = LCD_BL,
        .rst_active_level = 0,
        .bckl_active_level = 1,
        .offset_hor = 0,
        .offset_ver = 0,
        .width = CONFIG_LV_HOR_RES_MAX,
        .height = CONFIG_LV_VER_RES_MAX,
        .rotate = SC_DIR, 
    };
    ret = g_lcd.init(&lcd_cfg);
    if (ESP_OK != ret)
    {
        ESP_LOGE(TAG, "screen initialize failed");
        return;
    }
    
    lvgl_init(&g_lcd);
    
    lv_8ms_init();
    
    lv_demo_widgets(); // Newly Added

    //lv_qm_ui_entry();
}
