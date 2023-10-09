#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

int main()
{
	run_all_tests();
	run();
	_CrtDumpMemoryLeaks();

	return 0;
}