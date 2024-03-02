#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4     // หมายเลขพินที่เชื่อมต่อกับ DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // รอสักครู่ระหว่างการอ่านค่า
  delay(2000);

  // อ่านความชื้นและอุณหภูมิ
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // ตรวจสอบว่าการอ่านค่าสำเร็จหรือไม่
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // แสดงค่าอุณหภูมิและความชื้น
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
}


//   adafruit/Adafruit Unified Sensor
//   adafruit/DHT sensor library