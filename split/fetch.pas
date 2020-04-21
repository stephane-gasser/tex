procedure fetch(a: halfword);
begin
  curc := mem[a].hh.b1;
  curf := eqtb[3935 + mem[a].hh.b0 + cursize].hh.rh;
  if curf = 0 then{723:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(338);
    end;
    printsize(cursize);
    printchar(32);
    printint(mem[a].hh.b0);
    print(883);
    print(curc - 0);
    printchar(41);
    begin
      helpptr := 4;
      helpline[3] := 884;
      helpline[2] := 885;
      helpline[1] := 886;
      helpline[0] := 887;
    end;
    error;
    curi := nullcharacter;
    mem[a].hh.rh := 0;
  end{:723}

  else
  begin
    if (curc - 0 >= fontbc[curf]) and (curc - 0 <= fontec[curf]) then
      curi := fontinfo[charbase[curf] + curc].qqqq
    else
      curi := nullcharacter;
    if not ((curi.b0 > 0)) then
    begin
      charwarning(curf, curc - 0);
      mem[a].hh.rh := 0;
    end;
  end;
end;
