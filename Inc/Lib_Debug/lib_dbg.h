#ifndef __LIB_DEBUG_H__
#deifne __LIB_DEBUG_H__


#include "stm32f10x.h"

#ifdef LIB_DEBUG_LOCAL
#define LIB_DEBUG_DEF 
#else
#define LIB_DEBUG_DEF               extern
#endif

LIB_DEBUG_DEF void debug(void);

#endif