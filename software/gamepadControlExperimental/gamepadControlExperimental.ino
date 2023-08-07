#include <AccelStepper.h>

#define enPin 8
#define xDirPin 5
#define yDirPin 6
#define zDirPin 7
#define xStepPin 2
#define yStepPin 3
#define zStepPin 4

// Define max speed and acceleration for each stepper in steps/s and steps/s^2
const float maxSpeedX = 5000.0;       //AX1
const float accelerationX = 500.0;   //AX1
const float maxSpeedY = 5000.0;       //AX2
const float accelerationY = 500.0;   //AX2
const float maxSpeedZ = 5000.0;       //AX3
const float accelerationZ = 500.0;   //AX3

// Create instances of AccelStepper for each stepper motor
AccelStepper stepperX(AccelStepper::DRIVER, xStepPin, xDirPin);
AccelStepper stepperY(AccelStepper::DRIVER, yStepPin, yDirPin);
AccelStepper stepperZ(AccelStepper::DRIVER, zStepPin, zDirPin);

void setup() {
  Serial.begin(115200);

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
    int xValue, yValue, zValue;

    sscanf(dataString.c_str(),"%d,%d,%d", &xValue, &yValue, &zValue);

    //xDirection
    float xSpeed = map(xValue, 0, 256, -maxSpeedX, maxSpeedX);
    if (xValue != 128) {
      stepperX.setSpeed(xSpeed);
    }
    else
    {
      stepperX.setSpeed(0);
    }

    //yDirection
    float ySpeed = map(yValue, 0, 256, -maxSpeedY, maxSpeedY);
    if (yValue != 128) {
      stepperY.setSpeed(ySpeed);
    }
    else
    {
      stepperY.setSpeed(0);
    }

    //zDirection
    float zSpeed = map(zValue, 0, 256, -maxSpeedZ, maxSpeedZ);
    if (zValue != 128) {
      stepperZ.setSpeed(zSpeed);
    }
    else
    {
      stepperZ.setSpeed(0);
    }
    stepperX.runSpeed();
    stepperY.runSpeed();
    stepperZ.runSpeed();        

  }

}
