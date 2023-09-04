const int seg7[] = {A4, A3, A2, A1, 9, 8, 7};
const int scan[] = { 6, 5, 4, 3 }; //電晶體腳位
int passward[] = {17, 17, 17, 17, 17, 17, 17, 17, 0, 6, 0, 4, 2, 2, 0}; //預設密碼，17為未輸入狀態
int longg = 0; //密碼的長度
int longg2 = 0; //輸入的長度
int sett = 0, inp = 1; //設定是否可用 : 是否可輸入
int runn = 11; //跑馬燈
int rr = 0; //是否跑馬
int keyData[] = {82, 160, 233, 302, 368, 431, 493, 552, 610, 668, 725, 783, 841, 900, 960}; /*a0的電壓值判斷陣列*/
int keyin[] = {40, 20, 21, 22, 40, 3, 6, 9, 0, 2, 5, 8, 23, 1, 4, 7}; /*20:text,21:set,22:open,23:c -- 功能鍵*/
int Data[15]; //輸入值
int outdata[4]; //七段顯示
int popo = 0; //警報是否響起
int fose = 0; //錯誤的次數
int yno = 1; //輸入是否正確
int delaytime = 1; //七段掃描時間
// 七節顯示器編碼表
char TAB[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67,
               0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0 , 0x40/*未輸入狀態*/
             };
int ii, jj , b, i;  // 迴圈用的變數
int kp = 11; //跑馬燈從哪開始跑
int key; //輸入按鍵編號
long llat = 0; //跑馬更變時間
long lastTime = 0; //計時100ms
long lastt = 0; //紀錄警報時間
long llk = 0;   //警報時間到數
int tt = 5000;  //警報時間
byte scanLine; //七段掃描線
#define DP_pin 12
#define Buzzer 10    //蜂鳴器腳位
#define point -1     // 小數點的位置 0/1/2/3 為千/百/十/個位數
#define outputA 2    // 定義連接腳位 CLK
#define outputB 11   // 定義連接腳位 DT

void setup() {
  Serial.begin(9600);
  for (ii = 0; ii < 4; ii++) {
    pinMode(scan[ii], OUTPUT); //設定電晶體io
    digitalWrite(scan[ii], LOW);  // 掃描端電晶體 OFF
  }
  for (ii = 0; ii < 7; ii++) {
    pinMode(seg7[ii], OUTPUT); //設定七段a-g io
  }
  for (ii = 0; ii < 15; ii++)Data[ii] = 17;//把字變成未輸入狀態
  for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態;
}

void loop() {
  ScanNext();
  if (millis() - lastTime >= 100) {
    lastTime = millis();
    ReadKeyPad(); //鍵盤輸入
    if (popo == 1) {  //警報
      rr = 0; //跑馬燈關閉
      for (ii = 0; ii < 4; ii++)outdata[ii] = 16;//把字變成無
      outdata[2] = tt / 1000; //顯示5秒
      if (millis() - llk > 800) { //過一秒繼續顯示倒數值
        llk = millis();
        tt -= 1000; //過一秒
        for (ii = 0; ii < 4; ii++)outdata[ii] = 16;//把字變成無
        outdata[2] = tt / 1000; //顯示5秒
        ScanNext(); //七段顯示
      }
      for (i = 4000; i > 3000; i -= 100) { //警報聲
        tone(10, i);  //頻率由高到低
        for (ii = 0; ii < 20; ii++) { //delay+七段
          delay(1);   //延長聲音
          ScanNext();  //避免七段在delay時不會亮
        }
        noTone(10);//無聲
      }
    }
  }

  if (rr == 1) { //跑馬燈
    if (millis() - llat >= 1000) {
      llat = millis(); //更新計數時間
      for (jj = 3; jj >= 0; jj--) {
        if (Data[jj + kp] > 10)outdata[jj] = 16; //到最高位元空格
        if (Data[jj + kp] < 10)outdata[jj] = Data[jj + kp]; //是數字就跑馬輸出
        Serial.print(outdata[3 - jj]);
        if (Data[jj + kp] > 10)kp = 12; //若遇第一個未輸入(17)，就回到最低位元
      }
      Serial.println( );
      kp -= 1; //換下一個數字
    }
  }

  if (millis() - lastt >= 5000 && popo == 1) { //五秒警報取消
    popo = 0; //警報結束
    for (ii = 0; ii < 15; ii++)Data[ii] = 17;//把字變成未輸入狀態;
    for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態;
    longg2 = 0; //把輸入長度規0
    inp = 1; //恢復輸入
  }

}

