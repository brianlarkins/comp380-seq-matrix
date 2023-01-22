#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "wctimer.h"


int main(int argc, char **argv) {
  wc_timer_t t;

  if (argc < 2) {
    printf("usage: lab1 <size>\n\t<size>\t size of matrices and vectors\n");
    exit(-1);
  }

  wc_tsc_calibrate();   // we must always calibrate the TSC timer in every program
  WC_INIT_TIMER(t);     // timers must be initialized before use

  /* timer example */
  WC_START_TIMER(t);   // start as close to the code you want to measure

  /* do stuff that takes time */
  usleep(1000);

  WC_STOP_TIMER(t);    // stop timer when you're done

  // there are nice macros to convert times to different units -- see wctimer.h
  printf("timer duration: %10.3f ms\n", WC_READ_TIMER_MSEC(t));
}
