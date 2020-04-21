procedure printromanint(n: integer);
label
  10;
var
  j, k: poolpointer;
  u, v: nonnegativeinteger;
begin
  j := strstart[260];
  v := 1000;
  while true do
  begin
    while n >= v do
    begin
      printchar(strpool[j]);
      n := n - v;
    end;
    if n <= 0 then
      goto 10;
    k := j + 2;
    u := v div (strpool[k - 1] - 48);
    if strpool[k - 1] = 50 then
    begin
      k := k + 2;
      u := u div (strpool[k - 1] - 48);
    end;
    if n + u >= v then
    begin
      printchar(strpool[k]);
      n := n + u;
    end
    else
    begin
      j := j + 2;
      v := v div (strpool[j - 1] - 48);
    end;
  end;
  10: ;
end;
