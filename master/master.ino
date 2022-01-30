#include <SoftwareSerial.h>
SoftwareSerial mySerial(D0,D1);
void setup() {
//pinMode(D13, OUTPUT);
mySerial.begin(9600);
}

void loop() {
  char c;
  if(mySerial.available()){
    c=mySerial.read();
     mySerial.print(c); 
     
  
    /*if(c=='A'){
      c++;
      mySerial.print(c); 
    }
    if(c=='B'){
      mySerial.print(c);  
    }*/
  }
  

}
