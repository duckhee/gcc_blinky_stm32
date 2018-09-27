#ifndef __MODE_H__
#define __MODE_H__

#include "hw_config.h"

/* Private define ------------------------------------------------------------*/
#define SP_PROCESS_SIZE             0x200  /* Process stack size */
#define SP_PROCESS                  0x02   /* Process stack */
#define SP_MAIN                     0x00   /* Main stack */
#define THREAD_MODE_PRIVILEGED      0x00   /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED    0x01   /* Thread mode has unprivileged access */

#ifdef MODE_PRIVILEGE_LOCAL
#define MODE_PRIVILEGE_DEF
#else
#define MODE_PRIVILEGE_DEF        extern
#endif



MODE_PRIVILEGE_DEF uint32_t  Get_Current_ThreadMode(void);
MODE_PRIVILEGE_DEF uint32_t  Get_Current_Stack(void);
MODE_PRIVILEGE_DEF void Mode_Privilege_Test(void);

#endif