procedure printcurrentstring;
var
  j: poolpointer;
begin
  j := strstart[strptr];
  while j < poolptr do
  begin
    printchar(strpool[j]);
    j := j + 1;
  end;
end;
