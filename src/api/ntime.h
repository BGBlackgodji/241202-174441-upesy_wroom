#ifndef NTIME_H
#define NTIME_H

#include <time.h>

class NetworkTime {
    public:
        // return is success
        static bool load(int timeout = 10 * 1000);
        
        static tm get();

        static void print();
};

#endif