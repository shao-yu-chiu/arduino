// 消除開關彈跳 Debounce 及久按開關的應用
// 常數宣告，設定I/O腳位
const int buttonPin = 2;       // 按鍵pin腳
const int ledPin1[] = {6,7,8,9,10,11,12};	       // LED pin
const int longPress = 1000;    // 久按開關的時間設定

// 變數宣告
int ledState = HIGH;	       // 宣告LED的狀態，一開始預設為不亮
int buttonState;	       // 按鍵讀取狀態的變數
int lastButtonState = LOW;    // 上次的按鍵讀取狀態變數

int brightness = 0;     // LED 的亮度變數
int fadeAmount = 10;    // LED 亮度增減的數值，值愈大，變化愈快

unsigned long lastDebounceTime = 0;	// 記錄上一次消除彈跳的時間
unsigned long debounceDelay = 50;	// 消除開關彈跳的延遲時間設為50ms

void setup() {
  pinMode(buttonPin, INPUT);
  for(int i=0;i<=7;i++){
  pinMode(ledPin[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // 讀取按鍵開關狀態
  int reading = digitalRead(buttonPin);
  // 當開關壓下或有雜訊時，開關狀態有改變（不相等）
  if (reading != lastButtonState) {
     // 重設上一次的消除彈跳時間
     lastDebounceTime = millis();
  }
  
  // 判斷現在與上次時間點的差值有無超過 debounceDelay，若有，代表消除開關彈跳時間已過
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {	// 如果按鍵狀態有改變
      buttonState = reading;
      // 只有在buttonState為 LOW 時才改變亮度
      if (buttonState==LOW) ChangeBrightness();
    }
    else {   // 按鍵狀態無改變，代表久按的情況
        // 現在與上次時間差值有無超過久按值
        if ((millis() - lastDebounceTime) > longPress) {  
            // 只有在buttonState為 LOW 時才改變亮度
            if (buttonState==LOW) ChangeBrightness();     
        }
      }
    }
  lastButtonState = reading;	// 儲存按鍵讀值
}

// 改變 LED 亮度的副程式
void ChangeBrightness(void) {
    brightness = brightness + fadeAmount;  // 改變下次亮度的數值
    // 進行邊界值的限制
    if (brightness>255) brightness=255;
    if (brightness<0) brightness=0;
    // 當遞增至邊界值255，或遞減至邊界值0時，反轉 fadeAmount 值
    if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
    for(int i=0;i<=7;i++){
    analogWrite(ledPin[i], brightness);
    }
    Serial.print("brightness = ");    // 顯示亮度值資訊
    Serial.println(brightness);
    // 延遲 30ms 方便觀察微小變化的效果
    delay(30);
}
