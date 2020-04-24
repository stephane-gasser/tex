#include "readtoks.h"
void readtoks(int n, halfword r)
label
  30;
var
  p: halfword;
  q: halfword;
  s: integer;
  m: smallnumber;
begin
  scannerstatus := 2;
  warningindex := r;
  defref := getavail;
  mem[defref].hh.lh := 0;
  p := defref;
  begin
    q := getavail;
    mem[p].hh.rh := q;
    mem[q].hh.lh := 3584;
    p := q;
  end;
  if (n < 0) or (n > 15) then
    m := 16
  else
    m := n;
  s := alignstate;
  alignstate := 1000000;
  repeat
    {483:}
beginfilereading;
    curinput.namefield := m + 1;
    if readopen[m] = 2 then
      {484:}
if interaction > 1 then
        if n < 0 then
        begin
          ;
          print(338);
          terminput;
        end
        else
        begin
          ;
          println;
          sprintcs(r);
          begin
            ;
            print(61);
            terminput;
          end;
          n := -1;
        end
      else
        fatalerror(753){:484}

    else if readopen[m] = 1 then
      {485:}
if inputln(readfile[m], false) then
        readopen[m] := 0
      else
      begin
        aclose(readfile[m]);
        readopen[m] := 2;
      end{:485}

    else{486:}
if not inputln(readfile[m], true) then
    begin
      aclose(readfile[m]);
      readopen[m] := 2;
      if alignstate <> 1000000 then
      begin
        runaway;
        begin
          if interaction = 3 then;
          printnl(262);
          print(754);
        end;
        printesc(534);
        begin
          helpptr := 1;
          helpline[0] := 755;
        end;
        alignstate := 1000000;
        error;
      end;
    end{:486}
;
    curinput.limitfield := last;
    if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
      curinput.limitfield :=
        curinput.limitfield - 1
    else
      buffer[curinput.limitfield] := eqtb[5311].int;
    First := curinput.limitfield + 1;
    curinput.locfield := curinput.startfield;
    curinput.statefield := 33;
    while true do
    begin
      gettoken;
      if curtok = 0 then
        goto 30;
      if alignstate < 1000000 then
      begin
        repeat
          gettoken;
        until curtok = 0;
        alignstate := 1000000;
        goto 30;
      end;
      begin
        q := getavail;
        mem[p].hh.rh := q;
        mem[q].hh.lh := curtok;
        p := q;
      end;
    end;
    30:
      endfilereading{:483}
;
  until alignstate = 1000000;
  curval := defref;
  scannerstatus := 0;
  alignstate := s;
end;
