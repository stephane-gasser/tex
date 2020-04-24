#include "xtoken.h"
void xtoken(void)
begin
  while curcmd > 100 do
  begin
    expand;
    getnext;
  end;
  if curcs = 0 then
    curtok := (curcmd * 256) + curchr
  else
    curtok := 4095 + curcs;
end;
