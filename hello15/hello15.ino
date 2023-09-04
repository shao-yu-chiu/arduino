int seg7[]={13,12,11,10,9,8,7};
char TAB[]={0x76,0x00,0x79,0x00,0x38,0x00,0x38,0x00,0x3F,0x00,0x06,0x00,0x6D,0x00};
void setup() {
for(int i=0;i<7;i++){
  pinMode(seg7[i],OUTPUT);
  }
}

void loop() {
for(int i=0;i<14;i++){
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
