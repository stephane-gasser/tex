#include "linebreak.h"
#include "newpenalty.h"
#include "deleteglueref.h"
#include "flushnodelist.h"
#include "newparamglue.h"
#include "popnest.h"
#include "finiteshrink.h"
#include "inittrie.h"
#include "getnode.h"
#include "trybreak.h"
#include "hyphenate.h"
#include "confusion.h"
#include "postlinebreak.h"
#include "freenode.h"

void linebreak(int finalwidowpenalty)
{
	bool autobreaking;
	halfword prevp, q, r, s, prevs;
	internalfontnumber f;
	smallnumber j;
	unsigned char c;
	packbeginline = mode_line;
	link(temp_head) = link(head);
	if ((tail >= himemmin))
		tail_append(newpenalty(10000));
	else 
		if (type(tail) != 10)
			tail_append(newpenalty(10000));
		else
		{
			type(tail) = 12;
			deleteglueref(info(tail+1));
			flushnodelist(link(tail+1));
			mem[tail+1].int_ = 10000;
		}
	link(tail) = newparamglue(14);
	initcurlang = prev_graf%0x1'00'00;
	initlhyf = prev_graf/4194304;
	initrhyf = (prev_graf/0x1'00'00)%64;
	popnest();
	noshrinkerroryet = true;
	if (subtype(left_skip()) && mem[left_skip()+3].int_)
		left_skip() = finiteshrink(left_skip());
	if (subtype(right_skip()) && mem[right_skip()+3].int_)
		right_skip() = finiteshrink(right_skip());
	q = left_skip();
	r = right_skip();
	background[1] = mem[q+1].int_+mem[r+1].int_;
	background[2] = 0;
	background[3] = 0;
	background[4] = 0;
	background[5] = 0;
	background[2+type(q)] = mem[q+2].int_;
	background[2+type(r)] = background[2+type(r)]+mem[r+2].int_;
	background[6] = mem[q+3].int_+mem[r+3].int_;
	minimumdemerits = 0x3F'FF'FF'FF;
	minimaldemerits[3] = 0x3F'FF'FF'FF;
	minimaldemerits[2] = 0x3F'FF'FF'FF;
	minimaldemerits[1] = 0x3F'FF'FF'FF;
	minimaldemerits[0] = 0x3F'FF'FF'FF;
	if (par_shape_ptr() == 0)
		if (dimen_par(hang_indent_code) == 0)
		{
			lastspecialline = 0;
			secondwidth = dimen_par(hsize_code);
			secondindent = 0;
		}
		else
		{
			lastspecialline = abs(int_par(hang_after_code));
			if (int_par(hang_after_code) < 0)
			{
				firstwidth = dimen_par(hsize_code)-abs(dimen_par(hang_indent_code));
				if (dimen_par(hang_indent_code) >= 0)
					firstindent = dimen_par(hang_indent_code);
				else
					firstindent = 0;
				secondwidth = dimen_par(hsize_code);
				secondindent = 0;
			}
			else
			{
				firstwidth = dimen_par(hsize_code);
				firstindent = 0;
				secondwidth = dimen_par(hsize_code)-abs(dimen_par(hang_indent_code));
				if (dimen_par(hang_indent_code) >= 0)
					secondindent = dimen_par(hang_indent_code);
				else
					secondindent = 0;
			}
		}
	else
	{
		lastspecialline = info(par_shape_ptr())-1;
		secondwidth = mem[par_shape_ptr()+2 * (lastspecialline+1)].int_;
		secondindent = mem[par_shape_ptr()+2 * lastspecialline+1].int_;
	}
	if (int_par(looseness_code) == 0)
		easyline = lastspecialline;
	else
		easyline = 0xFF'FF;
	threshold = int_par(pretolerance_code);
	if (threshold >= 0)
	{
		secondpass = false;
		finalpass = false;
	}
	else
	{
		threshold = int_par(tolerance_code);
		secondpass = true;
		finalpass = (dimen_par(emergency_stretch_code) <= 0);
	}
	while (true)
	{
		if (threshold > 10000)
			threshold = 10000;
		if (secondpass)
		{
			if (trienotready)
				inittrie();
			curlang = initcurlang;
			lhyf = initlhyf;
			rhyf = initrhyf;
		}
		q = getnode(3);
		type(q) = 0;
		subtype(q) = 2;
		link(q) = active;
		link(q+1) = 0;
		info(q+1) = prev_graf+1;
		mem[q+2].int_ = 0;
		link(active) = q;
		for (int i = 1; i <= 6; i++)
			activewidth[i] = background[i];
		passive = 0;
		printednode = temp_head;
		passnumber = 0;
		fontinshortdisplay = 0;
		curp = link(temp_head);
		autobreaking = true;
		prevp = curp;
		while (curp && link(active) != active)
		{
			if ((curp >= himemmin))
			{
				prevp = curp;
				do
				{
					f = type(curp);
					activewidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(curp)].qqqq.b0].int_;
					curp = link(curp);
				} while (curp >= himemmin);
			}
			switch (type(curp))
			{
				case 0:
				case 1:
				case 2: 
					activewidth[1] += mem[curp+1].int_;
					break;
				case 8:
					if (subtype(curp) == 4)
					{
						curlang = link(curp+1);
						lhyf = type(curp+1);
						rhyf = subtype(curp+1);
					}
					break;
				case 10:
					if (autobreaking)
						if (prevp >= himemmin)
							trybreak(0, 0);
						else 
							if (type(prevp) < 9)
								trybreak(0, 0);
							else 
								if (type(prevp) == 11 && subtype(prevp) != 1)
									trybreak(0, 0);
					if (subtype(info(curp+1)) && mem[info(curp+1)+3].int_)
						info(curp+1) = finiteshrink(info(curp+1));
					q = info(curp+1);
					activewidth[1] += mem[q+1].int_;
					activewidth[2+type(q)] += mem[q+2].int_;
					activewidth[6] += mem[q+3].int_;
					if (secondpass && autobreaking)
					{
						prevs = curp;
						s = link(prevs);
						if (s)
						{
							bool label31 = false;
							while (true)
							{
								if (s >= himemmin)
								{
									c = subtype(s);
									hf = type(s);
								}
								else 
									if (type(s) == 6)
										if (link(s+1) == 0)
										{
											prevs = s;
											s = link(prevs);
											continue;
										}
										else
										{
											q = link(s+1);
											c = subtype(q);
											hf = type(q);
										}
									else 
										if (type(s) == 11 && subtype(s) == 0)
										{
											prevs = s;
											s = link(prevs);
											continue;
										}
										else 
											if (type(s) == 8)
											{
												if (subtype(s) == 4)
												{
													curlang = link(s+1);
													lhyf = type(s+1);
													rhyf = subtype(s+1);
												}
												prevs = s;
												s = link(prevs);
												continue;
											}
											else
											{
												label31 = true;
												break;
											}
								if (lc_code(c))
									if (lc_code(c) == c && int_par(uc_hyph_code) > 0)
										break;
									else
									{
										label31 = true;
										break;
									}
								prevs = s;
								s = link(prevs);
							}
							while (!label31)
							{
								hyfchar = hyphenchar[hf];
								if (hyfchar < 0)
									break;
								if (hyfchar > 255)
									break;
								ha = prevs;
								if (lhyf+rhyf > 63)
									break;
								hn = 0;
								while (true)
								{
									if (s >= himemmin)
									{
										if (type(s) != hf)
											break;
										hyfbchar = subtype(s);
										c = hyfbchar;
										if (lc_code(c) == 0)
											break;
										if (hn == 63)
											break;
										hb = s;
										hn++;
										hu[hn] = c;
										hc[hn] = lc_code(c);
										hyfbchar = 256;
									}
									else 
										if (type(s) == 6)
										{
											if (type(s+1) != hf)
												break;
											j = hn;
											q = link(s+1);
											if (q > 0)
												hyfbchar = subtype(q);
											while (q > 0)
											{
												c = subtype(q);
												if (lc_code(c) == 0)
													break;
												if (j == 63)
													break;
												j++;
												hu[j] = c;
												hc[j] = lc_code(c);
												q = link(q);
											}
											hb = s;
											hn = j;
											if (subtype(s)%2)
												hyfbchar = fontbchar[hf];
											else
												hyfbchar = 256;
										}
										else 
											if (type(s) == 11 && subtype(s) == 0)
											{
												hb = s;
												hyfbchar = fontbchar[hf];
											}
											else
												break;
									s = link(s);
								}
								if (hn < lhyf+rhyf)
									break;
								bool label34 = true;
								while (label34)
								{
									if (s < himemmin)
										switch (type(s))
										{
											case 6: 
												break;
											case 11: 
												if (subtype(s))
												{
													label34 = false;
													continue;
												}
												break;
											case 8:
											case 10:
											case 12:
											case 3:
											case 5:
											case 4: 
												label34 = false;
												continue;
											default: 
												label31 = true;
												break;
										}
									s = link(s);
								}
								if (!label31)
									hyphenate();
								break;
							}
						}
					}
					break;
				case 11: 
					if (subtype(curp) == 1)
					{
						if (link(curp) < himemmin && autobreaking && type(link(curp)) == 10)
							trybreak(0, 0);
						activewidth[1] += mem[curp+1].int_;
					}
					else
						activewidth[1] += mem[curp+1].int_;
					break;
				case 6:
					f = type(curp+1);
					activewidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(curp+1)].qqqq.b0].int_;
					break;
				case 7:
					s = info(curp+1);
					discwidth = 0;
					if (s == 0)
						trybreak(int_par(ex_hyphen_penalty_code), 1);
					else
					{
						do
						{
							if (s >= himemmin)
							{
								f = type(s);
								discwidth += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s)].qqqq.b0].int_;
							}
							else
								switch (type(s))
								{
									case 6:
										f = type(s+1);
										discwidth += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s+1)].qqqq.b0].int_;
										break;
									case 0:
									case 1:
									case 2:
									case 11: 
										discwidth += mem[s+1].int_;
										break;
									default: 
										confusion(936); //disc3
								}
							s = link(s);
						} while (s);
						activewidth[1] += discwidth;
						trybreak(int_par(hyphen_penalty_code), 1);
						activewidth[1] -= discwidth;
					}
					r = subtype(curp);
					s = link(curp);
					while (r > 0)
					{
						if (s >= himemmin)
						{
							f = type(s);
							activewidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s)].qqqq.b0].int_;
						}
						else
							switch (type(s))
							{
								case 6:
									f = type(s+1);
									activewidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s+1)].qqqq.b0].int_;
									break;
								case 0:
								case 1:
								case 2:
								case 11: 
									activewidth[1] += mem[s+1].int_;
									break;
								default: 
									confusion(937); //disc4
							}
						r = r-1;
						s = link(s);
					}
					prevp = curp;
					curp = s;
					continue;
				case 9:
					autobreaking = subtype(curp) == 1;
					{
						if (link(curp) < himemmin && autobreaking && type(link(curp)) == 10)
							trybreak(0, 0);
						activewidth[1] += mem[curp+1].int_;
					}
					break;
				case 12: 
					trybreak(mem[curp+1].int_, 0);
					break;
				case 4:
				case 3:
				case 5: 
					break;
				default: 
					confusion(935); //paragraph
			}
			prevp = curp;
			curp = link(curp);
		}
		if (curp == 0)
		{
			trybreak(-10000, 1);
			if (link(active) != active)
			{
				r = link(active);
				fewestdemerits = 0x3F'FF'FF'FF;
				do
				{
					if (type(r) != 2 && mem[r+2].int_ < fewestdemerits)
					{
						fewestdemerits = mem[r+2].int_;
						bestbet = r;
					}
					r = link(r);
				} while (r != active);
				bestline = info(bestbet+1);
				if (int_par(looseness_code) == 0)
				{
					postlinebreak(finalwidowpenalty);
					q = link(active);
					while (q != active)
					{
						curp = link(q);
						if (type(q) == 2)
							freenode(q, 7);
						else
							freenode(q, 3);
						q = curp;
					}
					q = passive;
					while (q)
					{
						curp = link(q);
						freenode(q, 2);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
				r = link(active);
				actuallooseness = 0;
				do
				{
					if (type(r) != 2)
					{
						linediff = info(r+1)-bestline;
						if ((linediff < actuallooseness && int_par(looseness_code) <= linediff) || (linediff > actuallooseness && int_par(looseness_code) >= linediff))
						{
							bestbet = r;
							actuallooseness = linediff;
							fewestdemerits = mem[r+2].int_;
						}
						else 
							if (linediff == actuallooseness && mem[r+2].int_ < fewestdemerits)
							{
								bestbet = r;
								fewestdemerits = mem[r+2].int_;
							}
					}
					r = link(r);
				} while (r != active);
				bestline = info(bestbet+1);
				if (actuallooseness == int_par(looseness_code) || finalpass)
				{
					postlinebreak(finalwidowpenalty);
					q = link(active);
					while (q != active)
					{
						curp = link(q);
						if (type(q) == 2)
							freenode(q, 7);
						else
							freenode(q, 3);
						q = curp;
					}
					q = passive;
					while (q)
					{
						curp = link(q);
						freenode(q, 2);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
			}
		}
		q = link(active);
		while (q != active)
		{
			curp = link(q);
			if (type(q) == 2)
				freenode(q, 7);
			else
				freenode(q, 3);
			q = curp;
		}
		q = passive;
		while (q)
		{
			curp = link(q);
			freenode(q, 2);
			q = curp;
		}
		;
		if (!secondpass)
		{
			threshold = int_par(tolerance_code);
			secondpass = true;
			finalpass = dimen_par(emergency_stretch_code) <= 0;
		}
		else
		{
			background[2] += dimen_par(emergency_stretch_code);
			finalpass = true;
		}
	}
	postlinebreak(finalwidowpenalty);
	q = link(active);
	while (q != active)
	{
		curp = link(q);
		if (type(q) == 2)
			freenode(q, 7);
		else
			freenode(q, 3);
		q = curp;
	}
	q = passive;
	while (q)
	{
		curp = link(q);
		freenode(q, 2);
		q = curp;
	}
	packbeginline = 0;
}
