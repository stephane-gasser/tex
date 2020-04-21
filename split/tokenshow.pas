procedure tokenshow(p: halfword);
begin
  if p <> 0 then
    showtokenlist(mem[p].hh.rh, 0, 10000000);
end;
