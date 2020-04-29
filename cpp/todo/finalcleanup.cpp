#include "finalcleanup.h"
void finalcleanup(void)
label
  10;
var
  c: smallnumber;
{
  c = curchr;
  if (jobname == 0)
    openlogfile;
  while inputptr > 0 do
    if (curinput.statefield == 0)
      endtokenlist
    else
      endfilereading;
  while openparens > 0 do
  {
    print(1275);
    openparens = openparens-1;
  }
  if (curlevel > 1)
  {
    printnl(40);
    printesc(1276);
    print(1277);
    printint(curlevel-1);
    printchar(41);
  }
  while condptr != 0 do
  {
    printnl(40);
    printesc(1276);
    print(1278);
    printcmdchr(105, curif);
    if (ifline != 0)
    {
      print(1279);
      printint(ifline);
    }
    print(1280);
    ifline = mem[condptr+1].int;
    curif = mem[condptr].hh.b1;
    tempptr = condptr;
    condptr = mem[condptr].hh.rh;
    freenode(tempptr, 2);
  }
  if (history != 0)
    if (((history == 1) or (interaction < 3)))
      if (selector == 19)
      {
        selector = 17;
        printnl(1281);
        selector = 19;
      }
  if (c == 1)
  {
    for c = 0 to 4 do
      if (curmark[c] != 0)
        deletetokenref(
          curmark[c]);
    if (lastglue != 65535)
      deleteglueref(lastglue);
    storefmtfile;
    goto 10;
    printnl(1282);
    goto 10;
  }
  10: ;
}
