#include "shiftcase.h"
#include "lecture.h"
#include "equivalent.h"

void shiftcase(Token tk) // lc_code_base / uc_code_base
{
	auto p = scantoks(false, false, tk);
	for (p = dynamic_cast<TokenNode*>(defref->link); p; next(p))
	{
		auto t = p->token;
		if (t < single_base+cs_token_flag)
		{
			eightbits c = t%(1<<8);
			if (auto subst = eqtb_local[tk.chr+c-local_base].int_; subst)
				p->token = t-c+subst;
		}
	}
	back_list(dynamic_cast<TokenNode*>(defref->link));
	delete defref;
	defref = nullptr;
}
