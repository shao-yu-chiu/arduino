/* LCD模組的練習　電路連接指示
 * LCD RS→ pin 12  * LCD E → pin 7 * LCD D4→ pin 5
 * LCD D5→ pin 4  * LCD D6→ pin 3 * LCD D7→ pin 2
 * LCD R/W 接地
 */
 
#include <LiquidCrystal.h>          // 引入 LCD 函式庫
LiquidCrystal lcd(12, 7, 5, 4, 3, 2); // 初始化 LCD 模組
char ch;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);         // 設定LCD字幕為 16*2
  lcd.cursor();           // 顯示游標
  lcd.blink();              // 游標閃爍
  lcd.home();             // 將游標移至左上角
  lcd.print("Hello, LCD");  // 顯示字串
  lcd.setCursor(0,1);         // 移動游標至第0行第1列
  lcd.print("  Arduino...");    // 顯示字串
}

void loop()
{
  if (Serial.available()) { // 若串列緩衝區有資料
    lcd.clear();                // 清除LCD螢幕
    while (1) {
      ch=Serial.read();
      if (ch=='\r') {           // 如果是行結尾則離開迴圈
        Serial.println();
        break;            // 離開迴圈
      }
      if (ch>0) {
          Serial.print(ch);       // 顯示讀到的字元至Serial Monitor
          lcd.print(ch);      // 顯示讀到的字元至LCD
      }
    }
  }
}
