#include "maincontrol.h"
#include "fixlanguage.h"
#include "getavail.h"
#include "newligature.h"
#include "newdisc.h"
#include "freenode.h"
#include "getnext.h"
#include "xtoken.h"
#include "scancharnum.h"
#include "newspec.h"
#include "newglue.h"
#include "newparamglue.h"
#include "getxtoken.h"
#include "charwarning.h"
#include "begintokenlist.h"
#include "backinput.h"
#include "pauseforinstructions.h"
#include "showcurcmdchr.h"
#include "appspace.h"
#include "reportillegalcase.h"
#include "newligitem.h"
#include "appendglue.h"
#include "insertdollarsign.h"
#include "appendkern.h"
#include "newsavelevel.h"
#include "unsave.h"
#include "offsave.h"
#include "scandimen.h"
#include "handlerightbrace.h"
#include "beginbox.h"
#include "scanbox.h"
#include "newgraf.h"
#include "indentinhmode.h"
#include "normalparagraph.h"
#include "buildpage.h"
#include "headforvmode.h"
#include "newkern.h"
#include "itsallover.h"
#include "endgraf.h"
#include "begininsertoradjust.h"
#include "makemark.h"
#include "appendpenalty.h"
#include "deletelast.h"
#include "unpackage.h"
#include "newkern.h"
#include "appenditaliccorrection.h"
#include "makeaccent.h"
#include "alignerror.h"
#include "noalignerror.h"
#include "omiterror.h"
#include "initalign.h"
#include "privileged.h"
#include "doendv.h"
#include "cserror.h"
#include "initmath.h"
#include "starteqno.h"
#include "newnoad.h"
#include "scanmath.h"
#include "scanrulespec.h"
#include "appenddiscretionary.h"
#include "setmathchar.h"
#include "scanfifteenbitint.h"
#include "scantwentysevenbitint.h"
#include "mathlimitswitch.h"
#include "mathac.h"
#include "mathradical.h"
#include "scanspec.h"
#include "pushnest.h"
#include "newstyle.h"
#include "appendchoices.h"
#include "subsup.h"
#include "mathfraction.h"
#include "mathleftright.h"
#include "aftermath.h"
#include "prefixedcommand.h"
#include "gettoken.h"
#include "saveforafter.h"
#include "issuemessage.h"
#include "openorclosein.h"
#include "showwhatever.h"
#include "shiftcase.h"
#include "doextension.h"

void goto70()
{
	mains = eqtb[4751+curchr].hh.rh;
	if (mains == 1000)
		curlist.auxfield.hh.lh = 1000;
		else 
			if (mains < 1000)
			{
				if (mains > 0)
					curlist.auxfield.hh.lh = mains;
			}
			else 
				if (curlist.auxfield.hh.lh < 1000)
					curlist.auxfield.hh.lh = 1000;
				else
					curlist.auxfield.hh.lh = mains;
	mainf = cur_font();
	bchar = fontbchar[mainf];
	falsebchar = fontfalsebchar[mainf];
	if (curlist.modefield > 0 && eqtb[5313].int_ != curlist.auxfield.hh.rh)
		fixlanguage();
	ligstack = avail;
	if (ligstack == 0)
		ligstack = getavail();
	else
	{
		avail = link(ligstack);
		link(ligstack) = 0;
	}
	type(ligstack) = mainf;
	curl = curchr;
	subtype(ligstack) = curl;
	curq = curlist.tailfield;
	if (cancelboundary)
	{
		cancelboundary = false;
		maink = 0;
	}
	else
		maink = bcharlabel[mainf];
}

