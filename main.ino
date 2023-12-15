#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HTTPClient.h>

// Définition des broches pour le module MFRC522
#define SS_PIN D0
#define RST_PIN D1
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Définition des paramètres WiFi et de l'URL de l'API
String ssid;
String password;
String apiUrl = "http://badges-api.glitch.me";

void setup() {
  // Configuration des broches
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  Serial.begin(115200);
  delay(10);

  // Connexion au réseau WiFi
  Serial.println("veuillez renseigner le SSID du Wifi : ");
  while (Serial.available() <= 0) {
    if (Serial.available() > 0) {
      break;
    }  
  }
  // On récupère le SSID
  ssid = Serial.readStringUntil('\n');
  Serial.println(ssid);

  Serial.println("veuillez renseigner le mot de passe du Wifi : ");
    while (Serial.available() <= 0) {
    if (Serial.available() > 0) {
      break;
    }  
  }
  // On récupère le password
  password = Serial.readStringUntil('\n');
  Serial.println(password);

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
  Serial.println("Connecté");
  // Initialisation du module MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial(); // Affiche les informations sur le module RFID
}

void loop() {
  // Vérification de la présence d'une nouvelle carte RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Obtention de l'UID de la carte RFID
    String uid = getUID();
    Serial.println("UID de la carte: " + uid);

    // Validation de la carte RFID à l'aide de l'API
    if (validateCard(uid)) {
      // Accès autorisé
      Serial.println("Accès autorisé");
      digitalWrite(D3, LOW);
      digitalWrite(D2, HIGH);
      delay(3000);
      digitalWrite(D2, LOW);
    } else {
      // Accès refusé
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      Serial.println("Accès refusé");
      delay(3000);
      digitalWrite(D3, LOW);
    }

    delay(2000);
  }
}

// Fonction pour obtenir l'UID de la carte RFID
String getUID() {
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  return uid;
}

// Fonction pour valider la carte RFID à l'aide de l'API
bool validateCard(String uid) {
  HTTPClient http;

  // Construction de l'URL pour la validation de la carte RFID
  String url = apiUrl + "/validate/" + uid;
  http.begin(url);

  // Envoi de la requête HTTP GET à l'API
  int httpCode = http.GET();

  // Fermeture de la connexion HTTP
  http.end();

  // Retourne vrai si le code HTTP est 200 (OK)
  return httpCode == 200;
}