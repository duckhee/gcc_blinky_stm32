#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__

#include "hal_rf.h"
#include "hal_cc2520.h"
#include "basic_rf.h"


#ifdef ZIGBEE_LOCAL
#define ZIGBEE_DEF
#else
#define ZIGBEE_DEF          extern
#endif

#ifdef  BOARD_DEF_MANGO_Z1
    ZIGBEE_DEF void Zigbee_Test(void);
#endif

#endif