#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "constants.h"

#include "images/maschis.h"


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
        Serial.printf("BLE connected!\n");
        
        // hacky but it works!
        memcpy(bm_pointer, connected_bm, sizeof(connected_bm));
    }
    void onDisconnect(BLEServer *pServer){
        Serial.printf("BLE disconnected!\n");
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
    BLEService *gen_control_service = pServer->createService(GENERAL_CONTROL_SERVICE_UUID);
    BLECharacteristic *gen_control_char = gen_control_service->createCharacteristic(
                                            GENERAL_CONTROL_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    gen_control_char->setValue("obama lama");
    gen_control_char->setCallbacks(new bleCallback());

    gen_control_service->start();
}

void startBLE(){
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(GENERAL_CONTROL_SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}



void bleStartAll(){
    initServicesAndChars(initBLE());
    startBLE();
}