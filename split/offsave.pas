procedure offsave;
var
  p: halfword;
begin
  if curgroup = 0 then{1066:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(776);
    end;
    printcmdchr(curcmd, curchr);
    begin
      helpptr := 1;
      helpline[0] := 1042;
    end;
    error;
  end{:1066}

  else
  begin
    backinput;
    p := getavail;
    mem[29997].hh.rh := p;
    begin
      if interaction = 3 then;
      printnl(262);
      print(625);
    end;
    {1065:}
case curgroup of
      14:
      begin
        mem[p].hh.lh := 6711;
        printesc(516);
      end;
      15:
      begin
        mem[p].hh.lh := 804;
        printchar(36);
      end;
      16:
      begin
        mem[p].hh.lh := 6712;
        mem[p].hh.rh := getavail;
        p := mem[p].hh.rh;
        mem[p].hh.lh := 3118;
        printesc(1041);
      end;
      others:
      begin
        mem[p].hh.lh := 637;
        printchar(125);
      end
    end{:1065}
;
    print(626);
    begintokenlist(mem[29997].hh.rh, 4);
    begin
      helpptr := 5;
      helpline[4] := 1036;
      helpline[3] := 1037;
      helpline[2] := 1038;
      helpline[1] := 1039;
      helpline[0] := 1040;
    end;
    error;
  end;
end;
