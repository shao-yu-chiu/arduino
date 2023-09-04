int buttonPin = 2;
int ledPin = 10;
int longpress = 1000;
int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

int brightness = 0;
int fadeAmount = 10;

unsigned long lastDebounceTime = 0;
unsigned long deBounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        change brightness();
      }
    }
    }
    else {
      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (buttonState == LOW) {
          change brightness();
        }
      }
    }
  lastButtonState = reading;
}
void ChangeBrightness(void) {
  brightness = brightness + fadeAmount;  // 改變下次亮度的數值
  // 進行邊界值的限制
  if (brightness > 255) brightness = 255;
  if (brightness < 0) brightness = 0;
  // 當遞增至邊界值255，或遞減至邊界值0時，反轉 fadeAmount 值
  if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
  analogWrite(ledPin, brightness);
  Serial.print("brightness = ");    // 顯示亮度值資訊
  Serial.println(brightness);
  // 延遲 30ms 方便觀察微小變化的效果
  delay(30);
}
