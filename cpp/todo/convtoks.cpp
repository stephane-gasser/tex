#include "convtoks.h"
void convtoks(void)
var
  oldsetting: 0..21;
  c: 0..5;
  savescannerstatus: smallnumber;
  b: poolpointer;
begin
  c := curchr;
  {471:}
case c of
    0, 1: scanint;
    2, 3:
    begin
      savescannerstatus := scannerstatus;
      scannerstatus := 0;
      gettoken;
      scannerstatus := savescannerstatus;
    end;
    4: scanfontident;
    5: if jobname = 0 then
        openlogfile;
  end{:471}
;
  oldsetting := selector;
  selector := 21;
  b := poolptr;
  {472:}
case c of
    0: printint(curval);
    1: printromanint(curval);
    2: if curcs <> 0 then
        sprintcs(curcs)
      else
        printchar(curchr);
    3: printmeaning;
    4:
    begin
      print(fontname[curval]);
      if fontsize[curval] <> fontdsize[curval] then
      begin
        print(741);
        printscaled(fontsize[curval]);
        print(397);
      end;
    end;
    5: print(jobname);
  end{:472}
;
  selector := oldsetting;
  mem[29988].hh.rh := strtoks(b);
  begintokenlist(mem[29997].hh.rh, 4);
end;

