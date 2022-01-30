#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
#include <dht.h>  
// Set these to run example.
#define FIREBASE_HOST "login-5353c.firebaseio.com"
#define FIREBASE_AUTH "U5aBAvoXlABZCM3JThVb4drPH1XUbsV4KXjgUzwz"
#define WIFI_SSID "ilham"
#define WIFI_PASSWORD "ghtp6677"
dht DHT;
#define DHT11_PIN D4   


#define LED D1
void setup() {
Serial.begin(9600);
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
pinMode(LED, OUTPUT);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.setInt("Temperature", 0);
}
int n = 0;
void loop() {
  int chk = DHT.read11(DHT11_PIN);
  int t=DHT.temperature;
  int h=DHT.humidity;  
    if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  String fireTemp = String(t) + String("°C");
    Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("°C ");
Firebase.setString("Temperature",fireTemp);
delay(4000);

     if (Firebase.failed()) {

      Serial.print("pushing /logs failed:");

      Serial.println(Firebase.error()); 

      return;

  }
  n = Firebase.getInt("led");

if (n==1) {
Serial.println("LED ON");
digitalWrite(D1,HIGH);  
return;
//delay(10);
}
else {
Serial.println("LED OFF");
digitalWrite(D1,LOW);  
}

}
