#include <Wire.h>
#include <Servo.h>
#include "mpu6500.h"

// IMU (MPU-6500)
bfs::Mpu6500 imu(&Wire, 0x68);

// Servo
Servo servo;
const int SERVO_PIN = 9;

// サーボの角度範囲（安全のため少し狭め）
const int SERVO_MIN = 10;
const int SERVO_MAX = 170;

// ローパス（揺れ防止）
float filteredDeg = 90.0f;
const float alpha = 0.15f;

// 角度制限（加速度で安定して取れる範囲）
const float TILT_LIMIT_DEG = 45.0f;

static float clampf(float v, float lo, float hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

static int clampi(int v, int lo, int hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  // I2C
  Wire.begin();
  Wire.setClock(100000);

  // IMU　初期化
  if (!imu.Begin()) {
    Serial.println("MPU6500 init failed");
    while (1) {}
  }
  Serial.println("MPU6500 init success");

  // Servo 初期化
  servo.attach(SERVO_PIN);
  servo.write(90);
  delay(500);
}

// 加速度から roll（左右傾き）を計算（度）
float calcRollDeg(float ax, float ay, float az) {
  float roll = atan2f(ay, az) * 180.0f / PI;
  return roll;
}

void loop() {
  if (!imu.Read()) return;

  // 加速度 [m/s^2]
  float ax = imu.accel_x_mps2();
  float ay = imu.accel_y_mps2();
  float az = imu.accel_z_mps2();

  // 左右の傾き
  float rollDeg = calcRollDeg(ax, ay, az);
  rollDeg = clampf(rollDeg, -TILT_LIMIT_DEG, TILT_LIMIT_DEG);

  // roll(-45..+45) => servo(0..180)
  float targetDeg = (rollDeg + TILT_LIMIT_DEG) * (180.0f / (2.0f * TILT_LIMIT_DEG));

  // サーボの安全域へ
  targetDeg = clampf(targetDeg, SERVO_MIN, SERVO_MAX);

  // ローパスで揺れ軽減
  filteredDeg = (1.0f - alpha) * filteredDeg + alpha * targetDeg;

  servo.write((int)filteredDeg);

  // デバッグ表示
  Serial.print("rollDeg=");
  Serial.print(rollDeg, 2);
  Serial.print(" servo=");
  Serial.println((int)filteredDeg);

  delay(10);
}
