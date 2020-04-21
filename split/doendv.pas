procedure doendv;
begin
  baseptr := inputptr;
  inputstack[baseptr] := curinput;
  while (inputstack[baseptr].indexfield <> 2) and (inputstack[baseptr].locfield = 0) and (inputstack[baseptr].statefield = 0) do
    baseptr := baseptr - 1;
  if (inputstack[baseptr].indexfield <> 2) or (inputstack[baseptr].locfield <> 0) or (inputstack[baseptr].statefield <> 0) then
    fatalerror(595);
  if curgroup = 6 then
  begin
    endgraf;
    if fincol then
      finrow;
  end
  else
    offsave;
end;
