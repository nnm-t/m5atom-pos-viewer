#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"
#include "TM1637Display.h"

#include "ble-pos-viewer.h"
#include "pos-price.h"
#include "pos-num.h"
#include "pos-num-characteristic-callbacks.h"
#include "pos-price-characteristic-callbacks.h"

namespace
{
    constexpr uint8_t dio_pin = 26;
    constexpr uint8_t clock_pin = 32;
    constexpr uint8_t brightness = 10;

    // UUID 16bit形式でないとESP32 BLE ClientでAdvertiseできない
    BLEUUID service_uuid(static_cast<uint16_t>(0xF6E7));
    BLEUUID price_characteristic_uuid(static_cast<uint16_t>(0x0001));

    BLEPOSViewer ble_pos_viewer(service_uuid);

    TM1637Display tm1637(clock_pin, dio_pin);
    POSPrice price(tm1637);
    POSNum num;
}

void setup()
{
    M5.begin(true, true, true);

    // BLE Wrapper Class
    ble_pos_viewer.Init("M5Atom-Pos-Viewer");
    ble_pos_viewer.CreateCharacteristicRW<POSPriceCharacteristicCallbacks>(price_characteristic_uuid, &num, &price);
    ble_pos_viewer.Start();

    BLEAdvertisementData advertisement_data;
    ble_pos_viewer.StartAdvertising(advertisement_data, service_uuid);

    num.SetBrightness(brightness);
    num.Reset();
    price.SetBrightness(brightness);
    price.Reset();
}

void loop()
{
    M5.update();

    if (M5.Btn.wasPressed())
    {
        // Reset
        num.Reset();
        price.Reset();
    }

    price.Update();

    delay(100);
}