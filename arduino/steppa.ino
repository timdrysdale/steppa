// AccelStepper - Version: 1.61.0
#include <AccelStepper.h>
#include <MultiStepper.h>


#include <Adafruit_NeoPixel.h>
#include <Encoder.h>
#include <Stepper.h>
 
#define PIN      12
#define N_LEDS 3

#define dirPin 6
#define stepPin 5
#define stepSpeed 500
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


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



void setup() {
  strip.begin();
  Serial.begin(9600);
  // set the speed at 60 rpm:
  pinMode(2, INPUT_PULLUP); 
  Serial.println("Stepper tester:");
  stepper.setMaxSpeed(1000);
  
}
 
void loop() {

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

   if (knobPosition > 5) { 
     // Set the speed in steps per second:
    stepper.setSpeed(stepSpeed);
    // Step the motor with a constant speed as set by setSpeed():
    stepper.runSpeed();
   }
   if (knobPosition < -5) { 
        if (digitalRead(2) == false) {
        // Set the speed in steps per second:
      stepper.setSpeed(-stepSpeed);
      // Step the motor with a constant speed as set by setSpeed():
      stepper.runSpeed();
   } else {
         knobPosition = 0;
         knob.write(0);
         stepper.stop();
    indicate(knobPosition);
   }
     
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

  } else if (value > 5) {
      Serial.println("red");
      strip.setPixelColor(2, red);
  } else {
      Serial.println("blue");
      strip.setPixelColor(1, blue);
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

static void step(int count) {
  
  
}
