procedure deleteglueref(p: halfword);
begin
  if mem[p].hh.rh = 0 then
    freenode(p, 4)
  else
    mem[p].hh.rh := mem[p].hh.rh - 1;
end;
