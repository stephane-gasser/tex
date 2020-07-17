#include "builddiscretionary.h"
#include "unsave.h"
#include "impression.h"
#include "erreur.h"
#include "popnest.h"
#include "noeud.h"
#include "lecture.h"
#include "pushnest.h"
#include "texte.h"

void builddiscretionary(halfword tok, halfword align)
{
	unsave(tok);
	// Prune the current list, if necessary, until it contains only |char_node|, |kern_node|, |hlist_node|, |vlist_node|, |rule_node|,
	//  and |ligature_node| items; set |n| to the length of the list, and set |q| to the list's tail
	auto q = head;
	auto p = link(q);
	int n = 0;
	while (p)
	{
		if (!is_char_node(p) && type(p) > rule_node && type(p) != kern_node && type(p) != ligature_node)
		{
			error("Improper discretionary list", "Discretionary lists must contain only boxes and kerns.", align);
			diagnostic("\rThe following discretionary sublist has been deleted:"+showbox(p)+"\n");
			flushnodelist(p);
			link(q) = 0;
			break;
		}
		q = p;
		p = link(q);
		n++;
	}
	p = link(head);
	popnest();
	switch (saved(-1))
	{
		case 0: 
			pre_break(tail) = p;
			break;
		case 1: 
			post_break(tail) = p;
			break;
		case 2: //Attach list |p| to the current list, and record its length; then finish up and |return|
			if (n > 0 && abs(mode) == mmode)
			{
				error("Illegal math "+esc("discretionary"), "Sorry: The third part of a discretionary break must be\nempty, in math formulas. I had to delete your third part.", align);
				flushnodelist(p);
				n = 0;
			}
			else
				link(tail) = p;
			if (n <= 255)
				subtype(tail) = n;
			else
				error("Discretionary list is too long", "Wow---I never thought anybody would tweak me here.\nYou can't seriously need such a huge discretionary list?", align);
			if (n > 0)
				tail = q;
			saveptr--;
			return;
	}
	saved(-1)++;
	newsavelevel(10);
	std::tie(std::ignore, std::ignore, tok) = scanleftbrace(align);
	pushnest();
	mode = -hmode;
	space_factor = 1000;
}
