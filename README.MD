# SSD1306 driver

This library implements only send commands/data to display API and requires to implement adapter functions

# Usage

```cpp
#include <PE_SSD1306.h>

void SSD1306_reset_t() {
    //TODO reset pins manipulation here
}

void SSD1306_write_t(uint8_t reg, const uint8_t *data, uint16_t size) {
    //TODO write data to display interface here (I2C or SPI)
}

PE_SSD1306 SSD1306 = PE_SSD1306(
    PE_SSD1306_VCC_INTERNAL, //<-- Display VCC mode, select for 5V or 3.3V
    128,                     //<-- Display width
    64,                      //<-- Display height
    SSD1306_reset_t,         //<-- Reset display adapter
    SSD1306_write_t          //<-- Write display adapter
);

int main(void) {
    // First need to send initialization sequences to display
    SSD1306.initialize();

    //TODO manipulation usage
}
```