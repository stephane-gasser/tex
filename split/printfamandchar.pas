procedure printfamandchar(p: halfword);
begin
  printesc(464);
  printint(mem[p].hh.b0);
  printchar(32);
  print(mem[p].hh.b1 - 0);
end;
