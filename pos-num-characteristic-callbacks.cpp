#include "pos-num-characteristic-callbacks.h"

void POSNumCharacteristicCallbacks::onRead(BLECharacteristic* pCharacteristic)
{

}

void POSNumCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic)
{
    uint8_t* data = pCharacteristic->getData();

    _num->DrawNumber(*data);
}