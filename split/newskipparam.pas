function newskipparam(n: smallnumber): halfword;
var
  p: halfword;
begin
  tempptr := newspec({224:}
eqtb[2882 + n].hh.rh{:224}
);
  p := newglue(tempptr);
  mem[tempptr].hh.rh := 0;
  mem[p].hh.b1 := n + 1;
  newskipparam := p;
end;
