#include <LiquidCrystal.h>
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int SoilMoistSensor = 9;
int SoilMoistState;

const int TrigPin = A1;
const int EchoPin = A2;

long period, interval;

#define relay 12

void setup() 
{ 
  //setup code
  pinMode(SoilMoistSensor, INPUT);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);
  
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("SMART IRRIGATION");

  delay(2000);
  lcd.clear();
  delay(200);
  
  Serial.begin(9600);
}
 
void loop() { 
  // main code
  /**Ultrasonic Sensor**/
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);  
  period = pulseIn(EchoPin,HIGH);
  interval = period/58.2;
  Serial.print("Ultrasonic Distance: ");
  Serial.println(interval);

  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(interval);
  lcd.print("cm  ");
  
  int SoilMoistState = digitalRead(SoilMoistSensor);
  
  Serial.println(SoilMoistState);
  Serial.println("");


  if(SoilMoistState == 1) 
  {
    lcd.setCursor(0, 1);
    lcd.print("SOIL DRY PUMP ON");

    digitalWrite(relay, LOW);
    
    delay(2000);
  }
  else
  {
    digitalWrite(relay, HIGH);
    
    lcd.setCursor(0, 1);
    lcd.print("SOIL WET PUMPOFF");

    delay(100);
  }
  
  delay(2000);
}