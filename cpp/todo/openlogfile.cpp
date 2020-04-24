#include "openlogfile.h"
void openlogfile(void)
var
  oldsetting: 0..21;
  k: 0..bufsize;
  l: 0..bufsize;
  months: packed array[1..36] of char;
begin
  oldsetting := selector;
  if jobname = 0 then
    jobname := 795;
  packjobname(796);
  while not aopenout(logfile) do{535:}

  begin
    selector := 17;
    promptfilename(798, 796);
  end{:535}
;
  logname := amakenamestring(logfile);
  selector := 18;
  logopened := true;
  {536:}
begin
    write(logfile, 'This is TeX, Version 3.14159265');
    slowprint(formatident);
    print(799);
    printint(eqtb[5284].int);
    printchar(32);
    months := 'JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC';
    for k := 3 * eqtb[5285].int - 2 to 3 * eqtb[5285].int do
      write(logfile, months[k]);
    printchar(32);
    printint(eqtb[5286].int);
    printchar(32);
    printtwo(eqtb[5283].int div 60);
    printchar(58);
    printtwo(eqtb[5283].int mod 60);
  end{:536}
;
  inputstack[inputptr] := curinput;
  printnl(797);
  l := inputstack[0].limitfield;
  if buffer[l] = eqtb[5311].int then
    l := l - 1;
  for k := 1 to l do
    print(buffer[k]);
  println;
  selector := oldsetting + 2;
end;
