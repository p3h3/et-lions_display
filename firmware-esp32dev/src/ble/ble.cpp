#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "constants.h"

#include "images/connected.h"

#include "images/go_lions_rainbow.h"
#include "images/no_bitches.h"
#include "images/adidaslions.h"
#include "images/bushofstealers.h"
#include "images/etlionsrainbow.h"
#include "images/foul.h"
#include "images/lion.h"
#include "images/toor.h"
#include "images/wtf.h"
#include "images/bushof_dealers.h"
#include "images/medical_strippers.h"




uint8_t *bm_pointer;

uint8_t *brightness_pointer;
uint8_t brightness_before;

uint8_t *animation_pointer;




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
        *brightness_pointer = second_byte;

    }
};



class picCharacteristcCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *PCharacteristic){
        uint8_t firstByte = PCharacteristic->getValue()[0];

        // cancel animation
        *animation_pointer = 0;

        if(firstByte == 1){
            memcpy(bm_pointer, go_lions_rainbow_bm, sizeof(go_lions_rainbow_bm));
        }
        if(firstByte == 2){
            memcpy(bm_pointer, no_bitches_bm, sizeof(no_bitches_bm));
        }

        if(firstByte == 3){
            memcpy(bm_pointer, adidas_lions_bm, sizeof(go_lions_rainbow_bm));
        }
        if(firstByte == 4){
            memcpy(bm_pointer, bushof_stealers_bm, sizeof(no_bitches_bm));
        }

        if(firstByte == 5){
            memcpy(bm_pointer, etlions_rainbow_bm, sizeof(go_lions_rainbow_bm));
        }
        if(firstByte == 6){
            memcpy(bm_pointer, foul_bm, sizeof(no_bitches_bm));
        }

        if(firstByte == 7){
            memcpy(bm_pointer, lion_bm, sizeof(go_lions_rainbow_bm));
        }
        if(firstByte == 8){
            memcpy(bm_pointer, toor_bm, sizeof(no_bitches_bm));
        }

        if(firstByte == 9){
            memcpy(bm_pointer, wtf_bm, sizeof(go_lions_rainbow_bm));
        }

        if(firstByte == 10){
            memcpy(bm_pointer, bushof_dealers_bm, sizeof(no_bitches_bm));
        }

        if(firstByte == 11){
            memcpy(bm_pointer, medical_strippers_bm, sizeof(go_lions_rainbow_bm));
        }

        if(*brightness_pointer == 0){
            *brightness_pointer = 100;
        }
    }
};

class animationCharacteristicCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *PCharacteristic){
        uint8_t firstByte = PCharacteristic->getValue()[0];

        // ohne strom animation
        if(firstByte == 1){
            *animation_pointer = 1;
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


void bleInitPointers(uint8_t *bitmap, uint8_t *brightness, uint8_t *animation){
    bm_pointer = bitmap;
    brightness_pointer = brightness;
    animation_pointer = animation;
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
    bitmap1_char->setCallbacks(new animationCharacteristicCallback());
    BLECharacteristic *bitmap2_char = bitmap_service->createCharacteristic(
                                            BITMAP_BITMAP2_CHAR_UUID,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );
    bitmap2_char->setCallbacks(new picCharacteristcCallback());


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