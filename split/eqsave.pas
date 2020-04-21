procedure eqsave(p: halfword; l: quarterword);
begin
  if saveptr > maxsavestack then
  begin
    maxsavestack := saveptr;
    if maxsavestack > savesize - 6 then
      overflow(541, savesize);
  end;
  if l = 0 then
    savestack[saveptr].hh.b0 := 1
  else
  begin
    savestack[saveptr] :=
      eqtb[p];
    saveptr := saveptr + 1;
    savestack[saveptr].hh.b0 := 0;
  end;
  savestack[saveptr].hh.b1 := l;
  savestack[saveptr].hh.rh := p;
  saveptr := saveptr + 1;
end;
