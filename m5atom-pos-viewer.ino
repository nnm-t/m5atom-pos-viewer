#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"
#include "TM1637Display.h"

#include "matrix_number.h"
#include "ble-pos-client.h"

namespace
{
    constexpr uint8_t dio_pin = 26;
    constexpr uint8_t clock_pin = 32;
    constexpr uint8_t brightness = 10;

    BLEUUID service_uuid(static_cast<uint16_t>(0xFFFF));
    BLEUUID num_characteristic_uuid(static_cast<uint16_t>(0x0000));
    BLEUUID price_characteristic_uuid(static_cast<uint16_t>(0x0001));

    BLEPosClient ble_client("M5Atom-Pos-Viewer", service_uuid, num_characteristic_uuid, price_characteristic_uuid);

    uint8_t count = 0;

    TM1637Display tm1637(clock_pin, dio_pin);
}


bool do_connect = false;
bool do_scan = false;
bool is_connected = false;

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

    ble_client.Begin();

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

    ble_client.Update();
}