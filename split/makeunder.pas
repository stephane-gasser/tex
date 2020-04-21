procedure makeunder(q: halfword);
var
  p, x, y: halfword;
  delta: scaled;
begin
  x := cleanbox(q + 1, curstyle);
  p := newkern(3 * fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int);
  mem[x].hh.rh := p;
  mem[p].hh.rh := fractionrule(fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int);
  y := vpackage(x, 0, 1, 1073741823);
  delta := mem[y + 3].int + mem[y + 2].int + fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int;
  mem[y + 3].int := mem[x + 3].int;
  mem[y + 2].int := delta - mem[y + 3].int;
  mem[q + 1].hh.lh := y;
  mem[q + 1].hh.rh := 2;
end;
