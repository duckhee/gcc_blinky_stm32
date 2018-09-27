#include "mode.h"


//need to fix core_cm3.c file assembler 


/* Private macro -------------------------------------------------------------*/ 
#if defined ( __CC_ARM   )
__ASM void __SVC(void) 
{ 
  SVC 0x01 
  BX R14
}
#elif defined ( __ICCARM__ )
static __INLINE  void __SVC()                     { __ASM ("svc 0x01");}
#elif defined   (  __GNUC__  )
static __INLINE void __SVC()                      { __ASM volatile ("svc 0x01");}
#endif

/* Private variables ---------------------------------------------------------*/
__IO uint8_t PSPMemAlloc[SP_PROCESS_SIZE];

MODE_PRIVILEGE_DEF uint32_t  Get_Current_ThreadMode(void)
{
    /* Check Thread mode privilege status */
    if((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
    {
        /* Thread mode has privileged access  */
        return THREAD_MODE_PRIVILEGED;
    }
    else
    {
        /* Thread mode has unprivileged access*/
        return THREAD_MODE_UNPRIVILEGED;
    }
}

MODE_PRIVILEGE_DEF uint32_t  Get_Current_Stack(void)
{
    if((__get_CONTROL() & 0x02) == SP_MAIN)
    {
        /* Main stack is used as the current stack */
        return SP_MAIN;
    }
    else
    {
        /* Process stack is used as the current stack */
        return SP_PROCESS;
    }
}

MODE_PRIVILEGE_DEF void Mode_Privilege_Test(void)
{
    __IO uint32_t Index;

    DEBUG_MSG_FUNC_START;

    /* Switch Thread mode Stack from Main to Process */
    /* Initialize memory reserved for Process Stack */
    for(Index = 0; Index < SP_PROCESS_SIZE; Index++)
    {
        PSPMemAlloc[Index] = 0x00;
    }
    printf("PSPMemAlloc address = 0x%0X\r\n", PSPMemAlloc);

    printf("(1) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Set Process stack value */ 
    __set_PSP((uint32_t)PSPMemAlloc + SP_PROCESS_SIZE);
    printf("(2) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Select Process Stack as Thread mode Stack */
    __set_CONTROL(SP_PROCESS);
    printf("(3) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Get the Thread mode stack used */
    if(Get_Current_Stack() == SP_MAIN)
    {
        printf("CurrentStack is Main Stack\r\n");
    }
    else
    {
        printf("CurrentStack is Process Stack\r\n");

        /* Get process stack pointer value */
        printf("PSPValue = 0x%0X\r\n", __get_PSP());
    }
  
    /* Switch Thread mode from privileged to unprivileged */
    /* Thread mode has unprivileged access */
    __set_CONTROL(THREAD_MODE_UNPRIVILEGED | SP_PROCESS);
    /* Unprivileged access mainly affect ability to:
    - Use or not use certain instructions such as MSR fields
    - Access System Control Space (SCS) registers such as NVIC and SysTick */
    printf("(4) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Switch back Thread mode from unprivileged to privileged */
    /* Try to switch back Thread mode to privileged (Not possible, this can be
    done only in Handler mode) */
    __set_CONTROL(THREAD_MODE_PRIVILEGED | SP_PROCESS);
    printf("(5) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Generate a system call exception, and in the ISR switch back Thread mode
    to privileged */
    __SVC();
    printf("(6) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());

    /* Select Main Stack */
    __set_CONTROL(SP_MAIN);
    printf("(7) CurrentStack = %d, ThreadMode = %d\r\n",
           Get_Current_Stack(), Get_Current_ThreadMode());
}

