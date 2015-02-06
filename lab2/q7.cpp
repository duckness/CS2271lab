#include <avr/io.h> 
#include <Arduino.h>

#define SWITCH_POT      2
#define SWITCH_TOUCH    3
#define LED_POT         6
#define LED_TOUCH       7

void setup () {
    pinMode(SWITCH_POT, INPUT); 
    pinMode(SWITCH_TOUCH, INPUT); 
    pinMode(LED_POT, OUTPUT);
    pinMode(LED_TOUCH, OUTPUT); 
}

void flashLedTouch (int delayVal) {
    digitalWrite(LED_TOUCH, HIGH); 
    delay(delayVal); 
    digitalWrite(LED_TOUCH, LOW); 
    delay(delayVal);
}

int remapPot (int val) {
    return (int)(val * 255.0 / 1023.0); 
}

int remapTouch (int val) {
    return (int)(val  / 1023.0 * (500 - 125) + 125); 
}

void loop () {
    int pot = remapPot(analogRead(0));
    int touch = remapTouch(analogRead(1));

    if (digitalRead(SWITCH_POT)) {
        analogWrite(6, pot); 
    }
    if (digitalRead(SWITCH_TOUCH)) {
        flashLedTouch(touch);
    }
}

int main (void) {
    init();
    setup();
    while (1) {
        loop(); 
        if (serialEventRun) {
            serialEventRun();
        }
    }
    return 0; 
}

