#include "backinput.h"
#include "endtokenlist.h"
#include "getavail.h"
#include "overflow.h"
#include "pushinput.h"

void backinput(void)
{
	while (state == token_list && loc == 0 && token_type != v_template)
		endtokenlist();
	auto p = getavail();
	info(p) = curtok;
	if (curtok < right_brace_limit)
		if (curtok < left_brace_limit)
			alignstate--;
		else
			alignstate++;
	push_input();
	state = token_list;
	start = p;
	token_type = backed_up;
	loc = p;
}
