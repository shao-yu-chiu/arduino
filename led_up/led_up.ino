int pin;
int delaytime =500;
int bright=50;
void setup() {
  for(pin=8;pin<=11;pin++){
pinMode(pin,OUTPUT);
pinMode(pin,HIGH);
}
Serial.begin(9600);
}

void loop() {
if (Serial.available()){
  delaytime=Serial.parseInt();
  Serial.print("Delaytime is ");
  Serial.print(delaytime);
  Serial.println("ms");
  }
  for(pin=8;pin<=11;pin++){
analogWrite(pin,bright);
Serial.println(bright);
if(bright>254) bright=bright-255;
else bright=bright+1;
delay(delaytime);
analogWrite(pin,255);
}
}
