//
// Created by vl0011 on 23. 7. 29.
//

#include "GrepfaController.h"
bool coils[2] = {false, false};
// 0 - on/off
// 1- direction
uint16_t input_registers[4] = {
        TYPE_MOTOR,     // type
        DEVICE_VERSION, // version
        0,              // sensor 1
        0               // sensor 2
};
void GrepfaController::begin(HardwareSerial& serial, pin_size_t A, pin_size_t B) {
    seg.begin(SEG_HARDWARE, SEG_DIGIT_NUM, digits, segs,
              true, false, false, false);

    seg.setChars("---");

    relayA = A;
    relayB = B;

    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);

    slave = new ModbusRTUSlave(serial);

    slave->configureCoils(coils, 3);
    slave->configureInputRegisters(input_registers, 4);


    slave->begin(MODBUS_ID, MODBUS_BAUD, MODBUS_PARITY);

    xTaskCreate(GrepfaController::mbTask, "modbus", 1024, this, 4, NULL);
//    xTaskCreate(GrepfaController::segTask, "segment", 128, this, 5, NULL);
}

void GrepfaController::poll() {
    slave->poll();

    if (mode) {
        pollAuto();
    } else {
        pollManual();
    }
}



void GrepfaController::mbTask(void * param) {
    auto* gc = (GrepfaController*) param;
    while (1) {
        gc->poll();
    }
}

void GrepfaController::setManual() {
}

void GrepfaController::segTask(void * param) {
    auto* seg = (GrepfaController*) param;
    while (1) {
        seg->seg.refreshDisplay();
    }
}

void GrepfaController::pollAuto() {
    if (coils[COIL_ADDRESS_ON]) {
        if (coils[COIL_ADDRESS_DIRECTION]) {
            seg.setChars("A.OP");
        } else {
            seg.setChars("A.CL");
        }
        digitalWrite(relayA,  coils[COIL_ADDRESS_DIRECTION]);
        digitalWrite(relayB, !coils[COIL_ADDRESS_DIRECTION]);

    } else {
        digitalWrite(relayA, LOW);
        digitalWrite(relayB, LOW);
        seg.setChars("A.ST");
    }
    seg.refreshDisplay();
}

void GrepfaController::pollManual() {

}
