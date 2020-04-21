function badness(t, s: scaled): halfword;
var
  r: integer;
begin
  if t = 0 then
    badness := 0
  else if s <= 0 then
    badness := 10000
  else
  begin
    if t <= 7230584 then
      r := (t * 297) div s
    else if s >= 1663497 then
      r := t div (s div 297)
    else
      r := t;
    if r > 1290 then
      badness := 10000
    else
      badness := (r * r * r + 131072) div 262144;
  end;
end;
