#pragma once

#include <string>

#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"

#include "pos-price.h"

class POSPriceCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    POSPrice* _price;

public:
    POSPriceCharacteristicCallbacks(POSPrice* price) : _price(price)
    {

    }

    void onRead(BLECharacteristic* pCharacteristic) override;

    void onWrite(BLECharacteristic* pCharacteristic) override;
};