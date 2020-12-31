#include "pos-num.h"

void POSNum::SetBrightness(const uint8_t brightness)
{
    M5.dis.setBrightness(brightness);
}

const bool POSNum::DrawNumber(const uint8_t number)
{
    if (number >= number_length)
    {
        return false;
    }

    for (uint8_t y = 0; y < led_rowcol; y++)
    {
        for (uint8_t x = 0; x < led_rowcol; x++)
        {
            M5.dis.drawpix(x + y * led_rowcol, matrix_numbers[number][y][x]);
        }
    }

    return true;
}