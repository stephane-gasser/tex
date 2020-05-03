#include "trybreak.h"
#include "confusion.h"
#include "getnode.h"
#include "badness.h"
#include "freenode.h"

void trybreak(int pi, smallnumber breaktype)
{
	halfword r, prevr, oldl;
	bool nobreakyet;
	halfword prevprevr, s, q, v;
	int t;
	internalfontnumber f;
	halfword l;
	bool noderstaysactive;
	scaled linewidth;
	char fitclass;
	halfword b;
	int d;
	bool artificialdemerits;
	halfword savelink;
	scaled shortfall;
	if (abs(pi) >= 10000)
		if (pi > 0)
			return;
		else
		pi = -10000;
	nobreakyet = true;
	prevr = active;
	oldl = 0;
	for (int i = 1; i <= 6; i++)
		curactivewidth[i] = activewidth[i];
	while (true)
	{
		r = link(prevr);
		if (type(r) == 2)
		{
			for (int i = 1; i <= 6; i++)
				curactivewidth[i] = curactivewidth[i]+mem[r+1].int_;
			prevprevr = prevr;
			prevr = r;
			continue;
		}
		l = info(r+1);
		if (l > oldl)
		{
			if ((minimumdemerits < max_dimen) and ((oldl != easyline) or (r == active)))
			{
				if (nobreakyet)
				{
					nobreakyet = false;
					for (int i = 1; i <= 6; i++)
						breakwidth[i] = background[i];
					s = curp;
					if (breaktype > 0)
						if (curp)
						{
							t = subtype(curp);
							v = curp;
							s = link(curp+1);
							while (t > 0)
							{
								t--;
								v = link(v);
								if (v >= himemmin)
								{
									f = type(v);
									breakwidth[1] += -fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(v)].qqqq.b0].int_;
								}
								else
									switch (type(v))
									{
										case 6:
											f = type(v+1);
											breakwidth[1] += -fontinfo[widthbase[f]+fontinfo[charbase[f]+type(v+1)].qqqq.b0].int_;
											break;
										case 0:
										case 1:
										case 2:
										case 11: 
											breakwidth[1] -= mem[v+1].int_;
											break;
										default: 
											confusion(922); //disc1
									}
							}
							while (s)
							{
								if (s >= himemmin)
								{
									f = type(s);
									breakwidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s)].qqqq.b0].int_;
								}
								else
									switch (type(s))
									{
										case 6:
											f = type(s+1);
											breakwidth[1] += fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(s+1)].qqqq.b0].int_;
											break;
										case 0:
										case 1:
										case 2:
										case 11: 
											breakwidth[1] += mem[s+1].int_;
											break;
										default: 
											confusion(923); //disc2
									}
								s = link(s);
							}
							breakwidth[1] += discwidth;
							if (link(curp+1) == 0)
								s = link(v);
						}
					while (s)
					{
						if (s >= himemmin)
							continue;
						switch (type(s))
						{
							case 10:
								v = info(s+1);
								breakwidth[1] -= mem[v+1].int_;
								breakwidth[2+type(v)] -= mem[v+2].int_;
								breakwidth[6] -= mem[v+3].int_;
								break;
							case 12: 
								break;
							case 9: 
								breakwidth[1] -= mem[s+1].int_;
								break;
							case 11: 
								if (subtype(s) != 1)
									continue;
								else
									breakwidth[1] -= mem[s+1].int_;
								break;
							default: 
								continue;
						}
						s = link(s);
					}
				}
				if (type(prevr) == 2)
					for (int i = 1; i <= 6; i++)
						mem[prevr+i].int_ += -curactivewidth[i]+breakwidth[i];
				else 
					if (prevr == active)
						for (int i = 1; i <= 6; i++)
							activewidth[i] = breakwidth[i];
					else
					{
						q = getnode(7);
						link(q) = r;
						type(q) = 2;
						subtype(q) = 0;
						for (int i = 1; i <= 6; i++)
							mem[q+i].int_ = breakwidth[i]-curactivewidth[i];
						link(prevr) = q;
						prevprevr = prevr;
						prevr = q;
					}
				if (abs(int_par(adj_demerits_code)) >= max_dimen-minimumdemerits)
					minimumdemerits = 1073741822;
				else
					minimumdemerits += abs(int_par(adj_demerits_code));
				for (fitclass = 0; fitclass <= 3; fitclass++)
				{
					if (minimaldemerits[fitclass] <= minimumdemerits)
					{
						q = getnode(2);
						link(q) = passive;
						passive = q;
						link(q+1) = curp;
						info(q+1) = bestplace[fitclass];
						q = getnode(3);
						link(q+1) = passive;
						info(q+1) = bestplline[fitclass]+1;
						subtype(q) = fitclass;
						type(q) = breaktype;
						mem[q+2].int_ = minimaldemerits[fitclass];
						link(q) = r;
						link(prevr) = q;
						prevr = q;
					}
					minimaldemerits[fitclass] = max_dimen;
				}
				minimumdemerits = max_dimen;
				if (r != active)
				{
					q = getnode(7);
					link(q) = r;
					type(q) = 2;
					subtype(q) = 0;
					for (int i = 1; i <= 6; i++)
						mem[q+i].int_ = curactivewidth[i]-breakwidth[i];
					link(prevr) = q;
					prevprevr = prevr;
					prevr = q;
				}
			}
			if (r == active)
				return;
			if (l > easyline)
			{
				linewidth = secondwidth;
				oldl = 65534;
			}
			else
			{
				oldl = l;
				if (l > lastspecialline)
					linewidth = secondwidth;
				else 
					if (par_shape_ptr() == 0)
						linewidth = firstwidth;
					else
						linewidth = mem[par_shape_ptr()+2*l].int_;
			}
		}
		artificialdemerits = false;
		shortfall = linewidth-curactivewidth[1];
		if (shortfall > 0)
			if (curactivewidth[3] || curactivewidth[4] || curactivewidth[5])
			{
				b = 0;
				fitclass = 2;
			}
			else
			{
				if (shortfall > 7230584 && curactivewidth[2] < 1663497)
				{
					b = 10000;
					fitclass = 0;
				}
				else
				{
					b = badness(shortfall, curactivewidth[2]);
					if (b > 12)
						if (b > 99)
							fitclass = 0;
						else
							fitclass = 1;
					else
						fitclass = 2;
				}
			}
		else
		{
			if (-shortfall > curactivewidth[6])
				b = 10001;
			else
				b = badness(-shortfall, curactivewidth[6]);
			if (b > 12)
				fitclass = 3;
			else
				fitclass = 2;
		}
		if (b > 10000 || pi == -10000)
		{
			if (finalpass && minimumdemerits == max_dimen && link(r) == active &&prevr == active)
				artificialdemerits = true;
			else 
				if (b > threshold)
				{
					link(prevr) = link(r);
					freenode(r, 3);
					if (prevr == active)
					{
						r = link(active);
						if (type(r) == 2)
						{
							for (int i = 1; i <= 6; i++)
								curactivewidth[i] = activewidth[i] = activewidth[i]+mem[r+i].int_;
							link(active) = link(r);
							freenode(r, 7);
						}
					}
					else 
						if (type(prevr) == 2)
						{
							r = link(prevr);
							if (r == active)
							{
								for (int i = 1; i <= 6; i++)
									curactivewidth[i] -= mem[prevr+1].int_;
								link(prevprevr) = active;
								freenode(prevr, 7);
								prevr = prevprevr;
							}
							else 
								if (type(r) == 2)
								{
									for (int i = 1; i <= 6; i++)
									{
										curactivewidth[i] += mem[r+1].int_;
										mem[prevr+i].int_ += mem[r+i].int_;
									}
									link(prevr) = link(r);
									freenode(r, 7);
								}
						}
					continue;
				}
			noderstaysactive = false;
		}
		else
		{
			prevr = r;
			if (b > threshold)
				continue;
			noderstaysactive = true;
		}
		if (artificialdemerits)
			d = 0;
		else
		{
			d = int_par(line_penalty_code)+b;
			if (abs(d) >= 10000)
				d = 100000000;
			else
				d *= d;
			if (pi)
				if (pi > 0)
					d += pi*pi;
				else 
					if (pi > -10000)
						d -= pi*pi;
			if (breaktype == 1 && type(r) == 1)
				if (curp)
					d += int_par(double_hyphen_demerits_code);
				else
				d += int_par(final_hyphen_demerits_code);
			if (abs(fitclass-subtype(r)) > 1)
				d += int_par(adj_demerits_code);
		}
		d += mem[r+2].int_;
		if (d <= minimaldemerits[fitclass])
		{
			minimaldemerits[fitclass] = d;
			bestplace[fitclass] = link(r+1);
			bestplline[fitclass] = l;
			if (d < minimumdemerits)
				minimumdemerits = d;
		}
		if (noderstaysactive)
			continue;
		link(prevr) = link(r);
		freenode(r, 3);
		if (prevr == active)
		{
			r = link(active);
			if (type(r) == 2)
			{
				for (int i = 1; i <= 6; i++)
					curactivewidth[i] = activewidth[i] = activewidth[i]+mem[r+i].int_;
				link(active) = link(r);
				freenode(r, 7);
			}
		}
		else 
			if (type(prevr) == 2)
			{
				r = link(prevr);
				if (r == active)
				{
					for (int i = 1; i <= 6; i++)
						curactivewidth[i] -= mem[prevr+1].int_;
					link(prevprevr) = active;
					freenode(prevr, 7);
					prevr = prevprevr;
				}
				else 
					if (type(r) == 2)
					{
						for (int i = 1; i <= 6; i++)
						{
							curactivewidth[i] += mem[r+1].int_;
							mem[prevr+i].int_ += mem[r+i].int_;
						}
						link(prevr) = link(r);
						freenode(r, 7);
					}
			}
	}
}
