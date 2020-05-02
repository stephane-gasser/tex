#include "idlookup.h"
#include "streqbuf.h"
#include "overflow.h"
#include "makestring.h"

halfword idlookup(int j, int l)
{
	int h = buffer[j];
	for (halfword k = j+1; k <j+l; k++)
	{
		h = 2*h+buffer[k];
		while (h >= hash_prime)
			h -= hash_prime;
	}
	halfword p = h+hash_base;
	while (true)
	{
		if (hash[p].rh > 0)
			if (strstart[hash[p].rh+1]-strstart[hash[p].rh] == l)
				if (streqbuf(hash[p].rh, j))
					return p;
		if (hash[p].lh == 0)
		{
			if (nonewcontrolsequence)
				p = undefined_control_sequence;
			else
			{
				if (hash[p].rh > 0)
				{
					do
					{
						if (hashused == hash_base)
							overflow(503, 2100); //hash size
						hashused--;
					} while (hash[hashused].rh);
					hash[p].lh = hashused;
					p = hashused;
				}
				if (poolptr+l > poolsize)
					overflow(257, poolsize-initpoolptr); //pool size
				int d = (poolptr-strstart[strptr]);
				while (poolptr > strstart[strptr])
				{
					poolptr--;
					strpool[poolptr+l] = strpool[poolptr];
				}
				for (halfword k = j; k <j+l; k++)
					strpool[poolptr++] = buffer[k];
				hash[p].rh = makestring();
				poolptr += d;
			}
			return p;
		}
		p = hash[p].lh;
	}
}
