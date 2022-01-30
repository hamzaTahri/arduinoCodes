const int sensor=A0; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading
void setup()
{
pinMode(sensor,INPUT); // Configuring pin A1 as input
Serial.begin(9600);
}
void loop() 
{
vout=analogRead(sensor)*5./1023*100;
 vout = 5*vout/1023; //on calcule le voltage
float   temp = vout/0.01;
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(temp);
Serial.println();
Serial.println();
delay(1000); //Delay of 1 second for ease of viewing 
}