void goto80()
{
	if (curl < 256)
	{
		if (link(curq) > 0)
		if (subtype(curlist.tailfield) == hyphenchar[mainf])
			insdisc = true;
		if (ligaturepresent)
		{
			mainp = newligature(mainf, curl, link(curq));
			if (lfthit)
			{
				subtype(mainp) = 2;
				lfthit = false;
			}
			if (rthit && ligstack == 0)
			{
				subtype(mainp)++;
				rthit = false;
			}
			link(curq) = mainp;
			curlist.tailfield = mainp;
			ligaturepresent = false;
		}
		if (insdisc)
		{
			insdisc = false;
			if (curlist.modefield > 0)
			{
				link(curlist.tailfield) = newdisc();
				curlist.tailfield = link(curlist.tailfield);
			}
		}
	}
}

void goto101()
{
	mains = eqtb[4751+curchr].hh.rh;
	if (mains == 1000)
		curlist.auxfield.hh.lh = 1000;
	else 
		if (mains < 1000)
		{
			if (mains > 0)
				curlist.auxfield.hh.lh = mains;
		}
		else 
			if (curlist.auxfield.hh.lh < 1000)
				curlist.auxfield.hh.lh = 1000;
			else
				curlist.auxfield.hh.lh = mains;
	ligstack = avail;
	if (ligstack == 0)
		ligstack = getavail();
	else
	{
		avail = link(ligstack);
		link(ligstack) = 0;
	}
	type(ligstack) = mainf;
	curr = curchr;
	subtype(ligstack) = curr;
	if (curr == falsebchar)
		curr = 256;
}

void goto95()
{
	mainp = link(ligstack+1);
	if (mainp > 0)
	{
		link(curlist.tailfield) = mainp;
		curlist.tailfield = link(curlist.tailfield);
	}
	tempptr = ligstack;
	ligstack = link(tempptr);
	freenode(tempptr, 2);
	maini = fontinfo[charbase[mainf]+curl].qqqq;
	ligaturepresent = true;
	if (ligstack == 0)
		if (mainp > 0)
		{
			getnext();
			if (curcmd == 11 || curcmd == 12 || curcmd == 68)
			{
				goto101();
				return;
			}
			xtoken();
			if (curcmd == 11 || curcmd == 12 || curcmd == 68)
			{
				goto101();
				return;
			}
			if (curcmd == 16)
			{
				scancharnum();
				curchr = curval;
				goto101();
				return;
			}
			if (curcmd == 65)
				bchar = 256;
			curr = bchar;
			ligstack = 0;
			return;
		}
		else
			curr = bchar;
	else
		curr = subtype(ligstack);
}

void goto120()
{
	if (eqtb[2894].hh.rh == 0)
	{
		mainp = fontglue[cur_font()];
		if (mainp == 0)
		{
			mainp = newspec(0);
			maink = parambase[cur_font()]+2;
			mem[mainp+1].int_ = fontinfo[maink].int_;
			mem[mainp+2].int_ = fontinfo[maink+1].int_;
			mem[mainp+3].int_ = fontinfo[maink+2].int_;
			fontglue[cur_font()] = mainp;
		}
		tempptr = newglue(mainp);
	}
	else
		tempptr = newparamglue(12);
	link(curlist.tailfield) = tempptr;
	curlist.tailfield = tempptr;
	getxtoken();
}

bool goto92()
{
	if (curchr < fontbc[mainf] || curchr > fontec[mainf])
	{
		charwarning(mainf, curchr);
		link(ligstack) = avail;
		avail = ligstack;
		getxtoken();
		return true;
	}
	maini = fontinfo[charbase[mainf]+curl].qqqq;
	if (maini.b0 <= 0)
	{
		charwarning(mainf, curchr);
		link(ligstack) = avail;
		avail = ligstack;
		getxtoken();
		return true;
	}
	link(curlist.tailfield) = ligstack;
	curlist.tailfield = ligstack;
	getnext();
	if (curcmd == 11 || curcmd == 12 || curcmd == 68)
		goto101();
	else
	{
		xtoken();
		if (curcmd == 11 || curcmd == 12 || curcmd == 68)
			goto101();
		else
		{
			if (curcmd == 16)
			{
				scancharnum();
				curchr = curval;
				goto101();
			}
			else
			{
				if (curcmd == 65)
					bchar = 256;
				curr = bchar;
				ligstack = 0;
			}
		}
	}
	return false;
}

