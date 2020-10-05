#include "shipout.h"
#include "impression.h"
#include "erreur.h"
#include "fichier.h"
#include "preparemag.h"
#include "noeud.h"
#include "equivalent.h"
#include "outwhat.h"
#include "dvi.h"
#include "police.h"
#include "chaine.h"
#include "buildpage.h"
#include <iostream>
#include <cmath>

float vet_glue(float g)
{
	constexpr float billion = 1000000000.;
	if (g > billion)
		return billion;
	if (g < -billion)
		return -billion;
	return g; 
}

static void hlistout(BoxNode*);

static void vlistout(BoxNode *thisbox)
{
	scaled curg = 0;
	float curglue = 0.0;
	glueord gorder = thisbox->glue_order;
	char gsign = thisbox->glue_sign;
	auto p = thisbox->list_ptr;
	curs++;
	if (curs > 0)
		dvi_out(push);
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	auto leftedge = curh;
	curv -= thisbox->height;
	auto topedge = curv;
	for (; p; next(p))
		switch (p->type)
		{
			case char_node:
			case whatsit_node:
			case kern_node:
				p->vlist(0);
				break;
			case hlist_node:
			case vlist_node:
				p->vlist(leftedge);
				break;
			case rule_node:
				p->vlist(thisbox->width);
				break;
			case glue_node:
			{
				auto pp = dynamic_cast<GlueNode*>(p);
				auto g = pp->glue_ptr;
				ruleht = g->width-curg;
				if (gsign)
					if (gsign == 1)
					{
						if (g->stretch_order == gorder)
						{
							curglue += g->stretch;
							curg = round(vet_glue(thisbox->glue_set*curglue));
						}
					}
					else 
						if (g->shrink_order == gorder)
						{
							curglue -= g->shrink;
							curg = round(vet_glue(thisbox->glue_set*curglue));
						}
				ruleht += curg;
				if (pp->subtype >= a_leaders)
				{
					if (pp->leader_ptr->type == rule_node)
					{
						auto leaderbox = dynamic_cast<RuleNode*>(pp->leader_ptr);
						rulewd = leaderbox->width;
						ruledp = 0;
						if (is_running(rulewd))
							rulewd = thisbox->width;
						ruleht += ruledp;
						curv += ruleht;
						if (ruleht > 0 &&rulewd > 0)
						{
							synch_h();
							synch_v();
							dvi_out(put_rule);
							dvifour(ruleht);
							dvifour(rulewd);
						}
						break;
					}
					auto leaderbox = dynamic_cast<BoxNode*>(pp->leader_ptr);
					auto leaderht = leaderbox->height+leaderbox->depth;
					if (leaderht > 0 && ruleht > 0)
					{
						ruleht += 10;
						auto edge = curv+ruleht;
						scaled lx = 0;
						if (pp->subtype == a_leaders)
						{
							auto savev = curv;
							curv = topedge+leaderht*((curv-topedge)/leaderht);
							if (curv < savev)
								curv += leaderht;
						}
						else
						{
							lq = ruleht/leaderht;
							lr = ruleht%leaderht;
							if (pp->subtype == c_leaders)
								curv += lr/2;
							else
							{
								lx = lr/(lq+1);
								curv += (lr-(lq-1)*lx)/2;
							}
						}
						while (curv+leaderht <= edge)
						{
							curh = leftedge+leaderbox->shift_amount;
							synch_h();
							auto saveh = dvih;
							curv += leaderbox->height;
							synch_v();
							auto savev = dviv;
							auto outerdoingleaders = doingleaders;
							doingleaders = true;
							(leaderbox->type == vlist_node ? vlistout : hlistout)(leaderbox);
							doingleaders = outerdoingleaders;
							dviv = savev;
							dvih = saveh;
							curh = leftedge;
							curv = savev-leaderbox->height+leaderht+lx;
						}
						curv = edge-10;
						break;
					}
				}
				curv += ruleht;
			}
		}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}

