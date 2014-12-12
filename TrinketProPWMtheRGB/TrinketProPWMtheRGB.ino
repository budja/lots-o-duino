
boolean fadeRed = false;
boolean fadeGreen = false;
boolean fadeBlue = false;

int redPin = 1;
int greenPin = 0;
int bluePin = 4;

void setup() {
  randomSeed(analogRead(1));
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  fadeRed = false;
  fadeGreen = false;
  fadeBlue = false;
  if (random(0, 99) >= 50) fadeRed = true;
  if (random(0, 99) >= 50) fadeGreen = true;
  if (random(0, 99) >= 50) fadeBlue = true;

  digitalWrite(13, HIGH);
  
  // fade the LED on thisPin from off to brightest:
  for (int brightness = 0; brightness < 64; brightness++) {
    if (fadeRed) analogWrite(redPin, brightness);
    if (fadeGreen) analogWrite(greenPin, brightness);
    if (fadeBlue) analogWrite(bluePin, brightness);
    delay(10);
  } 

  digitalWrite(13, LOW);
  // fade the LED on thisPin from brithstest to off:
  for (int brightness = 64; brightness >= 0; brightness--) {
    if (fadeRed) analogWrite(redPin, brightness);
    if (fadeGreen) analogWrite(greenPin, brightness);
    if (fadeBlue) analogWrite(bluePin, brightness);
    delay(10);
  } 
  // pause between LEDs:
  delay(100);
}
