procedure printsize(s: integer);
begin
  if s = 0 then
    printesc(412)
  else if s = 16 then
    printesc(413)
  else
    printesc(414);
end;
