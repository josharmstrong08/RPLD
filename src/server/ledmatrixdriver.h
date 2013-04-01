/**
 *
 */

#ifndef LEDMATRIXDRIVER_H
#define LEDMATRIXDRIVER_H

#include "leddriver.h"
#include <stdint.h>

class LEDMatrixDriver : public LEDDriver {
public:
  virtual int OutputFrame(uint8_t (**frame)[3], unsigned long width, unsigned long height);

};

#endif
