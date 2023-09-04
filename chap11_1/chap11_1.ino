// 伺服機控制練習：可透過Serial Monitor下達控制位置給伺服機
// 控制的範圍為 500～2500
const byte Servo_pin = 22;  // 伺服機的控制埠 D11
int pos=1500;  // 伺服機位置，起始值預設為1500 （1.5ms正中央位置）

void setup() 
{ 
  Serial.begin(9600);          // 啟用串列埠
  pinMode(Servo_pin, OUTPUT);  // 設定伺服機的I/O為輸出
  digitalWrite(Servo_pin,LOW); // 預設為 LOW
} 
 
void loop() 
{
  // 判斷串列埠緩衝區有無資料
  if (Serial.available()) {
    pos=Serial.parseInt();        // 從串列埠緩衝區中讀取下一個有效的整數資料
    if (pos>2500) pos=2500;      // 限制範圍
    if (pos<500) pos=500;        // 限制範圍
    Serial.println(pos);          // 在 Serial Monitor 中顯示訊息
  }
  digitalWrite(Servo_pin,HIGH);  // 輸出高準位
  delayMicroseconds(pos);        // 延遲脈寬的時間
  digitalWrite(Servo_pin,LOW);   // 輸出低準位 20 ms
  delay(20);
}
