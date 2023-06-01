/**********************************************************************************
 11-11.io Sensor Connector ·  אש  نار · 
 by Riccardo Mantelli for UniverseEverywhere Ltd · London UK
 **********************************************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <WebSocketsClient_Generic.h>
#include <SocketIOclient_Generic.h>
#include <Hash.h>

#define Declination -0.00669
#define hmc5883l_address 0x1E

ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

IPAddress serverIP(192, 168, 43, 2);
uint16_t serverPort = 3000;
StaticJsonDocument<200> doc;
int flame = 0;

void socketIOEvent(socketIOmessageType_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case sIOtype_DISCONNECT:
      Serial.println("[IOc] Disconnected");
      break;
    case sIOtype_CONNECT:
      Serial.print("[IOc] Connected to URL: ");
      Serial.println((char*) payload);

      socketIO.send(sIOtype_CONNECT, "/");

      break;
    case sIOtype_EVENT:
      Serial.print("[IOc] Get event: ");
      Serial.println((char*) payload);

      break;
    case sIOtype_ACK:
      Serial.print("[IOc] Get ack: ");
      Serial.println(length);

      hexdump(payload, length);
      break;
    case sIOtype_ERROR:
      Serial.print("[IOc] Get error: ");
      Serial.println(length);

      hexdump(payload, length);
      break;
    case sIOtype_BINARY_EVENT:
      Serial.print("[IOc] Get binary: ");
      Serial.println(length);

      hexdump(payload, length);
      break;
    case sIOtype_BINARY_ACK:
      Serial.print("[IOc] Get binary ack: ");
      Serial.println(length);

      hexdump(payload, length);
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.print("\nStart ESP8266_WebSocketClientSocketIO on ");
  Serial.println(ARDUINO_BOARD);
  Serial.println(WEBSOCKETS_GENERIC_VERSION);

  if (WiFi.getMode() & WIFI_AP) {
    WiFi.softAPdisconnect(true);
  }

  WiFiMulti.addAP("11-11", "universe111");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.print("WebSockets Client started @ IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Connecting to WebSockets Server @ IP address: ");
  Serial.print(serverIP);
  Serial.print(", port: ");
  Serial.println(serverPort);

  socketIO.setReconnectInterval(10000);
  socketIO.setExtraHeaders("Authorization: 1234567890");
  socketIO.begin(serverIP, serverPort);
  socketIO.onEvent(socketIOEvent);
}

unsigned long messageTimestamp = 0;

void loop() {
  socketIO.loop();

  uint64_t now = millis();

  if (now - messageTimestamp > 200) {
    messageTimestamp = now;

    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    Serial.print("Flame : ");
    flame = map(analogRead(0), 0, 1024, 1024, 0);
    Serial.println(flame);
    array.add("flame");
    JsonObject param1 = array.createNestedObject();
    param1["intensity"] = flame;

    String output;
    serializeJson(doc, output);

    socketIO.send
