#include "loadfmtfile.h"
#include "cesure.h"
#include "police.h"
#include "equivalent.h"
#include "idlookup.h"
#include "fichier.h"
#include <iostream>

static halfword& link(halfword p) { return mem[p].hh.rh; }
static halfword& info(halfword p) { return mem[p].hh.lh; }
static halfword& rlink(halfword p) { return link(p+1); }
static halfword& llink(halfword p) { return info(p+1); }
static halfword& node_size(halfword p) { return mem[p].hh.lh; }

static wordfile fmtfile;

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
