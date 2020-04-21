function newrule: halfword;
var
  p: halfword;
begin
  p := getnode(4);
  mem[p].hh.b0 := 2;
  mem[p].hh.b1 := 0;
  mem[p + 1].int := -1073741824;
  mem[p + 2].int := -1073741824;
  mem[p + 3].int := -1073741824;
  newrule := p;
end;

