#include <AccelStepper.h>
#include <Servo.h>

// Jaw Stepper
#define HALFSTEP 8

#define motorPin1  11     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define motorPin2  10     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define motorPin3  9    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define motorPin4  8    // IN4 on ULN2003 ==> Orange on 28BYJ-48

// Define max speed and acceleration for each stepper in steps/s and steps/s^2
const float maxSpeedJaw = 1000.0;      //Jaw
const float accelerationJaw = 600.0;  //Jaw
const float jawSteps = 1000.0;         //Jaw

// Create instances of AccelStepper for each stepper motor
AccelStepper stepperJaw(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
Servo AX4;
Servo AX5;

void setup() {
  AX4.attach(6);
  AX5.attach(3);
  Serial.begin(115200);
  // Set max speed and acceleration for each stepper
  stepperJaw.setMaxSpeed(maxSpeedJaw);
  stepperJaw.setSpeed(900);
  stepperJaw.setAcceleration(accelerationJaw);
  stepperJaw.setCurrentPosition(0); // set position as zero
  AX4.write(90); //continuous servo is off
  AX5.write(0); //set sg90 current position to zero 
}

void loop() {
  if (Serial.available()) { // Check if data is here
    String dataString = Serial.readStringUntil('\n');
    
    // Read the serial data and parse the numbers
    int biteValue; 
    int ax4Value;
    int ax5Value;
    sscanf(dataString.c_str(),"%d,%d,%d", &biteValue,&ax4Value,&ax5Value);
    
    //Jaw
    if (biteValue == 1) {
      stepperJaw.moveTo(-jawSteps);
    }
    else {
      stepperJaw.moveTo(0);
    }

    //AX4
    if (ax4Value == 0) { //stop
      AX4.write(90);
    }
    if (ax4Value == 1) { //turn positive
      AX4.write(90 - 45/2);
    }
    if (ax4Value == 2) { //turn negative
      AX4.write(90 + 45/2);
    }

    //AX5
    if (ax5Value == 0) { //stop
      AX5.write(0);
    }
    if (ax5Value == 1) { //turn positive
      AX5.write(15);
    }
    if (ax5Value == 2) { //turn negative
      AX5.write(30);
    }
    //send commands       
    stepperJaw.run();
  }

}
