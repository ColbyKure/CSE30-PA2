/*
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function setClock.s
 * Date: 5-2-18
 * Sources of Help: notes
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for setClock.s
 *
 * void setClock( unsigned char clock[], const struct tInfo * tmPtr );
 *
 * The setClock function should set the Binary coded decimal values for the
 * time into our clock arrauy.
 *
 * Purpose: Tests our setClock implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testsetClock() {

  // Declare our struct tInfo to hold our times
  struct tInfo time;

  // Set the times to all 0 for a zeroed out test
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;
  time.am_pm = 'A'; 
  unsigned char clock [CLOCK_ARR_SIZE];
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  //(void)printf("  %x:%x:%x:%c\n", clock[0], clock[1], clock[2], clock[3]);
  TEST(clock[HR_INDEX] == 0 && clock[MIN_INDEX] == 0 && clock[SEC_INDEX] == 0 
       && clock[AM_PM_INDEX] == 'A');

  // Test some random times
  time.tm_sec = 50;
  time.tm_min = 23;
  time.tm_hour = 12;
  time.am_pm = 'P'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  //(void)printf("  %x:%x:%x:%c\n", clock[0], clock[1], clock[2], clock[3]);
  TEST(clock[HR_INDEX] == 0x12 && clock[MIN_INDEX] == 0x23 &&
      clock[SEC_INDEX] == 0x50 && clock[AM_PM_INDEX] == 'P');

  // Test some random times
  time.tm_sec = 32;
  time.tm_min = 9;
  time.tm_hour = 11;
  time.am_pm = 'A'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  //(void)printf("  %x:%x:%x:%c\n", clock[0], clock[1], clock[2], clock[3]);
  TEST(clock[HR_INDEX] == 0x11 && clock[MIN_INDEX] == 0x9 &&
      clock[SEC_INDEX] == 0x32 && clock[AM_PM_INDEX] == 'A');

  /*
   * YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */

  time.tm_sec = 99;
  time.tm_min = 99;
  time.tm_hour = 99;
  time.am_pm = 'P'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  (void)printf("  %x:%x:%x:%c\n", clock[0], clock[1], clock[2], clock[3]);
  TEST(clock[HR_INDEX] == 0x99 && clock[MIN_INDEX] == 0x99 &&
      clock[SEC_INDEX] == 0x99 && clock[AM_PM_INDEX] == 'P');

  time.tm_sec = 11;
  time.tm_min = 11;
  time.tm_hour = 11;
  time.am_pm = 'P'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  //(void)printf("  %x:%x:%x:%c\n", clock[0], clock[1], clock[2], clock[3]);
  TEST(clock[HR_INDEX] == 0x11 && clock[MIN_INDEX] == 0x11 &&
      clock[SEC_INDEX] == 0x11 && clock[AM_PM_INDEX] == 'P');

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testsetClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
