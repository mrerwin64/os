#ifndef OS_DELAY_H
#define OS_DELAY_H

static inline __attribute__((unused)) void busy_wait(const unsigned long iterations) {
    for (volatile unsigned long j = 0; j < iterations; j++) {
        ;
    }
}

#endif //OS_DELAY_H
