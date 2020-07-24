#include "makeord.h"
#include "fetch.h"
#include "noeud.h"
#include "police.h"

void makeord(halfword q)
{
	bool label20 = false;
	do
	{
		if (link(q+3) == 0 && link(q+2) == 0 && link(q+1) == 1)
		{
			halfword p = link(q);
			if (p && type(p) >= 16 && type(p) <= 22 && link(p+1) == 1 && type(p+1) == type(q+1))
			{
				link(q+1) = 4;
				fetch(q+1);
				if (char_tag(curi) == lig_tag)
				{
					int a = fonts[curf].lig_kern_start(curi);
					curc = character(lig_char(p));
					curi = fontinfo[a].qqqq;
					if (skip_byte(curi) > stop_flag)
					{
						a = fonts[curf].lig_kern_restart(curi);
						curi = fontinfo[a].qqqq;
					}
					while (true)
					{
						halfword r;
						if (next_char(curi) == curc)
							if (skip_byte(curi) <= stop_flag)
								if (op_byte(curi) >= kern_flag)
								{
									p = newkern(fonts[curf].char_kern(curi));
									link(p) = link(q);
									link(q) = p;
									return;
								}
								else
								{
									switch (op_byte(curi))
									{
										// AB -> CB (symboles =:| et =:|>)
										case 1:
										case 5: 
											subtype(q+1) = rem_byte(curi);
											break;
										// AB -> AC (symboles |=: et |=:>)
										case 2:
										case 6: 
											subtype(p+1) = rem_byte(curi);
											break;
										// AB -> ACB (symboles |=:|, |=:|> et |=:|>>)
										case 3:
										case 7:
										case 11:
											r = newnoad();
											subtype(r+1) = rem_byte(curi);
											type(r+1) = type(q+1);
											link(q) = r;
											link(r) = p;
											if (op_byte(curi) < 11) // symboles |=:| et |=:|>
												link(r+1) = 1;
											else // symbole |=:|>>
												link(r+1) = 4; 
											break;
										// AB -> C (symbole =;)
										default:
											link(q) = link(p);
											subtype(q+1) = rem_byte(curi);
											mem[q+3] = mem[p+3];
											mem[q+2] = mem[p+2];
											freenode(p, 4);
									}
									if (op_byte(curi) > 3)
										return;
									link(q+1) = 1;
									label20 = true;
								}
						if (label20)
							break;
						if (skip_byte(curi) >= stop_flag)
							return;
						a += skip_byte(curi)+1;
						curi = fontinfo[a].qqqq;
					}
				}
			}
		}
	} while (label20);
}
