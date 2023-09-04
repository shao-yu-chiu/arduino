int buttonPin=2,ledPin=8;
unsigned long lasttime;
//boolean buttonState;
//boolean ledState=HIGH;
void setup() {
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
}

void loop() {
if(digitalRead(buttonPin)==LOW){
  digitalWrite(ledPin,!digitalRead(ledPin));
  lasttime=millis();
  delay(20);
  while(1){
    if(digitalRead(buttonPin)==HIGH) break;
    if(millis()-lasttime>1000){
    digitalWrite(ledPin,!digitalRead(ledPin));
    delay(50);
    }
    }
     delay(20);
}
}
