function initterminal: boolean;
label
  10;
begin
  reset(termin, 'TTY:', '/O/I');
  while true do
  begin
    ;
    write(termout, '**');
    break(termout);
    if not inputln(termin, true) then
    begin
      writeln(termout);
      write(termout, '! End of file on the terminal... why?');
      initterminal := false;
      goto 10;
    end;
    curinput.locfield := First;
    while (curinput.locfield < last) and (buffer[curinput.locfield] = 32) do
      curinput.locfield := curinput.locfield + 1;
    if curinput.locfield < last then
    begin
      initterminal := true;
      goto 10;
    end;
    writeln(termout, 'Please type the name of your input file.');
  end;
  10: ;
end;
