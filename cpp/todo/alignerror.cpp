#include "alignerror.h"
void alignerror(void)
begin
  if abs(alignstate) > 2 then{1128:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1113);
    end;
    printcmdchr(curcmd, curchr);
    if curtok = 1062 then
    begin
      helpptr := 6;
      helpline[5] := 1114;
      helpline[4] := 1115;
      helpline[3] := 1116;
      helpline[2] := 1117;
      helpline[1] := 1118;
      helpline[0] := 1119;
    end
    else
    begin
      begin
        helpptr := 5;
        helpline[4] := 1114;
        helpline[3] := 1120;
        helpline[2] := 1117;
        helpline[1] := 1118;
        helpline[0] := 1119;
      end;
    end;
    error;
  end{:1128}

  else
  begin
    backinput;
    if alignstate < 0 then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(657);
      end;
      alignstate := alignstate + 1;
      curtok := 379;
    end
    else
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1109);
      end;
      alignstate := alignstate - 1;
      curtok := 637;
    end;
    begin
      helpptr := 3;
      helpline[2] := 1110;
      helpline[1] := 1111;
      helpline[0] := 1112;
    end;
    inserror;
  end;
end;
