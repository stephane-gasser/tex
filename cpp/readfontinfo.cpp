#include "readfontinfo.h"
#include "printnl.h"
#include "print.h"
#include "sprintcs.h"
#include "printchar.h"
#include "printfilename.h"
#include "printscaled.h"
#include "printint.h"
#include "error.h"
#include "bclose.h"
#include "packfilename.h"
#include "bopenin.h"
#include "xnoverd.h"

void notLoadable(halfword u, strnumber nom, strnumber aire, scaled s, bool fileopened)
{
	printnl(262); //! 
	print(801); //Font 
	sprintcs(u);
	printchar('=');
	printfilename(nom, aire, 338); //
	if (s >= 0)
	{
		print(741); // at 
		printscaled(s);
		print(397); //pt
	}
	else if (s != -1000)
	{
		print(802); // scaled 
		printint(-s);
	}
	if (fileopened)
		print(803); // not loadable: Bad metric (TFM) file
	else
		print(804); // not loadable: Metric (TFM) file not found
	helpptr = 5;
	helpline[4] = 805; //I wasn't able to read the size data for this font,
	helpline[3] = 806; //so I will ignore the font specification.
	helpline[2] = 807; //[Wizards can fix TFM files using TFtoPL/PLtoTF.]
	helpline[1] = 808; //You might try inserting a different font spec;
	helpline[0] = 809; //e.g., type `I\font<same font id>=<substitute font name>'.
	error();
	if (fileopened)
		bclose(tfmfile);
}

