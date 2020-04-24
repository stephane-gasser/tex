#include "itsallover.h"
bool itsallover(void)
label
  10;
begin
  if privileged then
  begin
    if (29998 = pagetail) and (curlist.headfield = curlist.tailfield) and (deadcycles = 0) then
    begin
      itsallover := true;
      goto 10;
    end;
    backinput;
    begin
      mem[curlist.tailfield].hh.rh := newnullbox;
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    mem[curlist.tailfield + 1].int := eqtb[5833].int;
    begin
      mem[curlist.tailfield].hh.rh := newglue(8);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    begin
      mem[curlist.tailfield].hh.rh := newpenalty(-1073741824);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    buildpage;
  end;
  itsallover := false;
  10: ;
end;
