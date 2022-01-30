
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
  #define WIFI_SSID "AndroidAP"
  #define WIFI_PASSWORD "poiq9088"

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
  #define servo D13
  #define venti D12
  int angle = 0;    
                

  
 void setup(){
  
    Serial.begin(9600);
/************** connection WIFI / connection firebase ***************/
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      pinMode(LED, OUTPUT);
      pinMode(LED_2, OUTPUT);
      pinMode(venti, OUTPUT);
      pinMode(LED_gaz, OUTPUT);
      pinMode(mouvement,INPUT);
      servo_test.attach(servo);   
    }  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
 }
 int n = 0;
 int m = 0;
 int s = 0;
 int v = 0 ; 
 
 void loop() {
  
/************** lecture Gaz + transmission firebase ***************/
    int gaz;
    gaz=analogRead(gaz_pin);
    String gaz_string = String(gaz) ;  
    Firebase.setString("Gaz",gaz_string);
    delay(1000);
/************** lecture Temp et Humidity + transmission firebase  ***************/  
    int chk = DHT.read11(DHT11_PIN);
    int t=DHT.temperature;
    int h=DHT.humidity;  
    String fireTemp = String(t) ;
    Firebase.setString("Temperature",fireTemp);
    delay(1000);
/************** lecture luminosité + transmission firebase ***************/  
     int lumiere= random(0, 1023);
     String lum = String(lumiere) ;
     Firebase.setString("Luminosite",lum); 
     delay(1000);
/************** detection mouvement + transmission firebase ***************/  
    String Mouv="1";
    String NoMouv="0";
    if(digitalRead(mouvement)==HIGH){
        Firebase.setString("Mouvement",Mouv); 
    }else{
       Firebase.setString("Mouvement",NoMouv); 
    }
/************** controle light 1 firebase ***************/       
   n = Firebase.getInt("led");
   if (n==1) {
      digitalWrite(LED,HIGH);  
    }else {
      digitalWrite(LED,LOW);  
    }
/************** controle light 2 firebase ***************/       
   m = Firebase.getInt("Light");
   if(m==1) {
      digitalWrite(LED_2,HIGH);  
    }else {
      digitalWrite(LED_2,LOW);  
    }
/************** door firebase  ***************/
   s = Firebase.getInt("door");
   if (s==1){                                   
        servo_test.write(180);                 
    }else{
        servo_test.write(0);                 
    }
/************** venti Firebase  ***************/
   v = Firebase.getInt("ventilation");
   if(v==1) {
      digitalWrite(venti,HIGH);  
    }else {
      digitalWrite(venti,LOW);  
    }
/************** Controle Raspberry ***************/
      char c;  
      while(Serial.available()>0){
         c=Serial.read();
         Serial.println(c);
          /**** Gaz ****/
         if(c=='g'){
                  for(int j=0; j<15; j++){
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
        if(c=='t'){
            digitalWrite(venti,HIGH);
             
        }
      /**** Lummiere ****/
        if(c=='l'){
             digitalWrite(LED_2,HIGH); 
             digitalWrite(LED,HIGH);
             digitalWrite(LED_gaz,HIGH);
             
          
        }
        /******** Assistante vocale********/
        if(c=='a'){
            digitalWrite(LED_2,HIGH);
            Firebase.set("Light",1); 
            
            
        }
        if(c=='b'){
            digitalWrite(LED_2,LOW);
            Firebase.set("Light",0); 
             
          
        }
         if(c=='c'){
          
            digitalWrite(LED,HIGH); 
            Firebase.set("led",1);
          
                      
        }
         if(c=='d'){

            digitalWrite(LED,LOW);
            Firebase.set("led",0);
 
                      
        }
        if(c=='e'){
              digitalWrite(venti,HIGH); 
              Firebase.set("ventilation",1);
              
         
                      
        }
      }
      
 /************** Send data to Raspberry ***************/ 
   Serial.print("<");
   Serial.print(t);
   Serial.print(",");
   Serial.print(gaz);
   Serial.print(",");
   Serial.print(lumiere);
   Serial.println(">");
   delay(10000);

 }
 

 
