#include <InterruptHandler.h>

// Inherit from InterruptHandler
class ChangeCounter : InterruptHandler {
  byte inputPin;
  unsigned long riseCounter;
  unsigned long fallCounter;

public:
  ChangeCounter(byte pin) : riseCounter(0), fallCounter(0), inputPin(pin) {}
  
  void begin() {
    pinMode(inputPin, INPUT);
    riseCounter = 0;
    fallCounter = 0;
    attachInterrupt(digitalPinToInterrupt(inputPin), CHANGE);
  }

  void stop() {
    detachInterrupt(digitalPinToInterrupt(inputPin));
  }

  unsigned long getRises() {
    return riseCounter;
  }

  unsigned long getFalls() {
    return fallCounter;
  }

  // Overwrite handleInterrupt() method
  virtual void handleInterrupt(int8_t interruptNum) {
    if (digitalRead(inputPin))
      ++riseCounter;
    else
      ++fallCounter;
  }
};

ChangeCounter counter(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  counter.begin();
  delay(5000);
  counter.stop();

  Serial.println("");
  Serial.print("Rises: ");
  Serial.println(counter.getRises());
  Serial.print("Falls: ");
  Serial.println(counter.getFalls());
}
