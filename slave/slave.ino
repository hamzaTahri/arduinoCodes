#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
String val1="valeur 1";
String val2="valeur 2";
void setup() {
mySerial.begin(9600);
}

void loop() {
      int chambre_1_lumiere = analogRead(A0);
      int chambre_2_lumiere = analogRead(A1);
      
      mySerial.println(chambre_1_lumiere);
      delay(5000);
      //mySerial.println(chambre_2_lumiere);
      //delay(5000);
  
  
 /* mySerial.print("\n");
  mySerial.print("B\n");
  mySerial.print(chambre_1_lumiere);
  mySerial.print("\n");*/

}
