#include "newgraf.h"
void newgraf(bool indented)
begin
  curlist.pgfield := 0;
  if (curlist.modefield = 1) or (curlist.headfield <> curlist.tailfield) then
  begin
    mem[curlist.tailfield].hh.rh := newparamglue(2);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  pushnest;
  curlist.modefield := 102;
  curlist.auxfield.hh.lh := 1000;
  if eqtb[5313].int <= 0 then
    curlang := 0
  else if eqtb[5313].int > 255 then
    curlang := 0
  else
    curlang := eqtb[5313].int;
  curlist.auxfield.hh.rh := curlang;
  curlist.pgfield := (normmin(eqtb[5314].int) * 64 + normmin(eqtb[5315].int)) * 65536 + curlang;
  if indented then
  begin
    curlist.tailfield := newnullbox;
    mem[curlist.headfield].hh.rh := curlist.tailfield;
    mem[curlist.tailfield + 1].int := eqtb[5830].int;
  end;
  if eqtb[3414].hh.rh <> 0 then
    begintokenlist(eqtb[3414].hh.rh, 7);
  if nestptr = 1 then
    buildpage;
end;
