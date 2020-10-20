
#include <Adafruit_NeoPixel.h>
#include <Encoder.h>
#include <Stepper.h>
 
#define PIN      12
#define N_LEDS 14


// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knob(3, 4);
//   avoid using pins with LEDs attached


long knobPosition = 0;
long knobMax = 15;
long knobMin = -15;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t blue = strip.Color(0,0,255);

// Number of steps per output rotation
const int stepsPerRevolution = 50;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  strip.begin();
  Serial.begin(9600);
  // set the speed at 60 rpm:
  myStepper.setSpeed(1000);
  pinMode(2, INPUT_PULLUP); 
  Serial.println("Stepper tester:");
  
}
 
void loop() {
  //chase(strip.Color(255, 0, 0)); // Red
  //chase(strip.Color(0, 255, 0)); // Green
  //chase(strip.Color(0, 0, 255)); // Blue
  
  long newKnobPosition;
  newKnobPosition = knob.read();
  if (newKnobPosition > knobMax) {
      knob.write(knobMax);
      newKnobPosition = knobMax;    
  }
  if (newKnobPosition < knobMin) {
      knob.write(knobMin);
      newKnobPosition = knobMin; 
  }     
  if (newKnobPosition != knobPosition) {
    Serial.print("Knob = ");
    Serial.print(newKnobPosition);
    Serial.println();
    knobPosition = newKnobPosition;
    indicate(knobPosition);
  }

  
   Serial.println(digitalRead(2));
   if (digitalRead(2) == false) {
   if (knobPosition > 5) { 
   myStepper.step(stepsPerRevolution); 
   }
   if (knobPosition < -5) { 
   myStepper.step(-stepsPerRevolution); 
   }
   } else {
         knobPosition = 0;
         knob.write(0);
    indicate(knobPosition);
   }
  
}

static void indicate(long value) {
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i  , 0); // erase all pixels
  }
  Serial.println(value);
  if (value < -5) {
    Serial.println("green");
    strip.setPixelColor(0, green);
    strip.setPixelColor(1, green);
    strip.setPixelColor(2, green);
    
  } else if (value > 5) {
      Serial.println("red");
      strip.setPixelColor(7, red);
      strip.setPixelColor(8, red);
      strip.setPixelColor(9, red);
  } else {
      Serial.println("blue");
      strip.setPixelColor(3, blue);
      strip.setPixelColor(4, blue);
      strip.setPixelColor(5, blue);
      strip.setPixelColor(6, blue);
  }
  strip.show();
}
 
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(5);
  }
}
