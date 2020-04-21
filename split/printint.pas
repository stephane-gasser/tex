procedure printint(n: integer);
var
  k: 0..23;
  m: integer;
begin
  k := 0;
  if n < 0 then
  begin
    printchar(45);
    if n > -100000000 then
      n := -n
    else
    begin
      m := -1 - n;
      n := m div 10;
      m := (m mod 10) + 1;
      k := 1;
      if m < 10 then
        dig[0] := m
      else
      begin
        dig[0] := 0;
        n := n + 1;
      end;
    end;
  end;
  repeat
    dig[k] := n mod 10;
    n := n div 10;
    k := k + 1;
  until n = 0;
  printthedigs(k);
end;
