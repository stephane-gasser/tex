procedure printglue(d: scaled; order: integer; s: strnumber);
begin
  printscaled(d);
  if (order < 0) or (order > 3) then
    print(310)
  else if order > 0 then
  begin
    print(
      311);
    while order > 1 do
    begin
      printchar(108);
      order := order - 1;
    end;
  end
  else if s <> 0 then
    print(s);
end;
