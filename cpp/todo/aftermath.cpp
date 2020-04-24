#include "aftermath.h"
void aftermath(void)
var
  l: boolean;
  danger: boolean;
  m: integer;
  p: halfword;
  a: halfword;
  {1198:}
b: halfword;
  w: scaled;
  z: scaled;
  e: scaled;
  q: scaled;
  d: scaled;
  s: scaled;
  g1, g2: smallnumber;
  r: halfword;
  t: halfword;{:1198}

begin
  danger := false;
  {1195:}
if (fontparams[eqtb[3937].hh.rh] < 22) or (fontparams[eqtb[3953].hh.rh] < 22) or (fontparams[eqtb[3969].hh.rh] < 22) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1157);
    end;
    begin
      helpptr := 3;
      helpline[2] := 1158;
      helpline[1] := 1159;
      helpline[0] := 1160;
    end;
    error;
    flushmath;
    danger := true;
  end
  else if (fontparams[eqtb[3938].hh.rh] < 13) or (fontparams[eqtb[3954].hh.rh] < 13) or (fontparams[eqtb[3970].hh.rh] < 13) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1161);
    end;
    begin
      helpptr := 3;
      helpline[2] := 1162;
      helpline[1] := 1163;
      helpline[0] := 1164;
    end;
    error;
    flushmath;
    danger := true;
  end{:1195}
;
  m := curlist.modefield;
  l := false;
  p := finmlist(0);
  if curlist.modefield = -m then
  begin{1197:}

    begin
      getxtoken;
      if curcmd <> 3 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1165);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1166;
          helpline[0] := 1167;
        end;
        backerror;
      end;
    end{:1197}
;
    curmlist := p;
    curstyle := 2;
    mlistpenalties := false;
    mlisttohlist;
    a := hpack(mem[29997].hh.rh, 0, 1);
    unsave;
    saveptr := saveptr - 1;
    if savestack[saveptr + 0].int = 1 then
      l := true;
    danger := false;
    {1195:}
if (fontparams[eqtb[3937].hh.rh] < 22) or (fontparams[eqtb[3953].hh.rh] < 22) or (fontparams[eqtb[3969].hh.rh] < 22) then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1157);
      end;
      begin
        helpptr := 3;
        helpline[2] := 1158;
        helpline[1] := 1159;
        helpline[0] := 1160;
      end;
      error;
      flushmath;
      danger := true;
    end
    else if (fontparams[eqtb[3938].hh.rh] < 13) or (fontparams[eqtb[3954].hh.rh] < 13) or (fontparams[eqtb[3970].hh.rh] < 13) then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1161);
      end;
      begin
        helpptr := 3;
        helpline[2] := 1162;
        helpline[1] := 1163;
        helpline[0] := 1164;
      end;
      error;
      flushmath;
      danger := true;
    end{:1195}
;
    m := curlist.modefield;
    p := finmlist(0);
  end
  else
    a := 0;
  if m < 0 then{1196:}

  begin
    begin
      mem[curlist.tailfield].hh.rh := newmath(eqtb[5831].int, 0);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    curmlist := p;
    curstyle := 2;
    mlistpenalties := (curlist.modefield > 0);
    mlisttohlist;
    mem[curlist.tailfield].hh.rh := mem[29997].hh.rh;
    while mem[curlist.tailfield].hh.rh <> 0 do
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    begin
      mem[curlist.tailfield].hh.rh := newmath(eqtb[5831].int, 1);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    curlist.auxfield.hh.lh := 1000;
    unsave;
  end{:1196}

  else
  begin
    if a = 0 then{1197:}

    begin
      getxtoken;
      if curcmd <> 3 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1165);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1166;
          helpline[0] := 1167;
        end;
        backerror;
      end;
    end{:1197}
;
    {1199:}
curmlist := p;
    curstyle := 0;
    mlistpenalties := false;
    mlisttohlist;
    p := mem[29997].hh.rh;
    adjusttail := 29995;
    b := hpack(p, 0, 1);
    p := mem[b + 5].hh.rh;
    t := adjusttail;
    adjusttail := 0;
    w := mem[b + 1].int;
    z := eqtb[5844].int;
    s := eqtb[5845].int;
    if (a = 0) or danger then
    begin
      e := 0;
      q := 0;
    end
    else
    begin
      e := mem[a + 1].int;
      q := e + fontinfo[6 + parambase[eqtb[3937].hh.rh]].int;
    end;
    if w + q > z then{1201:}

    begin
      if (e <> 0) and ((w - totalshrink[0] + q <= z) or (totalshrink[1] <> 0) or (totalshrink[2] <> 0) or (totalshrink[3] <> 0)) then
      begin
        freenode(b, 7);
        b := hpack(p, z - q, 0);
      end
      else
      begin
        e := 0;
        if w > z then
        begin
          freenode(b, 7);
          b := hpack(p, z, 0);
        end;
      end;
      w := mem[b + 1].int;
    end{:1201}
;
    {1202:}
d := half(z - w);
    if (e > 0) and (d < 2 * e) then
    begin
      d := half(z - w - e);
      if p <> 0 then
        if not (p >= himemmin) then
          if mem[p].hh.b0 = 10 then
            d := 0;
    end{:1202}
;
    {1203:}
begin
      mem[curlist.tailfield].hh.rh := newpenalty(eqtb[5274].int);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    if (d + s <= eqtb[5843].int) or l then
    begin
      g1 := 3;
      g2 := 4;
    end
    else
    begin
      g1 := 5;
      g2 := 6;
    end;
    if l and (e = 0) then
    begin
      mem[a + 4].int := s;
      appendtovlist(a);
      begin
        mem[curlist.tailfield].hh.rh := newpenalty(10000);
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
    end
    else
    begin
      mem[curlist.tailfield].hh.rh := newparamglue(g1);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end{:1203}
;
    {1204:}
if e <> 0 then
    begin
      r := newkern(z - w - e - d);
      if l then
      begin
        mem[a].hh.rh := r;
        mem[r].hh.rh := b;
        b := a;
        d := 0;
      end
      else
      begin
        mem[b].hh.rh := r;
        mem[r].hh.rh := a;
      end;
      b := hpack(b, 0, 1);
    end;
    mem[b + 4].int := s + d;
    appendtovlist(b){:1204}
;
    {1205:}
if (a <> 0) and (e = 0) and not l then
    begin
      begin
        mem[curlist.tailfield].hh.rh := newpenalty(10000);
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      mem[a + 4].int := s + z - mem[a + 1].int;
      appendtovlist(a);
      g2 := 0;
    end;
    if t <> 29995 then
    begin
      mem[curlist.tailfield].hh.rh := mem[29995].hh.rh;
      curlist.tailfield := t;
    end;
    begin
      mem[curlist.tailfield].hh.rh := newpenalty(eqtb[5275].int);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    if g2 > 0 then
    begin
      mem[curlist.tailfield].hh.rh := newparamglue(g2);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end{:1205}
;
    resumeafterdisplay{:1199}
;
  end;
end;
