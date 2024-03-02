
#include <ArduinoJson.h>

float globalHumidity = 0.0;
float globalTemperature = 0.0;

// ฟังก์ชันส่งข้อมูล MQTT
void mqtt_publish(void * parameter) {
  for(;;) {
    if (!client.connected()) {
      // ถ้าไม่เชื่อมต่อ MQTT ก็เชื่อมต่อ
    }
    client.loop();

    // สร้าง JSON object
    StaticJsonDocument<200> doc;
    doc["temperature"] = globalTemperature;
    doc["humidity"] = globalHumidity;
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer); // แปลงข้อมูลเป็น JSON string

    client.publish("esp/dht22", jsonBuffer); // ส่ง JSON ผ่าน MQTT

    vTaskDelay(10000 / portTICK_PERIOD_MS); // รอ 10 วินาที
  }
}

// ฟังก์ชันอ่านข้อมูลจาก DHT22
void readDHT(void * parameter) {
  for(;;) {
    globalHumidity = dht.readHumidity();
    globalTemperature = dht.readTemperature();

    vTaskDelay(5000 / portTICK_PERIOD_MS); // รอ 5 วินาที
  }
}
