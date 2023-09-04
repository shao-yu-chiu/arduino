int led1=8;
int led2=9;
int led3=10;
int led4=11;
int delaytime =500;
void setup() {
  // put your setup code here, to run once:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
Serial.begin(9600);
}

void loop() {
if (Serial.available()){
  delaytime=Serial.parseInt();
  Serial.print("Delaytime is ");
  Serial.print(delaytime);
  Serial.println("ms");
  }
digitalWrite(led1,LOW);
delay(delaytime);
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
delay(delaytime);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
delay(delaytime);
digitalWrite(led3,HIGH);
digitalWrite(led4,LOW);
delay(delaytime);
digitalWrite(led4,HIGH);
}
