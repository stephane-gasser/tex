#include "compresstrie.h"
triepointer compresstrie(triepointer p)
begin
  if p = 0 then
    compresstrie := 0
  else
  begin
    triel[p] := compresstrie(triel[p]);
    trier[p] := compresstrie(trier[p]);
    compresstrie := trienode(p);
  end;
end;
