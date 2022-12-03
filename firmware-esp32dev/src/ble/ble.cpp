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



class bitmapControlCallback: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic* pCharacteristic){
        Serial.printf("bitmap control characteristic read");
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



class bitmapDataCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *PCharacteristic){
        Serial.printf("bitmap data write\n");
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
    // general control service
    BLEService *gen_control_service = pServer->createService(GENERAL_CONTROL_SERVICE_UUID);
    BLECharacteristic *gen_control_char = gen_control_service->createCharacteristic(
                                            GENERAL_CONTROL_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    gen_control_char->setValue("obama lama");
    gen_control_char->setCallbacks(new genControlCallback());




    // bitmap service
    BLEService *bitmap_service = pServer->createService(BITMAP_SERVICE_UUID);
    BLECharacteristic *bitmap_control_char = bitmap_service->createCharacteristic(
                                            BITMAP_CONTROL_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap_control_char->setValue("obama lama");
    bitmap_control_char->setCallbacks(new bitmapControlCallback());

    // data characteristics - all go to one callback
    BLECharacteristic *bitmap1_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP1_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap1_char->setCallbacks(new bitmapDataCallback());
    BLECharacteristic *bitmap2_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP2_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap2_char->setCallbacks(new bitmapDataCallback());
    BLECharacteristic *bitmap3_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP3_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap3_char->setCallbacks(new bitmapDataCallback());
    BLECharacteristic *bitmap4_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP4_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap4_char->setCallbacks(new bitmapDataCallback());
    BLECharacteristic *bitmap5_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP5_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap5_char->setCallbacks(new bitmapDataCallback());


    // start the services (otherwise they aren't displayed and aren't accessible)
    gen_control_service->start();
    bitmap_service->start();
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