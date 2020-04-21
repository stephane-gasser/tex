procedure scanint;
label
  30;
var
  negative: boolean;
  m: integer;
  d: smallnumber;
  vacuous: boolean;
  OKsofar: boolean;
begin
  radix := 0;
  OKsofar := true;
  {441:}
negative := false;
  repeat
    {406:}
repeat
      getxtoken;
    until curcmd <> 10{:406}
;
    if curtok = 3117 then
    begin
      negative := not negative;
      curtok := 3115;
    end;
  until curtok <> 3115{:441}
;
  if curtok = 3168 then{442:}

  begin
    gettoken;
    if curtok < 4095 then
    begin
      curval := curchr;
      if curcmd <= 2 then
        if curcmd = 2 then
          alignstate := alignstate + 1
        else
          alignstate := alignstate - 1;
    end
    else if curtok < 4352 then
      curval := curtok - 4096
    else
      curval := curtok - 4352;
    if curval > 255 then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(698);
      end;
      begin
        helpptr := 2;
        helpline[1] := 699;
        helpline[0] := 700;
      end;
      curval := 48;
      backerror;
    end
    else{443:}

    begin
      getxtoken;
      if curcmd <> 10 then
        backinput;
    end{:443}
;
  end{:442}

  else if (curcmd >= 68) and (curcmd <= 89) then
    scansomethinginternal(0,
      false)
  else{444:}

  begin
    radix := 10;
    m := 214748364;
    if curtok = 3111 then
    begin
      radix := 8;
      m := 268435456;
      getxtoken;
    end
    else if curtok = 3106 then
    begin
      radix := 16;
      m := 134217728;
      getxtoken;
    end;
    vacuous := true;
    curval := 0;
    {445:}
while true do
    begin
      if (curtok < 3120 + radix) and (curtok >= 3120) and (curtok <= 3129) then
        d := curtok - 3120
      else if radix = 16 then
        if (curtok <= 2886) and (curtok >= 2881) then
          d := curtok - 2871
        else if (curtok <= 3142) and (curtok >= 3137) then
          d := curtok - 3127
        else
          goto 30
      else
        goto 30;
      vacuous := false;
      if (curval >= m) and ((curval > m) or (d > 7) or (radix <> 10)) then
      begin
        if OKsofar then
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(701);
          end;
          begin
            helpptr := 2;
            helpline[1] := 702;
            helpline[0] := 703;
          end;
          error;
          curval := 2147483647;
          OKsofar := false;
        end;
      end
      else
        curval := curval * radix + d;
      getxtoken;
    end;
    30:
    {:445}
;
    if vacuous then{446:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(664);
      end;
      begin
        helpptr := 3;
        helpline[2] := 665;
        helpline[1] := 666;
        helpline[0] := 667;
      end;
      backerror;
    end{:446}

    else if curcmd <> 10 then
      backinput;
  end{:444}
;
  if negative then
    curval := -curval;
end;
