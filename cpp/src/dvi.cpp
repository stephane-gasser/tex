#include "dvi.h"
#include "police.h"

void writedvi(dviindex a, dviindex b)
{
	for (auto k = a; k < b; k++)
		dvifile << dvibuf[k];
}

void dviswap(void)
{
	if (dvilimit == dvibufsize)
	{
		writedvi(0, halfbuf);
		dvilimit = halfbuf;
		dvioffset = dvioffset+dvibufsize;
		dviptr = 0;
	}
	else
	{
		writedvi(halfbuf, dvibufsize);
		dvilimit = dvibufsize;
	}
	dvigone = dvigone+halfbuf;
}

void dvi_out(eightbits e)
{
	dvibuf[dviptr++] = e;
	if (dviptr == dvilimit)
		dviswap();
}

void dvifour(uint32_t x)
{
	dvi_out(x>>24);
	for (int i = 0; i < 3; i++)
	{
		x <<= 8;
		dvi_out(x>>24);
	}
}

void dvifontdef(internalfontnumber f)
{
	dvi_out(fnt_def1);
	dvi_out(f-1);
	auto &ft = fonts[f];
	dvi_out(ft.check.b0);
	dvi_out(ft.check.b1);
	dvi_out(ft.check.b2);
	dvi_out(ft.check.b3);
	dvifour(ft.size);
	dvifour(ft.dsize);
	dvi_out(ft.area.size());
	dvi_out(ft.name.size());
	for (auto c: ft.area)
		dvi_out(c);
	for (auto c: ft.name)
		dvi_out(c);
}

void dvipop(int l)
{
	if (l == dvioffset+dviptr && dviptr > 0)
		dviptr--;
	else
		dvi_out(pop);
}

enum
{
	none_seen = 0, //no |y_here| or |z_here| nodes have been encountered yet
	y_seen = 6, //we have seen |y_here| but not |z_here|
	z_seen = 12 //we have seen |z_here| but not |y_here|
};

enum
{
	y0 = 161, //move down by |y|
	y1 = 162, //move down and set |y|
	z0 = 166, //move down by |z|
	z1 = 167  //move down and set |z|
};

class MovementNode : public LinkedNode
{
	public:
		int width;
		int location;
		halfword info;
};

MovementNode *down_ptr, *right_ptr;

void movement(scaled w, eightbits o)
{
	auto q = new MovementNode;
	q->width = w;
	q->location = dvioffset+dviptr;
	if (o == down1)
	{
		q->link = down_ptr;
		down_ptr = q;
	}
	else
	{
		q->link = right_ptr;
		right_ptr = q;
	}
	auto p = dynamic_cast<MovementNode*>(q->link);
	smallnumber mstate = 0;
	bool l40 = false;
	int k;
	while (p)
	{
		if (p->width == w)
		{
			switch (mstate+p->info)
			{
				case none_seen+yz_OK:
				case none_seen+y_OK:
				case z_seen+yz_OK:
				case z_seen+y_OK: 
					if (p->location < dvigone)
						break;
					else
					{
						k = p->location-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += y1-down1;
						p->info = y_here;
						l40 = true;
						break;
					}
					break;
				case none_seen+z_OK:
				case y_seen+yz_OK:
				case y_seen+z_OK: 
					if (p->location < dvigone)
						break;
					else
					{
						k = p->location-dvioffset;
						if (k < 0)
							k += dvibufsize;
						dvibuf[k] += z1-down1;
						p->info = z_here;
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
			p = dynamic_cast<MovementNode*>(p->link);
		}
		else
		{
			switch (mstate+p->info)
			{
				case none_seen+y_here: 
					mstate = y_seen;
					p = dynamic_cast<MovementNode*>(p->link);
					break;
				case none_seen+z_here: 
					mstate = z_seen;
					p = dynamic_cast<MovementNode*>(p->link);
					break;
				case y_seen+z_here:
				case z_seen+y_here: 
					p = dynamic_cast<MovementNode*>(p->link);
					break;
			}
		}
	}
	if (!l40)
	{
		q->info = yz_OK;
		if (abs(w) >= 1<<23)
		{
		 	dvi_out(o+3); //|down4| or |right4|
			dvifour(w);
			return;
		}
		if (abs(w) >= 1<<15)
		{
			dvi_out(o+2); //|down3| or |right3|
			if (w < 0)
				w += 1<<24;
			dvi_out(w>>16);
			w %= 1<<16;
			dvi_out(w>>8);
			dvi_out(w%(1<<8));
			return;
		}
		if (abs(w) >= 1<<7)
		{
			dvi_out(o+1); //|down2| or |right2|
			if (w < 0)
				w += 1<<16;
			dvi_out(w>>8);
			dvi_out(w%(1<<8));
			return;
		}
		dvi_out(o);
		if (w < 0)
			w += 1<<8;
		dvi_out(w%(1<<8));
		return;
	}
	q->info = p->info;
	if (q->info == y_here)
	{
		dvi_out(o+y0-down1); //|y0| or |w0|
		while (q->link != p)
		{
			q = dynamic_cast<MovementNode*>(q->link);
			switch (q->info)
			{
				case yz_OK: 
					q->info = z_OK;
					break;
				case y_OK: 
					q->info = d_fixed;
			}
		}
	}
	else
	{
		dvi_out(o+z0-down1); //|z0| or |x0|
		while (q->link != p)
		{
			q = dynamic_cast<MovementNode*>(q->link);
			switch (q->info)
			{
				case yz_OK: 
					q->info = y_OK;
					break;
				case z_OK: 
					q->info = d_fixed;
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

void prunemovements(int l)
{
	while (down_ptr)
	{
		if (down_ptr->location < l)
			break;
		auto p = down_ptr;
		down_ptr = dynamic_cast<MovementNode*>(p->link);
		delete p;
	}
	while (right_ptr)
	{
		if (right_ptr->location < l)
			break;
		auto p = right_ptr;
		right_ptr = dynamic_cast<MovementNode*>(p->link);
		delete p;
	}
}

