/*
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function interpretTime
 * Date: 5-2-18
 * Sources of Help: notes
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for interpretTime
 *
 * unsigned long interpretTime(struct tInfo * tInfoPtr, const char * time);
 *
 * The interpretTime function will take the time as a string and then populate
 * the tInfo struct with ints and a char.
 *
 * Purpose: Tests interpretTime function checks to see that input is parsed
 * correctly an that the error flags are correctly implemented.
 */
void testinterpretTime() {
  struct tInfo  tInfo;
  tInfo.tm_hour = -1;
  tInfo.tm_min = -1;
  tInfo.tm_sec = -1;
  tInfo.am_pm = 'a';
  char * time;
  long int mask = 0;

  time = "12:35:49A";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 12);
  TEST(tInfo.tm_min == 35);
  TEST(tInfo.tm_sec == 49);
  TEST(tInfo.am_pm == 'A');
  TEST(mask == 0);

  time = "11:45:06P";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 11);
  TEST(tInfo.tm_min == 45);
  TEST(tInfo.tm_sec == 6);
  TEST(tInfo.am_pm == 'P');
  TEST(mask == 0);

  time = "01:02:55A";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 1);
  TEST(tInfo.tm_min == 2);
  TEST(tInfo.tm_sec == 55);
  TEST(tInfo.am_pm == 'A');
  TEST(mask == 0);

  time = "1:2:40P";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 1);
  TEST(tInfo.tm_min == 2);
  TEST(tInfo.tm_sec == 40);
  TEST(tInfo.am_pm == 'P');
  TEST(mask == 0);

  time = "1234:99:67";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 1234);
  TEST(tInfo.tm_min == 99);
  TEST(tInfo.tm_sec == 67);
  TEST(mask == 0x5);

  time = "2:27:17";
  mask = interpretTime(&tInfo, time);
  TEST(tInfo.tm_hour == 2);
  TEST(tInfo.tm_min == 27);
  TEST(tInfo.tm_sec == 17);
  TEST(mask == 0x1);

  time = "6:51:12b";
  mask = interpretTime(&tInfo, time);
  TEST(mask == 0x1);
  
  time = "13:13:12b";
  mask = interpretTime(&tInfo, time);
  TEST(mask == 0x5);

  time = "6a:51:120b";
  mask = interpretTime(&tInfo, time);
  TEST(mask == 0x7);

  time = "1:1:1:1:1:1:1";
  mask = interpretTime(&tInfo, time);
  TEST(mask == 0x1);

  
}

int main( void ) {

  fprintf(stderr, "Running tests for interpretTime...\n");
  testinterpretTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
