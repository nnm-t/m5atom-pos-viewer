#include "pos-price-characteristic-callbacks.h"

void POSPriceCharacteristicCallbacks::onRead(BLECharacteristic* pCharacteristic)
{

}

void POSPriceCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic)
{
    // 3bytes
    std::string value_str = pCharacteristic->getValue();
    uint16_t price = 0;
    uint8_t num = 0;

    if (value_str.length() < 1 | value_str.length() > 3)
    {
        return;
    }

    num = static_cast<uint8_t>(value_str[0]);

    if (value_str.length() == 3)
    {
        price = (static_cast<uint16_t>(value_str[1]) << 8) + static_cast<uint8_t>(value_str[2]);
    }
    else if (value_str.length() == 2)
    {
        price = static_cast<uint8_t>(value_str[1]);
    }

    if (price > 9999)
    {
        price = 9999;
    }

    _num->DrawNumber(num);
    _price->ShowNumberDec(price);
}