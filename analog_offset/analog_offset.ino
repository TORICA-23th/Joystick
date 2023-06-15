#define STICK_X 26
#define STICK_Y 27
#define ADJUST  28
#define LED_YELLOW  LED_BUILTIN
#define LED_BLUE    PIN_LED_RXL

// 動作範囲・オフセット範囲設定
const float range_deg = 30.0; // -range_deg ~ +range_deg
const float max_offset_deg = 20.0;

// ジョイスティックの操作方向指定
const float phase_rad = (3.14 / 2);    //3.14 / 4;
//      y
//      |  pi/4
//      | /
//  ----|----x 0
//      |
//      |

// ジョイスティックのゼロ点調整
const float stick_x_zero_raw = 2055.0;
const float stick_y_zero_raw = 2065.0;

#include <IcsHardSerialClass.h>

const byte EN_PIN = 29;
const long BAUDRATE = 115200;
const int TIMEOUT = 100;    //通信できてないか確認用にわざと遅めに設定
IcsHardSerialClass krs(&Serial1, EN_PIN, BAUDRATE, TIMEOUT); //インスタンス＋ENピン(2番ピン)およびUARTの指定
const int servo_zero_pos = 7500;

void setup() {
  analogReadResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("x");
  Serial.println(analogRead(STICK_X));
  Serial.println("y");
  Serial.println(analogRead(STICK_Y));

  delay(1000);
}
