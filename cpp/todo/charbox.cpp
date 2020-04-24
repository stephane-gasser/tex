#include "charbox.h"
halfword charbox(internalfontnumber f, quarterword c)
var
  q: fourquarters;
  hd: eightbits;
  b, p: halfword;
begin
  q := fontinfo[charbase[f] + c].qqqq;
  hd := q.b1 - 0;
  b := newnullbox;
  mem[b + 1].int := fontinfo[widthbase[f] + q.b0].int + fontinfo[italicbase[f] + (q.b2 - 0) div 4].int;
  mem[b + 3].int := fontinfo[heightbase[f] + (hd) div 16].int;
  mem[b + 2].int := fontinfo[depthbase[f] + (hd) mod 16].int;
  p := getavail;
  mem[p].hh.b1 := c;
  mem[p].hh.b0 := f;
  mem[b + 5].hh.rh := p;
  charbox := b;
end;
