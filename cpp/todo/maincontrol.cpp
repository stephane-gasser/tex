#include "maincontrol.h"
void maincontrol(void)
label
  60, 21, 70, 80, 90, 91, 92, 95, 100, 101, 110, 111, 112, 120, 10;
var
  t: integer;
begin
  if eqtb[3419].hh.rh <> 0 then
    begintokenlist(eqtb[3419].hh.rh, 12);
  60:
    getxtoken;
  21:
    {1031:}
if interrupt <> 0 then
      if OKtointerrupt then
      begin
        backinput;
        begin
          if interrupt <> 0 then
            pauseforinstructions;
        end;
        goto 60;
      end;
  {if panicking then checkmem(false);}

  if eqtb[5299].int > 0 then
    showcurcmdchr{:1031}
;
  case abs(curlist.modefield) + curcmd of
    113, 114, 170: goto 70;
    118:
    begin
      scancharnum;
      curchr := curval;
      goto 70;
    end;
    167:
    begin
      getxtoken;
      if (curcmd = 11) or (curcmd = 12) or (curcmd = 68) or (curcmd = 16) then
        cancelboundary := true;
      goto 21;
    end;
    112: if curlist.auxfield.hh.lh = 1000 then
        goto 120
      else
        appspace;
    166, 267: goto 120;
    {1045:}
1, 102, 203, 11, 213, 268: ;
    40, 141, 242:
    begin
      {406:}
repeat
        getxtoken;
      until curcmd <> 10{:406}
;
      goto 21;
    end;
    15: if itsallover then
        goto 10;
    {1048:}
23, 123, 224, 71, 172, 273,{:1048}
{1098:}
39,{:1098}
{1111:}
45,{:1111}

    {1144:}
49, 150,{:1144}
7, 108, 209: reportillegalcase;
    {1046:}
8, 109, 9, 110, 18, 119, 70, 171, 51, 152, 16, 117, 50, 151, 53, 154, 67, 168, 54,
    155, 55, 156, 57, 158, 56, 157, 31, 132, 52, 153, 29, 130, 47, 148, 212, 216, 217, 230, 227, 236, 239{:1046}
: insertdollarsign;
    {1056:}
