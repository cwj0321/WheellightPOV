#include <Adafruit_NeoPixel.h>

#define PIN 6                    // 네오픽셀 핀 번호
#define NUMPIXELS 8              // 네오픽셀 개수
#define NUMCOLUMNS 120           // 이미지 열 수
#define BRIGHTNESS 50            // 밝기 설정
#define HALL_SENSOR_PIN 2        // 홀 센서 핀 번호
#define WHEEL_DIAMETER 0.4       // 바퀴 지름 (단위: 미터)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

volatile int rotationCount = 0;  // 회전 수
unsigned long lastTime = 0;      // 마지막 회전 시간
float rpm = 0;                   // RPM
unsigned long delayTime = 100;   // 기본 딜레이 시간 (밀리초)

const uint8_t colors[NUMPIXELS][NUMCOLUMNS][3] PROGMEM = {
 
};

void setup() {
  pinMode(HALL_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countRotation, RISING);
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();
  pixels.show();
  Serial.begin(9600); // 시리얼 모니터를 통해 RPM 확인
}

void loop() {
  // RPM 계산 (100ms마다 갱신)
  if (millis() - lastTime >= 100) {
    if (rotationCount > 0) {
      unsigned long currentTime = millis();
      float timePerRotation = (currentTime - lastTime) / 1000.0; // 회전 시간 (초 단위)
      rpm = (60.0 / timePerRotation);  // RPM 계산
      lastTime = currentTime;
      rotationCount = 0;

      // 출력 딜레이 계산 (속도가 높을수록 짧아짐)
      float rotationTimeSec = 60.0 / rpm;  // 한 바퀴 회전 시간 (초 단위)
      delayTime = (rotationTimeSec * 1000) / NUMCOLUMNS;  // 열 전환 지연 시간
    } else {
      rpm = 0;
      delayTime = 100;  // 기본 지연 시간
    }
  }

  // 속도가 10 km/h 이상일 때만 출력
  if (rpm >= 83.33) { // 대략 10 km/h에 해당
    for (int col = 0; col < NUMCOLUMNS; col++) {
      updateColumnColors(col);
      pixels.show();
      delay(delayTime); // 속도에 따른 지연 시간
    }
  } else {
    pixels.clear();
    pixels.show();
  }

  // 시리얼 모니터에 상태 출력
  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" | Delay: ");
  Serial.print(delayTime);
  Serial.println(" ms");
}

// 홀 센서 인터럽트 함수
void countRotation() {
  rotationCount++;
}

// 열 색상을 설정하는 함수
void updateColumnColors(int col) {
  for (int i = 0; i < NUMPIXELS; i++) {
    uint8_t r = pgm_read_byte(&colors[i][col][0]);
    uint8_t g = pgm_read_byte(&colors[i][col][1]);
    uint8_t b = pgm_read_byte(&colors[i][col][2]);
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
}