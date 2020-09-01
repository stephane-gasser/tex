#include "globals.h"
#include "equivalent.h"

halfword& link(halfword p) { return mem[p].hh.rh; }
halfword& info(halfword p) { return mem[p].hh.lh; }
halfword& node_size(halfword p) { return mem[p].hh.lh; }
halfword& rlink(halfword p) { return link(p+1); }
halfword& llink(halfword p) { return info(p+1); }
int cur_length(void) { return currentString.size(); }
bool is_running(int d) { return d == null_flag; }
alphafile& cur_file(void) { return inputfile[index]; }

void set_cur_lang(void) { curlang = (language() <= 0 || language() > 255) ? 0 : language(); }
void append_char(ASCIIcode c) { currentString += c; }
void flush_char(void) { currentString.pop_back(); }

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

void append_to_name(int &k, char c)
{
	k++;
	if (k <= filenamesize)
		nameoffile[k] = xchr[c]; 
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

quarterword &state = curinput.statefield;
quarterword &index = curinput.indexfield;
std::string &name = curinput.namefield;
scaled &act_width = activewidth[1];
scaled &page_goal = pagesofar[0];
scaled &page_total = pagesofar[1];
scaled &page_shrink = pagesofar[6];
scaled &page_depth = pagesofar[7];
