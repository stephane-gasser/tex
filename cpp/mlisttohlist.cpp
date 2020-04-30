#include "mlisttohlist.h"
#include "xovern.h"
#include "makefraction.h"
#include "hpack.h"
#include "freenode.h"
#include "makeop.h"
#include "makeradical.h"
#include "makeover.h"
#include "makeunder.h"
#include "makemathaccent.h"
#include "makevcenter.h"
#include "flushnodelist.h"
#include "mathglue.h"
#include "deleteglueref.h"
#include "mathkern.h"
#include "confusion.h"
#include "fetch.h"
#include "newcharacter.h"
#include "hpack.h"
#include "makeord.h"
#include "makescripts.h"
#include "freenode.h"
#include "newkern.h"
#include "newglue.h"
#include "newpenalty.h"
#include "makeleftright.h"

void mlisttohlist(void)
{
	halfword p, x, y, z;
	int pen;
	scaled delta;
	smallnumber s, t, savestyle;
	auto mlist = curmlist;
	auto penalties = mlistpenalties;
	auto style = curstyle;
	auto q = mlist;
	halfword r = 0;
	smallnumber rtype = 17;
	scaled maxh = 0;
	scaled maxd = 0;
	if (curstyle < 4)
		cursize = 0;
	else
		cursize = 16*((curstyle-2)/2);
	curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
	while (q)
	{
		delta = 0;
		switch (type(q))
		{
			case 18: 
				switch (rtype)
				{
					case 18:
					case 17:
					case 19:
					case 20:
					case 22:
					case 30:
						type(q) = 16;
						continue;
				}
				break;
			case 19:
			case 21:
			case 22:
			case 31:
				if (rtype == 18)
					type(r) = 16;
				if (type(q) == 31)
				{
					r = q;
					rtype = type(r);
					q = link(q);
					continue;
				}
				break;
			case 30: 
				r = q;
				rtype = type(r);
				q = link(q);
				continue;
			case 25:
				makefraction(q);
				z = hpack(mem[q+1].int_, 0, 1);
				if (mem[z+3].int_ > maxh)
					maxh = mem[z+3].int_;
				if (mem[z+2].int_ > maxd)
					maxd = mem[z+2].int_;
				freenode(z, 7);
				r = q;
				rtype = type(r);
				q = link(q);
				continue;
			case 17:
				delta = makeop(q);
				if (subtype(q) == 1)
				{
					z = hpack(mem[q+1].int_, 0, 1);
					if (mem[z+3].int_ > maxh)
						maxh = mem[z+3].int_;
					if (mem[z+2].int_ > maxd)
						maxd = mem[z+2].int_;
					freenode(z, 7);
					r = q;
					rtype = type(r);
					q = link(q);
					continue;
				}
				break;
			case 16: 
				makeord(q);
				break;
			case 20:
			case 23: 
				break;
			case 24: 
				makeradical(q);
				break;
			case 27: 
				makeover(q);
				break;
			case 26: 
				makeunder(q);
				break;
			case 28: 
				makemathaccent(q);
				break;
			case 29: 
				makevcenter(q);
				break;
			case 14:
				curstyle = subtype(q);
				if (curstyle < 4)
					cursize = 0;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
				q = link(q);
				continue;
				break;
			case 15:
				switch (curstyle/2)
				{
					case 0:
						p = info(q+1);
						info(q+1) = 0;
						break;
					case 1:
						p = link(q+1);
						link(q+1) = 0;
						break;
					case 2:
						p = info(q+2);
						info(q+2) = 0;
						break;
					case 3:
						p = link(q+2);
						link(q+2) = 0;
				}
				flushnodelist(info(q+1));
				flushnodelist(link(q+1));
				flushnodelist(info(q+2));
				flushnodelist(link(q+2));
				type(q) = 14;
				subtype(q) = curstyle;
				mem[q+1].int_ = 0;
				mem[q+2].int_ = 0;
				if (p)
				{
					z = link(q);
					link(q) = p;
					while (link(p))
						p = link(p);
					link(p) = z;
				}
				q = link(q);
				continue;
			case 3:
			case 4:
			case 5:
			case 8:
			case 12:
			case 7: 
				q = link(q);
				continue;
			case 2:
				if (mem[q+3].int_ > maxh)
					maxh = mem[q+3].int_;
				if (mem[q+2].int_ > maxd)
					maxd = mem[q+2].int_;
				q = link(q);
				continue;
			case 10:

				if (subtype(q) == 99)
				{
					x = info(q+1);
					y = mathglue(x, curmu);
					deleteglueref(x);
					info(q+1) = y;
					subtype(q) = 0;
				}
				else 
					if (cursize && subtype(q) == 98)
					{
						p = link(q);
						if (p)
							if (type(p) == 10 || type(p) == 11)
							{
								link(q) = link(p);
								link(p) = 0;
								flushnodelist(p);
							}
					}
				q = link(q);
				continue;
			case 11:
				mathkern(q, curmu);
				q = link(q);
				continue;
			default: 
				confusion(888); //mlist1
		}
		switch (link(q+1))
		{
			case 1:
			case 4:
				fetch(q+1);
				if (curi.b0 > 0)
				{
					delta = fontinfo[italicbase[curf]+(curi.b2-0)/4].int_;
					p = newcharacter(curf, curc);
					if (link(q+1) == 4 && fontinfo[2+parambase[curf]].int_)
						delta = 0;
					if (link(q+3) == 0 && delta)
					{
						link(p) = newkern(delta);
						delta = 0;
					}
				}
				else
					p = 0;
				break;
			case 0: 
				p = 0;
				break;
			case 2: 
				p = info(q+1);
				break;
			case 3:
				curmlist = info(q+1);
				savestyle = curstyle;
				mlistpenalties = false;
				mlisttohlist;
				curstyle = savestyle;
				if (curstyle < 4)
					cursize = 0;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
				p = hpack(link(29997), 0, 1);
				break;
			default: 
				confusion(889); //mlist2
		}
		mem[q+1].int_ = p;
		if (link(q+3) || link(q+2))
			makescripts(q, delta);
		z = hpack(mem[q+1].int_, 0, 1);
		if (mem[z+3].int_ > maxh)
			maxh = mem[z+3].int_;
		if (mem[z+2].int_ > maxd)
			maxd = mem[z+2].int_;
		freenode(z, 7);
		r = q;
		rtype = type(r);
		q = link(q);
	}
	if (rtype == 18)
		type(r) = 16;
	p = 29997;
	link(p) = 0;
	q = mlist;
	rtype = 0;
	curstyle = style;
	if (curstyle < 4)
		cursize = 0;
	else
		cursize = 16*((curstyle-2)/2);
	curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
	while (q)
	{
		t = 16;
		s = 4;
		pen = 10000;
		switch (type(q))
		{
			case 17:
			case 20:
			case 21:
			case 22:
			case 23: 
				t = type(q);
				break;
			case 18:
				t = 18;
				pen = eqtb[5272].int_;
				break;
			case 19:
				t = 19;
				pen = eqtb[5273].int_;
				break;
			case 16:
			case 29:
			case 27:
			case 26:
				break;
			case 24: 
				s = 5;
				break;
			case 28:
				s = 5;
				break;
			case 25:
				t = 23;
				s = 6;
				break;
			case 30:
			case 31: 
				t = makeleftright(q, style, maxd, maxh);
				break;
			case 14:
				curstyle = type(q);
				s = 3;
				if (curstyle < 4)
					cursize = 0;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
				r = q;
				q = link(q);
				freenode(r, s);
				continue;
				break;
			case 8:
			case 12:
			case 2:
			case 7:
			case 5:
			case 3:
			case 4:
			case 10:
			case 11:
				link(p) = q;
				p = q;
				q = link(q);
				link(p) = 0;
				continue;
			default: 
				confusion(890); //mlist3
		}
		if (rtype > 0)
		{
			switch (strpool[rtype*8+t+magicoffset])
			{
				case 48: 
					x = 0;
					break;
				case 49: 
					if (curstyle < 4)
						x = 15;
					else
						x = 0;
					break;
				case 50: 
					x = 15;
					break;
				case 51: 
					if (curstyle < 4)
						x = 16;
					else
						x = 0;
					break;
				case 52: 
					if (curstyle < 4)
						x = 17;
					else
						x = 0;
					break;
				default: 
					confusion(892); //mlist4
			}
			if (x)
			{
				y = mathglue(glue_par(x), curmu);
				z = newglue(y);
				link(y) = 0;
				link(p) = z;
				p = z;
				subtype(z) = x+1;
			}
		}
		if (mem[q+1].int_ != 0)
		{
			link(p) = mem[q+1].int_;
			do
				p = link(p);
			while (link(p));
		}
		if (penalties && link(q) && pen < 10000)
		{
			rtype = type(link(q));
			if (rtype != 12 && rtype != 19)
			{
				z = newpenalty(pen);
				link(p) = z;
				p = z;
			}
		}
		rtype = t;
	}
}
