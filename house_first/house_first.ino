
/************** Biblio ***************/
  #include <ESP8266WiFi.h>
  #include <FirebaseArduino.h>
  #include <ESP8266HTTPClient.h>
  #include <dht.h>  
  #include <SoftwareSerial.h>
  #include <Servo.h>    

  
/************** Firebase configuration ***************/
  #define FIREBASE_HOST "login-5353c.firebaseio.com"
  #define FIREBASE_AUTH "U5aBAvoXlABZCM3JThVb4drPH1XUbsV4KXjgUzwz"
  #define WIFI_SSID "ilham"
  #define WIFI_PASSWORD "ghtp6677"

/************** Pin ***************/
  SoftwareSerial mySerial(D0,D1);
  dht DHT;
  Servo servo_test;  
  #define DHT11_PIN D4   
  #define gaz_pin A0
  #define LED D9
  #define LED_2 D10
  #define LED_gaz D7
  #define mouvement D8
  #define servo D11
  #define venti D12
  int angle = 0;    
                

  
 void setup(){
  
    Serial.begin(9600);
/************** connection WIFI / connection firebase ***************/
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    //Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED){
      //Serial.print(".");
      delay(500);
      pinMode(LED, OUTPUT);
      pinMode(LED_2, OUTPUT);
      pinMode(venti, OUTPUT);
      pinMode(LED_gaz, OUTPUT);
      pinMode(mouvement,INPUT);
      servo_test.attach(servo);   
    }
    //Serial.println();
    //Serial.print("connected: ");
    //Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    /*Firebase.setInt("Temperature", 0);
    Firebase.setInt("Gaz", 0);
    Firebase.setInt("Luminosite", 0);
    Firebase.setInt("led", 0);
    Firebase.setInt("Light", 0);
    //Firebase.setInt("Luminosite", 0);*/

 }
 int n = 0;
 int m = 0;
 int s = 0;
 void loop() {
  
/************** lecture Gaz + transmission firebase ***************/
    int gaz;
    gaz=analogRead(gaz_pin);
    String gaz_string = String(gaz) ;  
    Firebase.setString("Gaz",gaz_string);
    /*if(gaz>150){
        digitalWrite(LED_gaz,HIGH); 
        delay(10); 
        digitalWrite(LED_gaz,LOW);
        delay(10);  
     }else{
        digitalWrite(LED_gaz,LOW);  
        delay(10); 
     }*/
    
/************** lecture Temp et Humidity + transmission firebase  ***************/  
    int chk = DHT.read11(DHT11_PIN);
    int t=DHT.temperature;
    int h=DHT.humidity;  
    if (isnan(h) || isnan(t)) {                                                
     // Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } 
    String fireTemp = String(t) ;
    //Serial.print("%  Temperature: ");  
    //Serial.print(t);  
    //Serial.println("°C ");
    Firebase.setString("Temperature",fireTemp);
    //delay(1000);
    
/************** lecture luminosité + transmission firebase ***************/  
     char c;
     int a= random(0, 1023);
     String lum = String(a) ;
       Firebase.setString("Luminosite",lum); 
       delay(5000);
       /*if (a < 10) {
          Serial.println(" - Noir");
      } else if (a < 200) {
          Serial.println(" - Sombre");
      } else if (a < 500) {
          Serial.println(" - Lumiere");
      } else if (a < 800) {
          Serial.println(" - Lumineux");
      } else {
          Serial.println(" - Tres lumineux");
      }*/
   /*if(mySerial.available()){
       c=mySerial.read();
         String lum = String(c) ;
         mySerial.print(lum);*/
       //Firebase.setString("Luminosite",c); 
/************** Controle Raspberry ***************/  
      while(Serial.available()>0){
         c=Serial.read();
         Serial.println(c);
         /**** Mouvement ****/
         if(c=='1'){
                 for(int j=0; j<10; j++){
                  digitalWrite(LED_gaz,HIGH); 
                  digitalWrite(LED,HIGH);
                  digitalWrite(LED_2,HIGH);
                  delay(100); 
                  digitalWrite(LED_gaz,LOW); 
                  digitalWrite(LED_2,LOW);
                  digitalWrite(LED,LOW);
                  delay(100); 
                }
         }
          /**** Gaz ****/
         if(c=='2'){
                  for(int j=0; j<10; j++){
                  digitalWrite(LED_gaz,HIGH); 
                  digitalWrite(LED,HIGH);
                  digitalWrite(LED_2,HIGH);
                  delay(100); 
                  digitalWrite(LED_gaz,LOW); 
                  digitalWrite(LED_2,LOW);
                  digitalWrite(LED,LOW);
                  delay(100); 
                  } 
            }
      
      
      
          /**** Temp ****/
        if(c=='3'){
          digitalWrite(venti,HIGH);     
        }
      /**** Lummiere ****/
        if(c=='4'){
             digitalWrite(LED_2,HIGH); 
             digitalWrite(LED,HIGH);
          
      }
      }
       
   
/************** detection mouvement + transmission firebase ***************/  
    String Mouv="1";
    String NoMouv="0";
    if(digitalRead(mouvement)==HIGH){
        //Serial.println("mouvement detecte");
        Firebase.setString("Mouvement",Mouv); 
    }else{
      // Serial.println("pas de mouvement detecte");
       Firebase.setString("Mouvement",NoMouv); 
    }
   
/************** failed firebase  ***************/ 
    if (Firebase.failed()) {
      // Serial.print("pushing /logs failed:");
       //Serial.println(Firebase.error()); 
       return;
     }
      if(gaz>200){
        digitalWrite(LED_gaz,HIGH); 
        delay(1000); 
        digitalWrite(LED_gaz,LOW); 
        delay(1000);
      }else{
        digitalWrite(LED_gaz,LOW);  
        delay(1000); 
      }
/************** controle light 1 firebase ***************/       
   n = Firebase.getInt("led");
   if (n==1) {
      Serial.println("LED ON");
      digitalWrite(LED,HIGH);  
    }else {
      Serial.println("LED OFF");
      digitalWrite(LED,LOW);  
    }
/************** controle light 2 firebase ***************/       
   m = Firebase.getInt("Light");
   if(m==1) {
      //Serial.println("LED ON");
      digitalWrite(LED_2,HIGH);  
    }else {
      //Serial.println("LED OFF");
      digitalWrite(LED_2,LOW);  
    }
 /************** controle store firebase ***************/       
  /* s = Firebase.getInt("door");
   if (s==1) {
      for(angle = 0; angle < 180; angle += 1){                                  
        servo_test.write(angle);                 
        delay(15);                       
      }  
    }else {
       for(angle = 180; angle>=1; angle-=5){                                
          servo_test.write(angle);              
          delay(15);                      
        } 

    }*/
    //s = Firebase.getInt("door");
     
        //digitalWrite(venti,HIGH);   
        //delay(2000); 
        //digitalWrite(venti,LOW);  

 }
 

 
