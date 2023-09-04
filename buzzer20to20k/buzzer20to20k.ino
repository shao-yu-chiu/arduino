int buzzer=14;
void setup() {
 pinMode(buzzer,OUTPUT);
 Serial.begin(9600);
}

void loop() {
 for(int freq=20;freq<=20000;freq+=100){
  tone(buzzer,freq);
  delay(100);
  Serial.println(freq);
  }
}
