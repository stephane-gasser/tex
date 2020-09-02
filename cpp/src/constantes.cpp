#include "globals.h"
#include "equivalent.h"

halfword& link(halfword p) { return mem[p].hh.rh; }
halfword& info(halfword p) { return mem[p].hh.lh; }
halfword& node_size(halfword p) { return mem[p].hh.lh; }
halfword& rlink(halfword p) { return link(p+1); }
halfword& llink(halfword p) { return info(p+1); }

alphafile& cur_file(void) { return inputfile[index]; }
void set_cur_lang(void) { curlang = (language() <= 0 || language() > 255) ? 0 : language(); } 

void tail_append(LinkedNode *p) 
{
	tail->link = p;
	next(tail);
}

void flush_string(void)
{
	strings.pop_back();
	currentString = "";
}

float vet_glue(float g)
{
	constexpr float billion = 1000000000.;
	if (g > billion)
		return billion;
	if (g < -billion)
		return -billion;
	return g;
}
