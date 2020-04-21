procedure endtokenlist;
begin
  if curinput.indexfield >= 3 then
  begin
    if curinput.indexfield <= 4 then
      flushlist(curinput.startfield)
    else
    begin
      deletetokenref(curinput.startfield);
      if curinput.indexfield = 5 then
        while paramptr > curinput.limitfield do
        begin
          paramptr := paramptr - 1;
          flushlist(paramstack[paramptr]);
        end;
    end;
  end
  else if curinput.indexfield = 1 then
    if alignstate > 500000 then
      alignstate := 0
    else
      fatalerror(595);
  begin
    inputptr := inputptr - 1;
    curinput := inputstack[inputptr];
  end;
  begin
    if interrupt <> 0 then
      pauseforinstructions;
  end;
end;
