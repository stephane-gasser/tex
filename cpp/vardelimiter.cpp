#include "vardelimiter.h"
#include "newnullbox.h"
#include "heightplusdepth.h"
#include "stackintobox.h"
#include "charbox.h"
#include "half.h"

halfword vardelimiter(halfword d, smallnumber s, scaled v)
{
	internalfontnumber f = 0;
	scaled w = 0;
	bool largeattempt = false;
	smallnumber z = mem[d].qqqq.b0;
	quarterword x = mem[d].qqqq.b1;
	bool label40 = false;
	fourquarters q;
	while (true)
	{
		if (z || x)
		{
			z += s+16;
			do
			{
				z -= 16;
				g = fam_fnt(z);
				if (g)
				{
					auto y = x;
					if (y >= fontbc[g] && y <= fontec[g])
					{
						bool label22;
						do 
						{
							label22 = false;
							q = fontinfo[charbase[g]+y].qqqq;
							if (q.b0 > 0)
							{
								if (q.b2%4 == 3)
								{
									f = g;
									c = y;
									label40 = true;
									break;
								}
								eightbits hd = q.b1;
								scaled u = fontinfo[heightbase[g]+hd/16].int_+fontinfo[depthbase[g]+hd%16].int_;
								if (u > w)
								{
									f = g;
									c = y;
									w = u;
									if (u >= v)
									{
										label40 = true;
										break;
									}
								}
								if (q.b2%4 == 2)
								{
									y = q.b3;
									label22 = true;
								}
							}
						} while (label22);
						if (label40)
							break;
					}
				}
			} while (z >= 16);
		}
		if (!largeattempt && !label40)
		{
			largeattempt = true;
			z = mem[d].qqqq.b2;
			x = mem[d].qqqq.b3;
		}
	}
	halfword b;
	if (f)
		if (q.b2%4 == 3)
		{
			b = newnullbox();
			type(b) = 1;
			fourquarters r = fontinfo[extenbase[f]+q.b3].qqqq;
			c = r.b3;
			auto u = heightplusdepth(f, c);
			w = 0;
			q = fontinfo[charbase[f]+c].qqqq;
			mem[b+1].int_ = fontinfo[widthbase[f]+q.b0].int_+fontinfo[italicbase[f]+q.b2/4].int_;
			c = r.b2;
			if (c)
				w += heightplusdepth(f, c);
			c = r.b1;
			if (c)
				w += heightplusdepth(f, c);
			c = r.b0;
			if (c)
				w += heightplusdepth(f, c);
			int n = 0;
			if (u > 0)
				while (w < v)
				{
					w += u;
					n++;
					if (r.b1)
						w += u;
				}
			c = r.b2;
			if (c)
				stackintobox(b, f, c);
			c = r.b3;
			for (int m = 1; m <= n; m++)
				stackintobox(b, f, c);
			c = r.b1;
			if (c)
			{
				stackintobox(b, f, c);
				c = r.b3;
				for (int m = 1; m <= n; m++)
					stackintobox(b, f, c);
			}
			c = r.b0;
			if (c)
				stackintobox(b, f, c);
			mem[b+2].int_ = w-mem[b+3].int_;
		}
		else
			b = charbox(f, c);
	else
	{
		b = newnullbox();
		mem[b+1].int_ = eqtb[5841].int_;
	}
	mem[b+4].int_ = half(mem[b+3].int_-mem[b+2].int_)-fontinfo[22+parambase[fam_fnt(2+s)]].int_;
	return b;
}
