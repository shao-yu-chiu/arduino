int buttonPin = 2, ledPin;
int ledState = HIGH;         // 宣告LED的狀態，一開始預設為不亮
int buttonState;         // 按鍵讀取狀態的變數
int lastButtonState = LOW;    // 上次的按鍵讀取狀態變數
int origin=6;

unsigned long lastDebounceTime = 0; // 記錄上一次消除彈跳的時間
unsigned long debounceDelay = 50; // 消除開關彈跳的延遲時間設為50ms
void setup() {
  pinMode(buttonPin, INPUT);
  for (int i = 6; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  int reading = digitalRead(buttonPin);
  // 當開關壓下或有雜訊時，開關狀態有改變（不相等）
  if (reading != lastButtonState) {
    // 重設上一次的消除彈跳時間
    lastDebounceTime = millis();
  }

  // 判斷現在與上次時間點的差值有無超過 debounceDelay，若有，代表消除開關彈跳時間已過
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) { // 如果按鍵狀態有改變
      buttonState = reading;
      // 只有在buttonState為 LOW 時才改變亮度
      if (buttonState == LOW){
        if(origin==13){
         digitalWrite(13,digitalRead(ledPin)==HIGH);
         digitalWrite(6,digitalRead(ledPin)==LOW);
         origin=6;
         delay(50);
        }
        else{
          digitalWrite(origin,digitalRead(ledPin)==HIGH);
         digitalWrite(origin+1,digitalRead(ledPin)==LOW);
         origin=origin+1;
         delay(50);
          } 
        }
    }
    else {   // 按鍵狀態無改變，代表久按的情況
      // 現在與上次時間差值有無超過久按值
      if ((millis() - lastDebounceTime) > 1000) {
        // 只有在buttonState為 LOW 時才改變亮度
        if (buttonState == LOW){
          if(origin==13){
         digitalWrite(13,digitalRead(ledPin)==HIGH);
         digitalWrite(6,digitalRead(ledPin)==LOW);
         origin=6;
         delay(20);
        }
        else{
          digitalWrite(origin,digitalRead(ledPin)==HIGH);
         digitalWrite(origin+1,digitalRead(ledPin)==LOW);
         origin=origin+1;
         delay(20);
          } 
        }
        }
    }
  }
  lastButtonState = reading;  // 儲存按鍵讀值
}
