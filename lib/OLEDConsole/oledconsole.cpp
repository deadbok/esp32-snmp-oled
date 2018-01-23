#include "oledconsole.h"

OLEDConsole::OLEDConsole()
{
    this->display = new SSD1306(OLED_ADDR, OLED_SDA, OLED_SCL);
    memset(this->buffer, ' ', OLED_CHARS_ALL);
}

void OLEDConsole::init()
{
    //Set the display reset pin as an output.
    pinMode(OLED_RST, OUTPUT);
    //Set GPIO16 low to reset OLED.
    digitalWrite(OLED_RST, LOW);
    delay(50);
    //While OLED is running, must set GPIO16 in high
    digitalWrite(OLED_RST, HIGH);
    //Initialising the display.
    this->display->init();
    delay(100);

    //Set some defaults.
    display->flipScreenVertically();
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
}

void OLEDConsole::draw_buffer()
{
    int i = 0;
    int y = 0;
    char line[OLED_CHARS_LINE + 1];



    this->display->clear();
    while ((i + 1) < OLED_CHARS_ALL)
    {
        memcpy(line, (const char *)(this->buffer + i), OLED_CHARS_LINE);
        line[OLED_CHARS_LINE] = '\0';
        this->display->drawString(0, y, (const char *)(line));
        i += OLED_CHARS_LINE;
        y += FONT_HEIGHT;
    }
    this->display->display();
}

int OLEDConsole::scroll()
{
    unsigned char tbuffer[OLED_LINES * OLED_CHARS_LINE];
    unsigned int i = 0;

    memcpy(tbuffer, this->buffer, OLED_CHARS_ALL);
/*     for (i = 0; i < OLED_CHARS_ALL; i++)
    {
        tbuffer[i] = this->buffer[i];
    } */

    memcpy(this->buffer, tbuffer + OLED_CHARS_LINE, OLED_CHARS_ALL - OLED_CHARS_LINE);
/*     for (i = OLED_CHARS_LINE; i < OLED_CHARS_ALL; i++)
    {
        this->buffer[i - OLED_CHARS_LINE] = tbuffer[i];
    } */

    memset(this->buffer + (OLED_CHARS_ALL - OLED_CHARS_LINE), 0, OLED_CHARS_LINE);
/*     for (i = OLED_CHARS_ALL - OLED_CHARS_LINE; i < OLED_CHARS_ALL; i++)
    {
        this->buffer[i] = ' ';
    } */
    //this->draw_buffer();
    
    return(OLED_CHARS_ALL - OLED_CHARS_LINE);
}

void OLEDConsole::puts(String str)
{

    unsigned int i_src = 0;
    unsigned int i_dst = this->current_pos;

    // Keep adding characters from the input until we're through.
    while (i_src < str.length())
    {      
        if (str[i_src] == '\n')
        {
            i_dst = ((i_dst / OLED_CHARS_LINE) + 1) * OLED_CHARS_LINE;
        }
        else 
        {
            if (i_dst < OLED_CHARS_ALL)
            {
                this->buffer[i_dst] = str[i_src];
                i_dst++;
            }
            else
            {
                i_dst = this->scroll();
                this->buffer[i_dst] = str[i_src];
                i_dst++;
            }
        }
        i_src++;
    }
    this->current_pos = i_dst;

    //this->draw_buffer();
}