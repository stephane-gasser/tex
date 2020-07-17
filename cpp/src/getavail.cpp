#include "getavail.h"
#include "runaway.h"
#include "erreur.h"

halfword getavail(void)
{
	halfword p = avail;
	if (p)
		avail = link(avail);
	else 
		if (memend < memmax)
			p = ++memend;
		else
		{
			p = --himemmin;
			if (himemmin <= lomemmax)
			{
				runaway();
				overflow("main memory size", memmax+1-memmin, curalign);
			}
		}
	link(p) = 0;
	return p;
}

halfword fast_get_avail(void)
{
	auto q = avail;
	if (q == 0)
		q = getavail();
	else  
	{ 
		avail = link(q); 
		link(q) = 0; 
	}
	return q;
}

void store_new_token(halfword &p, halfword t)
{

	auto q = getavail(); 
	link(p) = q; 
	info(q) = t;
	p = q;
}

void fast_store_new_token(halfword &p, halfword t)
{
	auto q = fast_get_avail();
	link(p) = q; 
	info(q) = t;
	p = q;
}

//! single-word node liberation 
void free_avail(halfword p)
{
	link(p) = avail; 
	avail = p;
}
