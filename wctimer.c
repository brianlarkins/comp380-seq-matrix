/* ******************************************************/
/*                                                      */
/*  timer. - TSC timer calibration routines             */
/*                                                      */
/*  created: 1/22/23                                    */
/*                                                      */
/* ******************************************************/
#include <stdio.h>

#include "wctimer.h"

/**
 * gtc_tsc_calibrate - calibrate the TSC timer
 * @return the calculated MHz of the current PE for tick-to-ns conversion
 */
double wc_tsc_calibrate(void) {
  struct timespec start, end, sleep;
  uint64_t tscstart, tscend, tscdiff, clockdiff;
  double tscticks;

  // calibrate TSC timer
  sleep.tv_sec = 0;
  sleep.tv_nsec = 25 * 1000000L; // 25ms
  tscticks = 0.0;
  tscdiff = clockdiff = 0;

  // run calibration test 10 times (250 ms)
  // also do sanity checking against clock_gettime()
  for (int i=0; i<10; i++) {
    memset(&start, 0, sizeof(start));
    memset(&end, 0, sizeof(end));

    start = gtc_get_wtime();
    tscstart = gtc_get_tsctime();
    nanosleep(&sleep, NULL);
    tscend   = gtc_get_tsctime();
    end = gtc_get_wtime();
    end.tv_sec  -= start.tv_sec;
    end.tv_nsec -= start.tv_nsec;
    clockdiff += (1000000000L * (end.tv_sec)) + end.tv_nsec; // should be 25M ns
    tscdiff   += (tscend - tscstart);

    // 25ms * 40 == 1000ms == 1sec
    tscticks += ((tscend - tscstart) * 40) / (double) 1e6;
  }

  tscticks /= 10.0;

  // clockdiff and tscdiff should be ~250M ns or 250 ms
  fprintf(stderr, "wc_tsc_calibrate: calibrated MHz: %7.3f clock_gettime: %7.3f ms rtdsc: %7.3f ms\n",
        tscticks,
        (clockdiff/(double)1e6),
        ((tscdiff/tscticks)/(double)1e3));
  return tscticks;
}
