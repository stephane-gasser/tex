#include "shiftcase.h"
#include "lecture.h"
#include "equivalent.h"

void shiftcase(Token tk) // lc_code_base / uc_code_base
{
	scanNonMacroToks(tk);
	for (auto &p: defRef.list)
		if (p < single_base+cs_token_flag)
		{
			eightbits c = p%(1<<8);
			if (auto subst = eqtb_local[tk.chr+c-local_base].int_; subst)
				p += subst-c;
		}
	back_list(&defRef);
	defRef.list.clear();
	defRef.token_ref_count = 0;
}
