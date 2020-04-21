procedure alterboxdimen;
var
  c: smallnumber;
  b: eightbits;
begin
  c := curchr;
  scaneightbitint;
  b := curval;
  scanoptionalequals;
  scandimen(false, false, false);
  if eqtb[3678 + b].hh.rh <> 0 then
    mem[eqtb[3678 + b].hh.rh + c].int := curval;
end;
