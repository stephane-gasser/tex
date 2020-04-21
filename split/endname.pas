procedure endname;
begin
  if strptr + 3 > maxstrings then
    overflow(258, maxstrings - initstrptr);
  if areadelimiter = 0 then
    curarea := 338
  else
  begin
    curarea := strptr;
    strstart[strptr + 1] := strstart[strptr] + areadelimiter;
    strptr := strptr + 1;
  end;
  if extdelimiter = 0 then
  begin
    curext := 338;
    curname := makestring;
  end
  else
  begin
    curname := strptr;
    strstart[strptr + 1] := strstart[strptr] + extdelimiter - areadelimiter - 1;
    strptr := strptr + 1;
    curext := makestring;
  end;
end;
