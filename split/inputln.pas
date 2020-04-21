function inputln(var f: alphafile; bypasseoln: boolean): boolean;
var
  lastnonblank: 0..bufsize;
begin
  if bypasseoln then
    if not EOF(f) then
      get(f);
  last := First;
  if EOF(f) then
    inputln := false
  else
  begin
    lastnonblank := First;
    while not eoln(f) do
    begin
      if last >= maxbufstack then
      begin
        maxbufstack :=
          last + 1;
        if maxbufstack = bufsize then
          {35:}
if formatident = 0 then
          begin
            writeln(
              termout, 'Buffer size exceeded!');
            goto 9999;
          end
          else
          begin
            curinput.locfield := First;
            curinput.limitfield := last - 1;
            overflow(256, bufsize);
          end{:35}
;
      end;
      buffer[last] := xord[f^];
      get(f);
      last := last + 1;
      if buffer[last - 1] <> 32 then
        lastnonblank := last;
    end;
    last := lastnonblank;
    inputln := true;
  end;
end;
