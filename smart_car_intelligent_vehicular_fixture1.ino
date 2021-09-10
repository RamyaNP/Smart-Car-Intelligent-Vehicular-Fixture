int gas = 0;
int Light = 0;
int DistanceBack = 0;
int distanceThreshBack = 0;
int BaseTemp = 0;
int TempMeasure = 0;
int Force = 0;
int DistanceSide = 0;
int DistanceThreshSide = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  gas = analogRead(A0);
  Serial.print("gas");
  delay(100); // Wait for 100 millisecond(s)
  if (gas > 500) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  Light = analogRead(A1);
  if (Light > 700) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }

  distanceThreshBack = 320;
  DistanceBack = 0.01723 * readUltrasonicDistance(2, 3);
  Serial.print(" distance");
  if (DistanceBack > distanceThreshBack) {
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  }
  if (DistanceBack <= distanceThreshBack) {
    digitalWrite(7, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  }
  if (DistanceBack <= distanceThreshBack - 100) {
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
  }
  if (DistanceBack <= distanceThreshBack - 250) {
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
  }
  if (DistanceBack <= distanceThreshBack - 350) {
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(100); // Wait for 100 millisecond(s)

  BaseTemp = 40;
  TempMeasure = map(((analogRead(A2) - 20) * 3), 0, 1023, -40, 125);
  Serial.print(TempMeasure);
  Serial.println(" C");
  if (TempMeasure < BaseTemp) {
    analogWrite(11, 51);
    analogWrite(10, 204);
    analogWrite(9, 255);
  }
  if (TempMeasure >= BaseTemp && TempMeasure < BaseTemp + 30) {
    analogWrite(11, 51);
    analogWrite(10, 255);
    analogWrite(9, 51);
  }
  if (TempMeasure >= BaseTemp + 30 && TempMeasure < BaseTemp + 60) {
    analogWrite(11, 255);
    analogWrite(10, 255);
    analogWrite(9, 0);
  }
  if (TempMeasure >= BaseTemp + 60 && TempMeasure < BaseTemp + 70) {
    analogWrite(11, 255);
    analogWrite(10, 153);
    analogWrite(9, 0);
  }
  if (TempMeasure >= BaseTemp + 70) {
    analogWrite(11, 255);
    analogWrite(10, 0);
    analogWrite(9, 0);
  }
  delay(100); // Wait for 100 millisecond(s)

  DistanceThreshSide = 100;
  DistanceSide = 0.01723 * readUltrasonicDistance(6, 6);
  if (DistanceSide < DistanceThreshSide) {
    tone(8, 92, 1000); // play tone 30 (F#2 = 92 Hz)
  }
  delay(100); // Wait for 100 millisecond(s)
}