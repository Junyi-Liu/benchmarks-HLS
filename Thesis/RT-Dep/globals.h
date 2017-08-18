#define AUTOESL
#define MAX_QUEUE_SIZE 512
#define SIZE 256
#define SIZE1 32


#ifdef AUTOESL
#include<ap_cint.h>
#define DATATYPE int64
#define CTRLTYPE uint8
#define extractBits(a,b,c) apint_get_range(a,b,c)
#define concat(a,b) apint_concatenate(a,b)
#endif
#ifdef CATAPULT
#include <ac_fixed.h>
#include <ac_int.h>
#define DATATYPE ac_fixed<32,16,0,AC_RND,AC_SAT>
#define CTRLTYPE ac_int<10,1>
#endif
#ifdef GCC
#define DATATYPE double
#define CTRLTYPE int
#endif

#define SIZE 256



#define min(a,b) (((CTRLTYPE)(a)>(CTRLTYPE)(b))?(CTRLTYPE)(b):(CTRLTYPE)(a))
#define max(a,b) (((CTRLTYPE)(a)<(CTRLTYPE)(b))?(CTRLTYPE)(b):(CTRLTYPE)(a))
