#include "fincol.h"
#include "confusion.h"
#include "fatalerror.h"
#include "getavail.h"
#include "newnullbox.h"
#include "newglue.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "unsave.h"
#include "newsavelevel.h"
#include "hpack.h"
#include "vpackage.h"
#include "getnode.h"
#include "initspan.h"
#include "popnest.h"
#include "getxtoken.h"
#include "initcol.h"

bool fincol(void)
{
	halfword p, q, r, s, u;
	scaled w;
	glueord o;
	halfword n;
	if (curalign == 0)
		confusion(908); //endv
	q = link(curalign);
	if (q == 0)
		confusion(908); //endv
	if (alignstate < 500000)
		fatalerror(595); //(interwoven alignment preambles are not allowed)
	p = link(q);
	if (p == 0 && info(curalign+5) < 257)
		if (curloop != 0)
		{
			link(q) = newnullbox();
			p = link(q);
			info(p) = end_span;
			mem[p+1].int_ = -0x40'00'00'00;
			curloop = link(curloop);
			q = hold_head;
			r = mem[curloop+3].int_;
			while (r)
			{
				link(q) = getavail();
				q = link(q);
				info(q) = info(r);
				r = link(r);
			}
			link(q) = 0;
			mem[p+3].int_ = link(hold_head);
			q = hold_head;
			r = mem[curloop+2].int_;
			while (r)
			{
				link(q) = getavail();
				q = link(q);
				info(q) = info(r);
				r = link(r);
			}
			link(q) = 0;
			mem[p+2].int_ = link(hold_head);
			curloop = link(curloop);
			link(p) = newglue(info(curloop+1));
		}
		else
		{
			if (interaction == 3)
				printnl(262); //! 
			print(909); //Extra alignment tab has been changed to 
			printesc(898); //cr
			helpptr = 3;
			helpline[2] = 910; //You have given more \span or & marks than there were
			helpline[1] = 911; //in the preamble to the \halign or \valign now in progress.
			helpline[0] = 912; //So I'll assume that you meant to type \cr instead.
			info(curalign+5) = 257;
			error();
		}
	if (info(curalign+5) != 256)
	{
		unsave();
		newsavelevel(6);
		if (mode == -hmode)
		{
			adjusttail = curtail;
			u = hpack(link(head), 0, 1);
			w = mem[u+1].int_;
			curtail = adjusttail;
			adjusttail = 0;
		}
		else
		{
			u = vpackage(link(head), 0, 1, 0);
			w = mem[u+3].int_;
		}
		n = 0;
		if (curspan != curalign)
		{
			q = curspan;
			do
			{
				n++;
				q = link(link(q));
			} while (q != curalign);
			if (n > 255)
			confusion(913); // spans
			q = curspan;
			while (link(link(q)) < n)
				q = link(q);
			if (link(link(q)) > n)
			{
				s = getnode(2);
				info(s) = info(q);
				link(s) = n;
				info(q) = s;
				mem[s+1].int_ = w;
			}
			else 
				if (mem[info(q)+1].int_ < w)
					mem[info(q)+1].int_ = w;
		}
		else 
			if (w > mem[curalign+1].int_)
				mem[curalign+1].int_ = w;
		type(u) = 13;
		subtype(u) = n;
		if (totalstretch[3])
			o = 3;
			else 
				if (totalstretch[2])
					o = 2;
				else 
					if (totalstretch[1])
						o = 1;
					else
						o = 0;
		subtype(u+5) = o;
		mem[u+6].int_ = totalstretch[o];
		if (totalshrink[3])
			o = 3;
		else 
			if (totalshrink[2])
				o = 2;
			else 
				if (totalshrink[1])
					o = 1;
				else
					o = 0;
		type(u+5) = o;
		mem[u+4].int_ = totalshrink[o];
		popnest();
		link(tail) = u;
		tail = u;
		tail_append(newglue(info(link(curalign)+1)));
		subtype(tail) = 12;
		if (info(curalign+5) >= 257)
			return true;
		initspan(p);
	}
	alignstate = 1000000;
	do
		getxtoken();
	while (curcmd == spacer);
	curalign = p;
	initcol();
	return false;
}
