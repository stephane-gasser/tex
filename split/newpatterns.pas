procedure newpatterns;
label
  30, 31;
var
  k, l: 0..64;
  digitsensed: boolean;
  v: quarterword;
  p, q: triepointer;
  firstchild: boolean;
  c: ASCIIcode;
begin
  if trienotready then
  begin
    if eqtb[5313].int <= 0 then
      curlang := 0
    else if eqtb[5313].int > 255 then
      curlang := 0
    else
      curlang := eqtb[5313].int;
    scanleftbrace;
    {961:}
k := 0;
    hyf[0] := 0;
    digitsensed := false;
    while true do
    begin
      getxtoken;
      case curcmd of
        11, 12:{962:}
if digitsensed or (curchr < 48) or (curchr > 57) then
          begin
            if curchr = 46 then
              curchr := 0
            else
            begin
              curchr := eqtb[4239 + curchr].hh.rh;
              if curchr = 0 then
              begin
                begin
                  if interaction = 3 then;
                  printnl(262);
                  print(956);
                end;
                begin
                  helpptr := 1;
                  helpline[0] := 955;
                end;
                error;
              end;
            end;
            if k < 63 then
            begin
              k := k + 1;
              hc[k] := curchr;
              hyf[k] := 0;
              digitsensed := false;
            end;
          end
          else if k < 63 then
          begin
            hyf[k] := curchr - 48;
            digitsensed := true;
          end{:962}
;
        10, 2:
        begin
          if k > 0 then{963:}

          begin
            {965:}
if hc[1] = 0 then
              hyf[0] := 0;
            if hc[k] = 0 then
              hyf[k] := 0;
            l := k;
            v := 0;
            while true do
            begin
              if hyf[l] <> 0 then
                v := newtrieop(k - l, hyf[l], v);
              if l > 0 then
                l := l - 1
              else
                goto 31;
            end;
            31:
            {:965}
;
            q := 0;
            hc[0] := curlang;
            while l <= k do
            begin
              c := hc[l];
              l := l + 1;
              p := triel[q];
              firstchild := true;
              while (p > 0) and (c > triec[p]) do
              begin
                q := p;
                p := trier[q];
                firstchild := false;
              end;
              if (p = 0) or (c < triec[p]) then{964:}

              begin
                if trieptr = triesize then
                  overflow(
                    950, triesize);
                trieptr := trieptr + 1;
                trier[trieptr] := p;
                p := trieptr;
                triel[p] := 0;
                if firstchild then
                  triel[q] := p
                else
                  trier[q] := p;
                triec[p] := c;
                trieo[p] := 0;
              end{:964}
;
              q := p;
            end;
            if trieo[q] <> 0 then
            begin
              begin
                if interaction = 3 then;
                printnl(262);
                print(957);
              end;
              begin
                helpptr := 1;
                helpline[0] := 955;
              end;
              error;
            end;
            trieo[q] := v;
          end{:963}
;
          if curcmd = 2 then
            goto 30;
          k := 0;
          hyf[0] := 0;
          digitsensed := false;
        end;
        others:
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(954);
          end;
          printesc(952);
          begin
            helpptr := 1;
            helpline[0] := 955;
          end;
          error;
        end
      end;
    end;
    30:
    {:961}
;
  end
  else
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(951);
    end;
    printesc(952);
    begin
      helpptr := 1;
      helpline[0] := 953;
    end;
    error;
    mem[29988].hh.rh := scantoks(false, false);
    flushlist(defref);
  end;
end;
