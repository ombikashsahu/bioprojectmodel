
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); //Defining rx and tx pins. 2 is rx pin and 3 is tx pin
const int trigPin = 6; //Defining trigger pin of Ultrasonic sensor
const int echoPin = 9; //Defining echo pin of ultrasonic sensor
const int buzzer = 7; //Defining buzzer pin
void setup() 
{

Serial.begin(9600); //Just for serial monitor output
mySerial.begin(9600);
  delay(1000);
pinMode(trigPin, OUTPUT); //Setting trigger pin as output pin
pinMode(echoPin, INPUT); //setting echo pin as input
pinMode (buzzer, OUTPUT); //Setting buzzer pin as output
}
long duration, distance; //Defining variables
void loop()
{
  updateSerial();
digitalWrite(trigPin, LOW); //Code for sending a pulse
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); //Code for catching the pulse
distance = duration/58.2; //finding distance using the duration of the pulse sent by trigger 
if(distance<20) // When distance of Obstacle is less than 20 cm 
{mySerial.println("AT+CMGF=1"); //Setting gsm module to calling mode
  updateSerial();

mySerial.println("ATDxxxxxxxxxx"); //setting number to call replace xx's with the number
  updateSerial();

digitalWrite(buzzer,LOW ); //Beep the buzzer
delay(2000); //buzzer beep 2 sec (2000 milliseconds)
}
else // When there is no obstacle 
{
digitalWrite(buzzer, HIGH); 
} 
// delay(100);
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}