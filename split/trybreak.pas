procedure trybreak(pi: integer; breaktype: smallnumber);
label
  10, 30, 31, 22, 60;
var
  r: halfword;
  prevr: halfword;
  oldl: halfword;
  nobreakyet: boolean;
  {830:}
prevprevr: halfword;
  s: halfword;
  q: halfword;
  v: halfword;
  t: integer;
  f: internalfontnumber;
  l: halfword;
  noderstaysactive: boolean;
  linewidth: scaled;
  fitclass: 0..3;
  b: halfword;
  d: integer;
  artificialdemerits: boolean;
  savelink: halfword;
  shortfall: scaled;
  {:830}
begin
  {831:}
if abs(pi) >= 10000 then
    if pi > 0 then
      goto 10
    else
      pi := -10000{:831}
;
  nobreakyet := true;
  prevr := 29993;
  oldl := 0;
  curactivewidth[1] := activewidth[1];
  curactivewidth[2] := activewidth[2];
  curactivewidth[3] := activewidth[3];
  curactivewidth[4] := activewidth[4];
  curactivewidth[5] := activewidth[5];
  curactivewidth[6] := activewidth[6];
  while true do
  begin
    22:
      r := mem[prevr].hh.rh;
    {832:}
if mem[r].hh.b0 = 2 then
    begin
      curactivewidth[1] := curactivewidth[1] + mem[r + 1].int;
      curactivewidth[2] := curactivewidth[2] + mem[r + 2].int;
      curactivewidth[3] := curactivewidth[3] + mem[r + 3].int;
      curactivewidth[4] := curactivewidth[4] + mem[r + 4].int;
      curactivewidth[5] := curactivewidth[5] + mem[r + 5].int;
      curactivewidth[6] := curactivewidth[6] + mem[r + 6].int;
      prevprevr := prevr;
      prevr := r;
      goto 22;
    end{:832}
;{835:}

    begin
      l := mem[r + 1].hh.lh;
      if l > oldl then
      begin
        if (minimumdemerits < 1073741823) and ((oldl <> easyline) or (r = 29993)) then{836:}

        begin
          if nobreakyet then{837:}

          begin
            nobreakyet :=
              false;
            breakwidth[1] := background[1];
            breakwidth[2] := background[2];
            breakwidth[3] := background[3];
            breakwidth[4] := background[4];
            breakwidth[5] := background[5];
            breakwidth[6] := background[6];
            s := curp;
            if breaktype > 0 then
              if curp <> 0 then{840:}

              begin
                t := mem[curp].hh.b1;
                v := curp;
                s := mem[curp + 1].hh.rh;
                while t > 0 do
                begin
                  t := t - 1;
                  v := mem[v].hh.rh;
                  {841:}
if (v >= himemmin) then
                  begin
                    f := mem[v].hh.b0;
                    breakwidth[1] := breakwidth[1] - fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[v].hh.b1].qqqq.b0].int;
                  end
                  else
                    case mem[v].hh.b0 of
                      6:
                      begin
                        f := mem[v + 1].hh.b0;
                        breakwidth[1] := breakwidth[1] - fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[v + 1].hh.b1].qqqq.b0].int;
                      end;
                      0, 1, 2, 11: breakwidth[1] := breakwidth[1] - mem[v + 1].int;
                      others: confusion(922)
                    end{:841}
;
                end;
                while s <> 0 do
                begin
                  {842:}
if (s >= himemmin) then
                  begin
                    f := mem[s].hh.b0;
                    breakwidth[1] := breakwidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s].hh.b1].qqqq.b0].int;
                  end
                  else
                    case mem[s].hh.b0 of
                      6:
                      begin
                        f := mem[s + 1].hh.b0;
                        breakwidth[1] := breakwidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s + 1].hh.b1].qqqq.b0].int;
                      end;
                      0, 1, 2, 11: breakwidth[1] := breakwidth[1] + mem[s + 1].int;
                      others: confusion(923)
                    end{:842}
;
                  s := mem[s].hh.rh;
                end;
                breakwidth[1] := breakwidth[1] + discwidth;
                if mem[curp + 1].hh.rh = 0 then
                  s := mem[v].hh.rh;
              end{:840}
