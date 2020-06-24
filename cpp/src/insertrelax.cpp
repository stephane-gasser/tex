#include "insertrelax.h"
#include "backinput.h"

void insertrelax(void)
{
	curtok = cs_token_flag+curcs;
	backinput();
	curtok = cs_token_flag+frozen_relax;
	backinput();
	token_type = inserted;
}
