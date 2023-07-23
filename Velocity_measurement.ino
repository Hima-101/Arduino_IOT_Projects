#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define echo A0 //echo pin
#define trigger A1// Trigger pin

#define Recheck A5 // choose the pin for the Recheck button

#define Green 8
#define Red 9
#define buz 10
#define Blue 11

//define variables 
float speed = 0, distance = 0, Time = 0;
int flag1 = 0, flag2 = 0;
int time1, time2;

//other configuration
const unsigned int BEEP_FREQUENCY = 3000;

//define function
void ultrasonicRead();


void setup() {
  pinMode(Recheck, INPUT_PULLUP);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);

  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(buz, OUTPUT);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("PARVAT");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Vehicle  Speed ");
  lcd.setCursor(0,1);
  lcd.print("  Measurement  ");
  delay(2000);
  lcd.clear();

}

void loop() {
  ultrasonicRead();// calls ultrasonic function below;

  if(distance<=30 && flag1==0){// distance in cm.
    digitalWrite(Red, 0);
    digitalWrite(Blue, 1);
    tone(buz, BEEP_FREQUENCY, 600);
    time1 = millis();
    flag1 = 1;
  }
  if(distance<=20 && flag2==0){
    time2 = millis();
    flag2 = 1;
  }

  if(flag1 == 1 && flag2 == 1){
    flag1 = 2; flag2 = 2;

    if(time2 > time1){
     Time = time2 - time1; // running toward system;
    }
    else if(time1>time2){
      Time = time1 - time2;
    }//running away from the system
     
    Time = Time/1000; // convert millisecond to second 
    speed = 10/Time; // v = d/t
    speed = speed*(0.36);// cm/s --> km/hr

    digitalWrite(Red, 0);
    digitalWrite(Blue, 0);
    digitalWrite(Green, 1);// implies speed is calculated and displayed
    
    tone(buz, BEEP_FREQUENCY, 200); //beep when done;
   
  }

  // once speed is calculated and dislayed...

  if(digitalRead(Recheck)==0){
    speed = 0;
    flag1 = 0;
    flag2 =0;
    digitalWrite(Red, 1);
    digitalWrite(Green, 0);
    digitalWrite(Blue, 0);// implies velocity measurement has started again..
    
    tone(buz, BEEP_FREQUENCY, 400);// BEEP when done;
  }
 
 
  lcd.setCursor(0,0);
  lcd.print("Dist. in cm ");
  lcd.print(distance);
  
  lcd.setCursor(0,1);
  lcd.print("Speed km/hr ");
  lcd.print(speed);
  delay(10);// loop repeates in every 10 ms;
}

//creating ultrasonic function...

void ultrasonicRead(){
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);
long time = pulseIn(echo, HIGH);
distance = time / 28.5 / 2; // distance in cm

}



