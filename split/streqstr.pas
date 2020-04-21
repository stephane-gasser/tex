function streqstr(s, t: strnumber): boolean;
label
  45;
var
  j, k: poolpointer;
  result: boolean;
begin
  result := false;
  if (strstart[s + 1] - strstart[s]) <> (strstart[t + 1] - strstart[t]) then
    goto 45;
  j := strstart[s];
  k := strstart[t];
  while j < strstart[s + 1] do
  begin
    if strpool[j] <> strpool[k] then
      goto 45;
    j := j + 1;
    k := k + 1;
  end;
  result := true;
  45:
    streqstr := result;
end;

