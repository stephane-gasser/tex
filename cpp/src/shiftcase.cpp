#include "shiftcase.h"
#include "lecture.h"

void shiftcase(Token tk)
{
	auto p = scantoks(false, false, tk);
	p = dynamic_cast<TokenNode*>(defref->link);
	while (p)
	{
		auto t = p->token;
		if (t < cs_token_flag+single_base)
		{
			eightbits c = t%(1<<8);
			if (equiv(tk.chr+c))
				p->token = t-c+equiv(tk.chr+c);
		}
		p = dynamic_cast<TokenNode*>(p->link);
	}
	back_list(dynamic_cast<TokenNode*>(defref->link));
	delete defref;
	defref = nullptr;
}
