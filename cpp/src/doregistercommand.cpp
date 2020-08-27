#include "doregistercommand.h"
#include "impression.h"
#include "erreur.h"
#include "lecture.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "multandadd.h"
#include "xovern.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "eqworddefine.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "texte.h"

void doregistercommand(smallnumber a, Token t)
//t.cmd: register_ / advance /multiply / divide
{
	halfword l, q, r, s;
	halfword p;
	q = t.cmd;
	if (q != register_)
		t = getxtoken();
	switch (t.cmd)
	{
		case assign_int:
		case assign_dimen:
		case assign_glue:
		case assign_mu_glue:
			l = t.chr;
			p = t.cmd-assign_int;
			break;
		case register_:
			switch (p = t.chr)
			{
				case int_val: 
					l = scaneightbitint()+count_base;
					break;
				case dimen_val: 
					l = scaneightbitint()+scaled_base;
					break;
				case glue_val: 
					l = scaneightbitint()+skip_base;
					break;
				case mu_val: 
					l = scaneightbitint()+mu_skip_base;
			}
			break;
		default:
		{
			Token tk;
			tk.cmd = q;
			tk.chr = 0;
			error("You can't use `"+cmdchr(t)+"' after "+cmdchr(tk), "I'm forgetting what you said and not changing anything.");
			return;
		}
	}
	if (q == register_)
		scanoptionalequals();
	else 
		if (scankeyword("by"))
			aritherror = false;
	int val;
	GlueSpec *g;
	switch (q)
	{
		case register_:
			switch (p)
			{
				case int_val: 
					val = scanint();
					break;
				case dimen_val: 
					val = scan_normal_dimen();
					break;
				case glue_val: 
				case mu_val: 
					g = scanglue(p);
			}
			break;
		case advance:
			switch (p)
			{
				case int_val: 
					val = scanint()+eqtb[l].int_;
					break;
				case dimen_val: 
					val = scan_normal_dimen()+eqtb[l].int_;
					break;
				case glue_val: 
				case mu_val: 
					g = new GlueSpec(scanglue(p));
					r = equiv(l);
					GlueSpec *R;
					R->num = r;
					deleteglueref(g);
					g->width += R->width;
					if (g->stretch == 0)
						g->stretch_order = 0;
					if (g->stretch_order == R->stretch_order)
						g->stretch += R->stretch;
					else 
						if (g->stretch_order < R->stretch_order && R->stretch)
						{
							g->stretch = R->stretch;
							g->stretch_order = R->stretch_order;
						}
					if (g->shrink == 0)
						g->shrink_order = 0;
					if (g->shrink_order == R->shrink_order)
						g->shrink += R->shrink;
					else 
						if (g->shrink_order < R->shrink_order && R->shrink)
						{
							g->shrink = R->shrink;
							g->shrink_order = R->shrink_order;
						}
			}
			break;
	case multiply:
		val = scanint();
		switch (p)
		{
			case int_val: 
				val = mult_integers(eqtb[l].int_, val);
				break;
			case dimen_val: 
				val = nx_plus_y(eqtb[l].int_, val, 0);
				break;
			case glue_val: 
			case mu_val: 
				s = equiv(l);
				GlueSpec *S;
				S->num = s;
				g = new GlueSpec(S);
				r = g->num;
				g->width = nx_plus_y(S->width, val, 0);
				g->stretch = nx_plus_y(S->stretch, val, 0);
				g->shrink = nx_plus_y(S->shrink, val, 0);
		}
		break;
	case divide:
		val = scanint();
		switch (p)
		{
			case int_val: 
			case dimen_val: 
				val = xovern(eqtb[l].int_, val);
				break;
			case glue_val:
			case mu_val:
				s = equiv(l);
				GlueSpec *S;
				S->num = s;
				g = new GlueSpec(S);
				g->width = xovern(S->width, val);
				g->stretch = xovern(S->stretch, val);
				g->shrink = xovern(S->shrink, val);
		}
	}
	if (aritherror)
	{
		error("Arithmetic overflow", "I can't carry out that multiplication or division,\nsince the result is out of range.");
		if (p >= glue_val)
			deleteglueref(g);
		return;
	}
	switch (p)
	{
		case int_val: 
		case dimen_val: 
			word_define(a, l, val);
			break;
		case glue_val:
		case mu_val:
			g = trapzeroglue(g);
			define(a, l, glue_ref, g->num);
	}
}
