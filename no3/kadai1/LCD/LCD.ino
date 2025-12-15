
#include <LiquidCrystal.h>

const int rs = 7, en = 8, d7 = 12, d6 = 11, d5 = 10, d4 = 9, d3 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte musictone[8] = { //♪記号
    B01100,
    B01010,
    B01001,
    B01001,
    B01010,
    B11000,
    B11000,
};

const uint8_t msg1[] = {
  0xB6, // ｶ
  0xDE, // ﾞ
  0xDD, // ﾝ
  0xCA, // ﾊ
  0xDE, // ﾞ
  0xD9, // ﾙ
  0xBF,  // ｿ
  0xDE // ﾞ

};
void printBytes(const uint8_t* s, size_t n) {
  for (size_t i = 0; i < n; i++) {
    lcd.write(s[i]);
  }
}
int mode = 0;

void setup() {
  lcd.begin(16, 2);
  // カスタム文字登録
  lcd.createChar(0, musictone);
}

void loop() {
  lcd.clear();
    lcd.setCursor(0, 0);
    printBytes(msg1, sizeof(msg1));
    lcd.print("!!!!");
    lcd.setCursor(1, 1);
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.write(byte(0));
    delay(3000); 
}