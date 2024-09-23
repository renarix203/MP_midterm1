#include <Arduino.h>

const int RED_LED_PIN = 9;
const int YELLOW_LED_PIN = 10;
const int GREEN_LED_PIN = 11;

const int SW1_PIN = 2;
const int SW2_PIN = 3;
const int SW3_PIN = 4;

int currentPin = RED_LED_PIN;

int redBrightness = 0;
int yellowBrightness = 0;
int greenBrightness = 0;

unsigned long startTime1 = 0;
unsigned long startTime2 = 0;
unsigned long startTime3 = 0;
unsigned long debounceDelay = 20;

void increaseBrightness(int pin);
void decreaseBrightness(int pin);
void switchLed();

void setup() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    pinMode(SW1_PIN, INPUT_PULLUP);
    pinMode(SW2_PIN, INPUT_PULLUP);
    pinMode(SW3_PIN, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop() {
    // check if the button is pressed and debounce
    if (digitalRead(SW1_PIN) == LOW) {
        if (millis() - startTime1 > debounceDelay) {
            startTime1 = millis();
            increaseBrightness(currentPin);
        }
    }
    if (digitalRead(SW2_PIN) == LOW) {
        if (millis() - startTime2 > debounceDelay) {
            startTime2 = millis();
            decreaseBrightness(currentPin);
        }
    }
    if (digitalRead(SW3_PIN) == LOW) {
        // extra delay at led switch to mitigate the effect of multiple button presses
        if (millis() - startTime3 > debounceDelay + 200) {
            startTime3 = millis();
            switchLed();
        }
    }

    analogWrite(RED_LED_PIN, redBrightness);
    analogWrite(YELLOW_LED_PIN, yellowBrightness);
    analogWrite(GREEN_LED_PIN, greenBrightness);
}

void increaseBrightness(int pin) {
    // increase brightness by 1 on the selected pin
    if (pin == RED_LED_PIN) {
        redBrightness = redBrightness + 1;
        if (redBrightness > 255) {
            redBrightness = 255;
        }
    } else if (pin == YELLOW_LED_PIN) {
        yellowBrightness = yellowBrightness + 1;
        if (yellowBrightness > 255) {
            yellowBrightness = 255;
        }
    } else if (pin == GREEN_LED_PIN) {
        greenBrightness = greenBrightness + 1;
        if (greenBrightness > 255) {
            greenBrightness = 255;
        }
    }
}

void decreaseBrightness(int pin) {
    // decrease brightness by 1 on the selected pin
    if (pin == RED_LED_PIN) {
        redBrightness = redBrightness - 1;
        if (redBrightness < 0) {
            redBrightness = 0;
        }
    } else if (pin == YELLOW_LED_PIN) {
        yellowBrightness = yellowBrightness - 1;
        if (yellowBrightness < 0) {
            yellowBrightness = 0;
        }
    } else if (pin == GREEN_LED_PIN) {
        greenBrightness = greenBrightness - 1;
        if (greenBrightness < 0) {
            greenBrightness = 0;
        }
    }
}

void switchLed() {
    // select next led
    currentPin = currentPin + 1;
    if (currentPin > GREEN_LED_PIN) {
        currentPin = RED_LED_PIN;
    }

    // indicate the selected led
    digitalWrite(currentPin, LOW);
    delay(50);
    digitalWrite(currentPin, HIGH);
    delay(50);
    digitalWrite(currentPin, LOW);
}