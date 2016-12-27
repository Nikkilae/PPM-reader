# PPM Reader for Arduino

PPM Reader is an interrupt based [pulse-position modulation](https://en.wikipedia.org/wiki/Pulse-position_modulation) (PPM) signal reading library for Arduino. Its purpose is to provide an easy to use, non-blocking solution for reading PPM signals from an RC receiver that is able to output channel data as PPM.

Using interrupts (instead of pulseIn or some equivalent) to detect pulses means that reading the signal can be done in a non-blocking way. This means that using PPM Reader doesn't significantly slow down your program's code and you can do any other timing sensitive processes in your program meanwhile reading the incoming PPM signals.

The library uses [zeitgeist87's InterruptHandler library](https://github.com/zeitgeist87/InterruptHandler) for object-oriented interrupt handling. A copy of a compatible version of the library is included in this repository.

## Usage

### Installation
Download the contents of this repository on your computer. Move the downloaded PPMReader and InterruptHandler directories in your Arduino library directory.

### Arduino setup and code

Connect your RC receiver's PPM pin to your Arduino board's digital pin. Make sure that you use a pin that supports interrupts. You can find information on that from the [Arduino language reference](https://www.arduino.cc/en/Reference/AttachInterrupt).

* Include the library PPMReader.h to your program. If you're using an older version of Arduino, you may also need to include InterruptHandler.h in your main program.
* Initialize a PPMReader object with its constructor `PPMReader(interruptPin, channelAmount);`.
* Read channel values from the PPMReader object's public methods
	* Use `latestValidChannelValue(channel, defaultValue)` to read the latest value for the channel that was considered valid (in between the predetermined minimum and maximum channel values).
	* Alternatively use `rawChannelValue(channel)` to read the latest raw (not necessarily valid) channel value. The contents of the raw channel values may differ depending on your RC setup. For example some RC devices may output "illegal" channel values in the case of signal loss or failure and so you may be able to detect the need for a failsafe procedure.

When referring to channel numbers in the above methods, note that channel numbers start from 1, not 0.

### Example Arduino sketch
```c++

#include <PPMReader.h>
// #include <InterruptHandler.h>   <-- You may need this on some versions of Arduino

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
int interruptPin = 3;
int channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Print latest valid values from all channels
    for (int channel = 1; channel <= channelAmount; ++channel) {
        unsigned long value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
    Serial.println();
}

```

### Fine tuning
The PPMReader class should work with default settings for many regular RC receivers that output PPM. The default settings are as follows (all of them represent time in microseconds):
* `minChannelValue = 1000` The minimum possible channel value. Should be lesser than maxChannelValue.
* `maxChannelValue = 2000` The maximum possible channel value. Should be greater than minChannelValue.
* `channelValueMaxError = 10` The maximum error in channel value to either direction for still considering the channel value as valid. This leeway is required because your PPM outputter may have tiny errors and also the Arduino board's refresh rate only allows a [limited resolution for timing functions](https://www.arduino.cc/en/Reference/Micros).
* `blankTime = 2100` The time between pulses that will be considered the end to a signal frame. This should be greater than maxChannelValue + channelValueMaxError.

You can modify any of the above settings directly from the PPMReader object. They are public unsigned long variables.

## Testing
The library has been tested and proven to work on the following setup:
* An Arduino Nano board
* FlySky FS-i6 transmitter with the FS-iA6B receiver
* Up to 6 channels

Please mention any issues, bugs or improvement ideas.