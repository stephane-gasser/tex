#include "trienode.h"
triepointer trienode(triepointer p)
label
  10;
var
  h: triepointer;
  q: triepointer;
begin
  h := abs(triec[p] + 1009 * trieo[p] + 2718 * triel[p] + 3142 * trier[p]) mod triesize;
  while true do
  begin
    q := triehash[h];
    if q = 0 then
    begin
      triehash[h] := p;
      trienode := p;
      goto 10;
    end;
    if (triec[q] = triec[p]) and (trieo[q] = trieo[p]) and (triel[q] = triel[p]) and (trier[q] = trier[p]) then
    begin
      trienode := q;
      goto 10;
    end;
    if h > 0 then
      h := h - 1
    else
      h := triesize;
  end;
  10: ;
end;
