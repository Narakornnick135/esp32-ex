#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80); // HTTP server on port 80

// HTML code for the webpage
const char* htmlPage =
  "<!DOCTYPE html>"
  "<html>"
  "<head><title>ESP32 Web Server</title></head>"
  "<body>"
  "<h1>Hello from ESP32!</h1>"
  "</body>"
  "</html>";

void handleRoot() {
  server.send(200, "text/html", htmlPage); // Send HTML page
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define endpoint
  server.on("/", handleRoot);

  // Start server
  server.begin();
}

void loop() {
  server.handleClient(); // Handle client requests
}

