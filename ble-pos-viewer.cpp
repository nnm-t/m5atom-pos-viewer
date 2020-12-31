#include "ble-pos-viewer.h"

void BLEPOSViewer::Init(const char* device_name)
{
    BLEDevice::init(device_name);
    _server = BLEDevice::createServer();

    _service = _server->createService(_service_uuid);
}

void BLEPOSViewer::Start()
{
    _service->start();
}

void BLEPOSViewer::StartAdvertising(BLEAdvertisementData& advertisement_data, BLEUUID& service_uuid)
{
    _advertising = _server->getAdvertising();
    _advertising->setAdvertisementData(advertisement_data);
    _advertising->addServiceUUID(service_uuid);
    _advertising->setScanResponse(true);
    _advertising->setMinPreferred(0x06);
    _advertising->setMinPreferred(0x12);
    _advertising->start();
}