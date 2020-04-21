procedure printwritewhatsit(s: strnumber; p: halfword);
begin
  printesc(s);
  if mem[p + 1].hh.lh < 16 then
    printint(mem[p + 1].hh.lh)
  else if mem[p + 1].hh.lh = 16 then
    printchar(42)
  else
    printchar(45);
end;
