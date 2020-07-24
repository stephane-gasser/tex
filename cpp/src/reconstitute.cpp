#include "reconstitute.h"
#include "getavail.h"
#include "noeud.h"
#include "police.h"

static void set_cur_r(int j, int n, halfword &curr, halfword &currh, halfword hchar)
{
	curr = j < n ? hu[j+1] : bchar;
	currh = hyf[j]%2 ? hchar : non_char;
}

static void wrap_lig(bool test, halfword &t)
{
	if (ligaturepresent)
	{
		halfword p = newligature(hf, curl, link(curq));
		if (lfthit)
		{
			subtype(p) = 2;
			lfthit = false;
		}
		if (test && ligstack == 0)
		{
			subtype(p)++;
			rthit = false;
		}
		link(curq) = p;
		t = p;
		ligaturepresent = false;
	}
}

static void pop_lig_stack(smallnumber &j, halfword &t)
{
	if (lig_ptr(ligstack) > 0)
	{
		link(t) = lig_ptr(ligstack);
		t = link(t);
		j++;
	}
}

smallnumber reconstitute(smallnumber j, smallnumber n, halfword bchar, halfword hchar)
{
	halfword p, t;
	halfword currh, testchar;
	scaled w;
	fontindex k;
	hyphenpassed = 0;
	t = hold_head;
	w = 0;
	link(hold_head) = 0;
	curl = hu[j];
	curq = t;
	if (j == 0)
	{
		ligaturepresent = initlig;
		p = initlist;
		if (ligaturepresent)
			lfthit = initlft;
		while (p > 0)
		{
			link(t) = getavail();
			t = link(t);
			type(t) = hf;
			subtype(t) = subtype(p);
			p = link(p);
		}
	}
	else 
		if (curl < non_char)
		{
			link(t) = getavail();
			t = link(t);
			type(t) = hf;
			subtype(t) = curl;
		}
	ligstack = 0;
	set_cur_r(j, n, curr, currh, hchar);
	bool skipLoop;
	bool recommence;
	do
	{
		recommence = false;
		skipLoop = false;
		if (curl == 256)
		{
			k = fonts[hf].bcharlabel;
			if (k == 0)
				skipLoop = true;
		}
		else
		{
			if (fonts[hf].char_tag(curl) != lig_tag)
				skipLoop = true;
			else
			{
				k = fonts[hf].lig_kern_start(fonts[hf].char_info(curl));
				if (skip_byte(fontinfo[k].qqqq) > stop_flag)
					k = fonts[hf].lig_kern_restart(fontinfo[k].qqqq);
			}
		}
		if (!skipLoop)
			testchar = currh < non_char ? currh : curr;
		while (!skipLoop)
		{
			if (next_char(fontinfo[k].qqqq) == testchar)
				if (skip_byte(fontinfo[k].qqqq) <= stop_flag)
					if (currh < non_char)
					{
						hyphenpassed = j;
						hchar = non_char;
						currh = non_char;
						recommence = true;
						break;
					}
					else
					{
						if (hchar < non_char && hyf[j]%2)
						{
							hyphenpassed = j;
							hchar = non_char;
						}
						if (op_byte(fontinfo[k].qqqq) < kern_flag)
						{
							if (curl == non_char)
								lfthit = true;
							if (j == n && ligstack == 0)
								rthit = true;
							switch (op_byte(fontinfo[k].qqqq))
							{
								// AB -> CB (symboles =:| et =:|>)
								case 1:
								case 5:
									curl = rem_byte(fontinfo[k].qqqq);
									ligaturepresent = true;
									break;
								// AB -> AC (symboles |=: et |=:>)
								case 2:
								case 6:
									curr = rem_byte(fontinfo[k].qqqq);
									if (ligstack > 0)
										character(ligstack) = curr;
									else
									{
										ligstack = newligitem(curr);
										if (j == n)
											bchar = non_char;
										else
										{
											p = getavail();
											lig_ptr(ligstack) = p;
											character(p) = hu[j+1];
											font(p) = hf;
										}
									}
									break;
								// AB -> ACB (symbole |=:|)
								case 3:
									curr = rem_byte(fontinfo[k].qqqq);
									p = ligstack;
									ligstack = newligitem(curr);
									link(ligstack) = p;
									break;
								// AB -> ACB (symboles |=:|> et |=:|>>)
								case 7:
								case 11:
									wrap_lig(false, t);
									curq = t;
									curl = rem_byte(fontinfo[k].qqqq);
									ligaturepresent = true;
									break;
								// AB -> C (symbole !=)
								default:
									curl = rem_byte(fontinfo[k].qqqq);
									ligaturepresent = true;
									if (ligstack > 0)
									{
										pop_lig_stack(j, t);
										p = ligstack;
										ligstack = link(p);
										freenode(p, 2);
										if (ligstack == 0)
											set_cur_r(j, n, curr, currh, hchar);
										else
											curr = subtype(ligstack);
									}
									else 
										if (j == n)
										{
											skipLoop = true;
											continue;
										}
										else
										{
											link(t) = getavail();
											t = link(t);
											type(t) = hf;
											subtype(t) = curr;
											j++;
											set_cur_r(j, n, curr, currh, hchar);
										}
							}
							if (op_byte(fontinfo[k].qqqq) > 4 && op_byte(fontinfo[k].qqqq) != 7)
							{
								skipLoop = true;
								continue;
							}
							recommence = true;
							break;
						}
						w = fonts[hf].char_kern(fontinfo[k].qqqq);
						skipLoop = true;
						continue;
					}
			if (skip_byte(fontinfo[k].qqqq) >= 128)
				if (currh == 256)
				{
					skipLoop = true;
					continue;
				}
				else
				{
					currh = 256;
					recommence = true;
					break;
				}
			k += skip_byte(fontinfo[k].qqqq)+1;
		}
		if (recommence)
			continue;
		wrap_lig(rthit, t);
		if (w)
		{
			link(t) = newkern(w);
			t = link(t);
			w = 0;
		}
		if (ligstack > 0)
		{
			curq = t;
			curl = subtype(ligstack);
			ligaturepresent = true;
			pop_lig_stack(j, t);
			p = ligstack;
			ligstack = link(p);
			freenode(p, 2);
			if (ligstack == 0)
				set_cur_r(j, n, curr, currh, hchar);
			else
				curr = subtype(ligstack);
			recommence = true;
			continue;
		}
	} while (recommence);
	return j;
}
