int buzzer=14;
void setup() {
 pinMode(buzzer,OUTPUT);
}
void bird(void){
  for(int freq=8000;freq>=600;freq-=100){
    tone(buzzer,freq);
    delay(1);
    }
    noTone(buzzer);
  }
void loop() {
 bird();
 delay(1);
 bird();
 delay(1);
}
