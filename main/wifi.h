#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "0x69 50 31 31 50 4D";
const char* password = "sv7gu4dy84rez";

String serverName = "http://172.104.196.152:3333/";

// FUNCTIONS
int generate();
void shoot(int id);
void reload(int id);

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

String post(String route, int id) {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName + route;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());

    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
    // Send HTTP GET request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    char str[80];
    sprintf(str, "id=%d", id);
    puts(str);
    int httpResponseCode = http.POST(str);
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      http.end();
      return payload;
    }
    else {
      http.end();
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      return "";
    }
  }
  else {
    Serial.println("WiFi Disconnected");
    return "";
  }
}

int generate() {
  String payload = post("generate_id", 0);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload.c_str());
  return doc["player"]["id"];;
}

void shoot(int id) {
  post("shoot", id);
}

void reload(int id) {
  post("reload", id);
}

#endif
