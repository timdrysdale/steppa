![alt text][logo]

# steppa

Stepper motor test code for arduino with encoder input, neopixel indicator and limit switch


## Operation

The circuit has three modes
- stopped (four blue lights in centre of display)
- turning left (three red lights on left of display)
- turning right (three green lights on right of display)

The encoder position is automatically assumed to be centralised when you start the code. The motor is therefore off.

Turn the encoder to either side until either the display shows red or green lights. Return the encoder to central position to stop the motor (blue lights shown).
If the limit switch is triggered, the mode is set back to "stopped" but the motor can be engaged again by moving the encoder.

![alt text][operation]

### Caveats

It is possible to damage your equipment by setting the number of steps per revolution so high that the motor continues to run for a significant time after the microswitch is triggered (the limit switch is only checked every "steps per revolution").

Once the limit switch has triggered, you could damage your equipment by repeatedly driving it in the direction that forces it into the limit switch, as re-engerisation after the limit switch is permitted in this sketch, because it is intended for use in testing of stepper-motor based hardware where this may be necessary for hardware development purposes.

## Installation

- clone the repository

    ```
	git clone https://github.com/timdrysdale/steppa.git
	```


- open your arduino IDE
- create a new sketch
- add <wherever_you_cloned>/steppa/arduino/steppa.ino
- install the libraries if not already installed
    - Encoder by Paul Stoffregen (version 1.4.1)
	- Stepper (built-in) by Arduino (version 1.1.3)
	- Adafruit Neopixel by Adafruit (version 1.6.)
- select target destination and board
- upload sketch to your board


## Hardware

The hardware is currently:
- a strip of 10 RGB neopixels
- five-pin rotary encoder (using internal pullups)
- normally-closed microswitch
- L298N driver
- 2-phase stepper motor
- external power supply

# Notes

The stepper motor shown gets hot when driven with the L298N driver at 12V because this is in excess of the rated voltage for the motor. For such cases where the supply voltage to the driver chip exceeds the rated voltage, it is suggested to use a DRV8825-based driver circuit which has an adjustable current limiter to handle this scenario (sometimes called fast-stepping mode).

[logo]: ./img/boot-hat.png "boot and hat"
[operation]: ./img/operation.gif "operating the stepper with the encoder as control"	 

	 
		 