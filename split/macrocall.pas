procedure macrocall;
label
  10, 22, 30, 31, 40;
var
  r: halfword;
  p: halfword;
  q: halfword;
  s: halfword;
  t: halfword;
  u, v: halfword;
  rbraceptr: halfword;
  n: smallnumber;
  unbalance: halfword;
  m: halfword;
  refcount: halfword;
  savescannerstatus: smallnumber;
  savewarningindex: halfword;
  matchchr: ASCIIcode;
begin
  savescannerstatus := scannerstatus;
  savewarningindex := warningindex;
  warningindex := curcs;
  refcount := curchr;
  r := mem[refcount].hh.rh;
  n := 0;
  if eqtb[5293].int > 0 then{401:}

  begin
    begindiagnostic;
    println;
    printcs(warningindex);
    tokenshow(refcount);
    enddiagnostic(false);
  end{:401}
;
  if mem[r].hh.lh <> 3584 then{391:}

  begin
    scannerstatus := 3;
    unbalance := 0;
    longstate := eqtb[curcs].hh.b0;
    if longstate >= 113 then
      longstate := longstate - 2;
    repeat
      mem[29997].hh.rh := 0;
      if (mem[r].hh.lh > 3583) or (mem[r].hh.lh < 3328) then
        s := 0
      else
      begin
        matchchr := mem[r].hh.lh - 3328;
        s := mem[r].hh.rh;
        r := s;
        p := 29997;
        m := 0;
      end;
      {392:}
22:
        gettoken;
      if curtok = mem[r].hh.lh then{394:}

      begin
        r := mem[r].hh.rh;
        if (mem[r].hh.lh >= 3328) and (mem[r].hh.lh <= 3584) then
        begin
          if curtok < 512 then
            alignstate := alignstate - 1;
          goto 40;
        end
        else
          goto 22;
      end{:394}
;
      {397:}
if s <> r then
        if s = 0 then{398:}

        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(650);
          end;
          sprintcs(warningindex);
          print(651);
          begin
            helpptr := 4;
            helpline[3] := 652;
            helpline[2] := 653;
            helpline[1] := 654;
            helpline[0] := 655;
          end;
          error;
          goto 10;
        end{:398}

        else
        begin
          t := s;
          repeat
            begin
              q := getavail;
              mem[p].hh.rh := q;
              mem[q].hh.lh := mem[t].hh.lh;
              p := q;
            end;
            m := m + 1;
            u := mem[t].hh.rh;
            v := s;
            while true do
            begin
              if u = r then
                if curtok <> mem[v].hh.lh then
                  goto 30
                else
                begin
                  r := mem[v].hh.rh;
                  goto 22;
                end;
              if mem[u].hh.lh <> mem[v].hh.lh then
                goto 30;
              u := mem[u].hh.rh;
              v := mem[v].hh.rh;
            end;
            30:
              t := mem[t].hh.rh;
          until t = r;
          r := s;
        end{:397}
;
      if curtok = partoken then
        if longstate <> 112 then{396:}

        begin
          if longstate = 111 then
          begin
            runaway;
            begin
              if interaction = 3 then;
              printnl(262);
              print(645);
            end;
            sprintcs(warningindex);
            print(646);
            begin
              helpptr := 3;
              helpline[2] := 647;
              helpline[1] := 648;
              helpline[0] := 649;
            end;
            backerror;
          end;
          pstack[n] := mem[29997].hh.rh;
          alignstate := alignstate - unbalance;
          for m := 0 to n do
            flushlist(pstack[m]);
          goto 10;
        end{:396}
;
      if curtok < 768 then
        if curtok < 512 then{399:}

        begin
          unbalance := 1;
          while true do
          begin
            begin
              begin
                q := avail;
                if q = 0 then
                  q := getavail
                else
                begin
                  avail := mem[q].hh.rh;
                  mem[q].hh.rh := 0;
                  {dynused:=dynused+1;}
