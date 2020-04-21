procedure deletetokenref(p: halfword);
begin
  if mem[p].hh.lh = 0 then
    flushlist(p)
  else
    mem[p].hh.lh := mem[p].hh.lh - 1;
end;
