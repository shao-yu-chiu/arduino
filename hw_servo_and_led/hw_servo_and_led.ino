// 伺服機控制練習：可透過Serial Monitor下達控制位置給伺服機
// 控制的範圍為 500～2500
#include<Servo.h>
Servo myservo;
unsigned lasttime=0;
const byte Servo_pin = 22;  // 伺服機的控制埠 D11
int pos=0;  // 伺服機位置，起始值預設為0 （最右邊）
int led=24;
bool ledstate=1;
int count=0;
void setup() 
{ 
  Serial.begin(9600);          // 啟用串列埠
  myservo.attach(Servo_pin);
  pinMode(led, OUTPUT);  // 設定伺服機的I/O為輸出
  digitalWrite(led,ledstate);
}
void loop() {
  if(millis()-lasttime>=500){
    digitalWrite(led,!ledstate);
    }
  if(millis()-lasttime>=1000){
    lasttime=millis();
    count++;
    
    if(count<30){ 
    pos=pos+6;
     myservo.write(pos);
    }
    else if(count<60){
      pos=pos-6;
     myservo.write(pos);
    }
    else if(count>60) count=0;
  }
      }
    