37, 137, 238:
    begin
      begin
        mem[curlist.tailfield].hh.rh := scanrulespec;
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      if abs(curlist.modefield) = 1 then
        curlist.auxfield.int := -65536000
      else if abs(curlist.modefield) = 102 then
        curlist.auxfield.hh.lh := 1000;
    end;
    {:1056}
{1057:}
28, 128, 229, 231: appendglue;
    30, 131, 232, 233: appendkern;
    {:1057}
{1063:}
2, 103: newsavelevel(1);
    62, 163, 264: newsavelevel(14);
    63, 164, 265: if curgroup = 14 then
        unsave
      else
        offsave;
    {:1063}
{1067:}
3, 104, 205: handlerightbrace;
    {:1067}
{1073:}
22, 124, 225:
    begin
      t := curchr;
      scandimen(false, false, false);
      if t = 0 then
        scanbox(curval)
      else
        scanbox(-curval);
    end;
    32, 133, 234: scanbox(1073742237 + curchr);
    21, 122, 223: beginbox(0);
    {:1073}
{1090:}
44: newgraf(curchr > 0);
    12, 13, 17, 69, 4, 24, 36, 46, 48, 27, 34, 65, 66:
    begin
      backinput;
      newgraf(true);
    end;
    {:1090}
{1092:}
145, 246: indentinhmode;
    {:1092}
{1094:}
14:
    begin
      normalparagraph;
      if curlist.modefield > 0 then
        buildpage;
    end;
    115:
    begin
      if alignstate < 0 then
        offsave;
      endgraf;
      if curlist.modefield = 1 then
        buildpage;
    end;
    116, 129, 138, 126, 134: headforvmode;
    {:1094}
{1097:}
38, 139, 240, 140, 241: begininsertoradjust;
    19, 120, 221: makemark;
    {:1097}
{1102:}
43, 144, 245: appendpenalty;
    {:1102}
{1104:}
26, 127, 228: deletelast;
    {:1104}
{1109:}
25, 125, 226: unpackage;
    {:1109}
{1112:}
146: appenditaliccorrection;
    247:
    begin
      mem[curlist.tailfield].hh.rh := newkern(0);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    {:1112}
{1116:}
149, 250: appenddiscretionary;
    {:1116}
{1122:}
147: makeaccent;
    {:1122}
{1126:}
6, 107, 208, 5, 106, 207: alignerror;
    35, 136, 237: noalignerror;
    64, 165, 266: omiterror;
    {:1126}
{1130:}
33, 135: initalign;
    235: if privileged then
        if curgroup = 15 then
          initalign
        else
          offsave;
    10, 111: doendv;
    {:1130}
{1134:}
68, 169, 270: cserror;
    {:1134}
{1137:}
105: initmath;
    {:1137}
{1140:}
251: if privileged then
        if curgroup = 15 then
          starteqno
        else
          offsave;
    {:1140}
{1150:}
204:
    begin
      begin
        mem[curlist.tailfield].hh.rh := newnoad;
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      backinput;
      scanmath(curlist.tailfield + 1);
    end;
    {:1150}
{1154:}
214, 215, 271: setmathchar(eqtb[5007 + curchr].hh.rh - 0);
    219:
    begin
      scancharnum;
      curchr := curval;
      setmathchar(eqtb[5007 + curchr].hh.rh - 0);
    end;
    220:
    begin
      scanfifteenbitint;
      setmathchar(curval);
    end;
    272: setmathchar(curchr);
    218:
    begin
      scantwentysevenbitint;
      setmathchar(curval div 4096);
    end;
    {:1154}
{1158:}
253:
    begin
      begin
        mem[curlist.tailfield].hh.rh := newnoad;
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      mem[curlist.tailfield].hh.b0 := curchr;
      scanmath(curlist.tailfield + 1);
    end;
    254: mathlimitswitch;
    {:1158}
{1162:}
269: mathradical;
    {:1162}
{1164:}
248, 249: mathac;
    {:1164}
{1167:}
259:
    begin
      scanspec(12, false);
      normalparagraph;
      pushnest;
      curlist.modefield := -1;
      curlist.auxfield.int := -65536000;
      if eqtb[3418].hh.rh <> 0 then
        begintokenlist(eqtb[3418].hh.rh, 11);
    end;
    {:1167}
{1171:}
256:
    begin
      mem[curlist.tailfield].hh.rh := newstyle(curchr);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    258:
    begin
      begin
        mem[curlist.tailfield].hh.rh := newglue(0);
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      mem[curlist.tailfield].hh.b1 := 98;
    end;
    257: appendchoices;
    {:1171}
{1175:}
211, 210: subsup;
    {:1175}
{1180:}
255: mathfraction;
    {:1180}
{1190:}
252: mathleftright;
    {:1190}
{1193:}
206: if curgroup = 15 then
        aftermath
      else
        offsave;
    {:1193}
{1210:}
72, 173, 274, 73, 174, 275, 74, 175, 276, 75, 176, 277, 76, 177, 278, 77,
    178, 279, 78, 179, 280, 79, 180, 281, 80, 181, 282, 81, 182, 283, 82, 183, 284, 83, 184,
    285, 84, 185, 286, 85, 186, 287, 86, 187, 288, 87, 188, 289, 88, 189, 290, 89, 190, 291, 90, 191, 292, 91, 192, 293, 92, 193, 294, 93, 194, 295, 94, 195, 296, 95, 196, 297, 96, 197,
    298, 97, 198, 299, 98, 199, 300, 99, 200, 301, 100, 201, 302, 101, 202, 303: prefixedcommand;
    {:1210}
{1268:}
41, 142, 243:
    begin
      gettoken;
      aftertoken := curtok;
    end;
    {:1268}
{1271:}
42, 143, 244:
    begin
      gettoken;
      saveforafter(curtok);
    end;
    {:1271}
{1274:}
61, 162, 263: openorclosein;
    {:1274}
{1276:}
59, 160, 261: issuemessage;
    {:1276}
{1285:}
58, 159, 260: shiftcase;
    {:1285}
{1290:}
20, 121, 222: showwhatever;
    {:1290}
{1347:}
60, 161, 262: doextension;{:1347}
{:1045}

  end;
  goto 60;
  70:
    {1034:}
