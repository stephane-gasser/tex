procedure printnl(s: strnumber);
begin
  if ((termoffset > 0) and (odd(selector))) or ((fileoffset > 0) and (selector >= 18)) then
    println;
  print(s);
end;
