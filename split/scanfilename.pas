procedure scanfilename;
label
  30;
begin
  nameinprogress := true;
  beginname;
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  while true do
  begin
    if (curcmd > 12) or (curchr > 255) then
    begin
      backinput;
      goto 30;
    end;
    if not morename(curchr) then
      goto 30;
    getxtoken;
  end;
  30:
    endname;
  nameinprogress := false;
end;
