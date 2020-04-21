procedure geqdefine(p: halfword; t: quarterword; e: halfword);
begin
  eqdestroy(eqtb[p]);
  eqtb[p].hh.b1 := 1;
  eqtb[p].hh.b0 := t;
  eqtb[p].hh.rh := e;
end;
