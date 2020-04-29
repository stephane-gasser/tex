#include "maincontrol.h"
void maincontrol(void)
label
  60, 21, 70, 80, 90, 91, 92, 95, 100, 101, 110, 111, 112, 120, 10;
var
  t: integer;
{
  if (eqtb[3419].hh.rh != 0)
    begintokenlist(eqtb[3419].hh.rh, 12);
  60:
    getxtoken;
  21:
    
if (interrupt != 0)
      if (OKtointerrupt)
      {
        backinput;
        {
          if (interrupt != 0)
            pauseforinstructions;
        }
        goto 60;
      }
  

  if (eqtb[5299].int > 0)
    showcurcmdchr
;
  case abs(curlist.modefield)+curcmd of
    113, 114, 170: goto 70;
    118:
    {
      scancharnum;
      curchr = curval;
      goto 70;
    }
    167:
    {
      getxtoken;
      if ((curcmd == 11) or (curcmd == 12) or (curcmd == 68) or (curcmd == 16))
        cancelboundary = true;
      goto 21;
    }
    112: if (curlist.auxfield.hh.lh == 1000)
        goto 120
      else
        appspace;
    166, 267: goto 120;
    
1, 102, 203, 11, 213, 268: ;
    40, 141, 242:
    {
      
repeat
        getxtoken;
      until curcmd != 10
;
      goto 21;
    }
    15: if (itsallover)
        goto 10;
    
23, 123, 224, 71, 172, 273,

39,

45,

    
49, 150,
7, 108, 209: reportillegalcase;
    
8, 109, 9, 110, 18, 119, 70, 171, 51, 152, 16, 117, 50, 151, 53, 154, 67, 168, 54,
    155, 55, 156, 57, 158, 56, 157, 31, 132, 52, 153, 29, 130, 47, 148, 212, 216, 217, 230, 227, 236, 239
: insertdollarsign;
    
37, 137, 238:
    {
      {
        mem[curlist.tailfield].hh.rh = scanrulespec;
        curlist.tailfield = mem[curlist.tailfield].hh.rh;
      }
      if (abs(curlist.modefield) == 1)
        curlist.auxfield.int = -65536000
      else if (abs(curlist.modefield) == 102)
        curlist.auxfield.hh.lh = 1000;
    }
    

28, 128, 229, 231: appendglue;
    30, 131, 232, 233: appendkern;
    

2, 103: newsavelevel(1);
    62, 163, 264: newsavelevel(14);
    63, 164, 265: if (curgroup == 14)
        unsave
      else
        offsave;
    

3, 104, 205: handlerightbrace;
    

22, 124, 225:
    {
      t = curchr;
      scandimen(false, false, false);
      if (t == 0)
        scanbox(curval)
      else
        scanbox(-curval);
    }
    32, 133, 234: scanbox(1073742237+curchr);
    21, 122, 223: beginbox(0);
    

44: newgraf(curchr > 0);
    12, 13, 17, 69, 4, 24, 36, 46, 48, 27, 34, 65, 66:
    {
      backinput;
      newgraf(true);
    }
    

145, 246: indentinhmode;
    

14:
    {
      normalparagraph;
      if (curlist.modefield > 0)
        buildpage;
    }
    115:
    {
      if (alignstate < 0)
        offsave;
      endgraf;
      if (curlist.modefield == 1)
        buildpage;
    }
    116, 129, 138, 126, 134: headforvmode;
    

38, 139, 240, 140, 241: begininsertoradjust;
    19, 120, 221: makemark;
    

43, 144, 245: appendpenalty;
    

26, 127, 228: deletelast;
    

25, 125, 226: unpackage;
    

146: appenditaliccorrection;
    247:
    {
      mem[curlist.tailfield].hh.rh = newkern(0);
      curlist.tailfield = mem[curlist.tailfield].hh.rh;
    }
    

149, 250: appenddiscretionary;
    

147: makeaccent;
    

6, 107, 208, 5, 106, 207: alignerror;
    35, 136, 237: noalignerror;
    64, 165, 266: omiterror;
    

33, 135: initalign;
    235: if (privileged)
        if (curgroup == 15)
          initalign
        else
          offsave;
    10, 111: doendv;
    

68, 169, 270: cserror;
    

105: initmath;
    

251: if (privileged)
        if (curgroup == 15)
          starteqno
        else
          offsave;
    

204:
    {
      {
        mem[curlist.tailfield].hh.rh = newnoad;
        curlist.tailfield = mem[curlist.tailfield].hh.rh;
      }
      backinput;
      scanmath(curlist.tailfield+1);
    }
    

214, 215, 271: setmathchar(eqtb[5007+curchr].hh.rh-0);
    219:
    {
      scancharnum;
      curchr = curval;
      setmathchar(eqtb[5007+curchr].hh.rh-0);
    }
    220:
    {
      scanfifteenbitint;
      setmathchar(curval);
    }
    272: setmathchar(curchr);
    218:
    {
      scantwentysevenbitint;
      setmathchar(curval div 4096);
    }
    

253:
    {
      {
        mem[curlist.tailfield].hh.rh = newnoad;
        curlist.tailfield = mem[curlist.tailfield].hh.rh;
      }
      mem[curlist.tailfield].hh.b0 = curchr;
      scanmath(curlist.tailfield+1);
    }
    254: mathlimitswitch;
    

269: mathradical;
    

248, 249: mathac;
    

259:
    {
      scanspec(12, false);
      normalparagraph;
      pushnest;
      curlist.modefield = -1;
      curlist.auxfield.int = -65536000;
      if (eqtb[3418].hh.rh != 0)
        begintokenlist(eqtb[3418].hh.rh, 11);
    }
    

256:
    {
      mem[curlist.tailfield].hh.rh = newstyle(curchr);
      curlist.tailfield = mem[curlist.tailfield].hh.rh;
    }
    258:
    {
      {
        mem[curlist.tailfield].hh.rh = newglue(0);
        curlist.tailfield = mem[curlist.tailfield].hh.rh;
      }
      mem[curlist.tailfield].hh.b1 = 98;
    }
    257: appendchoices;
    

211, 210: subsup;
    

255: mathfraction;
    

252: mathleftright;
    

206: if (curgroup == 15)
        aftermath
      else
        offsave;
    

72, 173, 274, 73, 174, 275, 74, 175, 276, 75, 176, 277, 76, 177, 278, 77,
    178, 279, 78, 179, 280, 79, 180, 281, 80, 181, 282, 81, 182, 283, 82, 183, 284, 83, 184,
    285, 84, 185, 286, 85, 186, 287, 86, 187, 288, 87, 188, 289, 88, 189, 290, 89, 190, 291, 90, 191, 292, 91, 192, 293, 92, 193, 294, 93, 194, 295, 94, 195, 296, 95, 196, 297, 96, 197,
    298, 97, 198, 299, 98, 199, 300, 99, 200, 301, 100, 201, 302, 101, 202, 303: prefixedcommand;
    

41, 142, 243:
    {
      gettoken;
      aftertoken = curtok;
    }
    

42, 143, 244:
    {
      gettoken;
      saveforafter(curtok);
    }
    

61, 162, 263: openorclosein;
    

59, 160, 261: issuemessage;
    

58, 159, 260: shiftcase;
    

20, 121, 222: showwhatever;
    

60, 161, 262: doextension;


  }
  goto 60;
  70:
    
