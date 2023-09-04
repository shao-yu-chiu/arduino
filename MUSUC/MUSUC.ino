/*  音樂盒程式 歌曲：新不了情  (採用存放在 程式記憶體的方式)  by 梅克2工作室
    回憶過去痛苦的相思忘不了為何你還來撥動我心跳  */

#include <avr/pgmspace.h>
#include "pitches.h"    // 引入音調的標頭檔 (包含8個八度音)
const byte Buzzer = 14; // 蜂鳴器的接腳 D10
const int rhythm = 500;	// 定義每1拍的音長(ms)
char index;		// 音樂盒資料的讀取指標
int SoundLeng;		// 音長的變數
int song_tone;		// 音高的變數

// 宣告歌譜的陣列資料, 第一筆為音高, 第二筆為音長, 結束代碼為-1
const float song[] PROGMEM = {_C5,0.5,
_D5,0.5,	_E5,1,  _C5,0.5,		_B4,0.5,	_A4,0.5,	_B4,0.25,
_C5,0.75,	_E5,0.5,	_D5,1,	_B4,0.5, _A4,0.5,  _G4,0.5,  _A4,0.25,  _B4,0.75,
_D5,0.5,  _C5,1,  0,0.5,  _C5,0.25,_B4,0.25, _C5,1,  0,0.25,  _A4,0.25, _A4,0.25,  _B4,0.25,  _C5,0.5,   _B4,0.5,
_A4,0.5, _G4,0.5,  0,1,  _C5,0.5,   _D5,0.5, _E5,1, _C5,0.5,  _B4,0.5,  _A4,0.5,   _B4,0.25, _C5,0.75, _E5,0.5,  _D5,1,  _B4,0.5,   _A4,0.5,
_GS4,0.5, _F5,0.5,  _E5,0.5,  _B4,0.5,   _C5,1,0,3
-1 };

void setup() {
  pinMode(Buzzer,OUTPUT);
}

void loop() {
  index=0;      //指標歸 0, 從歌曲陣列song的第 0 筆開始讀取並發音
  while (1) {
    if(analogRead(A0)>500) break;
    song_tone = pgm_read_float(&song[index]);			//讀出歌曲陣列中的音高
    index++;    //指標加 1
    SoundLeng = pgm_read_float(&song[index])*rhythm;		//讀出音長並計算
    index++;    //指標加 1
    if (song_tone==-1)				//若是結束代碼-1, 則跳出 while 迴圈
        break;
    else if (song_tone==0)			//休止符的處理
        delay(SoundLeng*1.3);			//暫停指定的音長時間(不發聲)
    else {
        tone(Buzzer, song_tone, SoundLeng);	//讀出音高對應的頻率並發聲
        delay(SoundLeng*1.3);			//暫停指定的音長時間
    }
  }
}
