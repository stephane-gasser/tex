procedure printhex(n: integer);
var
  k: 0..22;
begin
  k := 0;
  printchar(34);
  repeat
    dig[k] := n mod 16;
    n := n div 16;
    k := k + 1;
  until n = 0;
  printthedigs(k);
end;
