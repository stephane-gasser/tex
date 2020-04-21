function rounddecimals(k: smallnumber): scaled;
var
  a: integer;
begin
  a := 0;
  while k > 0 do
  begin
    k := k - 1;
    a := (a + dig[k] * 131072) div 10;
  end;
  rounddecimals := (a + 1) div 2;
end;
