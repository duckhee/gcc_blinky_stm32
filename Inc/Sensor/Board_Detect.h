#ifndef __BOARD_DETECT_H__
#define __BOARD_DETECT_H__

#include "hw_config.h"


extern __IO uint16_t BoardDetectValue;

#ifdef BOARD_DETECT_LOCAL
#define BOARD_DETECT_DEF
#else
#define BOARD_DETECT_DEF            extern
#endif


BOARD_DETECT_DEF void board_detect_initialize(void);
BOARD_DETECT_DEF void board_detect(void);

#endif