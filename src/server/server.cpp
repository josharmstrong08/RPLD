/**
 * server.cpp
 * Main entry point for the Raspberry Pi server.
 *
 * This program has the following responsibilities:
 *  - Listen for incoming TCP messages from the client
 *  - Drive the LED matrices
 */;

#include <stdlib.h>
#include "ledmatrixdriver.h"

/**
 * Main entry point for the server. 
 *
 */
int main(int argc, char **argv) {
  
  LEDMatrixDriver driver;
  driver.OutputFrame(NULL, 0, 0);

  return EXIT_SUCCESS;
}
