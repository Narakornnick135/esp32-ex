#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

void handleRoot() {
  server.send(SPIFFS, "/index.html", "text/html");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void handleToggleLED() {
  // Add your code to toggle an LED here
  Serial.println("LED Toggled");
  server.send(200, "text/plain", "Toggled LED");
}

void setup() {
  Serial.begin(115200);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/script.js", HTTP_GET, []() {
    server.send(SPIFFS, "/script.js", "application/javascript");
  });
  server.on("/toggle-led", HTTP_GET, handleToggleLED);

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop() {
  server.handleClient();
}
