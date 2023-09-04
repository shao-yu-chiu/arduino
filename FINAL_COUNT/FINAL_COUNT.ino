int seg7[]={13,12,11,10,9,8,7};
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
int scan[]={2,3,4,5};
int a[]={1,5,0,0};
int delaytime=1;
unsigned lasttime=0;
int reset=13;
bool buttonreset;
void setup() {
for(int i=0;i<7;i++){
  pinMode(seg7[i],OUTPUT);
  }
  for(int i=0;i<4;i++){
    pinMode(scan[i],OUTPUT);
    }
 }

void loop() {
   buttonreset = digitalRead(reset);
  if (buttonreset == LOW) {
   a[0]=1;
   a[1]=5;
   a[2]=0;
   a[3]=0;
  }
  for(int i=0;i<4;i++){
    OutPort(TAB[a[i]]);
    digitalWrite(scan[i],HIGH);
    delay(delaytime);
    digitalWrite(scan[i],LOW);
    }
    if(a[3]==0 && a[2]==0 && a[1]==0 && a[0]==0){
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
    else{
    if ((millis() -lasttime) > 100) {
      if(a[3]==0){
       if (a[2] == 0 && a[1] == 0) {
        a[0]=a[0]-1;
        }
      if (a[2] == 0 ) {
        a[1]=a[1]-1;
       a[2]=10; 
      }
        a[2] = a[2] - 1;
      }
      if(a[3]==0){
        a[3]=10;
        }
        a[3]=a[3]-1;
     lasttime = millis();
    }
    OutPort(TAB[a[0]]);
    digitalWrite(scan[0], HIGH);
    delay(5);
    digitalWrite(scan[0], LOW);

    OutPort(TAB[a[1]]);
    digitalWrite(scan[1], HIGH);
    delay(5);
    digitalWrite(scan[1], LOW);

    OutPort(TAB[a[2]]);
    digitalWrite(scan[2], HIGH);
    delay(5);
    digitalWrite(scan[2], LOW);

    OutPort(TAB[a[3]]);
    digitalWrite(scan[3], HIGH);
    delay(5);
    digitalWrite(scan[3], LOW);
    }
    }
void OutPort(byte dat){
  for(int j=0;j<7;j++){
    if(dat%2==1) digitalWrite(seg7[j],HIGH);
    else digitalWrite(seg7[j],LOW);
    dat=dat/2;
    }
  }
