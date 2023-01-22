#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "wctimer.h"


int main(int argc, char **argv) {
  double start, end;

  if (argc < 2) {
    printf("usage: lab1 <size>\n\t<size>\t size of matrices and vectors\n");
    exit(-1);
  }

  /* timer example */
  start = get_wctime();
  /* do stuff that takes time */
  end = get_wctime();
  printf("timer duration: %10.7f ms\n", (end-start)*1000.0); // 1000 converts s to ms
}
