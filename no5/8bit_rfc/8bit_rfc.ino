#include <LedControl.h>

// (DIN, CLK, CS, 接続しているMAX7219の数)
LedControl lc = LedControl(11, 13, 12, 1);

void setup() {
   Serial.begin(9600); // ← デバッグ用
  // 0番目のMAX7219を起動
  lc.shutdown(0, false);

  // 明るさ設定（0～15）
  lc.setIntensity(0, 5);

  // 表示クリア
  lc.clearDisplay(0);
  printf("init");
}

void loop() {
  Serial.println("LED ON");
  printf("a");
  // 1行ずつ点灯
  for (int row = 0; row < 8; row++) {
    printf(row);
    lc.setRow(0, row, B11111111); // 横一列点灯
    delay(1000);
    lc.clearDisplay(0);
    delay(1000);
  }

  delay(500);
}
