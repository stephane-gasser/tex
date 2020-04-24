#include "insertrelax.h"
#include "backinput.h"

void insertrelax(void)
{
	curtok = 4095+curcs;
	backinput();
	curtok = 6716;
	backinput();
	curinput.indexfield = 4;
}