void ReadKeyPad() {
  key = analogRead(A0);
  if (key < 1000 && inp == 1) {//若有輸入，且允許輸入
    rr = 0; //先不要跑馬
    for (jj = 14; jj > 10; jj--)  outdata[jj - 11] = Data[jj];//顯示最低位元
    ScanNext();
    int kk = 0;
    if (key > 15) { //若不是最後一顆按鈕
      for (kk = 1; kk < 16; kk++) { // 輸入電壓值判斷按下哪一顆按鈕
        if (key > (keyData[kk - 1] - 15) && key < (keyData[kk - 1] + 15)) break;
      }
    }
    kk = keyin[kk]; //把鍵盤值換成密碼鎖鍵盤按鍵值
    if (kk <= 10) { //輸入是數字
      tone(10, 2500); // 按下按鈕叫
      for (ii = 0; ii < 30; ii++) { //delay+七段
        delay(1);
        ScanNext();  //避免七段在delay時不會亮
      }
      noTone(10);

      for (jj = 0; jj <= 13; jj++) { // 將數值往左移位儲存
        Data[jj] = Data[jj + 1];
      }

      Data[14] = kk;// 儲存剛按的數值至個位數
      longg2 = 0;
      longg = 0;
      for (ii = 14; ii >= 0; ii--) { //取輸入的長度
        if (Data[ii] < 10)longg2 += 1; //若是數字長度加一
        if (Data[ii] > 10)  break;   //若是未輸入長度加一
      }
      for (ii = 14; ii >= 0; ii--) { //取密碼的長度
        if (passward[ii] < 10)longg += 1; //若是數字長度加一
        if (passward[ii] > 10) break;  //若是未輸入長度加一
      }
      Serial.print("longg="); //序列副顯示輸入與預設密碼
      Serial.println(longg);
      Serial.print("longg2=");
      Serial.println(longg2);
      Serial.print("input=");
      for (jj = 0; jj <= 14 ; jj++) {  //序列附顯式輸入的數值
        if (Data[jj] < 10)Serial.print(Data[jj]);
      }
      Serial.println( );//換行

      Serial.print("passward="); //序列附顯式現在密碼
      for (jj = 0; jj <= 14; jj++) {
        if (passward[jj] < 10)Serial.print(passward[jj]);
      }
      Serial.println( ); //換行
    }

    if (longg2 > 4) { //輸入長度大於4
      rr = 1; //loop開始跑馬
      llat = millis(); //開始計時(換數字)
      kp = 11; //從哪開始
    }
    if (longg2 <= 4) { //輸入長度小於4
      rr = 0; //不要跑馬
      for (jj = 14; jj > 10; jj--) { //把輸入存入顯示陣列
        outdata[jj - 11] = Data[jj];
      }
    }
    ScanNext();
    /*----------------------------------------------------------------------------------------------------------------*/
    if (kk >= 20) { //輸入是功能鍵
      rr = 0;
      if (kk == 22) {  //按下open
        for (int i = 0; i <= 14; i++) { //依順序每個位元判斷是否一樣
          if (passward[i] == Data[ i])yno = 1; //一樣繼續判斷下一個位元
          if (passward[i] != Data[ i]) { //有不一樣就跳出
            yno = 0; //表錯誤
            break; //不再繼續偵測
          }
        }
        Serial.println(yno); //檢查是否錯誤
        if (yno == 0) {//錯誤
          fose += 1; //錯誤次數加一
          for (ii = 0; ii < 15; ii++)Data[ii] = 17; //把字變成未輸入狀態
          for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態
          longg2 = 0; //長度規0
          sett = 0; //無法啟用設定
          for ( b = 0; b < 3; b++) {// 叫三下
            tone(10, 5000);
            for (ii = 0; ii < 30; ii++) { //delay+七段
              delay(1);
              ScanNext();//避免七段在delay時不會亮
            }
            noTone(10);
            for (ii = 0; ii < 100; ii++) { //delay+七段
              delay(1);
              ScanNext();//避免七段在delay時不會亮
            }
          }

          if (fose >= 3) { //錯三次鎖5s
            popo = 1; //警報開啟
            lastt = millis(); //開始計時
            llk = millis(); //多久要換數字
            tt = 5000; //倒數5秒
            fose = 0; //把錯的次數歸0
            inp = 0; //禁止輸入
          }
          ScanNext(); //七段輸出
        }
        if (yno == 1) { /*正確*/
          fose = 0; //把錯的次數歸0
          sett = 1; //啟用設定
          for (ii = 0; ii < 15; ii++)Data[ii] = 17; //把字變成未輸入狀態
          for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態
          for (b = 0; b < 2; b++) {
            tone(10, 5000); // 叫兩下
            for (ii = 0; ii < 30; ii++) { //delay+七段
              delay(1);
              ScanNext(); //避免七段在delay時不會亮
            }
            noTone(10);
            for (ii = 0; ii < 100; ii++) { //delay+七段
              delay(1);
              ScanNext();  //避免七段在delay時不會亮
            }
          }
          ScanNext(); //七段輸出
          //for (ii = 0; ii < 15; ii++)Data[ii] = 17; //把字變成未輸入狀態
          //for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態
          longg2 = 0;
        }
      }
      /*----------------------------------------------------------------------------------------------------------------------*/
      if (kk == 23) { //清除
        for (int y = 0; y < 15; y++) Data[y] = 17;
        for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態;
        tone(10, 2500); // 按下按鈕叫
        for (ii = 0; ii < 30; ii++) { //delay+七段
          delay(1);
          ScanNext();  //避免七段在delay時不會亮
        }
        noTone(10);
      }
      /*-----------------------------------------------------------------------------------------------------------------------*/
      if (kk == 21 ) { //按下set
        Serial.print("sett="); //序列附顯式set是否啟用
        Serial.println(sett);  //序列附顯式set是否啟用
        if (sett == 1) {
          tone(10, 4000); // 按下按鈕長叫表設定完成
          for (ii = 0; ii < 200; ii++) { //delay+七段
            delay(1);
            ScanNext();  //避免七段在delay時不會亮
          }
          noTone(10);
          for (ii = 0; ii < 15; ii++)passward[ii] = Data[ii]; //把換成新密碼
          for (ii = 0; ii < 15; ii++)Data[ii] = 17;//把字變成未輸入狀態
          for (ii = 0; ii < 4; ii++)outdata[ii] = 17; //把字變成未輸入狀態;
          longg2 = 0; //長度規0
          sett = 0;//設定關閉
          longg = 0;  //長度規0
          Serial.println( );
          Serial.print("passward="); //序列附顯示新密碼
          for (jj = 0; jj <= 14; jj++) {  //序列附顯示新密碼
            if (passward[jj] < 10)Serial.print(passward[jj]);
          }
          Serial.println( );//序列附換行
        }
      }
      /*--------------------------------------------------------------------------------------------------------------------------*/
    }
    while (analogRead(A0) < 1000) {      // 等待放開
      ScanNext(); //七段輸出
    }
  }
}
/*----------------------------------------------------------------------------------------------------------------*/
void ScanNext() {  //七段電晶體掃描
  OutPort(TAB[outdata[scanLine]]);
  digitalWrite(scan[scanLine], HIGH);  // 指定的掃描端電晶體 ON
  delay(delaytime);
  digitalWrite(scan[scanLine], LOW);   // 指定的掃描端電晶體 OFF
  scanLine = (scanLine + 1) % 4;      // 換下一條掃描線, 並限制在 0~3

}
/*----------------------------------------------------------------------------------------------------------------*/
void OutPort(byte dat) {  //七段解碼輸出
  for (jj = 0; jj < 7; jj++) {
    digitalWrite(DP_pin, scanLine == point);
    if (dat % 2 == 1) // 取出 dat 的最低位元
      digitalWrite(seg7[jj], HIGH);  // 若為 1 代表該段要亮, 輸出高準位
    else
      digitalWrite(seg7[jj], LOW);   // 若為 0 代表該段要滅, 輸出低準位
    dat = dat / 2; // 除2，進行下一位元的處理
  }
}