void goto110112(bool is110)
{
	while (true)
	{
		if (is110)
		{
			if (maini.b2%4 != 1)
			{
				goto80();
				if (ligstack == 0)
					return;
				curq = curlist.tailfield;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;;
				is110 = true;
				continue;
			}
			if (curr == 256)
			{
				goto80();
				if (ligstack == 0)
					return;;
				curq = curlist.tailfield;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;
				is110 = true;
				continue;
			}
			maink = ligkernbase[mainf]+maini.b3;
			mainj = fontinfo[maink].qqqq;
			if (mainj.b0 > 128)
			{
				maink = ligkernbase[mainf]+256*mainj.b2+mainj.b3+32768-256*128;
				mainj = fontinfo[maink].qqqq;
			}
		}
		if (mainj.b1 == curr)
			if (mainj.b0 <= 128)
			{
				if (mainj.b2 >= 128)
				{
					if (curl < 256)
					{
						if (link(curq) > 0 && subtype(curlist.tailfield) == hyphenchar[mainf])
							insdisc = true;
						if (ligaturepresent)
						{
							mainp = newligature(mainf, curl, link(curq));
							if (lfthit)
							{
								subtype(mainp) = 2;
								lfthit = false;
							}
							if (rthit && ligstack == 0)
							{
								subtype(mainp)++;
								rthit = false;
							}
							link(curq) = mainp;
							curlist.tailfield = mainp;
							ligaturepresent = false;
						}
						if (insdisc)
						{
							insdisc = false;
							if (curlist.modefield > 0)
							{
								link(curlist.tailfield) = newdisc();
								curlist.tailfield = link(curlist.tailfield);
							}
						}
					}
					link(curlist.tailfield) = newkern(fontinfo[kernbase[mainf]+256*mainj.b2+mainj.b3].int_);
					curlist.tailfield = link(curlist.tailfield);
					if (ligstack == 0)
						return;;
					curq = curlist.tailfield;
					curl = subtype(ligstack);
					if (ligstack < himemmin)
						goto95();
					else
						if (goto92())
							return;
					is110 = true;
					continue;
				}
				if (curl == 256)
					lfthit = true;
				else 
					if (ligstack == 0)
						rthit = true;
				if (interrupt)
					pauseforinstructions();
				switch (mainj.b2)
				{
					case 1:
					case 5:
						curl = mainj.b3;
						maini = fontinfo[charbase[mainf]+curl].qqqq;
						ligaturepresent = true;
						break;
					case 2:
					case 6:
						curr = mainj.b3;
						if (ligstack == 0)
						{
							ligstack = newligitem(curr);
							bchar = 256;
						}
						else 
							if (ligstack >= himemmin)
							{
								mainp = ligstack;
								ligstack = newligitem(curr);
								link(ligstack+1) = mainp;
							}
							else
								subtype(ligstack) = curr;
						break;
					case 3:
						curr = mainj.b3;
						mainp = ligstack;
						ligstack = newligitem(curr);
						link(ligstack) = mainp;
						break;
					case 7:
					case 11:
						if (curl < 256)
						{
							if (link(curq) > 0)
							if (subtype(curlist.tailfield) == hyphenchar[mainf])
								insdisc = true;
							if (ligaturepresent)
							{
								mainp = newligature(mainf, curl, link(curq));
								if (lfthit)
								{
									subtype(mainp) = 2;
									lfthit = false;
								}
								link(curq) = mainp;
								curlist.tailfield = mainp;
								ligaturepresent = false;
							}
							if (insdisc)
							{
								insdisc = false;
								if (curlist.modefield > 0)
								{
									link(curlist.tailfield) = newdisc();
									curlist.tailfield = link(curlist.tailfield);
								}
							}
						}
						curq = curlist.tailfield;
						curl = mainj.b3;
						maini = fontinfo[charbase[mainf]+curl].qqqq;
						ligaturepresent = true;
						break;
					default:
						curl = mainj.b3;
						ligaturepresent = true;
						if (ligstack == 0)
						{
							goto80();
							if (ligstack == 0)
								return;;
							curq = curlist.tailfield;
							curl = subtype(ligstack);
						}
						if (ligstack < himemmin)
							goto95();
						else
							if (goto92())
								return;;
				}
				if (mainj.b2 > 4 && mainj.b2 != 7)
				{
					goto80();
					if (ligstack == 0)
						return;;
					curq = curlist.tailfield;
					curl = subtype(ligstack);
					if (ligstack < himemmin)
						goto95();
					else 
						if (goto92())
							return;
					is110 = true;
					continue;
				}
				if (curl < 256)
				{
					is110 = true;
					continue;
				}
				maink = bcharlabel[mainf];
				mainj = fontinfo[maink].qqqq;
				is110 = false;
				continue;
			}
		if (mainj.b0 == 0)
			maink++;
		else
		{
			if (mainj.b0 >= 128)
			{
				goto80();
				if (ligstack == 0)
					return;;
				curq = curlist.tailfield;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;
				is110 = true;
				continue;
			}
			maink += mainj.b0+1;
		}
		mainj = fontinfo[maink].qqqq;
		is110 = false;
	}
}

