procedure scanspec(c: groupcode; threecodes: boolean);
label
  40;
var
  s: integer;
  speccode: 0..1;
begin
  if threecodes then
    s := savestack[saveptr + 0].int;
  if scankeyword(841) then
    speccode := 0
  else if scankeyword(842) then
    speccode := 1
  else
  begin
    speccode := 1;
    curval := 0;
    goto 40;
  end;
  scandimen(false, false, false);
  40:
    if threecodes then
    begin
      savestack[saveptr + 0].int := s;
      saveptr := saveptr + 1;
    end;
  savestack[saveptr + 0].int := speccode;
  savestack[saveptr + 1].int := curval;
  saveptr := saveptr + 2;
  newsavelevel(c);
  scanleftbrace;
end;
