#include "backinput.h"
#include "endtokenlist.h"
#include "getavail.h"
#include "overflow.h"
#include "pushinput.h"

//! Undoes one token of input.
//! Sometimes TeX has read too far and wants to ``unscan'' what it has
//! seen. The \a back_input procedure takes care of this by putting the token
//! just scanned back into the input stream, ready to be read again. This
//! procedure can be used only if \a cur_tok represents the token to be
//! replaced. Some applications of TeX use this procedure a lot,
//! so it has been slightly optimized for speed.
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