mains := eqtb[4751 + curchr].hh.rh;
  if mains = 1000 then
    curlist.auxfield.hh.lh := 1000
  else if mains < 1000 then
  begin
    if mains > 0 then
      curlist.auxfield.hh.lh := mains;
  end
  else if curlist.auxfield.hh.lh < 1000 then
    curlist.auxfield.hh.lh :=
      1000
  else
    curlist.auxfield.hh.lh := mains;
  mainf := eqtb[3934].hh.rh;
  bchar := fontbchar[mainf];
  falsebchar := fontfalsebchar[mainf];
  if curlist.modefield > 0 then
    if eqtb[5313].int <> curlist.auxfield.hh.rh then
      fixlanguage;
  begin
    ligstack := avail;
    if ligstack = 0 then
      ligstack := getavail
    else
    begin
      avail := mem[ligstack].hh.rh;
      mem[ligstack].hh.rh := 0;{dynused:=dynused+1;}

    end;
  end;
  mem[ligstack].hh.b0 := mainf;
  curl := curchr + 0;
  mem[ligstack].hh.b1 := curl;
  curq := curlist.tailfield;
  if cancelboundary then
  begin
    cancelboundary := false;
    maink := 0;
  end
  else
    maink := bcharlabel[mainf];
  if maink = 0 then
    goto 92;
  curr := curl;
  curl := 256;
  goto 111;
  80:
    {1035:}
if curl < 256 then
    begin
      if mem[curq].hh.rh > 0 then
        if mem[curlist.tailfield].hh.b1 = hyphenchar[mainf] + 0 then
          insdisc := true;
      if ligaturepresent then
      begin
        mainp := newligature(mainf, curl, mem[curq].hh.rh);
        if lfthit then
        begin
          mem[mainp].hh.b1 := 2;
          lfthit := false;
        end;
        if rthit then
          if ligstack = 0 then
          begin
            mem[mainp].hh.b1 := mem[mainp].hh.b1 + 1;
            rthit := false;
          end;
        mem[curq].hh.rh := mainp;
        curlist.tailfield := mainp;
        ligaturepresent := false;
      end;
      if insdisc then
      begin
        insdisc := false;
        if curlist.modefield > 0 then
        begin
          mem[curlist.tailfield].hh.rh := newdisc;
          curlist.tailfield := mem[curlist.tailfield].hh.rh;
        end;
      end;
    end{:1035}
;
  90:
    {1036:}
if ligstack = 0 then
      goto 21;
  curq := curlist.tailfield;
  curl := mem[ligstack].hh.b1;
  91:
    if not (ligstack >= himemmin) then
      goto 95;
  92:
    if (curchr < fontbc[mainf]) or (curchr > fontec[mainf]) then
    begin
      charwarning(mainf, curchr);
      begin
        mem[ligstack].hh.rh := avail;
        avail := ligstack;{dynused:=dynused-1;}

      end;
      goto 60;
    end;
  maini := fontinfo[charbase[mainf] + curl].qqqq;
  if not (maini.b0 > 0) then
  begin
    charwarning(mainf, curchr);
    begin
      mem[ligstack].hh.rh := avail;
      avail := ligstack;{dynused:=dynused-1;}

    end;
    goto 60;
  end;
  mem[curlist.tailfield].hh.rh := ligstack;
  curlist.tailfield := ligstack{:1036}
