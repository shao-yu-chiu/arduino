/* 溫度感測IC TC77 的溫度感測，送出的溫度感測資料為 raw data */
#include <LiquidCrystal.h>          // 引入 LCD 函式庫
LiquidCrystal lcd(12, 7, 5, 4, 3, 2); // 初始化 LCD 模組

const byte ChipSelect_Pin = 10;         // 指定TC77的晶片選擇腳為D10
const byte dataPin = 11;		// 指定TC77的資料腳為D11
const byte clockPin = 13;		// 指定TC77的CLK為D13
int temp;           // 建立符合TC77資料格式的變數

void setup() {
  pinMode (ChipSelect_Pin, OUTPUT);	// 指定晶片選擇腳為輸出埠
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);         // 設定LCD字幕為 16*2
  lcd.cursor();           // 顯示游標
  lcd.blink();              // 游標閃爍
  lcd.home();             // 將游標移至左上角
  lcd.print("Hello, LCD");  // 顯示字串
  lcd.setCursor(0,1);         // 移動游標至第0行第1列
  lcd.print("  I'm  No:15       ");    // 顯示字串
}

void loop() {
  byte val1,val2;
  digitalWrite(ChipSelect_Pin,LOW);  // 指定CS=LOW，準備進行讀取動作
  //  透過SPI依序讀高8位元→val1，讀低8位元→val2
  val1=shiftIn(dataPin,clockPin,MSBFIRST);
  val2=shiftIn(dataPin,clockPin,MSBFIRST);
  // 讀取完成，讓CS=HIGH變成非選擇狀態
  digitalWrite(ChipSelect_Pin,HIGH);
  temp = val1 * 256 + val2;	// 合成 16 位元的整數資料形態（最高位元為正負號）
  Serial.print("T");
  Serial.println(temp>>3);	// 移除最低3位元無效位元後送出至串列埠
  delay(100);
}
