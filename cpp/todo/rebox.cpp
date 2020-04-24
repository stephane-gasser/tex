#include "rebox.h"
halfword rebox(halfword b, scaled w)
var
  p: halfword;
  f: internalfontnumber;
  v: scaled;
begin
  if (mem[b + 1].int <> w) and (mem[b + 5].hh.rh <> 0) then
  begin
    if mem[b].hh.b0 = 1 then
      b := hpack(b, 0, 1);
    p := mem[b + 5].hh.rh;
    if ((p >= himemmin)) and (mem[p].hh.rh = 0) then
    begin
      f := mem[p].hh.b0;
      v := fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[p].hh.b1].qqqq.b0].int;
      if v <> mem[b + 1].int then
        mem[p].hh.rh := newkern(mem[b + 1].int - v);
    end;
    freenode(b, 7);
    b := newglue(12);
    mem[b].hh.rh := p;
    while mem[p].hh.rh <> 0 do
      p := mem[p].hh.rh;
    mem[p].hh.rh := newglue(12);
    rebox := hpack(b, w, 0);
  end
  else
  begin
    mem[b + 1].int := w;
    rebox := b;
  end;
end;

