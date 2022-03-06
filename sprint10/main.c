#include"Mcal/Inc/Cpu.h"
#include"Common/Platform_Types.h"

int main()
{
	CPU_StartCriticalSection();

	CPU_StopCriticalSection();

	return 0;
}