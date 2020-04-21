function scanrulespec: halfword;
label
  21;
var
  q: halfword;
begin
  q := newrule;
  if curcmd = 35 then
    mem[q + 1].int := 26214
  else
  begin
    mem[q + 3].int := 26214;
    mem[q + 2].int := 0;
  end;
  21:
    if scankeyword(732) then
    begin
      scandimen(false, false, false);
      mem[q + 1].int := curval;
      goto 21;
    end;
  if scankeyword(733) then
  begin
    scandimen(false, false, false);
    mem[q + 3].int := curval;
    goto 21;
  end;
  if scankeyword(734) then
  begin
    scandimen(false, false, false);
    mem[q + 2].int := curval;
    goto 21;
  end;
  scanrulespec := q;
end;
