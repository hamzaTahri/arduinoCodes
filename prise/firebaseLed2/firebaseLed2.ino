
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Definimos la librerias par la conexion a nuestro servidor
#include "FirebaseESP8266.h"

// Definimos la direccion host de nuestro servidor
#define FIREBASE_HOST "controleled-bd17e.firebaseio.com"
// Definimos el token de nuestro servidor
#define FIREBASE_AUTH "iX9ZhnLmazX9nLRPjKjUstBEiPg35IWpuBcjP8z5"

// Definimos la conexion a punto de acceso wifi
#define WIFI_SSID "ilham"
#define WIFI_PASSWORD "ghtp66/77"

WiFiClient client;
FirebaseData firebaseData;

//definimos el pin para el led
#define LED D1

void setup() {
  Serial.begin(9600);

  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println ("");
  Serial.println ("Se conectó al wifi!");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(LED, OUTPUT);
}

void loop() {

  Firebase.getInt(firebaseData,"/led");
  int dato=firebaseData.intData();
  
  digitalWrite(LED,dato); 

  Serial.println(dato);

}
