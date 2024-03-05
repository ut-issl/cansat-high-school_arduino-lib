// ミッション例：高度30mで蓋を開け，着陸後に写真を撮る
// 使うデバイス：
// - 光センサ：放出されたかどうかを判断する（ピン A1）
// - 気圧・温湿度計：気圧を読んで高度を計算する（ピン A4, A5）
// - GPS：飛行地点や着陸地点を取得する（ピン 8）
// - サーボモーター：蓋を開ける（ピン 4）
// - カメラ：着陸地点で写真を撮る（ピン 7, 11, 12, 13, A4, A5）


#include <CanSatSchool.h>

#include "device.hpp"
#include "sequence.hpp"

void setup()
{
    // ロガーを初期化
    String file_name = "log.txt";  // 記録するファイル名
    logger.enableSDCard(file_name, PIN_SD_SS);
    // logger.setDebug();

    // Wire (Arduino-I2C) を初期化
    Wire.begin();
    // SPI を初期化
    SPI.begin();

    initDevice();
}

void loop()
{
    static unsigned long last_time_ms = 0;
    unsigned long current_time_ms = millis();

    // 2000ms ごとに commonTask を実行する
    unsigned long interval_ms = 2000;
    if (current_time_ms - last_time_ms > interval_ms) {
        commonTask();
        last_time_ms = current_time_ms;
    }

    // ミッションのフェーズによってタスクを実行する
    switch (phase) {
        case LOADING:
            loadingTask();
            break;
        case LAUNCHING:
            launchingTask();
            break;
        case DESCENDING:
            descendingTask();
            break;
        case LANDED:
            landedTask();
            break;
        case FINISHED:
            // 何もしない
            break;
    }
}
