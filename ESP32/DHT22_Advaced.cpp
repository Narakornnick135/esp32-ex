#include <Arduino.h>
#include <DHT.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <PubSubClient.h>
#include <WiFi.h>

#define DHTPIN 4     // พินที่เชื่อมต่อ DHT22
#define DHTTYPE DHT22   // ใช้ DHT22
DHT dht(DHTPIN, DHTTYPE);

// ข้อมูลสำหรับเชื่อมต่อ WiFi และ MQTT
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.mqtt.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ฟังก์ชันเชื่อมต่อ WiFi
void setup_wifi() {
  delay(10);
  // เชื่อมต่อ WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// ฟังก์ชันส่งข้อมูล MQTT
void mqtt_publish(void * parameter) {
  for(;;) { // loop forever
    if (!client.connected()) {
      // ถ้าไม่เชื่อมต่อ MQTT ก็เชื่อมต่อ
    }
    client.loop();

    // ส่งข้อมูลที่นี่
    client.publish("esp/test", "Hello from ESP32");

    vTaskDelay(10000 / portTICK_PERIOD_MS); // รอ 10 วินาที
  }
}

// ฟังก์ชันอ่านข้อมูลจาก DHT22
void readDHT(void * parameter) {
  for(;;) { // loop forever
    // อ่านค่าจาก DHT22
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // ทำการจัดเก็บข้อมูลที่นี่

    vTaskDelay(5000 / portTICK_PERIOD_MS); // รอ 5 วินาที
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();

  // สร้าง tasks
  xTaskCreate(mqtt_publish, "MQTT Publish", 10000, NULL, 1, NULL);
  xTaskCreate(readDHT, "Read DHT", 10000, NULL, 1, NULL);
}

void loop() {
  // ใน freeRTOS, loop นี้จะไม่ถูกใช้งาน
}
