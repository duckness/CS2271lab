#include <avr/io.h> 
#include <Arduino.h>

#define ISR_SWITCH_POT      0
#define ISR_SWITCH_TOUCH    1
#define LED_POT             6
#define LED_TOUCH           7

unsigned char flagPot = 0;
unsigned char flagTouch = 0;

unsigned char toggleFlag (unsigned char flag) {
    return !flag;
}

void int0ISR () {
    toggleFlag(flagPot);
}

void int1ISR () {
    toggleFlag(flagTouch);
}

void setup () {
    attachInterrupt(ISR_SWITCH_POT, int0ISR, RISING);
    attachInterrupt(ISR_SWITCH_TOUCH, int1ISR, RISING);
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
    return (int)(val  / 1023.0 * (500 - 125) + 125.0); 
}

void loop () {
    int pot = remapPot(analogRead(0));
    int touch = remapTouch(analogRead(1));

    if (flagPot) {
        analogWrite(6, pot); 
    }
    if (flagTouch) {
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

