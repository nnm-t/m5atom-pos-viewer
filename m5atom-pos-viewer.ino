#include "Arduino.h"
#include "M5Atom.h"
#include "TM1637Display.h"

#include "matrix_number.h"

namespace
{
    constexpr uint8_t dio_pin = 26;
    constexpr uint8_t clock_pin = 32;
    constexpr uint8_t brightness = 10;

    uint8_t count = 0;

    TM1637Display tm1637(clock_pin, dio_pin);
}

bool drawNumbers(const uint8_t number)
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

    tm1637.showNumberDec(number * 100);

    return true;
}

void setup()
{
    M5.begin(true, true, true);

    M5.dis.setBrightness(brightness);
    tm1637.setBrightness(brightness);
    drawNumbers(count);
}

void loop()
{
    M5.update();

    if (M5.Btn.wasPressed())
    {
        if(++count >= number_length)
        {
            count = 0;
        }

        drawNumbers(count);
    }
}