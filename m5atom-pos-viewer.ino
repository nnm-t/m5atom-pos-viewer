#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"
#include "TM1637Display.h"

#include "matrix_number.h"

#include "ble-pos-viewer.h"
#include "pos-num-characteristic-callbacks.h"
#include "pos-price-characteristic-callbacks.h"

namespace
{
    constexpr uint8_t dio_pin = 26;
    constexpr uint8_t clock_pin = 32;
    constexpr uint8_t brightness = 10;

    BLEUUID service_uuid(static_cast<uint16_t>(0xFFFF));
    BLEUUID num_characteristic_uuid(static_cast<uint16_t>(0x0000));
    BLEUUID price_characteristic_uuid(static_cast<uint16_t>(0x0001));

    BLEPOSViewer ble_pos_viewer(service_uuid);

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

    // BLE Wrapper Class
    ble_pos_viewer.Init("M5Atom-Pos-Viewer");
    ble_pos_viewer.CreateCharacteristicRW<POSNumCharacteristicCallbacks>(num_characteristic_uuid);
    ble_pos_viewer.CreateCharacteristicRW<POSPriceCharacteristicCallbacks>(price_characteristic_uuid);

    ble_pos_viewer.Start();

    BLEAdvertisementData advertisement_data;
    ble_pos_viewer.StartAdvertising(advertisement_data);

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