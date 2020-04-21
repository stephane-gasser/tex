function xovern(x: scaled; n: integer): scaled;
var
  negative: boolean;
begin
  negative := false;
  if n = 0 then
  begin
    aritherror := true;
    xovern := 0;
    remainder := x;
  end
  else
  begin
    if n < 0 then
    begin
      x := -x;
      n := -n;
      negative := true;
    end;
    if x >= 0 then
    begin
      xovern := x div n;
      remainder := x mod n;
    end
    else
    begin
      xovern := -((-x) div n);
      remainder := -((-x) mod n);
    end;
  end;
  if negative then
    remainder := -remainder;
end;

