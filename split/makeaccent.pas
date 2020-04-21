procedure makeaccent;
var
  s, t: real;
  p, q, r: halfword;
  f: internalfontnumber;
  a, h, x, w, delta: scaled;
  i: fourquarters;
begin
  scancharnum;
  f := eqtb[3934].hh.rh;
  p := newcharacter(f, curval);
  if p <> 0 then
  begin
    x := fontinfo[5 + parambase[f]].int;
    s := fontinfo[1 + parambase[f]].int / 65536.0;
    a := fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[p].hh.b1].qqqq.b0].int;
    doassignments;
    {1124:}
q := 0;
    f := eqtb[3934].hh.rh;
    if (curcmd = 11) or (curcmd = 12) or (curcmd = 68) then
      q := newcharacter(f, curchr)
    else if curcmd = 16 then
    begin
      scancharnum;
      q := newcharacter(f, curval);
    end
    else
      backinput{:1124}
;
    if q <> 0 then{1125:}

    begin
      t := fontinfo[1 + parambase[f]].int / 65536.0;
      i := fontinfo[charbase[f] + mem[q].hh.b1].qqqq;
      w := fontinfo[widthbase[f] + i.b0].int;
      h := fontinfo[heightbase[f] + (i.b1 - 0) div 16].int;
      if h <> x then
      begin
        p := hpack(p, 0, 1);
        mem[p + 4].int := x - h;
      end;
      delta := round((w - a) / 2.0 + h * t - x * s);
      r := newkern(delta);
      mem[r].hh.b1 := 2;
      mem[curlist.tailfield].hh.rh := r;
      mem[r].hh.rh := p;
      curlist.tailfield := newkern(-a - delta);
      mem[curlist.tailfield].hh.b1 := 2;
      mem[p].hh.rh := curlist.tailfield;
      p := q;
    end{:1125}
;
    mem[curlist.tailfield].hh.rh := p;
    curlist.tailfield := p;
    curlist.auxfield.hh.lh := 1000;
  end;
end;
