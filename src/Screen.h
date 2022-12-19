#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

#include "Numbers.h"

class Screen
{
public:
    Screen(int TFT_CS, int TFT_DC, int TFT_RST);
    void setup();
    void drawNumber(int x, int y, int w, int h, int number = 0);
    // void drawNumber(int x, int y, int w, int h, int number = 0, bool *style = &starck);
    Adafruit_ST7735 screen = Adafruit_ST7735(0, 0, 0);
};

