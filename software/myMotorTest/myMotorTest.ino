/**
 * JoKauda Robotic Arm Controller with AccelStepper Library
 *
 * This Arduino sketch controls three stepper motors along the X, Y, and Z axes using the AccelStepper library.
 * The stepper motors can move in both positive and negative directions based on the data received from the Serial communication.
 *
 * Date: 7/31/2023
 * Author: Jonathan Ilagan
 */
#include <AccelStepper.h>

#define enPin 8
#define xDirPin 5
#define yDirPin 6
#define zDirPin 7
#define xStepPin 2
#define yStepPin 3
#define zStepPin 4
#define steps 2000

// Define max speed and acceleration for each stepper
const float maxSpeedX = 5000.0;
const float accelerationX = 1000.0;
const float maxSpeedY = 1000.0;
const float accelerationY = 5000.0;
const float maxSpeedZ = 5000.0;
const float accelerationZ = 5000.0;

AccelStepper stepperX(AccelStepper::DRIVER, xStepPin, xDirPin);
AccelStepper stepperY(AccelStepper::DRIVER, yStepPin, yDirPin);
AccelStepper stepperZ(AccelStepper::DRIVER, zStepPin, zDirPin);

void setup() {
  Serial.begin(9600);
  stepperX.setMaxSpeed(maxSpeedX);
  stepperX.setAcceleration(accelerationX);
  stepperY.setMaxSpeed(maxSpeedY);
  stepperY.setAcceleration(accelerationY);
  stepperZ.setMaxSpeed(maxSpeedZ);
  stepperZ.setAcceleration(accelerationZ);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();

    switch (data) {
      case 'a':
        stepperX.move(steps);
        stepperX.runToPosition();
        break;
      case 's':
        stepperY.move(steps);
        stepperY.runToPosition();
        break;
      case 'd':
        stepperZ.move(steps);
        stepperZ.runToPosition();
        break;
      case 'z':
        stepperX.move(-steps);
        stepperX.runToPosition();
        break;
      case 'x':
        stepperY.move(-steps);
        stepperY.runToPosition();
        break;
      case 'c':
        stepperZ.move(-steps);
        stepperZ.runToPosition();
        break;
    }
  }
}
