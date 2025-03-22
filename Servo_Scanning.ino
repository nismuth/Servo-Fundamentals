// Scanning Servo

#include <Servo.h>

// Create a Servo object
Servo myServo;

// Define the range of the servo
const int minAngle = 0;   // Minimum angle for the servo
const int maxAngle = 180; // Maximum angle for the servo
const int stepDelay = 20; // Delay between position updates (milliseconds)

void setup() {
  // Attach the servo to pin 9
  myServo.attach(9);
}

void loop() {
  // Sweep the servo from minAngle to maxAngle
  for (int angle = minAngle; angle <= maxAngle; angle++) {
    myServo.write(angle);     // Set the servo position
    delay(stepDelay);         // Wait to create slow movement
  }

  // Sweep the servo from maxAngle back to minAngle
  for (int angle = maxAngle; angle >= minAngle; angle--) {
    myServo.write(angle);     // Set the servo position
    delay(stepDelay);         // Wait to create slow movement
  }
}