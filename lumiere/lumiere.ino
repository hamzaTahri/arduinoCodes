/*
 * Code d'exemple pour une photorésistance.
 */

// Fonction setup(), appelée au démarrage de la carte Arduino
void setup() {

  // Initialise la communication avec le PC
  Serial.begin(9600);
}

// Fonction loop(), appelée continuellement en boucle tant que la carte Arduino est alimentée
void loop() {
  
  // Mesure la tension sur la broche A0
  int photocellReading = analogRead(A0);
  
  // Envoi la mesure au PC pour affichage et attends 250ms
  Serial.println(photocellReading);
  //delay(250);

  if (photocellReading < 10) {
    Serial.println(" - Noir");
  } else if (photocellReading < 200) {
    Serial.println(" - Sombre");
  } else if (photocellReading < 500) {
    Serial.println(" - Lumiere");
  } else if (photocellReading < 800) {
    Serial.println(" - Lumineux");
  } else {
    Serial.println(" - Tres lumineux");
  }
  delay(500);
}