;
            while s <> 0 do
            begin
              if (s >= himemmin) then
                goto 30;
              case mem[s].hh.b0 of
                10:{838:}

                begin
                  v := mem[s + 1].hh.lh;
                  breakwidth[1] := breakwidth[1] - mem[v + 1].int;
                  breakwidth[2 + mem[v].hh.b0] := breakwidth[2 + mem[v].hh.b0] - mem[v + 2].int;
                  breakwidth[6] := breakwidth[6] - mem[v + 3].int;
                end{:838}
;
                12: ;
                9: breakwidth[1] := breakwidth[1] - mem[s + 1].int;
                11: if mem[s].hh.b1 <> 1 then
                    goto 30
                  else
                    breakwidth[1] := breakwidth[1] - mem[s + 1].int;
                others: goto 30
              end;
              s := mem[s].hh.rh;
            end;
            30: ;
          end{:837}
;
          {843:}
if mem[prevr].hh.b0 = 2 then
          begin
            mem[prevr + 1].int := mem[prevr + 1].int - curactivewidth[1] + breakwidth[1];
            mem[prevr + 2].int := mem[prevr + 2].int - curactivewidth[2] + breakwidth[2];
            mem[prevr + 3].int := mem[prevr + 3].int - curactivewidth[3] + breakwidth[3];
            mem[prevr + 4].int := mem[prevr + 4].int - curactivewidth[4] + breakwidth[4];
            mem[prevr + 5].int := mem[prevr + 5].int - curactivewidth[5] + breakwidth[5];
            mem[prevr + 6].int := mem[prevr + 6].int - curactivewidth[6] + breakwidth[6];
          end
          else if prevr = 29993 then
          begin
            activewidth[1] := breakwidth[1];
            activewidth[2] := breakwidth[2];
            activewidth[3] := breakwidth[3];
            activewidth[4] := breakwidth[4];
            activewidth[5] := breakwidth[5];
            activewidth[6] := breakwidth[6];
          end
          else
          begin
            q := getnode(7);
            mem[q].hh.rh := r;
            mem[q].hh.b0 := 2;
            mem[q].hh.b1 := 0;
            mem[q + 1].int := breakwidth[1] - curactivewidth[1];
            mem[q + 2].int := breakwidth[2] - curactivewidth[2];
            mem[q + 3].int := breakwidth[3] - curactivewidth[3];
            mem[q + 4].int := breakwidth[4] - curactivewidth[4];
            mem[q + 5].int := breakwidth[5] - curactivewidth[5];
            mem[q + 6].int := breakwidth[6] - curactivewidth[6];
            mem[prevr].hh.rh := q;
            prevprevr := prevr;
            prevr := q;
          end{:843}
;
          if abs(eqtb[5279].int) >= 1073741823 - minimumdemerits then
            minimumdemerits := 1073741822
          else
            minimumdemerits := minimumdemerits + abs(eqtb[5279].int);
          for fitclass := 0 to 3 do
          begin
            if minimaldemerits[fitclass] <= minimumdemerits then{845:}

            begin
              q := getnode(2);
              mem[q].hh.rh := passive;
              passive := q;
              mem[q + 1].hh.rh := curp;
{passnumber:=passnumber+1;
mem[q].hh.lh:=passnumber;}
mem[q + 1].hh.lh := bestplace[fitclass];
              q := getnode(3);
              mem[q + 1].hh.rh := passive;
              mem[q + 1].hh.lh := bestplline[fitclass] + 1;
              mem[q].hh.b1 := fitclass;
              mem[q].hh.b0 := breaktype;
              mem[q + 2].int := minimaldemerits[fitclass];
              mem[q].hh.rh := r;
              mem[prevr].hh.rh := q;
              prevr := q;
{if eqtb[5295].int>0 then[846:]begin printnl(924);
printint(mem[passive].hh.lh);print(925);printint(mem[q+1].hh.lh-1);
printchar(46);printint(fitclass);if breaktype=1 then printchar(45);
print(926);printint(mem[q+2].int);print(927);
if mem[passive+1].hh.lh=0 then printchar(48)else printint(mem[mem[
passive+1].hh.lh].hh.lh);end[:846];}
end{:845}
;
            minimaldemerits[fitclass] := 1073741823;
          end;
          minimumdemerits := 1073741823;
          {844:}
