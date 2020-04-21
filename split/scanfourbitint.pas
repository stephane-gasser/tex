procedure scanfourbitint;
begin
  scanint;
  if (curval < 0) or (curval > 15) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(692);
    end;
    begin
      helpptr := 2;
      helpline[1] := 693;
      helpline[0] := 689;
    end;
    interror(curval);
    curval := 0;
  end;
end;
