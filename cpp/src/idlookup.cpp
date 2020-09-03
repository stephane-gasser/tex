#include "idlookup.h"
#include "equivalent.h"
#include "erreur.h"
#include "makestring.h"

static bool hash_is_full(void) { return hashused == hash_base; } //! test if all positions are occupied

static std::map<std::string, halfword> numero;

halfword idlookup(const std::string &s, bool nonewcontrolsequence)
{
	if (numero.find(s) != numero.end())
		return numero[s];
	if (nonewcontrolsequence)
		return undefined_control_sequence;
	if (hash_is_full())
		overflow("hash size", hash_size);
	numero[s] = --hashused;
	strings.push_back(s);
	eqtb_cs[hashused-hash_base].text = s;
	return hashused;
/*	int h = 0;
	for (unsigned char c: s)
		h = (2*h+c)%hash_prime;
	halfword p = h+hash_base;
	while (true)
	{
		if (text(p) > 0 && strings[text(p)] == s)
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
	}*/
}
