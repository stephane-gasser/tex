procedure prefixedcommand;
label
  30, 10;
var
  a: smallnumber;
  f: internalfontnumber;
  j: halfword;
  k: fontindex;
  p, q: halfword;
  n: integer;
  e: boolean;
begin
  a := 0;
  while curcmd = 93 do
  begin
    if not odd(a div curchr) then
      a := a + curchr;
    {404:}
repeat
      getxtoken;
    until (curcmd <> 10) and (curcmd <> 0){:404}
;
    if curcmd <= 70 then{1212:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1178);
      end;
      printcmdchr(curcmd, curchr);
      printchar(39);
      begin
        helpptr := 1;
        helpline[0] := 1179;
      end;
      backerror;
      goto 10;
    end{:1212}
;
  end;
  {1213:}
if (curcmd <> 97) and (a mod 4 <> 0) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(685);
    end;
    printesc(1170);
    print(1180);
    printesc(1171);
    print(1181);
    printcmdchr(curcmd, curchr);
    printchar(39);
    begin
      helpptr := 1;
      helpline[0] := 1182;
    end;
    error;
  end{:1213}
;
  {1214:}
if eqtb[5306].int <> 0 then
    if eqtb[5306].int < 0 then
    begin
      if (a >= 4) then
        a := a - 4;
    end
    else if not (a >= 4) then
      a := a + 4{:1214}
;
  case curcmd of
    {1217:}
87: if (a >= 4) then
        geqdefine(3934, 120, curchr)
      else
        eqdefine(3934, 120, curchr);
    {:1217}
{1218:}
97:
    begin
      if odd(curchr) and not (a >= 4) and (eqtb[5306].int >= 0) then
        a := a + 4;
      e := (curchr >= 2);
      getrtoken;
      p := curcs;
      q := scantoks(true, e);
      if (a >= 4) then
        geqdefine(p, 111 + (a mod 4), defref)
      else
        eqdefine(p, 111 + (a mod 4), defref);
    end;
    {:1218}
{1221:}
94:
    begin
      n := curchr;
      getrtoken;
      p := curcs;
      if n = 0 then
      begin
        repeat
          gettoken;
        until curcmd <> 10;
        if curtok = 3133 then
        begin
          gettoken;
          if curcmd = 10 then
            gettoken;
        end;
      end
      else
      begin
        gettoken;
        q := curtok;
        gettoken;
        backinput;
        curtok := q;
        backinput;
      end;
      if curcmd >= 111 then
        mem[curchr].hh.lh := mem[curchr].hh.lh + 1;
      if (a >= 4) then
        geqdefine(p, curcmd, curchr)
      else
        eqdefine(p, curcmd, curchr);
    end;
    {:1221}
{1224:}
95:
    begin
      n := curchr;
      getrtoken;
      p := curcs;
      if (a >= 4) then
        geqdefine(p, 0, 256)
      else
        eqdefine(p, 0, 256);
      scanoptionalequals;
      case n of
        0:
        begin
          scancharnum;
          if (a >= 4) then
            geqdefine(p, 68, curval)
          else
            eqdefine(p, 68, curval);
        end;
        1:
        begin
          scanfifteenbitint;
          if (a >= 4) then
            geqdefine(p, 69, curval)
          else
            eqdefine(p, 69, curval);
        end;
        others:
        begin
          scaneightbitint;
          case n of
            2: if (a >= 4) then
                geqdefine(p, 73, 5318 + curval)
              else
                eqdefine(p, 73,
                  5318 + curval);
            3: if (a >= 4) then
                geqdefine(p, 74, 5851 + curval)
              else
                eqdefine(p, 74, 5851 + curval);
            4: if (a >= 4) then
                geqdefine(p, 75, 2900 + curval)
              else
                eqdefine(p, 75, 2900 + curval);
            5: if (a >= 4) then
                geqdefine(p, 76, 3156 + curval)
              else
                eqdefine(p, 76, 3156 + curval);
            6: if (a >= 4) then
                geqdefine(p, 72, 3422 + curval)
              else
                eqdefine(p, 72, 3422 + curval);
          end;
        end
      end;
    end;
    {:1224}
{1225:}
96:
    begin
      scanint;
      n := curval;
      if not scankeyword(841) then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1072);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1199;
          helpline[0] := 1200;
        end;
        error;
      end;
      getrtoken;
      p := curcs;
      readtoks(n, p);
      if (a >= 4) then
        geqdefine(p, 111, curval)
      else
        eqdefine(p, 111, curval);
    end;
    {:1225}
{1226:}
71, 72:
    begin
      q := curcs;
      if curcmd = 71 then
      begin
        scaneightbitint;
        p := 3422 + curval;
      end
      else
        p := curchr;
      scanoptionalequals;
      {404:}
repeat
        getxtoken;
      until (curcmd <> 10) and (curcmd <> 0){:404}
;
      if curcmd <> 1 then{1227:}

      begin
        if curcmd = 71 then
        begin
          scaneightbitint;
          curcmd := 72;
          curchr := 3422 + curval;
        end;
        if curcmd = 72 then
        begin
          q := eqtb[curchr].hh.rh;
          if q = 0 then
            if (a >= 4) then
              geqdefine(p, 101, 0)
            else
              eqdefine(p, 101, 0)
          else
          begin
            mem[q].hh.lh := mem[q].hh.lh + 1;
            if (a >= 4) then
              geqdefine(p, 111, q)
            else
              eqdefine(p, 111, q);
          end;
          goto 30;
        end;
      end{:1227}
