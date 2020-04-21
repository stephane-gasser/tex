procedure resumeafterdisplay;
begin
  if curgroup <> 15 then
    confusion(1168);
  unsave;
  curlist.pgfield := curlist.pgfield + 3;
  pushnest;
  curlist.modefield := 102;
  curlist.auxfield.hh.lh := 1000;
  if eqtb[5313].int <= 0 then
    curlang := 0
  else if eqtb[5313].int > 255 then
    curlang := 0
  else
    curlang := eqtb[5313].int;
  curlist.auxfield.hh.rh := curlang;
  curlist.pgfield := (normmin(eqtb[5314].int) * 64 + normmin(eqtb[5315].int)) * 65536 + curlang;{443:}

  begin
    getxtoken;
    if curcmd <> 10 then
      backinput;
  end{:443}
;
  if nestptr = 1 then
    buildpage;
end;
