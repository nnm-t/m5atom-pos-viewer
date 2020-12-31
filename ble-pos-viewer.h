#pragma once

#include "Arduino.h"
#include "M5Atom.h"
#include "BLEDevice.h"

class BLEPOSViewer
{
    const BLEUUID _service_uuid;

    BLEServer* _server = nullptr;
    BLEService* _service = nullptr;
    BLEAdvertising* _advertising = nullptr;

public:
    BLEPOSViewer(const BLEUUID& service_uuid) : _service_uuid(service_uuid)
    {

    }

    void Init(const char* device_name);

    void Start();

    void StartAdvertising(BLEAdvertisementData& advertisement_data, BLEUUID& service_uuid);

    template <class T, class... Args> BLECharacteristic* const CreateCharacteristic(const BLEUUID& uuid, const uint32_t property, Args... args);

    template <class T, class... Args> BLECharacteristic* const CreateCharacteristicRW(const BLEUUID& uuid, Args... args);
};

template <class T, class... Args> BLECharacteristic* const BLEPOSViewer::CreateCharacteristic(const BLEUUID& uuid, const uint32_t property, Args... args)
{
    BLECharacteristic* const characteristic = _service->createCharacteristic(uuid, property);
    characteristic->setCallbacks(new T(args...));

    return characteristic;
}

template <class T, class... Args> BLECharacteristic* const BLEPOSViewer::CreateCharacteristicRW(const BLEUUID& uuid, Args... args)
{
    return this->CreateCharacteristic<T, Args...>(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE, args...);
}