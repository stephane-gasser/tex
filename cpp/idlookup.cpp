#include "idlookup.h"
#include "streqbuf.h"
#include "overflow.h"
#include "makestring.h"

halfword idlookup(int j, int l)
{
	int h = buffer[j];
	for (halfword k = j+1; k < j+l; k++)
	{
		h = 2*h+buffer[k];
		while (h >= hash_prime)
			h -= hash_prime;
	}
	halfword p = h+hash_base;
	while (true)
	{
		if (text(p) > 0)
			if (length(text(p)) == l)
				if (streqbuf(text(p), j))
					return p;
		if (next(p) == 0)
		{
			if (nonewcontrolsequence)
				p = undefined_control_sequence;
			else
			{
				if (text(p) > 0)
				{
					do
					{
						if (hash_is_full())
							overflow("hash size", hash_size);
						hashused--;
					} while (text(hashused));
					next(p) = hashused;
					p = hashused;
				}
				if (poolptr+l > poolsize)
					overflow("pool size", poolsize-initpoolptr);
				int d = (poolptr-strstart[strptr]);
				while (poolptr > strstart[strptr])
				{
					poolptr--;
					strpool[poolptr+l] = strpool[poolptr];
				}
				for (halfword k = j; k <j+l; k++)
					strpool[poolptr++] = buffer[k];
				text(p) = makestring();
				poolptr += d;
			}
			return p;
		}
		p = next(p);
	}
}
