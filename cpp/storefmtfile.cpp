#include "storefmtfile.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "jumpout.h"
#include "printchar.h"
#include "printint.h"
#include "overflow.h"
#include "makestring.h"
#include "packjobname.h"
#include "wopenout.h"
#include "promptfilename.h"
#include "wmakenamestring.h"
#include "slowprint.h"
#include "println.h"
#include "sortavail.h"
#include "printesc.h"
#include "printfilename.h"
#include "printscaled.h"
#include "inittrie.h"
#include "wclose.h"

void writeInt(twohalves num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void writeInt(memoryword num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void writeInt(fourquarters num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void writeInt(std::uint32_t num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void storefmtfile(void)
{
	int j, k, l;
	halfword p, q;
	int x;
	fourquarters w;
	if (saveptr)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1257); //You can't dump inside a group
		helpptr = 1;
		helpline[0] = 1258; //`{...\dump}' is a no-no.
		if (interaction == 3)
			interaction = 2;
		if (logopened)
			error();
		history = 3;
		jumpout();
	}
	selector = 21;
	print(1271); // (preloaded format=
	print(jobname);
	printchar(' ');
	printint(eqtb[5286].int_);
	printchar('.');
	printint(eqtb[5285].int_);
	printchar('.');
	printint(eqtb[5284].int_);
	printchar(')');
	if (interaction == 0)
		selector = 18;
	else
		selector = 19;
	if (poolptr+1 > poolsize)
		overflow(257, poolsize-initpoolptr); //pool size
	formatident = makestring();
	packjobname(785); //.fmt
	while (!wopenout(fmtfile))
		promptfilename(1272, 785); //format file name//.fmt
	printnl(1273); //Beginning to dump on file 
	slowprint(wmakenamestring(fmtfile));
	strptr--;
	poolptr = strstart[strptr];
	printnl(338); //
	slowprint(formatident);
	writeInt(117275187);
	writeInt(0);
	writeInt(30000);
	writeInt(6106);
	writeInt(1777);
	writeInt(307);
	writeInt(poolptr);
	writeInt(strptr);
	for (k = 0; k <= strptr; k++)
		writeInt(strstart[k]);
	for (k = 0; k+4 < poolptr; k += 4)
	{
		w.b0 = strpool[k];
		w.b1 = strpool[k+1];
		w.b2 = strpool[k+2];
		w.b3 = strpool[k+3];
		writeInt(w);
	}
	k = poolptr-4;
	w.b0 = strpool[k];
	w.b1 = strpool[k+1];
	w.b2 = strpool[k+2];
	w.b3 = strpool[k+3];
	writeInt(w);
	println();
	printint(strptr);
	print(1259); // strings of total length 
	printint(poolptr);
	sortavail();
	varused = 0;
	writeInt(lomemmax);
	writeInt(rover);
	p = 0;
	q = rover;
	x = 0;
	do
	{
		for (k = p; k <= q+1; k++)
			writeInt(mem[k]);
		x += q+2-p;
		varused = varused+q-p;
		p = q+info(q);
		q = link(q+1);
	} while (q != rover);
	varused += lomemmax-p;
	dynused = memend+1-himemmin;
	for (k = p; k <= lomemmax; k++)
		writeInt(mem[k]);
	x += lomemmax+1-p;
	writeInt(himemmin);
	writeInt(avail);
	for (k = himemmin; k <= memend; k++)
		writeInt(mem[k]);
	x += memend+1-himemmin;
	p = avail;
	while (p)
	{
		dynused--;
		p = link(p);
	}
	writeInt(varused);
	writeInt(dynused);
	println();
	printint(x);
	print(1260); // memory locations dumped; current usage is 
	printint(varused);
	printchar('&');
	printint(dynused);
	k = 1;
	do
	{
		bool label41 = false;
		for (j = k; j < 5262; j++)
			if (equiv(j) == equiv(j+1) && eq_type(j) == eq_type(j+1) && eq_level(j) == eq_level(j+1))
			{
				label41 = true;
				break;
			}
		if (label41)
		{
			j++;
			l = j;
			for (;j < 5262; j++)
				if (equiv(j) != equiv(j+1) || eq_type(j) != eq_type(j+1) || eq_level(j) != eq_level(j+1))
					break;
		}
		else
			l = 5263;
		writeInt(l-k);
		for (;k < l; k++)
			writeInt(eqtb[k]);
		k = j+1;
		writeInt(k-l);
	} while (k != 5263);
	do
	{
		bool label42 = false;
		for (j = k; j < 6106; j++)
			if (eqtb[j].int_ == eqtb[j+1].int_)
			{
				label42 = true;
				break;
			}
		if (label42)
		{
			j++;
			l = j;
			for (;j < 6106; j++)
				if (eqtb[j].int_ != eqtb[j+1].int_)
					break;
		}
		else
			l = 6107;
		writeInt(l-k);
		for (;k < l; k++)
			writeInt(eqtb[k]);
		k = j+1;
		writeInt(k-l);
	} while (k <= 6106);
	writeInt(parloc);
	writeInt(writeloc);
	writeInt(hashused);
	cscount = 2613-hashused;
	for (p = 514; p <= hashused; p++)
		if (hash[p].rh)
		{
			writeInt(p);
			writeInt(hash[p]);
			cscount++;
		}
	for (p = hashused+1; p <= 2880; p++)
		writeInt(hash[p]);
	writeInt(cscount);
	println();
	printint(cscount);
	print(1261); // multiletter control sequences
	writeInt(fmemptr);
	for (k = 0; k <fmemptr; k++)
		writeInt(fontinfo[k]);
	writeInt(fontptr);
	for (k = 0; k <= fontptr; k++)
	{
		writeInt(fontcheck[k]);
		writeInt(fontsize[k]);
		writeInt(fontdsize[k]);
		writeInt(fontparams[k]);
		writeInt(hyphenchar[k]);
		writeInt(skewchar[k]);
		writeInt(fontname[k]);
		writeInt(fontarea[k]);
		writeInt(fontbc[k]);
		writeInt(fontec[k]);
		writeInt(charbase[k]);
		writeInt(widthbase[k]);
		writeInt(heightbase[k]);
		writeInt(depthbase[k]);
		writeInt(italicbase[k]);
		writeInt(ligkernbase[k]);
		writeInt(kernbase[k]);
		writeInt(extenbase[k]);
		writeInt(parambase[k]);
		writeInt(fontglue[k]);
		writeInt(bcharlabel[k]);
		writeInt(fontbchar[k]);
		writeInt(fontfalsebchar[k]);
		printnl(1264); //\font
		printesc(hash[2624+k].rh);
		printchar('=');
		printfilename(fontname[k], fontarea[k], 338); //
		if (fontsize[k] != fontdsize[k])
		{
			print(741); // at 
			printscaled(fontsize[k]);
			print(397); //pt
		}
	}
	println();
	printint(fmemptr-7);
	print(1262); // words of font info for 
	printint(fontptr-0);
	print(1263); // preloaded font
	if (fontptr != 1)
		printchar('s');
	writeInt(hyphcount);
	for (k = 0; k <= 307; k++)
		if (hyphword[k])
		{
			writeInt(k);
			writeInt(hyphword[k]);
			writeInt(hyphlist[k]);
		}
	println();
	printint(hyphcount);
	print(1265); // hyphenation exception
	if (hyphcount != 1)
		printchar('s');
	if (trienotready)
		inittrie();
	writeInt(triemax);
	for (k = 0; k <= triemax; k++)
		writeInt(trie[k]);
	writeInt(trieopptr);
	for (k = 1; k<= trieopptr; k++)
	{
		writeInt(hyfdistance[k]);
		writeInt(hyfnum[k]);
		writeInt(hyfnext[k]);
	}
	printnl(1266); //Hyphenation trie of length 
	printint(triemax);
	print(1267); // has 
	printint(trieopptr);
	print(1268); // op
	if (trieopptr != 1)
		printchar('s');
	print(1269); // out of 
	printint(trieopsize);
	for (k = 255; k > -1; k--)
		if (trieused[k] > 0)
		{
			printnl(799); //    
			printint(trieused[k]);
			print(1270); // for language 
			printint(k);
			writeInt(k);
			writeInt(trieused[k]);
		}
	writeInt(interaction);
	writeInt(formatident);
	writeInt(69069);
	eqtb[5294].int_ = 0;
	wclose(fmtfile);
}
