#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define echo A0
#define trigger A1
#define buz 10
#define green 9
#define red 8
 
float distance = 0;
float time = 0;
 int range = 30;

 const unsigned int BEEP_FREQUENCY = 3000;
 void ultrasonicRead();

void setup() {
  Serial.begin(9600);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buz, OUTPUT);

 lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("PARVAT");
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print(" Vehicle ");
  lcd.setCursor(2,1);
  lcd.print(" Alert System ");
  delay(3000);
  lcd.clear();

}

void loop() {
  ultrasonicRead();
  if(distance<range){
  digitalWrite(red, 1);
  digitalWrite(green, 0);
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(" VEHICLE IS ");
  lcd.setCursor(3,1);
  lcd.print(" PRESENT!! ");
  tone(buz, BEEP_FREQUENCY, 200);


  } // range = fixed obstacle distance
else {
  digitalWrite(red, 0);
  digitalWrite(green, 1);
   lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("VEHICLE IS");
  lcd.setCursor(1,1);
  lcd.print("NOT PRESENT");
  
  
}
  Serial.println("distance  = ");
  Serial.println(distance);
  delay(500);
 }

void ultrasonicRead(){
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(2);
digitalWrite(trigger, LOW);

long time = pulseIn(echo, HIGH);
distance = time / 28.5 / 2;
}
