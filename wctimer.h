/* ******************************************************/
/*                                                      */
/*  timer.h - timing structs and inlines                */
/*                                                      */
/*  created: 6/30/19                                    */
/*                                                      */
/* ******************************************************/

// compiler intrinsics for TSC timing, should be okay on clang, gcc, and icc
#include <x86intrin.h>

struct wc_timer_s {
  uint64_t total;
  uint64_t last;
  uint64_t temp;
};
typedef struct wc_timer_s wc_timer_t;


static inline uint64_t wc_get_tsctime() {
  return __rdtsc();
}

#define WC_CPU_HZ                 tsc_cpu_hz*(double)1e6
#define WC_INIT_ATIMER(TMR)       do { TMR.total = 0; TMR.temp = 0; TMR.last = 0; } while (0)
#define WC_START_ATIMER(TMR)      TMR.last = wc_get_tsctime();
#define WC_STOP_ATIMER(TMR)       do {\
                                      TMR.temp = wc_get_tsctime();\
                                      TMR.total += TMR.temp - TMR.last;\
                                    } while (0)

#define WC_READ_ATIMER(TMR)          TMR.total
#define WC_READ_ATIMER_NSEC(TMR)     (double)(WC_READ_ATIMER(TMR)/(WC_CPU_HZ)) * (double)1e9
#define WC_READ_ATIMER_USEC(TMR)     (double)(WC_READ_ATIMER(TMR)/(WC_CPU_HZ)) * (double)1e6
#define WC_READ_ATIMER_MSEC(TMR)     (double)(WC_READ_ATIMER(TMR)/(WC_CPU_HZ)) * (double)1000.0
#define WC_READ_ATIMER_SEC(TMR)      (double)WC_READ_ATIMER(TMR)/(WC_CPU_HZ)

// timer.c
double             wc_tsc_calibrate(void);

double tsc_cpu_hz = wc_tsc_calibrate(); // global variable
