#include "fmtfile.h"
#include "impression.h" 
#include "erreur.h"
#include "jumpout.h"
#include "equivalent.h"
#include "chaine.h"
#include "cesure.h"
#include "police.h"
#include "fichier.h"
#include "texte.h"
#include <iostream>

static wordfile fmtfile;
static halfword himemmin = hi_mem_stat_min;
static halfword lomemmax = lo_mem_stat_max+1+1000;
static halfword memend = mem_top;
static halfword rover = lo_mem_stat_max+1;
inline memoryword mem[memmax+1];
/*	for (int k = 1; k < 20; k++) // glues
		mem[k].int_ = 0;
	for (int k = hi_mem_stat_min; k <= mem_top; k++) // au-dessus de rover
		mem[k].int_ = 0;*/

static halfword& link(halfword p) { return mem[p].hh.rh; }
static halfword& info(halfword p) { return mem[p].hh.lh; }
static halfword& node_size(halfword p) { return mem[p].hh.lh; }
static halfword& rlink(halfword p) { return link(p+1); }
static halfword& llink(halfword p) { return info(p+1); }

static void openfmtfile(void)
{
	auto j = loc;
	if (buffer[loc] == '&')
	{
		loc++;
		buffer[last] = ' ';
		for (j = loc; buffer[j] != ' '; j++); //trim à droite
		auto fname = std::string(buffer+loc, buffer+j);
		if (wopenin(fmtfile, packbufferedname(none, fname)))
		{
			loc = j;
			return;
		}
		if (wopenin(fmtfile, packbufferedname(area, fname)))
		{
			loc = j;
			return;
		}
		std::cout << "Sorry, I can't find that format;\n will try PLAIN.\n" << std::flush;
	}
	if (wopenin(fmtfile, packbufferedname(area_name, "")))
	{
		loc = j;
		return;
	}
	std::cout << "I can't find the PLAIN format file!\n";
	throw std::string();
}

