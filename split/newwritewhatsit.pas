procedure newwritewhatsit(w: smallnumber);
begin
  newwhatsit(curchr, w);
  if w <> 2 then
    scanfourbitint
  else
  begin
    scanint;
    if curval < 0 then
      curval := 17
    else if curval > 15 then
      curval := 16;
  end;
  mem[curlist.tailfield + 1].hh.lh := curval;
end;
