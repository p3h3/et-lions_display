#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "constants.h"


BLEServer *initBLE(){
    BLEDevice::init("mmmmmhhhhhhhh");
    BLEServer *pServer = BLEDevice::createServer();
    return pServer;
}

void initServicesAndChars(BLEServer *pServer){
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                            CHARACTERISTIC_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE
                                        );

    pCharacteristic->setValue("obama lama");
    pService->start();
    
}

void startBLE(){
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}



void allTogether(){
    initServicesAndChars(initBLE());
    startBLE();
}