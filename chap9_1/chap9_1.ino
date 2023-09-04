/* Beep + Serial Monitor 的發聲控制 */

#include "pitches.h"      // 引入音調的標頭檔 (包含8個八度音)
const byte Buzzer = 14;   // 蜂鳴器的接腳 D8
char chr, index;

// 宣告一個字元 1~7 對應到第4八度音 Do~Si 的音調陣列
int notes4[] = { NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4 };
// 宣告一個字元 A~G 對應到第5八度音 La,Si,Do,Re,Mi,Fa,So 的音調陣列
int notes5[] = { NOTE_A5,NOTE_B5,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5 };

void setup() {
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);      // start serial port
}
void bird(void){
  for(int freq=8000;freq>=600;freq-=100){
    tone(Buzzer,freq);
    delay(1);
    }
    noTone(Buzzer);
  }
void loop() {
  // 判斷串列埠緩衝區有無資料
  if (Serial.available()) {
    chr=Serial.read();    // 從串列埠緩衝區中讀取下一個有效的字元資料
    if ((chr-'1')>=0 && (chr-'7')<=0) {      // 判斷讀入的字元是否介於'1'～'7'
        index=chr-'1';   // 取得音調陣列中的索引值  
        tone(Buzzer, notes4[index], 200);    // 發出指定音調頻率, 維持200ms
    }
    else if ((chr-'A')>=0 && (chr-'G')<=0) { // 判斷讀入的字元是否介於'A'～'G'
        index=chr-'A';   // 取得音調陣列中的索引值
        tone(Buzzer, notes5[index], 200);    // 發出指定音調頻率, 維持200ms
    }
    else if(chr=='q')bird();
    Serial.print("Tone ");      // 在 Serial Monitor 中顯示訊息
    Serial.println(chr);        //
    delay(200*1.3);            // 延遲 200*1.3 ms
  }
}
