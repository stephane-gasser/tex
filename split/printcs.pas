procedure printcs(p: integer);
begin
  if p < 514 then
    if p >= 257 then
      if p = 513 then
      begin
        printesc(504);
        printesc(505);
        printchar(32);
      end
      else
      begin
        printesc(p - 257);
        if eqtb[3983 + p - 257].hh.rh = 11 then
          printchar(32);
      end
    else if p < 1 then
      printesc(506)
    else
      print(p - 1)
  else if p >= 2881 then
    printesc(506)
  else if (hash[p].rh < 0) or (hash[p].rh >= strptr) then
    printesc(
      507)
  else
  begin
    printesc(hash[p].rh);
    printchar(32);
  end;
end;
