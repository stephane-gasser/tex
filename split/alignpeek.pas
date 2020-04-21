procedure alignpeek;
label
  20;
begin
  20:
    alignstate := 1000000;
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  if curcmd = 34 then
  begin
    scanleftbrace;
    newsavelevel(7);
    if curlist.modefield = -1 then
      normalparagraph;
  end
  else if curcmd = 2 then
    finalign
  else if (curcmd = 5) and (curchr = 258) then
    goto 20
  else
  begin
    initrow;
    initcol;
  end;
end;

