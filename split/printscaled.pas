procedure printscaled(s: scaled);
var
  delta: scaled;
begin
  if s < 0 then
  begin
    printchar(45);
    s := -s;
  end;
  printint(s div 65536);
  printchar(46);
  s := 10 * (s mod 65536) + 5;
  delta := 10;
  repeat
    if delta > 65536 then
      s := s - 17232;
    printchar(48 + (s div 65536));
    s := 10 * (s mod 65536);
    delta := delta * 10;
  until s <= delta;
end;
