#include "prunepagetop.h"
halfword prunepagetop(halfword p)
var
  prevp: halfword;
  q: halfword;
begin
  prevp := 29997;
  mem[29997].hh.rh := p;
  while p <> 0 do
    case mem[p].hh.b0 of
      0, 1, 2:{969:}

      begin
        q := newskipparam(10);
        mem[prevp].hh.rh := q;
        mem[q].hh.rh := p;
        if mem[tempptr + 1].int > mem[p + 3].int then
          mem[tempptr + 1].int := mem[tempptr + 1].int - mem[p + 3].int
        else
          mem[tempptr + 1].int := 0;
        p := 0;
      end{:969}
;
      8, 4, 3:
      begin
        prevp := p;
        p := mem[prevp].hh.rh;
      end;
      10, 11, 12:
      begin
        q := p;
        p := mem[q].hh.rh;
        mem[q].hh.rh := 0;
        mem[prevp].hh.rh := p;
        flushnodelist(q);
      end;
      others: confusion(958)
    end;
  prunepagetop := mem[29997].hh.rh;
end;
