#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <math.h>

class Screen
{
    public:
        Screen(int TFT_CS, int TFT_DC, int TFT_RST);
        void setup();
        // void drawNumber(int x, int y, int w, int h, int number = 0, bool *style = &starck);
        void drawNumber(int x, int y, int w, int h, int number = 0);
        void drawTime(int hours = 0, int minutes = 0);
        void calculColor(String str);
        StaticJsonDocument<200> style;
        StaticJsonDocument<200> defaultStyle;
        Adafruit_ST7735 screen = Adafruit_ST7735(0, 0, 0);
};

void hexToRGB(char* hex, int &r, int &g, int &b);
uint16_t rgbTo16bits(uint8_t r, uint8_t g, uint8_t b);