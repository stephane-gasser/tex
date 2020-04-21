procedure saveforafter(t: halfword);
begin
  if curlevel > 1 then
  begin
    if saveptr > maxsavestack then
    begin
      maxsavestack := saveptr;
      if maxsavestack > savesize - 6 then
        overflow(541, savesize);
    end;
    savestack[saveptr].hh.b0 := 2;
    savestack[saveptr].hh.b1 := 0;
    savestack[saveptr].hh.rh := t;
    saveptr := saveptr + 1;
  end;
end;
