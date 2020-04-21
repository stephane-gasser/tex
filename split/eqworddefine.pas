procedure eqworddefine(p: halfword; w: integer);
begin
  if xeqlevel[p] <> curlevel then
  begin
    eqsave(p, xeqlevel[p]);
    xeqlevel[p] := curlevel;
  end;
  eqtb[p].int := w;
end;
