#include <Arduino.h>
#include <IRremote.hpp>
#include <LedControl.h>

/*=======================表示パターン==========================*/
const byte PATTERN_0[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B00011000
};

const byte PATTERN_1[8] = {
  B00010000,
  B00110000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00111000
};

const byte PATTERN_2[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00000100,
  B00001000,
  B00010000,
  B00100100,
  B00111100
};

const byte PATTERN_3[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00000100,
  B00011000,
  B00000100,
  B00100100,
  B00011000
};

const byte PATTERN_4[8] = {
  B00000000,
  B00001000,
  B00011000,
  B00101000,
  B00101000,
  B00111100,
  B00001000,
  B00001000
};

const byte PATTERN_5[8] = {
  B00000000,
  B00111100,
  B00100000,
  B00111000,
  B00000100,
  B00000100,
  B00100100,
  B00011000
};

const byte PATTERN_6[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00100000,
  B00111000,
  B00100100,
  B00100100,
  B00011000
};

const byte PATTERN_7[8] = {
  B00000000,
  B00111100,
  B00100100,
  B00000100,
  B00001000,
  B00001000,
  B00010000,
  B00010000
};

const byte PATTERN_8[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00011000,
  B00100100,
  B00100100,
  B00011000
};


const byte PATTERN_9[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00011100,
  B00000100,
  B00100100,
  B00011000
};

const byte PATTERN_IN[8] = {
  B10000001,
  B01000010,
  B00111100,
  B01111110,
  B11011011,
  B01111110,
  B00100100,
  B11000011
};

/*==========================表示パターンここまで===============================*/

/* ========= ピン設定 ========= */
const uint8_t IR_RECEIVE_PIN = 11;

// MAX7219 (DIN, CLK, CS)
const uint8_t MAX_DIN = 12;
const uint8_t MAX_CLK = 10;
const uint8_t MAX_CS  = 9;
LedControl lc = LedControl(MAX_DIN, MAX_CLK, MAX_CS, 1);

// クリア
void clearDisplay() {
  lc.clearDisplay(0);
}


void showPattern(const byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]);
  }
}

void handleCommand(uint8_t command, bool isRepeat) {
  if (isRepeat) {
    // 長押し中
    Serial.println("REPEAT");
    return;
  }

  switch (command) {
    case 0x16: showPattern(PATTERN_0); Serial.println("0"); break;
    case 0x0C: showPattern(PATTERN_1); Serial.println("1"); break;
    case 0x18: showPattern(PATTERN_2); Serial.println("2"); break;
    case 0x5E: showPattern(PATTERN_3); Serial.println("3"); break;
    case 0x08: showPattern(PATTERN_4); Serial.println("4"); break;
    case 0x1C: showPattern(PATTERN_5); Serial.println("5"); break;
    case 0x5A: showPattern(PATTERN_6); Serial.println("6"); break;
    case 0x42: showPattern(PATTERN_7); Serial.println("7"); break;
    case 0x52: showPattern(PATTERN_8); Serial.println("8"); break;
    case 0x4A: showPattern(PATTERN_9); Serial.println("9"); break;

    // case 0x45: showText("PWR"); Serial.println("POWER"); break;
    // case 0x46: showText("VOL+"); Serial.println("VOL+"); break;
    // case 0x15: showText("VOL-"); Serial.println("VOL-"); break;
    // case 0x09: showText("UP");   Serial.println("UP"); break;
    // case 0x07: showText("DOWN"); Serial.println("DOWN"); break;
    // case 0x44: showText("BACK"); Serial.println("FAST BACK"); break;
    // case 0x43: showText("FWD");  Serial.println("FAST FORWARD"); break;
    // case 0x40: showText("PAUS"); Serial.println("PAUSE"); break;
    // case 0x47: showText("FUNC"); Serial.println("FUNC/STOP"); break;

    default:
      Serial.print("OTHER command=0x");
      Serial.println(command, HEX);
      showPattern(PATTERN_IN);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);

  // MAX7219初期化
  lc.shutdown(0, false);    // スリープ解除
  lc.setIntensity(0, 8);    // 明るさ
  lc.clearDisplay(0);

  Serial.println("IR + MAX7219 READY");

  // IR受信開始（v4系）
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {

    uint8_t command = IrReceiver.decodedIRData.command;
    bool isRepeat = (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT);

    handleCommand(command, isRepeat);

    IrReceiver.resume();
    delay(150); // チャタり防止（好みで調整）
  }
}

