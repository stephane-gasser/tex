procedure printmeaning;
begin
  printcmdchr(curcmd, curchr);
  if curcmd >= 111 then
  begin
    printchar(58);
    println;
    tokenshow(curchr);
  end
  else if curcmd = 110 then
  begin
    printchar(58);
    println;
    tokenshow(curmark[curchr]);
  end;
end;
