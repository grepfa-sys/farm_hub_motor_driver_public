#include "config.h"

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <SerialUART.h>
#include <Arduino.h>
#include <SevSeg.h>
#include <GrepfaController.h>


SevSeg seg;

void BTN_ISR_M() {
    static unsigned long lastClickMillis = 0;
    int unsigned long current = millis();

    if (current - lastClickMillis <= DEBOUNCING_INTERVAL_MILLIS) {
        lastClickMillis = current;
        return;
    }
    lastClickMillis = current;
    Serial.printf("hello m\n");
}

void BTN_ISR_P() {
    static unsigned long lastClickMillis = 0;
    int unsigned long current = millis();

    if (current - lastClickMillis <= DEBOUNCING_INTERVAL_MILLIS) {
        lastClickMillis = current;
        return;
    }
    lastClickMillis = current;
    Serial.printf("hello p\n");
}

void BTN_ISR_N() {
    static unsigned long lastClickMillis = 0;
    int unsigned long current = millis();

    if (current - lastClickMillis <= DEBOUNCING_INTERVAL_MILLIS) {
        lastClickMillis = current;
        return;
    }
    lastClickMillis = current;
    Serial.printf("hello n\n");
}

void setup() {
    Serial.begin();
    Serial.printf("test start\n");

    attachInterrupt(digitalPinToInterrupt(PIN_BTN_M), BTN_ISR_M, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_P), BTN_ISR_P, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_N), BTN_ISR_N, FALLING);

    delay(200);

    Serial2.setTX(8);
    Serial2.setRX(9);

    GrepfaController ctr{};
    ctr.begin((HardwareSerial&)Serial2, PIN_RELAY_A, PIN_RELAY_B);

    while (1) {
    }
}

void loop() {}
//void setup1() {}
//void loop1() {}