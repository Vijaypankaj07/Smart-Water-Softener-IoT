#include <WiFi.h>
#include <PubSubClient.h>

// ===============================
// WiFi Configuration
// ===============================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===============================
// MQTT Configuration
// ===============================
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "ecowell/watersoftener/data";
const char* control_topic = "ecowell/watersoftener/control";

WiFiClient espClient;
PubSubClient client(espClient);

// ===============================
// Sensor Variables
// ===============================
int flow;
int pressure;
int salt;
int tds;

bool powerStatus = true;
String regenStatus = "OFF";

// ===============================
// Device States
// ===============================
enum DeviceState {
  IDLE,
  MONITORING,
  REGENERATION_REQUIRED,
  REGENERATION_RUNNING,
  FAULT
};

DeviceState currentState = IDLE;

// ===============================
// MQTT Reconnect
// ===============================
void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting to MQTT... ");

    String clientId = "ESP32-";
    clientId += String(random(1000,9999));

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.subscribe(control_topic);
     Serial.println("Subscribed to Control Topic");
    }
    else {
      Serial.print("Failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Command Received: ");
  Serial.println(message);

  if (message == "START") {

    currentState = REGENERATION_RUNNING;
    regenStatus = "ON";

    Serial.println("Regeneration Started");

    delay(5000);   // Simulate regeneration

    currentState = MONITORING;
    regenStatus = "OFF";

    Serial.println("Regeneration Completed");
  }


}






// ===============================
// Setup
// ===============================
void setup() {

  Serial.begin(115200);

  Serial.println("================================");
  Serial.println(" Smart Water Softener");
  Serial.println("================================");

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

 client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);
}

// ===============================
// Loop
// ===============================
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // -------------------------
  // Simulate Sensors
  // -------------------------
  flow = random(0, 40);
  pressure = random(20, 80);
  salt = random(0, 100);
  tds = random(100, 700);

  // -------------------------
  // State Machine
  // -------------------------
  String stateText;
  String alert = "NORMAL";

  if (pressure < 25) {
    currentState = FAULT;
    stateText = "FAULT";
    alert = "LOW PRESSURE";
  }
  else if (flow == 0) {
    currentState = FAULT;
    stateText = "FAULT";
    alert = "NO WATER FLOW";
  }
  else if (salt < 20) {
    currentState = REGENERATION_REQUIRED;
    stateText = "REGENERATION_REQUIRED";
    alert = "LOW SALT";
  }
  else if (tds > 500) {
    currentState = REGENERATION_REQUIRED;
    stateText = "REGENERATION_REQUIRED";
    alert = "HIGH TDS";
  }
  else {
    currentState = MONITORING;
    stateText = "MONITORING";
    alert = "NORMAL";
  }

  // -------------------------
  // Display Sensor Values
  // -------------------------
  Serial.println("--------------------------------");

  Serial.print("Flow: ");
  Serial.print(flow);
  Serial.println(" L/min");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" PSI");

  Serial.print("Salt Level: ");
  Serial.print(salt);
  Serial.println(" %");

  Serial.print("TDS: ");
  Serial.print(tds);
  Serial.println(" ppm");

  Serial.print("Power Status: ");
  Serial.println(powerStatus ? "ON" : "OFF");

  Serial.print("Regeneration: ");
  Serial.println(regenStatus);

  Serial.print("State: ");
  Serial.println(stateText);

  Serial.print("Alert: ");
  Serial.println(alert);

  // -------------------------
  // MQTT Payload
  // -------------------------
  String payload =
"{"
"\"flow\":" + String(flow) +
",\"pressure\":" + String(pressure) +
",\"salt\":" + String(salt) +
",\"tds\":" + String(tds) +
",\"state\":\"" + stateText + "\"" +
",\"alert\":\"" + alert + "\"" +
",\"power\":\"" + String(powerStatus ? "ON" : "OFF") + "\"" +
"}";

  // -------------------------
  // Publish MQTT
  // -------------------------
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("MQTT Publish Success");
  } else {
    Serial.println("MQTT Publish Failed");
  }

  delay(3000);
}