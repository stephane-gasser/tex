procedure printtwo(n: integer);
begin
  n := abs(n) mod 100;
  printchar(48 + (n div 10));
  printchar(48 + (n mod 10));
end;

