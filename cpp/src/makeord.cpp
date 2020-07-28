#include "makeord.h"
#include "fetch.h"
#include "noeud.h"
#include "police.h"

void makeord(halfword q)
{
	bool label20 = false;
	do
	{
		if (math_type(subscr(q)) == 0 && math_type(supscr(q)) == 0 && math_type(nucleus(q)) == math_char)
		{
			auto p = link(q);
			if (p && type(p) >= ord_noad && type(p) <= punct_noad && math_type(nucleus(p)) == math_char && fam(nucleus(p)) == fam(nucleus(q)))
			{
				math_type(nucleus(q)) = math_text_char;
				auto [ft, curc] = fetch(nucleus(q));
				if (char_tag(ft.char_info(curc)) == lig_tag)
				{
					int a = ft.lig_kern_start(ft.char_info(curc));
					curc = character(nucleus(p));
					if (skip_byte(Font::infos(a)) > stop_flag)
						a = ft.lig_kern_restart(Font::infos(a));
					while (true)
					{
						halfword r;
						if (next_char(Font::infos(a)) == curc)
							if (skip_byte(Font::infos(a)) <= stop_flag)
								if (op_byte(Font::infos(a)) >= kern_flag)
								{
									p = newkern(ft.char_kern(Font::infos(a)));
									link(p) = link(q);
									link(q) = p;
									return;
								}
								else
								{
									switch (op_byte(Font::infos(a)))
									{
										// AB -> CB (symboles =:| et =:|>)
										case 1:
										case 5: 
											character(nucleus(q)) = rem_byte(Font::infos(a));
											break;
										// AB -> AC (symboles |=: et |=:>)
										case 2:
										case 6: 
											character(nucleus(p)) = rem_byte(Font::infos(a));
											break;
										// AB -> ACB (symboles |=:|, |=:|> et |=:|>>)
										case 3:
										case 7:
										case 11:
											r = newnoad();
											character(nucleus(r)) = rem_byte(Font::infos(a));
											fam(nucleus(r)) = fam(nucleus(q));
											link(q) = r;
											link(r) = p;
											if (op_byte(Font::infos(a)) < 11) // symboles |=:| et |=:|>
												math_type(nucleus(r)) = math_char;
											else // symbole |=:|>>
												math_type(nucleus(r)) = math_text_char; 
											break;
										// AB -> C (symbole =;)
										default:
											link(q) = link(p);
											character(nucleus(q)) = rem_byte(Font::infos(a));
											mem[subscr(q)] = mem[subscr(p)];
											mem[supscr(q)] = mem[supscr(p)];
											freenode(p, noad_size);
									}
									if (op_byte(Font::infos(a)) > 3)
										return;
									math_type(nucleus(q)) = math_char;
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
