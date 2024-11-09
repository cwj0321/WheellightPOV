#include <Adafruit_NeoPixel.h>
#define PIN 6  // 네오픽셀 스트립이 연결된 핀
#define NUMPIXELS 8  // 픽셀 수

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int brightness = 100; // 밝기 설정 (0~255)

// int delayTime = 50; // 각 열의 표시 시간 (ms)

// 알파벳 패턴 (세로 8픽셀, 가로는 각 열을 표현함)
// A부터 Z까지의 알파벳에 맞는 비트맵 패턴 정의
byte alphabet[][8] = {
  {B00111100, B01001010, B01001010, B01001010, B01111110, B01001010, B01001010, B01001010}, // A
  {B01111100, B01001010, B01001010, B01111100, B01001010, B01001010, B01111100, B00000000}, // B
  {B00111110, B01000000, B01000000, B01000000, B01000000, B01000000, B00111110, B00000000}, // C
  {B01111100, B01001010, B01001010, B01001010, B01001010, B01001010, B01111100, B00000000}, // D
  {B01111110, B01000000, B01000000, B01111100, B01000000, B01000000, B01111110, B00000000}, // E
  {B01111110, B01000000, B01000000, B01111100, B01000000, B01000000, B01000000, B00000000}, // F
  {B00111100, B01000010, B01000000, B01000000, B01001110, B01000010, B00111100, B00000000}, // G
  {B01001010, B01001010, B01001010, B01111110, B01001010, B01001010, B01001010, B00000000}, // H
  {B01111100, B00010000, B00010000, B00010000, B00010000, B00010000, B01111100, B00000000}, // I
  {B00011110, B00000100, B00000100, B00000100, B00000100, B01000100, B00111000, B00000000}, // J
  {B01001010, B01001100, B01010000, B01100000, B01010000, B01001100, B01001010, B00000000}, // K
  {B01000000, B01000000, B01000000, B01000000, B01000000, B01000000, B01111110, B00000000}, // L
  {B01000010, B01100110, B01011010, B01000010, B01000010, B01000010, B01000010, B00000000}, // M
  {B01000110, B01100110, B01010110, B01001110, B01000110, B01000110, B01000110, B00000000}, // N
  {B00111100, B01000010, B01000010, B01000010, B01000010, B01000010, B00111100, B00000000}, // O
  {B01111100, B01001010, B01001010, B01111100, B01000000, B01000000, B01000000, B00000000}, // P
  {B00111100, B01000010, B01000010, B01000010, B01001010, B01000100, B00111010, B00000000}, // Q
  {B01111100, B01001010, B01001010, B01111100, B01001000, B01000100, B01000010, B00000000}, // R
  {B00111110, B01000000, B01000000, B00111100, B00000010, B00000010, B01111100, B00000000}, // S
  {B01111110, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00000000}, // T
  {B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B00111100, B00000000}, // U
  {B01000010, B01000010, B01000010, B00100100, B00100100, B00011000, B00001000, B00000000}, // V
  {B01000010, B01000010, B01000010, B01000010, B01011010, B01011010, B00100100, B00000000}, // W
  {B01000010, B00100100, B00011000, B00001000, B00011000, B00100100, B01000010, B00000000}, // X
  {B01000010, B00100100, B00011000, B00010000, B00010000, B00010000, B00010000, B00000000}, // Y
  {B01111110, B00000010, B00000100, B00001000, B00010000, B00100000, B01111110, B00000000}, // Z
};

// 글자 출력
void displayLetter(char letter) {
  if (letter >= 'A' && letter <= 'Z') {
    int index = letter - 'A'; // 알파벳의 인덱스
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (bitRead(alphabet[index][i], 7 - j)) {
          strip.setPixelColor(j, strip.Color(0, 255, 0)); // 녹색으로 픽셀 점등
        } else {
          strip.setPixelColor(j, 0); // 꺼짐
        }
      }
      strip.show();
      delay(50); // 각 열 출력 후 지연 시간
    }
  }
}

// 단어 출력
void displayWord(String word) {
  word.toUpperCase();  // 대문자로 변환
  for (int i = 0; i < word.length(); i++) {
    displayLetter(word[i]);
    delay(100);  // 글자 간 딜레이
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();  // 픽셀 초기화
}

void loop() {
  displayWord("NEOPIXEL");  // 단어 출력
  delay(1000);  // 다음 출력 전 딜레이
}