/*
 * Filename: interpretTime.c
 * Author: Colby Kuew
 * Userid: cs30xdc
 * Description: file holding functino interpretTime
 * Date: May 02 2018
 * Sources of Help: notes
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "pa2.h"

/*
 * Function Name: interpretTime(0
 * Function Prototype: unsigned long interpretTime(struct tInfo * tInfoPtr,
 *    const char * time);
 * Description: function parses the time string and populates the tinfo struct
 * Parameters: 
 *    arg 1 - struct * tInfoPtr - pointer to tInfo struct
 *    arg 2 - char * time - string that contains time
 * Side Effects: set error flag in case of error 
 * Error Conditions: wrong number of separators or wrong format
 * Return Value: return 0 if no errors 
 */

unsigned long interpretTime(struct tInfo * tInfoPtr, const char * time) {
  unsigned long ret = 0x0;
  char timeArr[BUFSIZ];
  strncpy(timeArr, time, BUFSIZ);

  int counter = 0;
  for(int i = 0; i < BUFSIZ; i++) {
    if(timeArr[i] == CHAR_SEPARATOR) {
      counter++;
    }
    else if(timeArr[i] == '\0')
      break;
  }
  if(counter != REQ_SEPARATORS) {
    ret = ret | ERR_TIME_FORMAT;
    return ret;
  }

  //init variables to -1 for testing, should always be overwritten
  int sec;
  int min;
  int hour;
  char * endptr; 
  // get hour
  char * sepPtr = strchr(timeArr, CHAR_SEPARATOR);
  *sepPtr = '\0'; // replace ':' with null
  errno = 0;
  hour = strtol(timeArr, &endptr, BASE); // get hour integer
  if(*endptr != '\0') {
    ret = ret | ERR_TIME_NUM;
  }

  // get min
  endptr = sepPtr + 1; // align endptr to next char
  sepPtr = strchr(endptr, CHAR_SEPARATOR);
  *sepPtr = '\0'; // replace ':' with null
  errno = 0;
  min = strtol(endptr, &endptr, BASE); // get min
  if(*endptr != '\0') {
    ret = ret | ERR_TIME_NUM;
  }

  //get sec
  endptr = endptr + 1;  // align endptr to next char 
  errno = 0;
  sec = strtol(endptr, &endptr, BASE);

  //get and set am/pm
  if(strlen(endptr) != AM_PM_LENGTH) {
    ret = ret | ERR_TIME_FORMAT; //too many chars 
  }
  else if(*endptr == 'a' || *endptr == 'A') {
    tInfoPtr->am_pm = 'A';
  }
  else if(*endptr == 'p' || *endptr == 'P') {
    tInfoPtr->am_pm = 'P';
  }
  else {
     ret = ret | ERR_TIME_FORMAT; //not correct singleton char
  }

  //check ranges for values
  if(isInRange(hour, MIN_HR, MAX_HR+1) == 0) {
    ret = ret | ERR_TIME_RANGE;
  }
  if(isInRange(min, MIN_MIN, MAX_MIN+1) == 0) {
    ret = ret | ERR_TIME_RANGE;
  }
  if(isInRange(sec, MIN_SEC, MAX_SEC+1) == 0) {
    ret = ret | ERR_TIME_RANGE;
  }

  // set values in struct
  tInfoPtr->tm_hour = hour;
  tInfoPtr->tm_min = min;
  tInfoPtr->tm_sec = sec;

  return ret;
}
