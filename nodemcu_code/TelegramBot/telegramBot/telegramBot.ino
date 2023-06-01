#include <SimpleDHT.h>
#include "CTBot.h"

CTBot myBot;
SimpleDHT11 dht11;
const String SSID = "nome_rete";
const String PASSWORD = "password_rete";
const String TOKEN = "token_bot";
String mssg;

#define PIN_DHT11 4

void setup() {
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
  
  myBot.wifiConnect(SSID, PASSWORD);
  myBot.setTelegramToken(TOKEN);
  
  if (myBot.testConnection()) {
    Serial.println("\ntestConnection OK");
  } else {
    Serial.println("\ntestConnection NOK");
  }
}

void loop() {
  TBMessage msg;
  byte temperature = 0;
  byte humidity = 0;
  
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(PIN_DHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }
  
  if (CTBotMessageText == myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("TEMP")) {
      mssg = "Temperatura: " + String(temperature);
      myBot.sendMessage(msg.sender.id, mssg);
    } else if (msg.text.equalsIgnoreCase("HUMID")) {
      mssg = "Umidità: " + String(humidity);
      myBot.sendMessage(msg.sender.id, mssg);
    } else if (msg.text.equalsIgnoreCase("DOOR")) {
      mssg = "Apertura Porta";
      myBot.sendMessage(msg.sender.id, mssg);
    } else {
      String reply = "Welcome to 11-11.io Telegram Server > Torino";
      myBot.sendMessage(msg.sender.id, reply);
    }
  }
  
  delay(500);
}
