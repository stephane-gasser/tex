function newparamglue(n: smallnumber): halfword;
var
  p: halfword;
  q: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 10;
  mem[p].hh.b1 := n + 1;
  mem[p + 1].hh.rh := 0;
  q :={224:}
eqtb[2882 + n].hh.rh{:224}
;
  mem[p + 1].hh.lh := q;
  mem[q].hh.rh := mem[q].hh.rh + 1;
  newparamglue := p;
end;
