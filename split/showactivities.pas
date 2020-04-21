procedure showactivities;
var
  p: 0..nestsize;
  m: -203..203;
  a: memoryword;
  q, r: halfword;
  t: integer;
begin
  nest[nestptr] := curlist;
  printnl(338);
  println;
  for p := nestptr downto 0 do
  begin
    m := nest[p].modefield;
    a := nest[p].auxfield;
    printnl(363);
    printmode(m);
    print(364);
    printint(abs(nest[p].mlfield));
    if m = 102 then
      if nest[p].pgfield <> 8585216 then
      begin
        print(365);
        printint(nest[p].pgfield mod 65536);
        print(366);
        printint(nest[p].pgfield div 4194304);
        printchar(44);
        printint((nest[p].pgfield div 65536) mod 64);
        printchar(41);
      end;
    if nest[p].mlfield < 0 then
      print(367);
    if p = 0 then
    begin
      {986:}
if 29998 <> pagetail then
      begin
        printnl(979);
        if outputactive then
          print(980);
        showbox(mem[29998].hh.rh);
        if pagecontents > 0 then
        begin
          printnl(981);
          printtotals;
          printnl(982);
          printscaled(pagesofar[0]);
          r := mem[30000].hh.rh;
          while r <> 30000 do
          begin
            println;
            printesc(330);
            t := mem[r].hh.b1 - 0;
            printint(t);
            print(983);
            if eqtb[5318 + t].int = 1000 then
              t := mem[r + 3].int
            else
              t := xovern(mem[r + 3].int, 1000) * eqtb[5318 + t].int;
            printscaled(t);
            if mem[r].hh.b0 = 1 then
            begin
              q := 29998;
              t := 0;
              repeat
                q := mem[q].hh.rh;
                if (mem[q].hh.b0 = 3) and (mem[q].hh.b1 = mem[r].hh.b1) then
                  t := t + 1;
              until q = mem[r + 1].hh.lh;
              print(984);
              printint(t);
              print(985);
            end;
            r := mem[r].hh.rh;
          end;
        end;
      end{:986}
;
      if mem[29999].hh.rh <> 0 then
        printnl(368);
    end;
    showbox(mem[nest[p].headfield].hh.rh);
    {219:}
case abs(m) div (101) of
      0:
      begin
        printnl(369);
        if a.int <= -65536000 then
          print(370)
        else
          printscaled(a.int);
        if nest[p].pgfield <> 0 then
        begin
          print(371);
          printint(nest[p].pgfield);
          print(372);
          if nest[p].pgfield <> 1 then
            printchar(115);
        end;
      end;
      1:
      begin
        printnl(373);
        printint(a.hh.lh);
        if m > 0 then
          if a.hh.rh > 0 then
          begin
            print(374);
            printint(a.hh.rh);
          end;
      end;
      2: if a.int <> 0 then
        begin
          print(375);
          showbox(a.int);
        end;
    end{:219}
;
  end;
end;
