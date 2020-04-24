#include "flushmath.h"
void flushmath(void)
begin
  flushnodelist(mem[curlist.headfield].hh.rh);
  flushnodelist(curlist.auxfield.int);
  mem[curlist.headfield].hh.rh := 0;
  curlist.tailfield := curlist.headfield;
  curlist.auxfield.int := 0;
end;

