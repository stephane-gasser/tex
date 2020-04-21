procedure hlistout;
label
  21, 13, 14, 15;
var
  baseline: scaled;
  leftedge: scaled;
  saveh, savev: scaled;
  thisbox: halfword;
  gorder: glueord;
  gsign: 0..2;
  p: halfword;
  saveloc: integer;
  leaderbox: halfword;
  leaderwd: scaled;
  lx: scaled;
  outerdoingleaders: boolean;
  edge: scaled;
  gluetemp: real;
  curglue: real;
  curg: scaled;
begin
  curg := 0;
  curglue := 0.0;
  thisbox := tempptr;
  gorder := mem[thisbox + 5].hh.b1;
  gsign := mem[thisbox + 5].hh.b0;
  p := mem[thisbox + 5].hh.rh;
  curs := curs + 1;
  if curs > 0 then
  begin
    dvibuf[dviptr] := 141;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
  if curs > maxpush then
    maxpush := curs;
  saveloc := dvioffset + dviptr;
  baseline := curv;
  leftedge := curh;
  while p <> 0 do
    {620:}
21:
      if (p >= himemmin) then
      begin
        if curh <> dvih then
        begin
          movement(curh - dvih, 143);
          dvih := curh;
        end;
        if curv <> dviv then
        begin
          movement(curv - dviv, 157);
          dviv := curv;
        end;
        repeat
          f := mem[p].hh.b0;
          c := mem[p].hh.b1;
          if f <> dvif then{621:}

          begin
            if not fontused[f] then
            begin
              dvifontdef(f);
              fontused[f] := true;
            end;
            if f <= 64 then
            begin
              dvibuf[dviptr] := f + 170;
              dviptr := dviptr + 1;
              if dviptr = dvilimit then
                dviswap;
            end
            else
            begin
              begin
                dvibuf[dviptr] := 235;
                dviptr := dviptr + 1;
                if dviptr = dvilimit then
                  dviswap;
              end;
              begin
                dvibuf[dviptr] := f - 1;
                dviptr := dviptr + 1;
                if dviptr = dvilimit then
                  dviswap;
              end;
            end;
            dvif := f;
          end{:621}
;
          if c >= 128 then
          begin
            dvibuf[dviptr] := 128;
            dviptr := dviptr + 1;
            if dviptr = dvilimit then
              dviswap;
          end;
          begin
            dvibuf[dviptr] := c - 0;
            dviptr := dviptr + 1;
            if dviptr = dvilimit then
              dviswap;
          end;
          curh := curh + fontinfo[widthbase[f] + fontinfo[charbase[f] + c].qqqq.b0].int;
          p := mem[p].hh.rh;
        until not (p >= himemmin);
        dvih := curh;
      end
      else{622:}

      begin
        case mem[p].hh.b0 of
          0, 1:{623:}
if mem[p + 5].hh.rh = 0 then
              curh := curh + mem[p + 1].int
            else
            begin
              saveh := dvih;
              savev := dviv;
              curv := baseline + mem[p + 4].int;
              tempptr := p;
              edge := curh;
              if mem[p].hh.b0 = 1 then
                vlistout
              else
                hlistout;
              dvih := saveh;
              dviv := savev;
              curh := edge + mem[p + 1].int;
              curv := baseline;
            end{:623}
;
          2:
          begin
            ruleht := mem[p + 3].int;
            ruledp := mem[p + 2].int;
            rulewd := mem[p + 1].int;
            goto 14;
          end;
          8:{1367:}