;
  100:
    {1038:}
getnext;
  if curcmd = 11 then
    goto 101;
  if curcmd = 12 then
    goto 101;
  if curcmd = 68 then
    goto 101;
  xtoken;
  if curcmd = 11 then
    goto 101;
  if curcmd = 12 then
    goto 101;
  if curcmd = 68 then
    goto 101;
  if curcmd = 16 then
  begin
    scancharnum;
    curchr := curval;
    goto 101;
  end;
  if curcmd = 65 then
    bchar := 256;
  curr := bchar;
  ligstack := 0;
  goto 110;
  101:
    mains := eqtb[4751 + curchr].hh.rh;
  if mains = 1000 then
    curlist.auxfield.hh.lh := 1000
  else if mains < 1000 then
  begin
    if mains > 0 then
      curlist.auxfield.hh.lh := mains;
  end
  else if curlist.auxfield.hh.lh < 1000 then
    curlist.auxfield.hh.lh :=
      1000
  else
    curlist.auxfield.hh.lh := mains;
  begin
    ligstack := avail;
    if ligstack = 0 then
      ligstack := getavail
    else
    begin
      avail := mem[ligstack].hh.rh;
      mem[ligstack].hh.rh := 0;{dynused:=dynused+1;}

    end;
  end;
  mem[ligstack].hh.b0 := mainf;
  curr := curchr + 0;
  mem[ligstack].hh.b1 := curr;
  if curr = falsebchar then
    curr := 256{:1038}
;
  110:
    {1039:}
if ((maini.b2 - 0) mod 4) <> 1 then
      goto 80;
  if curr = 256 then
    goto 80;
  maink := ligkernbase[mainf] + maini.b3;
  mainj := fontinfo[maink].qqqq;
  if mainj.b0 <= 128 then
    goto 112;
  maink := ligkernbase[mainf] + 256 * mainj.b2 + mainj.b3 + 32768 - 256 * (128);
  111:
    mainj := fontinfo[maink].qqqq;
  112:
    if mainj.b1 = curr then
      if mainj.b0 <= 128 then{1040:}

      begin
        if mainj.b2 >= 128 then
        begin
          if curl < 256 then
          begin
            if mem[curq].hh.rh > 0 then
              if mem[curlist.tailfield].hh.b1 = hyphenchar[mainf] + 0 then
                insdisc := true;
            if ligaturepresent then
            begin
              mainp := newligature(mainf, curl, mem[curq].hh.rh);
              if lfthit then
              begin
                mem[mainp].hh.b1 := 2;
                lfthit := false;
              end;
              if rthit then
                if ligstack = 0 then
                begin
                  mem[mainp].hh.b1 := mem[mainp].hh.b1 + 1;
                  rthit := false;
                end;
              mem[curq].hh.rh := mainp;
              curlist.tailfield := mainp;
              ligaturepresent := false;
            end;
            if insdisc then
            begin
              insdisc := false;
              if curlist.modefield > 0 then
              begin
                mem[curlist.tailfield].hh.rh := newdisc;
                curlist.tailfield := mem[curlist.tailfield].hh.rh;
              end;
            end;
          end;
          begin
            mem[curlist.tailfield].hh.rh := newkern(fontinfo[kernbase[mainf] + 256 * mainj.b2 + mainj.b3].int);
            curlist.tailfield := mem[curlist.tailfield].hh.rh;
          end;
          goto 90;
        end;
        if curl = 256 then
          lfthit := true
        else if ligstack = 0 then
          rthit := true;
        begin
          if interrupt <> 0 then
            pauseforinstructions;
        end;
        case mainj.b2 of
          1, 5:
          begin
            curl := mainj.b3;
            maini := fontinfo[charbase[mainf] + curl].qqqq;
            ligaturepresent := true;
          end;
          2, 6:
          begin
            curr := mainj.b3;
            if ligstack = 0 then
            begin
              ligstack := newligitem(curr);
              bchar := 256;
            end
            else if (ligstack >= himemmin) then
            begin
              mainp := ligstack;
              ligstack := newligitem(curr);
              mem[ligstack + 1].hh.rh := mainp;
            end
            else
              mem[ligstack].hh.b1 := curr;
          end;
          3:
          begin
            curr := mainj.b3;
            mainp := ligstack;
            ligstack := newligitem(curr);
            mem[ligstack].hh.rh := mainp;
          end;
          7, 11:
          begin
            if curl < 256 then
            begin
              if mem[curq].hh.rh > 0 then
                if mem[curlist.tailfield].hh.b1 = hyphenchar[mainf] + 0 then
                  insdisc := true;
              if ligaturepresent then
              begin
                mainp := newligature(mainf, curl, mem[curq].hh.rh);
                if lfthit then
                begin
                  mem[mainp].hh.b1 := 2;
                  lfthit := false;
                end;
                if false then
                  if ligstack = 0 then
                  begin
                    mem[mainp].hh.b1 := mem[mainp].hh.b1 + 1;
                    rthit := false;
                  end;
                mem[curq].hh.rh := mainp;
                curlist.tailfield := mainp;
                ligaturepresent := false;
              end;
              if insdisc then
              begin
                insdisc := false;
                if curlist.modefield > 0 then
                begin
                  mem[curlist.tailfield].hh.rh := newdisc;
                  curlist.tailfield := mem[curlist.tailfield].hh.rh;
                end;
              end;
            end;
            curq := curlist.tailfield;
            curl := mainj.b3;
            maini := fontinfo[charbase[mainf] + curl].qqqq;
            ligaturepresent := true;
          end;
          others:
          begin
            curl := mainj.b3;
            ligaturepresent := true;
            if ligstack = 0 then
              goto 80
            else
              goto 91;
          end
        end;
        if mainj.b2 > 4 then
          if mainj.b2 <> 7 then
            goto 80;
        if curl < 256 then
          goto 110;
        maink := bcharlabel[mainf];
        goto 111;
      end{:1040}
