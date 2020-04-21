procedure printspec(p: integer; s: strnumber);
begin
  if (p < memmin) or (p >= lomemmax) then
    printchar(42)
  else
  begin
    printscaled(mem[p + 1].int);
    if s <> 0 then
      print(s);
    if mem[p + 2].int <> 0 then
    begin
      print(312);
      printglue(mem[p + 2].int, mem[p].hh.b0, s);
    end;
    if mem[p + 3].int <> 0 then
    begin
      print(313);
      printglue(mem[p + 3].int, mem[p].hh.b1, s);
    end;
  end;
end;
