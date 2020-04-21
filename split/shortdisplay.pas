procedure shortdisplay(p: integer);
var
  n: integer;
begin
  while p > memmin do
  begin
    if (p >= himemmin) then
    begin
      if p <= memend then
      begin
        if mem[p].hh.b0 <> fontinshortdisplay then
        begin
          if (mem[p].hh.b0 < 0) or (mem[p].hh.b0 > fontmax) then
            printchar(42)
          else
            {267:}
printesc(hash[2624 + mem[p].hh.b0].rh){:267}
;
          printchar(32);
          fontinshortdisplay := mem[p].hh.b0;
        end;
        print(mem[p].hh.b1 - 0);
      end;
    end
    else
      {175:}
case mem[p].hh.b0 of
        0, 1, 3, 8, 4, 5, 13: print(308);
        2: printchar(124);
        10: if mem[p + 1].hh.lh <> 0 then
            printchar(32);
        9: printchar(36);
        6: shortdisplay(mem[p + 1].hh.rh);
        7:
        begin
          shortdisplay(mem[p + 1].hh.lh);
          shortdisplay(mem[p + 1].hh.rh);
          n := mem[p].hh.b1;
          while n > 0 do
          begin
            if mem[p].hh.rh <> 0 then
              p := mem[p].hh.rh;
            n := n - 1;
          end;
        end;
        others: end{:175}
;
    p := mem[p].hh.rh;
  end;
end;
