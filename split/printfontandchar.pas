procedure printfontandchar(p: integer);
begin
  if p > memend then
    printesc(309)
  else
  begin
    if (mem[p].hh.b0 < 0) or (mem[p].hh.b0 > fontmax) then
      printchar(42)
    else
      {267:}
printesc(hash[2624 + mem[p].hh.b0].rh){:267}
;
    printchar(32);
    print(mem[p].hh.b1 - 0);
  end;
end;
