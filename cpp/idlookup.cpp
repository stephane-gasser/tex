#include "idlookup.h"
#include "overflow.h"
#include "makestring.h"
#include "texte.h"

//! test if all positions are occupied
static bool hash_is_full(void) { return hashused == hash_base; }

//! link for coalesced lists
static halfword& next(halfword p) { return hash[p].lh; }

halfword idlookup(const std::string &s)
{
	int h = 0;
	for (auto c: s)
	{
		h = 2*h+(unsigned char)c;
		while (h >= hash_prime)
			h -= hash_prime;
	}
	halfword p = h+hash_base;
	while (true)
	{
		if (text(p) > 0)
			if (length(text(p)) == s.size())
				if (TXT(text(p)) == s)
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
				str_room(s.size());
				int d = cur_length();
				while (cur_length() > 0)
				{
					flush_char();
					strpool[poolptr+s.size()] = strpool[poolptr];
				}
				for (auto c: s)
					append_char(c);
				text(p) = txt(makestring());
				poolptr += d;
			}
			return p;
		}
		p = next(p);
	}
}
