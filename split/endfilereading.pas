procedure endfilereading;
begin
  First := curinput.startfield;
  line := linestack[curinput.indexfield];
  if curinput.namefield > 17 then
    aclose(inputfile[curinput.indexfield]);
  begin
    inputptr := inputptr - 1;
    curinput := inputstack[inputptr];
  end;
  inopen := inopen - 1;
end;
