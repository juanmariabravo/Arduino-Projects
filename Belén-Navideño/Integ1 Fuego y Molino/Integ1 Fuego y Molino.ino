// Integración 1: fuego parpadeante y molino giratorio

#include <Stepper.h>

const uint8_t FIRE_LED_1 = 3;
const uint8_t FIRE_LED_2 = 5;
const uint8_t FIRE_LED_3 = 6;

const int MOTOR_STEPS_PER_REV = 2048;
Stepper motorMolino(MOTOR_STEPS_PER_REV, 8, 10, 9, 11);

uint32_t fireLastUpdate = 0;
uint32_t motorLastStep = 0;

void setup() {
  pinMode(FIRE_LED_1, OUTPUT);
  pinMode(FIRE_LED_2, OUTPUT);
  pinMode(FIRE_LED_3, OUTPUT);
  motorMolino.setSpeed(4);
}

void loop() {
  uint32_t now = millis();

  // El fuego se actualiza cada 50 ms, sin bloquear el bucle.
  if ((uint32_t)(now - fireLastUpdate) >= 50) {
    fireLastUpdate = now;
    analogWrite(FIRE_LED_1, random(100, 255));
    analogWrite(FIRE_LED_2, random(40, 150));
    analogWrite(FIRE_LED_3, random(120, 255));
  }

  // El motor avanza un paso cada 5 ms.
  int motorInterval = 5;
  if ((uint32_t)(now - motorLastStep) >= (uint32_t)motorInterval) {
    motorLastStep = now;
    motorMolino.step(1);
  }
}
