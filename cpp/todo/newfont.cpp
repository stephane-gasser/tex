#include "newfont.h"
void newfont(smallnumber a)
label
  50;
var
  u: halfword;
  s: scaled;
  f: internalfontnumber;
  t: strnumber;
  oldsetting: 0..21;
  flushablestring: strnumber;
begin
  if jobname = 0 then
    openlogfile;
  getrtoken;
  u := curcs;
  if u >= 514 then
    t := hash[u].rh
  else if u >= 257 then
    if u = 513 then
      t := 1218
    else
      t := u - 257
  else
  begin
    oldsetting := selector;
    selector := 21;
    print(1218);
    print(u - 1);
    selector := oldsetting;
    begin
      if poolptr + 1 > poolsize then
        overflow(257, poolsize - initpoolptr);
    end;
    t := makestring;
  end;
  if (a >= 4) then
    geqdefine(u, 87, 0)
  else
    eqdefine(u, 87, 0);
  scanoptionalequals;
  scanfilename;
  {1258:}
nameinprogress := true;
  if scankeyword(1219) then{1259:}

  begin
    scandimen(false, false, false);
    s := curval;
    if (s <= 0) or (s >= 134217728) then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1221);
      end;
      printscaled(s);
      print(1222);
      begin
        helpptr := 2;
        helpline[1] := 1223;
        helpline[0] := 1224;
      end;
      error;
      s := 10 * 65536;
    end;
  end{:1259}

  else if scankeyword(1220) then
  begin
    scanint;
    s := -curval;
    if (curval <= 0) or (curval > 32768) then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(552);
      end;
      begin
        helpptr := 1;
        helpline[0] := 553;
      end;
      interror(curval);
      s := -1000;
    end;
  end
  else
    s := -1000;
  nameinprogress := false{:1258}
;
  {1260:}
flushablestring := strptr - 1;
  for f := 1 to fontptr do
    if streqstr(fontname[f], curname) and streqstr(fontarea[f], curarea) then
    begin
      if curname = flushablestring then
      begin
        begin
          strptr := strptr - 1;
          poolptr := strstart[strptr];
        end;
        curname := fontname[f];
      end;
      if s > 0 then
      begin
        if s = fontsize[f] then
          goto 50;
      end
      else if fontsize[f] = xnoverd(fontdsize[f], -s, 1000) then
        goto 50;
    end{:1260}
;
  f := readfontinfo(u, curname, curarea, s);
  50:
    eqtb[u].hh.rh := f;
  eqtb[2624 + f] := eqtb[u];
  hash[2624 + f].rh := t;
end;
