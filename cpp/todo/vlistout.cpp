#include "vlistout.h"
void vlistout(void)
label
  13, 14, 15;
var
  leftedge: scaled;
  topedge: scaled;
  saveh, savev: scaled;
  thisbox: halfword;
  gorder: glueord;
  gsign: 0..2;
  p: halfword;
  saveloc: integer;
  leaderbox: halfword;
  leaderht: scaled;
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
  leftedge := curh;
  curv := curv - mem[thisbox + 3].int;
  topedge := curv;
  while p <> 0 do{630:}

  begin
    if (p >= himemmin) then
      confusion(827)
    else{631:}

    begin
      case mem[p].hh.b0 of
        0, 1:{632:}
if mem[p + 5].hh.rh = 0 then
            curv := curv + mem[p + 3].int + mem[p + 2].int
          else
          begin
            curv := curv + mem[p + 3].int;
            if curv <> dviv then
            begin
              movement(curv - dviv, 157);
              dviv := curv;
            end;
            saveh := dvih;
            savev := dviv;
            curh := leftedge + mem[p + 4].int;
            tempptr := p;
            if mem[p].hh.b0 = 1 then
              vlistout
            else
              hlistout;
            dvih := saveh;
            dviv := savev;
            curv := savev + mem[p + 2].int;
            curh := leftedge;
          end{:632}
;
        2:
        begin
          ruleht := mem[p + 3].int;
          ruledp := mem[p + 2].int;
          rulewd := mem[p + 1].int;
          goto 14;
        end;
        8:{1366:}
outwhat(p){:1366}
;
        10:{634:}

        begin
          g := mem[p + 1].hh.lh;
          ruleht := mem[g + 1].int - curg;
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
          ruleht := ruleht + curg;
          if mem[p].hh.b1 >= 100 then{635:}

          begin
            leaderbox := mem[p + 1].hh.rh;
            if mem[leaderbox].hh.b0 = 2 then
            begin
              rulewd := mem[leaderbox + 1].int;
              ruledp := 0;
              goto 14;
            end;
            leaderht := mem[leaderbox + 3].int + mem[leaderbox + 2].int;
            if (leaderht > 0) and (ruleht > 0) then
            begin
              ruleht := ruleht + 10;
              edge := curv + ruleht;
              lx := 0;
              {636:}
if mem[p].hh.b1 = 100 then
              begin
                savev := curv;
                curv := topedge + leaderht * ((curv - topedge) div leaderht);
                if curv < savev then
                  curv := curv + leaderht;
              end
              else
              begin
                lq := ruleht div leaderht;
                lr := ruleht mod leaderht;
                if mem[p].hh.b1 = 101 then
                  curv := curv + (lr div 2)
                else
                begin
                  lx := lr div (lq + 1);
                  curv := curv + ((lr - (lq - 1) * lx) div 2);
                end;
              end{:636}
;
              while curv + leaderht <= edge do{637:}

              begin
                curh := leftedge + mem[leaderbox + 4].int;
                if curh <> dvih then
                begin
                  movement(curh - dvih, 143);
                  dvih := curh;
                end;
                saveh := dvih;
                curv := curv + mem[leaderbox + 3].int;
                if curv <> dviv then
                begin
                  movement(curv - dviv, 157);
                  dviv := curv;
                end;
                savev := dviv;
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
                curh := leftedge;
                curv := savev - mem[leaderbox + 3].int + leaderht + lx;
              end{:637}
;
              curv := edge - 10;
              goto 15;
            end;
          end{:635}
;
          goto 13;
        end{:634}
;
        11: curv := curv + mem[p + 1].int;
        others: end;
      goto 15;
      14:
        {633:}
if (rulewd = -1073741824) then
          rulewd := mem[thisbox + 1].int;
      ruleht := ruleht + ruledp;
      curv := curv + ruleht;
      if (ruleht > 0) and (rulewd > 0) then
      begin
        if curh <> dvih then
        begin
          movement(
            curh - dvih, 143);
          dvih := curh;
        end;
        if curv <> dviv then
        begin
          movement(curv - dviv, 157);
          dviv := curv;
        end;
        begin
          dvibuf[dviptr] := 137;
          dviptr := dviptr + 1;
          if dviptr = dvilimit then
            dviswap;
        end;
        dvifour(ruleht);
        dvifour(rulewd);
      end;
      goto 15{:633}
;
      13:
        curv := curv + ruleht;
    end{:631}
;
    15:
      p := mem[p].hh.rh;
  end{:630}
;
  prunemovements(saveloc);
  if curs > 0 then
    dvipop(saveloc);
  curs := curs - 1;
end;
