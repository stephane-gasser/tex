procedure clearforerrorprompt;
begin
  while (curinput.statefield <> 0) and (curinput.namefield = 0) and (inputptr > 0) and (curinput.locfield > curinput.limitfield) do
    endfilereading;
  println;
  breakin(termin, true);
end;
