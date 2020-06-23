#include "shortdisplay.h"
#include "printchar.h"
#include "print.h"
#include "printesc.h"
#include "texte.h"

static halfword& font_id_text(halfword p) { return text(font_id_base+p); }

void shortdisplay(int p)
{
	while (p > memmin)
	{
		if (p >= himemmin)
		{
			if (p <= memend)
			{
				if (font(p) != fontinshortdisplay)
				{
					if (font(p) < 0 || font(p) > fontmax)
						printchar('*');
					else
						printesc(TXT(font_id_text(p)));
					printchar(' ');
					fontinshortdisplay = font(p);
				}
				printchar(character(p));
			}
		}
		else
		switch (type(p))
		{
			case hlist_node:
			case vlist_node:
			case ins_node:
			case whatsit_node:
			case mark_node:
			case adjust_node:
			case unset_node: 
				print("[]");
				break;
			case rule_node: 
				printchar('|');
				break;
			case glue_node: 
				if (glue_ptr(p) != zero_glue)
					printchar(' ');
				break;
			case math_node:
				printchar('$');
				break;
			case ligature_node:
				shortdisplay(lig_ptr(p));
				break;
			case disc_node:
				shortdisplay(pre_break(p));
				shortdisplay(post_break(p));
				for (int n = replace_count(p); n > 0; n--)
					if (link(p))
						p = link(p);
		}
		p = link(p);
	}
}