mains = eqtb[4751+curchr].hh.rh;
  if (mains == 1000)
    curlist.auxfield.hh.lh = 1000
  else if (mains < 1000)
  {
    if (mains > 0)
      curlist.auxfield.hh.lh = mains;
  }
  else if (curlist.auxfield.hh.lh < 1000)
    curlist.auxfield.hh.lh :=
      1000
  else
    curlist.auxfield.hh.lh = mains;
  mainf = eqtb[3934].hh.rh;
  bchar = fontbchar[mainf];
  falsebchar = fontfalsebchar[mainf];
  if (curlist.modefield > 0)
    if (eqtb[5313].int != curlist.auxfield.hh.rh)
      fixlanguage;
  {
    ligstack = avail;
    if (ligstack == 0)
      ligstack = getavail
    else
    {
      avail = mem[ligstack].hh.rh;
      mem[ligstack].hh.rh = 0;

    }
  }
  mem[ligstack].hh.b0 = mainf;
  curl = curchr+0;
  mem[ligstack].hh.b1 = curl;
  curq = curlist.tailfield;
  if (cancelboundary)
  {
    cancelboundary = false;
    maink = 0;
  }
  else
    maink = bcharlabel[mainf];
  if (maink == 0)
    goto 92;
  curr = curl;
  curl = 256;
  goto 111;
  80:
    
