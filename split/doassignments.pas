procedure doassignments;
label
  10;
begin
  while true do
  begin
    {404:}
repeat
      getxtoken;
    until (curcmd <> 10) and (curcmd <> 0){:404}
;
    if curcmd <= 70 then
      goto 10;
    setboxallowed := false;
    prefixedcommand;
    setboxallowed := true;
  end;
  10: ;
end;
