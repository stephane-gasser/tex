#include "movement.h"
#include "getnode.h"
#include "dviswap.h"
#include "dvifour.h"

void movement(scaled w, eightbits o)
{
	auto q = getnode(movement_node_size);
	width(q) = w;
	location(q) = dvioffset+dviptr;
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
		if (width(p) == w)
		{
			switch (mstate+info(p))
			{
				case none_seen+yz_OK:
				case none_seen+y_OK:
				case z_seen+yz_OK:
				case z_seen+y_OK: 
					if (location(p) < dvigone)
						break;
					else
					{
						k = location(p)-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += 5;
						info(p) = 1;
						l40 = true;
						break;
					}
					break;
				case none_seen+z_OK:
				case y_seen+yz_OK:
				case y_seen+z_OK: 
					if (location(p) < dvigone)
						break;
					else
					{
						k = location(p)-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += 10;
						info(p) = 2;
						l40 = true;
						break;
					}
					break;
				case none_seen+y_here:
				case none_seen+z_here:
				case y_seen+z_here:
				case z_seen+y_here:
					l40 = true;
					break;
			}
			p = link(p);
		}
		else
		{
			switch (mstate+info(p))
			{
				case none_seen+y_here: 
					mstate = y_seen;
					p = link(p);
					break;
				case none_seen+z_here: 
					mstate = z_seen;
					p = link(p);
					break;
				case y_seen+z_here:
				case z_seen+y_here: 
					p = link(p);
					break;
			}
		}
	}
	if (!l40)
	{
		info(q) = 3;
		if (abs(w) >= 8388608)
		{
			dvi_out(o+3);
			dvifour(w);
			return;
		}
		if (abs(w) >= 0x80'00)
		{
			dvi_out(o+2);
			if (w < 0)
				w += 16777216;
			dvi_out(w/0x1'00'00);
			w %= 0x1'00'00;
			dvi_out(w/0x1'00);
			dvi_out(w%0x1'00);
			return;
		}
		if (abs(w) >= 128)
		{
			dvi_out(o+1);
			if (w < 0)
				w += 0x1'00'00;
			dvi_out(w/0x1'00);
			dvi_out(w%0x1'00);
			return;
		}
		dvi_out(o);
		if (w < 0)
			w += 0x1'00;
		dvi_out(w%0x1'00);
		return;
	}
	info(q) = info(p);
	if (info(q) == 1)
	{
		dvi_out(o+4);
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
		dvi_out(o+9);
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

void synch_h(void)
{
	if (curh != dvih)
	{
		movement(curh-dvih, right1);
		dvih = curh;
	}
}

void synch_v(void)
{
	if (curv != dviv)
	{
		movement(curv-dviv, down1);
		dviv = curv;
	}
}
