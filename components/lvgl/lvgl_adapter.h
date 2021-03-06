#ifndef _LVGL_LCD_ADAPTER_H
#define _LVGL_LCD_ADAPTER_H

#include "lvgl.h"
#include "esp_err.h"
#include "screen_driver.h"
#include "lcd_touch.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
 * @brief Initiliaze display device for lvgl
 * @note  This function only registers the dispaly driver into lvgl, and does not initiliaze the display driver.
 * 
 * @param driver Pointer to display driver
 * @return
 *  - ESP_OK: Success
 *  - ESP_ERR_NO_MEM: Cannot allocate memory
 *  - ESP_ERR_INVALID_ARG: Invalid pointer of driver
 */
    esp_err_t lvgl_display_init(scr_driver_t *driver);
    esp_err_t lvgl_indev_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _LVGL_LCD_ADAPTER_H */