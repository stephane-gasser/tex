#include "makeop.h"
scaled makeop(halfword q)
var
  delta: scaled;
  p, v, x, y, z: halfword;
  c: quarterword;
  i: fourquarters;
  shiftup, shiftdown: scaled;
begin
  if (mem[q].hh.b1 = 0) and (curstyle < 2) then
    mem[q].hh.b1 := 1;
  if mem[q + 1].hh.rh = 1 then
  begin
    fetch(q + 1);
    if (curstyle < 2) and (((curi.b2 - 0) mod 4) = 2) then
    begin
      c := curi.b3;
      i := fontinfo[charbase[curf] + c].qqqq;
      if (i.b0 > 0) then
      begin
        curc := c;
        curi := i;
        mem[q + 1].hh.b1 := c;
      end;
    end;
    delta := fontinfo[italicbase[curf] + (curi.b2 - 0) div 4].int;
    x := cleanbox(q + 1, curstyle);
    if (mem[q + 3].hh.rh <> 0) and (mem[q].hh.b1 <> 1) then
      mem[x + 1].int := mem[x + 1].int - delta;
    mem[x + 4].int := half(mem[x + 3].int - mem[x + 2].int) - fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int;
    mem[q + 1].hh.rh := 2;
    mem[q + 1].hh.lh := x;
  end
  else
    delta := 0;
  if mem[q].hh.b1 = 1 then{750:}

  begin
    x := cleanbox(q + 2, 2 * (curstyle div 4) + 4 + (curstyle mod 2));
    y := cleanbox(q + 1, curstyle);
    z := cleanbox(q + 3, 2 * (curstyle div 4) + 5);
    v := newnullbox;
    mem[v].hh.b0 := 1;
    mem[v + 1].int := mem[y + 1].int;
    if mem[x + 1].int > mem[v + 1].int then
      mem[v + 1].int := mem[x + 1].int;
    if mem[z + 1].int > mem[v + 1].int then
      mem[v + 1].int := mem[z + 1].int;
    x := rebox(x, mem[v + 1].int);
    y := rebox(y, mem[v + 1].int);
    z := rebox(z, mem[v + 1].int);
    mem[x + 4].int := half(delta);
    mem[z + 4].int := -mem[x + 4].int;
    mem[v + 3].int := mem[y + 3].int;
    mem[v + 2].int := mem[y + 2].int;
    {751:}
if mem[q + 2].hh.rh = 0 then
    begin
      freenode(x, 7);
      mem[v + 5].hh.rh := y;
    end
    else
    begin
      shiftup := fontinfo[11 + parambase[eqtb[3938 + cursize].hh.rh]].int - mem[x + 2].int;
      if shiftup < fontinfo[9 + parambase[eqtb[3938 + cursize].hh.rh]].int then
        shiftup := fontinfo[9 + parambase[eqtb[3938 + cursize].hh.rh]].int;
      p := newkern(shiftup);
      mem[p].hh.rh := y;
      mem[x].hh.rh := p;
      p := newkern(fontinfo[13 + parambase[eqtb[3938 + cursize].hh.rh]].int);
      mem[p].hh.rh := x;
      mem[v + 5].hh.rh := p;
      mem[v + 3].int := mem[v + 3].int + fontinfo[13 + parambase[eqtb[3938 + cursize].hh.rh]].int + mem[x + 3].int + mem[x + 2].int + shiftup;
    end;
    if mem[q + 3].hh.rh = 0 then
      freenode(z, 7)
    else
    begin
      shiftdown := fontinfo[12 + parambase[eqtb[3938 + cursize].hh.rh]].int - mem[z + 3].int;
      if shiftdown < fontinfo[10 + parambase[eqtb[3938 + cursize].hh.rh]].int then
        shiftdown := fontinfo[10 + parambase[eqtb[3938 + cursize].hh.rh]].int;
      p := newkern(shiftdown);
      mem[y].hh.rh := p;
      mem[p].hh.rh := z;
      p := newkern(fontinfo[13 + parambase[eqtb[3938 + cursize].hh.rh]].int);
      mem[z].hh.rh := p;
      mem[v + 2].int := mem[v + 2].int + fontinfo[13 + parambase[eqtb[3938 + cursize].hh.rh]].int + mem[z + 3].int + mem[z + 2].int + shiftdown;
    end{:751}
;
    mem[q + 1].int := v;
  end{:750}
;
  makeop := delta;
end;
