#include "copynodelist.h"
#include "getavail.h"
#include "getnode.h"
#include "confusion.h"

static void add_token_ref(halfword p)
{
	token_ref_count(p)++;
}

halfword copynodelist(halfword p)
{
	auto h = getavail();
	auto q = h;
	while (p)
	{
		int words = 1;
		halfword r;
		if (p >= himemmin)
			r = getavail();
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					r = getnode(box_node_size);
					mem[r+6] = mem[p+6];
					mem[r+5] = mem[p+5];
					list_ptr(r) = copynodelist(list_ptr(p));
					words = 5;
					break;
				case rule_node:
					r = getnode(rule_node_size);
					words = rule_node_size;
					break;
				case ins_node:
					r = getnode(ins_node_size);
					mem[r+4] = mem[p+4];
					add_glue_ref(split_top_ptr(p));
					ins_ptr(r) = copynodelist(ins_ptr(p));
					words = ins_node_size-1;
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case open_node:
							r = getnode(open_node_size);
							words = open_node_size;
							break;
						case write_node:
						case special_node:
							r = getnode(write_node_size);
							add_token_ref(write_tokens(p));
							words = write_node_size;
							break;
						case close_node:
						case language_node:
							r = getnode(small_node_size);
							words = small_node_size;
							break;
						default:
							confusion("ext2");
					}
					break;
				case glue_node:
					r = getnode(small_node_size);
					add_glue_ref(glue_ptr(p));
					glue_ptr(r) = glue_ptr(p);
					leader_ptr(r) = copynodelist(leader_ptr(p));
					break;
				case kern_node:
				case math_node:
				case penalty_node:
					r = getnode(small_node_size);
					words = 2;
					break;
				case ligature_node:
					r = getnode(small_node_size);
					mem[lig_char(r)] = mem[lig_char(p)];
					lig_ptr(r) = copynodelist(lig_ptr(p));
					break;
				case disc_node:
					r = getnode(small_node_size);
					pre_break(r) = copynodelist(pre_break(p));
					post_break(r) = copynodelist(post_break(p));
					break;
				case mark_node:
					r = getnode(small_node_size);
					info(mark_ptr(p))++;
					words = small_node_size;
					break;
				case adjust_node:
					r = getnode(small_node_size);
					adjust_ptr(r) = copynodelist(adjust_ptr(p));
					break;
				default: 
					confusion("copying");
			}
		;
		for (;words > 0; words--)
			mem[r+words] = mem[p+words];
		link(q) = r;
		q = r;
		p = link(p);
	}
	link(q) = 0;
	q = link(h);
	link(h) = avail;
	avail = h;
	return q;
}
