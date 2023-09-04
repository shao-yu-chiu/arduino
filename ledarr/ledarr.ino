int pin[]={8,9,10,11};
int delaytime =500;
void setup() {
  for(int i=0;i<=3;i++){
pinMode(pin[i],OUTPUT);
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
  for(int i=0;i<=3;i++){
digitalWrite(pin[i],LOW);
delay(delaytime);
digitalWrite(pin[i],HIGH);
}
}
