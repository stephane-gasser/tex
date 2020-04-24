#include "appendtovlist.h"
void appendtovlist(halfword b)
var
  d: scaled;
  p: halfword;
begin
  if curlist.auxfield.int > -65536000 then
  begin
    d := mem[eqtb[2883].hh.rh + 1].int - curlist.auxfield.int - mem[b + 3].int;
    if d < eqtb[5832].int then
      p := newparamglue(0)
    else
    begin
      p := newskipparam(1);
      mem[tempptr + 1].int := d;
    end;
    mem[curlist.tailfield].hh.rh := p;
    curlist.tailfield := p;
  end;
  mem[curlist.tailfield].hh.rh := b;
  curlist.tailfield := b;
  curlist.auxfield.int := mem[b + 2].int;
end;
