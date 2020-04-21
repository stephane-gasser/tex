procedure scanleftbrace;
begin
  {404:}
repeat
    getxtoken;
  until (curcmd <> 10) and (curcmd <> 0){:404}
;
  if curcmd <> 1 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(657);
    end;
    begin
      helpptr := 4;
      helpline[3] := 658;
      helpline[2] := 659;
      helpline[1] := 660;
      helpline[0] := 661;
    end;
    backerror;
    curtok := 379;
    curcmd := 1;
    curchr := 123;
    alignstate := alignstate + 1;
  end;
end;
