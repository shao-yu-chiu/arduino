int seg7[]={13,12,11,10,9,8,7};
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
int com[]={2,3,4,5};
int origin=1500;
int a[5];
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
    a[3]=n%10;
    n=n/10;
    a[2]=n%10;
    n=n/10;
    a[1]=n%10;
    n=n/10;
    a[0]=n%10;
    n=n/10;
  }
void loop() {
if(Serial.available()){
  origin=Serial.parseInt();
  setnumber(origin);
  Serial.println(origin);
  }
  setnumber(origin);
for(int i=0;i<4;i++){
    OutPort(TAB[a[i]]);
    digitalWrite(com[i],HIGH);
    delay(10);
    digitalWrite(com[i],LOW);
    }
    delay(100);
    if(origin=0){
      for(int i=0;i<4;i++){
        OutPort(TAB[a[i]]);
    digitalWrite(com[i],HIGH);
    delay(10);
    digitalWrite(com[i],LOW);
      }
      }
}
void OutPort(byte dat){
  for(int j=0;j<7;j++){
    if(dat%2==1) digitalWrite(seg7[j],HIGH);
    else digitalWrite(seg7[j],LOW);
    dat=dat/2;
    }
  }