end;
              end;
              mem[p].hh.rh := q;
              mem[q].hh.lh := curtok;
              p := q;
            end;
            gettoken;
            if curtok = partoken then
              if longstate <> 112 then{396:}

              begin
                if longstate = 111 then
                begin
                  runaway;
                  begin
                    if interaction = 3 then;
                    printnl(262);
                    print(645);
                  end;
                  sprintcs(warningindex);
                  print(646);
                  begin
                    helpptr := 3;
                    helpline[2] := 647;
                    helpline[1] := 648;
                    helpline[0] := 649;
                  end;
                  backerror;
                end;
                pstack[n] := mem[29997].hh.rh;
                alignstate := alignstate - unbalance;
                for m := 0 to n do
                  flushlist(pstack[m]);
                goto 10;
              end{:396}
;
            if curtok < 768 then
              if curtok < 512 then
                unbalance := unbalance + 1
              else
              begin
                unbalance := unbalance - 1;
                if unbalance = 0 then
                  goto 31;
              end;
          end;
          31:
            rbraceptr := p;
          begin
            q := getavail;
            mem[p].hh.rh := q;
            mem[q].hh.lh := curtok;
            p := q;
          end;
        end{:399}

        else{395:}

        begin
          backinput;
          begin
            if interaction = 3 then;
            printnl(262);
            print(637);
          end;
          sprintcs(warningindex);
          print(638);
          begin
            helpptr := 6;
            helpline[5] := 639;
            helpline[4] := 640;
            helpline[3] := 641;
            helpline[2] := 642;
            helpline[1] := 643;
            helpline[0] := 644;
          end;
          alignstate := alignstate + 1;
          longstate := 111;
          curtok := partoken;
          inserror;
          goto 22;
        end{:395}

      else{393:}

      begin
        if curtok = 2592 then
          if mem[r].hh.lh <= 3584 then
            if mem[r].hh.lh >= 3328 then
              goto 22;
        begin
          q := getavail;
          mem[p].hh.rh := q;
          mem[q].hh.lh := curtok;
          p := q;
        end;
      end{:393}
;
      m := m + 1;
      if mem[r].hh.lh > 3584 then
        goto 22;
      if mem[r].hh.lh < 3328 then
        goto 22;
      40:
        if s <> 0 then{400:}

        begin
          if (m = 1) and (mem[p].hh.lh < 768) and (p <> 29997) then
          begin
            mem[rbraceptr].hh.rh := 0;
            begin
              mem[p].hh.rh := avail;
              avail := p;
              {dynused:=dynused-1;}
end;
            p := mem[29997].hh.rh;
            pstack[n] := mem[p].hh.rh;
            begin
              mem[p].hh.rh := avail;
              avail := p;{dynused:=dynused-1;}

            end;
          end
          else
            pstack[n] := mem[29997].hh.rh;
          n := n + 1;
          if eqtb[5293].int > 0 then
          begin
            begindiagnostic;
            printnl(matchchr);
            printint(n);
            print(656);
            showtokenlist(pstack[n - 1], 0, 1000);
            enddiagnostic(false);
          end;
        end{:400}
{:392}
;
    until mem[r].hh.lh = 3584;
  end{:391}
;
  {390:}
while (curinput.statefield = 0) and (curinput.locfield = 0) and (curinput.indexfield <> 2) do
    endtokenlist;
  begintokenlist(refcount, 5);
  curinput.namefield := warningindex;
  curinput.locfield := mem[r].hh.rh;
  if n > 0 then
  begin
    if paramptr + n > maxparamstack then
    begin
      maxparamstack :=
        paramptr + n;
      if maxparamstack > paramsize then
        overflow(636, paramsize);
    end;
    for m := 0 to n - 1 do
      paramstack[paramptr + m] := pstack[m];
    paramptr := paramptr + n;
  end{:390}
;
  10:
    scannerstatus := savescannerstatus;
  warningindex := savewarningindex;
end;
