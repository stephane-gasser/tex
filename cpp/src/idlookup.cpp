#include "idlookup.h"
#include "equivalent.h"
#include "erreur.h"

//! test if all positions are occupied
static bool hash_is_full(void) { return hashused == hash_base; }

//! link for coalesced lists
static halfword& next(halfword p) { return hash[p].lh; }

halfword idlookup(const std::string &s)
{
	int h = 0;
	for (unsigned char c: s)
		h = (2*h+c)%hash_prime;
	halfword p = h+hash_base;
	while (true)
	{
		if (text(p) > 0)
			if (strings[text(p)] == s)
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
				strings.push_back(s);
				text(p) = strings.size()-1;
			}
			return p;
		}
		p = next(p);
	}
}
