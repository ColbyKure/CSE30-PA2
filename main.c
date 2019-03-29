/*
 * Filename: main.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: main driver for program that displays the BCD clock
 * Date: 5/7/18 
 * Sources of help: lecture notes, piazza, discussion slides
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function name: main()
 * Prototype: int main(int argc, char * argv[])
 * Description: This will parse the input from the command line and then
 *    error check it to make sure that the input is valid. Then, the program
 *    will flag an error and print an error message to stderr. Then, if the
 *    input is valid, proceed to print out the clock and the specified number of
 *    ticks otherwise use default values.
 * Parameters: 
 *        arg 1 - argc, number of arguments
 *        arg 2 - argv, array of input from command line
 * Side Effects: prints out error message to stderr, and BCDclock pattern
 *    to stdout on no error
 * Error Condition: 
 *    incorrect number of arguments
 *    error parsing numTicks of numTicks not in range 
 *    incorrect format for time
 *    error parsing time or valus in time are not in range
 * Return Value: return EXIT_FAILURE on fail and EXIT_SUCCESS on success
 */

int main(int argc, char * argv[]) {
  //define some local variables
  unsigned char clock[CLOCK_ARR_SIZE] = {0};// zero-filled clock
  char * endptr;
  errno = 0;
  int numTicks;

  //check if invalid number of arguments
  if(argc > MAX_ARGS) {
    fprintf(stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS,
      MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
    return EXIT_FAILURE;
  }

  //look for STR_HELP
  if(argc == MIN_ARGS ) {
    if(strncmp(STR_HELP, argv[HELP_INDEX], STR_HELP_LEN) == 0) {
      fprintf(stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS,
        MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_SUCCESS;
    }
  }

  //parse numTicks
  if(argc < MIN_ARGS) { // set numTicks to default if no input
    numTicks = DEF_TICKS;
  }
  else { // set numTicks to user input
    errno = 0;
    numTicks = strtol(argv[NUM_TICKS_INDEX], &endptr, BASE);
    if(errno != 0 || endptr == 0) {
      fprintf(stderr, STR_TICK_PARSE_ERR);
    }
    if(isInRange(numTicks, MIN_TICKS, MAX_TICKS) != 1) {
      fprintf(stderr, STR_TICKS_RANGE_ERR, numTicks, MIN_TICKS, MAX_TICKS);
    }
  }

  //parse startTime
  struct tm * tmPtr = 0;
  struct timeval tp = {0};
  struct tInfo * time = malloc(sizeof(struct tInfo)); 
  int defTimeFlag = 0;

  //get current time 
  if(argc <= MIN_ARGS) {
    timeRightNow(&tp, NULL);
    tmPtr = localtime(&tp.tv_sec); //tm holds local time

    //using tm convert time
    convertTime(time, tmPtr);
    defTimeFlag = 1;
  }
  else {
    //get input time
    int flag = 0;
    int mask = interpretTime(time, argv[START_TIME_INDEX]);
    if(mask != 0) {
      if((mask & ERR_TIME_FORMAT) != 0) { //format error?
        fprintf(stderr, STR_TIME_FORMAT_ERR);
        flag = 1;
      }
      if((mask & ERR_TIME_NUM) != 0) { //parse error?
        fprintf(stderr, STR_TIME_PARSE_ERR);
        flag = 1;
      }
      if((mask & ERR_TIME_RANGE) != 0) { //range error?
        fprintf(stderr, STR_TIME_RANGE_ERR);
        flag = 1;
      }
      if(flag == 1) {
        free(time);
        return EXIT_FAILURE;
      }
    }
  }

  //struct tInfo time holds values 
  if(defTimeFlag == 1) {
    //used default time
    char * currTime = asctime(tmPtr);
    printf("%s\n", currTime);
  }
  setClock(clock, time);
  printClock(clock);
  for(int i = 0; i < numTicks; i++) {
    tickClock(clock);
    printClock(clock);
  }
  free(time);
  return EXIT_SUCCESS;
}
