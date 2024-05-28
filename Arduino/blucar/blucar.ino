#include <SoftwareSerial.h>
SoftwareSerial HC05(0,1);

#define motor1a 6
#define motor1b 7
#define motor2a 8
#define motor2b 9
#define motor3a 10
#define motor3b 11
#define motor4a 12
#define motor4b 13
#define trig 2
#define echo 3
char control;
bool go = true;

void setup(){
    Serial.begin(9600);
    HC05.begin(9600);
    pinMode(motor1a, OUTPUT);
    pinMode(motor1b, OUTPUT);
    pinMode(motor2a, OUTPUT);
    pinMode(motor2b, OUTPUT);
    pinMode(motor3a, OUTPUT);
    pinMode(motor3b, OUTPUT);
    pinMode(motor4a, OUTPUT);
    pinMode(motor4b, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);       
}
int getDistance(){
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  
  /* Phát xung từ chân trig */
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
  
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  distance = int(duration/2/29.412);
  return distance;
}
void stopm(){
  digitalWrite(motor1a, 0);
  digitalWrite(motor1b, 0);
  digitalWrite(motor2a, 0);
  digitalWrite(motor2b, 0);
  digitalWrite(motor3a, 0);
  digitalWrite(motor3b, 0);
  digitalWrite(motor4a, 0);
  digitalWrite(motor4b, 0);
}
void goAhead(){
  digitalWrite(motor1a, 1);
  digitalWrite(motor1b, 0); //1
  digitalWrite(motor2a, 1); //1
  digitalWrite(motor2b, 0);
  digitalWrite(motor3a, 0);
  digitalWrite(motor3b, 1);//1
  digitalWrite(motor4a, 1);
  digitalWrite(motor4b, 0);
}
void backward(){
  digitalWrite(motor1a, 0);
  digitalWrite(motor1b, 1);
  digitalWrite(motor2a, 0);
  digitalWrite(motor2b, 1);
  digitalWrite(motor3a, 1);
  digitalWrite(motor3b, 0);
  digitalWrite(motor4a, 0);
  digitalWrite(motor4b, 1);
}
void turnLeft(){
  digitalWrite(motor1a, 1);
  digitalWrite(motor1b, 0); //1
  digitalWrite(motor2a, 1); //1
  digitalWrite(motor2b, 0);
  digitalWrite(motor3a, 1);
  digitalWrite(motor3b, 0);
  digitalWrite(motor4a, 0);
  digitalWrite(motor4b, 1);
}
void turnRight(){
  digitalWrite(motor1a, 0);
  digitalWrite(motor1b, 1);
  digitalWrite(motor2a, 0);
  digitalWrite(motor2b, 1);
  digitalWrite(motor3a, 0);
  digitalWrite(motor3b, 1);//1
  digitalWrite(motor4a, 1);
  digitalWrite(motor4b, 0);
}
void slipLeft(){
  digitalWrite(motor1a, 1);
  digitalWrite(motor1b, 0); //1
  digitalWrite(motor2a, 0); //1
  digitalWrite(motor2b, 1);
  digitalWrite(motor3a, 0);
  digitalWrite(motor3b, 1);//1
  digitalWrite(motor4a, 0);
  digitalWrite(motor4b, 1);
  
}
void slipRight(){
  digitalWrite(motor1a, 0);
  digitalWrite(motor1b, 1); //1
  digitalWrite(motor2a, 1); //1
  digitalWrite(motor2b, 0);
  digitalWrite(motor3a, 1);
  digitalWrite(motor3b, 0);//1
  digitalWrite(motor4a, 1);
  digitalWrite(motor4b, 0);
}
void loop(){
  if(HC05.available()>0){
    control = HC05.read();
    Serial.println(control);
    Serial.println(go);
    switch(control){
      case 'F':
        if(go)
          goAhead();
        else
          stopm();
        if(getDistance() <= 10){
          go = false;
        }else{
          go = true;
        }
        break;
      case 'B':
        backward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'G':
        slipLeft();
        break;
      case 'I':
        slipRight();
        break;
      case 'S':
        stopm();
        break;
     }  
  }
}
