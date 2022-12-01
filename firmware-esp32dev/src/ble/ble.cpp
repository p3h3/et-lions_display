#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "constants.h"

#include "images/connected.h"


uint8_t *bm_pointer;


class bleCallback: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic* pCharacteristic){
        Serial.printf("char read");
    }

    void onWrite(BLECharacteristic *PCharacteristic){
        Serial.printf("char write");
    }
};

class bleConnectionCallback: public BLEServerCallbacks{
    void onConnect(BLEServer *pServer){
        Serial.printf("connected!");
        
        memcpy(bm_pointer, connected_bm, sizeof(connected_bm));
    }
    void onDisconnect(BLEServer *pServer){
        Serial.printf("disconnected!");
    }
};


void bleInitBitmapPointer(uint8_t *bitmap){
    bm_pointer = bitmap;
}


BLEServer *initBLE(){
    BLEDevice::init("mmmmmhhhhhhhh");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new bleConnectionCallback());
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
    pCharacteristic->setCallbacks(new bleCallback());

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