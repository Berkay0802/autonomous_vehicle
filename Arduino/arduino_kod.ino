// This uses Serial Monitor to display Range Finder distance readings
// Include NewPing Library
#include "NewPing.h"
// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9 //Ultrasonik sensörün trig pini Arduino'nun 9.pinine tanımlandı.
#define ECHO_PIN 10  //Ultrasonik sensörün echo pini Arduino'nun 10.pinine
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  
// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float duration=0, distance=0;

const int MotorLE = 11;
const int MotorRE = 3;
const int MotorR1 = 7;
const int MotorR2 = 2;
const int MotorL1 = 12;
const int MotorL2 = 13;

//Sensor Connection
  const int left_sensor_pin =4;//sol sensör 0
  const int right_sensor_pin =8;//sağ sensör 1
// Sensor State
  int left_sensor_state;
  int right_sensor_state;

void setup()
{
pinMode(MotorLE, OUTPUT); //Enable_A
pinMode(MotorRE, OUTPUT); //Enable_B
pinMode(MotorR1, OUTPUT); //inputB1
pinMode(MotorR2, OUTPUT); //inputB2
pinMode(MotorL1, OUTPUT); //inputA1
pinMode(MotorL2, OUTPUT); //inputA2
pinMode(TRIGGER_PIN, OUTPUT); //trıgger
pinMode(ECHO_PIN, INPUT); //echo

pinMode(left_sensor_pin,  INPUT); // initialize Left sensor as an input
pinMode(right_sensor_pin, INPUT); // initialize Right sensor as an input

pinMode(13,OUTPUT);
Serial.begin(9600);

}
void loop()
{ 
 // distance = sonar.ping_cm();
  duration = sonar.ping();
  distance = (duration / 2) * 0.0343;
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance= duration*0.034/2;
  if (distance >= 400 || distance <= 2) 
  {
    Serial.println("Out of range");
  }
  else{
    while(distance==0 ||distance>30){
  distance = sonar.ping_cm();//mesafe cm
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
    if(data=="Sag"){
        sag();
        delay(350);
    }
    else if(data=="Sol"){
        sol();
        delay(350);
        break;
    }
    else if(data=="ileri"){
        ileri();
        delay(150);
    }
    else if(data=="Geri"){
        geri();
        delay(150);
    }

else{
 left_sensor_state = digitalRead(left_sensor_pin);
 right_sensor_state = digitalRead(right_sensor_pin);
 //Serial.println(right_sensor_state);
//beyazda sıfır siyahta 1 olur
 if(right_sensor_state==1 && left_sensor_state==1) {
  distance = sonar.ping_cm();//mesafe cm
//  if(distance<=20){
//   dur();
//   delay(150);
//}
  ileri(); //FORWARD
}
 else if(right_sensor_state==0 && left_sensor_state==1) {
  sag(); //Move Right

 }
 
 else if(right_sensor_state==1 && left_sensor_state==0) {
  sol(); //Move Left
}
 
 else if(right_sensor_state==0 && left_sensor_state==0) {
  dur(); //STOP
 }
 Serial.println(distance);
 distance = sonar.ping_cm();//mesafe cm
}
distance = sonar.ping_cm();//mesafe cm
}

  dur();  //  dur
  delay(150);
Serial.println(distance);
}
  }
  

void geri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 100); // Sağ motorun hızı 150
  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 100); // Sol motorun hızı 150
  
  
}
void sol(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // SOL motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // SOL motorun geri hareketi pasif
  analogWrite(MotorRE, 200); // SOL motorun hızı 0 (Motor GERİ)
  digitalWrite(MotorL1, LOW); // SAĞ motorun ileri hareketi aktif
  digitalWrite(MotorL2, HIGH); // SAĞ motorun geri hareketi pasif
  analogWrite(MotorLE, 250); // SAĞ motorun hızı 150
 
}
void sag(){ // Robotun sola dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, LOW); // SOL motorun ileri hareketi aktif
  digitalWrite(MotorR2, HIGH); // SOL motorun geri hareketi pasif
  analogWrite(MotorRE, 250); // SOL motorun hızı 150  
  digitalWrite(MotorL1, HIGH); // SAĞ motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // SAĞ motorun geri hareketi pasif
  analogWrite(MotorLE, 200); // SAĞ motorun hızı 0 (Motor GERİ)
 
}
void ileri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.
  distance = sonar.ping_cm();//mesafe cm
 //   if(distance<=35){
  // dur();
  // delay(150);
 
// }
  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 75); // Sağ motorun hızı 150
  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 75); // Sol motorun hızı 150
  
}


void dur(){ // Robotun sola dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi pasif
  analogWrite(MotorLE, 0); // Sol motorun hızı 150  
  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi pasif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (Motor duruyor)
}
