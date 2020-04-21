procedure printruledimen(d: scaled);
begin
  if (d = -1073741824) then
    printchar(42)
  else
    printscaled(d);
end;
