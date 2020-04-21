function multandadd(n: integer; x, y, maxanswer: scaled): scaled;
begin
  if n < 0 then
  begin
    x := -x;
    n := -n;
  end;
  if n = 0 then
    multandadd := y
  else if ((x <= (maxanswer - y) div n) and (-x <= (maxanswer + y) div n)) then
    multandadd := n * x + y
  else
  begin
    aritherror := true;
    multandadd := 0;
  end;
end;
