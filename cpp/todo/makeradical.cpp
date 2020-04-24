#include "makeradical.h"
void makeradical(halfword q)
var
  x, y: halfword;
  delta, clr: scaled;
begin
  x := cleanbox(q + 1, 2 * (curstyle div 2) + 1);
  if curstyle < 2 then
    clr := fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int +
      (abs(fontinfo[5 + parambase[eqtb[3937 + cursize].hh.rh]].int) div 4)
  else
  begin
    clr := fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int;
    clr := clr + (abs(clr) div 4);
  end;
  y := vardelimiter(q + 4, cursize, mem[x + 3].int + mem[x + 2].int + clr + fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int);
  delta := mem[y + 2].int - (mem[x + 3].int + mem[x + 2].int + clr);
  if delta > 0 then
    clr := clr + half(delta);
  mem[y + 4].int := -(mem[x + 3].int + clr);
  mem[y].hh.rh := overbar(x, clr, mem[y + 3].int);
  mem[q + 1].hh.lh := hpack(y, 0, 1);
  mem[q + 1].hh.rh := 2;
end;
