procedure trapzeroglue;
begin
  if (mem[curval + 1].int = 0) and (mem[curval + 2].int = 0) and (mem[curval + 3].int = 0) then
  begin
    mem[0].hh.rh := mem[0].hh.rh + 1;
    deleteglueref(curval);
    curval := 0;
  end;
end;
