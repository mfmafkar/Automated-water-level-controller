#define trig 50
#define echo 51
#define red 52
#define green 53
#define yellow 48
#define bulb 13
#define buzzer 22
#include<LiquidCrystal.h>
LiquidCrystal lcd1 (1, 2, 4, 5, 6, 7);
int level, waterLevel;
bool state;
//map(value, fromLow, fromHigh, toLow, toHigh)

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(bulb, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd1.begin(16, 4);
  lcd1.setCursor(0, 0);
  lcd1.print(" Automated Water ");
  lcd1.setCursor(1, 1);
  lcd1.print("Level Indicator");
  delay (2000);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Initializing....");
  delay(2000);
  lcd1.clear();
}

void loop() {
  ultrasonic();

  delay(500);
  lcd1.clear();
}

void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH);

  long cm = t / 29 / 2;


  if (cm >= 0 && cm <= 30) {
    level = map(cm, 0, 30, 100, 0);
    lcd1.print("Water Level ");
    lcd1.print(level);
    lcd1.print(" % ");
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);


    if (level <= 20) {
      digitalWrite(bulb, HIGH);
      digitalWrite(yellow, HIGH);
      lcd1.setCursor(1, 1);
      lcd1.print(" Pump ON ");
      state = true;
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);




    } else if (level < 96 && state == 1) {
      digitalWrite(bulb, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(buzzer, LOW);
      lcd1.setCursor(1, 1);
      lcd1.print(" Pump ON");


    } else {
      digitalWrite(bulb, LOW);
      digitalWrite(yellow, LOW);
      state = false;
      lcd1.setCursor(1, 1);
      lcd1.print(" Pump OFF ");
      if (level == 96) {
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
      }
    }

  } else {
    lcd1.print("LEVEL READ ERROR");
    digitalWrite(green, LOW);
    digitalWrite(bulb, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);

  }
}









