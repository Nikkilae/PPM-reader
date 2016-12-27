InterruptHandler
===========

An object-oriented interrupt handler library for the Arduino. Instead of the
simple C function pointer used by the built-in [attachInterrupt()](https://www.arduino.cc/en/Reference/AttachInterrupt)
function, it uses a pure C++ virtual method as a callback. This
allows for a cleaner more object oriented design, which is especially useful for
libraries. The performance should be on par with the built-in version of
[attachInterrupt()](https://www.arduino.cc/en/Reference/AttachInterrupt),
because it is based on an only slightly modified version of the original
Arduino source code.

Usage
-----

The usage is very simple. You just inherit from
the class InterruptHandler and implement the method handleInterrupt(). 

```cpp
#include <InterruptHandler.h>

// Inherit from InterruptHandler
class MyLib : InterruptHandler {
  byte inputPin;
  unsigned long localState1;
  unsigned long localState2;

public:
  MyLib(byte inputPin) : inputPin(pin) {}
  
  void begin() {
    pinMode(inputPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(inputPin), CHANGE);
  }

  void stop() {
    detachInterrupt(digitalPinToInterrupt(inputPin));
  }

  // Overwrite handleInterrupt() method
  virtual void handleInterrupt(int8_t interruptNum) {
    // Do something
    localState1 = digitalRead(inputPin);
    // ...
  }
};
```