if (curl < 256)
    {
      if (mem[curq].hh.rh > 0)
        if (mem[curlist.tailfield].hh.b1 == hyphenchar[mainf]+0)
          insdisc = true;
      if (ligaturepresent)
      {
        mainp = newligature(mainf, curl, mem[curq].hh.rh);
        if (lfthit)
        {
          mem[mainp].hh.b1 = 2;
          lfthit = false;
        }
        if (rthit)
          if (ligstack == 0)
          {
            mem[mainp].hh.b1 = mem[mainp].hh.b1+1;
            rthit = false;
          }
        mem[curq].hh.rh = mainp;
        curlist.tailfield = mainp;
        ligaturepresent = false;
      }
      if (insdisc)
      {
        insdisc = false;
        if (curlist.modefield > 0)
        {
          mem[curlist.tailfield].hh.rh = newdisc;
          curlist.tailfield = mem[curlist.tailfield].hh.rh;
        }
      }
    }
;
  90:
    
if (ligstack == 0)
      goto 21;
  curq = curlist.tailfield;
  curl = mem[ligstack].hh.b1;
  91:
    if (not (ligstack >= himemmin))
      goto 95;
  92:
    if ((curchr < fontbc[mainf]) or (curchr > fontec[mainf]))
    {
      charwarning(mainf, curchr);
      {
        mem[ligstack].hh.rh = avail;
        avail = ligstack;

      }
      goto 60;
    }
  maini = fontinfo[charbase[mainf]+curl].qqqq;
  if (not (maini.b0 > 0))
  {
    charwarning(mainf, curchr);
    {
      mem[ligstack].hh.rh = avail;
      avail = ligstack;

    }
    goto 60;
  }
  mem[curlist.tailfield].hh.rh = ligstack;
  curlist.tailfield = ligstack
;
  100:
    
getnext;
  if (curcmd == 11)
    goto 101;
  if (curcmd == 12)
    goto 101;
  if (curcmd == 68)
    goto 101;
  xtoken;
  if (curcmd == 11)
    goto 101;
  if (curcmd == 12)
    goto 101;
  if (curcmd == 68)
    goto 101;
  if (curcmd == 16)
  {
    scancharnum;
    curchr = curval;
    goto 101;
  }
  if (curcmd == 65)
    bchar = 256;
  curr = bchar;
  ligstack = 0;
  goto 110;
  101:
    mains = eqtb[4751+curchr].hh.rh;
  if (mains == 1000)
    curlist.auxfield.hh.lh = 1000
  else if (mains < 1000)
  {
    if (mains > 0)
      curlist.auxfield.hh.lh = mains;
  }
  else if (curlist.auxfield.hh.lh < 1000)
    curlist.auxfield.hh.lh :=
      1000
  else
    curlist.auxfield.hh.lh = mains;
  {
    ligstack = avail;
    if (ligstack == 0)
      ligstack = getavail
    else
    {
      avail = mem[ligstack].hh.rh;
      mem[ligstack].hh.rh = 0;

    }
  }
  mem[ligstack].hh.b0 = mainf;
  curr = curchr+0;
  mem[ligstack].hh.b1 = curr;
  if (curr == falsebchar)
    curr = 256
;
  110:
    
