#include "finalcleanup.h"
void finalcleanup(void)
label
  10;
var
  c: smallnumber;
begin
  c := curchr;
  if jobname = 0 then
    openlogfile;
  while inputptr > 0 do
    if curinput.statefield = 0 then
      endtokenlist
    else
      endfilereading;
  while openparens > 0 do
  begin
    print(1275);
    openparens := openparens - 1;
  end;
  if curlevel > 1 then
  begin
    printnl(40);
    printesc(1276);
    print(1277);
    printint(curlevel - 1);
    printchar(41);
  end;
  while condptr <> 0 do
  begin
    printnl(40);
    printesc(1276);
    print(1278);
    printcmdchr(105, curif);
    if ifline <> 0 then
    begin
      print(1279);
      printint(ifline);
    end;
    print(1280);
    ifline := mem[condptr + 1].int;
    curif := mem[condptr].hh.b1;
    tempptr := condptr;
    condptr := mem[condptr].hh.rh;
    freenode(tempptr, 2);
  end;
  if history <> 0 then
    if ((history = 1) or (interaction < 3)) then
      if selector = 19 then
      begin
        selector := 17;
        printnl(1281);
        selector := 19;
      end;
  if c = 1 then
  begin
    for c := 0 to 4 do
      if curmark[c] <> 0 then
        deletetokenref(
          curmark[c]);
    if lastglue <> 65535 then
      deleteglueref(lastglue);
    storefmtfile;
    goto 10;
    printnl(1282);
    goto 10;
  end;
  10: ;
end;
