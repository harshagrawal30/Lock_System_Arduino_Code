
//M2M Communication based 2-Factor Authenticated Locking System
#include <Servo.h>
#include <LiquidCrystal.h>
#define echoPin 2
#define trigPin 3
long duration;
int distance;

String dicid;
String pwd;
String id = "adgsdfgsgdsghew";
String otpp = "";
int sled1 = 12;
int sled2 = 13;
bool isObjectFind = false;
Servo myservo;
const int rs = 11, en = 10, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(10);
  pinMode(sled1, 1);
  pinMode(sled2, 1);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin condition
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("This is an authe");
  lcd.setCursor(0, 1);
  lcd.print("nticated doorway");
  digitalWrite(sled1, 0);
  digitalWrite(sled2,0);
  while (Serial.available() == 0) {
    loopSensing();
  }
  if (Serial.readStringUntil('\n') == "giveid") {
    Serial.println(id);
  }
  else{
    Serial.println("error");
  }
  while (Serial.available() == 0) {
    loopSensing();
  }
  if (Serial.readStringUntil('\n') == "generateOtp") {
    otp();
    check();
  }
  else{
    Serial.println("error");
  }
}

void otp() {
  long randomNum = random(100000,999999);
  String number = (String)randomNum;
  otpp = number;
  Serial.println(otpp);

}
void check() {
  while (Serial.available() == 0) {
    loopSensing();
  }

  pwd = Serial.readStringUntil('\n');

  if (pwd != "giveid" and pwd.length() == 6) {
    if (pwd == otpp ) {
      Serial.println("unlocked");
      myservo.write(100);
      digitalWrite(sled2, 0);
      digitalWrite(sled1, 1);
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Welcome! The Gat");
      lcd.setCursor(0, 1);
      lcd.print("eway is opened");
      unsigned long counter = 0;
      bool isLockSignal = true;
      
      while (Serial.available() == 0) {
        loopSensing();
        counter += 1;
        delay(1000);
        if (counter >= 10) {
          lock();
          isLockSignal = false;
          break;
        }
      };
      if (isLockSignal) {
        if (Serial.readStringUntil('\n') == "lockAgain") {
          lock();
        }
        else{
          Serial.println("error");
        }
      }
    }
    if (pwd != otpp ) {
      Serial.println("unmatched otp");
      myservo.write(10);
      digitalWrite(sled1, 0);
    }
  }
  else{
    Serial.println("error");
  }
}
void lock() {
  Serial.println("Locked Again");
  myservo.write(10);
  digitalWrite(sled1, 0);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Thank you! The G");
  lcd.setCursor(0, 1);
  lcd.print("ateway is closed");
  delay(5000);
}

void loopSensing() {
  if(Serial.available())return;
  digitalWrite(trigPin, LOW);
  if(Serial.available())return;
  delayMicroseconds(2);
  if(Serial.available())return;
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  if(Serial.available())return;
  delayMicroseconds(10);
  if(Serial.available())return;
  digitalWrite(trigPin, LOW);
  if(Serial.available())return;
  // Reads the echoPin, returns the sound wave travel time in microseconds

  duration = pulseIn(echoPin, HIGH);
  if(Serial.available())return;
  distance = duration * 0.034 / 2;
  if(Serial.available())return;
  if (distance <= 100 and isObjectFind == false) {
    if(Serial.available())return;
    isObjectFind = true;
    if(Serial.available())return;
    objectDetected();
    if(Serial.available())return;
  }
  else if (distance > 100 and isObjectFind == true) {
    if(Serial.available())return;
    isObjectFind = false;
    if(Serial.available())return;
    lcd.begin(16, 2);
    if(Serial.available())return;
    lcd.setCursor(0, 0);
    if(Serial.available())return;
    lcd.print("This is an authe");
    if(Serial.available())return;
    lcd.setCursor(0, 1);
    if(Serial.available())return;
    lcd.print("nticated doorway");
    if(Serial.available())return;
    digitalWrite(sled2, 0);
    if(Serial.available())return;
  }
}

void objectDetected() {
if(Serial.available())return;
  digitalWrite(sled2, 1);
if(Serial.available())return;
  lcd.begin(16, 2);
  if(Serial.available())return;
  lcd.setCursor(0, 0);
  if(Serial.available())return;
  lcd.print("Use Mobile App t");
  if(Serial.available())return;
  lcd.setCursor(0, 1);
  if(Serial.available())return;
  lcd.print("o unlock Gateway");
  if(Serial.available())return;
}
