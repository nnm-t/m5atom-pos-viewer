#pragma once

#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"

class POSPriceCharacteristicCallbacks : public BLECharacteristicCallbacks
{
public:
    void onRead(BLECharacteristic* pCharacteristic) override;

    void onWrite(BLECharacteristic* pCharacteristic) override;
};