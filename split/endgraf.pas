procedure endgraf;
begin
  if curlist.modefield = 102 then
  begin
    if curlist.headfield = curlist.tailfield then
      popnest
    else
      linebreak(eqtb[5269].int);
    normalparagraph;
    errorcount := 0;
  end;
end;