if r <> 29993 then
          begin
            q := getnode(7);
            mem[q].hh.rh := r;
            mem[q].hh.b0 := 2;
            mem[q].hh.b1 := 0;
            mem[q + 1].int := curactivewidth[1] - breakwidth[1];
            mem[q + 2].int := curactivewidth[2] - breakwidth[2];
            mem[q + 3].int := curactivewidth[3] - breakwidth[3];
            mem[q + 4].int := curactivewidth[4] - breakwidth[4];
            mem[q + 5].int := curactivewidth[5] - breakwidth[5];
            mem[q + 6].int := curactivewidth[6] - breakwidth[6];
            mem[prevr].hh.rh := q;
            prevprevr := prevr;
            prevr := q;
          end{:844}
;
        end{:836}
;
        if r = 29993 then
          goto 10;
        {850:}
if l > easyline then
        begin
          linewidth := secondwidth;
          oldl := 65534;
        end
        else
        begin
          oldl := l;
          if l > lastspecialline then
            linewidth := secondwidth
          else if eqtb[3412].hh.rh = 0 then
            linewidth := firstwidth
          else
            linewidth := mem[eqtb[3412].hh.rh + 2 * l].int;
        end{:850}
;
      end;
    end{:835}
;{851:}

    begin
      artificialdemerits := false;
      shortfall := linewidth - curactivewidth[1];
      if shortfall > 0 then
        {852:}
if (curactivewidth[3] <> 0) or (curactivewidth[4] <> 0) or (curactivewidth[5] <> 0) then
        begin
          b := 0;
          fitclass := 2;
        end
        else
        begin
          if shortfall > 7230584 then
            if curactivewidth[2] < 1663497 then
            begin
              b := 10000;
              fitclass := 0;
              goto 31;
            end;
          b := badness(shortfall, curactivewidth[2]);
          if b > 12 then
            if b > 99 then
              fitclass := 0
            else
              fitclass := 1
          else
            fitclass := 2;
          31: ;
        end{:852}

      else{853:}

      begin
        if -shortfall > curactivewidth[6] then
          b := 10001
        else
          b := badness(-shortfall, curactivewidth[6]);
        if b > 12 then
          fitclass := 3
        else
          fitclass := 2;
      end{:853}
;
      if (b > 10000) or (pi = -10000) then{854:}

      begin
        if finalpass and (minimumdemerits = 1073741823) and (mem[r].hh.rh = 29993) and (prevr = 29993) then
          artificialdemerits := true
        else if b > threshold then
          goto 60;
        noderstaysactive := false;
      end{:854}

      else
      begin
        prevr := r;
        if b > threshold then
          goto 22;
        noderstaysactive := true;
      end;
      {855:}
if artificialdemerits then
        d := 0
      else{859:}

      begin
        d := eqtb[5265].int + b;
        if abs(d) >= 10000 then
          d := 100000000
        else
          d := d * d;
        if pi <> 0 then
          if pi > 0 then
            d := d + pi * pi
          else if pi > -10000 then
            d := d - pi * pi;
        if (breaktype = 1) and (mem[r].hh.b0 = 1) then
          if curp <> 0 then
            d := d + eqtb[5277].int
          else
            d := d + eqtb[5278].int;
        if abs(fitclass - mem[r].hh.b1) > 1 then
          d := d + eqtb[5279].int;
      end{:859}
