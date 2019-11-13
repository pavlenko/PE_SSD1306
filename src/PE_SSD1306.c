#include "PE_SSD1306.h"

void PE_SSD1306_initialize(PE_SSD1306_t *display)
{
    display->reset();

    uint8_t muxRatio   = display->height - 1;
    uint8_t chargePump = (display->vcc == PE_SSD1306_VCC_EXTERNAL) ? 0x10 : 0x14;
    uint8_t preCharge  = (display->vcc == PE_SSD1306_VCC_EXTERNAL) ? 0x22 : 0xF1;

    const uint8_t init1[] = {
        PE_SSD1306_DISPLAY_OFF,                  // 0xAE
        PE_SSD1306_DISPLAY_CLOCK_DIVIDER, 0x80u, // 0xD5, the suggested value 0x80
        PE_SSD1306_MULTIPLEX_RATIO, muxRatio,    // 0xA8, value
        PE_SSD1306_DISPLAY_OFFSET, 0x00u,        // 0xD3, no offset
        PE_SSD1306_START_LINE | 0x00u,           // 0x40 | val
        PE_SSD1306_CHARGE_PUMP, chargePump,      // 0x8D, val
        PE_SSD1306_MEMORY_MODE, 0x00u,           // 0x20, val (act like ks0108)
        PE_SSD1306_SEGMENT_REMAP_ON,             // 0xA0
        PE_SSD1306_COM_SCAN_DECREMENT,           // 0xC8
    };

    display->write(PE_SSD1306_WRITE_COMMAND, init1, sizeof(init1));

    if (96 == display->width && 16 == display->height) {
        uint8_t contrast = (display->vcc == PE_SSD1306_VCC_EXTERNAL) ? 0x10u : 0xAFu;

        const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x02u,     // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        display->write(PE_SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    } if (128 == display->width && 32 == display->height) {
        uint8_t contrast = 0x8Fu;

        const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x02u,      // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        display->write(PE_SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    } if (128 == display->width && 64 == display->height) {
        uint8_t contrast = (display->vcc == PE_SSD1306_VCC_EXTERNAL) ? 0x9Fu : 0xCFu;

        const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x12u,     // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        display->write(PE_SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    }

    const uint8_t init3[] = {
        PE_SSD1306_PRE_CHARGE_PERIOD, preCharge, // 0xD9
        PE_SSD1306_VCOMH_DESELECT, 0x40u,        // 0xDB, val
        PE_SSD1306_ALL_ON_DISABLE,               // 0xA4
        PE_SSD1306_INVERSE_DISABLE,              // 0xA6
        PE_SSD1306_SCROLL_DISABLE,               // 0x2E
        PE_SSD1306_DISPLAY_ON,
    };

    display->write(PE_SSD1306_WRITE_COMMAND, init3, sizeof(init3));
}

void PE_SSD1306_setEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_DISPLAY_ON : PE_SSD1306_DISPLAY_OFF),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setInverse(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_INVERSE_ENABLE : PE_SSD1306_INVERSE_DISABLE),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setContrast(PE_SSD1306_t *display, uint8_t contrast)
{
    const uint8_t data[] = {
        PE_SSD1306_CONTRAST_CONTROL,
        contrast,
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setFlipX(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_SEGMENT_REMAP_OFF : PE_SSD1306_SEGMENT_REMAP_ON),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setFlipY(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_COM_SCAN_INCREMENT : PE_SSD1306_COM_SCAN_DECREMENT),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setAllEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_ALL_ON_ENABLE : PE_SSD1306_ALL_ON_DISABLE),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_setScrollEnabled(PE_SSD1306_t *display, PE_SSD1306_BOOL_t value)
{
    const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_SCROLL_ENABLE : PE_SSD1306_SCROLL_DISABLE),
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE_SSD1306_update(PE_SSD1306_t *display, uint8_t *buffer, uint16_t size)
{
    static const uint8_t data[] = {
        PE_SSD1306_PAGE_START_ADDRESS,
        PE_SSD1306_COLUMN_L_ADDRESS,
        PE_SSD1306_COLUMN_H_ADDRESS,
    };

    display->write(PE_SSD1306_WRITE_COMMAND, data, sizeof(data));
    display->write(PE_SSD1306_WRITE_DATA, buffer, size);
}
