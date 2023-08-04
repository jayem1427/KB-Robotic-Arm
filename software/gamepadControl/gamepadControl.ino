#include <AccelStepper.h>
#include <MultiStepper.h>

#define enPin 8
#define xDirPin 5
#define yDirPin 6
#define zDirPin 7
#define xStepPin 2
#define yStepPin 3
#define zStepPin 4

// Define max speed and acceleration for each stepper in steps/s and steps/s^2
const float maxSpeedX = 5000.0;
const float accelerationX = 1000.0;
const float maxSpeedY = 1000.0;
const float accelerationY = 5000.0;
const float maxSpeedZ = 5000.0;
const float accelerationZ = 5000.0;
const float maxDeltaX = 1000.0;

// Create instances of AccelStepper for each stepper motor
AccelStepper stepperX(AccelStepper::DRIVER, xStepPin, xDirPin);
AccelStepper stepperY(AccelStepper::DRIVER, yStepPin, yDirPin);
AccelStepper stepperZ(AccelStepper::DRIVER, zStepPin, zDirPin);

void setup() {
  Serial.begin(9600);

  // Set max speed and acceleration for each stepper
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
  if (Serial.available()) { // Check if data is here
    String dataString = Serial.readStringUntil('\n');
    
    // Read the serial data and parse the numbers
    int xValue = Serial.parseInt();
    int yValue = Serial.parseInt();
    Serial.read(); // Read and discard the newline character

    //xDirection
    float xSpeed = map(xValue, 0, 256, -maxSpeedX, maxSpeedX);
    if (xValue != 128) {
      stepperX.setSpeed(xSpeed);
      stepperX.runSpeed();
    }
    else
    {
      stepperX.setSpeed(0);
    }
    //yDirection
    float ySpeed = map(yValue, 0, 256, -maxSpeedY, maxSpeedY);
    if (yValue != 128) {
      stepperY.setSpeed(ySpeed);
      stepperY.runSpeed();
    }
    else
    {
      stepperY.setSpeed(0);
    }
    //zDirection
    float zSpeed = map(yValue, 0, 256, -maxSpeedZ, maxSpeedZ);
    if (yValue != 128) {
      stepperZ.setSpeed(zSpeed);
      stepperZ.runSpeed();
    }
    else
    {
      stepperZ.setSpeed(0);
    }        
  }
}
