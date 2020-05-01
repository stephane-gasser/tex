#include "insthetoks.h"
#include "thetoks.h"
#include "begintokenlist.h"

void insthetoks(void)
{
	link(garbage) = thetoks();
	begintokenlist(link(temp_head), 4);
}
