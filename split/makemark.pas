procedure makemark;
var
  p: halfword;
begin
  p := scantoks(false, true);
  p := getnode(2);
  mem[p].hh.b0 := 4;
  mem[p].hh.b1 := 0;
  mem[p + 1].int := defref;
  mem[curlist.tailfield].hh.rh := p;
  curlist.tailfield := p;
end;
