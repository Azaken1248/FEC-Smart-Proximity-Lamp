#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <BH1750.h>
#include <Wire.h>
#include <SPI.h>

// Firebase Configurations
#define WIFI_SSID "Azaken's Galaxy A50"
#define WIFI_PASSWORD "rgtm4117"
#define API_KEY "oZfDIpwkxS1GyTPAIlmSgmlFX8QYJGaVkJKhvqFr"
#define DATABASE_URL "https://esp32-fb-a24cd-default-rtdb.firebaseio.com/"

// Luminosity Sensor
BH1750 lightMeter(0x23);
int externalBrightness = 0;

// PIR Sensor
#define PIR_PIN 4
#define ledPin 2
bool pir;

FirebaseData fbdo;
int brightness;
bool ledStatus = false;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Initialize Firebase
    Firebase.begin(DATABASE_URL, API_KEY);

    // Initialize BH1750 sensor
    Wire.begin();
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        Serial.println(F("BH1750 Advanced begin"));
    }
    else
    {
        Serial.println(F("Error initializing BH1750"));
    }

    // Setup PIR sensor
    pinMode(PIR_PIN, INPUT);
    pinMode(ledPin, OUTPUT);

    // Set Firebase parameters
    Firebase.setInt(fbdo, "/brightness", brightness);
    Firebase.setBool(fbdo, "/ledStatus", ledStatus);
}

void loop()
{
    // Read luminosity level
    if (lightMeter.measurementReady())
    {
        externalBrightness = (int)lightMeter.readLightLevel();
        Serial.println("Measurement Ready!");
        Serial.print("External Brightness: ");
    }

    Serial.println(externalBrightness);

    // Check PIR sensor
    pir = digitalRead(PIR_PIN);
    if (pir == HIGH)
    {
        // Human detected
        Serial.println("Human detected");

        // Adjust LED brightness
        brightness = externalBrightness + 60;
        Serial.print("Brightness: ");
        Serial.println(brightness);
        for (int i = 0; i <= brightness; i++)
        {
            analogWrite(ledPin, i);
            delay(10);
        }

        // Update LED status and brightness to Firebase
        ledStatus = true;
        Firebase.setInt(fbdo, "/brightness", brightness);
        Firebase.setBool(fbdo, "/ledStatus", ledStatus);

        delay(20000); // Wait for 20 seconds
    }
    else
    {
        // No human detected
        Serial.println("Human not detected");

        // Turn off LED
        analogWrite(ledPin, 0);

        // Update LED status to Firebase
        ledStatus = false;
        Firebase.setBool(fbdo, "/ledStatus", ledStatus);

        delay(1000);
    }
}
