#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"

Adafruit_MPU6050 m_p_u;

void setup()
{
  Serial.begin(115200);

  while (!Serial)
    Serial.println("Establishing Connection!");
  delay(20);

  if (!m_p_u.begin())
  {
    while (1)
    {
      Serial.println("Initializing MPU!");
      delay(20);
    }
  }
}

void loop()
{
  sensors_event_t acc, gcc, temp;
  m_p_u.getEvent(&acc, &gcc, &temp);
  Serial.println("Acceleration on x axis");
  Serial.println(acc.acceleration.x);
  Serial.println("Acceleration on y axis");
  Serial.println(acc.acceleration.y);
  Serial.println("Acceleration on z axis");
  Serial.println(acc.acceleration.z);
  delay(10);
}
