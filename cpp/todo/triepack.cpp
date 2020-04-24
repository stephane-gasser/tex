#include "triepack.h"
void triepack(triepointer p)
var
  q: triepointer;
begin
  repeat
    q := triel[p];
    if (q > 0) and (triehash[q] = 0) then
    begin
      firstfit(q);
      triepack(q);
    end;
    p := trier[p];
  until p = 0;
end;
