#include <Adafruit_NeoPixel.h>

#define PIN 6  // 네오픽셀이 연결된 핀 번호
#define NUMPIXELS 8  // LED 개수


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// 각 글자를 8x6 매트릭스로 정의 (Hanseo 글자)
byte letters[6][8] = {
  {B10101, B10101, B11111, B10101, B10101},  // H
  {B01110, B10001, B11111, B10001, B10001},  // A
  {B01110, B10001, B10000, B10000, B01110},  // N
  {B11111, B01000, B01110, B01000, B11111},  // S
  {B01110, B10001, B10001, B10001, B01110},  // E
  {B11110, B10001, B11110, B10000, B10000}   // O
};

void setup() {
  strip.begin();
  strip.show();  // 초기화 후 LED 끄기
  Serial.begin(9600);
  strip.setBrightness(100);
}

void loop() {
  // 각 글자를 한 줄씩 출력하는 루프
  for (int letter = 0; letter < 5; letter++) {  // Hanseo의 각 글자
    for (int row = 0; row < 8; row++) {  // 각 글자의 행(세로) 8줄
      displayRow(letters[letter][row]);  // 각 줄을 네오픽셀로 출력
      delay(50);  // 딜레이로 잔상효과
    }
    delay(50);  // 글자 간 짧은 딜레이
  }
}

// 각 줄의 데이터를 네오픽셀로 출력
void displayRow(byte rowData) {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (rowData & (1 << i)) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));  // LED 켜기 (빨강)
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));    // LED 끄기
    }
  }
  strip.show();  // LED 업데이트
}