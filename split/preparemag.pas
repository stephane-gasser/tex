procedure preparemag;
begin
  if (magset > 0) and (eqtb[5280].int <> magset) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(547);
    end;
    printint(eqtb[5280].int);
    print(548);
    printnl(549);
    begin
      helpptr := 2;
      helpline[1] := 550;
      helpline[0] := 551;
    end;
    interror(magset);
    geqworddefine(5280, magset);
  end;
  if (eqtb[5280].int <= 0) or (eqtb[5280].int > 32768) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(552);
    end;
    begin
      helpptr := 1;
      helpline[0] := 553;
    end;
    interror(eqtb[5280].int);
    geqworddefine(5280, 1000);
  end;
  magset := eqtb[5280].int;
end;
