int led_pin=13;
int analog_pin=A0;

void setup() {

Serial.begin(9600);

pinMode(led_pin, OUTPUT);

}

void loop() {

  int temp;
  
  temp=analogRead(analog_pin);
  Serial.println(temp);
  
  if(temp>512){

    Serial.println("« dangerous!! »");
    digitalWrite(led_pin,HIGH);
    delay(1000);
    digitalWrite(led_pin,LOW);
    delay(1000);

  }else{
    Serial.println("« No dangerous! »");
    digitalWrite(led_pin,LOW);
    delay(1000);

  }

}
