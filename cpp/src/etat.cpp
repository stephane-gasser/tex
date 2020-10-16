#include "etat.h"
#include "noeud.h"
#include "erreur.h"
#include "fichier.h"
#include "impression.h"
#include "equivalent.h"
#include "alignement.h"
#include "lecture.h"
#include "getnext.h"
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

void startinput(char status)
{
	scanfilename(status);
	if (curext == "")
		curext = ".tex";
	name = pack_cur_name();
	while (true)
	{
		beginfilereading();
		if (aopenin(cur_file(), name))
			break;
		if (curarea == "" && aopenin(cur_file(), packfilename(curname, TEX_area, curext)))
			break;
		endfilereading();
		name = promptfilename("input file name", ".tex");
	}
	if (jobname == "")
	{
		jobname = curname;
		openlogfile();
	}
	print(std::string(termoffset+name.size() > maxprintline-2 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : "")+"(");
	openparens++;
	print(name);
	std::cout << std::flush;
	state = new_line;
	line = 1;
	if (inputln(cur_file(), false))
		firmuptheline();
	if (end_line_char_inactive())
		limit--;
	else
		buffer[limit] = end_line_char();
	First = limit+1;
	loc = start;
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
	TokenList tl;
	tl.list.push_back(t.tok);
	back_list(&tl);
}