;
  if mainj.b0 = 0 then
    maink := maink + 1
  else
  begin
    if mainj.b0 >= 128 then
      goto80;
    maink := maink + mainj.b0 + 1;
  end;
  goto 111{:1039}
;
  95:
    {1037:}
mainp := mem[ligstack + 1].hh.rh;
  if mainp > 0 then
  begin
    mem[curlist.tailfield].hh.rh := mainp;
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  tempptr := ligstack;
  ligstack := mem[tempptr].hh.rh;
  freenode(tempptr, 2);
  maini := fontinfo[charbase[mainf] + curl].qqqq;
  ligaturepresent := true;
  if ligstack = 0 then
    if mainp > 0 then
      goto 100
    else
      curr := bchar
  else
    curr :=
      mem[ligstack].hh.b1;
  goto 110{:1037}
{:1034}
;
  120:
    {1041:}
if eqtb[2894].hh.rh = 0 then
    begin{1042:}

      begin
        mainp := fontglue[eqtb[3934].hh.rh];
        if mainp = 0 then
        begin
          mainp := newspec(0);
          maink := parambase[eqtb[3934].hh.rh] + 2;
          mem[mainp + 1].int := fontinfo[maink].int;
          mem[mainp + 2].int := fontinfo[maink + 1].int;
          mem[mainp + 3].int := fontinfo[maink + 2].int;
          fontglue[eqtb[3934].hh.rh] := mainp;
        end;
      end{:1042}
;
      tempptr := newglue(mainp);
    end
    else
      tempptr := newparamglue(12);
  mem[curlist.tailfield].hh.rh := tempptr;
  curlist.tailfield := tempptr;
  goto 60{:1041}
;
  10: ;
end;
