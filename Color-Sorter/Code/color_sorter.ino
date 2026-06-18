#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int colour = 0;
boolean GATE_FLG = 0;

void setup() {

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);

  Serial.begin(9600);
}

void loop() {

  colour = readColor();

  delay(10);

  switch (colour) {

    case 1:
      bottomServo.write(30);
      GATE_FLG = 1;
      break;

    case 2:
      bottomServo.write(70);
      GATE_FLG = 1;
      break;

    case 3:
      bottomServo.write(115);
      GATE_FLG = 1;
      break;

    case 4:
      bottomServo.write(160);
      GATE_FLG = 1;
      break;

    case 0:
      break;
  }

  colour = 0;

  if (GATE_FLG) {

    delay(200);

    topServo.write(0);

    delay(280);

    topServo.write(90);

    delay(1000);

    GATE_FLG = 0;
  }
}

int readColor() {

  // RED
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;

  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print(" ");

  delay(50);

  // GREEN
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;

  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print(" ");

  delay(50);

  // BLUE
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;

  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println(" ");

  delay(50);

  // RED
  if ((R > 16 && R < 19) &&
      (G > 55 && G < 58) &&
      (B > 52 && B < 55)) {

    colour = 1;
    Serial.println(" RED ");
  }

  // GREEN
  if ((R > 31 && R < 45) &&
      (G > 38 && G < 40) &&
      (B > 51 && B < 58)) {

    colour = 2;
    Serial.println(" GREEN ");
  }

  // YELLOW
  if ((R > 12 && R < 14) &&
      (G > 20 && G < 21) &&
      (B > 34 && B < 36)) {

    colour = 3;
    Serial.println(" YELLOW ");
  }

  // BLUE
  if ((R > 40 && R < 43) &&
      (G > 50 && G < 54) &&
      (B > 38 && B < 42)) {

    colour = 4;
    Serial.println(" BLUE ");
  }

  return colour;
}