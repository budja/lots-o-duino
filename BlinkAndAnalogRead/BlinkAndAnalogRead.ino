/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 11 Dec 2014
 by Dave Anderson
 
 This example code is in the public domain.
 
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED

void setup() {
  Serial.begin(9600);
  Serial.println("BlinkAndAnalogRead sketch started");
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
}

int analogValue = 0;
int oldAnalogValue = 1;

void loop() {
  // read the value from the sensor:
  analogValue = analogRead(sensorPin);    
  if (analogValue != oldAnalogValue)
  {
    Serial.print("Analog value changed. New value is ");
    Serial.println(analogValue, DEC);
    oldAnalogValue = analogValue;
  }

  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(analogValue);          
  // turn the ledPin off:        
  digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(analogValue);                  
}
