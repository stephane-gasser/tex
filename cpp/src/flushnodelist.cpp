#include "flushnodelist.h"
#include "freenode.h"
#include "deleteglueref.h"
#include "lecture.h"
#include "erreur.h"

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
					freenode(p, box_node_size);
					break;
				case rule_node:
					freenode(p, rule_node_size);
					break;
				case ins_node:
					flushnodelist(ins_ptr(p));
					deleteglueref(ins_ptr(p));
					freenode(p, ins_node_size);
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case open_node:
							freenode(p, open_node_size);
							break;
						case write_node:
						case special_node:
							deletetokenref(write_tokens(p));
							freenode(p, write_node_size);
							break;
						case close_node:
						case language_node: 
							freenode(p, small_node_size);
							break;
						default: 
							confusion("ext3");
					}
					break;
				case glue_node:
					deleteglueref(glue_ptr(p));
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
					freenode(p, style_node_size);
					break;
				case choice_node:
					flushnodelist(display_mlist(p));
					flushnodelist(text_mlist(p));
					flushnodelist(script_mlist(p));
					flushnodelist(script_script_mlist(p));
					freenode(p, style_node_size);
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
						freenode(p, radical_noad_size);
					else
						freenode(p, noad_size);
					break;
				case left_noad:
				case right_noad:
					freenode(p, noad_size);
					break;
				case fraction_noad:
					flushnodelist(info(numerator(p)));
					flushnodelist(info(denominator(p)));
					freenode(p, fraction_noad_size);
					break;
				default: 
					confusion("flushing"); 
			}
		}
		p = q;
	}
}
