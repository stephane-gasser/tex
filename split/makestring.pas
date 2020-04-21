function makestring: strnumber;
begin
  if strptr = maxstrings then
    overflow(258, maxstrings - initstrptr);
  strptr := strptr + 1;
  strstart[strptr] := poolptr;
  makestring := strptr - 1;
end;
