/* 溫度感測IC TC77 的溫度感測與LCD顯示 */

#include <LiquidCrystal.h>	        // 引入 LCD 函式庫
LiquidCrystal lcd(12, 7, 5, 4, 3, 2);	// 初始化 LCD 模組

const byte ChipSelect_Pin = 10;         // 指定TC77的晶片選擇腳為D10
const byte dataPin = 11;		// 指定TC77的資料腳為D11
const byte clockPin = 13;		// 指定TC77的CLK為D13
int temp;           // 建立符合TC77資料格式的變數
float tempC, tempF;

void setup() {
  pinMode (ChipSelect_Pin, OUTPUT);	// 指定晶片選擇腳為輸出埠
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, INPUT);
  lcd.begin(16, 2);	      // 設定LCD字幕為 16*2
  lcd.write(0xB2);            // 顯示度的ASCII碼
  lcd.print("C=");	      // 顯示字串
  lcd.setCursor(0,1);	      // 移動游標至第0行第1列
  lcd.write(0xB2);            // 顯示度的ASCII碼
  lcd.print("F=");	      // 顯示字串
  Serial.begin(9600);
}

void loop() {
  byte val1,val2;
  digitalWrite(ChipSelect_Pin,LOW);  // 指定CS=LOW，準備進行讀取動作
  //  透過SPI依序讀高8位元→val1，讀低8位元→val2
  val1=shiftIn(dataPin,clockPin,MSBFIRST);
  val2=shiftIn(dataPin,clockPin,MSBFIRST);
  // 讀取完成，讓CS=HIGH變成非選擇狀態
  digitalWrite(ChipSelect_Pin,HIGH);
  Serial.print(val1,BIN);        // 顯示第１筆資料
  Serial.print("\t");
  Serial.println(val2,BIN);      // 顯示第２筆資料，其中最低3位元無效
  temp = val1 * 256 + val2;     // 合成 16 位元的整數資料形態（最高位元為正負號）
  tempC = (temp>>3) * 0.0625;   // 移除最低3位元無效位元後，轉成攝氏溫度
  tempF = 1.8 * tempC + 32.0;   // 轉換成華氏溫度
  lcd.setCursor(3,0);	        // 移動游標至第3行第0列
  lcd.print(tempC);             // 顯示取得的攝氏溫度
  lcd.print(" ");               // 輸出一個空白字
  lcd.setCursor(3,1);	        // 移動游標至第3行第1列
  lcd.print(tempF);             // 顯示取得的華氏溫度
  lcd.print(" ");               // 輸出一個空白字
}