void maincontrol(void)
{
	int t;
	if (eqtb[3419].hh.rh)
		begintokenlist(eqtb[3419].hh.rh, 12);
	getxtoken();
	while (true)
	{
		if (interrupt && OKtointerrupt)
		{
			backinput();
			if (interrupt)
				pauseforinstructions();
			getxtoken();
			continue;
		}
		if (eqtb[5299].int_ > 0)
			showcurcmdchr();
		switch (abs(curlist.modefield)+curcmd)
		{
			case 113:
			case 114:
			case 170: 
				goto70();
				if (maink == 0)
				{
					if (!goto92())
						goto110112(true);
					continue;
				}
				curr = curl;
				curl = 256;
				mainj = fontinfo[maink].qqqq;
				goto110112(false);
				continue;
			case 118:
				scancharnum();
				curchr = curval;
				if (maink == 0)
				{
					if (!goto92())
						goto110112(true);
					continue;
				}
				curr = curl;
				curl = 256;
				goto70();
				mainj = fontinfo[maink].qqqq;
				goto110112(false);
				continue;
			case 167:
				getxtoken();
				if (curcmd == 11 || curcmd == 12 || curcmd == 68 || curcmd == 16)
					cancelboundary = true;
				continue;
			case 112: 
				if (curlist.auxfield.hh.lh == 1000)
				{
					goto120();
					continue;
				}
				else
					appspace();
				break;
			case 166:
			case 267: 
				goto120();
				continue;
			case 1:
			case 102:
			case 203:
			case 11:
			case 213:
			case 268: 
				break;
			case 40:
			case 141:
			case 242:
				do
					getxtoken();
				while (curcmd == 10);
				continue;
			case 15: 
				if (itsallover())
					return;
				break;
			case 23:
			case 123:
			case 224:
			case 71:
			case 172:
			case 273:
			case 39:
			case 45:
			case 49:
			case 150:
			case 7:
			case 108:
			case 209: 
				reportillegalcase();
				break;
			case 8:
			case 109:
			case 9:
			case 110:
			case 18:
			case 119:
			case 70:
			case 171:
			case 51:
			case 152:
			case 16:
			case 117:
			case 50:
			case 151:
			case 53:
			case 154:
			case 67:
			case 168:
			case 54:
			case 155:
			case 55:
			case 156:
			case 57:
			case 158:
			case 56:
			case 157:
			case 31:
			case 132:
			case 52:
			case 153:
			case 29:
			case 130:
			case 47:
			case 148:
			case 212:
			case 216:
			case 217:
			case 230:
			case 227:
			case 236:
			case 239: 
				insertdollarsign();
				break;
			case 37:
			case 137:
			case 238:
				link(curlist.tailfield) = scanrulespec();
				curlist.tailfield = link(curlist.tailfield);
				if (abs(curlist.modefield) == 1)
					curlist.auxfield.int_ = -65536000;
				else 
					if (abs(curlist.modefield) == 102)
						curlist.auxfield.hh.lh = 1000;
				break;
			case 28:
			case 128:
			case 229:
			case 231: 
				appendglue();
				break;
			case 30:
			case 131:
			case 232:
			case 233: 
				appendkern();
				break;
			case 2:
			case 103: 
				newsavelevel(1);
				break;
			case 62:
			case 163:
			case 264: 
				newsavelevel(14);
				break;
			case 63:
			case 164:
			case 265: 
				if (curgroup == 14)
					unsave();
				else
					offsave();
				break;
			case 3:
			case 104:
			case 205: 
				handlerightbrace();
				break;
			case 22:
			case 124:
			case 225:
				t = curchr;
				scandimen(false, false, false);
				if (t == 0)
					scanbox(curval);
				else
					scanbox(-curval);
				break;
			case 32:
			case 133:
			case 234: 
				scanbox(1073742237+curchr);
				break;
			case 21:
			case 122:
			case 223: 
				beginbox(0);
				break;
			case 44: 
				newgraf(curchr > 0);
				break;
			case 12:
			case 13:
			case 17:
			case 69:
			case 4:
			case 24:
			case 36:
			case 46:
			case 48:
			case 27:
			case 34:
			case 65:
			case 66:
				backinput();
				newgraf(true);
				break;
			case 145:
			case 246: 
				indentinhmode();
				break;
			case 14:
				normalparagraph();
				if (curlist.modefield > 0)
				buildpage();
				break;
			case 115:
				if (alignstate < 0)
					offsave();
				endgraf();
				if (curlist.modefield == 1)
					buildpage();
				break;
			case 116:
			case 129:
			case 138:
			case 126:
			case 134: 
				headforvmode();
				break;
			case 38:
			case 139:
			case 240:
			case 140:
			case 241: 
				begininsertoradjust();
				break;
			case 19:
			case 120:
			case 221: 
				makemark();
				break;
			case 43:
			case 144:
			case 245: 
				appendpenalty();
				break;
			case 26:
			case 127:
			case 228: 
				deletelast();
				break;
			case 25:
			case 125:
			case 226: 
				unpackage();
				break;
			case 146: 
				appenditaliccorrection();
				break;
			case 247:
				link(curlist.tailfield) = newkern(0);
				curlist.tailfield = link(curlist.tailfield);
				break;
			case 149:
			case 250: 
				appenddiscretionary();
				break;
			case 147: 
				makeaccent();
				break;
			case 6:
			case 107:
			case 208:
			case 5:
			case 106:
			case 207: 
				alignerror();
				break;
			case 35:
			case 136:
			case 237: 
				noalignerror();
				break;
			case 64:
			case 165:
			case 266: 
				omiterror();
				break;
			case 33:
			case 135: 
				initalign();
				break;
			case 235: 
				if (privileged())
					if (curgroup == 15)
						initalign();
					else
						offsave();
				break;
			case 10:
			case 111: 
				doendv();
				break;
			case 68:
			case 169:
			case 270: 
				cserror();
				break;
			case 105: 
				initmath();
				break;
			case 251: 
				if (privileged())
					if (curgroup == 15)
						starteqno();
					else
						offsave();
				break;
			case 204:
				link(curlist.tailfield) = newnoad();
				curlist.tailfield = link(curlist.tailfield);
				backinput();
				scanmath(curlist.tailfield+1);
				break;
			case 214:
			case 215:
			case 271: 
				setmathchar(eqtb[5007+curchr].hh.rh);
				break;
			case 219:
				scancharnum();
				curchr = curval;
				setmathchar(eqtb[5007+curchr].hh.rh);
				break;
			case 220:
				scanfifteenbitint();
				setmathchar(curval);
				break;
			case 272: 
				setmathchar(curchr);
				break;
			case 218:
				scantwentysevenbitint();
				setmathchar(curval/4096);
				break;
			case 253:
				link(curlist.tailfield) = newnoad();
				curlist.tailfield = link(curlist.tailfield);
				type(curlist.tailfield) = curchr;
				scanmath(curlist.tailfield+1);
				break;
			case 254: 
				mathlimitswitch();
				break;
			case 269: 
				mathradical();
				break;
			case 248:
			case 249: 
				mathac();
				break;
			case 259:
				scanspec(12, false);
				normalparagraph();
				pushnest();
				curlist.modefield = -1;
				curlist.auxfield.int_ = -65536000;
				if (eqtb[3418].hh.rh)
				begintokenlist(eqtb[3418].hh.rh, 11);
				break;
			case 256:
				link(curlist.tailfield) = newstyle(curchr);
				curlist.tailfield = link(curlist.tailfield);
				break;
			case 258:
				link(curlist.tailfield) = newglue(0);
				curlist.tailfield = link(curlist.tailfield);
				mem[curlist.tailfield].hh.b1 = 98;
				break;
			case 257: 
				appendchoices();
				break;
			case 211:
			case 210: 
				subsup();
				break;
			case 255: 
				mathfraction();
				break;
			case 252: 
				mathleftright();
				break;
			case 206: 
				if (curgroup == 15)
					aftermath();
				else
					offsave();
				break;
			case 72:
			case 173:
			case 274:
			case 73:
			case 174:
			case 275:
			case 74:
			case 175:
			case 276:
			case 75:
			case 176:
			case 277:
			case 76:
			case 177:
			case 278:
			case 77:
			case 178:
			case 279:
			case 78:
			case 179:
			case 280:
			case 79:
			case 180:
			case 281:
			case 80:
			case 181:
			case 282:
			case 81:
			case 182:
			case 283:
			case 82:
			case 183:
			case 284:
			case 83:
			case 184:
			case 285:
			case 84:
			case 185:
			case 286:
			case 85:
			case 186:
			case 287:
			case 86:
			case 187:
			case 288:
			case 87:
			case 188:
			case 289:
			case 88:
			case 189:
			case 290:
			case 89:
			case 190:
			case 291:
			case 90:
			case 191:
			case 292:
			case 91:
			case 192:
			case 293:
			case 92:
			case 193:
			case 294:
			case 93:
			case 194:
			case 295:
			case 94:
			case 195:
			case 296:
			case 95:
			case 196:
			case 297:
			case 96:
			case 197:
			case 298:
			case 97:
			case 198:
			case 299:
			case 98:
			case 199:
			case 300:
			case 99:
			case 200:
			case 301:
			case 100:
			case 201:
			case 302:
			case 101:
			case 202:
			case 303: 
				prefixedcommand();
				break;
			case 41:
			case 142:
			case 243:
				gettoken();
				aftertoken = curtok;
				break;
			case 42:
			case 143:
			case 244:
				gettoken();
				saveforafter(curtok);
				break;
			case 61:
			case 162:
			case 263: 
				openorclosein();
				break;
			case 59:
			case 160:
			case 261: 
				issuemessage();
				break;
			case 58:
			case 159:
			case 260: 
				shiftcase();
				break;
			case 20:
			case 121:
			case 222: 
				showwhatever();
				break;
			case 60:
			case 161:
			case 262: 
				doextension();
		}
		getxtoken();
	}
}
