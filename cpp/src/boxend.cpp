#include "boxend.h"
#include "appendtovlist.h"
#include "buildpage.h"
#include "newnoad.h"
#include "eqdefine.h"
#include "geqdefine.h"
#include "getxtoken.h"
#include "appendglue.h"
#include "impression.h"
#include "backerror.h"
#include "flushnodelist.h"
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
					if (adjust_head != adjusttail)
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
					link(p+1) = 2;
					info(p+1) = curbox;
					curbox = p;
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < ship_out_flag)
			// Store (c) \a cur_box in a box register
			if (boxcontext < box_flag+256)
				eqdefine(boxcontext-box_flag+box_base, box_ref, curbox);
			else
				geqdefine(boxcontext-box_flag-256+box_base, box_ref, curbox);
		else 
			if (curbox && boxcontext > ship_out_flag)
			// Append a new leader node that uses \a cur_box
			{
				do
					getxtoken();
				while (curcmd == spacer || curcmd == escape);
				if ((curcmd == hskip && abs(mode) != vmode) || (curcmd == vskip && abs(mode) == vmode))
				{
					appendglue();
					subtype(tail) = boxcontext-(leader_flag-a_leaders);
					leader_ptr(tail) = curbox;
				}
				else
				{
					print_err("Leaders not followed by proper glue");
					helpptr = 3;
					helpline[2] = "You should say `\\leaders <box or rule><hskip or vskip>'.";
					helpline[1] = "I found the <box or rule>, but there's no suitable";
					helpline[0] = "<hskip or vskip>, so I'm ignoring these leaders.";
					backerror();
					flushnodelist(curbox);
				}
			}

	else
	shipout(curbox);
}
