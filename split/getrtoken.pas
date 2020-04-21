procedure getrtoken;
label
  20;
begin
  20:
    repeat
      gettoken;
    until curtok <> 2592;
  if (curcs = 0) or (curcs > 2614) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1183);
    end;
    begin
      helpptr := 5;
      helpline[4] := 1184;
      helpline[3] := 1185;
      helpline[2] := 1186;
      helpline[1] := 1187;
      helpline[0] := 1188;
    end;
    if curcs = 0 then
      backinput;
    curtok := 6709;
    inserror;
    goto 20;
  end;
end;
