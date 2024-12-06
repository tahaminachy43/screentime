#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 9;  
const int echoPin = 10; 

float duration, distance; 

Servo myServo; // Create a servo object to control a servo motor

int servoPin = 5; // Define the pin to which the servo is connected

void setup() {
  myServo.attach(servoPin); // Attach the servo on pin 5 to the servo object
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Begin serial communication
  myServo.write(75); // Set initial servo position
  Serial.println("Monitoring distance...");
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2; // Convert to cm
  Serial.print("Distance: ");
  Serial.println(distance);

  int age = 0;

  // Determine the "age" based on the distance
  if (distance >= 1 && distance <= 10) {
    age = 18;
  } else if (distance > 10 && distance <= 20) {
    age = 30;
  } else if (distance > 20 && distance <= 30) {
    age = 50;
  }

  if (age == 18 || age == 30 || age == 50) {
    Serial.print("Detected age: ");
    Serial.println(age);

    int delayTime;
    if (age == 18) {
      delayTime = 30000; // 30 seconds
    } else if (age == 30) {
      delayTime = 20000; // 20 seconds
    } else if (age == 50) {
      delayTime = 10000; // 10 seconds
    }

    // Sweep the servo from 75 to 90 degrees in steps of 1 degree
    for (int angle = 75; angle <= 90; angle++) {
      myServo.write(angle); // Set the servo position
      Serial.print("Angle: ");
      Serial.println(angle);
      delay(150); // Wait for servo to reach the position
    }
    delay(delayTime);

    // Sweep the servo back from 90 to 75 degrees in steps of 1 degree
    for (int angle = 90; angle >= 75; angle--) {
      myServo.write(angle); // Set the servo position
      delay(150); // Wait for servo to reach the position
    }
    delay(1000);

    myServo.write(130); // Move to a final position
    delay(30000);
    myServo.write(70); // Return to the initial position
  } else {
    Serial.println("Out of range. Waiting...");
  }

  delay(500); // Short delay before the next measurement
}


