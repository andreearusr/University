#include <stdlib.h>
#include <crtdbg.h> 

#include <iostream>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

#include "Reteta.h"

int main()
{
	{
		all_tests();
		Repository repo;
		Validator valid;
		Reteta reteta{ repo };
		Service srv{ repo , valid , reteta };
		Consola ui{ srv };
		ui.run();

	}
	_CrtDumpMemoryLeaks();

	return 0;
}