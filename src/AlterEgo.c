#include "libs.h"

static void mainLoop(void);
/*--------------------------------------------------------------------------*/

int main(void)
{
        ULONG result = LibsOpen();

        if (RT_OK == result)
        {
                mainLoop();
        }
        
        LibsClose();

        return 0;
}

/*--------------------------------------------------------------------------*/

static void mainLoop(void)
{

}


/*--------------------------------------------------------------------------*/