static void hlistout(BoxNode *thisbox)
{
	scaled curg = 0;
	float curglue = 0.0;
	glueord gorder = thisbox->glue_order;
	char gsign = thisbox->glue_sign;
	auto p = thisbox->list_ptr;
	curs++;
	if (curs > 0)
		dvi_out(push);
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	scaled baseline = curv;
	scaled leftedge = curh;
	while (p)
	{
		switch (p->type)
		{
			case char_node:
			{
				synch_h();
				synch_v();
				for (; p->type == char_node; next(p))
					p->hlist(0, 0, 0);
				dvih = curh;
				continue;
			}
			case hlist_node:
			case vlist_node:
				p->hlist(baseline, 0, 0);
				break;
			case rule_node:
				p->hlist(baseline, thisbox->height, thisbox->depth);
				break;
			case whatsit_node:
			case kern_node:
			case math_node: 
				p->hlist(0, 0, 0);
				break;
			case ligature_node:
			{
				p->hlist(0, 0, 0);
				p = lig_trick;
				continue;
			}
			case glue_node:
			{
				auto P = dynamic_cast<GlueNode*>(p);
				auto g = P->glue_ptr;
				rulewd = g->width-curg;
				if (gsign)
					if (gsign == 1)
					{
						if (g->stretch_order == gorder)
						{
							curglue += g->stretch;
							curg = round(vet_glue(thisbox->glue_set*curglue));
						}
					}
					else 
						if (g->shrink_order == gorder)
						{
							curglue -= g->shrink;
							curg = round(vet_glue(thisbox->glue_set*curglue));
						}
				rulewd += curg;
				if (P->subtype >= a_leaders)
				{
					auto leaderbox = dynamic_cast<BoxNode*>(P->leader_ptr);
					if (leaderbox->type == rule_node)
					{
						ruleht = leaderbox->height;
						ruledp = leaderbox->depth;
						if (is_running(ruleht))
							ruleht = thisbox->height;
						if (is_running(ruledp))
							ruledp = thisbox->depth;
						ruleht += ruledp;
						if (ruleht > 0 && rulewd > 0)
						{
							synch_h();
							curv = baseline+ruledp;
							synch_v();
							dvi_out(set_rule);
							dvifour(ruleht);
							dvifour(rulewd);
							curv = baseline;
							dvih = dvih+rulewd;
						}
						curh = curh+rulewd;
						break;
					}
					scaled leaderwd = leaderbox->width;
					if (leaderwd > 0 && rulewd > 0)
					{
						rulewd = rulewd+10;
						auto edge = curh+rulewd;
						scaled lx = 0;
						if (P->subtype == a_leaders)
						{
							auto saveh = curh;
							curh = leftedge+leaderwd*((curh-leftedge)/leaderwd);
							if (curh < saveh)
								curh = curh+leaderwd;
						}
						else
						{
							lq = rulewd/leaderwd;
							lr = rulewd%leaderwd;
							if (P->subtype == c_leaders)
								curh += lr/2;
							else
							{
								lx = lr/(lq+1);
								curh += (lr-(lq-1)*lx)/2;
							}
						}
						while (curh+leaderwd <= edge)
						{
							curv = baseline+leaderbox->shift_amount;
							synch_v();
							auto savev = dviv;
							synch_h();
							auto saveh = dvih;
							bool outerdoingleaders = doingleaders;
							doingleaders = true;
							(leaderbox->type == vlist_node ? vlistout : hlistout)(leaderbox);
							doingleaders = outerdoingleaders;
							dviv = savev;
							dvih = saveh;
							curv = baseline;
							curh = saveh+leaderwd+lx;
						}
						curh = edge-10;
						break;
					}
				}
				curh = curh+rulewd;
				break;
			}
		}
		next(p);
		continue;
	}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}


static void ensure_dvi_open(void)
{
	if (outputfilename == "")
	{
		if (jobname == "")
			openlogfile();
		while (!bopenout(dvifile, outputfilename = packjobname(".dvi")))
			promptfilename("file name for output", ".dvi");
	}
}