;
      backinput;
      curcs := q;
      q := scantoks(false, false);
      if mem[defref].hh.rh = 0 then
      begin
        if (a >= 4) then
          geqdefine(p, 101, 0)
        else
          eqdefine(p, 101, 0);
        begin
          mem[defref].hh.rh := avail;
          avail := defref;
          {dynused:=dynused-1;}
end;
      end
      else
      begin
        if p = 3413 then
        begin
          mem[q].hh.rh := getavail;
          q := mem[q].hh.rh;
          mem[q].hh.lh := 637;
          q := getavail;
          mem[q].hh.lh := 379;
          mem[q].hh.rh := mem[defref].hh.rh;
          mem[defref].hh.rh := q;
        end;
        if (a >= 4) then
          geqdefine(p, 111, defref)
        else
          eqdefine(p, 111, defref);
      end;
    end;
    {:1226}
{1228:}
73:
    begin
      p := curchr;
      scanoptionalequals;
      scanint;
      if (a >= 4) then
        geqworddefine(p, curval)
      else
        eqworddefine(p, curval);
    end;
    74:
    begin
      p := curchr;
      scanoptionalequals;
      scandimen(false, false, false);
      if (a >= 4) then
        geqworddefine(p, curval)
      else
        eqworddefine(p, curval);
    end;
    75, 76:
    begin
      p := curchr;
      n := curcmd;
      scanoptionalequals;
      if n = 76 then
        scanglue(3)
      else
        scanglue(2);
      trapzeroglue;
      if (a >= 4) then
        geqdefine(p, 117, curval)
      else
        eqdefine(p, 117, curval);
    end;
    {:1228}
{1232:}
85:
    begin
      {1233:}
if curchr = 3983 then
        n := 15
      else if curchr = 5007 then
        n := 32768
      else if curchr = 4751 then
        n := 32767
      else if curchr = 5574 then
        n := 16777215
      else
        n := 255{:1233}
;
      p := curchr;
      scancharnum;
      p := p + curval;
      scanoptionalequals;
      scanint;
      if ((curval < 0) and (p < 5574)) or (curval > n) then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1201);
        end;
        printint(curval);
        if p < 5574 then
          print(1202)
        else
          print(1203);
        printint(n);
        begin
          helpptr := 1;
          helpline[0] := 1204;
        end;
        error;
        curval := 0;
      end;
      if p < 5007 then
        if (a >= 4) then
          geqdefine(p, 120, curval)
        else
          eqdefine(p, 120,
            curval)
      else if p < 5574 then
        if (a >= 4) then
          geqdefine(p, 120, curval + 0)
        else
          eqdefine(p, 120, curval + 0)
      else if (a >= 4) then
        geqworddefine(p, curval)
      else
        eqworddefine(p, curval);
    end;
    {:1232}
{1234:}
86:
    begin
      p := curchr;
      scanfourbitint;
      p := p + curval;
      scanoptionalequals;
      scanfontident;
      if (a >= 4) then
        geqdefine(p, 120, curval)
      else
        eqdefine(p, 120, curval);
    end;
    {:1234}
{1235:}
89, 90, 91, 92: doregistercommand(a);
    {:1235}
{1241:}
98:
    begin
      scaneightbitint;
      if (a >= 4) then
        n := 256 + curval
      else
        n := curval;
      scanoptionalequals;
      if setboxallowed then
        scanbox(1073741824 + n)
      else
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(680);
        end;
        printesc(536);
        begin
          helpptr := 2;
          helpline[1] := 1210;
          helpline[0] := 1211;
        end;
        error;
      end;
    end;
    {:1241}
{1242:}
79: alteraux;
    80: alterprevgraf;
    81: alterpagesofar;
    82: alterinteger;
    83: alterboxdimen;
    {:1242}
{1248:}
84:
    begin
      scanoptionalequals;
      scanint;
      n := curval;
      if n <= 0 then
        p := 0
      else
      begin
        p := getnode(2 * n + 1);
        mem[p].hh.lh := n;
        for j := 1 to n do
        begin
          scandimen(false, false, false);
          mem[p + 2 * j - 1].int := curval;
          scandimen(false, false, false);
          mem[p + 2 * j].int := curval;
        end;
      end;
      if (a >= 4) then
        geqdefine(3412, 118, p)
      else
        eqdefine(3412, 118, p);
    end;
    {:1248}
{1252:}
99: if curchr = 1 then
      begin
        newpatterns;
        goto 30;
        begin
          if interaction = 3 then;
          printnl(262);
          print(1215);
        end;
        helpptr := 0;
        error;
        repeat
          gettoken;
        until curcmd = 2;
        goto 10;
      end
      else
      begin
        newhyphexceptions;
        goto 30;
      end;
    {:1252}
{1253:}
77:
    begin
      findfontdimen(true);
      k := curval;
      scanoptionalequals;
      scandimen(false, false, false);
      fontinfo[k].int := curval;
    end;
    78:
    begin
      n := curchr;
      scanfontident;
      f := curval;
      scanoptionalequals;
      scanint;
      if n = 0 then
        hyphenchar[f] := curval
      else
        skewchar[f] := curval;
    end;
    {:1253}
{1256:}
88: newfont(a);
    {:1256}
{1264:}
100: newinteraction;
    {:1264}
others: confusion(1177)
  end;
  30:
    {1269:}
if aftertoken <> 0 then
    begin
      curtok := aftertoken;
      backinput;
      aftertoken := 0;
    end{:1269}
;
  10: ;
end;
