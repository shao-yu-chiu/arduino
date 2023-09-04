int seg7[]={13,12,11,10,9,8,7};
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
void setup() {
for(int i=0;i<7;i++){
  pinMode(seg7[i],OUTPUT);
  }
}

void loop() {
for(int i=0;i<10;i++){
  OutPort(TAB[i]);
  delay(500);
  }
}
void OutPort(byte dat){
  for(int j=0;j<7;j++){
    if(dat%2==1) digitalWrite(seg7[j],HIGH);
    else digitalWrite(seg7[j],LOW);
    dat=dat/2;
    }
  }
