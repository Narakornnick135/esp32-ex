#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <EEPROM.h>

// กำหนดค่าสำหรับ WiFi AP
const char *ssid = "ESP32-Config";
const char *ssidpassword = "12345678";

// กำหนดขนาดของ EEPROM ที่จะใช้
const int EEPROM_SIZE = 512;

// ตำแหน่งเริ่มต้นของแต่ละข้อมูลใน EEPROM
const int ADDR_WIFI_SSID = 0;
const int ADDR_WIFI_PASS = 32; // สมมติว่า SSID ยาวสูงสุด 31 ตัวอักษร + null terminator
const int ADDR_MQTT_USER = 96;
const int ADDR_MQTT_PASS = 128;
const int ADDR_MQTT_BROKER = 160; // แต่ละข้อมูลห่างกัน 32 ตัวอักษร

// สร้างออบเจกต์ของ AsyncWebServer
AsyncWebServer server(80);


void writeString(int addr, String value) {
  for (int i = 0; i < value.length(); i++) {
    EEPROM.write(addr + i, value[i]);
  }
  EEPROM.write(addr + value.length(), '\0'); // สิ้นสุด string
  EEPROM.commit();
}

String readString(int addr) {
  String value;
  char ch;
  while ((ch = EEPROM.read(addr++)) != '\0' && addr < EEPROM_SIZE) {
    value += ch;
  }
  return value;
}

void setup() {
  Serial.begin(115200);
  
  // เริ่มต้น SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // เริ่มต้น EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // ตั้งค่า ESP32 เป็น Access Point
  WiFi.softAP(ssid, ssidpassword);
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());
  Serial.print("SSID : ");
  Serial.print(ssid);
  Serial.print(" Pass: ");
  Serial.println(ssidpassword);
   // เส้นทางสำหรับเสิร์ฟไฟล์ CSS
  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/bootstrap.min.css", "text/css");
  });

  // เส้นทางสำหรับเสิร์ฟไฟล์ JavaScript
  server.on("/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/bootstrap.bundle.min.js", "application/javascript");
  });
  // เส้นทางสำหรับ root หรือหน้าหลัก
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // เส้นทางสำหรับรับค่าจากฟอร์ม
  server.on("/submit", HTTP_GET, [](AsyncWebServerRequest *request){
    // รับค่าจาก TextBox และบันทึกลง EEPROM
    String ssid = request->getParam("ssid")->value();
    String password = request->getParam("password")->value();
    String mqttUser = request->getParam("mqttUser")->value();
    String mqttPass = request->getParam("mqttPass")->value();
    String mqttBroker = request->getParam("mqttBroker")->value();
    
    writeString(ADDR_WIFI_SSID, ssid);
    writeString(ADDR_WIFI_PASS, password);
    writeString(ADDR_MQTT_USER, mqttUser);
    writeString(ADDR_MQTT_PASS, mqttPass);
    writeString(ADDR_MQTT_BROKER, mqttBroker);
    Serial.println("Save To EEPROM");
    request->send(200, "text/plain", "Settings Saved. Please reset the device.");
  });

  // เริ่มต้นเว็บเซิร์ฟเวอร์
  server.begin();
  Serial.println(readString(ADDR_WIFI_SSID));
  Serial.println(readString(ADDR_WIFI_PASS));
  Serial.println(readString(ADDR_MQTT_USER));
  Serial.println(readString(ADDR_MQTT_PASS));
  Serial.println(readString(ADDR_MQTT_BROKER));

}


void loop() {
  // ไม่มีการดำเนินการใน loop
}
