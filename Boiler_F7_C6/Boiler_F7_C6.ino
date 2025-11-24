#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>

const char* ssid = "MIN";
const char* password = "123456789";
//const char* notifyToken = "qwyx8nQeJEPpEmO9dqldcoIHEK5x5SkhWGk4lLUVsbo";

#define LINE_TOKEN  "qwyx8nQeJEPpEmO9dqldcoIHEK5x5SkhWGk4lLUVsbo"

//const char* serverName = "notify-api.line.me";
//const int httpsPort = 443;

void setup() {
  Serial.begin(9600);
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

// กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  LINE.notify("Boiler Block C");



}

void loop() {
  int runMode = digitalRead(D0);
  int tempHigh = digitalRead(D1);
  int tempLow = digitalRead(D2);
  if (runMode == HIGH) {
    Serial.println("Boiler is on");
    sendLineNotify("Boiler is on");
  }
  if (tempLow == HIGH) {
    Serial.println("Boiler temperature is low");
    sendLineNotify("Boiler temperature is low");
  }
  if (tempHigh == HIGH) {
    Serial.println("Boiler temperature is high");
    sendLineNotify("Boiler temperature is high");
  }
  delay(1000);
}

void sendLineNotify(String message) {
  WiFiClientSecure client;
  if (!client.connect(serverName, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }
  String request = "POST /api/notify HTTP/1.1\r\n";
  request += "Host: notify-api.line.me\r\n";
  request += "Authorization: Bearer " + String(notifyToken) + "\r\n";
  request += "Content-Type: application/x-www-form-urlencoded\r\n";
  request += "Cache-Control: no-cache\r\n";
  request += "Content-Length: " + String(message.length()) + "\r\n\r\n";
  request += message;
  client.print(request);
  delay(500);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String response = client.readString();
  Serial.println(response);
}
