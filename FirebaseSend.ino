#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Azaken's Galaxy A50"
#define WIFI_PASSWORD "rgtm4117"

#define API_KEY "oZfDIpwkxS1GyTPAIlmSgmlFX8QYJGaVkJKhvqFr"

#define DATABASE_URL "https://esp32-fb-a24cd-default-rtdb.firebaseio.com/"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

int a, b, x, y;

void setup()
{

    Serial.begin(115200);
    delay(2000);
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

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    config.api_key = API_KEY;

    config.database_url = DATABASE_URL;

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
    // otherwise the SSL connection will fail.
    //////////////////////////////////////////////////////////////////////////////////////////////

    Firebase.begin(DATABASE_URL, API_KEY);

    // Comment or pass false value when WiFi reconnection will control by your code or third party library
    // Firebase.reconnectWiFi(true);

    Firebase.setDoubleDigits(5);
}

void loop()
{

    x = random(0, 9);
    y = random(10, 19);

    if (Firebase.ready())
    {

        // Firebase.setInt(fbdo, main, 5);
        Firebase.setInt(fbdo, "/test/a", x);
        Firebase.setInt(fbdo, "/test/b", y);
        delay(200);

        Serial.printf("Get int a--  %s\n", Firebase.getInt(fbdo, "/test/a") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
        a = fbdo.to<int>();
        Serial.printf("Get int b--  %s\n", Firebase.getInt(fbdo, "/test/b") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
        b = fbdo.to<int>();

        Serial.println();
        Serial.print("a:");
        Serial.print(a);
        Serial.print("  b: ");
        Serial.print(b);

        Serial.println();
        Serial.println("------------------");
        Serial.println();

        delay(2500);
    }
}
