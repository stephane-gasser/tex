#include "makefraction.h"
void makefraction(halfword q)
var
  p, v, x, y, z: halfword;
  delta, delta1, delta2, shiftup, shiftdown, clr: scaled;
begin
  if mem[q + 1].int = 1073741824 then
    mem[q + 1].int := fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int;
  {744:}
x := cleanbox(q + 2, curstyle + 2 - 2 * (curstyle div 6));
  z := cleanbox(q + 3, 2 * (curstyle div 2) + 3 - 2 * (curstyle div 6));
  if mem[x + 1].int < mem[z + 1].int then
    x := rebox(x, mem[z + 1].int)
  else
    z := rebox(z, mem[x + 1].int);
  if curstyle < 2 then
  begin
    shiftup := fontinfo[8 + parambase[eqtb[3937 + cursize].hh.rh]].int;
    shiftdown := fontinfo[11 + parambase[eqtb[3937 + cursize].hh.rh]].int;
  end
  else
  begin
    shiftdown := fontinfo[12 + parambase[eqtb[3937 + cursize].hh.rh]].int;
    if mem[q + 1].int <> 0 then
      shiftup := fontinfo[9 + parambase[eqtb[3937 + cursize].hh.rh]].int
    else
      shiftup := fontinfo[10 + parambase[eqtb[3937 + cursize].hh.rh]].int;
  end{:744}
;
  if mem[q + 1].int = 0 then{745:}

  begin
    if curstyle < 2 then
      clr := 7 * fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int
    else
      clr := 3 * fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int;
    delta := half(clr - ((shiftup - mem[x + 2].int) - (mem[z + 3].int - shiftdown)));
    if delta > 0 then
    begin
      shiftup := shiftup + delta;
      shiftdown := shiftdown + delta;
    end;
  end{:745}

  else{746:}

  begin
    if curstyle < 2 then
      clr := 3 * mem[q + 1].int
    else
      clr := mem[q + 1].int;
    delta := half(mem[q + 1].int);
    delta1 := clr - ((shiftup - mem[x + 2].int) - (fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int + delta));
    delta2 := clr - ((fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int - delta) - (mem[z + 3].int - shiftdown));
    if delta1 > 0 then
      shiftup := shiftup + delta1;
    if delta2 > 0 then
      shiftdown := shiftdown + delta2;
  end{:746}
;
  {747:}
v := newnullbox;
  mem[v].hh.b0 := 1;
  mem[v + 3].int := shiftup + mem[x + 3].int;
  mem[v + 2].int := mem[z + 2].int + shiftdown;
  mem[v + 1].int := mem[x + 1].int;
  if mem[q + 1].int = 0 then
  begin
    p := newkern((shiftup - mem[x + 2].int) - (mem[z + 3].int - shiftdown));
    mem[p].hh.rh := z;
  end
  else
  begin
    y := fractionrule(mem[q + 1].int);
    p := newkern((fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int - delta) - (mem[z + 3].int - shiftdown));
    mem[y].hh.rh := p;
    mem[p].hh.rh := z;
    p := newkern((shiftup - mem[x + 2].int) - (fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int + delta));
    mem[p].hh.rh := y;
  end;
  mem[x].hh.rh := p;
  mem[v + 5].hh.rh := x{:747}
;
  {748:}
if curstyle < 2 then
    delta := fontinfo[20 + parambase[eqtb[3937 + cursize].hh.rh]].int
  else
    delta := fontinfo[21 + parambase[eqtb[3937 + cursize].hh.rh]].int;
  x := vardelimiter(q + 4, cursize, delta);
  mem[x].hh.rh := v;
  z := vardelimiter(q + 5, cursize, delta);
  mem[v].hh.rh := z;
  mem[q + 1].int := hpack(x, 0, 1){:748}
;
end;