outwhat(p){:1367}
;
          10:{625:}

          begin
            g := mem[p + 1].hh.lh;
            rulewd := mem[g + 1].int - curg;
            if gsign <> 0 then
              if gsign = 1 then
              begin
                if mem[g].hh.b0 = gorder then
                begin
                  curglue := curglue + mem[g + 2].int;
                  gluetemp := mem[thisbox + 6].gr * curglue;
                  if gluetemp > 1000000000.0 then
                    gluetemp := 1000000000.0
                  else if gluetemp < -1000000000.0 then
                    gluetemp := -1000000000.0;
                  curg := round(gluetemp);
                end;
              end
              else if mem[g].hh.b1 = gorder then
              begin
                curglue := curglue - mem[g + 3].int;
                gluetemp := mem[thisbox + 6].gr * curglue;
                if gluetemp > 1000000000.0 then
                  gluetemp := 1000000000.0
                else if gluetemp < -1000000000.0 then
                  gluetemp := -1000000000.0;
                curg := round(gluetemp);
              end;
            rulewd := rulewd + curg;
            if mem[p].hh.b1 >= 100 then{626:}

            begin
              leaderbox := mem[p + 1].hh.rh;
              if mem[leaderbox].hh.b0 = 2 then
              begin
                ruleht := mem[leaderbox + 3].int;
                ruledp := mem[leaderbox + 2].int;
                goto 14;
              end;
              leaderwd := mem[leaderbox + 1].int;
              if (leaderwd > 0) and (rulewd > 0) then
              begin
                rulewd := rulewd + 10;
                edge := curh + rulewd;
                lx := 0;
                {627:}
if mem[p].hh.b1 = 100 then
                begin
                  saveh := curh;
                  curh := leftedge + leaderwd * ((curh - leftedge) div leaderwd);
                  if curh < saveh then
                    curh := curh + leaderwd;
                end
                else
                begin
                  lq := rulewd div leaderwd;
                  lr := rulewd mod leaderwd;
                  if mem[p].hh.b1 = 101 then
                    curh := curh + (lr div 2)
                  else
                  begin
                    lx := lr div (lq + 1);
                    curh := curh + ((lr - (lq - 1) * lx) div 2);
                  end;
                end{:627}
;
                while curh + leaderwd <= edge do{628:}

                begin
                  curv := baseline + mem[leaderbox + 4].int;
                  if curv <> dviv then
                  begin
                    movement(curv - dviv, 157);
                    dviv := curv;
                  end;
                  savev := dviv;
                  if curh <> dvih then
                  begin
                    movement(curh - dvih, 143);
                    dvih := curh;
                  end;
                  saveh := dvih;
                  tempptr := leaderbox;
                  outerdoingleaders := doingleaders;
                  doingleaders := true;
                  if mem[leaderbox].hh.b0 = 1 then
                    vlistout
                  else
                    hlistout;
                  doingleaders := outerdoingleaders;
                  dviv := savev;
                  dvih := saveh;
                  curv := baseline;
                  curh := saveh + leaderwd + lx;
                end{:628}
;
                curh := edge - 10;
                goto 15;
              end;
            end{:626}
;
            goto 13;
          end{:625}
;
          11, 9: curh := curh + mem[p + 1].int;
          6:{652:}

          begin
            mem[29988] := mem[p + 1];
            mem[29988].hh.rh := mem[p].hh.rh;
            p := 29988;
            goto 21;
          end{:652}
;
          others: end;
        goto 15;
      14:
        {624:}
if (ruleht = -1073741824) then
          ruleht := mem[thisbox + 3].int;
        if (ruledp = -1073741824) then
          ruledp := mem[thisbox + 2].int;
        ruleht := ruleht + ruledp;
        if (ruleht > 0) and (rulewd > 0) then
        begin
          if curh <> dvih then
          begin
            movement(
            curh - dvih, 143);
            dvih := curh;
          end;
          curv := baseline + ruledp;
          if curv <> dviv then
          begin
            movement(curv - dviv, 157);
            dviv := curv;
          end;
          begin
            dvibuf[dviptr] := 132;
            dviptr := dviptr + 1;
            if dviptr = dvilimit then
              dviswap;
          end;
          dvifour(ruleht);
          dvifour(rulewd);
          curv := baseline;
          dvih := dvih + rulewd;
        end{:624}
;
      13:
        curh := curh + rulewd;
      15:
        p := mem[p].hh.rh;
      end{:622}
{:620}
;
  prunemovements(saveloc);
  if curs > 0 then
    dvipop(saveloc);
  curs := curs - 1;
end;

