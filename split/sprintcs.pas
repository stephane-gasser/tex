procedure sprintcs(p: halfword);
begin
  if p < 514 then
    if p < 257 then
      print(p - 1)
    else if p < 513 then
      printesc(
        p - 257)
    else
    begin
      printesc(504);
      printesc(505);
    end
  else
    printesc(hash[p].rh);
end;
