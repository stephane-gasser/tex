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
#include "texte.h"

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
		printnl("! ");
		print("You can't dump inside a group");
		helpptr = 1;
		helpline[0] = txt("`{...\\dump}' is a no-no.");
		if (interaction == error_stop_mode)
			interaction = scroll_mode;
		if (logopened)
			error();
		history = fatal_error_stop;
		jumpout();
	}
	selector = new_string;
	print(" (preloaded format=");
	print(TXT(jobname));
	printchar(' ');
	printint(int_par(year_code));
	printchar('.');
	printint(int_par(month_code));
	printchar('.');
	printint(int_par(day_code));
	printchar(')');
	if (interaction == batch_mode)
		selector = log_only;
	else
		selector = term_and_log;
	if (poolptr+1 > poolsize)
		overflow("pool size", poolsize-initpoolptr);
	formatident = makestring();
	packjobname(".fmt");
	while (!wopenout(fmtfile))
		promptfilename("format file name", ".fmt"); 
	printnl("Beginning to dump on file ");
	slowprint(wmakenamestring(fmtfile));
	strptr--;
	poolptr = strstart[strptr];
	printnl("");
	slowprint(formatident);
	writeInt(117275187);
	writeInt(0);
	writeInt(mem_top);
	writeInt(6106);
	writeInt(hash_prime);
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
	print(" strings of total length ");
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
	print(" memory locations dumped; current usage is ");
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
	for (p = hash_base; p <= hashused; p++)
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
	print(" multiletter control sequences");
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
		printnl("\\font");
		printesc(TXT(text(font_id_base+k)));
		printesc("FONT");
		printchar('=');
		printfilename(fontname[k], fontarea[k], txt(""));
		if (fontsize[k] != fontdsize[k])
		{
			print(" at ");
			printscaled(fontsize[k]);
			print("pt");
		}
	}
	println();
	printint(fmemptr-7);
	print(" words of font info for ");
	printint(fontptr-0);
	print(" preloaded font");
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
	print(" hyphenation exception");
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
	printnl("Hyphenation trie of length ");
	printint(triemax);
	print(" has ");
	printint(trieopptr);
	print(" op");
	if (trieopptr != 1)
		printchar('s');
	print(" out of ");
	printint(trieopsize);
	for (k = 255; k > -1; k--)
		if (trieused[k] > 0)
		{
			printnl("    ");
			printint(trieused[k]);
			print(" for language ");
			printint(k);
			writeInt(k);
			writeInt(trieused[k]);
		}
	writeInt(interaction);
	writeInt(formatident);
	writeInt(69069);
	int_par(tracing_stats_code) = 0;
	wclose(fmtfile);
}
