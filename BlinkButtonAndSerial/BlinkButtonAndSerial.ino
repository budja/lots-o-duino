/*
  Blink and Button
  Turns on an LED on for one second, then off for one second, repeatedly.
  If the button on the Screw Shield is pressed, the blink rate changes to
  four times per second.
  When the button changes state, send a message about it to the serial
  port

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

    modified 11 Dec 2014
    by Dave Anderson
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize the serial port to run at 9600 bits per second
  Serial.begin(9600);
  Serial.println("BlinkButtonAndSerial sketch started");
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(A5, INPUT_PULLUP);
}

int buttonLowBlinkDelay = 250;
int buttonHighBlinkDelay = 1000;
int delayTime;
int buttonState = HIGH;
int oldButtonState = LOW;

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(A5);
  if (buttonState == LOW) delayTime = buttonLowBlinkDelay;
  else delayTime = buttonHighBlinkDelay;
  if (buttonState != oldButtonState)
  {
    Serial.print("Button state changed. New state is ");
    if (buttonState == LOW) Serial.println("LOW");
    else Serial.println("HIGH");
    oldButtonState = buttonState;
  }
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delayTime);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(delayTime);              // wait for a second
}
