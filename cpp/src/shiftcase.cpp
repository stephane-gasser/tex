#include "shiftcase.h"
#include "lecture.h"
#include "equivalent.h"

void shiftcase(Token tk)
{
	auto p = scantoks(false, false, tk);
	p = dynamic_cast<TokenNode*>(defref->link);
	while (p)
	{
		auto t = p->token;
		if (t < single_base+cs_token_flag)
		{
			eightbits c = t%(1<<8);
			if (eqtb[tk.chr+c].int_)
				p->token = t-c+eqtb[tk.chr+c].int_;
		}
		p = dynamic_cast<TokenNode*>(p->link);
	}
	back_list(dynamic_cast<TokenNode*>(defref->link));
	delete defref;
	defref = nullptr;
}
