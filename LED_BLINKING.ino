int temp = 0;
// 4-->blue (else)
// 6-->RED  (10,50)
// 7-->green (50,70)
void setup() 
{
  // put your setup code here, to run once:
   pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
   pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(temp<3){
      digitalWrite(4,HIGH);
      delay(500);
      digitalWrite(4, LOW);
      delay(500);
      }
    else if(temp<6&&temp>=3){
      digitalWrite(7,HIGH);
      delay(500);
      digitalWrite(7, LOW);
      delay(500);
      }
    else{
      digitalWrite(6,HIGH);
      delay(500);
      digitalWrite(6, LOW);
      delay(500); 
    }  
     temp++;
}
