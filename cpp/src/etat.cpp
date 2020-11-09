#include "etat.h"
#include "noeud.h"
#include "erreur.h"
#include "fichier.h"
#include "impression.h"
#include "equivalent.h"
#include "alignement.h"
#include "lecture.h"
#include "getnext.h"
#include "tampon.h"
#include <iostream>

void popnest(void)
{
	delete head;
	nest.pop_back();
	curlist = nest.back();
}

void pushnest(void)
{
	if (nest.size()-1 == nestsize)
		overflow("semantic nest size", nestsize); 
	nest.push_back(curlist);
	tail = head = new LinkedNode;
	prev_graf = 0;
	mode_line = line; 
}

//! leave an input level, re-enter the old
void pop_input(void)
{  
	inputstack.pop_back();
	curinput = inputstack.back(); 
}

//! //enter a new input level, save the old
void push_input(void)
{
	if (inputstack.size()-1 == stacksize)
		overflow("input stack size", stacksize);
	inputstack.push_back(curinput);
}

constexpr char TEX_area[] = "TeXinputs:";

void startinput(char status, int first)
{
	scanfilename(status);
	if (curext == "")
		curext = ".tex";
	auto fname = pack_cur_name();
	while (true)
	{
		beginfilereading();
		curinput.start = first;
		if (aopenin(cur_file(), fname))
			break;
		if (curarea == "" && aopenin(cur_file(), fname = packfilename(curname, TEX_area, curext)))
			break;
		first = curinput.start;
		endfilereading();
		fname = promptfilename("input file name", ".tex", first);
	}
	if (jobname == "")
	{
		jobname = curname;
		openlogfile(curinput.start);
	}
	print(std::string(termoffset+fname.size() > maxprintline-2 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : "")+"(");
	openparens++;
	print(fname);
	std::cout << std::flush;
	state = new_line;
	line = 1;
	if (int lst = inputln(cur_file(), false, curinput.start); lst >= 0)
	{
		curinput.limit = lst;
		if (pausing() > 0 && interaction > nonstop_mode)
			lst = firmuptheline();
	} // else EOF
	removeLastBuf();
	bufBegin();
}

//! Undoes one token of input.
//! Sometimes TeX has read too far and wants to ``unscan'' what it has seen. The \a back_input procedure takes care of this by putting the token
//! just scanned back into the input stream, ready to be read again. This procedure can be used only if \a cur_tok represents the token to be
//! replaced. Some applications of TeX use this procedure a lot, so it has been slightly optimized for speed.
void backinput(Token t)
{
	while (state == token_list && Start.list.size() == 0 && token_type != v_template)
		endtokenlist();
	if (t.tok < right_brace_limit)
		if (t.tok < left_brace_limit)
			alignstate--;
		else
			alignstate++;
	backList(t.tok);
}