;
{if eqtb[5295].int>0 then[856:]begin if printednode<>curp then[857:]
begin printnl(338);
if curp=0 then shortdisplay(mem[printednode].hh.rh)else begin savelink:=
mem[curp].hh.rh;mem[curp].hh.rh:=0;printnl(338);
shortdisplay(mem[printednode].hh.rh);mem[curp].hh.rh:=savelink;end;
printednode:=curp;end[:857];printnl(64);
if curp=0 then printesc(597)else if mem[curp].hh.b0<>10 then begin if
mem[curp].hh.b0=12 then printesc(531)else if mem[curp].hh.b0=7 then
printesc(349)else if mem[curp].hh.b0=11 then printesc(340)else printesc(
343);end;print(928);
if mem[r+1].hh.rh=0 then printchar(48)else printint(mem[mem[r+1].hh.rh].
hh.lh);print(929);if b>10000 then printchar(42)else printint(b);
print(930);printint(pi);print(931);
if artificialdemerits then printchar(42)else printint(d);end[:856];}

      d := d + mem[r + 2].int;
      if d <= minimaldemerits[fitclass] then
      begin
        minimaldemerits[fitclass] := d;
        bestplace[fitclass] := mem[r + 1].hh.rh;
        bestplline[fitclass] := l;
        if d < minimumdemerits then
          minimumdemerits := d;
      end{:855}
;
      if noderstaysactive then
        goto 22;
      60:
        {860:}
mem[prevr].hh.rh := mem[r].hh.rh;
      freenode(r, 3);
      if prevr = 29993 then{861:}

      begin
        r := mem[29993].hh.rh;
        if mem[r].hh.b0 = 2 then
        begin
          activewidth[1] := activewidth[1] + mem[r + 1].int;
          activewidth[2] := activewidth[2] + mem[r + 2].int;
          activewidth[3] := activewidth[3] + mem[r + 3].int;
          activewidth[4] := activewidth[4] + mem[r + 4].int;
          activewidth[5] := activewidth[5] + mem[r + 5].int;
          activewidth[6] := activewidth[6] + mem[r + 6].int;
          curactivewidth[1] := activewidth[1];
          curactivewidth[2] := activewidth[2];
          curactivewidth[3] := activewidth[3];
          curactivewidth[4] := activewidth[4];
          curactivewidth[5] := activewidth[5];
          curactivewidth[6] := activewidth[6];
          mem[29993].hh.rh := mem[r].hh.rh;
          freenode(r, 7);
        end;
      end{:861}

      else if mem[prevr].hh.b0 = 2 then
      begin
        r := mem[prevr].hh.rh;
        if r = 29993 then
        begin
          curactivewidth[1] := curactivewidth[1] - mem[prevr + 1].int;
          curactivewidth[2] := curactivewidth[2] - mem[prevr + 2].int;
          curactivewidth[3] := curactivewidth[3] - mem[prevr + 3].int;
          curactivewidth[4] := curactivewidth[4] - mem[prevr + 4].int;
          curactivewidth[5] := curactivewidth[5] - mem[prevr + 5].int;
          curactivewidth[6] := curactivewidth[6] - mem[prevr + 6].int;
          mem[prevprevr].hh.rh := 29993;
          freenode(prevr, 7);
          prevr := prevprevr;
        end
        else if mem[r].hh.b0 = 2 then
        begin
          curactivewidth[1] := curactivewidth[1] + mem[r + 1].int;
          curactivewidth[2] := curactivewidth[2] + mem[r + 2].int;
          curactivewidth[3] := curactivewidth[3] + mem[r + 3].int;
          curactivewidth[4] := curactivewidth[4] + mem[r + 4].int;
          curactivewidth[5] := curactivewidth[5] + mem[r + 5].int;
          curactivewidth[6] := curactivewidth[6] + mem[r + 6].int;
          mem[prevr + 1].int := mem[prevr + 1].int + mem[r + 1].int;
          mem[prevr + 2].int := mem[prevr + 2].int + mem[r + 2].int;
          mem[prevr + 3].int := mem[prevr + 3].int + mem[r + 3].int;
          mem[prevr + 4].int := mem[prevr + 4].int + mem[r + 4].int;
          mem[prevr + 5].int := mem[prevr + 5].int + mem[r + 5].int;
          mem[prevr + 6].int := mem[prevr + 6].int + mem[r + 6].int;
          mem[prevr].hh.rh := mem[r].hh.rh;
          freenode(r, 7);
        end;
      end{:860}
;
    end{:851}
;
  end;
  10: ;{[858:]if curp=printednode then if curp<>0 then if mem[curp].hh.b0=7
then begin t:=mem[curp].hh.b1;while t>0 do begin t:=t-1;
printednode:=mem[printednode].hh.rh;end;end[:858]}

end;

