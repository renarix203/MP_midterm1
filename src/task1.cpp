#include <Arduino.h>

// program is the same as the one in tinkercad

#define RED 8
#define YELLOW 9
#define GREEN 10

void trafficLight();

// function renamed not to conflict with the setup() function
void task1_setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

// function renamed not to conflict with the loop() function
void task1_loop()
{
  trafficLight();
}

void trafficLight()
{
  // lights end with yellow to smoothly transition to red in the next cycle
  digitalWrite(RED, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(YELLOW, LOW);
}