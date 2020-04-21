procedure initrow;
begin
  pushnest;
  curlist.modefield := (-103) - curlist.modefield;
  if curlist.modefield = -102 then
    curlist.auxfield.hh.lh := 0
  else
    curlist.
      auxfield.int := 0;
  begin
    mem[curlist.tailfield].hh.rh := newglue(mem[mem[29992].hh.rh + 1].hh.lh);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  mem[curlist.tailfield].hh.b1 := 12;
  curalign := mem[mem[29992].hh.rh].hh.rh;
  curtail := curhead;
  initspan(curalign);
end;
