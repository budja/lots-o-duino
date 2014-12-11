#include <Adafruit_NeoPixel.h>

#define PIN 6  //pin for neopixel output
#define NAccumulate 10  //length of moving average
#define NPixels 60    //length of pixel string
/*Aleks Zosuls, Adafruit 2014. This code makes a bargraph intensity
meter based on the values of an analog input pin.
*/

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPixels, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
int analogPin = 3;  //analog input pin
int ADVal = 0;
float radAD = 0;
float accumulator[NAccumulate] = {0};
int i = 0;
float accumulate = 0;
int j =0;
int k = 0;
float avgVal;
float intensity;
int pixUp;

void setup() {
   Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
}

void loop() {
  
  //read ADC
  ADVal = analogRead(analogPin);    // read the input pin
  //set value in accumulator vector which is used to store moving avg
  accumulator[i] = ADVal;
  i = (i + 1) % NAccumulate;
  accumulate = 0;
  //sum all moving average values
 for(j=0; j< NAccumulate; j++)  {
   accumulate = accumulate + accumulator[j];
 }
 avgVal = accumulate/NAccumulate;
  //compute pixels scale to full range equals pi/2
  radAD = avgVal * 3.14 /(2* 1023);  
  //map values to a sin to approximate a log function
  intensity= sin(radAD);
  //scale to number of leds
  intensity = intensity * NPixels;
  pixUp = int(intensity);
  Serial.println(pixUp);
  
  //output pixels slots string into two colors one for the sub levels and 
  //one for supra values of threshold
  for(k=0; k<NPixels; k++) {
    if(k < pixUp) {
      strip.setPixelColor(k, strip.Color(50,0,0));
    }
    else {
     strip.setPixelColor(k, strip.Color(0,0,50)); 
  }
  }
   strip.show();
   
  // Some example procedures showing how to display to the pixels:
 //blinkk();
 //delay(random(400,5000));
  
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
 
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

 
  //theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
/*void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
*/
/*void blinkk(void)
{
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),sevenEigthOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),threeQuarterOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),halfOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),eyeClosed);
  delay(200);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),halfOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),threeQuarterOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),sevenEigthOpen);
  delay(20);
  eyelid(strip.Color(ledRed, ledGreen, ledBlue),wideOpen);
}
  
void eyelid(uint32_t colour, uint8_t lidState[]) {
  uint16_t i;
  
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, (colour * lidState[i]));
    }
    strip.show();
   
}


/*
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/
