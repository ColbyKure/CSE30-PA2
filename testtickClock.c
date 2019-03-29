/*
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function tickClock
 * Date: 5-2-18
 * Sources of Help: notes
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for tickClock
 *
 * void tickClock(unsigned char clock[]);
 *
 * The tickClock increments the clock array by calling the incrementClockValue 
 * function and updates the values accordingly 
 *
 * Purpose: Tests tickClock to make sure that it correctly increments the next
 * value if need be.
 */
void testtickClock() {
  unsigned char clock[3];

  clock[0] = 0x1;
  clock[1] = 0x0;
  clock[2] = 0x0;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x1);
  TEST(clock[1] == 0x0);
  TEST(clock[2] == 0x1);
  TEST(clock[3] == 'A');

  clock[0] = 0x11;
  clock[1] = 0x59;
  clock[2] = 0x59;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x1);
  TEST(clock[1] == 0x0);
  TEST(clock[2] == 0x0);
  TEST(clock[3] == 'P');
  printf("%x:%x:%x%c\n\n", clock[0], clock[1], clock[2], clock[3]);

  clock[0] = 0x11;
  clock[1] = 0x59;
  clock[2] = 0x59;
  clock[3] = 'P';
  tickClock(clock);
  TEST(clock[0] == 0x1);
  TEST(clock[1] == 0x0);
  TEST(clock[2] == 0x0);
  TEST(clock[3] == 'A');
  printf("%x:%x:%x%c\n\n", clock[0], clock[1], clock[2], clock[3]);

  clock[0] = 0x5;
  clock[1] = 0x59;
  clock[2] = 0x40;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x5);
  TEST(clock[1] == 0x59);
  TEST(clock[2] == 0x41);
  TEST(clock[3] == 'A');

  clock[0] = 0x11;
  clock[1] = 0x59;
  clock[2] = 0x3;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x11);
  TEST(clock[1] == 0x59);
  TEST(clock[2] == 0x4);
  TEST(clock[3] == 'A');

  clock[0] = 0x3;
  clock[1] = 0x43;
  clock[2] = 0x29;
  clock[3] = 'P';
  tickClock(clock);
  TEST(clock[0] == 0x3);
  TEST(clock[1] == 0x43);
  TEST(clock[2] == 0x30);
  TEST(clock[3] == 'P');

  clock[0] = 0x4;
  clock[1] = 0x59;
  clock[2] = 0x59;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x5);
  TEST(clock[1] == 0x0);
  TEST(clock[2] == 0x0);
  TEST(clock[3] == 'A');

  clock[0] = 0x6;
  clock[1] = 0x39;
  clock[2] = 0x59;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x6);
  TEST(clock[1] == 0x40);
  TEST(clock[2] == 0x0);
  TEST(clock[3] == 'A');

  clock[0] = 0x4;
  clock[1] = 0x0;
  clock[2] = 0x0;
  clock[3] = 'P';
  tickClock(clock);
  TEST(clock[0] == 0x4);
  TEST(clock[1] == 0x0);
  TEST(clock[2] == 0x1);
  TEST(clock[3] == 'P');

  clock[0] = 0x1;
  clock[1] = 0x2;
  clock[2] = 0x3;
  clock[3] = 'A';
  tickClock(clock);
  TEST(clock[0] == 0x1);
  TEST(clock[1] == 0x2);
  TEST(clock[2] == 0x4);
  TEST(clock[3] == 'A');
}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
