#define PIR_PIN 4
const int ledPin = 2;

bool pir;

void setup()
{
    Serial.begin(9600);
    delay(1500);
    pinMode(PIR_PIN, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    pir_sensor_getdata();
}

void pir_sensor_getdata()
{
    pir = digitalRead(PIR_PIN);
    if (pir == HIGH)
    {
        Serial.println("Human detected");
        for (int brightness = 0; brightness <= 255; brightness++)
        {
            analogWrite(ledPin, brightness);
            delay(10);
        }

        delay(1000);
    }
    else
    {
        Serial.println("Human not detected");
        analogWrite(ledPin, 0);
        delay(1000);
    }
}
