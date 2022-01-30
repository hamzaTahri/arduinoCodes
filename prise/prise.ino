#include <ESP8266WiFi.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN D1
const char* ssid = "ilham";
const char* password = "ghtp66/77";
 
int ledPin = D0; 
WiFiServer server(80);
 
void setup() 
{
  // initialisation de la communication série
  Serial.begin(9600);
    //dht.begin();
  

  // initialisation de la sortie pour la led 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connexion wifi
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

  // connection  en cours ...
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }

  // Wifi connecter
  Serial.println("WiFi connecter");
 
  // Démmarrage du serveur.
  server.begin();
  Serial.println("Serveur demarrer !");
 
  // Affichage de l'adresse IP
  Serial.println("Utiliser cette adresse URL pour la connexion :");
  Serial.println("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  int chk = DHT.read11(DHT11_PIN);
  int t=DHT.temperature;
  int h=DHT.humidity;
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }



{
WiFiClient client;

  
  // Vérification si le client est connecter.
  client = server.available();
  if (!client)
  {
    return;
  }
 
  // Attendre si le client envoie des données ...
  Serial.println("nouveau client");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH); // allumer la led
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW); // éteindre la led
    value = LOW;
  }
 
  // Réponse
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Etat de la led : ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Allumer </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Eteindre </button></a><br />");  
  client.println("</html>");
  while(h!=0 && t!=0){
    client.print("Humidity: ");
   client.print(h);
  client.print(" %\t");
  client.print("Temperature: ");
  client.print(t);
  client.print(" .");
   delay(10000);
 


 
}
  Serial.println("Client deconnecter");
  Serial.println("");
}
}
