// IRremote v4


#include <Arduino.h>
#include <IRremote.hpp>

const uint8_t IR_RECEIVE_PIN = 11;

void printButtonName(uint32_t command, bool isRepeat) {
  if (isRepeat) {
    Serial.println("REPEAT");
    return;
  }

  switch (command) {
    case 0x45: Serial.println("POWER"); break;
    case 0x47: Serial.println("FUNC/STOP"); break;
    case 0x46: Serial.println("VOL+"); break;
    case 0x44: Serial.println("FAST BACK"); break;
    case 0x40: Serial.println("PAUSE"); break;
    case 0x43: Serial.println("FAST FORWARD"); break;
    case 0x07: Serial.println("DOWN"); break;
    case 0x15: Serial.println("VOL-"); break;
    case 0x09: Serial.println("UP"); break;
    case 0x16: Serial.println("EQ"); break;
    case 0x19: Serial.println("ST/REPT"); break;
    case 0x0D: Serial.println("0"); break;
    case 0x0C: Serial.println("1"); break;
    case 0x18: Serial.println("2"); break;
    case 0x5E: Serial.println("3"); break;
    case 0x08: Serial.println("4"); break;
    case 0x1C: Serial.println("5"); break;
    case 0x5A: Serial.println("6"); break;
    case 0x42: Serial.println("7"); break;
    case 0x52: Serial.println("8"); break;
    case 0x4A: Serial.println("9"); break;

    default:
      Serial.print("OTHER command=0x");
      Serial.println(command, HEX);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println("IR Receiver Button Decode (IRremote v4)");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // 受信開始
}

void loop() {
  if (IrReceiver.decode()) {
    // デバッグ表示（プロトコル/アドレス/コマンド等）
    // IrReceiver.printIRResultShort(&Serial); Serial.println();

    // NEC系だと「command」がボタンに対応しやすい
    uint32_t command = IrReceiver.decodedIRData.command;
    bool isRepeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

    printButtonName(command, isRepeat);

    IrReceiver.resume(); // 次の受信へ
    delay(200);          // 連打抑制（好みで調整）
  }
}
