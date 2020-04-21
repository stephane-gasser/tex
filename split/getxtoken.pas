procedure getxtoken;
label
  20, 30;
begin
  20:
    getnext;
  if curcmd <= 100 then
    goto 30;
  if curcmd >= 111 then
    if curcmd < 115 then
      macrocall
    else
    begin
      curcs := 2620;
      curcmd := 9;
      goto 30;
    end
  else
    expand;
  goto 20;
  30:
    if curcs = 0 then
      curtok := (curcmd * 256) + curchr
    else
      curtok := 4095 + curcs;
end;
