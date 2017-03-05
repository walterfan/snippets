#int clock_gettime(clockid_t clock_id, struct timespec *tp);
#include <time.h>
#include <stdio.h>

/**                                                                             
 * sleep for `sec' seconds, without relying on the wall clock of time(2)        
 * or gettimeofday(2).                                                          
 *                                                                              
 * under ideal conditions is accurate to one microsecond. To get nanosecond     
 * accuracy, replace sleep()/usleep() with something with higher resolution     
 * like nanosleep() or ppoll().                                          
 */
void
true_sleep(int sec)
{
        struct timespec ts_start;
        struct timespec ts_end;

	clock_gettime(CLOCK_MONOTONIC, &ts_start);

        ts_end = ts_start;
        ts_end.tv_sec += sec;

        for(;;) {
                struct timespec ts_current;
                struct timespec ts_remaining;

                clock_gettime(CLOCK_MONOTONIC, &ts_current);

		ts_remaining.tv_sec = ts_end.tv_sec - ts_current.tv_sec;
                ts_remaining.tv_nsec = ts_end.tv_nsec - ts_current.tv_nsec;
                while (ts_remaining.tv_nsec > 1000000000) {
                        ts_remaining.tv_sec++;
                        ts_remaining.tv_nsec -= 1000000000;
                }
		while (ts_remaining.tv_nsec < 0) {
			ts_remaining.tv_sec--;
                        ts_remaining.tv_nsec += 1000000000;
                }

                if (ts_remaining.tv_sec < 0) {
                        break;
                }

                if (ts_remaining.tv_sec > 0) {
                        sleep(ts_remaining.tv_sec);
                } else {
                        usleep(ts_remaining.tv_nsec / 1000);
                }
        }
}

int main()
{
        true_sleep(10);
}

