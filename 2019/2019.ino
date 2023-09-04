int seg7[] = {18,17,16,15,9,8,7};
char TAB[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
int com[] = {6,5,4,3};
int a[] = {8,8,8,8};
int delaytime = 1;
void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(seg7[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(com[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    OutPort(a[i]);
    digitalWrite(com[i], HIGH);
    delay(delaytime);
    digitalWrite(com[i], LOW);
  }
  if (millis() - delaytime > 100) {
    if (a[1] == 0 && a[2] == 0 && a[3] == 0) {
      a[0] = a[0] - 1;
    }
    else if (a[2] == 0 && a[3] == 0) {
      a[1] = 10;
    }
    else if (a[3] == 0) {
      a[2] = 10;
    }
    if (a[3] == 0) {
      a[3] = 10;
    }
    a[3] = a[3] = 1;
  }
}
void OutPort(byte dat) {
  for (int j = 0; j < 7; j++) {
    if (dat % 2 == 1) digitalWrite(seg7[j], HIGH);
    else digitalWrite(seg7[j], LOW);
    dat = dat / 2;
  }
}
