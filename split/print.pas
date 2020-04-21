procedure print(s: integer);
label
  10;
var
  j: poolpointer;
  nl: integer;
begin
  if s >= strptr then
    s := 259
  else if s < 256 then
    if s < 0 then
      s := 259
    else
    begin
      if selector > 20 then
      begin
        printchar(s);
        goto 10;
      end;
      if ({244:}
s = eqtb[5312].int{:244}
) then
        if selector < 20 then
        begin
          println;
          goto 10;
        end;
      nl := eqtb[5312].int;
      eqtb[5312].int := -1;
      j := strstart[s];
      while j < strstart[s + 1] do
      begin
        printchar(strpool[j]);
        j := j + 1;
      end;
      eqtb[5312].int := nl;
      goto 10;
    end;
  j := strstart[s];
  while j < strstart[s + 1] do
  begin
    printchar(strpool[j]);
    j := j + 1;
  end;
  10: ;
end;

