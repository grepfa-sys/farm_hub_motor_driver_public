//
// Created by vl0011 on 23. 7. 29.
//

#ifndef UNTITLED_GREPFACONTROLLER_H
#define UNTITLED_GREPFACONTROLLER_H

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <Arduino.h>
#include <SevSeg.h>
#include <ModbusRTUSlave.h>

// modbus device id
#define MODBUS_ID (11)

// modbus serial parity - default data - 8, stop - 1, parity - even
#define MODBUS_PARITY SERIAL_8E1

// modbus serial baud
#define MODBUS_BAUD 9600

// segment pin
#define PIN_SEGMENT_A  20
#define PIN_SEGMENT_B  18
#define PIN_SEGMENT_C  22
#define PIN_SEGMENT_D  27
#define PIN_SEGMENT_E  28
#define PIN_SEGMENT_F  19
#define PIN_SEGMENT_G  21
#define PIN_SEGMENT_DP 26

// digit pin
#define PIN_DIGIT_1   13
#define PIN_DIGIT_10  14
#define PIN_DIGIT_100 15

// digit num
#define SEG_DIGIT_NUM 3

// N_TRANSISTORS
#define SEG_HARDWARE N_TRANSISTORS

typedef enum {
    TYPE_NONE = 0,
    TYPE_MOTOR,
    TYPE_DC_RELAY,
    TYPE_AC_RELAY,
    TYPE_TEM_SENSOR
} mb_device_type_t;

#define DEVICE_VERSION 1

// Indicates whether the device is in auto/manual mode.
// Also, the device can be switched to auto/manual mode remotely.
#define PIN_LED_MODE

// If the device is manual, use the motor toggle switch.
#define PIN_SW_MODE

enum GrepfaCtlCoil {
    COIL_ADDRESS_ON,
    COIL_ADDRESS_DIRECTION,
    COIL_ADDRESS_MAX
};

enum GrepfaCtlRegister {
    REG_ADDRESS_DELTA_TIME,
    REG_ADDRESS_MAX
};

class GrepfaController {
    SevSeg seg;

    uint8_t digits[3] = {PIN_DIGIT_1, PIN_DIGIT_10, PIN_DIGIT_100};
    uint8_t segs[8] = {
            PIN_SEGMENT_A,
            PIN_SEGMENT_B,
            PIN_SEGMENT_C,
            PIN_SEGMENT_D,
            PIN_SEGMENT_E,
            PIN_SEGMENT_F,
            PIN_SEGMENT_G,
            PIN_SEGMENT_DP
    };



    ModbusRTUSlave* slave;

    pin_size_t relayA;
    pin_size_t relayB;

    bool mode = true;

    static void mbTask(void *);
    static void segTask(void*);

    void pollAuto();
    void pollManual();

public:
    void begin(HardwareSerial& serial, pin_size_t A, pin_size_t B);
    void poll();

    void setManual();
};


#endif //UNTITLED_GREPFACONTROLLER_H
