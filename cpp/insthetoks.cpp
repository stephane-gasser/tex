#include "insthetoks.h"
#include "thetoks.h"
#include "begintokenlist.h"

void insthetoks(void)
{
	link(garbage) = thetoks();
	ins_list(link(temp_head));
}
