#define STICK_X 0
#define STICK_Y 1
#define ADJUST  2
#define LED_YELLOW  LED_BUILTIN
#define LED_BLUE    PIN_LED_RXL

// 動作範囲・オフセット範囲設定
const float range_deg = 30.0; // -range_deg ~ +range_deg
const float max_offset_deg = 20.0;

// ジョイスティックの操作方向指定
const float phase_rad = 0;    //3.14 / 4;
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

const byte EN_PIN = 3;
const long BAUDRATE = 115200;
const int TIMEOUT = 100;    //通信できてないか確認用にわざと遅めに設定
IcsHardSerialClass krs(&Serial1, EN_PIN, BAUDRATE, TIMEOUT); //インスタンス＋ENピン(2番ピン)およびUARTの指定
const int servo_zero_pos = 7500;

void setup() {
  analogReadResolution(12);
  krs.begin();  //サーボモータの通信初期設定
}

void loop() {
  uint32_t now_time = millis();
  static uint32_t last_time = 0;
  if (now_time - last_time >= 10) {
    last_time = now_time;

    servo_write(read_offset_deg() + control_curve_degree(stick_normalized()));
  }
}

float read_offset_deg() {
  uint32_t adjust_raw10 = 0;
  for (int i = 0; i < 10; i++) {
    adjust_raw10 += analogRead(ADJUST);
  }
  float adjust = ((float)(adjust_raw10 / 10) - 1024.0) / 2048; //  -1.0 ~ +1.0

  return adjust * 20;
}

void servo_write(float degree) { //get degree -range_deg ~ +range_deg, control servo
  int servo_val = servo_zero_pos + (2000 * degree / 135);
  /*
    if (abs(servo_val - servo_zero_pos) < 10) {
    servo_val = servo_zero_pos;
    }*/
  krs.setPos(0, servo_val);
  //Serial.println(servo_val);
}

float control_curve_degree(float val_normalized) { //get -1 ~ +1 , return degree -range_deg ~ +range_deg
  //float degree = val_normalized * abs(val_normalized) * range_deg;
  float degree = val_normalized * range_deg;
  if (degree >= range_deg) {
    degree = range_deg;
  }
  if (degree <= -range_deg) {
    degree = -range_deg;
  }
  return degree;
}

float stick_normalized() { //return -1 ~ +1
  uint32_t stick_x_raw10 = 0;
  uint32_t stick_y_raw10 = 0;
  for (int i = 0; i < 10; i++) {
    stick_x_raw10 += analogRead(STICK_X);
    stick_y_raw10 += analogRead(STICK_Y);
  }
  /*
    Serial.print(stick_y_raw10 / 10);
    Serial.print(",");
    Serial.println(stick_x_raw10 / 10);*/
  float stick_x = ((float)stick_x_raw10 / 10 - stick_x_zero_raw) / 2048.0;
  float stick_y = ((float)stick_y_raw10 / 10 - stick_y_zero_raw) / 2048.0;
  float len = sqrt(stick_x * stick_x + stick_y * stick_y);
  return (len * cos(atan2(stick_y, stick_x) - phase_rad));
}
