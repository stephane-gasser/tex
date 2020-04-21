procedure begintokenlist(p: halfword; t: quarterword);
begin
  begin
    if inputptr > maxinstack then
    begin
      maxinstack := inputptr;
      if inputptr = stacksize then
        overflow(593, stacksize);
    end;
    inputstack[inputptr] := curinput;
    inputptr := inputptr + 1;
  end;
  curinput.statefield := 0;
  curinput.startfield := p;
  curinput.indexfield := t;
  if t >= 5 then
  begin
    mem[p].hh.lh := mem[p].hh.lh + 1;
    if t = 5 then
      curinput.limitfield := paramptr
    else
    begin
      curinput.locfield :=
        mem[p].hh.rh;
      if eqtb[5293].int > 1 then
      begin
        begindiagnostic;
        printnl(338);
        case t of
          14: printesc(351);
          15: printesc(594);
          others: printcmdchr(72, t + 3407)
        end;
        print(556);
        tokenshow(p);
        enddiagnostic(false);
      end;
    end;
  end
  else
    curinput.locfield := p;
end;
