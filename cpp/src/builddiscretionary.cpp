#include "builddiscretionary.h"
#include "sauvegarde.h"
#include "impression.h"
#include "erreur.h"
#include "popnest.h"
#include "noeud.h"
#include "lecture.h"
#include "pushnest.h"
#include "texte.h"

void builddiscretionary(Token t)
{
	unsave();
	// Prune the current list, if necessary, until it contains only |char_node|, |kern_node|, |hlist_node|, |vlist_node|, |rule_node|,
	//  and |ligature_node| items; set |n| to the length of the list, and set |q| to the list's tail
	auto q = head;
	auto p = q->link;
	int n = 0;
	while (p)
	{
		if (!p->is_char_node() && p->type > rule_node && p->type != kern_node && p->type != ligature_node)
		{
			error("Improper discretionary list", "Discretionary lists must contain only boxes and kerns.");
			diagnostic("\rThe following discretionary sublist has been deleted:"+showbox(dynamic_cast<BoxNode*>(p))+"\n");
			flushnodelist(p);
			q->link = nullptr;
			break;
		}
		q = p;
		p = q->link;
		n++;
	}
	p = head->link;
	popnest();
	switch (savestack.back()->int_)
	{
		case 0: 
			dynamic_cast<DiscNode*>(tail)->pre_break = p;
			break;
		case 1: 
			dynamic_cast<DiscNode*>(tail)->post_break = p;
			break;
		case 2: //Attach list |p| to the current list, and record its length; then finish up and |return|
			if (n > 0 && abs(mode) == mmode)
			{
				error("Illegal math "+esc("discretionary"), "Sorry: The third part of a discretionary break must be\nempty, in math formulas. I had to delete your third part.");
				flushnodelist(p);
				n = 0;
			}
			else
				tail->link = p;
			if (n <= 255)
				dynamic_cast<DiscNode*>(tail)->replace_count = n;
			else
				error("Discretionary list is too long", "Wow---I never thought anybody would tweak me here.\nYou can't seriously need such a huge discretionary list?");
			if (n > 0)
				tail = q;
			savestack.pop_back();
			return;
	}
	savestack.back()->int_++;
	newsavelevel(disc_group);
	t = scanleftbrace();
	pushnest();
	mode = -hmode;
	space_factor = 1000;
}
