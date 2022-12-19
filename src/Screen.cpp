#include <Arduino.h>

#include "Screen.h"

Screen::Screen(int TFT_CS, int TFT_DC, int TFT_RST)
{
    screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
}

void Screen::setup()
{
    screen.initR(INITR_BLACKTAB);
    screen.fillScreen(ST7735_BLACK);
}

void Screen::drawNumber(int x, int y, int w, int h, int number = 0)
{
    for (int cy = y; cy < (y + h); cy += (h / 5))
    {
        for (int cx = x; cx < (x + w); cx += (w / 5))
        {
            if (starck[number][cy - y / 5][cx - x / 5])
            {
                Serial.print("■");
            }
            else
                Serial.print("□");
        }
        Serial.println();
    }
    Serial.println();
}