#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

int httpResponseCode;
String data = "";
enum WiFi_States {WiFi_Init, WiFi_Wait, WiFi_Shoot, WiFi_Reload};

extern int id;
extern bool shoot;
extern bool reload;

void wifi_setup() {
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    WiFiClient client;
    HTTPClient http;
    // Generate ID for blaster
    String serverPath = "http://172.104.196.152:3333/generate_id";
    http.begin(client, serverPath.c_str());
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpResponseCode = http.POST(data);
    if(httpResponseCode<0) {
        Serial.print("Error: COULD NOT GET ID!\n");
    }
    else {
        String payload = http.getString();
        Serial.println(payload);
        // ASSIGN ID HERE
    }
    http.end();
}

int WiFi_TickFct(int state) {
    if(WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        switch(state) {
            case WiFi_Init:
                state = WiFi_Wait;
                break;
            case WiFi_Wait:
                if(shoot) state = WiFi_Shoot;
                if(reload) state = WiFi_Reload;
                break;
            case WiFi_Shoot:
                state = WiFi_Wait;
                break;
            case WiFi_Reload:
                state = WiFi_Wait;
                break;
            default:
                state = WiFi_Init;
                break;
        }
        switch(state) {
            case WiFi_Init:
            case WiFi_Wait:
                break;
            case WiFi_Shoot:
                String shootPath = "http://172.104.196.152:3333/shoot?"; // FIXME: How to write path?
                http.begin(client, shootPath.c_str());
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                httpResponseCode = http.POST(data);
                if(httpResponseCode<0) {
                    Serial.print("ERROR: COULD NOT SHOOT");
                }
                break;
            case WiFi_Reload:
                String shootPath = "http://172.104.196.152:3333/reload?"; // FIXME: How to write path?
                http.begin(client, shootPath.c_str());
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                httpResponseCode = http.POST(data);
                if(httpResponseCode<0) {
                    Serial.print("ERROR: COULD NOT RELOAD");
                }
                break;
            default:
                break;
        }
    }
    else {
        Serial.print("ERROR: Lost connection?");
    }
    return state;
}

#endif // __WIFI_H__
