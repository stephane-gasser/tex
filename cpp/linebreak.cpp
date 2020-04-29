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
	packbeginline = curlist.mlfield;
	link(29997) = link(curlist.headfield);
	if ((curlist.tailfield >= himemmin))
	{
		link(curlist.tailfield) = newpenalty(10000);
		curlist.tailfield = link(curlist.tailfield);
	}
	else 
		if (type(curlist.tailfield) != 10)
		{
			link(curlist.tailfield) = newpenalty(10000);
			curlist.tailfield = link(curlist.tailfield);
		}
		else
		{
			type(curlist.tailfield) = 12;
			deleteglueref(info(curlist.tailfield+1));
			flushnodelist(link(curlist.tailfield+1));
			mem[curlist.tailfield+1].int_ = 10000;
		}
	link(curlist.tailfield) = newparamglue(14);
	initcurlang = curlist.pgfield%65536;
	initlhyf = curlist.pgfield/4194304;
	initrhyf = (curlist.pgfield/65536)%64;
	popnest();
	noshrinkerroryet = true;
	if (subtype(eqtb[2889].hh.rh) && mem[eqtb[2889].hh.rh+3].int_)
		eqtb[2889].hh.rh = finiteshrink(eqtb[2889].hh.rh);
	if (subtype(eqtb[2890].hh.rh)  &&mem[eqtb[2890].hh.rh+3].int_)
		eqtb[2890].hh.rh = finiteshrink(eqtb[2890].hh.rh);
	q = eqtb[2889].hh.rh;
	r = eqtb[2890].hh.rh;
	background[1] = mem[q+1].int_+mem[r+1].int_;
	background[2] = 0;
	background[3] = 0;
	background[4] = 0;
	background[5] = 0;
	background[2+type(q)] = mem[q+2].int_;
	background[2+type(r)] = background[2+type(r)]+mem[r+2].int_;
	background[6] = mem[q+3].int_+mem[r+3].int_;
	minimumdemerits = 1073741823;
	minimaldemerits[3] = 1073741823;
	minimaldemerits[2] = 1073741823;
	minimaldemerits[1] = 1073741823;
	minimaldemerits[0] = 1073741823;
	if (eqtb[3412].hh.rh == 0)
		if (eqtb[5847].int_ == 0)
		{
			lastspecialline = 0;
			secondwidth = eqtb[5833].int_;
			secondindent = 0;
		}
		else
		{
			lastspecialline = abs(eqtb[5304].int_);
			if (eqtb[5304].int_ < 0)
			{
				firstwidth = eqtb[5833].int_-abs(eqtb[5847].int_);
				if (eqtb[5847].int_ >= 0)
					firstindent = eqtb[5847].int_;
				else
					firstindent = 0;
				secondwidth = eqtb[5833].int_;
				secondindent = 0;
			}
			else
			{
				firstwidth = eqtb[5833].int_;
				firstindent = 0;
				secondwidth = eqtb[5833].int_-abs(eqtb[5847].int_);
				if (eqtb[5847].int_ >= 0)
					secondindent = eqtb[5847].int_;
				else
					secondindent = 0;
			}
		}
	else
	{
		lastspecialline = info(eqtb[3412].hh.rh)-1;
		secondwidth = mem[eqtb[3412].hh.rh+2 * (lastspecialline+1)].int_;
		secondindent = mem[eqtb[3412].hh.rh+2 * lastspecialline+1].int_;
	}
	if (eqtb[5282].int_ == 0)
		easyline = lastspecialline;
	else
		easyline = 65535;
	threshold = eqtb[5263].int_;
	if (threshold >= 0)
	{
		secondpass = false;
		finalpass = false;
	}
	else
	{
		threshold = eqtb[5264].int_;
		secondpass = true;
		finalpass = (eqtb[5850].int_ <= 0);
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
		link(q) = 29993;
		link(q+1) = 0;
		info(q+1) = curlist.pgfield+1;
		mem[q+2].int_ = 0;
		link(29993) = q;
		for (int i = 1; i <= 6; i++)
			activewidth[i] = background[i];
		passive = 0;
		printednode = 29997;
		passnumber = 0;
		fontinshortdisplay = 0;
		curp = link(29997);
		autobreaking = true;
		prevp = curp;
		while (curp && link(29993) != 29993)
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
								if (eqtb[4239+c].hh.rh)
									if (eqtb[4239+c].hh.rh == c && eqtb[5301].int_ > 0)
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
										if (eqtb[4239+c].hh.rh == 0)
											break;
										if (hn == 63)
											break;
										hb = s;
										hn++;
										hu[hn] = c;
										hc[hn] = eqtb[4239+c].hh.rh;
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
												if (eqtb[4239+c].hh.rh == 0)
													break;
												if (j == 63)
													break;
												j++;
												hu[j] = c;
												hc[j] = eqtb[4239+c].hh.rh;
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
						trybreak(eqtb[5267].int_, 1);
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
						trybreak(eqtb[5266].int_, 1);
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
			if (link(29993) != 29993)
			{
				r = link(29993);
				fewestdemerits = 1073741823;
				do
				{
					if (type(r) != 2 && mem[r+2].int_ < fewestdemerits)
					{
						fewestdemerits = mem[r+2].int_;
						bestbet = r;
					}
					r = link(r);
				} while (r != 29993);
				bestline = info(bestbet+1);
				if (eqtb[5282].int_ == 0)
				{
					postlinebreak(finalwidowpenalty);
					q = link(29993);
					while (q != 29993)
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
				r = link(29993);
				actuallooseness = 0;
				do
				{
					if (type(r) != 2)
					{
						linediff = info(r+1)-bestline;
						if ((linediff < actuallooseness && eqtb[5282].int_ <= linediff) || (linediff > actuallooseness && eqtb[5282].int_ >= linediff))
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
				} while (r != 29993);
				bestline = info(bestbet+1);
				if (actuallooseness == eqtb[5282].int_ || finalpass)
				{
					postlinebreak(finalwidowpenalty);
					q = link(29993);
					while (q != 29993)
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
		q = link(29993);
		while (q != 29993)
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
			threshold = eqtb[5264].int_;
			secondpass = true;
			finalpass = eqtb[5850].int_ <= 0;
		}
		else
		{
			background[2] += eqtb[5850].int_;
			finalpass = true;
		}
	}
	postlinebreak(finalwidowpenalty);
	q = link(29993);
	while (q != 29993)
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
