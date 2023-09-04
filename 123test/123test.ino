byte digit[8] = {1, 3, 5, 6, 7, 2, 4, 0};
byte num[4] = {5, 6, 7, 4};
byte led[3] = {2, 3, A4};
byte button[3] = {A0, A1, A2};
int SER_Pin = 8;   //pin 14 on the 75HC595
int RCLK_Pin = 9;  //pin 12 on the 75HC595
int SRCLK_Pin = A3; //pin 11 on the 75HC595
int reset = 10;

#define number_of_74hc595s 1
#define numOfRegisterPins number_of_74hc595s * 8
boolean registers[numOfRegisterPins];
byte seven_seg_digits[10][7] = { { 1, 1, 1, 1, 1, 1, 0 }, // = 0
  { 0, 1, 1, 0, 0, 0, 0 }, // = 1
  { 1, 1, 0, 1, 1, 0, 1 }, // = 2
  { 1, 1, 1, 1, 0, 0, 1 }, // = 3
  { 0, 1, 1, 0, 0, 1, 1 }, // = 4
  { 1, 0, 1, 1, 0, 1, 1 }, // = 5
  { 1, 0, 1, 1, 1, 1, 1 }, // = 6
  { 1, 1, 1, 0, 0, 0, 0 }, // = 7
  { 1, 1, 1, 1, 1, 1, 1 }, // = 8
  { 1, 1, 1, 0, 0, 1, 1 } // = 9
};


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    pinMode(button[i], INPUT_PULLUP);
  }
  pinMode(reset, INPUT_PULLUP);
  for (int i = 0; i <= 3; i++) {
    pinMode(num[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }

  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  clearRegisters();
  writeRegisters();
}
int second = 0;
int minute = 0;
int lastth = 0;
int lastminute = 0;
uint32_t lastbutton = 0;
uint32_t counttime = 0;
uint32_t ledtime = 0;
bool counting = 0;
int state = 0;
bool settime = 0;//0=countdown 1=last
int th = 5;
void loop() {
  if (settime) {
    disp(th / 10, th % 10, 0, 0);
    digitalWrite(led[1], HIGH);
  }
  else if(0==digitalRead(reset)){
   settime=0;
   counting =0;
   minute = lastminute;
   th = lastth;
   second = 0;
 }
 else {
  disp(minute / 10, minute % 10, second / 10, second % 10);
  if (millis() - counttime > 1000) {
  
    if (counting == 1) {
      second--;
      if (second < 0) {
        minute--;
        second = 59;
      }
      if (minute < 0) {
        minute = 0;
        second = 0;
      }
      Serial.print(minute);
      Serial.print(",");
      Serial.println(second);
      if (minute < th) {
        digitalWrite(led[0], HIGH);
       // Serial.println("Alarm");
      }
      else {
        digitalWrite(led[0], LOW);
      }
      if (minute <= 0 && second <= 0) {
        digitalWrite(led[1], HIGH);
        //Serial.println("STOP");
      }
      else {
        digitalWrite(led[1], LOW);
      }
      state = !state;
      digitalWrite(led[2], state);
      //Serial.println(digitalRead(led[2]));
    }
    else {
        //Serial.print(digitalRead(led[0]));
        //Serial.print(digitalRead(led[1]));
        //Serial.println(digitalRead(led[2]));
       // digitalWrite(led[0], !digitalRead(led[0]));
       // digitalWrite(led[1], !digitalRead(led[1]));
     }
     counttime = millis();
   }
   else if (millis() - ledtime>200){
     if (counting == 0){
      digitalWrite(led[0], !digitalRead(led[0]));
      digitalWrite(led[1], !digitalRead(led[1]));
      state = !state;
        digitalWrite(led[2], state);  //ditry fix about digitalRead error on led2
        ledtime = millis();
      }
    }
  }
  scan();

}
void change(int i) {
  switch (i) {
    case 0:
    if (0 == settime) {
      if(counting){
        counting = 0;
      }
      else{
        counting = 1;
        lastminute = minute;
        lastth = th;
      }
    }
    else {
    }
    break;
    case 1:
    if (0 == settime && counting == 0) {
      minute++;
      second = 0;
      //Serial.println(minute);
    }
    else  if (1 == settime) {
      th++;
      //Serial.println(th);
    }

    break;
    case 2:
    if (0 == settime && counting == 0) {
      minute--;
      if (minute < 0) {
        minute = 0;
      }
      second = 0;
      //Serial.println(minute);
    }
    else if (1 == settime) {
      th--;
      if (th < 0) {
        th = 0;
      }

      //Serial.println(th);
    }
    break;
  }


}
void scan() {
  uint32_t start = 0;
  int flag = 0;
  for (int i = 0; i <= 2; i++) {

    if (0 == digitalRead(button[i])) {


      if (millis() - lastbutton > 150) {
        start = millis();
        while (0 == digitalRead(button[i])) {
          if (settime) {
            disp(th / 10, th % 10, 0, 0);
          }
          else {
            disp(minute / 10, minute % 10, second / 10, second % 10);
          }
          if (i == 0 && millis() - start  >= 500 && flag==0) {
            settime = !settime;
            //Serial.print("SET TIME:");
            //Serial.println(settime);
            flag = 1;
            lastbutton = millis();
          
          }
        }

        if(flag==0){
          change(i);
          lastbutton = millis();
        }
      }

      //Serial.println(millis() - start);
    }

  }

}
void disp(int a, int b, int c, int d) {
  int data[4] = {a, b, c, d};
  for (int dig = 0; dig <= 3; dig++) {

    for (byte seg = 0; seg < 7; ++seg) {
      setRegisterPin(digit[seg], !seven_seg_digits[data[dig]][seg]);
      // digitalWrite(digit[seg], !seven_seg_digits[data[dig]][seg]);
    }
    writeRegisters();
    digitalWrite(num[dig], HIGH);
    delayMicroseconds(100);
    digitalWrite(num[dig], LOW);
  }
}

//set all register pins to LOW
void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = HIGH;
  }
}


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters() {

  digitalWrite(RCLK_Pin, LOW);

  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value) {
  registers[index] = value;
}

void serialEvent(){
  
  minute = Serial.parseInt();
  second = Serial.parseInt();
  th = Serial.parseInt();
  counting = Serial.parseInt();
  settime = 0;
  while(Serial.available()){
      int dummy = Serial.read();// statement
  }


}
