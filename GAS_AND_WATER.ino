#include<LiquidCrystal.h>
#define echo 9
#define trigger 10
#define waterValve 11
#define gasValve 12
#define gasSensor 8
long duration;
int distance;
int gasleak;
int percentageDistance;
const int buzzer = 13;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {

  lcd.begin(20, 4);
  lcd.clear();

  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(gasValve, OUTPUT);
  pinMode(waterValve , OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(trigger, LOW);
  digitalWrite(gasValve, LOW);
  digitalWrite(waterValve, LOW);

  lcd.setCursor(6, 0);
  lcd.print("GROUP : 5");
  lcd.setCursor(2, 1);
  lcd.print("GAS LEAKAGE AND");
  lcd.setCursor(5, 2);
  lcd.print("WATER LEVEL ");
  lcd.setCursor(2, 3);
  lcd.print("DETECTION SYSTEM");
  delay(2000);
  lcd.clear();
}

void loop() {
  // ultrasonic reading
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.017;
  percentageDistance = map(distance, 0, 1024, 0, 100);
  // gas leakage reading
  gasleak = digitalRead(gasSensor);

  //call functions
  cond1();
  cond2();
  cond3();
  cond4();

  water();
  gas();
  delay(500);
}

void water() {
  if (percentageDistance < 70) {
    digitalWrite(waterValve, HIGH);
  }
  else
  { 
    digitalWrite(waterValve, LOW);
  }
}

void gas() {
  if (gasleak == HIGH) {
    digitalWrite(gasValve, LOW);
  }
  else
  { 
    digitalWrite(gasValve, HIGH);
  }
}

void cond1() {
  if (percentageDistance > 70 && gasleak == HIGH)
    displayAlloff();
}
void cond2()
{
  if (percentageDistance < 70 && gasleak == LOW)
    displayAllon();
}
void cond3() {
  if (percentageDistance < 70 && gasleak == HIGH)
    displayWon();
}
void cond4() {
  if (percentageDistance > 70 && gasleak == LOW)
    displayGon();
}
void displayAlloff() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water= ");
  lcd.print( percentageDistance);
  lcd.print("%");
  lcd.setCursor(11, 0);
  lcd.print("Gas Lk= ");
  lcd.print( gasleak);
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("W-VALVE STATUS");
  lcd.print ("  OFF");
  lcd.setCursor(0, 3);
  lcd.print("G-VALVE STATUS ");
  lcd.print ("  OFF");
}

void displayAllon() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water= ");
  lcd.print( percentageDistance);
  lcd.print("%");
  lcd.setCursor(11, 0);
  lcd.print("Gas Lk= ");
  lcd.print( gasleak);
  noTone(buzzer);
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("W-VALVE STATUS");
  lcd.print ("  ON");
  lcd.setCursor(0, 3);
  lcd.print("G-VALVE STATUS ");
  lcd.print ("  ON");
}
void displayWon() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water= ");
  lcd.print( percentageDistance);
  lcd.print("%");
  lcd.setCursor(11, 0);
  lcd.print("Gas Lk= ");
  lcd.print( gasleak);

  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  delay(1000);

  lcd.setCursor(0, 2);
  lcd.print("W-VALVE STATUS");
  lcd.print ("  ON");
  lcd.setCursor(0, 3);
  lcd.print("G-VALVE STATUS ");
  lcd.print ("  OFF");
}
void displayGon() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water= ");
  lcd.print( percentageDistance);
  lcd.print("%");
  lcd.setCursor(11, 0);
  lcd.print("Gas Lk= ");
  lcd.print( gasleak);
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("W-VALVE STATUS");
  lcd.print ("  OFF");
  lcd.setCursor(0, 3);
  lcd.print("G-VALVE STATUS ");
  lcd.print ("  ON");
}
