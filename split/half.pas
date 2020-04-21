function half(x: integer): integer;
begin
  if odd(x) then
    half := (x + 1) div 2
  else
    half := x div 2;
end;
