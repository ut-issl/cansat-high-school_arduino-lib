#include <CanSatSchool.h>

// マイクの出力ピンを指定
#define PIN_MIC A2

// マイクを宣言
Microphone microphone(PIN_MIC);

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    Computer::init(9600);

    // Wire (Arduino-I2C) を初期化
    // マイクは I2C を使用するためこれが必要
    Wire.begin();

    // マイクを初期化
    microphone.init();

    delay(500);
}

void loop()
{
    // マイクの値を取得してシリアルモニタに表示
    print(microphone.read());

    // マイクの値を取得して変数に代入したい場合
    // int mic_value = microphone.read();

    // 1s 待つ
    delay(1000);
}