#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "constants.h"

#include "images/maschis.h"


uint8_t *bm_pointer;

uint8_t *brightness_pointer;
uint8_t brightness_before;



class genControlCallback: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic* pCharacteristic){
        Serial.printf("general control characteristic read");
    }

    void onWrite(BLECharacteristic *PCharacteristic){
        uint8_t firstByte = PCharacteristic->getValue()[0];

        // if the first bit of the first byte is true
        if((firstByte & 0x01) == 1){
            // turn on / keep on the matrix
            *brightness_pointer = brightness_before;
        }else{
            // turn off / keep off the matrix
            brightness_before = *brightness_pointer;
            *brightness_pointer = 0;
        }

        // set brightness of the matrix, ignore brughtness 0
        uint8_t second_byte = PCharacteristic->getValue()[1];
        if(second_byte != 0){
            *brightness_pointer = second_byte;
        }

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


void bleInitPointers(uint8_t *bitmap, uint8_t *brightness){
    bm_pointer = bitmap;
    brightness_pointer = brightness;
}


BLEServer *initBLE(){
    BLEDevice::init("led matrix");
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
    gen_control_char->setCallbacks(new genControlCallback());

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