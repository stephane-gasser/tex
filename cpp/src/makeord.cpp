#include "makeord.h"
#include "fetch.h"
#include "noeud.h"
#include "police.h"

void makeord(halfword q)
{
	bool label20 = false;
	do
	{
		Noad *Q;
		Q->num = q;
		if (Q->subscr.math_type == 0 && Q->supscr.math_type == 0 && Q->nucleus.math_type == math_char)
		{
			auto p = dynamic_cast<Noad*>(Q->link);
			if (p && p->type >= ord_noad && p->type <= punct_noad && p->nucleus.math_type == math_char && p->nucleus.fam == Q->nucleus.fam)
			{
				Q->nucleus.math_type = math_text_char;
				auto [ft, curc] = fetch(nucleus(q));
				if (char_tag(ft.char_info(curc)) == lig_tag)
				{
					int a = ft.lig_kern_start(ft.char_info(curc));
					curc = p->nucleus.character;
					if (skip_byte(Font::infos(a)) > stop_flag)
						a = ft.lig_kern_restart(Font::infos(a));
					while (true)
					{
						halfword r;
						if (next_char(Font::infos(a)) == curc)
							if (skip_byte(Font::infos(a)) <= stop_flag)
								if (op_byte(Font::infos(a)) >= kern_flag)
								{
									auto p = new KernNode(ft.char_kern(Font::infos(a)));
									p->link = Q->link;
									Q->link = p;
									return;
								}
								else
								{
									switch (op_byte(Font::infos(a)))
									{
										// AB -> CB (symboles =:| et =:|>)
										case 1:
										case 5: 
											Q->nucleus.character = rem_byte(Font::infos(a));
											break;
										// AB -> AC (symboles |=: et |=:>)
										case 2:
										case 6: 
											p->nucleus.character = rem_byte(Font::infos(a));
											break;
										// AB -> ACB (symboles |=:|, |=:|> et |=:|>>)
										case 3:
										case 7:
										case 11:
										{
											auto r = new Noad;
											r->nucleus.character = rem_byte(Font::infos(a));
											r->nucleus.fam = Q->nucleus.fam;
											Q->link = r;
											r->link = p;
											if (op_byte(Font::infos(a)) < 11) // symboles |=:| et |=:|>
												r->nucleus.math_type = math_char;
											else // symbole |=:|>>
												r->nucleus.math_type = math_text_char;
											break;
										// AB -> C (symbole =;)
										}
										default:
											Q->link = p->link;
											Q->nucleus.character = rem_byte(Font::infos(a));
											Q->subscr = p->subscr;
											Q->supscr = p->supscr;
											delete p;
									}
									if (op_byte(Font::infos(a)) > 3)
										return;
									Q->nucleus.math_type = math_char;
									label20 = true;
								}
						if (label20)
							break;
						if (skip_byte(Font::infos(a)) >= stop_flag)
							return;
						a += skip_byte(Font::infos(a))+1;
					}
				}
			}
		}
	} while (label20);
}
