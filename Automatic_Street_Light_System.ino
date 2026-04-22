#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define LDR 34
#define LED 2

const char* ssid = "OnePlus Nord 4";
const char* password = "123451234";

#define BOTtoken "8597413112:AAFTOnWyHqGGKBsDgLFn8j0nAwAlahsVVCA";  //🔁 replace
#define CHAT_ID "1962596939";// 🔁 replace

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int threshold = 50;

bool lastState = false;   // Track previous LED state

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  
  client.setInsecure();  // Required for ESP32 HTTPS

  bot.sendMessage(CHAT_ID, "✅ ESP32 Connected & System Started", "");
}

void loop() {
  int ldrValue = analogRead(LDR);
  Serial.println(ldrValue);

  bool currentState;

  if (ldrValue < threshold) {
    digitalWrite(LED, HIGH);
    currentState = true;   // LED ON
  } else {
    digitalWrite(LED, LOW);
    currentState = false;  // LED OFF
  }

  // Send message ONLY when state changes
  if (currentState != lastState) {
    if (currentState) {
      bot.sendMessage(CHAT_ID, "🌙 LED turned ON (Dark)", "");
    } else {
      bot.sendMessage(CHAT_ID, "☀️ LED turned OFF (Light)", "");
    }
    lastState = currentState;
  }

  delay(1000);
}
