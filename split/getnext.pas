procedure getnext;
label
  20, 25, 21, 26, 40, 10;
var
  k: 0..bufsize;
  t: halfword;
  cat: 0..15;
  c, cc: ASCIIcode;
  d: 2..3;
begin
  20:
    curcs := 0;
  if curinput.statefield <> 0 then{343:}

  begin
    25:
      if curinput.locfield <= curinput.limitfield then
      begin
        curchr := buffer[curinput.locfield];
        curinput.locfield := curinput.locfield + 1;
      21:
        curcmd := eqtb[3983 + curchr].hh.rh;
        {344:}
case curinput.statefield + curcmd of
          {345:}
10, 26, 42, 27, 43{:345}
: goto25;
          1, 17, 33:{354:}

          begin
            if curinput.locfield > curinput.limitfield then
              curcs := 513
            else
            begin
            26:
              k := curinput.locfield;
              curchr := buffer[k];
              cat := eqtb[3983 + curchr].hh.rh;
              k := k + 1;
              if cat = 11 then
                curinput.statefield := 17
              else if cat = 10 then
                curinput.
                statefield := 17
              else
                curinput.statefield := 1;
              if (cat = 11) and (k <= curinput.limitfield) then{356:}

              begin
                repeat
                  curchr :=
                    buffer[k];
                  cat := eqtb[3983 + curchr].hh.rh;
                  k := k + 1;
                until (cat <> 11) or (k > curinput.limitfield);
                {355:}
begin
                  if buffer[k] = curchr then
                    if cat = 7 then
                      if k < curinput.limitfield then
                      begin
                        c := buffer[k + 1];
                        if c < 128 then
                        begin
                          d := 2;
                          if (((c >= 48) and (c <= 57)) or ((c >= 97) and (c <= 102))) then
                            if k + 2 <= curinput.limitfield then
                            begin
                              cc := buffer[k + 2];
                              if (((cc >= 48) and (cc <= 57)) or ((cc >= 97) and (cc <= 102))) then
                                d := d + 1;
                            end;
                          if d > 2 then
                          begin
                            if c <= 57 then
                              curchr := c - 48
                            else
                              curchr := c - 87;
                            if cc <= 57 then
                              curchr := 16 * curchr + cc - 48
                            else
                              curchr := 16 * curchr + cc - 87;
                            buffer[k - 1] := curchr;
                          end
                          else if c < 64 then
                            buffer[k - 1] := c + 64
                          else
                            buffer[k - 1] := c - 64;
                          curinput.limitfield := curinput.limitfield - d;
                          First := First - d;
                          while k <= curinput.limitfield do
                          begin
                            buffer[k] := buffer[k + d];
                            k := k + 1;
                          end;
                          goto 26;
                        end;
                      end;
                end{:355}
;
                if cat <> 11 then
                  k := k - 1;
                if k > curinput.locfield + 1 then
                begin
                  curcs := idlookup(curinput.locfield, k - curinput.locfield);
                  curinput.locfield := k;
                  goto 40;
                end;
              end{:356}

              else{355:}
if buffer[k] = curchr then
                if cat = 7 then
                  if k < curinput.limitfield then
                  begin
                    c := buffer[k + 1];
                    if c < 128 then
                    begin
                      d := 2;
                      if (((c >= 48) and (c <= 57)) or ((c >= 97) and (c <= 102))) then
                        if k + 2 <= curinput.limitfield then
                        begin
                          cc := buffer[k + 2];
                          if (((cc >= 48) and (cc <= 57)) or ((cc >= 97) and (cc <= 102))) then
                            d := d + 1;
                        end;
                      if d > 2 then
                      begin
                        if c <= 57 then
                          curchr := c - 48
                        else
                          curchr := c - 87;
                        if cc <= 57 then
                          curchr := 16 * curchr + cc - 48
                        else
                          curchr := 16 * curchr + cc - 87;
                        buffer[k - 1] := curchr;
                      end
                      else if c < 64 then
                        buffer[k - 1] := c + 64
                      else
                        buffer[k - 1] := c - 64;
                      curinput.limitfield := curinput.limitfield - d;
                      First := First - d;
                      while k <= curinput.limitfield do
                      begin
                        buffer[k] := buffer[k + d];
                        k := k + 1;
                      end;
                      goto 26;
                    end;
                  end{:355}
;
              curcs := 257 + buffer[curinput.locfield];
              curinput.locfield := curinput.locfield + 1;
            end;
          40:
            curcmd := eqtb[curcs].hh.b0;
            curchr := eqtb[curcs].hh.rh;
            if curcmd >= 113 then
              checkoutervalidity;
          end{:354}
;
          14, 30, 46:{353:}

          begin
            curcs := curchr + 1;
            curcmd := eqtb[curcs].hh.b0;
            curchr := eqtb[curcs].hh.rh;
            curinput.statefield := 1;
            if curcmd >= 113 then
              checkoutervalidity;
          end{:353}
;
          8, 24, 40:{352:}

          begin
            if curchr = buffer[curinput.locfield] then
              if curinput.locfield < curinput.limitfield then
              begin
                c := buffer[curinput.locfield + 1];
                if c < 128 then
                begin
                  curinput.locfield := curinput.locfield + 2;
                  if (((c >= 48) and (c <= 57)) or ((c >= 97) and (c <= 102))) then
                    if curinput.locfield <= curinput.limitfield then
                    begin
                      cc := buffer[curinput.locfield];
                      if (((cc >= 48) and (cc <= 57)) or ((cc >= 97) and (cc <= 102))) then
                      begin
                        curinput.
                        locfield := curinput.locfield + 1;
                        if c <= 57 then
                          curchr := c - 48
                        else
                          curchr := c - 87;
                        if cc <= 57 then
                          curchr := 16 * curchr + cc - 48
                        else
                          curchr := 16 * curchr + cc - 87;
                        goto 21;
                      end;
                    end;
                  if c < 64 then
                    curchr := c + 64
                  else
                    curchr := c - 64;
                  goto 21;
                end;
              end;
            curinput.statefield := 1;
          end{:352}
