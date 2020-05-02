#include "loadfmtfile.h"
#include <iostream>

void readInt(twohalves &num)
{
	fmtfile.read(reinterpret_cast<char *>(&num), 4);
}

void readInt(memoryword &num)
{
	fmtfile.read(reinterpret_cast<char *>(&num), 4);
}

void readInt(fourquarters &num)
{
	fmtfile.read(reinterpret_cast<char *>(&num), 4);
}

void readInt(int &num)
{
	fmtfile.read(reinterpret_cast<char *>(&num), 4);
}

bool loadfmtfile(void)
{
	int j, k;
	halfword p, q;
	int x;
	fourquarters w;
	readInt(x);
	if (x != 117275187)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;	
	}
	readInt(x);
	if (x != 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	readInt(x);
	if (x != mem_top)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	readInt(x);	
	if (x != 6106)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	readInt(x);	
	if (x != hash_prime)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	readInt(x);	
	if (x != 307)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	readInt(x);	
	if (x < 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > poolsize)
	{
		std::cout << "---! Must increase the \nstring pool size\n";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		poolptr = x;
	readInt(x);	
	if (x < 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > maxstrings)
	{
		std::cout << "---! Must increase the \nmax strings\n";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		strptr = x;
	for (k = 0; k <= strptr; k++)
	{
		readInt(x);	
		if (x < 0 || x > poolptr)
		{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
		else
			strstart[k] = x;
	}
	for (k = 0; k+4 < poolptr; k = k+4)
	{
		readInt(w);
		strpool[k] = w.b0;
		strpool[k+1] = w.b1;
		strpool[k+2] = w.b2;
		strpool[k+3] = w.b3;
	}
	k = poolptr-4;
	readInt(w);
	strpool[k] = w.b0;
	strpool[k+1] = w.b1;
	strpool[k+2] = w.b2;
	strpool[k+3] = w.b3;
	initstrptr = strptr;
	initpoolptr = poolptr;
	readInt(x);	
	if (x < 1019 || x >= hi_mem_stat_min)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		lomemmax = x;
	readInt(x);	
	if (x < 20 || x > lomemmax)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		rover = x;
	p = 0;
	q = rover;
	do
	{
		for (k = p; k <= q+1; k++)
			readInt(mem[k]);
		p = q+info(q);
		if (p > lomemmax || (q >= link(q+1) && link(q+1) != rover))
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		q = link(q+1);
	} while (q != rover);
	for (k = p; k <= lomemmax; k++)
		readInt(mem[k]);
	if (memmin < -2)
	{
		p = info(rover+1);
		q = memmin+1;
		link(memmin) = 0;
		info(memmin) = 0;
		link(p+1) = q;
		info(rover+1) = q;
		link(q+1) = rover;
		info(q+1) = p;
		link(q) = 0xFF'FF;
		info(q) = -q;
	}
	readInt(x);	
	if (x < lomemmax+1 || x > hi_mem_stat_min)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		himemmin = x;
	readInt(x);	
	if (x < 0 || x > mem_top)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		avail = x;
	memend = mem_top;
	for (k = himemmin; k <= memend; k++)
		readInt(mem[k]);
	readInt(varused);
	readInt(dynused);
	k = 1;
	do
	{
		readInt(x);	
		if (x < 1 || k+x > 6107)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		for (j = k; j < k+x; j++)
			readInt(eqtb[j]);
		k += x;
		readInt(x);	
		if (x < 0 || k+x > 6107)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		for (j = k; j < k+x; j++)
			eqtb[j] = eqtb[k-1];
		k += x;
	}
	while (k <= 6106);
	readInt(x);	
	if (x < 514 || x > 2614)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		parloc = x;
	partoken = 4095+parloc;
	readInt(x);	
	if (x < 514 || x > 2614)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		writeloc = x;
	readInt(x);	
	if (x < 514 || x > 2614)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		hashused = x;
	p = 513;
	do
	{
		readInt(x);	
		if (x < p+1 || x > hashused)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			p = x;
		readInt(hash[p]);
	} while (p != hashused);
	for (p = hashused+1; p <= 2880; p++)
		readInt(hash[p]);
	readInt(cscount);
	readInt(x);
	if (x < 7)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > fontmemsize)
	{
		std::cout << "---! Must increase the \nfont mem size\n";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		fmemptr = x;
	for (k = 0; k < fmemptr; k++)
		readInt(fontinfo[k]);
	readInt(x);	
	if (x < 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > fontmax)
	{
		std::cout << "---! Must increase the \nfont max\n";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		fontptr = x;
	for (k = 0; k <= fontptr; k++)
	{
		readInt(fontcheck[k]);
		readInt(fontsize[k]);
		readInt(fontdsize[k]);
		readInt(x);	
		if (x < 0 || x > 0xFF'FF)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontparams[k] = x;
		readInt(hyphenchar[k]);
		readInt(skewchar[k]);
		readInt(x);	
		if (x < 0 || x > strptr)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontname[k] = x;
		readInt(x);	
		if (x < 0 || x > strptr)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontarea[k] = x;
		readInt(x);	
		if (x < 0 || x > 255)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontbc[k] = x;
		readInt(x);	
		if (x < 0 || x > 255)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontec[k] = x;
		readInt(charbase[k]);
		readInt(widthbase[k]);
		readInt(heightbase[k]);
		readInt(depthbase[k]);
		readInt(italicbase[k]);
		readInt(ligkernbase[k]);
		readInt(kernbase[k]);
		readInt(extenbase[k]);
		readInt(parambase[k]);
		readInt(x);	
		if (x < 0 || x > lomemmax)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontglue[k] = x;
		readInt(x);	
		if (x < 0 || x > fmemptr-1)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			bcharlabel[k] = x;
		readInt(x);	
		if (x < 0 || x > 256)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontbchar[k] = x;
		readInt(x);	
		if (x < 0 || x > 256)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			fontfalsebchar[k] = x;
	}
	{
	readInt(x);
	if (x < 0 || x > 307)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		hyphcount = x;
	}
	for (k = 1; k <= hyphcount; k++)
	{
		readInt(x);
		if (x < 0 || x > 307)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			j = x;
		readInt(x);
		if (x < 0 || x > strptr)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			hyphword[j] = x;
		readInt(x);
		if (x < 0 || x > 0xFF'FF)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			hyphlist[j] = x;
	}
	readInt(x);
	if (x < 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > triesize)
	{
		std::cout << "---! Must increase the \ntrie size\n";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		j = x;
	triemax = j;
	for (k = 0; k <= j; k++)
		readInt(trie[k]);
	readInt(x);
	if (x < 0)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	if (x > trieopsize)
	{
		std::cout << "---! Must increase the \ntrie op size";
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		j = x;
	trieopptr = j;
	for (k = 1; k <= j; k++)
	{
		readInt(x);
		if (x < 0 || x > 63)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			hyfdistance[k] = x;
		readInt(x);
		if (x < 0 || x > 63)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			hyfnum[k] = x;
		readInt(x);
		if (x < 0 || x > 255)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			hyfnext[k] = x;
	}
	for (k = 0; k <= 255; k++)
		trieused[k] = 0;
	k = 256;
	while (j > 0)
	{
		readInt(x);
		if (x < 0 || x > k-1)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		else
			k = x;
		readInt(x);
		if (x < 1 || x > j)
		{
			std::cout << "(Fatal format file error; I''m stymied\n";
			return false;
		}
		trieused[k] = x;
		j -= x;
		opstart[k] = j;
	}
	trienotready = false;
	readInt(x);
	if (x < 0 || x > 3)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		interaction = x;
	readInt(x);
	if (x < 0 || x > strptr)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	else
		formatident = x;
	readInt(x);
	if (x != 69069 || fmtfile.eof())
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		return false;
	}
	return true;
}
