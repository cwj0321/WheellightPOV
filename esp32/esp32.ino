//ESP32보드 Hall sensor RPM, NeoPixel, BLE, JSON 불러오기
#include <BluetoothSerial.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#define NEOPIXEL_PIN 18         // 네오픽셀 데이터 핀
#define HALL_SENSOR_PIN 4       // 홀 센서 핀
#define NUMPIXELS 64            // 네오픽셀 개수 (한 핀에 연결된 전체)
#define BRIGHTNESS 50           // 네오픽셀 밝기 설정

BluetoothSerial SerialBT;
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

volatile int rotationCount = 0; // 회전 수
unsigned long lastTime = 0;     // 마지막 회전 시간
float rpm = 0;                  // RPM
uint8_t colors[NUMPIXELS][3];   // 색상 배열

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();
  pixels.show();

  // Bluetooth 초기화
  if (!SerialBT.begin("ESP32_Display")) {
    Serial.println("Bluetooth initialization failed!");
    return;
  }
  Serial.println("Bluetooth initialized. Waiting for pairing...");

  // 홀 센서 인터럽트 설정
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countRotation, RISING);
}

void loop() {
  // Bluetooth로 JSON 데이터 수신
  if (SerialBT.available()) {
    String jsonData;
    while (SerialBT.available()) {
      jsonData += char(SerialBT.read());
    }
    parseColors(jsonData);  // JSON 파싱 및 colors 배열에 저장
    displayColors();
  }

  // RPM 계산 (100ms마다 갱신)
  if (millis() - lastTime >= 100) {
    if (rotationCount > 0) {
      unsigned long currentTime = millis();
      float timePerRotation = (currentTime - lastTime) / 1000.0; // 회전 시간 (초 단위)
      rpm = (60.0 / timePerRotation);  // RPM 계산
      lastTime = currentTime;
      rotationCount = 0;
    } else {
      rpm = 0;
    }
  }

  // 시리얼 모니터에 상태 출력
  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.println(" | Bluetooth connected: ");
}

// 홀 센서 인터럽트 함수
void countRotation() {
  rotationCount++;
}

// JSON 데이터를 파싱하여 colors 배열에 저장하는 함수
void parseColors(String jsonData) {
  DynamicJsonDocument doc(4096); // JSON 문서 크기 설정
  DeserializationError error = deserializeJson(doc, jsonData);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  // JSON 배열에서 색상 데이터를 가져와 colors 배열에 저장
  JsonArray colorArray = doc["colors"];
  for (int i = 0; i < NUMPIXELS; i++) {
    JsonArray rgb = colorArray[i];
    colors[i][0] = rgb[0];
    colors[i][1] = rgb[1];
    colors[i][2] = rgb[2];
  }
}

// colors 배열의 색상을 네오픽셀에 출력하는 함수
void displayColors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    uint8_t r = colors[i][0];
    uint8_t g = colors[i][1];
    uint8_t b = colors[i][2];
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}