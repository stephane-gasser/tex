#include "insertrelax.h"
#include "backinput.h"

void insertrelax(halfword cs)
{
	backinput(cs_token_flag+cs);
	backinput(cs_token_flag+frozen_relax);
	token_type = inserted;
}
