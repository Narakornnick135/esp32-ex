#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "5TH MEETING 03 (2.4G)"; // ชื่อ WiFi
const char* password = ""; // รหัสผ่าน WiFi
const char* mqtt_server = "smartgrid.cmru.ac.th"; // ที่อยู่ MQTT broker
const char* mqtt_user = "test";
const char* mqtt_pass = "test";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client",mqtt_user,mqtt_pass)) {
      Serial.println("connected");
      client.subscribe("your/topic"); // สมัครรับข้อมูลจาก topic ที่ต้องการ
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // ส่งข้อความไปยัง topic ที่กำหนด
  // client.publish("your/topic", "hello world");
}