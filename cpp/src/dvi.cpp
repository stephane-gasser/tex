#include "dvi.h"
#include "police.h"
#include "preparemag.h"
#include "fichier.h"
#include "impression.h"
#include "equivalent.h"
#include "chaine.h"

constexpr dviindex halfbuf = dvibufsize/2;

enum info
{
	y_here = 1, //!< \a info when the movement entry points to a \a y command
	z_here = 2, //!< \a info when the movement entry points to a \a z command
	yz_OK = 3, //!< \a info corresponding to an unconstrained \a down command
	y_OK = 4, //!< \a info corresponding to a \a down that can't become a \a z
	z_OK = 5, //!< \a info corresponding to a \a down that can't become a \a y
	d_fixed = 6 //!< \a info corresponding to a \a down that can't change
};

static eightbits dvibuf[dvibufsize+1];
static dviindex dvilimit = dvibufsize;
static int dvigone = 0;

void writedvi(dviindex a, dviindex b)
{
	for (auto k = a; k < b; k++)
		dvifile << dvibuf[k];
}

static void dviswap(void)
{
	if (dvilimit == dvibufsize)
	{
		writedvi(0, halfbuf);
		dvilimit = halfbuf;
		dvioffset += dvibufsize;
		dviptr = 0;
	}
	else
	{
		writedvi(halfbuf, dvibufsize);
		dvilimit = dvibufsize;
	}
	dvigone += halfbuf;
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
	for (auto c: ft.area+ft.name)
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

static MovementNode *down_ptr = nullptr, *right_ptr = nullptr;

void movement(scaled w, eightbits o)
{
	auto q = new MovementNode;
	q->width = w;
	q->location = dvioffset+dviptr;
	appendAtStart(o == down1 ? down_ptr : right_ptr, q);
	auto p = dynamic_cast<MovementNode*>(q->link);
	smallnumber mstate = 0;
	bool l40 = false;
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
						int k = p->location-dvioffset;
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
						int k = p->location-dvioffset;
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
	if (curh == dvih)
		return;
	movement(curh-dvih, right1);
	dvih = curh;
}

void synch_v(void)
{
	if (curv == dviv)
		return;
	movement(curv-dviv, down1);
	dviv = curv;
}

void prunemovements(int l)
{
	while (down_ptr)
	{
		if (down_ptr->location < l)
			break;
		removeNodeAtStart(down_ptr);
	}
	while (right_ptr)
	{
		if (right_ptr->location < l)
			break;
		removeNodeAtStart(down_ptr);
	}
}

void closefilesandterminate(void)
{
	for (int k = 0; k < 16; k++)
		if (writeopen[k])
			aclose(writefile[k]);
	while (curs > -1)
	{
		if (curs > 0)
			dvi_out(pop);
		else
		{
			dvi_out(eop);
			totalpages++;
		}
		curs--;
	}
	if (totalpages == 0)
		print("\rNo pages of output.");
	else
	{
		dvi_out(post);
		dvifour(lastbop);
		lastbop = dvioffset+dviptr-5;
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(mag());
		dvifour(maxv);
		dvifour(maxh);
		dvi_out(maxpush>>8);
		dvi_out(maxpush%(1<<8));
		dvi_out((totalpages>>8)%(1<<8));
		dvi_out(totalpages%(1<<8));
		for (; fonts.size(); fonts.pop_back())
			if (fonts.back().used)
				dvifontdef(fonts.size()+1);
		dvi_out(post_post);
		dvifour(lastbop);
		dvi_out(id_byte);
		for (int k = 4+(dvibufsize-dviptr)%4; k > 0; k--)
			dvi_out(223);
		if (dvilimit == halfbuf)
			writedvi(halfbuf, dvibufsize);
		if (dviptr > 0)
			writedvi(0, dviptr);
		print("\rOutput written on "+outputfilename+"// ("+std::to_string(totalpages)+" page"+(totalpages == 1 ? "" : "s")+", "+std::to_string(dvioffset+dviptr)+" bytes).");
		bclose(dvifile);
	}
	if (logopened)
	{
		logfile << "\n";
		aclose(logfile);
		selector -= 2;
		if (selector == term_only)
			print("\rTranscript written on "+logname+".");
	}
}

