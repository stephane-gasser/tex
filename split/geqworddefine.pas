procedure geqworddefine(p: halfword; w: integer);
begin
  eqtb[p].int := w;
  xeqlevel[p] := 1;
end;

