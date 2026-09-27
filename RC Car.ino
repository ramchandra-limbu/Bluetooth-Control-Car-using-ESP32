#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Motor A - Left motor
#define IN1 26
#define IN2 27
#define ENA 14

// Motor B - Right motor
#define IN3 25
#define IN4 33
#define ENB 32

int speedValue = 200;  // Speed: 0-255

void setup() {
  Serial.begin(115200);

  // Start Bluetooth
  SerialBT.begin("ESP32_CAR");

  Serial.println("Bluetooth started!");
  Serial.println("Connect to ESP32_CAR");

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopCar();
}

void loop() {

  if (SerialBT.available()) {

    char command = SerialBT.read();

    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {

      case 'F':
      case 'f':
        forward();
        break;

      case 'B':
      case 'b':
        backward();
        break;

      case 'L':
      case 'l':
        left();
        break;

      case 'R':
      case 'r':
        right();
        break;

      case 'S':
      case 's':
        stopCar();
        break;

      // Speed control
      case '1':
        speedValue = 100;
        break;

      case '2':
        speedValue = 150;
        break;

      case '3':
        speedValue = 200;
        break;

      case '4':
        speedValue = 255;
        break;
    }
  }
}

// ---------------- MOTOR FUNCTIONS ----------------

void forward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void backward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void left() {

  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void right() {

  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

