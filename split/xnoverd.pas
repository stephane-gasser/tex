function xnoverd(x: scaled; n, d: integer): scaled;
var
  positive: boolean;
  t, u, v: nonnegativeinteger;
begin
  if x >= 0 then
    positive := true
  else
  begin
    x := -x;
    positive := false;
  end;
  t := (x mod 32768) * n;
  u := (x div 32768) * n + (t div 32768);
  v := (u mod d) * 32768 + (t mod 32768);
  if u div d >= 32768 then
    aritherror := true
  else
    u := 32768 * (u div d) + (v div d);
  if positive then
  begin
    xnoverd := u;
    remainder := v mod d;
  end
  else
  begin
    xnoverd := -u;
    remainder := -(v mod d);
  end;
end;
