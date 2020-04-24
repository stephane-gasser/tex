#include "outwhat.h"
void outwhat(halfword p)
var
  j: smallnumber;
begin
  case mem[p].hh.b1 of
    0, 1, 2:{1374:}
if not doingleaders then
      begin
        j := mem[p + 1].hh.lh;
        if mem[p].hh.b1 = 1 then
          writeout(p)
        else
        begin
          if writeopen[j] then
            aclose(
              writefile[j]);
          if mem[p].hh.b1 = 2 then
            writeopen[j] := false
          else if j < 16 then
          begin
            curname := mem[p + 1].hh.rh;
            curarea := mem[p + 2].hh.lh;
            curext := mem[p + 2].hh.rh;
            if curext = 338 then
              curext := 790;
            packfilename(curname, curarea, curext);
            while not aopenout(writefile[j]) do
              promptfilename(1299, 790);
            writeopen[j] := true;
          end;
        end;
      end{:1374}
;
    3: specialout(p);
    4: ;
    others: confusion(1298)
  end;
end;
