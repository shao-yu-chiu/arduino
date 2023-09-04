int but = 2;
int ledp;
int i = 5;
int p=0;
int i2 = 5;
long late ;
boolean lep = HIGH;
boolean butp =HIGH;
void setup() {
  for (ledp = 3; ledp <= 10; ledp++) {
    pinMode(ledp, OUTPUT);
    digitalWrite(ledp, HIGH);
  }
  pinMode(but, INPUT);
  Serial.begin(9600);
}
void xxx(void) {
  i2 = i;
  i = i - 1;
  if (i<3) {
    i = 10;
  }
  if (digitalRead(i)== HIGH) {
    digitalWrite(i,LOW);
  }
  if (digitalRead(i2)== LOW) {
   digitalWrite(i2,HIGH);
  }
  delay(50);
}
void loop() {
  butp=digitalRead(but);
  if (butp == LOW) {
    late = millis();
    xxx();   
    delay(20);
    while (1) {
     butp=digitalRead(but);
      if (butp == HIGH) {        
        break;
      }
      if (millis()-late > 1000 ) {
         xxx();   
      }
    }
  }
  delay(20);
}
