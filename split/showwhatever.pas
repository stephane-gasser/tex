procedure showwhatever;
label
  50;
var
  p: halfword;
begin
  case curchr of
    3:
    begin
      begindiagnostic;
      showactivities;
    end;
    1:{1296:}

    begin
      scaneightbitint;
      begindiagnostic;
      printnl(1253);
      printint(curval);
      printchar(61);
      if eqtb[3678 + curval].hh.rh = 0 then
        print(410)
      else
        showbox(eqtb[3678 + curval].hh.rh);
    end{:1296}
;
    0:{1294:}

    begin
      gettoken;
      if interaction = 3 then;
      printnl(1247);
      if curcs <> 0 then
      begin
        sprintcs(curcs);
        printchar(61);
      end;
      printmeaning;
      goto 50;
    end{:1294}
;
    others:{1297:}

    begin
      p := thetoks;
      if interaction = 3 then;
      printnl(1247);
      tokenshow(29997);
      flushlist(mem[29997].hh.rh);
      goto 50;
    end{:1297}

  end;
  {1298:}
enddiagnostic(true);
  begin
    if interaction = 3 then;
    printnl(262);
    print(1254);
  end;
  if selector = 19 then
    if eqtb[5292].int <= 0 then
    begin
      selector := 17;
      print(1255);
      selector := 19;
    end{:1298}
;
  50:
    if interaction < 3 then
    begin
      helpptr := 0;
      errorcount := errorcount - 1;
    end
    else if eqtb[5292].int > 0 then
    begin
      helpptr := 3;
      helpline[2] := 1242;
      helpline[1] := 1243;
      helpline[0] := 1244;
    end
    else
    begin
      helpptr := 5;
      helpline[4] := 1242;
      helpline[3] := 1243;
      helpline[2] := 1244;
      helpline[1] := 1245;
      helpline[0] := 1246;
    end;
  error;
end;
