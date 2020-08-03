#include "boxend.h"
#include "buildpage.h"
#include "noeud.h"
#include "eqdefine.h"
#include "geqdefine.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "shipout.h"
#include "texte.h"

void boxend(int boxcontext)
{
	halfword p; //\a ord_noad for new box in math mode
	if (boxcontext < box_flag)
	{
		if (curbox)
		{
			shift_amount(curbox) = boxcontext;
			if (abs(mode) == vmode)
			{
				appendtovlist(curbox);
				if (adjusttail)
				{
					if (adjust_head->num != adjusttail)
						tail_append(adjust_head);
					adjusttail = 0;
				}
				if (mode > 0)
					buildpage();
			}
			else
			{
				if (abs(mode) == hmode)
					space_factor = 1000;
				else
				{
					p = newnoad();
					math_type(nucleus(p)) = sub_box;
					info(nucleus(p)) = curbox;
					curbox = p;
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < ship_out_flag) // Store (c) \a cur_box in a box register
			if (boxcontext < box_flag+256)
				eqdefine(boxcontext-box_flag+box_base, box_ref, curbox);
			else
				geqdefine(boxcontext-box_flag-256+box_base, box_ref, curbox);
		else 
			if (curbox && boxcontext > ship_out_flag) // Append a new leader node that uses \a cur_box
			{
				auto t = getXTokenSkipSpaceAndEscape();
				if ((t.cmd == hskip && abs(mode) != vmode) || (t.cmd == vskip && abs(mode) == vmode))
				{
					appendglue(t.chr);
					subtype(tail->num) = boxcontext-(leader_flag-a_leaders);
					leader_ptr(tail->num) = curbox;
				}
				else
				{
					backerror(t, "Leaders not followed by proper glue", "You should say `\\leaders <box or rule><hskip or vskip>'.\nI found the <box or rule>, but there's no suitable\n<hskip or vskip>, so I'm ignoring these leaders.");
					flushnodelist(curbox);
				}
			}

	else
	shipout(curbox);
}
