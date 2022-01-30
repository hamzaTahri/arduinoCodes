#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
#include <dht.h>                                                            // dht11 temperature and humidity sensor library
#define FIREBASE_HOST "arduinowemos-78d68.firebaseio.com"
#define FIREBASE_AUTH "cgnrFOExLGRaLfCjhhmRnGhz5wEw6F7ZNgyV69AS"
#define WIFI_SSID "ilham"
#define WIFI_PASSWORD "ghtp6677"                                 //password of wifi ssid

dht DHT;
#define DHT11_PIN D4                                                         // what digital pin we're connected to
//#define DHTTYPE DHT22                                                       // select dht type as DHT 11 or DHT22
//DHT dht(DHTPIN, DHTTYPE);                                                     

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

                           // connect to firebase
//  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  int chk = DHT.read11(DHT11_PIN);
  int t=DHT.temperature;
  int h=DHT.humidity;                                          // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t) + String("Â°C");                                                     //convert integer temperature to string temperature
  delay(4000);
  
  Firebase.pushString("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
  Firebase.pushString("/DHT11/Temperature", fireTemp);                                //setup path and send readings
   
}
