procedure showtokenlist(p, q: integer; l: integer);
label
  10;
var
  m, c: integer;
  matchchr: ASCIIcode;
  n: ASCIIcode;
begin
  matchchr := 35;
  n := 48;
  tally := 0;
  while (p <> 0) and (tally < l) do
  begin
    if p = q then{320:}

    begin
      firstcount := tally;
      trickcount := tally + 1 + errorline - halferrorline;
      if trickcount < errorline then
        trickcount := errorline;
    end{:320}
;
    {293:}
if (p < himemmin) or (p > memend) then
    begin
      printesc(309);
      goto 10;
    end;
    if mem[p].hh.lh >= 4095 then
      printcs(mem[p].hh.lh - 4095)
    else
    begin
      m := mem[p].hh.lh div 256;
      c := mem[p].hh.lh mod 256;
      if mem[p].hh.lh < 0 then
        printesc(555)
      else
        {294:}
case m of
          1, 2, 3, 4, 7, 8, 10,
          11, 12: print(c);
          6:
          begin
            print(c);
            print(c);
          end;
          5:
          begin
            print(matchchr);
            if c <= 9 then
              printchar(c + 48)
            else
            begin
              printchar(33);
              goto 10;
            end;
          end;
          13:
          begin
            matchchr := c;
            print(c);
            n := n + 1;
            printchar(n);
            if n > 57 then
              goto 10;
          end;
          14: print(556);
          others: printesc(555)
        end{:294}
;
    end{:293}
;
    p := mem[p].hh.rh;
  end;
  if p <> 0 then
    printesc(554);
  10: ;
end;
