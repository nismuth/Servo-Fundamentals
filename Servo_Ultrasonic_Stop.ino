#include <Servo.h>

// Create servo object
Servo myServo;

// Define Trig and Echo pins.
const int TRIG_PIN = 3;
const int ECHO_PIN = 2;

// Buzzer

// Range of servo
const int minAngle = 0;   // Minimum angle for the servo
const int maxAngle = 180; // Maximum angle for the servo
const int stepDelay = 20; // Delay between position updates (milliseconds)

// Distance threshold
const int stopDistance = 20; // Stop servo if an object is within 20 cm

void setup() {
  // Attach the servo to pin 9
  myServo.attach(9);
  
  // Define inputs and outputs for HC-SR04 sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  int distanceCentimeters = getDistanceCentimeters();

  // Print the distance on the Serial Monitor.
  Serial.print("Distance = ");
  Serial.print(distanceCentimeters);
  Serial.println(" cm");

  // Stop the servo if an object is too close
  if (distanceCentimeters <= stopDistance) {
    Serial.println("Object detected! Stopping servo...");
    return; // Stop executing the loop, keeping the servo at its last position
  }

  // Sweep the servo from minAngle to maxAngle
  for (int angle = minAngle; angle <= maxAngle; angle++) {
    if (getDistanceCentimeters() <= stopDistance) {
      Serial.println("Object detected! Stopping servo...");
      return; // Exit the loop if an object is detected
    }
    myServo.write(angle);
    delay(stepDelay);
  }

  // Sweep the servo from maxAngle back to minAngle
  for (int angle = maxAngle; angle >= minAngle; angle--) {
    if (getDistanceCentimeters() <= stopDistance) {
      Serial.println("Object detected! Stopping servo...");
      return; // Exit the loop if an object is detected
    }
    myServo.write(angle);
    delay(stepDelay);
  }

  delay(50); 
}

// Function to get distance from ultrasonic sensor
int getDistanceCentimeters() {
  // Clear the trigPin by setting it LOW.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds.
  long durationMicroseconds = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters. Speed of sound is roughly 0.034 cm/us.
  int distanceCentimeters = durationMicroseconds * 0.034 / 2;

  return distanceCentimeters;
}
