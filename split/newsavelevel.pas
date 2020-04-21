procedure newsavelevel(c: groupcode);
begin
  if saveptr > maxsavestack then
  begin
    maxsavestack := saveptr;
    if maxsavestack > savesize - 6 then
      overflow(541, savesize);
  end;
  savestack[saveptr].hh.b0 := 3;
  savestack[saveptr].hh.b1 := curgroup;
  savestack[saveptr].hh.rh := curboundary;
  if curlevel = 255 then
    overflow(542, 255);
  curboundary := saveptr;
  curlevel := curlevel + 1;
  saveptr := saveptr + 1;
  curgroup := c;
end;
