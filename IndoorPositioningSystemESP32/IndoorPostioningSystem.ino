#include "WiFi.h"
#include <math.h>
const uint16_t port =8090;
const char * host = "HOST IP";
const char* ssid = "SSID";
const char* password =  "Password";

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
    Serial.println(WiFi.status());
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  }

void loop()
{
    Serial.println("scan start");
    int rssi;
    float dist;
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    String address;
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            address=WiFi.SSID(i);
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            rssi=WiFi.RSSI(i);
            dist=-47-rssi;     
            dist/=20;
            dist=pow(10,dist);
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
    Serial.println("Connected to server successful!");
    client.print(address);
    client.print(dist);
    Serial.println("Disconnecting...");
    client.stop();
        }
    }
    // Wait a bit before scanning again
    delay(5000);
}
