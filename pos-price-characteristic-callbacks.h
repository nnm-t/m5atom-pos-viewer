#pragma once

#include <string>

#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"

#include "pos-num.h"
#include "pos-price.h"

class POSPriceCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    POSNum* _num;
    POSPrice* _price;

public:
    POSPriceCharacteristicCallbacks(POSNum* num, POSPrice* price) : _num(num), _price(price)
    {

    }

    void onRead(BLECharacteristic* pCharacteristic) override;

    void onWrite(BLECharacteristic* pCharacteristic) override;
};