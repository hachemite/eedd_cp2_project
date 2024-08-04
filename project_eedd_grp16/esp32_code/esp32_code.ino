//Pour Esp32:
//Inclusion des bibliothèques et déclaration des variables :
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
int buzz = 33;
const char* ssid = "wifi";
const char* password = "12345678";
#define BOTtoken "6998168290:AAF2mn_4x7hnRg31aqpRE1L7QVUzZGDAdGE"
#define CHAT_ID "1993600814"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 100;
unsigned long lastTimeBotRan;
#include <TinyGPS++.h>
#include <HardwareSerial.h>
HardwareSerial GPSSerial(1);
TinyGPSPlus gps;
// Inclusion des bibliothèques nécessaires pour la gestion du WiFi, la communication sécurisée,
//l'interaction avec Telegram, et le traitement des données GPS.
// Déclaration des constantes pour le nom du réseau WiFi, le mot de passe, le token du bot
//Telegram, et l'ID de chat Telegram.
// Déclaration des objets client pour la connexion sécurisée, bot pour le bot Telegram, et
//GPSSerial pour la communication série avec le GPS.

//Gestion des nouveaux messages Telegram :
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;
    while (GPSSerial.available()) {
      gps.encode(GPSSerial.read());
    }
    if (gps.charsProcessed() > 10) {
      float currentLat = gps.location.lat();
      float currentLng = gps.location.lng();


      if (text == "/start") {
        String control = "Bonjour, " + from_name + ".\n";
        control += "Utilisez les commandes ci-dessous pour surveiller la position GPS\n\n ";
        control += "/Localisation Pour connaître la position actuelle \n";
        bot.sendMessage(chat_id, control, "");
      }

      if (text == "/Localisation") {
        String Localisation = "Localisation : https://www.google.com/maps/@";
        Localisation += String(currentLat, 6);
        Localisation += ",";
        Localisation += String(currentLng, 6);
        Localisation += ",21z?entry=ttu";
        bot.sendMessage(chat_id,Localisation, "");
      }
    }
  }
}
// Fonction pour gérer les nouveaux messages reçus par le bot Telegram.
// Vérifie si le message provient de l'ID de chat autorisé.
// Si le message est "/start", envoie une réponse de bienvenue avec les commandes disponibles.
// Si le message est "/Localisation", envoie la localisation actuelle sous forme de lien Google
//Maps.
//Configuration initiale :
void setup() {
  Serial.begin(115200);
  GPSSerial.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
#ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
#endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}
Serial.begin(115200);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(23, INPUT_PULLUP);
pinMode(22, INPUT_PULLUP);
Serial.print("Connecting Wifi: ");
Serial.println(ssid);
pinMode(buzz, OUTPUT);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
bot.sendMessage(CHAT_ID, "Bot started up", "");
}
// Initialisation de la communication série pour le débogage et le module GPS.
// Connexion au réseau WiFi.
// Configuration des pins pour les entrées et sorties (buzzer et boutons).
// Envoi d'un message de démarrage via Telegram.
//Boucle principale :
void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  if (digitalRead(22) == 1) {
    digitalWrite(buzz, 1);
    delay(200);
    digitalWrite(buzz, 0);
    delay(200);
    digitalWrite(buzz, 1);
    delay(200);
    digitalWrite(buzz, 0);
    delay(200);
    digitalWrite(buzz, 1);
    delay(200);
    digitalWrite(buzz, 0);
    delay(200);
    bot.sendMessage(CHAT_ID, "Choque détectée", "");
  }
}