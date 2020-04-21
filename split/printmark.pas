procedure printmark(p: integer);
begin
  printchar(123);
  if (p < himemmin) or (p > memend) then
    printesc(309)
  else
    showtokenlist(mem[p].hh.rh, 0, maxprintline - 10);
  printchar(125);
end;
