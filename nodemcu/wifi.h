#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";

String serverName = "http://172.104.196.152:3333/";

// FUNCTIONS
int generate();
int shoot(int id);
int reload(int id);

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
  return doc["player"]["id"];
}

int shoot(int id) {
  String payload = post("shoot", id);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload.c_str());
  return doc["ammo"];
}

int reload(int id) {
  String payload = post("reload", id);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload.c_str());
  return doc["ammo"];
}

void alive(int id) {
  post("alive", id);
}
void dead(int id) {
  post("dead", id);
}

#endif
