#include "shipout.h"
void shipout(halfword p)
label
  30;
var
  pageloc: integer;
  j, k: 0..9;
  s: poolpointer;
  oldsetting: 0..21;
begin
  if eqtb[5297].int > 0 then
  begin
    printnl(338);
    println;
    print(828);
  end;
  if termoffset > maxprintline - 9 then
    println
  else if (termoffset > 0) or (fileoffset > 0) then
    printchar(32);
  printchar(91);
  j := 9;
  while (eqtb[5318 + j].int = 0) and (j > 0) do
    j := j - 1;
  for k := 0 to j do
  begin
    printint(eqtb[5318 + k].int);
    if k < j then
      printchar(46);
  end;
  break(termout);
  if eqtb[5297].int > 0 then
  begin
    printchar(93);
    begindiagnostic;
    showbox(p);
    enddiagnostic(true);
  end;
  {640:}
{641:}
if (mem[p + 3].int > 1073741823) or (mem[p + 2].int > 1073741823) or
    (mem[p + 3].int + mem[p + 2].int + eqtb[5849].int > 1073741823) or (mem[p + 1].int + eqtb[5848].int > 1073741823) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(832);
    end;
    begin
      helpptr := 2;
      helpline[1] := 833;
      helpline[0] := 834;
    end;
    error;
    if eqtb[5297].int <= 0 then
    begin
      begindiagnostic;
      printnl(835);
      showbox(p);
      enddiagnostic(true);
    end;
    goto 30;
  end;
  if mem[p + 3].int + mem[p + 2].int + eqtb[5849].int > maxv then
    maxv := mem[p + 3].int + mem[p + 2].int + eqtb[5849].int;
  if mem[p + 1].int + eqtb[5848].int > maxh then
    maxh := mem[p + 1].int + eqtb[5848].int{:641}
;
  {617:}
dvih := 0;
  dviv := 0;
  curh := eqtb[5848].int;
  dvif := 0;
  if outputfilename = 0 then
  begin
    if jobname = 0 then
      openlogfile;
    packjobname(793);
    while not bopenout(dvifile) do
      promptfilename(794, 793);
    outputfilename := bmakenamestring(dvifile);
  end;
  if totalpages = 0 then
  begin
    begin
      dvibuf[dviptr] := 247;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    begin
      dvibuf[dviptr] := 2;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    dvifour(25400000);
    dvifour(473628672);
    preparemag;
    dvifour(eqtb[5280].int);
    oldsetting := selector;
    selector := 21;
    print(826);
    printint(eqtb[5286].int);
    printchar(46);
    printtwo(eqtb[5285].int);
    printchar(46);
    printtwo(eqtb[5284].int);
    printchar(58);
    printtwo(eqtb[5283].int div 60);
    printtwo(eqtb[5283].int mod 60);
    selector := oldsetting;
    begin
      dvibuf[dviptr] := (poolptr - strstart[strptr]);
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    for s := strstart[strptr] to poolptr - 1 do
    begin
      dvibuf[dviptr] := strpool[s];
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    poolptr := strstart[strptr];
  end{:617}
;
  pageloc := dvioffset + dviptr;
  begin
    dvibuf[dviptr] := 139;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  for k := 0 to 9 do
    dvifour(eqtb[5318 + k].int);
  dvifour(lastbop);
  lastbop := pageloc;
  curv := mem[p + 3].int + eqtb[5849].int;
  tempptr := p;
  if mem[p].hh.b0 = 1 then
    vlistout
  else
    hlistout;
  begin
    dvibuf[dviptr] := 140;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  totalpages := totalpages + 1;
  curs := -1;
  30:
  {:640}
;
  if eqtb[5297].int <= 0 then
    printchar(93);
  deadcycles := 0;
  break(termout);
  {639:}
{if eqtb[5294].int>1 then begin printnl(829);printint(varused);
printchar(38);printint(dynused);printchar(59);end;}
flushnodelist(p);
{if eqtb[5294].int>1 then begin print(830);printint(varused);
printchar(38);printint(dynused);print(831);
printint(himemmin-lomemmax-1);println;end;}
{:639}
;
end;
