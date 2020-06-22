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

void dump_hh(twohalves num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void dump_wd(memoryword num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void dump_qqqq(fourquarters num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void dump_int(std::uint32_t num)
{
	fmtfile.write(reinterpret_cast<const char *>(&num), 4);
}

void dump_four_ASCII(int k)
{
	fourquarters w;
	w.b0 = strpool[k];
	w.b1 = strpool[k+1];
	w.b2 = strpool[k+2];
	w.b3 = strpool[k+3];
	dump_qqqq(w);
}

void storefmtfile(void)
{
	int j, k, l;
	halfword p, q;
	if (saveptr)
	{ 
		printnl("! ");
		print("You can't dump_int inside a group");
		helpptr = 1;
		helpline[0] = "`{...\\dump_int}' is a no-no.";
		if (interaction == error_stop_mode)
			interaction = scroll_mode;
		if (logopened)
			error();
		history = fatal_error_stop;
		jumpout();
	}
	selector = new_string;
	print(" (preloaded format=");
	print(jobname);
	printchar(' ');
	printint(year());
	printchar('.');
	printint(month());
	printchar('.');
	printint(day());
	printchar(')');
	if (interaction == batch_mode)
		selector = log_only;
	else
		selector = term_and_log;
	str_room(1);
	formatident = makestring();
	packjobname(format_extension);
	while (!wopenout(fmtfile))
		promptfilename("format file name", format_extension); 
	printnl("Beginning to dump_int on file ");
	slowprint(wmakenamestring(fmtfile));
	flush_string();
	printnl("");
	slowprint(formatident);
	dump_int(CHECKSUM);
	dump_int(mem_bot);
	dump_int(mem_top);
	dump_int(eqtb_size);
	dump_int(hash_prime);
	dump_int(hyph_size);
	dump_int(poolptr);
	dump_int(strptr);
	for (k = 0; k <= strptr; k++)
		dump_int(strstart[k]);
	for (k = 0; k+4 < poolptr; k += 4)
		dump_four_ASCII(k);
	k = poolptr-4;
	dump_four_ASCII(k);
	println();
	printint(strptr);
	print(" strings of total length ");
	printint(poolptr);
	sortavail();
	varused = 0;
	dump_int(lomemmax);
	dump_int(rover);
	p = 0;
	q = rover;
	int x = 0;
	do
	{
		for (k = p; k <= q+1; k++)
			dump_wd(mem[k]);
		x += q+2-p;
		varused += q-p;
		p = q+node_size(q);
		q = rlink(q);
	} while (q != rover);
	varused += lomemmax-p;
	dynused = memend+1-himemmin;
	for (k = p; k <= lomemmax; k++)
		dump_wd(mem[k]);
	x += lomemmax+1-p;
	dump_int(himemmin);
	dump_int(avail);
	for (k = himemmin; k <= memend; k++)
		dump_wd(mem[k]);
	x += memend+1-himemmin;
	p = avail;
	while (p)
	{
		dynused--;
		p = link(p);
	}
	dump_int(varused);
	dump_int(dynused);
	println();
	printint(x);
	print(" memory locations dump_inted; current usage is ");
	printint(varused);
	printchar('&');
	printint(dynused);
	k = active_base;
	do
	{
		bool found1 = false;
		for (j = k; j < int_base-1; j++)
			if (equiv(j) == equiv(j+1) && eq_type(j) == eq_type(j+1) && eq_level(j) == eq_level(j+1))
			{
				found1 = true;
				break;
			}
		if (found1)
		{
			j++;
			l = j;
			for (;j < int_base-1; j++)
				if (equiv(j) != equiv(j+1) || eq_type(j) != eq_type(j+1) || eq_level(j) != eq_level(j+1))
					break;
		}
		else
			l = int_base;
		dump_int(l-k);
		for (;k < l; k++)
			dump_wd(eqtb[k]);
		k = j+1;
		dump_int(k-l);
	} while (k != int_base);
	do
	{
		bool found2 = false;
		for (j = k; j < eqtb_size; j++)
			if (eqtb[j].int_ == eqtb[j+1].int_)
			{
				found2 = true;
				break;
			}
		if (found2)
		{
			j++;
			l = j;
			for (;j < eqtb_size; j++)
				if (eqtb[j].int_ != eqtb[j+1].int_)
					break;
		}
		else
			l = eqtb_size+1;
		dump_int(l-k);
		for (;k < l; k++)
			dump_wd(eqtb[k]);
		k = j+1;
		dump_int(k-l);
	} while (k <= eqtb_size);
	dump_int(parloc);
	dump_int(writeloc);
	dump_int(hashused);
	cscount = frozen_control_sequence-1-hashused;
	for (p = hash_base; p <= hashused; p++)
		if (hash[p].rh)
		{
			dump_int(p);
			dump_hh(hash[p]);
			cscount++;
		}
	for (p = hashused+1; p < undefined_control_sequence; p++)
		dump_hh(hash[p]);
	dump_int(cscount);
	println();
	printint(cscount);
	print(" multiletter control sequences");
	dump_int(fmemptr);
	for (k = 0; k <fmemptr; k++)
		dump_wd(fontinfo[k]);
	dump_int(fontptr);
	for (k = null_font; k <= fontptr; k++)
	{
		dump_qqqq(fontcheck[k]);
		dump_int(fontsize[k]);
		dump_int(fontdsize[k]);
		dump_int(fontparams[k]);
		dump_int(hyphenchar[k]);
		dump_int(skewchar[k]);
		dump_int(txt(fontname[k]));
		dump_int(txt(fontarea[k]));
		dump_int(fontbc[k]);
		dump_int(fontec[k]);
		dump_int(charbase[k]);
		dump_int(widthbase[k]);
		dump_int(heightbase[k]);
		dump_int(depthbase[k]);
		dump_int(italicbase[k]);
		dump_int(ligkernbase[k]);
		dump_int(kernbase[k]);
		dump_int(extenbase[k]);
		dump_int(parambase[k]);
		dump_int(fontglue[k]);
		dump_int(bcharlabel[k]);
		dump_int(fontbchar[k]);
		dump_int(fontfalsebchar[k]);
		printnl("\\font");
		printesc(TXT(text(font_id_base+k)));
		printesc("FONT");
		printchar('=');
		printfilename(fontname[k], fontarea[k], "");
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
	dump_int(hyphcount);
	for (k = 0; k <= hyph_size; k++)
		if (hyphword[k] != "")
		{
			dump_int(k);
			dump_int(txt(hyphword[k]));
			dump_int(hyphlist[k]);
		}
	println();
	printint(hyphcount);
	print(" hyphenation exception");
	if (hyphcount != 1)
		printchar('s');
	if (trienotready)
		inittrie();
	dump_int(triemax);
	for (k = 0; k <= triemax; k++)
		dump_hh(trie[k]);
	dump_int(trieopptr);
	for (k = 1; k<= trieopptr; k++)
	{
		dump_int(hyfdistance[k]);
		dump_int(hyfnum[k]);
		dump_int(hyfnext[k]);
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
			dump_int(k);
			dump_int(trieused[k]);
		}
	dump_int(interaction);
	dump_int(txt(formatident));
	dump_int(69069);
	tracing_stats() = 0;
	wclose(fmtfile);
}
