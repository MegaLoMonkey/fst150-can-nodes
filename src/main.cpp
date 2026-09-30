/*
 * FST-150 Tyre Temperature and Steering Angle Data System
 *
 * Entry point. Compile-time flags determine which node type is built.
 *
 * Build with:
 *   pio run -e tyre_node_FL      (or FR, RL, RR)
 *   pio run -e steering_node
 */

#include <Arduino.h>

// Phase 0: minimal validation sketch - blink and report node identity over serial
// This confirms the toolchain works end-to-end before adding sensors and CAN.

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("========================================");
    Serial.println("FST-150 Data System - Node starting up");
    Serial.println("========================================");

#ifdef NODE_TYPE_TYRE
    Serial.print("Node type: TYRE, corner ");
    Serial.println(TYRE_CORNER);
#endif

#ifdef NODE_TYPE_STEERING
    Serial.println("Node type: STEERING");
#endif

    Serial.print("CAN TX ID: 0x");
    Serial.println(CAN_TX_ID, HEX);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    Serial.println("Alive");
}
