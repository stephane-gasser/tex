procedure newhyphexceptions;
label
  21, 10, 40, 45;
var
  n: 0..64;
  j: 0..64;
  h: hyphpointer;
  k: strnumber;
  p: halfword;
  q: halfword;
  s, t: strnumber;
  u, v: poolpointer;
begin
  scanleftbrace;
  if eqtb[5313].int <= 0 then
    curlang := 0
  else if eqtb[5313].int > 255 then
    curlang := 0
  else
    curlang := eqtb[5313].int;
  {935:}
n := 0;
  p := 0;
  while true do
  begin
    getxtoken;
    21:
      case curcmd of
        11, 12, 68:{937:}
if curchr = 45 then{938:}

          begin
            if n < 63 then
            begin
              q := getavail;
              mem[q].hh.rh := p;
              mem[q].hh.lh := n;
              p := q;
            end;
          end{:938}

          else if eqtb[4239 + curchr].hh.rh = 0 then
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(944);
            end;
            begin
              helpptr := 2;
              helpline[1] := 945;
              helpline[0] := 946;
            end;
            error;
          end
          else if n < 63 then
          begin
            n := n + 1;
            hc[n] := eqtb[4239 + curchr].hh.rh;
          end{:937}
;
        16:
        begin
          scancharnum;
          curchr := curval;
          curcmd := 68;
          goto 21;
        end;
        10, 2:
        begin
          if n > 1 then{939:}

          begin
            n := n + 1;
            hc[n] := curlang;
            begin
              if poolptr + n > poolsize then
                overflow(257, poolsize - initpoolptr);
            end;
            h := 0;
            for j := 1 to n do
            begin
              h := (h + h + hc[j]) mod 307;
              begin
                strpool[poolptr] := hc[j];
                poolptr := poolptr + 1;
              end;
            end;
            s := makestring;
            {940:}
if hyphcount = 307 then
              overflow(947, 307);
            hyphcount := hyphcount + 1;
            while hyphword[h] <> 0 do
            begin
              {941:}
k := hyphword[h];
              if (strstart[k + 1] - strstart[k]) < (strstart[s + 1] - strstart[s]) then
                goto 40;
              if (strstart[k + 1] - strstart[k]) > (strstart[s + 1] - strstart[s]) then
                goto 45;
              u := strstart[k];
              v := strstart[s];
              repeat
                if strpool[u] < strpool[v] then
                  goto 40;
                if strpool[u] > strpool[v] then
                  goto 45;
                u := u + 1;
                v := v + 1;
              until u = strstart[k + 1];
            40:
              q := hyphlist[h];
              hyphlist[h] := p;
              p := q;
              t := hyphword[h];
              hyphword[h] := s;
              s := t;
            45:
              {:941}
;
              if h > 0 then
                h := h - 1
              else
                h := 307;
            end;
            hyphword[h] := s;
            hyphlist[h] := p{:940}
;
          end{:939}
;
          if curcmd = 2 then
            goto 10;
          n := 0;
          p := 0;
        end;
        others:{936:}

        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(680);
          end;
          printesc(940);
          print(941);
          begin
            helpptr := 2;
            helpline[1] := 942;
            helpline[0] := 943;
          end;
          error;
        end{:936}

      end;
  end{:935}
;
  10: ;
end;
