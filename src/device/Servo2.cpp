#include "./Servo2.h"

#include "./Servo.h"


Servo_t servo2;

void SRV2_Init()
{
    servo2.position = 0;
    servo2.setPosition = 1;  // servo2.setPosition = 0 にするとサーボが振動してしまうため1で初期化している

    servo2.servo.attach(PIN_SRV2);
    delay(1000);
    SRV2_Run();

    // Serial.println(F("SRV2 init done"));
    Serial.println(F("SRV2 init done"));
}

void SRV2_SetPosition(uint8_t pos)
{
    servo2.setPosition = pos;
}

uint8_t SRV2_GetPosition()
{
    return servo2.position;
}

void SRV2_Run()
{
    servo2.servo.write(servo2.setPosition);
    servo2.position = servo2.setPosition;
}
