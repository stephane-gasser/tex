#include "storefmtfile.h"
#include "impression.h" 
#include "erreur.h"
#include "jumpout.h"
#include "equivalent.h"
#include "makestring.h"
#include "cesure.h"
#include "police.h"
#include "fichier.h"
#include "texte.h"
#include "idlookup.h"

static halfword& link(halfword p) { return mem[p].hh.rh; }
static halfword& info(halfword p) { return mem[p].hh.lh; }
static halfword& rlink(halfword p) { return link(p+1); }
static halfword& llink(halfword p) { return info(p+1); }
static halfword& node_size(halfword p) { return mem[p].hh.lh; }

static halfword getnode(void)
{
	halfword p = rover;
	do
	{ 
		halfword q;
		for (q = p+node_size(p); link(q) == empty_flag; q += node_size(q))
		{
			auto t = rlink(q);
			if (q == rover)
				rover = t;
			llink(t) = llink(q);
			rlink(llink(q)) = t;
		}
		node_size(p) = q-p;
		p = rlink(p);
	} while (p != rover);
	return empty_flag;
}

//! sorts the available variable-size nodes by location
static void sortavail(void)
{
	auto p = getnode();
	p = rlink(rover);
	rlink(rover) = empty_flag;
	halfword oldrover = rover;
	while (p != oldrover)
		if (p < rover)
		{
			auto q = p;
			p = rlink(q);
			rlink(q) = rover;
			rover = q;
		}
		else
		{
			halfword q = rover;
			while (rlink(q) < p)
				q = rlink(q);
			auto r = rlink(p);
			rlink(p) = rlink(q);
			rlink(q) = p;
			p = r;
		}
	p = rover;
	while (rlink(p) != empty_flag)
	{
		llink(rlink(p)) = p;
		p = rlink(p);
	}
	rlink(p) = rover;
	llink(rover) = p;
}

constexpr char format_extension[] = ".fmt"; //!< the extension, as a WEB constant

static wordfile fmtfile;

static void dump_hh(twohalves num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(memoryword num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(MemoryNode num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_qqqq(fourquarters num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_int(std::uint32_t num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }

static std::string pool;

static void dump_four_ASCII(int k)
{
	fourquarters w;
	w.b0 = pool[k];
	w.b1 = pool[k+1];
	w.b2 = pool[k+2];
	w.b3 = pool[k+3];
	dump_qqqq(w);
}

void storefmtfile(void)
{
	int j, k, l;
	halfword p, q;
	if (savestack.size())
		fatal("You can't dump_int inside a group", "`{...\\dump_int}' is a no-no.");
	formatident = " (preloaded format="+jobname+" "+std::to_string(year())+"."+std::to_string(month())+"."+std::to_string(day())+")";
	selector = interaction == batch_mode ? log_only : term_and_log;
	std::string fname;
	while (!wopenout(fmtfile, fname = packjobname(format_extension)))
		promptfilename("format file name", format_extension); 
	printnl("Beginning to dump_int on file ");
	slowprint(fname);
	printnl(formatident);
	dump_int(CHECKSUM);
	dump_int(mem_bot);
	dump_int(mem_top);
	dump_int(eqtb_size);
	dump_int(hash_prime);
	dump_int(hyph_size);
	int poolptr = 0;
	std::vector<int> strstart;
	for (auto s: strings)
	{
		strstart.push_back(poolptr);
		for (auto c: s)
		{
			pool += c;
			poolptr++;
		}
	}
	strstart.push_back(poolptr);
	dump_int(poolptr);
	dump_int(strings.size());
	for (k = 0; k <= strings.size(); k++)
		dump_int(strstart[k]);
	for (k = 0; k+4 < poolptr; k += 4)
		dump_four_ASCII(k);
	k = poolptr-4;
	dump_four_ASCII(k);
	print("\n"+std::to_string(strings.size())+" strings of total length "+std::to_string(poolptr));
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
	print("\n"+std::to_string(x)+" memory locations dump_inted; current usage is "+std::to_string(varused)+"&"+std::to_string(dynused));
	k = active_base;
	do
	{
		bool found1 = false;
		for (j = k; j < int_base-1; j++)
			if (eqtb[j] == eqtb[j+1])
			{
				found1 = true;
				break;
			}
		if (found1)
		{
			j++;
			l = j;
			for (;j < int_base-1; j++)
				if (eqtb[j] != eqtb[j+1])
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
	print(std::to_string(cscount)+" multiletter control sequences");
	dump_int(Font::info.size()-1);
	for (auto &fi: Font::info)
		dump_wd(fi);
	dump_int(fonts.size()-1);
	for (auto &ft: fonts)
	{
		dump_qqqq(ft.check);
		dump_int(ft.size);
		dump_int(ft.dsize);
		dump_int(ft.params);
		dump_int(ft.hyphenchar);
		dump_int(ft.skewchar);
		dump_int(txt(ft.name));
		dump_int(txt(ft.area));
		dump_int(ft.bc);
		dump_int(ft.ec);
		dump_int(ft.charbase);
		dump_int(ft.widthbase);
		dump_int(ft.heightbase);
		dump_int(ft.depthbase);
		dump_int(ft.italicbase);
		dump_int(ft.ligkernbase);
		dump_int(ft.kernbase);
		dump_int(ft.extenbase);
		dump_int(ft.parambase);
		dump_int(ft.glue->num);
		dump_int(ft.bcharlabel);
		dump_int(ft.bchar);
		dump_int(ft.falsebchar);
		printnl("\\font");
		print(esc(eqtb_cs[k+font_id_base-hash_base].text)+esc("FONT")+"="+asFilename(ft.name, ft.area, ""));
		if (ft.size != ft.dsize)
			print(" at "+asScaled(ft.size)+"pt");
	}
	println();
	print(std::to_string(Font::info.size()-7)+" words of font info for "+std::to_string(fonts.size()+1)+" preloaded font"+(fonts.size()+1 == 1 ? "" : "s"));
	dump_int(hyphcount);
	for (k = 0; k <= hyph_size; k++)
		if (hyphword[k] != "")
		{
			dump_int(k);
			dump_int(txt(hyphword[k]));
			dump_int(hyphlist[k]->num);
		}
	println();
	print(std::to_string(hyphcount)+" hyphenation exception"+(hyphcount == 1 ? "" : "s"));
	if (trienotready)
		inittrie();
	dump_int(trie.size()-1);
	for (auto t: trie)
		dump_hh(t.hh);
	dump_int(trieOp.size()-1);
	for (k = 1; k < trieOp.size(); k++)
	{
		dump_int(trieOp[k].hyfdistance);
		dump_int(trieOp[k].hyfnum);
		dump_int(trieOp[k].hyfnext);
	}
	printnl("Hyphenation trie of length "+std::to_string(trie.size()-1)+" has "+std::to_string(trieOp.size()-1)+" op"+(trieOp.size()-1 == 1 ? "" : "s")+" out of "+std::to_string(trieopsize));
	for (k = 255; k > -1; k--)
		if (trieused[k] > 0)
		{
			printnl("    "+std::to_string(trieused[k])+" for language "+std::to_string(k));
			dump_int(k);
			dump_int(trieused[k]);
		}
	dump_int(interaction);
	dump_int(txt(formatident));
	dump_int(69069);
	tracing_stats() = 0;
	wclose(fmtfile);
}
