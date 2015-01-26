#ifndef	__ints
#define __ints

#include <stdint.h>
//#include <stdbool.h>

#define   uint8   unsigned char
#define   int8    signed char
#define   uint16  unsigned short
#define   int16   short
#define   uint32  unsigned long
#define   int32   long

#define _high(w)\
            *((char*)&w+1)

#define _low(w)\
            *((char*)&w)

#define   _byte0(d)\
              *((char*)&d)
#define   _byte1(d)\
              *((char*)&d+1)
#define   _byte2(d)\
              *((char*)&d+2)
#define   _byte3(d)\
              *((char*)&d+3)

#endif
