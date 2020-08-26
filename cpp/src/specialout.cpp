#include "specialout.h"
#include "movement.h"
#include "impression.h"
#include "erreur.h"
#include "dviswap.h"
#include "dvifour.h"

void specialout(NotOpenWriteWhatsitNode *p)
{
	synch_h();
	synch_v();
	auto oldsetting = selector;
	auto s = tokenlist(dynamic_cast<TokenNode*>(p->write_tokens->link), 0, poolsize/*-poolptr*/);
	if (cur_length() < 256)
	{
		dvi_out(xxx1);
		dvi_out(cur_length());
	}
	else
	{
		dvi_out(xxx4);
		dvifour(cur_length());
	}
	for (auto c: s)
		dvi_out(c);
}
