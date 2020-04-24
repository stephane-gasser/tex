#include "initalign.h"
void initalign(void)
label
  30, 31, 32, 22;
var
  savecsptr: halfword;
  p: halfword;
begin
  savecsptr := curcs;
  pushalignment;
  alignstate := -1000000;
  {776:}
if (curlist.modefield = 203) and ((curlist.tailfield <> curlist.headfield) or (curlist.auxfield.int <> 0)) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(680);
    end;
    printesc(520);
    print(893);
    begin
      helpptr := 3;
      helpline[2] := 894;
      helpline[1] := 895;
      helpline[0] := 896;
    end;
    error;
    flushmath;
  end{:776}
;
  pushnest;
  {775:}
if curlist.modefield = 203 then
  begin
    curlist.modefield := -1;
    curlist.auxfield.int := nest[nestptr - 2].auxfield.int;
  end
  else if curlist.modefield > 0 then
    curlist.modefield := -curlist.modefield{:775}
;
  scanspec(6, false);
  {777:}
mem[29992].hh.rh := 0;
  curalign := 29992;
  curloop := 0;
  scannerstatus := 4;
  warningindex := savecsptr;
  alignstate := -1000000;
  while true do
  begin
    {778:}
mem[curalign].hh.rh := newparamglue(11);
    curalign := mem[curalign].hh.rh{:778}
;
    if curcmd = 5 then
      goto 30;
    {779:}
{783:}
p := 29996;
    mem[p].hh.rh := 0;
    while true do
    begin
      getpreambletoken;
      if curcmd = 6 then
        goto 31;
      if (curcmd <= 5) and (curcmd >= 4) and (alignstate = -1000000) then
        if (p = 29996) and (curloop = 0) and (curcmd = 4) then
          curloop := curalign
        else
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(902);
          end;
          begin
            helpptr := 3;
            helpline[2] := 903;
            helpline[1] := 904;
            helpline[0] := 905;
          end;
          backerror;
          goto 31;
        end
      else if (curcmd <> 10) or (p <> 29996) then
      begin
        mem[p].hh.rh := getavail;
        p := mem[p].hh.rh;
        mem[p].hh.lh := curtok;
      end;
    end;
    31:
    {:783}
;
    mem[curalign].hh.rh := newnullbox;
    curalign := mem[curalign].hh.rh;
    mem[curalign].hh.lh := 29991;
    mem[curalign + 1].int := -1073741824;
    mem[curalign + 3].int := mem[29996].hh.rh;
    {784:}
p := 29996;
    mem[p].hh.rh := 0;
    while true do
    begin
      22:
        getpreambletoken;
      if (curcmd <= 5) and (curcmd >= 4) and (alignstate = -1000000) then
        goto 32;
      if curcmd = 6 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(906);
        end;
        begin
          helpptr := 3;
          helpline[2] := 903;
          helpline[1] := 904;
          helpline[0] := 907;
        end;
        error;
        goto 22;
      end;
      mem[p].hh.rh := getavail;
      p := mem[p].hh.rh;
      mem[p].hh.lh := curtok;
    end;
    32:
      mem[p].hh.rh := getavail;
    p := mem[p].hh.rh;
    mem[p].hh.lh := 6714{:784}
;
    mem[curalign + 2].int := mem[29996].hh.rh{:779}
;
  end;
  30:
    scannerstatus := 0{:777}
;
  newsavelevel(6);
  if eqtb[3420].hh.rh <> 0 then
    begintokenlist(eqtb[3420].hh.rh, 13);
  alignpeek;
end;