void undump_hh(twohalves &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_wd(memoryword &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_wd(MemoryNode &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_qqqq(fourquarters &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_int(int &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }

void badFormatIf(bool b)
{
	if (b)
		throw 1;
}

void tooSmallIf(bool b, const std::string &s)
{
	if (b)
	{
		std::cout << "---! Must increase the \n" << s << "\n";
		throw 1;
	}
}

int undump(int min, int max)
{
	int x;
	undump_int(x);
	badFormatIf(x < min || x > max);
	return x;
}

int undump_size(int min, int max, const std::string &s)
{
	int x;
	undump_int(x);
	badFormatIf(x < min);
	tooSmallIf(x > max, s);
	return x;
}

static std::string pool;

void undump_four_ASCII(void)
{
	fourquarters w;
	undump_qqqq(w);
	pool.push_back(w.b0);
	pool.push_back(w.b1);
	pool.push_back(w.b2);
	pool.push_back(w.b3);
}

static int cscount = 0;
static int varused =lo_mem_stat_max+1-mem_bot, dynused = hi_mem_stat_usage;
static halfword avail = 0;

void loadfmtfile(void)
{
	link(rover) = empty_flag;
	node_size(rover) = 1000;
	llink(rover) = rover;
	rlink(rover) = rover;
	openfmtfile();
	try
	{
		int j, k;
		halfword p, q;
		int x;
		fourquarters w;
		undump_int(x);
		badFormatIf(x != CHECKSUM);
		undump_int(x);
		badFormatIf(x != mem_bot);
		undump_int(x);
		badFormatIf(x != mem_top);
		undump_int(x);	
		badFormatIf(x != eqtb_size);
		undump_int(x);	
		badFormatIf(x != hash_prime);
		undump_int(x);	
		badFormatIf(x != hyph_size);
		int poolptr = undump_size(0, poolsize, "string pool size");
		int strptr = undump_size(0,  maxstrings, "max strings");
		std::vector<int> strstart;
		for (k = 0; k <= strptr; k++)
			strstart.push_back(undump(0,  poolptr));
		for (k = 0; k < strptr; k++)
			strings.push_back(std::string(pool.begin()+strstart[k], pool.begin()+strstart[k+1]));
		for (k = 0; k+4 < poolptr; k = k+4)
			undump_four_ASCII();
		k = poolptr-4;
		undump_four_ASCII();
		lomemmax = undump(lo_mem_stat_max+1000, hi_mem_stat_min-1);
		rover = undump(lo_mem_stat_max+1, lomemmax);
		p = 0;
		q = rover;
		do
		{
			for (k = p; k <= q+1; k++)
				undump_wd(mem[k]);
			p = q+node_size(q);
			badFormatIf(p > lomemmax || (q >= rlink(q) && rlink(q) != rover));
			q = rlink(q);
		} while (q != rover);
		for (k = p; k <= lomemmax; k++)
			undump_wd(mem[k]);
		if (memmin < mem_bot-2)
		{
			p = llink(rover);
			q = memmin+1;
			link(memmin) = 0;
			info(memmin) = 0;
			rlink(p) = q;
			llink(rover) = q;
			rlink(q) = rover;
			llink(q) = p;
			link(q) = empty_flag;
			info(q) = mem_bot-q;
		}
		himemmin = undump(lomemmax+1, hi_mem_stat_min);
		avail = undump(0, mem_top);
		memend = mem_top;
		for (k = himemmin; k <= memend; k++)
			undump_wd(mem[k]);
		undump_int(varused);
		undump_int(dynused);
		k = active_base;
		do
		{
			auto x = undump(1, eqtb_size+1-k);
			for (j = k; j < k+x; j++)
				undump_wd(eqtb[j]);
			k += x;
			x = undump(0, eqtb_size+1-k);
			for (j = k; j < k+x; j++)
				eqtb[j] = eqtb[k-1];
			k += x;
		} while (k <= eqtb_size);
		parloc = undump(hash_base, frozen_control_sequence);
		partoken = cs_token_flag+parloc;
		writeloc = undump(hash_base, frozen_control_sequence);
		hashused = undump(hash_base, frozen_control_sequence);
		p = null_cs;
		do
		{
			p = undump(p+1, hashused);
			undump_hh(hash[p]);
		} while (p != hashused);
		for (p = hashused+1; p < undefined_control_sequence; p++)
			undump_hh(hash[p]);
		undump_int(cscount);
		Font::info.resize(undump_size(7, fontmemsize, "font mem size")+1);
		for (auto &fi: Font::info)
			undump_wd(fi);
		fonts.resize(undump_size(0, fontmax, "font max")+1);
		for (auto &ft: fonts)
		{
			undump_qqqq(ft.check);
			undump_int(ft.size);
			undump_int(ft.dsize);
			ft.params = undump(0, 1<<16-1);
			undump_int(ft.hyphenchar);
			undump_int(ft.skewchar);
			ft.name = strings[undump(0, strptr)];
			ft.area = strings[undump(0, strptr)];
			ft.bc = undump(0, 255);
			ft.ec = undump(0, 255);
			undump_int(ft.charbase);
			undump_int(ft.widthbase);
			undump_int(ft.heightbase);
			undump_int(ft.depthbase);
			undump_int(ft.italicbase);
			undump_int(ft.ligkernbase);
			undump_int(ft.kernbase);
			undump_int(ft.extenbase);
			undump_int(ft.parambase);
			ft.glue->num = undump(0, lomemmax);
			ft.bcharlabel = undump(0, Font::info.size()-1);
			ft.bchar = undump(0, non_char);
			ft.falsebchar = undump(0, non_char);
		}
		hyphcount = undump(0, hyph_size);
		for (k = 1; k <= hyphcount; k++)
		{
			j = undump(0, hyph_size);
			hyphword[j] = undump(0, strptr);
			hyphlist[j]->num = undump(0, 1<<16-1);
		}
		j = undump_size(0, triesize, "trie size");
		trie.resize(j+1);
		for (auto t: trie)
			undump_hh(t.hh);
		j = undump_size(0, trieopsize, "trie op size");
		trieOp.resize(j+1);
		for (k = 1; k < trieOp.size(); k++)
		{
			trieOp[k].hyfdistance = undump(0, 63);
			trieOp[k].hyfnum = undump(0, 63);
			trieOp[k].hyfnext = undump(0, 1<<8-1);
		}
		for (k = 0; k <= 255; k++)
			trieused[k] = 0;
		k = 256;
		while (j > 0)
		{
			k = undump(0, k-1);
			trieused[k] = undump(1, j);
			j -= trieused[k];
			opstart[k] = j;
		}
		trienotready = false;
		interaction = undump(batch_mode, error_stop_mode);
		formatident = undump(0, strptr);
		undump_int(x);
		badFormatIf(x != 69069 || fmtfile.eof());
	}
	catch(...)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		wclose(fmtfile);
		throw std::string();
	}
	wclose(fmtfile);
}
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

static void dump_hh(twohalves num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(memoryword num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(MemoryNode num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_qqqq(fourquarters num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_int(std::uint32_t num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }

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
