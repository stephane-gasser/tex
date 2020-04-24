#include "getpreambletoken.h"
void getpreambletoken(void)
label
  20;
begin
  20:
    gettoken;
  while (curchr = 256) and (curcmd = 4) do
  begin
    gettoken;
    if curcmd > 100 then
    begin
      expand;
      gettoken;
    end;
  end;
  if curcmd = 9 then
    fatalerror(595);
  if (curcmd = 75) and (curchr = 2893) then
  begin
    scanoptionalequals;
    scanglue(2);
    if eqtb[5306].int > 0 then
      geqdefine(2893, 117, curval)
    else
      eqdefine(2893,
        117, curval);
    goto 20;
  end;
end;
