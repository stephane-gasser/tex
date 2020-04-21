procedure finrow;
var
  p: halfword;
begin
  if curlist.modefield = -102 then
  begin
    p := hpack(mem[curlist.headfield].hh.rh, 0, 1);
    popnest;
    appendtovlist(p);
    if curhead <> curtail then
    begin
      mem[curlist.tailfield].hh.rh := mem[curhead].hh.rh;
      curlist.tailfield := curtail;
    end;
  end
  else
  begin
    p := vpackage(mem[curlist.headfield].hh.rh, 0, 1, 1073741823);
    popnest;
    mem[curlist.tailfield].hh.rh := p;
    curlist.tailfield := p;
    curlist.auxfield.hh.lh := 1000;
  end;
  mem[p].hh.b0 := 13;
  mem[p + 6].int := 0;
  if eqtb[3420].hh.rh <> 0 then
    begintokenlist(eqtb[3420].hh.rh, 13);
  alignpeek;
end;

