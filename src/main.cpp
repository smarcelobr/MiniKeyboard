#include <Arduino.h>
#include <Keyboard.h>

constexpr uint8_t LED_PIN = LED_BUILTIN;
constexpr unsigned long BLINK_INTERVAL_MS = 500;

// Estado e temporização não bloqueante
static bool ledState = false;
static unsigned long ledLastToggle = 0;
static unsigned long lastPrint = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // garante estado inicial

    // configura entradas do teclado físico como Pull up:
    for (int i = 2; i <= 12; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    //Serial.begin(115200);

    // inicia a biblioteca keyboard
    Keyboard.begin();

}

void loop() {
    unsigned long now = millis();
    if (now - ledLastToggle >= BLINK_INTERVAL_MS) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        ledLastToggle = now;
    }

    for (int i = 2; i <= 12; i++) {
        if (digitalRead(i) == LOW) {
            //Send the message
            if (now<lastPrint || now - lastPrint >= 100) {
                Keyboard.print(i);
                Keyboard.print('-');
                lastPrint = now;
            }
        }
    }
}
