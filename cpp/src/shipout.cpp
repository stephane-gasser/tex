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
	while (p)
	{
		if (p->is_char_node())
			confusion("vlistout");
		else
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					if (P->list_ptr == nullptr)
						curv += P->height+P->depth;
					else
					{
						curv += P->height;
						if (curv != dviv)
						{
							movement(curv-dviv, down1);
							dviv = curv;
						}
						auto saveh = dvih;
						auto savev = dviv;
						curh = leftedge+P->shift_amount;
						if (p->type == vlist_node)
							vlistout(P);
						else
							hlistout(P);
						dvih = saveh;
						dviv = savev;
						curv = savev+P->depth;
						curh = leftedge;
					}
					break;
				}
				case rule_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					ruleht = P->height;
					ruledp = P->depth;
					rulewd = P->width;
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
					next(p);
					continue;
				}
				case whatsit_node:
					outwhat(dynamic_cast<WhatsitNode*>(p));
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
						auto leaderbox = dynamic_cast<RuleNode*>(pp->leader_ptr);
						if (leaderbox->type == rule_node)
						{
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
							next(p);
							continue;
						}
						auto leaderht = leaderbox->height+leaderbox->depth;
						if ((leaderht > 0) and (ruleht > 0))
						{
							ruleht += 10;
							auto edge = curv+ruleht;
							scaled lx = 0;
							if (pp->subtype == a_leaders)
							{
								auto savev = curv;
								curv = topedge+leaderht*((curv-topedge)/leaderht);
								if (curv < savev)
									curv = curv+leaderht;
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
								auto Leaderbox = dynamic_cast<BoxNode*>(leaderbox);
								curh = leftedge+Leaderbox->shift_amount;
								synch_h();
								auto saveh = dvih;
								curv += leaderbox->height;
								synch_v();
								auto savev = dviv;
								auto outerdoingleaders = doingleaders;
								doingleaders = true;
								(leaderbox->type == vlist_node ? vlistout : hlistout)(Leaderbox);
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curh = leftedge;
								curv = savev-leaderbox->height+leaderht+lx;
							}
							curv = edge-10;
							next(p);
							continue;
						}
					}
					curv = curv+ruleht;
					next(p);
					continue;
				}
				case kern_node: 
					curv += dynamic_cast<KernNode*>(p)->width;
			}
			next(p);
			continue;
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
		if (p->is_char_node())
		{
			synch_h();
			synch_v();
			auto P = dynamic_cast<CharNode*>(p);
			for (; p->is_char_node(); next(p))
			{
				auto f = P->font;
				auto c = P->character;
				if (f != dvif)
				{
					if (!fonts[f].used)
					{
						dvifontdef(f);
						fonts[f].used = true;
					}
					if (f <= 64+font_base)
						dvi_out(f-font_base-1+fnt_num_0);
					else
					{
						dvi_out(fnt1);
						dvi_out(f-font_base-1);
					}
					dvif = f;
				}
				;
				if (c >= 128)
					dvi_out(set1);
				dvi_out(c);
				curh += fonts[f].char_width(c);
			}
			dvih = curh;
		}
		else
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					if (P->list_ptr == nullptr)
						curh += P->width;
					else
					{
						auto saveh = dvih;
						auto savev = dviv;
						curv = baseline+P->shift_amount;
						auto edge = curh;
						(P->type == vlist_node ? vlistout : hlistout)(P);
						dvih = saveh;
						dviv = savev;
						curh = edge+P->width;
						curv = baseline;
					}
					break;
				}
				case rule_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					ruleht = P->height;
					ruledp = P->depth;
					rulewd = P->width;
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
					next(p);
					continue;
				}
				case whatsit_node:
					outwhat(dynamic_cast<WhatsitNode*>(p));
					break;
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
							next(p);
							continue;
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
							next(p);
							continue;
						}
					}
					curh = curh+rulewd;
					next(p);
					continue;
				}
				case kern_node:
					curh += dynamic_cast<KernNode*>(p)->width;
					break;
				case math_node: 
					curh += dynamic_cast<MathNode*>(p)->width;
					break;
				case ligature_node:
				{
					auto P = dynamic_cast<LigatureNode*>(p);
					lig_trick->font = P->font;
					lig_trick->character = P->character;
					lig_trick->link = p->link;
					p = lig_trick;
					continue;
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
		printnl("\nCompleted box being shipped out"+std::string(termoffset > maxprintline-9 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : ""));
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
