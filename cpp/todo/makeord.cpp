#include "makeord.h"
void makeord(halfword q)
label
  20, 10;
var
  a: integer;
  p, r: halfword;
begin
  20:
    if mem[q + 3].hh.rh = 0 then
      if mem[q + 2].hh.rh = 0 then
        if mem[q + 1].hh.rh = 1 then
        begin
          p := mem[q].hh.rh;
          if p <> 0 then
            if (mem[p].hh.b0 >= 16) and (mem[p].hh.b0 <= 22) then
              if mem[p + 1].hh.rh = 1 then
                if mem[p + 1].hh.b0 = mem[q + 1].hh.b0 then
                begin
                  mem[q + 1].hh.rh := 4;
                  fetch(q + 1);
                  if ((curi.b2 - 0) mod 4) = 1 then
                  begin
                    a := ligkernbase[curf] + curi.b3;
                    curc := mem[p + 1].hh.b1;
                    curi := fontinfo[a].qqqq;
                    if curi.b0 > 128 then
                    begin
                      a := ligkernbase[curf] + 256 * curi.b2 + curi.b3 + 32768 - 256 * (128);
                      curi := fontinfo[a].qqqq;
                    end;
                    while true do
                    begin
                      {753:}
if curi.b1 = curc then
                        if curi.b0 <= 128 then
                          if curi.b2 >= 128 then
                          begin
                            p := newkern(fontinfo[kernbase[curf] + 256 * curi.b2 + curi.b3].int);
                            mem[p].hh.rh := mem[q].hh.rh;
                            mem[q].hh.rh := p;
                            goto 10;
                          end
                          else
                          begin
                            begin
                              if interrupt <> 0 then
                                pauseforinstructions;
                            end;
                            case curi.b2 of
                              1, 5: mem[q + 1].hh.b1 := curi.b3;
                              2, 6: mem[p + 1].hh.b1 := curi.b3;
                              3, 7, 11:
                              begin
                                r := newnoad;
                                mem[r + 1].hh.b1 := curi.b3;
                                mem[r + 1].hh.b0 := mem[q + 1].hh.b0;
                                mem[q].hh.rh := r;
                                mem[r].hh.rh := p;
                                if curi.b2 < 11 then
                                  mem[r + 1].hh.rh := 1
                                else
                                  mem[r + 1].hh.rh := 4;
                              end;
                              others:
                              begin
                                mem[q].hh.rh := mem[p].hh.rh;
                                mem[q + 1].hh.b1 := curi.b3;
                                mem[q + 3] := mem[p + 3];
                                mem[q + 2] := mem[p + 2];
                                freenode(p, 4);
                              end
                            end;
                            if curi.b2 > 3 then
                              goto 10;
                            mem[q + 1].hh.rh := 1;
                            goto 20;
                          end{:753}
;
                      if curi.b0 >= 128 then
                        goto 10;
                      a := a + curi.b0 + 1;
                      curi := fontinfo[a].qqqq;
                    end;
                  end;
                end;
        end;
  10: ;
end;
