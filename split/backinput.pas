procedure backinput;
var
  p: halfword;
begin
  while (curinput.statefield = 0) and (curinput.locfield = 0) and (curinput.indexfield <> 2) do
    endtokenlist;
  p := getavail;
  mem[p].hh.lh := curtok;
  if curtok < 768 then
    if curtok < 512 then
      alignstate := alignstate - 1
    else
      alignstate := alignstate + 1;
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
  curinput.indexfield := 3;
  curinput.locfield := p;
end;
