#include <Arduino.h>

#include "Screen.h"

bool starck[10][5][5] =
    {
        {
            // 0
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
        },
        {
            // 1
            {0, 0, 0, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
        },
        {
            // 2
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
        },
        {
            // 3
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
        },
        {
            // 4
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
        },
        {
            // 5
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
        },
        {
            // 6
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
        },
        {
            // 7
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
        },
        {
            // 8
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
        },
        {// 9
         {1, 1, 1, 1, 1},
         {1, 0, 0, 0, 1},
         {1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1},
         {1, 1, 1, 1, 1}}};

Screen::Screen(int TFT_CS, int TFT_DC, int TFT_RST)
{
    screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    template["background"]["color"]["hex"]["24"] = true;
    template["number"]["color"]["hex"]["24"] = true;
    template["number"]["size"] = true;
    template["margin"]["left"] = true;
    template["margin"]["top"] = true;
    template["padding"] = true;
    style["background"]["color"]["hex"]["24"] = "000000";
    style["number"]["color"]["hex"]["24"] = "ffff00";
    style["number"]["size"] = 60;
    style["margin"]["left"] = 0;
    style["margin"]["top"] = 16;
    style["padding"] = 8;
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
            if (starck[number][(cy - y) / (w / 5)][(cx - x) / (h / 5)])
            {
                screen.fillRect(cx, cy, w / 5, h / 5, style["number"]["color"]["hex"]["16"].as<uint16_t>());
            }
        }
    }
}

void Screen::drawTime(int hours = 0, int minutes = 0)
{
    calculColor("background");
    calculColor("number");
    screen.fillScreen(style["background"]["color"]["hex"]["16"].as<uint16_t>());
    int numbersList[2][2] = {{0, 0}, {0, 0}};
    numbersList[0][1] = hours % 10;
    if (hours >= 10)
        numbersList[0][0] = floor(hours / 10);
    numbersList[1][1] = minutes % 10;
    if (minutes >= 10)
        numbersList[1][0] = floor(minutes / 10);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            int X = (x * (style["number"]["size"].as<int>() + style["padding"].as<int>())) + style["margin"]["left"].as<int>();
            int Y = (y * (style["number"]["size"].as<int>() + style["padding"].as<int>())) + style["margin"]["top"].as<int>();
            int size = style["number"]["size"].as<int>();
            drawNumber(X, Y, size, size, numbersList[y][x]);
        }
    }
}

void Screen::calculColor(String str)
{
    if (!style[str]["color"]["hex"]["16"])
    {
        if (!style[str]["color"]["rgb"])
        {
            if (!style[str]["color"]["hex"]["24"])
            {
                style[str]["color"]["hex"]["24"] = "ff0000";
            }
            int r, g, b;
            hexToRGB(style[str]["color"]["hex"]["24"].as<char *>(), r, g, b);
            style[str]["color"]["rgb"][0] = r;
            style[str]["color"]["rgb"][1] = g;
            style[str]["color"]["rgb"][2] = b;
        }
        style[str]["color"]["hex"]["16"] = rgbTo16bits(style[str]["color"]["rgb"][0].as<int>(), style[str]["color"]["rgb"][1].as<int>(), style[str]["color"]["rgb"][2].as<int>());
    }
}

void hexToRGB(char *hex, int &r, int &g, int &b)
{
    sscanf(hex, "%02x%02x%02x", &r, &g, &b);
}

uint16_t rgbTo16bits(uint8_t r, uint8_t g, uint8_t b)
{
    return (static_cast<uint8_t>((r / 255.0f) * 31.0f + 0.5f) << 11) | (static_cast<uint8_t>((g / 255.0f) * 63.0f + 0.5f) << 5) | static_cast<uint8_t>((b / 255.0f) * 31.0f + 0.5f);
}
