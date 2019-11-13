#ifndef PE_SSD1306_H
#define PE_SSD1306_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SSD1306 based displays API, except connection transport & graphics
 */
#include <stdint.h>

#define PE_SSD1306_I2C_ADDRESS_7BIT_A 0x3Cu
#define PE_SSD1306_I2C_ADDRESS_7BIT_B 0x3Du

#define PE_SSD1306_I2C_ADDRESS_8BIT_A 0x78u
#define PE_SSD1306_I2C_ADDRESS_8BIT_B 0x7Au

#define PE_SSD1306_WRITE_COMMAND 0x00u
#define PE_SSD1306_WRITE_DATA    0x40u

#define PE_SSD1306_COLUMN_L_ADDRESS      0x00u
#define PE_SSD1306_COLUMN_H_ADDRESS      0x10u
#define PE_SSD1306_MEMORY_MODE           0x20u
#define PE_SSD1306_SCROLL_DISABLE        0x2Eu
#define PE_SSD1306_SCROLL_ENABLE         0x2Fu
#define PE_SSD1306_START_LINE            0x40u
#define PE_SSD1306_CONTRAST_CONTROL      0x81u
#define PE_SSD1306_CHARGE_PUMP           0x8Du
#define PE_SSD1306_SEGMENT_REMAP_OFF     0xA0u
#define PE_SSD1306_SEGMENT_REMAP_ON      0xA1u
#define PE_SSD1306_ALL_ON_DISABLE        0xA4u
#define PE_SSD1306_ALL_ON_ENABLE         0xA5u
#define PE_SSD1306_INVERSE_DISABLE       0xA6u
#define PE_SSD1306_INVERSE_ENABLE        0xA7u
#define PE_SSD1306_MULTIPLEX_RATIO       0xA8u
#define PE_SSD1306_DISPLAY_OFF           0xAEu
#define PE_SSD1306_DISPLAY_ON            0xAFu
#define PE_SSD1306_PAGE_START_ADDRESS    0xB0u
#define PE_SSD1306_COM_SCAN_INCREMENT    0xC0u
#define PE_SSD1306_COM_SCAN_DECREMENT    0xC8u
#define PE_SSD1306_DISPLAY_OFFSET        0xD3u
#define PE_SSD1306_DISPLAY_CLOCK_DIVIDER 0xD5u
#define PE_SSD1306_PRE_CHARGE_PERIOD     0xD9u
#define PE_SSD1306_COM_PINS_CONFIG       0xDAu
#define PE_SSD1306_VCOMH_DESELECT        0xDBu

typedef enum {
    PE_SSD1306_FALSE = (uint8_t) 0x00u,
    PE_SSD1306_TRUE = (uint8_t) 0x01u,
} PE_SSD1306_BOOL_t;

typedef enum {
    PE_SSD1306_VCC_EXTERNAL = 0x01u,
    PE_SSD1306_VCC_INTERNAL = 0x02u,
} PE_SSD1306_VCC_t;

typedef void (*PE_SSD1306_reset_t)();

typedef void (*PE_SSD1306_write_t)(uint8_t reg, const uint8_t *data, uint16_t size);

typedef struct {
    PE_SSD1306_VCC_t vcc;
    uint8_t width;
    uint8_t height;
    PE_SSD1306_reset_t reset;
    PE_SSD1306_write_t write;
} PE_SSD1306_t;

/**
 * Initialize display procedure
 *
 * @param display
 */
void PE_SSD1306_initialize(PE_SSD1306_t *display);

/**
 * Set display enabled / disabled
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Inverse display pixels state (do not affect real memory data)
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setInverse(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Set display contrast
 *
 * @param display
 * @param contrast
 */
void PE_SSD1306_setContrast(PE_SSD1306_t *display, uint8_t contrast);

/**
 * Set display flipped horizontally
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setFlipX(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Set display flipped vertically
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setFlipY(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Set all pixels on, usable for damage test, maybe
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setAllEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Enable/disable scrolling
 *
 * @param display
 * @param value
 */
void PE_SSD1306_setScrollEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value);

/**
 * Update display ram with specific buffer
 *
 * @param display
 * @param buffer
 * @param size
 */
void PE_SSD1306_update(PE_SSD1306_t *display, uint8_t *buffer, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif //PE_SSD1306_H
