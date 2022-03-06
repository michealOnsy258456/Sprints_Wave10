#include "../common/Platform_Types.h"
#include "../common/Compiler.h"
#include "Inc/Cpu.h"


static uint8 guint8_CritCount = 0;


void CPU_StartCriticalSection(void)
{
    guint8_CritCount++;
    Disable_GlobalInterrupts();
}
void CPU_StopCriticalSection(void)
{
    if (guint8_CritCount == 0)
    {
        Enable_GlobalInterrupts();
    }
    else
    {
        guint8_CritCount--;
        if (guint8_CritCount == 0)
        {
            CPU_EnableGlobalInterrupt();
        }
        else
        {
            /* do nothing */
        }
    }
}