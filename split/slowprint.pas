procedure slowprint(s: integer);
var
  j: poolpointer;
begin
  if (s >= strptr) or (s < 256) then
    print(s)
  else
  begin
    j := strstart[s];
    while j < strstart[s + 1] do
    begin
      print(strpool[j]);
      j := j + 1;
    end;
  end;
end;

