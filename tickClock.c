/*
 * Filename: tickClock.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: file holds the tickClock function
 * Date: May 02 2018
 * Sources of Help: notes
 */

#include "pa2.h"
#include <stdio.h>

/*
 * Function Name: tickClock()
 * Function Prototype: void tickClock(unsigned char clock[]);
 * Description: ticks the clock by one second 
 * Parameters: 
 *    char clock[] - char array that holds the time
 * Side Effects: none 
 * Error Conditions: none
 * Return Value: none
 */

void tickClock(unsigned char clock[]) {
  // local variables 
  unsigned char temp;
  unsigned char tens;
  unsigned char ones;
  int flag = 0;

  //get the 8 bits for sec
  temp = clock[SEC_INDEX];
  tens = temp & TENS_BITMASK; //extract upper nibble with bitmask
  tens = tens >> NUM_BITS_IN_NIBBLE; //shift right to align the LSB to end
  ones = temp & ONES_BITMASK; //extract lower nibble with bitmask

  ones = incrementClockValue(ones, MAX_ONES_SEC);
  if(ones == 0) { //if was 9 before increment
    tens = incrementClockValue(tens, MAX_TENS_SEC); //increment upper
    flag = 1; //set flag for incrementing upper nibble
  }
  //rebuild full 8 bits and store result back into clock
  tens = tens << NUM_BITS_IN_NIBBLE;
  temp = tens | ones; 
  clock[SEC_INDEX] = temp;
  
  //now check if we need to increment the minutes 
  if(tens == 0 && flag == 1) {
    flag = 0; //reset flag
    //get the 8 bits for min
    temp = clock[MIN_INDEX];
    tens = temp & TENS_BITMASK;
    tens = tens >> NUM_BITS_IN_NIBBLE;
    ones = temp & ONES_BITMASK;

    ones = incrementClockValue(ones, MAX_ONES_MIN);
    if(ones == 0) {
      tens = incrementClockValue(tens, MAX_TENS_MIN);
      flag = 1; //set flag
    }
    //rebuild byte and store
    tens = tens << NUM_BITS_IN_NIBBLE;
    temp = tens | ones;
    clock[MIN_INDEX] = temp;
  }

  //now check if we need to increment hours
  if(tens == 0 && flag == 1) {
    flag = 0; //reset flag
    //get 8 bits for hour
    temp = clock[HR_INDEX];
    tens = temp & TENS_BITMASK;
    tens = tens >> NUM_BITS_IN_NIBBLE;
    ones = temp & ONES_BITMASK;

    if(tens == 0) {
      ones = incrementClockValue(ones, MAX_ONES_HR);
      if(ones == 0) {
        tens = incrementClockValue(tens, MAX_TENS_HR);
      }
    } 
    else if(tens == MAX_TENS_HR){
      ones = incrementClockValue(ones, MAX_HR_ONES);
      if(ones == 0) {
        tens = incrementClockValue(tens, MAX_TENS_HR);
      }
      else if(ones == MAX_HR_ONES) {
        flag = 1;
      }
    }
    tens = tens << NUM_BITS_IN_NIBBLE;
    temp = tens | ones;
    clock[HR_INDEX] = temp;
    if(flag == 1) {
      if(clock[AM_PM_INDEX] == AM_CHAR) {
        clock[AM_PM_INDEX] = PM_CHAR;
      }
      else {
        clock[AM_PM_INDEX] = AM_CHAR;
      }
    }
  }
}
