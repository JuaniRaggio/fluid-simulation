#ifndef __ERROR_MANAGEMENT_H__
#define __ERROR_MANAGEMENT_H__

#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stdout, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)

#endif

