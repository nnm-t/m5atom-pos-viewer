#pragma once

#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"

#include "pos-num.h"

class POSNumCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    POSNum* _num;

public:
    POSNumCharacteristicCallbacks(POSNum* num) : _num(num)
    {

    }

    void onRead(BLECharacteristic* pCharacteristic) override;

    void onWrite(BLECharacteristic* pCharacteristic) override;
};