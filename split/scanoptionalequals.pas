procedure scanoptionalequals;
begin
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  if curtok <> 3133 then
    backinput;
end;