;
          16, 32, 48:{346:}

          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(613);
            end;
            begin
              helpptr := 2;
              helpline[1] := 614;
              helpline[0] := 615;
            end;
            deletionsallowed := false;
            error;
            deletionsallowed := true;
            goto 20;
          end{:346}
;
          {347:}
11:{349:}

          begin
            curinput.statefield := 17;
            curchr := 32;
          end{:349}
;
          6:{348:}

          begin
            curinput.locfield := curinput.limitfield + 1;
            curcmd := 10;
            curchr := 32;
          end{:348}
;
          22, 15, 31, 47:{350:}

          begin
            curinput.locfield := curinput.limitfield + 1;
            goto 25;
          end{:350}
;
          38:{351:}

          begin
            curinput.locfield := curinput.limitfield + 1;
            curcs := parloc;
            curcmd := eqtb[curcs].hh.b0;
            curchr := eqtb[curcs].hh.rh;
            if curcmd >= 113 then
              checkoutervalidity;
          end{:351}
;
          2: alignstate := alignstate + 1;
          18, 34:
          begin
            curinput.statefield := 1;
            alignstate := alignstate + 1;
          end;
          3: alignstate := alignstate - 1;
          19, 35:
          begin
            curinput.statefield := 1;
            alignstate := alignstate - 1;
          end;
          20, 21, 23, 25, 28, 29, 36, 37, 39, 41, 44, 45: curinput.statefield := 1;
          {:347}
others: end{:344}
;
      end
      else
      begin
        curinput.statefield := 33;
        {360:}
if curinput.namefield > 17 then{362:}

        begin
          line := line + 1;
          First := curinput.startfield;
          if not forceeof then
            if inputln(inputfile[curinput.indexfield], true) then
              firmuptheline
            else
              forceeof := true;
          if forceeof then
          begin
            printchar(41);
            openparens := openparens - 1;
            break(termout);
            forceeof := false;
            endfilereading;
            checkoutervalidity;
            goto 20;
          end;
          if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
            curinput.limitfield :=
              curinput.limitfield - 1
          else
            buffer[curinput.limitfield] := eqtb[5311].int;
          First := curinput.limitfield + 1;
          curinput.locfield := curinput.startfield;
        end{:362}

        else
        begin
          if not (curinput.namefield = 0) then
          begin
            curcmd := 0;
            curchr := 0;
            goto 10;
          end;
          if inputptr > 0 then
          begin
            endfilereading;
            goto 20;
          end;
          if selector < 18 then
            openlogfile;
          if interaction > 1 then
          begin
            if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
              curinput.limitfield := curinput.limitfield + 1;
            if curinput.limitfield = curinput.startfield then
              printnl(616);
            println;
            First := curinput.startfield;
            begin
              ;
              print(42);
              terminput;
            end;
            curinput.limitfield := last;
            if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
              curinput.limitfield :=
                curinput.limitfield - 1
            else
              buffer[curinput.limitfield] := eqtb[5311].int;
            First := curinput.limitfield + 1;
            curinput.locfield := curinput.startfield;
          end
          else
            fatalerror(617);
        end{:360}
;
        begin
          if interrupt <> 0 then
            pauseforinstructions;
        end;
        goto 25;
      end;
  end{:343}

  else{357:}
if curinput.locfield <> 0 then
  begin
    t := mem[curinput.locfield].hh.lh;
    curinput.locfield := mem[curinput.locfield].hh.rh;
    if t >= 4095 then
    begin
      curcs := t - 4095;
      curcmd := eqtb[curcs].hh.b0;
      curchr := eqtb[curcs].hh.rh;
      if curcmd >= 113 then
        if curcmd = 116 then{358:}

        begin
          curcs := mem[curinput.locfield].hh.lh - 4095;
          curinput.locfield := 0;
          curcmd := eqtb[curcs].hh.b0;
          curchr := eqtb[curcs].hh.rh;
          if curcmd > 100 then
          begin
            curcmd := 0;
            curchr := 257;
          end;
        end{:358}

        else
          checkoutervalidity;
    end
    else
    begin
      curcmd := t div 256;
      curchr := t mod 256;
      case curcmd of
        1: alignstate := alignstate + 1;
        2: alignstate := alignstate - 1;
        5:{359:}

        begin
          begintokenlist(paramstack[curinput.limitfield + curchr - 1], 0);
          goto 20;
        end{:359}
;
        others: end;
    end;
  end
  else
  begin
    endtokenlist;
    goto 20;
  end{:357}
;
  {342:}
if curcmd <= 5 then
    if curcmd >= 4 then
      if alignstate = 0 then{789:}

      begin
        if (scannerstatus = 4) or (curalign = 0) then
          fatalerror(595);
        curcmd := mem[curalign + 5].hh.lh;
        mem[curalign + 5].hh.lh := curchr;
        if curcmd = 63 then
          begintokenlist(29990, 2)
        else
          begintokenlist(mem[curalign + 2].int, 2);
        alignstate := 1000000;
        goto 20;
      end{:789}
{:342}
;
  10: ;
end;