void shipout(BoxNode *p)
{
	if (tracing_output())
		print("\r\nCompleted box being shipped out"+std::string(termoffset > maxprintline-9 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : ""));
	print("[");
	int j = 9;
	while (count(j) == 0 && j > 0)
		j--;
	for (int k = 0; k <= j; k++)
	{
		print(std::to_string(count(k)));
		if (k < j)
			print(".");
	}
	std::cout << std::flush;
	if (tracing_output() > 0)
	{
		print("]");
		diagnostic(showbox(p)+"\n");
	}
	if (p->height > max_dimen || p->depth > max_dimen 
	 || p->height+p->depth+v_offset() > max_dimen 
	 || p->width+h_offset() > max_dimen)
	{
		error("Huge page cannot be shipped out", "The page just created is more than 18 feet tall or\nmore than 18 feet wide, so I suspect something went wrong.");
		if (tracing_output() <= 0)
		{
			diagnostic("\rThe following box has been deleted:"+showbox(p)+"\n");
			print("]");
		}
		deadcycles = 0;
		std::cout << std::flush;
		flushnodelist(p);
		return;
	}
	if (p->height+p->depth+v_offset() > maxv)
		maxv = p->height+p->depth+v_offset();
	if (p->width+h_offset() > maxh)
		maxh = p->width+h_offset();
	dvih = 0;
	dviv = 0;
	curh = h_offset();
	dvif = null_font;
	ensure_dvi_open();
	if (totalpages == 0)
	{
		dvi_out(pre);
		dvi_out(id_byte);
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(mag());
		dvi_out(cur_length());
		for (char c: " TeX output "+std::to_string(year())+"."+twoDigits(month())+"."+twoDigits(day())+":"+twoDigits(time()/60)+twoDigits(time()%60))
			dvi_out(c);
	}
	auto pageloc = dvioffset+dviptr;
	dvi_out(bop);
	for (auto k = 0; k < 10; k++)
		dvifour(count(k));
	dvifour(lastbop);
	lastbop = pageloc;
	curv = p->height+v_offset();
	if (p->type == vlist_node)
		vlistout(p);
	else
		hlistout(p);
	dvi_out(eop);
	totalpages++;
	curs = -1;
	if (tracing_output() <= 0)
		print("]");
	deadcycles = 0;
	std::cout << std::flush;
	flushnodelist(p);
}

void BoxNode::vlist(scaled leftedge)
{
	if (list_ptr == nullptr)
		curv += height+depth;
	else
	{
		curv += height;
		if (curv != dviv)
		{
			movement(curv-dviv, down1);
			dviv = curv;
		}
		auto saveh = dvih;
		auto savev = dviv;
		curh = leftedge+shift_amount;
		(type == vlist_node ? vlistout : hlistout)(this);
		dvih = saveh;
		dviv = savev;
		curv = savev+depth;
		curh = leftedge;
	}
}

void RuleNode::vlist(scaled w)
{
	ruleht = height;
	ruledp = depth;
	rulewd = width;
	if (is_running(rulewd))
		rulewd = w;
	ruleht += ruledp;
	curv += ruleht;
	if (ruleht > 0 &&rulewd > 0)
	{
		synch_h();
		synch_v();
		dvi_out(put_rule);
		dvifour(ruleht);
		dvifour(rulewd);
	}
}

void WhatsitNode::vlist(scaled) { outwhat(this); }
void WhatsitNode::hlist(scaled, scaled, scaled) { outwhat(this); }
void KernNode::vlist(scaled) { curv += width; }
void KernNode::hlist(scaled, scaled, scaled) { curh += width; }
void MathNode::hlist(scaled, scaled, scaled) { curh += width; }

void CharNode::hlist(scaled, scaled, scaled)
{
	if (font != dvif)
	{
		if (!fonts[font].used)
		{
			dvifontdef(font);
			fonts[font].used = true;
		}
		if (font <= 64+font_base)
			dvi_out(font-font_base-1+fnt_num_0);
		else
		{
			dvi_out(fnt1);
			dvi_out(font-font_base-1);
		}
		dvif = font;
	}
	if (character >= 128)
		dvi_out(set1);
	dvi_out(character);
	curh += width();
}

void BoxNode::hlist(scaled baseline, scaled, scaled)
{
	if (list_ptr == nullptr)
		curh += width;
	else
	{
		auto saveh = dvih;
		auto savev = dviv;
		curv = baseline+shift_amount;
		auto edge = curh;
		(type == vlist_node ? vlistout : hlistout)(this);
		dvih = saveh;
		dviv = savev;
		curh = edge+width;
		curv = baseline;
	}
}

void RuleNode::hlist(scaled baseline, scaled h, scaled d)
{
	ruleht = height;
	ruledp = depth;
	rulewd = width;
	if (is_running(ruleht))
		ruleht = h;
	if (is_running(ruledp))
		ruledp = d;
	ruleht += ruledp;
	if (ruleht > 0 && rulewd > 0)
	{
		synch_h();
		curv = baseline+ruledp;
		synch_v();
		dvi_out(set_rule);
		dvifour(ruleht);
		dvifour(rulewd);
		curv = baseline;
		dvih = dvih+rulewd;
	}
	curh = curh+rulewd;
}

void LigatureNode::hlist(scaled, scaled, scaled)
{
	lig_trick->font = font;
	lig_trick->character = character;
	lig_trick->link = link;
}

