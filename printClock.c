/*
 * Filename: printClock.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Contains function that prints out BCD clock
 * Date: May 07 2018
 * Sources of Help: piazza, lecture notes 
 */

#include <stdio.h>
#include "pa2.h"

/*
 * Function Name: printClock()
 * Function Prototype: void printClock(const unsigned char clock[]);
 * Description: This functin takes the values in clock[] and then it prints them
 *   out the time in a specified format.
 * Parameters: 
 *  arg 1 - clock - is an array of chars that contains the bits for time
 * Side Effects: prints out BCD clock to stdout
 * Error Conditions: none
 * Return Value: none
 */

void printClock(const unsigned char clock[]) {
  //print the top border
  for(int i = 0; i < CLOCK_WID; i++)
  {
    printf("%c", clock[AM_PM_INDEX]);
  }
  printf("\n"); // print newline

  //prep for printing middle section
  //extract nibbles
  unsigned char temp = clock[HR_INDEX];
  unsigned char hourT = temp >> NUM_BITS_IN_NIBBLE; //get hour_tens
  unsigned char hourO = temp & ONES_BITMASK; //get hour_ones
  
  temp = clock[MIN_INDEX];
  unsigned char minT = temp >> NUM_BITS_IN_NIBBLE; 
  unsigned char minO = temp & ONES_BITMASK;

  temp = clock[SEC_INDEX];
  unsigned char secT = temp >> NUM_BITS_IN_NIBBLE; 
  unsigned char secO = temp & ONES_BITMASK;

  //set new clock
  unsigned char BCDclock[TIME_NIBBLES] = {hourT, hourO, minT, minO, secT, 
    secO};

  //print bit section 
  for(int i = NUM_BITS_IN_NIBBLE; i > 0; i--) {
    //print side char
    if(isEven(i) == 1) {
      printf("%c ", CHAR_M); // space is added 
    }
    else {
      printf("%c ", clock[AM_PM_INDEX]); // space is added 
    }

    int shiftCount = i - 1;// setting bit we want to find as LSB
    for(int j = 0; j < TIME_NIBBLES; j++) {
      //print tens bit 
      temp = BCDclock[j];
      temp = temp >> shiftCount;
      if(isEven(temp) == 1) {
        printf("%c", CHAR_BIT_UNSET);
      }
      else {
        printf("%c", CHAR_BIT_SET);
      }

      j++; //INCREMENT COUNTER

      //print ones bit
      temp = BCDclock[j];
      temp = temp >> shiftCount;
      if(isEven(temp) == 1) {
        printf("%c", CHAR_BIT_UNSET);
      }
      else {
        printf("%c", CHAR_BIT_SET);
      }
      printf(" "); // print whitespace
    }//end print inside of row

    //print side char again
    if(isEven(i) == 1) { //i is even?
      printf("%c ", CHAR_M); // space is added 
    }
    else {
      printf("%c ", clock[AM_PM_INDEX]); // space is added 
    } 
    printf("\n"); // print newline
  }//end print bit section

  //print decimal row 
  printf("%c ", CHAR_M); //space added
  for(int i = 0; i < TIME_NIBBLES; i++) {
    printf("%d", BCDclock[i]);
    if(isEven(i) == 0) {//i is odd?
      printf(" ");//print whitespace on odd index
    }
  }
  printf("%c", CHAR_M); //print end-side of border
  printf("\n"); // print newline

  //print bottom border
  for(int i = 0; i < CLOCK_WID; i++)
  {
    printf("%c", clock[AM_PM_INDEX]);
  }
  printf("\n"); // print newline
  printf("\n"); // print newline
  return;
}


















