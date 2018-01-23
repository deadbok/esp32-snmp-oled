#ifndef OLEDCOM_H
#define OLEDCON_H

#include <SSD1306.h>

//OLED pin coonections to the ESP32
//OLED address
#define OLED_ADDR 0x3c
//OLED I2C
#define OLED_SDA 4
#define OLED_SCL 15
//OLED reset
#define OLED_RST 16

//Display text resolution.
#define OLED_LINES 6
#define OLED_CHARS_LINE 21
#define OLED_CHARS_ALL (OLED_LINES * OLED_CHARS_LINE)

#define FONT_HEIGHT 10

class OLEDConsole
{
  private:
    int scroll();

  protected:
    unsigned int current_pos = 0;
    unsigned char buffer[OLED_LINES * OLED_CHARS_LINE];
  
  public:
    SSD1306 *display;
    
    OLEDConsole();
    void init();
    void puts(String str);
    void draw_buffer();
};

#endif