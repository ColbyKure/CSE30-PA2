/*
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function incrementClakcValue
 * Date: 5-2-18
 * Sources of Help: notes
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for incrementClockValue
 *
 * unsigned char incrementClockValue(unsigned char BCDbits, const unsigned int
 *    maxValue)
 *
 * The incrementClockValue function should increment the BCDbits value and 
 * return the result unless the result is over the maxValue in the case return
 * 0.
 *
 * Purpose: Tests incrementClockValue, make sure it resets to 0 when the value
 * is above the maxValue
 */
void testincrementClockValue() {
  unsigned char bits = 0x0;
  int max = 0;

  bits = 4;
  max = 9;
  TEST(incrementClockValue(bits, max) == 5);

  bits = 5;
  max = 10;
  TEST(incrementClockValue(bits, max) == 6);

  bits = 56;
  max = 79;
  TEST(incrementClockValue(bits, max) == 57);

  bits = 79;
  max = 56;
  TEST(incrementClockValue(bits, max) == 0);

  bits = 4;
  max = 3;
  TEST(incrementClockValue(bits, max) == 0);

  bits = 9;
  max = 9;
  TEST(incrementClockValue(bits, max) == 0);

  bits = 8;
  max = 9;
  TEST(incrementClockValue(bits, max) == 9);

  bits = 6;
  max = 1;
  TEST(incrementClockValue(bits, max) == 0);

  bits = 0;
  max = 0;
  TEST(incrementClockValue(bits, max) == 0);

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testincrementClockValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
