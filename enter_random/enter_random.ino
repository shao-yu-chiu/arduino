int seg7[]={13,12,11,10,9,8,7};
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67,0x76,0x79,0x38,0x3F};
int com[]={2,3,4,5};
int data[]={10,11,12,13};
int delaytime=1;
int number=2016;
void setup() {
for(int i=0;i<7;i++){
  pinMode(seg7[i],OUTPUT);
  }
  for(int i=0;i<4;i++){
    pinMode(com[i],OUTPUT);
    }
     Serial.begin(9600);
}
void setnumber(int n){
    data[3]=n%10;
    n=n/10;
    data[2]=n%10;
    n=n/10;
    data[1]=n%10;
    n=n/10;
    data[0]=n%10;
    n=n/10;
  }
void loop() {
if(Serial.available()){
  number=Serial.parseInt();
  setnumber(number);
  Serial.println(number);
  }
  for(int i=0;i<4;i++){
    OutPort(TAB[data[i]]);
    digitalWrite(com[i],HIGH);
    delay(delaytime);
    digitalWrite(com[i],LOW);
    }
}
void OutPort(byte dat){
  for(int j=0;j<7;j++){
    if(dat%2==1) digitalWrite(seg7[j],HIGH);
    else digitalWrite(seg7[j],LOW);
    dat=dat/2;
    }
  }
