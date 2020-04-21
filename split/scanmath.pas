procedure scanmath(p: halfword);
label
  20, 21, 10;
var
  c: integer;
begin
  20:
      {404:}
repeat
      getxtoken;
    until (curcmd <> 10) and (curcmd <> 0){:404}
;
  21:
    case curcmd of
      11, 12, 68:
      begin
        c := eqtb[5007 + curchr].hh.rh - 0;
        if c = 32768 then
        begin{1152:}

          begin
            curcs := curchr + 1;
            curcmd := eqtb[curcs].hh.b0;
            curchr := eqtb[curcs].hh.rh;
            xtoken;
            backinput;
          end{:1152}
;
          goto 20;
        end;
      end;
      16:
      begin
        scancharnum;
        curchr := curval;
        curcmd := 68;
        goto 21;
      end;
      17:
      begin
        scanfifteenbitint;
        c := curval;
      end;
      69: c := curchr;
      15:
      begin
        scantwentysevenbitint;
        c := curval div 4096;
      end;
      others:{1153:}

      begin
        backinput;
        scanleftbrace;
        savestack[saveptr + 0].int := p;
        saveptr := saveptr + 1;
        pushmath(9);
        goto 10;
      end{:1153}

    end;
  mem[p].hh.rh := 1;
  mem[p].hh.b1 := c mod 256 + 0;
  if (c >= 28672) and ((eqtb[5307].int >= 0) and (eqtb[5307].int < 16)) then
    mem[p].hh.b0 := eqtb[5307].int
  else
    mem[p].hh.b0 := (c div 256) mod 16;
  10: ;
end;
