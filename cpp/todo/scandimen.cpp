#include "scandimen.h"
void scandimen(bool mu, bool  inf, bool  shortcut)
label
  30, 31, 32, 40, 45, 88, 89;
var
  negative: boolean;
  f: integer;
  {450:}
num, denom: 1..65536;
  k, kk: smallnumber;
  p, q: halfword;
  v: scaled;
  savecurval: integer;{:450}

begin
  f := 0;
  aritherror := false;
  curorder := 0;
  negative := false;
  if not shortcut then
  begin
    {441:}
negative := false;
    repeat
      {406:}
repeat
        getxtoken;
      until curcmd <> 10{:406}
;
      if curtok = 3117 then
      begin
        negative := not negative;
        curtok := 3115;
      end;
    until curtok <> 3115{:441}
;
    if (curcmd >= 68) and (curcmd <= 89) then
      {449:}
if mu then
      begin
        scansomethinginternal(3, false);
        {451:}
if curvallevel >= 2 then
        begin
          v := mem[curval + 1].int;
          deleteglueref(curval);
          curval := v;
        end{:451}
;
        if curvallevel = 3 then
          goto 89;
        if curvallevel <> 0 then
          muerror;
      end
      else
      begin
        scansomethinginternal(1, false);
        if curvallevel = 1 then
          goto 89;
      end{:449}

    else
    begin
      backinput;
      if curtok = 3116 then
        curtok := 3118;
      if curtok <> 3118 then
        scanint
      else
      begin
        radix := 10;
        curval := 0;
      end;
      if curtok = 3116 then
        curtok := 3118;
      if (radix = 10) and (curtok = 3118) then{452:}

      begin
        k := 0;
        p := 0;
        gettoken;
        while true do
        begin
          getxtoken;
          if (curtok > 3129) or (curtok < 3120) then
            goto 31;
          if k < 17 then
          begin
            q := getavail;
            mem[q].hh.rh := p;
            mem[q].hh.lh := curtok - 3120;
            p := q;
            k := k + 1;
          end;
        end;
        31:
          for kk := k downto 1 do
          begin
            dig[kk - 1] := mem[p].hh.lh;
            q := p;
            p := mem[p].hh.rh;
            begin
              mem[q].hh.rh := avail;
              avail := q;{dynused:=dynused-1;}

            end;
          end;
        f := rounddecimals(k);
        if curcmd <> 10 then
          backinput;
      end{:452}
;
    end;
  end;
  if curval < 0 then
  begin
    negative := not negative;
    curval := -curval;
  end;
  {453:}
if inf then
    {454:}
if scankeyword(311) then
    begin
      curorder := 1;
      while scankeyword(108) do
        if curorder = 3 then
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(705);
          end;
          print(706);
          begin
            helpptr := 1;
            helpline[0] := 707;
          end;
          error;
        end
        else
          curorder := curorder + 1;
      goto 88;
    end{:454}
;
  {455:}
savecurval := curval;
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  if (curcmd < 68) or (curcmd > 89) then
    backinput
  else
  begin
    if mu then
    begin
      scansomethinginternal(3, false);
      {451:}
if curvallevel >= 2 then
      begin
        v := mem[curval + 1].int;
        deleteglueref(curval);
        curval := v;
      end{:451}
;
      if curvallevel <> 3 then
        muerror;
    end
    else
      scansomethinginternal(1, false);
    v := curval;
    goto 40;
  end;
  if mu then
    goto 45;
  if scankeyword(708) then
    v := ({558:}
fontinfo[6 + parambase[eqtb[3934].hh.rh]].int{:558}
)
  else if scankeyword(709) then
    v := ({559:}
fontinfo[5 + parambase[eqtb[3934].hh.rh]].int{:559}
)
  else
    goto 45;{443:}

  begin
    getxtoken;
    if curcmd <> 10 then
      backinput;
  end{:443}
;
  40:
    curval := multandadd(savecurval, v, xnoverd(v, f, 65536), 1073741823);
  goto 89;
  45:
  {:455}
;
  if mu then
    {456:}
if scankeyword(337) then
      goto 88
    else
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(705);
      end;
      print(710);
      begin
        helpptr := 4;
        helpline[3] := 711;
        helpline[2] := 712;
        helpline[1] := 713;
        helpline[0] := 714;
      end;
      error;
      goto 88;
    end{:456}
;
  if scankeyword(704) then{457:}

  begin
    preparemag;
    if eqtb[5280].int <> 1000 then
    begin
      curval := xnoverd(curval, 1000, eqtb[5280].int);
      f := (1000 * f + 65536 * remainder) div eqtb[5280].int;
      curval := curval + (f div 65536);
      f := f mod 65536;
    end;
  end{:457}
;
  if scankeyword(397) then
    goto 88;
  {458:}
if scankeyword(715) then
  begin
    num := 7227;
    denom := 100;
  end
  else if scankeyword(716) then
  begin
    num := 12;
    denom := 1;
  end
  else if scankeyword(717) then
  begin
    num := 7227;
    denom := 254;
  end
  else if scankeyword(718) then
  begin
    num := 7227;
    denom := 2540;
  end
  else if scankeyword(719) then
  begin
    num := 7227;
    denom := 7200;
  end
  else if scankeyword(720) then
  begin
    num := 1238;
    denom := 1157;
  end
  else if scankeyword(721) then
  begin
    num := 14856;
    denom := 1157;
  end
  else if scankeyword(722) then
    goto 30
  else{459:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(705);
    end;
    print(723);
    begin
      helpptr := 6;
      helpline[5] := 724;
      helpline[4] := 725;
      helpline[3] := 726;
      helpline[2] := 712;
      helpline[1] := 713;
      helpline[0] := 714;
    end;
    error;
    goto 32;
  end{:459}
;
  curval := xnoverd(curval, num, denom);
  f := (num * f + 65536 * remainder) div denom;
  curval := curval + (f div 65536);
  f := f mod 65536;
  32:
  {:458}
;
  88:
    if curval >= 16384 then
      aritherror := true
    else
      curval := curval * 65536 + f;
  30:
  {:453}
;{443:}

  begin
    getxtoken;
    if curcmd <> 10 then
      backinput;
  end{:443}
;
  89:
    if aritherror or (abs(curval) >= 1073741824) then{460:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(727);
      end;
      begin
        helpptr := 2;
        helpline[1] := 728;
        helpline[0] := 729;
      end;
      error;
      curval := 1073741823;
      aritherror := false;
    end{:460}
;
  if negative then
    curval := -curval;
end;
