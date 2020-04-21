function overbar(b: halfword; k, t: scaled): halfword;
var
  p, q: halfword;
begin
  p := newkern(k);
  mem[p].hh.rh := b;
  q := fractionrule(t);
  mem[q].hh.rh := p;
  p := newkern(t);
  mem[p].hh.rh := q;
  overbar := vpackage(p, 0, 1, 1073741823);
end;
