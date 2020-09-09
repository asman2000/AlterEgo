#include "print.h"

extern int testsRun;
extern int testsFailed;

#define muAssert(test, msg) \
	do\
	{\
		if (!(test))\
		{\
			printFnc(__func__, msg);\
			testsFailed++;\
		}\
	} while (0)

#define muRun(test) \
	do\
	{\
		test();\
		testsRun++;\
	} while(0)

#define muFail(msg) \
	do\
	{\
		printFnc(__func__, msg);\
		testsFailed++;\
	} while (0)