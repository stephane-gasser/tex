#include "begininsertoradjust.h"
void begininsertoradjust(void)
begin
  if curcmd = 38 then
    curval := 255
  else
  begin
    scaneightbitint;
    if curval = 255 then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1084);
      end;
      printesc(330);
      printint(255);
      begin
        helpptr := 1;
        helpline[0] := 1085;
      end;
      error;
      curval := 0;
    end;
  end;
  savestack[saveptr + 0].int := curval;
  saveptr := saveptr + 1;
  newsavelevel(11);
  scanleftbrace;
  normalparagraph;
  pushnest;
  curlist.modefield := -1;
  curlist.auxfield.int := -65536000;
end;
