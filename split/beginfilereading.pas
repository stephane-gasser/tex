procedure beginfilereading;
begin
  if inopen = maxinopen then
    overflow(596, maxinopen);
  if First = bufsize then
    overflow(256, bufsize);
  inopen := inopen + 1;
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
  curinput.indexfield := inopen;
  linestack[curinput.indexfield] := line;
  curinput.startfield := First;
  curinput.statefield := 1;
  curinput.namefield := 0;
end;
