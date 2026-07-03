#include <Servo.h>

Servo gateServo;

// Motor Driver Pins
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// Buzzer & LED
const int buzzer = 12;
const int led = 13;

// Switch
const int button = 2;

void setup()
{
  Serial.begin(9600);

  gateServo.attach(6);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  // Everything OFF initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);

  gateServo.write(0);

  Serial.println("System Ready");
  Serial.println("Press Switch to Start");
}

void loop()
{
  // Wait for button press
  if (digitalRead(button) == HIGH)
  {
    return;
  }

  delay(200); // debounce

  Serial.println("Machine Started");

  // LED ON
  digitalWrite(led, HIGH);

  // Start buzzer
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);

  

  // 160 RPM Motor (Shredder)
  Serial.println("Shredder Running");

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(10000);

  digitalWrite(IN3, LOW);
  digitalWrite(IN3, LOW);

  delay(1000);
  // Open additive gate
  gateServo.write(90);
  delay(2000);

  // Close additive gate
  gateServo.write(0);
  delay(2000);

  // TT Motor (Mixer)
  Serial.println("Mixer Running");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  delay(10000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  delay(1000);

  // Completion buzzer
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);

  // LED OFF
  digitalWrite(led, LOW);

  Serial.println("Cycle Complete");
  Serial.println("Press Switch Again");

  // Wait until switch released
  while (digitalRead(button) == LOW)
  {
    delay(10);
  }
}