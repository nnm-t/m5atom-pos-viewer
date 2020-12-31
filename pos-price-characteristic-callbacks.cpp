#include "pos-price-characteristic-callbacks.h"

void POSPriceCharacteristicCallbacks::onRead(BLECharacteristic* pCharacteristic)
{

}

void POSPriceCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic)
{
    // 2bytes
    std::string value_str = pCharacteristic->getValue();
    uint16_t value = 0;

    if (value_str.length() < 1)
    {
        return;
    }

    if (value_str.length() > 1)
    {
        value = (static_cast<uint16_t>(value_str[0]) << 8) + static_cast<uint8_t>(value_str[1]);
    }
    else
    {
        value = static_cast<uint8_t>(value_str[0]);
    }

    if (value > 9999 | value < 0)
    {
        value = 0;
    }

    _price->ShowNumberDec(value);
}