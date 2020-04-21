function newglue(q: halfword): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 10;
  mem[p].hh.b1 := 0;
  mem[p + 1].hh.rh := 0;
  mem[p + 1].hh.lh := q;
  mem[q].hh.rh := mem[q].hh.rh + 1;
  newglue := p;
end;
