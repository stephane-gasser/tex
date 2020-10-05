#include "doregistercommand.h"
#include "impression.h"
#include "erreur.h"
#include "lecture.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "calcul.h"
#include "trapzeroglue.h"
#include "equivalent.h"

void doregistercommand(smallnumber a, Token t)
//t.cmd: register_ / advance /multiply / divide
{
	halfword l, q;
	halfword p;
	q = t.cmd;
	if (q != register_)
		t = getxtoken();
	switch (t.cmd)
	{
		case assign_int:    // assign_int+int_val
		case assign_dimen:  // assign_int+dimen_val
		case assign_glue:   // assign_int+glue_val
		case assign_mu_glue:// assign_int+mu_val
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
			error("You can't use `"+cmdchr(t)+"' after "+cmdchr(Token(q, 0)), "I'm forgetting what you said and not changing anything.");
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
	try
	{
		switch (p)
		{
			case int_val: 
				switch (q)
				{
					case register_:
						word_define(a, &eqtb_int[l-int_base], scanint());
						break;
					case advance:
						word_define(a, &eqtb_int[l-int_base], scanint()+eqtb_int[l-int_base].int_);
						break;
					case multiply:
						word_define(a, &eqtb_int[l-int_base], mult_integers(eqtb_int[l-int_base].int_, scanint()));
						break;
					case divide:
						word_define(a, &eqtb_int[l-int_base], xovern(eqtb_int[l-int_base].int_, scanint()));
				}
				break;
			case dimen_val: 
				switch (q)
				{
					case register_:
						word_define(a, &eqtb_dimen[l-dimen_base], scan_normal_dimen());
						break;
					case advance:
						word_define(a, &eqtb_dimen[l-dimen_base], scan_normal_dimen()+eqtb_dimen[l-dimen_base].int_);
						break;
					case multiply:
						word_define(a, &eqtb_dimen[l-dimen_base], nx_plus_y(eqtb_dimen[l-dimen_base].int_, scanint(), 0));
						break;
					case divide:
						word_define(a, &eqtb_dimen[l-dimen_base], xovern(eqtb_dimen[l-dimen_base].int_, scanint()));
				}
				break;
			case glue_val: 
				switch (q)
				{
					case register_:
						g = scanglue(glue_val);
						break;
					case advance:
					{
						g = new GlueSpec(scanglue(glue_val));
						auto R = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
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
						break;
					}
					case multiply:
					{
						auto val = scanint();
						auto S = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
						g = new GlueSpec(S);
						g->width = nx_plus_y(S->width, val, 0);
						g->stretch = nx_plus_y(S->stretch, val, 0);
						g->shrink = nx_plus_y(S->shrink, val, 0);
						break;
					}
					case divide:
					{
						auto val = scanint();
						auto S = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
						g = new GlueSpec(S);
						g->width = xovern(S->width, val);
						g->stretch = xovern(S->stretch, val);
						g->shrink = xovern(S->shrink, val);
					}
				}
				g = trapzeroglue(g);
				define(a, &eqtb_glue[l-glue_base], glue_ref, g);
				break;
			case mu_val: 
				switch (q)
				{
					case register_:
						g = scanglue(mu_val);
						break;
					case advance:
					{
						g = new GlueSpec(scanglue(mu_val));
						auto R = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
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
						break;
					}
					case multiply:
					{
						auto val = scanint();
						auto S = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
						g = new GlueSpec(S);
						g->width = nx_plus_y(S->width, val, 0);
						g->stretch = nx_plus_y(S->stretch, val, 0);
						g->shrink = nx_plus_y(S->shrink, val, 0);
						break;
					}
					case divide:
					{
						auto val = scanint();
						auto S = dynamic_cast<GlueSpec*>(eqtb_glue[l-glue_base].index);
						g = new GlueSpec(S);
						g->width = xovern(S->width, val);
						g->stretch = xovern(S->stretch, val);
						g->shrink = xovern(S->shrink, val);
					}
				}
				g = trapzeroglue(g);
				define(a, &eqtb_glue[l-glue_base], glue_ref, g);
		}
	}
	catch(ArithException &e)
	{
		error("Arithmetic overflow", "I can't carry out that multiplication or division,\nsince the result is out of range.");
		if (p >= glue_val)
			deleteglueref(g);
		return;
	}
}
