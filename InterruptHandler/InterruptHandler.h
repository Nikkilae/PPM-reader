/*
 * Copyright (C) 2015  Andreas Rohner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#elif defined(ENERGIA)
  #include "Energia.h"
#else
  #include "WProgram.h"
#endif

class InterruptHandler {
public:
  virtual void handleInterrupt(int8_t interruptNum) = 0;
  void attachInterrupt(int8_t interruptNum, uint8_t mode);
  void detachInterrupt(int8_t interruptNum);
};

#endif  /* INTERRUPTHANDLER_H */
