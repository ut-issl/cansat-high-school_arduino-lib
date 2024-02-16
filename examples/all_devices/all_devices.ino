#include <CanSatHighSchool.h>

uint16_t loop_count = 0;

void setup()
{
    // Wire(Arduino-I2C)の初期化
    Wire.begin();
    // デバック用シリアル通信は9600bps
    Serial.begin(9600);

    SD_Init();    // これは絶対最初に初期化！
    CAM2_Init();  // SDの後！
    BTH_Init();
    DCM_Init();
    IMU_Init();
    LIT_Init();
    SRV_Init();
    GPS_Init();
    MIC_Init();
    XBEE_Init();

    Serial.println(F("Init done"));
    delay(300);
}

void loop()
{
    IMU_UpdateAll();
    IMU_PrintAcc();
    IMU_PrintGyr();
    IMU_PrintMag();
    GPS_Update();
    GPS_Print();
    LIT_Print();
    BTH_Update();
    BTH_Print();
    MIC_Print();
    XBEE_Test();

    if (loop_count % 10 == 3) {
        CAM2_TakePic();
    }
    SD_Write(String(loop_count));

    Serial.println(loop_count);
    if (loop_count % 10 == 0) {
        Serial.println(F("Move Up!"));
        for (uint8_t pos = 0; pos <= 180; pos = pos + 30) {
            Serial.print(F("pos:"));
            Serial.println(pos);
            SRV_SetPosition(pos);
            SRV_Run();
            delay(500);
        }
    }
    if (loop_count % 10 == 5) {
        Serial.println(F("Move Down!"));
        for (uint8_t pos = 180; pos > 0; --pos) {
            Serial.print(F("pos:"));
            Serial.println(pos);
            SRV_SetPosition(pos);
            SRV_Run();
            delay(20);
        }
    }

    // DCは一旦含んでいない（基本的に使わないと考えているため）

    loop_count++;
    delay(1000);
}
