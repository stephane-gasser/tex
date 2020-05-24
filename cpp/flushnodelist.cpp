#include "flushnodelist.h"
#include "freenode.h"
#include "deleteglueref.h"
#include "deletetokenref.h"
#include "confusion.h"

void flushnodelist(halfword p)
{
	while (p)
	{
		auto q = link(p);
		if (p >= himemmin)
		{
			link(p) = avail;
			avail = p;
		}
		else
		{
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					flushnodelist(list_ptr(p));
					freenode(p, 7);
					break;
				case rule_node:
					freenode(p, 4);
					break;
				case ins_node:
					flushnodelist(ins_ptr(p));
					deleteglueref(ins_ptr(p));
					freenode(p, 5);
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case 0:
							freenode(p, 3);
							break;
						case 1:
						case 3:
							deletetokenref(link(p+1));
							freenode(p, 2);
							break;
						case 2:
						case 4: 
							freenode(p, 2);
							break;
						default: 
							confusion("ext3");
					}
					break;
				case glue_node:
					if (glue_ref_count(glue_ptr(p)) == 0)
						freenode(glue_ptr(p), 4);
					else
						glue_ref_count(glue_ptr(p))--;
					if (leader_ptr(p))
						flushnodelist(leader_ptr(p));
					freenode(p, 2);
					break;
				case kern_node:
				case math_node:
				case penalty_node: 
					freenode(p, 2);
					break;
				case ligature_node: 
					flushnodelist(lig_ptr(p));
					freenode(p, 2);
					break;
				case mark_node: 
					deletetokenref(mark_ptr(p));
					freenode(p, 2);
					break;
				case disc_node:
					flushnodelist(pre_break(p));
					flushnodelist(post_break(p));
					freenode(p, 2);
					break;
				case adjust_node: 
					flushnodelist(adjust_ptr(p));
					freenode(p, 2);
					break;
				case style_node:
					freenode(p, 3);
					break;
				case choice_node:
					flushnodelist(display_mlist(p));
					flushnodelist(text_mlist(p));
					flushnodelist(script_mlist(p));
					flushnodelist(script_script_mlist(p));
					freenode(p, 3);
					break;
				case ord_noad:
				case op_noad:
				case bin_noad:
				case rel_noad:
				case open_noad:
				case close_noad:
				case punct_noad:
				case inner_noad:
				case radical_noad:
				case over_noad:
				case under_noad:
				case vcenter_noad:
				case accent_noad:
					if (math_type(nucleus(p)) >= sub_box)
						flushnodelist(nucleus(p));
					if (math_type(supscr(p)) >= sub_box)
						flushnodelist(info(supscr(p)));
					if (math_type(subscr(p)) >= sub_box)
						flushnodelist(info(subscr(p)));
					if (type(p) == radical_noad || type(p) == accent_noad)
						freenode(p, 5);
					else
						freenode(p, 4);
					break;
				case left_noad:
				case right_noad:
					freenode(p, 4);
					break;
				case fraction_noad:
					flushnodelist(info(numerator(p)));
					flushnodelist(info(denominator(p)));
					freenode(p, 6);
					break;
				default: 
					confusion("flushing"); 
			}
		}
		p = q;
	}
}
