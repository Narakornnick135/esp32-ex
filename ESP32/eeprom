#include <EEPROM.h>

// กำหนดขนาดของ EEPROM ที่จะใช้
const int EEPROM_SIZE = 512;

// ตำแหน่งเริ่มต้นของแต่ละข้อมูลใน EEPROM
const int ADDR_WIFI_SSID = 0;
const int ADDR_WIFI_PASS = 32; // สมมติว่า SSID ยาวสูงสุด 31 ตัวอักษร + null terminator
const int ADDR_MQTT_USER = 96;
const int ADDR_MQTT_PASS = 128;
const int ADDR_MQTT_BROKER = 160; // แต่ละข้อมูลห่างกัน 32 ตัวอักษร

void setup() {
  Serial.begin(115200);
  
  // เริ่มต้น EEPROM พร้อมขนาดที่กำหนด
  EEPROM.begin(EEPROM_SIZE);

  // เขียนข้อมูลลงใน EEPROM
  writeString(ADDR_WIFI_SSID, "yourSSID");
  writeString(ADDR_WIFI_PASS, "yourPassword");
  writeString(ADDR_MQTT_USER, "yourMQTTUsername");
  writeString(ADDR_MQTT_PASS, "yourMQTTPassword");
  writeString(ADDR_MQTT_BROKER, "yourMQTTBrokerAddress");

  // อ่านและแสดงข้อมูลจาก EEPROM
  Serial.println(readString(ADDR_WIFI_SSID));
  Serial.println(readString(ADDR_WIFI_PASS));
  Serial.println(readString(ADDR_MQTT_USER));
  Serial.println(readString(ADDR_MQTT_PASS));
  Serial.println(readString(ADDR_MQTT_BROKER));

  // อย่าลืมเรียก EEPROM.end() เมื่อคุณเสร็จสิ้นการใช้งาน EEPROM
  EEPROM.end();
}

void loop() {
  // ไม่มีการดำเนินการใน loop
}

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
