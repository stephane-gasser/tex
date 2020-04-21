procedure eqdefine(p: halfword; t: quarterword; e: halfword);
begin
  if eqtb[p].hh.b1 = curlevel then
    eqdestroy(eqtb[p])
  else if curlevel > 1 then
    eqsave(p, eqtb[p].hh.b1);
  eqtb[p].hh.b1 := curlevel;
  eqtb[p].hh.b0 := t;
  eqtb[p].hh.rh := e;
end;
