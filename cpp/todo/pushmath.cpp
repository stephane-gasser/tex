#include "pushmath.h"
void pushmath(groupcode c)
begin
  pushnest;
  curlist.modefield := -203;
  curlist.auxfield.int := 0;
  newsavelevel(c);
end;