if (((maini.b2-0) mod 4) != 1)
      goto 80;
  if (curr == 256)
    goto 80;
  maink = ligkernbase[mainf]+maini.b3;
  mainj = fontinfo[maink].qqqq;
  if (mainj.b0 <= 128)
    goto 112;
  maink = ligkernbase[mainf]+256 * mainj.b2+mainj.b3+32768-256 * (128);
  111:
    mainj = fontinfo[maink].qqqq;
  112:
    if (mainj.b1 == curr)
      if (mainj.b0 <= 128)

      {
        if (mainj.b2 >= 128)
        {
          if (curl < 256)
          {
            if (mem[curq].hh.rh > 0)
              if (mem[curlist.tailfield].hh.b1 == hyphenchar[mainf]+0)
                insdisc = true;
            if (ligaturepresent)
            {
              mainp = newligature(mainf, curl, mem[curq].hh.rh);
              if (lfthit)
              {
                mem[mainp].hh.b1 = 2;
                lfthit = false;
              }
              if (rthit)
                if (ligstack == 0)
                {
                  mem[mainp].hh.b1 = mem[mainp].hh.b1+1;
                  rthit = false;
                }
              mem[curq].hh.rh = mainp;
              curlist.tailfield = mainp;
              ligaturepresent = false;
            }
            if (insdisc)
            {
              insdisc = false;
              if (curlist.modefield > 0)
              {
                mem[curlist.tailfield].hh.rh = newdisc;
                curlist.tailfield = mem[curlist.tailfield].hh.rh;
              }
            }
          }
          {
            mem[curlist.tailfield].hh.rh = newkern(fontinfo[kernbase[mainf]+256 * mainj.b2+mainj.b3].int);
            curlist.tailfield = mem[curlist.tailfield].hh.rh;
          }
          goto 90;
        }
        if (curl == 256)
          lfthit = true
        else if (ligstack == 0)
          rthit = true;
        {
          if (interrupt != 0)
            pauseforinstructions;
        }
        case mainj.b2 of
          1, 5:
          {
            curl = mainj.b3;
            maini = fontinfo[charbase[mainf]+curl].qqqq;
            ligaturepresent = true;
          }
          2, 6:
          {
            curr = mainj.b3;
            if (ligstack == 0)
            {
              ligstack = newligitem(curr);
              bchar = 256;
            }
            else if ((ligstack >= himemmin))
            {
              mainp = ligstack;
              ligstack = newligitem(curr);
              mem[ligstack+1].hh.rh = mainp;
            }
            else
              mem[ligstack].hh.b1 = curr;
          }
          3:
          {
            curr = mainj.b3;
            mainp = ligstack;
            ligstack = newligitem(curr);
            mem[ligstack].hh.rh = mainp;
          }
          7, 11:
          {
            if (curl < 256)
            {
              if (mem[curq].hh.rh > 0)
                if (mem[curlist.tailfield].hh.b1 == hyphenchar[mainf]+0)
                  insdisc = true;
              if (ligaturepresent)
              {
                mainp = newligature(mainf, curl, mem[curq].hh.rh);
                if (lfthit)
                {
                  mem[mainp].hh.b1 = 2;
                  lfthit = false;
                }
                if (false)
                  if (ligstack == 0)
                  {
                    mem[mainp].hh.b1 = mem[mainp].hh.b1+1;
                    rthit = false;
                  }
                mem[curq].hh.rh = mainp;
                curlist.tailfield = mainp;
                ligaturepresent = false;
              }
              if (insdisc)
              {
                insdisc = false;
                if (curlist.modefield > 0)
                {
                  mem[curlist.tailfield].hh.rh = newdisc;
                  curlist.tailfield = mem[curlist.tailfield].hh.rh;
                }
              }
            }
            curq = curlist.tailfield;
            curl = mainj.b3;
            maini = fontinfo[charbase[mainf]+curl].qqqq;
            ligaturepresent = true;
          }
          others:
          {
            curl = mainj.b3;
            ligaturepresent = true;
            if (ligstack == 0)
              goto 80
            else
              goto 91;
          }
        }
        if (mainj.b2 > 4)
          if (mainj.b2 != 7)
            goto 80;
        if (curl < 256)
          goto 110;
        maink = bcharlabel[mainf];
        goto 111;
      }
;
  if (mainj.b0 == 0)
    maink = maink+1
  else
  {
    if (mainj.b0 >= 128)
      goto80;
    maink = maink+mainj.b0+1;
  }
  goto 111
;
  95:
    
mainp = mem[ligstack+1].hh.rh;
  if (mainp > 0)
  {
    mem[curlist.tailfield].hh.rh = mainp;
    curlist.tailfield = mem[curlist.tailfield].hh.rh;
  }
  tempptr = ligstack;
  ligstack = mem[tempptr].hh.rh;
  freenode(tempptr, 2);
  maini = fontinfo[charbase[mainf]+curl].qqqq;
  ligaturepresent = true;
  if (ligstack == 0)
    if (mainp > 0)
      goto 100
    else
      curr = bchar
  else
    curr :=
      mem[ligstack].hh.b1;
  goto 110

;
  120:
    
if (eqtb[2894].hh.rh == 0)
    {

      {
        mainp = fontglue[eqtb[3934].hh.rh];
        if (mainp == 0)
        {
          mainp = newspec(0);
          maink = parambase[eqtb[3934].hh.rh]+2;
          mem[mainp+1].int = fontinfo[maink].int;
          mem[mainp+2].int = fontinfo[maink+1].int;
          mem[mainp+3].int = fontinfo[maink+2].int;
          fontglue[eqtb[3934].hh.rh] = mainp;
        }
      }
;
      tempptr = newglue(mainp);
    }
    else
      tempptr = newparamglue(12);
  mem[curlist.tailfield].hh.rh = tempptr;
  curlist.tailfield = tempptr;
  goto 60
;
  10: ;
}
