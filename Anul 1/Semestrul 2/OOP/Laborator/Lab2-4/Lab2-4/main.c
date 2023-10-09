#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
#include "UI.h"

int main()
{
	test_all();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
