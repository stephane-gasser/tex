procedure eqdestroy(w: memoryword);
var
  q: halfword;
begin
  case w.hh.b0 of
    111, 112, 113, 114: deletetokenref(w.hh.rh);
    117: deleteglueref(w.hh.rh);
    118:
    begin
      q := w.hh.rh;
      if q <> 0 then
        freenode(q, mem[q].hh.lh + mem[q].hh.lh + 1);
    end;
    119: flushnodelist(w.hh.rh);
    others: end;
end;

