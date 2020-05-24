#include "newtrieop.h"
#include "overflow.h"

quarterword newtrieop(smallnumber d, smallnumber  n, quarterword v)
{
	int h = abs(n+313*d+361*v+1009*curlang)%(2*trieopsize)-trieopsize;
	while (true)
	{
		int l = trieophash[h];
		if (l == 0)
		{
			if (trieopptr == trieopsize)
				overflow("pattern memory ops", trieopsize);
			quarterword u = trieused[curlang];
			if (u == 255)
				overflow("pattern memory ops per language", 255);
			trieopptr++;
			u++;
			trieused[curlang] = u;
			hyfdistance[trieopptr] = d;
			hyfnum[trieopptr] = n;
			hyfnext[trieopptr] = v;
			trieoplang[trieopptr] = curlang;
			trieophash[h] = trieopptr;
			trieopval[trieopptr] = u;
			return u;
		}
		if (hyfdistance[l] == d && hyfnum[l] == n && hyfnext[l] == v && trieoplang[l] == curlang)
			return trieopval[l];
		if (h > -trieopsize)
			h--;
		else
			h = trieopsize;
	}
}
