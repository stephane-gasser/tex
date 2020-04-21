procedure appendkern;
var
  s: quarterword;
begin
  s := curchr;
  scandimen(s = 99, false, false);
  begin
    mem[curlist.tailfield].hh.rh := newkern(curval);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  mem[curlist.tailfield].hh.b1 := s;
end;
