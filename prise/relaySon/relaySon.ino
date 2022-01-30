// Programme du capteur de son
// Letmeknow.fr

const int capteur =D2;// pin connecté à la sortie digital du capteur
const int LED =D3;// pin connecté à la LED + resistance
const int relay=D0;

void setup()
{
   pinMode(capteur, INPUT);
   pinMode(LED, OUTPUT);
   pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}

void loop()
{
if(digitalRead(capteur)== HIGH )
   {
   digitalWrite(relay, HIGH);// Allumer la LED
   //delay(10);// Temps de traitement
   }
else
   {
   digitalWrite(relay, LOW);// Eteindre la LED
   //delay(10);// Temps de traitement
   }
}
