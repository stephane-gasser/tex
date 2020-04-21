procedure gettoken;
begin
  nonewcontrolsequence := false;
  getnext;
  nonewcontrolsequence := true;
  if curcs = 0 then
    curtok := (curcmd * 256) + curchr
  else
    curtok := 4095 + curcs;
end;
