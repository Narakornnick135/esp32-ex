#include <Preferences.h>

Preferences preferences;

void setup() {
  Serial.begin(115200);

  // เริ่มต้นใช้งาน Preferences พร้อมชื่อ namespace ที่เป็นเอกลักษณ์
  preferences.begin("my-app", false);

  // เขียนค่าลงใน Preferences
  // ค่าที่เก็บสามารถเป็น int, float, double, bool, หรือ String
  int counter = preferences.getInt("counter", 0); // อ่านค่า counter ถ้าไม่มีให้เริ่มที่ 0
  counter++; // เพิ่มค่า counter
  preferences.putInt("counter", counter); // เขียนค่า counter กลับไปที่ Preferences
  Serial.print("Updated counter to: ");
  Serial.println(counter);

  // อ่านค่าจาก Preferences
  String ssid = preferences.getString("ssid", "defaultSSID"); // ตัวอย่างการอ่าน String
  Serial.print("SSID: ");
  Serial.println(ssid);

  // อย่าลืมปิดการใช้งาน Preferences เมื่อทำงานเสร็จ
  preferences.end();
}

void loop() {
  // โค้ดใน loop นี้ไม่ทำอะไร
}