internalfontnumber readfontinfo(halfword u, strnumber nom, strnumber aire, scaled s)
{
	bool fileopened = false;
	if (aire == 338) //
		packfilename(nom, 784, 810); //TeXfonts://.tfm
	else
		packfilename(nom, aire, 810); //.tfm
	if (!bopenin(tfmfile))
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	fileopened = true;
	halfword lf = tfmfile.get();
	if (lf > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	lf = lf*0x1'00+tfmfile.get();
	halfword lh = tfmfile.get();
	if (lh > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	lh = lh*0x1'00+tfmfile.get();
	halfword bc = tfmfile.get();
	if (bc > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	bc = bc*0x1'00+tfmfile.get();
	halfword ec = tfmfile.get();
	if (ec > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	ec = ec*0x1'00+tfmfile.get();
	if (bc > ec+1 || ec > 255)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	if (bc > 255)
		bc = 1;
	ec = 0;
	halfword nw = tfmfile.get();
	if (nw > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	nw = nw*0x1'00+tfmfile.get();
	halfword nh = tfmfile.get();
	if (nh > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	nh = nh*0x1'00+tfmfile.get();
	halfword nd = tfmfile.get();
	if (nd > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	nd = nd*0x1'00+tfmfile.get();
	halfword ni = tfmfile.get();
	if (ni > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	ni = ni*0x1'00+tfmfile.get();
	halfword nl = tfmfile.get();
	if (nl > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	nl = nl*0x1'00+tfmfile.get();
	halfword nk = tfmfile.get();
	if (nk > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	nk = nk*0x1'00+tfmfile.get();
	halfword ne = tfmfile.get();
	if (ne > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	ne = ne*0x1'00+tfmfile.get();
	halfword np = tfmfile.get();
	if (np > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	np = np*0x1'00+tfmfile.get();
	if (lf != 6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	if (nw == 0 || nh == 0 || nd == 0 || ni == 0)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	lf -= 6+lh;
	if (np < 7)
		lf += 7-np;
	if (fontptr == fontmax || fmemptr+lf > fontmemsize)
	{
		printnl(262); //! 
		print(801); //Font 
		sprintcs(u);
		printchar('=');
		printfilename(nom, aire, 338); //
		if (s >= 0)
		{
			print(741); // at 
			printscaled(s);
			print(397); //pt
		}
		else 
			if (s != -1000)
			{
				print(802); // scaled 
				printint(-s);
			}
		print(811); // not loaded: Not enough room left
		{
		helpptr = 4;
		helpline[3] = 812; //I'm afraid I won't be able to make use of this font,
		helpline[2] = 813; //because my memory for character-size data is too small.
		helpline[1] = 814; //If you're really stuck, ask a wizard to enlarge me.
		helpline[0] = 815; //Or maybe try `I\font<same font id>=<name of loaded font>'.
		}
		error();
		if (fileopened)
			bclose(tfmfile);
		return 0;
	}
	f = fontptr+1;
	charbase[f] = fmemptr-bc;
	widthbase[f] = charbase[f]+ec+1;
	heightbase[f] = widthbase[f]+nw;
	depthbase[f] = heightbase[f]+nh;
	italicbase[f] = depthbase[f]+nd;
	ligkernbase[f] = italicbase[f]+ni;
	kernbase[f] = ligkernbase[f]+nl-0x80'00;
	extenbase[f] = kernbase[f]+0x80'00+nk;
	parambase[f] = extenbase[f]+ne;
	if (lh < 2)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	eightbits a, b, c, d;
	fourquarters qw;
	qw.b0 = a = tfmfile.get();
	qw.b1 = b = tfmfile.get();
	qw.b2 = c = tfmfile.get();
	qw.b3 = d = tfmfile.get();
	fontcheck[f] = qw;
	scaled z = tfmfile.get();
	if (z > 127)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	z = z*0x1'00+tfmfile.get();
	z = z*0x1'00+tfmfile.get();
	z = z*16+tfmfile.get()/16;
	if (z < 0x1'00'00)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	while (lh > 2)
	{
		tfmfile.get();
		tfmfile.get();
		tfmfile.get();
		tfmfile.get();
		lh--;
	}
	fontdsize[f] = z;
	if (s != -1000)
		if (s >= 0)
			z = s;
		else
			z = xnoverd(z, -s, 1000);
	fontsize[f] = z;
	for (int k = fmemptr; k < widthbase[f]; k++)
	{
		a = tfmfile.get();
		qw.b0 = a;
		b = tfmfile.get();
		qw.b1 = b;
		c = tfmfile.get();
		qw.b2 = c;
		d = tfmfile.get();
		qw.b3 = d;
		fontinfo[k].qqqq = qw;
		if (a >= nw || b/16 >= nh || b%16 >= nd || c/4 >= ni)
		{
			notLoadable(u, nom, aire, s, fileopened);
			return 0;
		}
		switch (c%4)
		{
			case 1: 
				if (d >= nl)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
				break;
			case 3: 
				if (d >= ne)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
				break;
			case 2:
				if (d < bc || d > ec)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
				while (d < k+bc-fmemptr)
				{
					qw = fontinfo[charbase[f]+d].qqqq;
					if (qw.b2%4 != 2)
						break;
					d = qw.b3;
					if (d == k+bc-fmemptr)
					{
						notLoadable(u, nom, aire, s, fileopened);
						return 0;
					}
				}
		}
	}
	int alpha = 16;
	while (z >= 8388608)
	{
		z /= 2;
		alpha *= 2;
	}
	int beta = 0x1'00/alpha;
	alpha *= z;
	for (int k = widthbase[f]; k < ligkernbase[f]; k++)
	{
		a = tfmfile.get();
		b = tfmfile.get();
		c = tfmfile.get();
		d = tfmfile.get();
		scaled sw = ((((d*z)/0x1'00+c*z)/0x1'00)+b*z)/beta;
		if (a == 0)
			fontinfo[k].int_ = sw;
		else 
			if (a == 255)
			fontinfo[k].int_ = sw-alpha;
		else
		{
			notLoadable(u, nom, aire, s, fileopened);
			return 0;
		}
	}
	if (fontinfo[widthbase[f]].int_ != 0)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	if (fontinfo[heightbase[f]].int_ != 0)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	if (fontinfo[depthbase[f]].int_ != 0)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	if (fontinfo[italicbase[f]].int_ != 0)
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	int bchlabel = 0x7F'FF;
	bchar = 256;
	if (nl > 0)
	{
		for (int k = ligkernbase[f]; k < kernbase[f]+0x80'00; k++)
		{
			qw.b0 = a = tfmfile.get();
			qw.b1 = b = tfmfile.get();
			qw.b2 = c = tfmfile.get();
			qw.b3 = d = tfmfile.get();
			fontinfo[k].qqqq = qw;
			if (a > 128)
			{
				if (0x1'00*c+d >= nl)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
				if (a == 255 && k == ligkernbase[f])
					bchar = b;
			}
			else
			{
				if (b != bchar)
				{
					if (b < bc || b > ec)
					{
						notLoadable(u, nom, aire, s, fileopened);
						return 0;
					}
					qw = fontinfo[charbase[f]+b].qqqq;
					if (qw.b0 <= 0)
					{
						notLoadable(u, nom, aire, s, fileopened);
						return 0;
					}
				}
			if (c < 128)
			{
				if (d < bc || d > ec)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
				qw = fontinfo[charbase[f]+d].qqqq;
				if (qw.b0 <= 0)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
			}
			else 
				if (0x1'00*(c-0x80)+d >= nk)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
			if (a < 128)
				if (k-ligkernbase[f]+a+1 >= nl)
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
			}
		}
		if (a == 255)
			bchlabel = 0x1'00*c+d;
	}
	for (int k = kernbase[f]+0x80'00; k < extenbase[f]; k++)
	{
		a = tfmfile.get();
		b = tfmfile.get();
		c = tfmfile.get();
		d = tfmfile.get();
		scaled sw = ((((d*z)/0x1'00+c*z)/0x1'00)+b*z)/beta;
		if (a == 0)
			fontinfo[k].int_ = sw;
		else 
			if (a == 255)
				fontinfo[k].int_ = sw-alpha;
			else
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
	}
	for (int k = extenbase[f]; k < parambase[f]-1; k++)
	{
		qw.b0 = a = tfmfile.get();
		qw.b1 = b = tfmfile.get();
		qw.b2 = c = tfmfile.get();
		qw.b3 = d = tfmfile.get();
		fontinfo[k].qqqq = qw;
		if (a != 0)
		{
			if (a < bc || a > ec)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
			qw = fontinfo[charbase[f]+a].qqqq;
			if (qw.b0 <= 0)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
		}
		if (b != 0)
		{
			if (b < bc || b > ec)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
			qw = fontinfo[charbase[f]+b].qqqq;
			if (qw.b0 <= 0)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
		}
		if (c != 0)
		{
			if (c < bc || c > ec)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
			qw = fontinfo[charbase[f]+c].qqqq;
			if (qw.b0 <= 0)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
		}
		if (d < bc || d > ec)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
		qw = fontinfo[charbase[f]+d].qqqq;
		if (qw.b0 <= 0)
			{
				notLoadable(u, nom, aire, s, fileopened);
				return 0;
			}
	}
	for (int k = 1; k <= np; k++)
		if (k == 1)
		{
			scaled sw = tfmfile.get();
			if (sw > 127)
				sw -= 0x1'00;
			sw = sw*0x1'00+tfmfile.get();
			sw = sw*0x1'00+tfmfile.get();
			fontinfo[parambase[f]].int_ = sw*16+tfmfile.get()/16;
		}
		else
		{
			a = tfmfile.get();
			b = tfmfile.get();
			c = tfmfile.get();
			d = tfmfile.get();
			scaled sw = ((((d*z)/0x1'00+c*z)/0x1'00)+b*z)/beta;
			if (a == 0)
				fontinfo[parambase[f]+k-1].int_ = sw;
			else 
				if (a == 255)
					fontinfo[parambase[f]+k-1].int_ = sw-alpha;
				else
				{
					notLoadable(u, nom, aire, s, fileopened);
					return 0;
				}
		}
	if (tfmfile.eof())
	{
		notLoadable(u, nom, aire, s, fileopened);
		return 0;
	}
	for (int k = np+1; k <= 7; k++)
		fontinfo[parambase[f]+k-1].int_ = 0;
	if (np >= 7)
		fontparams[f] = np;
	else
		fontparams[f] = 7;
	hyphenchar[f] = int_par(default_hyphen_char_code);
	skewchar[f] = int_par(default_skew_char_code);
	if (bchlabel < nl)
		bcharlabel[f] = bchlabel+ligkernbase[f];
	else
		bcharlabel[f] = 0;
	fontbchar[f] = bchar;
	fontfalsebchar[f] = bchar;
	if (bchar <= ec && bchar >= bc)
	{
		qw = fontinfo[charbase[f]+bchar].qqqq;
		if ((qw.b0 > 0))
			fontfalsebchar[f] = 256;
	}
	fontname[f] = nom;
	fontarea[f] = aire;
	fontbc[f] = bc;
	fontec[f] = ec;
	fontglue[f] = 0;
	parambase[f]--;
	fmemptr += lf;
	fontptr = f;
	if (fileopened)
		bclose(tfmfile);
	return f;
}
