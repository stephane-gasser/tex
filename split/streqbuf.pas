function streqbuf(s: strnumber; k: integer): boolean;
label
  45;
var
  j: poolpointer;
  result: boolean;
begin
  j := strstart[s];
  while j < strstart[s + 1] do
  begin
    if strpool[j] <> buffer[k] then
    begin
      result := false;
      goto 45;
    end;
    j := j + 1;
    k := k + 1;
  end;
  result := true;
  45:
    streqbuf := result;
end;
