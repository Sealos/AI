/**
 * Proyecto 2: Othello
 * 
 * Inteligencia Artificial (CI5437)
 * 
 * Copyright (C) 2011 Universidad Simon Bolivar
 * Author: Blai Bonet, bonet@ldc.usb.ve
 * 
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cassert>

#include <sys/resource.h>
#include <sys/time.h>

//#define DEBUG

namespace Utils {

#if 0
extern float kappa_log;

inline size_t kappa_value(float p, float kl = kappa_log) {
    return (size_t)floor(-log(p) / kl);
}
#endif

inline float read_time_in_seconds() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return (float)r_usage.ru_utime.tv_sec +
           (float)r_usage.ru_utime.tv_usec / (float)1000000;
}

template<typename T> inline T min(const T a, const T b) {
    return a <= b ? a : b;
}

template<typename T> inline T max(const T a, const T b) {
    return a >= b ? a : b;
}

template<typename T> inline T abs(const T a) {
    return a < 0 ? -a : a;
}

}; // end of namespace

#undef DEBUG

#endif

