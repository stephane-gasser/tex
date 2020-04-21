procedure showcontext;
label
  30;
var
  oldsetting: 0..21;
  nn: integer;
  bottomline: boolean;
  {315:}
i: 0..bufsize;
  j: 0..bufsize;
  l: 0..halferrorline;
  m: integer;
  n: 0..errorline;
  p: integer;
  q: integer;
  {:315}
begin
  baseptr := inputptr;
  inputstack[baseptr] := curinput;
  nn := -1;
  bottomline := false;
  while true do
  begin
    curinput := inputstack[baseptr];
    if (curinput.statefield <> 0) then
      if (curinput.namefield > 17) or (baseptr = 0) then
        bottomline := true;
    if (baseptr = inputptr) or bottomline or (nn < eqtb[5317].int) then{312:}

    begin
      if (baseptr = inputptr) or (curinput.statefield <> 0) or (curinput.indexfield <> 3) or (curinput.locfield <> 0) then
      begin
        tally := 0;
        oldsetting := selector;
        if curinput.statefield <> 0 then
        begin
          {313:}
if curinput.namefield <= 17 then
            if (curinput.namefield = 0) then
              if baseptr = 0 then
                printnl(574)
              else
                printnl(
                  575)
            else
            begin
              printnl(576);
              if curinput.namefield = 17 then
                printchar(42)
              else
                printint(curinput.namefield - 1);
              printchar(62);
            end
          else
          begin
            printnl(577);
            printint(line);
          end;
          printchar(32){:313}
;{318:}

          begin
            l := tally;
            tally := 0;
            selector := 20;
            trickcount := 1000000;
          end;
          if buffer[curinput.limitfield] = eqtb[5311].int then
            j := curinput.limitfield
          else
            j := curinput.limitfield + 1;
          if j > 0 then
            for i := curinput.startfield to j - 1 do
            begin
              if i = curinput.locfield then
              begin
                firstcount := tally;
                trickcount := tally + 1 + errorline - halferrorline;
                if trickcount < errorline then
                  trickcount := errorline;
              end;
              print(buffer[i]);
            end{:318}
;
        end
        else
        begin
          {314:}
case curinput.indexfield of
            0: printnl(578);
            1, 2: printnl(579);
            3: if curinput.locfield = 0 then
                printnl(580)
              else
                printnl(581);
            4: printnl(582);
            5:
            begin
              println;
              printcs(curinput.namefield);
            end;
            6: printnl(583);
            7: printnl(584);
            8: printnl(585);
            9: printnl(586);
            10: printnl(587);
            11: printnl(588);
            12: printnl(589);
            13: printnl(590);
            14: printnl(591);
            15: printnl(592);
            others: printnl(63)
          end{:314}
;
          {319:}
begin
            l := tally;
            tally := 0;
            selector := 20;
            trickcount := 1000000;
          end;
          if curinput.indexfield < 5 then
            showtokenlist(curinput.startfield, curinput.locfield, 100000)
          else
            showtokenlist(mem[curinput.startfield].hh.rh,
              curinput.locfield, 100000){:319}
;
        end;
        selector := oldsetting;
        {317:}
if trickcount = 1000000 then
        begin
          firstcount := tally;
          trickcount := tally + 1 + errorline - halferrorline;
          if trickcount < errorline then
            trickcount := errorline;
        end;
        if tally < trickcount then
          m := tally - firstcount
        else
          m := trickcount - firstcount;
        if l + firstcount <= halferrorline then
        begin
          p := 0;
          n := l + firstcount;
        end
        else
        begin
          print(277);
          p := l + firstcount - halferrorline + 3;
          n := halferrorline;
        end;
        for q := p to firstcount - 1 do
          printchar(trickbuf[q mod errorline]);
        println;
        for q := 1 to n do
          printchar(32);
        if m + n <= errorline then
          p := firstcount + m
        else
          p := firstcount + (errorline - n - 3);
        for q := firstcount to p - 1 do
          printchar(trickbuf[q mod errorline]);
        if m + n > errorline then
          print(277){:317}
;
        nn := nn + 1;
      end;
    end{:312}

    else if nn = eqtb[5317].int then
    begin
      printnl(277);
      nn := nn + 1;
    end;
    if bottomline then
      goto 30;
    baseptr := baseptr - 1;
  end;
  30:
    curinput := inputstack[inputptr];
end;
