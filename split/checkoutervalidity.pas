procedure checkoutervalidity;
var
  p: halfword;
  q: halfword;
begin
  if scannerstatus <> 0 then
  begin
    deletionsallowed := false;
    {337:}
if curcs <> 0 then
    begin
      if (curinput.statefield = 0) or (curinput.namefield < 1) or (curinput.namefield > 17) then
      begin
        p := getavail;
        mem[p].hh.lh := 4095 + curcs;
        begintokenlist(p, 3);
      end;
      curcmd := 10;
      curchr := 32;
    end{:337}
;
    if scannerstatus > 1 then{338:}

    begin
      runaway;
      if curcs = 0 then
      begin
        if interaction = 3 then;
        printnl(262);
        print(604);
      end
      else
      begin
        curcs := 0;
        begin
          if interaction = 3 then;
          printnl(262);
          print(605);
        end;
      end;
      print(606);
      {339:}
p := getavail;
      case scannerstatus of
        2:
        begin
          print(570);
          mem[p].hh.lh := 637;
        end;
        3:
        begin
          print(612);
          mem[p].hh.lh := partoken;
          longstate := 113;
        end;
        4:
        begin
          print(572);
          mem[p].hh.lh := 637;
          q := p;
          p := getavail;
          mem[p].hh.rh := q;
          mem[p].hh.lh := 6710;
          alignstate := -1000000;
        end;
        5:
        begin
          print(573);
          mem[p].hh.lh := 637;
        end;
      end;
      begintokenlist(p, 4){:339}
;
      print(607);
      sprintcs(warningindex);
      begin
        helpptr := 4;
        helpline[3] := 608;
        helpline[2] := 609;
        helpline[1] := 610;
        helpline[0] := 611;
      end;
      error;
    end{:338}

    else
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(598);
      end;
      printcmdchr(105, curif);
      print(599);
      printint(skipline);
      begin
        helpptr := 3;
        helpline[2] := 600;
        helpline[1] := 601;
        helpline[0] := 602;
      end;
      if curcs <> 0 then
        curcs := 0
      else
        helpline[2] := 603;
      curtok := 6713;
      inserror;
    end;
    deletionsallowed := true;
  end;
end;
