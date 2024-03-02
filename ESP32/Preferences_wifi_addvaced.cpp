#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

Preferences preferences;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  preferences.begin("wifi-mqtt", false);
}

void loop() {
  if (stringComplete) {
    // แยกสตริงด้วย comma
    int firstCommaIndex = inputString.indexOf(',');
    int secondCommaIndex = inputString.indexOf(',', firstCommaIndex + 1);
    int thirdCommaIndex = inputString.indexOf(',', secondCommaIndex + 1);
    int fourthCommaIndex = inputString.indexOf(',', thirdCommaIndex + 1);

    String ssid = inputString.substring(0, firstCommaIndex);
    String password = inputString.substring(firstCommaIndex + 1, secondCommaIndex);
    String mqttUser = inputString.substring(secondCommaIndex + 1, thirdCommaIndex);
    String mqttPassword = inputString.substring(thirdCommaIndex + 1, fourthCommaIndex);
    String mqttBroker = inputString.substring(fourthCommaIndex + 1);

    // บันทึกค่าลงใน Preferences
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.putString("mqttUser", mqttUser);
    preferences.putString("mqttPassword", mqttPassword);
    preferences.putString("mqttBroker", mqttBroker);

    // แสดงค่าที่บันทึกไว้
    Serial.println("WiFi SSID: " + ssid + ", Password: " + password);
    Serial.println("MQTT User: " + mqttUser + ", Password: " + mqttPassword + ", Broker: " + mqttBroker);

    // เชื่อมต่อ WiFi
    connectToWifi(ssid, password);
    // connectToMQTT(mqttUser, mqttPassword, mqttBroker); // นี่เป็นฟังก์ชันที่คุณต้องเขียนขึ้นเองตาม library MQTT ที่คุณใช้

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void connectToWifi(String ssid, String password) {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected.");
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    // รวมสตริงเมื่อได้รับข้อมูล
    if (inChar == '\n') {
      stringComplete = true;
    } else if (inChar != '\r' && inChar != '\t') {
      inputString += inChar;
    }
  }
}
