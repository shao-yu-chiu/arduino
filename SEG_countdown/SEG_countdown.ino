int seg[] = {22, 12, 11, 10, 9, 8, 7};
int scan[] = {2, 3, 4, 5};
char TAB[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x00};
int i1, j1;
int t4 = 1;
int t3 = 1;
int t2 = 0;
int t1 = 0;
int reset = 13;
boolean RS;
unsigned long DT;

void setup() {
  for (i1 = 0; i1 < 7; i1++) {
    pinMode(seg[i1], OUTPUT);
  }
  for (i1 = 0; i1 < 4; i1++) {
    pinMode(scan[i1], OUTPUT);
    digitalWrite(scan[i1], LOW);
  }
  pinMode(reset, INPUT);
}

void loop() {
  RS = digitalRead(reset);
  if (RS == LOW) {
    t4 = 1;
    t3 = 1;
    t2 = 0;
    t1 = 0;
  }
  if (t4 == 0 and t3 == 0 and t2 == 0 and t1 == 0) {
    OutPort(TAB[0]);
    digitalWrite(scan[0], HIGH);
    delay(5);
    digitalWrite(scan[0], LOW);

    OutPort(TAB[0]);
    digitalWrite(scan[1], HIGH);
    delay(5);
    digitalWrite(scan[1], LOW);

    OutPort(TAB[0]);
    digitalWrite(scan[2], HIGH);
    delay(5);
    digitalWrite(scan[2], LOW);

    OutPort(TAB[0]);
    digitalWrite(scan[3], HIGH);
    delay(5);
    digitalWrite(scan[3], LOW);
  }
  else {
    if ((millis() - DT) > 100) {
      if (t3 == 0 and t2 == 0 and t1 == 0) {
        t4 = t4 - 1;
        t3=10;
      }
      if (t1 == 0) {
        if (t2 == 0) {
          t2 = 10;
          t3 = t3 - 1;
        }
        t2 = t2 - 1;
      }
      if (t1 == 0) {
        t1 = 10;
      }
      t1 = t1 - 1;
      DT = millis();
    }
    OutPort(TAB[t4]);
    digitalWrite(scan[0], HIGH);
    delay(5);
    digitalWrite(scan[0], LOW);

    OutPort(TAB[t3]);
    digitalWrite(scan[1], HIGH);
    delay(5);
    digitalWrite(scan[1], LOW);

    OutPort(TAB[t2]);
    digitalWrite(scan[2], HIGH);
    delay(5);
    digitalWrite(scan[2], LOW);

    OutPort(TAB[t1]);
    digitalWrite(scan[3], HIGH);
    delay(5);
    digitalWrite(scan[3], LOW);
  }
}

void OutPort(byte dat) {
  for (j1 = 0; j1 < 7; j1++) {
    if (dat % 2 == 1)
      digitalWrite(seg[j1], HIGH);
    else
      digitalWrite(seg[j1], LOW);
    dat = dat / 2;
  }
}
