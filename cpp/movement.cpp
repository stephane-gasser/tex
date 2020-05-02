#include "movement.h"
#include "getnode.h"
#include "dviswap.h"
#include "dvifour.h"

void movement(scaled w, eightbits o)
{
	auto q = getnode(3);
	mem[q+1].int_ = w;
	mem[q+2].int_ = dvioffset+dviptr;
	if (o == 157)
	{
		link(q) = downptr;
		downptr = q;
	}
	else
	{
		link(q) = rightptr;
		rightptr = q;
	}
	auto p = link(q);
	smallnumber mstate = 0;
	bool l40 = false;
	int k;
	while (p)
	{
		if (mem[p+1].int_ == w)
			switch (mstate+info(p))
			{
				case 3:
				case 4:
				case 15:
				case 16: 
					if (mem[p+2].int_ < dvigone)
						break;
					else
					{
						k = mem[p+2].int_-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += 5;
						info(p) = 1;
						l40 = true;
						break;
					}
					break;
				case 5:
				case 9:
				case 11: 
					if (mem[p+2].int_ < dvigone)
						break;
					else
					{
						k = mem[p+2].int_-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += 10;
						info(p) = 2;
						l40 = true;
						break;
					}
					break;
				case 1:
				case 2:
				case 8:
				case 13:
					l40 = true;
					break;
			}
		else
			switch (mstate+info(p))
			{
				case 1: 
					mstate = 6;
					break;
				case 2: 
					mstate = 12;
					break;
				case 8:
				case 13: 
					break;
			}
		p = link(p);
	}
	if (!l40)
	{
		info(q) = 3;
		if (abs(w) >= 8388608)
		{
			dvibuf[dviptr++] = o+3;
			if (dviptr == dvilimit)
				dviswap();
			dvifour(w);
			return;
		}
		if (abs(w) >= 0x80'00)
		{
			dvibuf[dviptr++] = o+2;
			if (dviptr == dvilimit)
				dviswap();
			if (w < 0)
				w += 16777216;
			dvibuf[dviptr++] = w/0x1'00'00;
			if (dviptr == dvilimit)
				dviswap();
			w %= 0x1'00'00;
			dvibuf[dviptr++] = w/0x1'00;
			if (dviptr == dvilimit)
				dviswap();
			dvibuf[dviptr++] = w%0x1'00;
			if (dviptr == dvilimit)
				dviswap();
			return;
		}
		if (abs(w) >= 128)
		{
			dvibuf[dviptr++] = o+1;
			if (dviptr == dvilimit)
				dviswap();
			if (w < 0)
			w += 0x1'00'00;
			dvibuf[dviptr++] = w/0x1'00;
			if (dviptr == dvilimit)
				dviswap();
			dvibuf[dviptr++] = w%0x1'00;
			if (dviptr == dvilimit)
				dviswap();
			return;
		}
		dvibuf[dviptr++] = o;
		if (dviptr == dvilimit)
			dviswap();
		if (w < 0)
		w += 0x1'00;
		dvibuf[dviptr++] = w%0x1'00;
		if (dviptr == dvilimit)
			dviswap();
		return;
	}
	info(q) = info(p);
	if (info(q) == 1)
	{
		dvibuf[dviptr++] = o+4;
		if (dviptr == dvilimit)
			dviswap();
		while (link(q) != p)
		{
			q = link(q);
			switch (info(q))
			{
				case 3: 
					info(q) = 5;
					break;
				case 4: 
					info(q) = 6;
			}
		}
	}
	else
	{
		dvibuf[dviptr++] = o+9;
		if (dviptr == dvilimit)
			dviswap();
		while (link(q) != p)
		{
			q = link(q);
			switch (info(q))
			{
				case 3: 
					info(q) = 4;
					break;
				case 5: 
					info(q) = 6;
			}
		}
	}
}
