procedure pushnest;
begin
  if nestptr > maxneststack then
  begin
    maxneststack := nestptr;
    if nestptr = nestsize then
      overflow(362, nestsize);
  end;
  nest[nestptr] := curlist;
  nestptr := nestptr + 1;
  curlist.headfield := getavail;
  curlist.tailfield := curlist.headfield;
  curlist.pgfield := 0;
  curlist.mlfield := line;
end;
