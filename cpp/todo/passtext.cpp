#include "passtext.h"
void passtext(void)
label
  30;
var
  l: integer;
  savescannerstatus: smallnumber;
begin
  savescannerstatus := scannerstatus;
  scannerstatus := 1;
  l := 0;
  skipline := line;
  while true do
  begin
    getnext;
    if curcmd = 106 then
    begin
      if l = 0 then
        goto 30;
      if curchr = 2 then
        l := l - 1;
    end
    else if curcmd = 105 then
      l := l + 1;
  end;
  30:
    scannerstatus := savescannerstatus;
end;
