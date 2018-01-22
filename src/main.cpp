#include <Arduino.h>

/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include <WiFi.h>

#include <main.h>
#include <oledconsole.h>

const unsigned char LED = 22;

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWD;

const char *udpAddress = "192.168.0.70";
const int udpPort = 1610;
WiFiUDP udp;

boolean connected = false;

OLEDConsole console;

//wifi event handler
void wifi_event(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        //When connected set
        Serial.printf("WiFi connected!\nIP address: %d.%d.%d.%d",
                      WiFi.localIP()[0],
                      WiFi.localIP()[1],
                      WiFi.localIP()[2],
                      WiFi.localIP()[3]);
        console.puts("WiFi connected\n");
        connected = true;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        //        console.puts("WiFi lost connection\n");
        connected = false;
        break;
    }
}

void connect_wifi(const char *ssid, const char *pwd)
{
    console.puts("Connecting: " + String(ssid) + "\n");

    // delete old config
    WiFi.disconnect(true);

    delay(1000);
    //register event handler
    WiFi.onEvent(wifi_event);

    //Initiate connection
    WiFi.begin(ssid, pwd);
}

void setup()
{
    // Set LED pin as an output.
    pinMode(LED, OUTPUT);

    console.init();

    Serial.begin(115200);

    connect_wifi(ssid, password);
}

void loop()
{
    while (true)
    {
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
        long uptime = millis() / 1000;
        if (connected)
        {
            //Send a packet
            //udp.beginPacket(udpAddress,udpPort);
            //udp.printf("Seconds since boot: %u", uptime);
            //udp.endPacket();
            console.puts((char *)("."));
        }
    }
}
