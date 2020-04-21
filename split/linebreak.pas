procedure linebreak(finalwidowpenalty: integer);
label
  30, 31, 32, 33, 34, 35, 22;
var
  {862:}
autobreaking: boolean;
  prevp: halfword;
  q, r, s, prevs: halfword;
  f: internalfontnumber;
  {:862}
{893:}
j: smallnumber;
  c: 0..255;{:893}

begin
  packbeginline := curlist.mlfield;
  {816:}
mem[29997].hh.rh := mem[curlist.headfield].hh.rh;
  if (curlist.tailfield >= himemmin) then
  begin
    mem[curlist.tailfield].hh.rh :=
      newpenalty(10000);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end
  else if mem[curlist.tailfield].hh.b0 <> 10 then
  begin
    mem[curlist.tailfield].hh.rh := newpenalty(10000);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end
  else
  begin
    mem[curlist.tailfield].hh.b0 := 12;
    deleteglueref(mem[curlist.tailfield + 1].hh.lh);
    flushnodelist(mem[curlist.tailfield + 1].hh.rh);
    mem[curlist.tailfield + 1].int := 10000;
  end;
  mem[curlist.tailfield].hh.rh := newparamglue(14);
  initcurlang := curlist.pgfield mod 65536;
  initlhyf := curlist.pgfield div 4194304;
  initrhyf := (curlist.pgfield div 65536) mod 64;
  popnest;
  {:816}
{827:}
noshrinkerroryet := true;
  if (mem[eqtb[2889].hh.rh].hh.b1 <> 0) and (mem[eqtb[2889].hh.rh + 3].int <> 0) then
    eqtb[2889].hh.rh := finiteshrink(eqtb[2889].hh.rh);
  if (mem[eqtb[2890].hh.rh].hh.b1 <> 0) and (mem[eqtb[2890].hh.rh + 3].int <> 0) then
    eqtb[2890].hh.rh := finiteshrink(eqtb[2890].hh.rh);
  q := eqtb[2889].hh.rh;
  r := eqtb[2890].hh.rh;
  background[1] := mem[q + 1].int + mem[r + 1].int;
  background[2] := 0;
  background[3] := 0;
  background[4] := 0;
  background[5] := 0;
  background[2 + mem[q].hh.b0] := mem[q + 2].int;
  background[2 + mem[r].hh.b0] := background[2 + mem[r].hh.b0] + mem[r + 2].int;
  background[6] := mem[q + 3].int + mem[r + 3].int;
  {:827}
{834:}
minimumdemerits := 1073741823;
  minimaldemerits[3] := 1073741823;
  minimaldemerits[2] := 1073741823;
  minimaldemerits[1] := 1073741823;
  minimaldemerits[0] := 1073741823;
  {:834}
{848:}
if eqtb[3412].hh.rh = 0 then
    if eqtb[5847].int = 0 then
    begin
      lastspecialline := 0;
      secondwidth := eqtb[5833].int;
      secondindent := 0;
    end
    else{849:}

    begin
      lastspecialline := abs(eqtb[5304].int);
      if eqtb[5304].int < 0 then
      begin
        firstwidth := eqtb[5833].int - abs(eqtb[5847].int);
        if eqtb[5847].int >= 0 then
          firstindent := eqtb[5847].int
        else
          firstindent :=
            0;
        secondwidth := eqtb[5833].int;
        secondindent := 0;
      end
      else
      begin
        firstwidth := eqtb[5833].int;
        firstindent := 0;
        secondwidth := eqtb[5833].int - abs(eqtb[5847].int);
        if eqtb[5847].int >= 0 then
          secondindent := eqtb[5847].int
        else
          secondindent := 0;
      end;
    end{:849}

  else
  begin
    lastspecialline := mem[eqtb[3412].hh.rh].hh.lh - 1;
    secondwidth := mem[eqtb[3412].hh.rh + 2 * (lastspecialline + 1)].int;
    secondindent := mem[eqtb[3412].hh.rh + 2 * lastspecialline + 1].int;
  end;
  if eqtb[5282].int = 0 then
    easyline := lastspecialline
  else
    easyline := 65535
  {:848}
;
  {863:}
threshold := eqtb[5263].int;
  if threshold >= 0 then
  begin
{if eqtb[5295].int>0 then begin
begindiagnostic;printnl(932);end;}
secondpass := false;
    finalpass := false;
  end
  else
  begin
    threshold := eqtb[5264].int;
    secondpass := true;
    finalpass := (eqtb[5850].int <= 0);
    {if eqtb[5295].int>0 then begindiagnostic;}
end;
  while true do
  begin
    if threshold > 10000 then
      threshold := 10000;
    if secondpass then{891:}

    begin
      if trienotready then
        inittrie;
      curlang := initcurlang;
      lhyf := initlhyf;
      rhyf := initrhyf;
    end{:891}
;
    {864:}
q := getnode(3);
    mem[q].hh.b0 := 0;
    mem[q].hh.b1 := 2;
    mem[q].hh.rh := 29993;
    mem[q + 1].hh.rh := 0;
    mem[q + 1].hh.lh := curlist.pgfield + 1;
    mem[q + 2].int := 0;
    mem[29993].hh.rh := q;
    activewidth[1] := background[1];
    activewidth[2] := background[2];
    activewidth[3] := background[3];
    activewidth[4] := background[4];
    activewidth[5] := background[5];
    activewidth[6] := background[6];
    passive := 0;
    printednode := 29997;
    passnumber := 0;
    fontinshortdisplay := 0{:864}
;
    curp := mem[29997].hh.rh;
    autobreaking := true;
    prevp := curp;
    while (curp <> 0) and (mem[29993].hh.rh <> 29993) do{866:}

    begin
      if (curp >= himemmin) then{867:}

      begin
        prevp := curp;
        repeat
          f := mem[curp].hh.b0;
          activewidth[1] := activewidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[curp].hh.b1].qqqq.b0].int;
          curp := mem[curp].hh.rh;
        until not (curp >= himemmin);
      end{:867}
;
      case mem[curp].hh.b0 of
        0, 1, 2: activewidth[1] := activewidth[1] + mem[curp + 1].int;
        8:{1362:}
if mem[curp].hh.b1 = 4 then
          begin
            curlang := mem[curp + 1].hh.rh;
            lhyf := mem[curp + 1].hh.b0;
            rhyf := mem[curp + 1].hh.b1;
          end{:1362}
;
        10:
        begin
          {868:}
if autobreaking then
            if (prevp >= himemmin) then
              trybreak(0, 0)
            else if (mem[prevp].hh.b0 < 9) then
              trybreak(0, 0)
            else if (mem[prevp].hh.b0 = 11) and (mem[prevp].hh.b1 <> 1) then
              trybreak(0, 0);
          if (mem[mem[curp + 1].hh.lh].hh.b1 <> 0) and (mem[mem[curp + 1].hh.lh + 3].int <> 0) then
            mem[curp + 1].hh.lh := finiteshrink(mem[curp + 1].hh.lh);
          q := mem[curp + 1].hh.lh;
          activewidth[1] := activewidth[1] + mem[q + 1].int;
          activewidth[2 + mem[q].hh.b0] := activewidth[2 + mem[q].hh.b0] + mem[q + 2].int;
          activewidth[6] := activewidth[6] + mem[q + 3].int{:868}
;
          if secondpass and autobreaking then{894:}

          begin
            prevs := curp;
            s := mem[prevs].hh.rh;
            if s <> 0 then
            begin
              {896:}
while true do
              begin
                if (s >= himemmin) then
                begin
                  c := mem[s].hh.b1 - 0;
                  hf := mem[s].hh.b0;
                end
                else if mem[s].hh.b0 = 6 then
                  if mem[s + 1].hh.rh = 0 then
                    goto 22
                  else
                  begin
                    q := mem[s + 1].hh.rh;
                    c := mem[q].hh.b1 - 0;
                    hf := mem[q].hh.b0;
                  end
                else if (mem[s].hh.b0 = 11) and (mem[s].hh.b1 = 0) then
                  goto 22
                else if mem[s].hh.b0 = 8 then
                begin
                  {1363:}
if mem[s].hh.b1 = 4 then
                  begin
                    curlang := mem[s + 1].hh.rh;
                    lhyf := mem[s + 1].hh.b0;
                    rhyf := mem[s + 1].hh.b1;
                  end{:1363}
;
                  goto 22;
                end
                else
                  goto 31;
                if eqtb[4239 + c].hh.rh <> 0 then
                  if (eqtb[4239 + c].hh.rh = c) or (eqtb[5301].int > 0) then
                    goto 32
                  else
                    goto 31;
                22:
                  prevs := s;
                s := mem[prevs].hh.rh;
              end;
              32:
                hyfchar := hyphenchar[hf];
              if hyfchar < 0 then
                goto 31;
              if hyfchar > 255 then
                goto 31;
              ha := prevs{:896}
;
              if lhyf + rhyf > 63 then
                goto 31;
              {897:}
hn := 0;
              while true do
              begin
                if (s >= himemmin) then
                begin
                  if mem[s].hh.b0 <> hf then
                    goto 33;
                  hyfbchar := mem[s].hh.b1;
                  c := hyfbchar - 0;
                  if eqtb[4239 + c].hh.rh = 0 then
                    goto 33;
                  if hn = 63 then
                    goto 33;
                  hb := s;
                  hn := hn + 1;
                  hu[hn] := c;
                  hc[hn] := eqtb[4239 + c].hh.rh;
                  hyfbchar := 256;
                end
                else if mem[s].hh.b0 = 6 then{898:}

                begin
                  if mem[s + 1].hh.b0 <> hf then
                    goto 33;
                  j := hn;
                  q := mem[s + 1].hh.rh;
                  if q > 0 then
                    hyfbchar := mem[q].hh.b1;
                  while q > 0 do
                  begin
                    c := mem[q].hh.b1 - 0;
                    if eqtb[4239 + c].hh.rh = 0 then
                      goto 33;
                    if j = 63 then
                      goto 33;
                    j := j + 1;
                    hu[j] := c;
                    hc[j] := eqtb[4239 + c].hh.rh;
                    q := mem[q].hh.rh;
                  end;
                  hb := s;
                  hn := j;
                  if odd(mem[s].hh.b1) then
                    hyfbchar := fontbchar[hf]
                  else
                    hyfbchar := 256;
                end{:898}

                else if (mem[s].hh.b0 = 11) and (mem[s].hh.b1 = 0) then
                begin
                  hb := s;
                  hyfbchar := fontbchar[hf];
                end
                else
                  goto 33;
                s := mem[s].hh.rh;
              end;
              33:
              {:897}
;
              {899:}
if hn < lhyf + rhyf then
                goto 31;
              while true do
              begin
                if not ((s >= himemmin)) then
                  case mem[s].hh.b0 of
                    6: ;
                    11: if mem[s].hh.b1 <> 0 then
                        goto 34;
                    8, 10, 12, 3, 5, 4: goto 34;
                    others: goto 31
                  end;
                s := mem[s].hh.rh;
              end;
              34:
              {:899}
;
              hyphenate;
            end;
            31: ;
          end{:894}
;
        end;
        11: if mem[curp].hh.b1 = 1 then
          begin
            if not (mem[curp].hh.rh >= himemmin) and autobreaking then
              if mem[mem[curp].hh.rh].hh.b0 = 10 then
                trybreak(0, 0);
            activewidth[1] := activewidth[1] + mem[curp + 1].int;
          end
          else
            activewidth[1] := activewidth[1] + mem[curp + 1].int;
        6:
        begin
          f := mem[curp + 1].hh.b0;
          activewidth[1] := activewidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[curp + 1].hh.b1].qqqq.b0].int;
        end;
        7:{869:}

        begin
          s := mem[curp + 1].hh.lh;
          discwidth := 0;
          if s = 0 then
            trybreak(eqtb[5267].int, 1)
          else
          begin
            repeat
              {870:}
if (s >= himemmin) then
              begin
                f := mem[s].hh.b0;
                discwidth := discwidth + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s].hh.b1].qqqq.b0].int;
              end
              else
                case mem[s].hh.b0 of
                  6:
                  begin
                    f := mem[s + 1].hh.b0;
                    discwidth := discwidth + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s + 1].hh.b1].qqqq.b0].int;
                  end;
                  0, 1, 2, 11: discwidth := discwidth + mem[s + 1].int;
                  others: confusion(936)
                end{:870}
;
              s := mem[s].hh.rh;
            until s = 0;
            activewidth[1] := activewidth[1] + discwidth;
            trybreak(eqtb[5266].int, 1);
            activewidth[1] := activewidth[1] - discwidth;
          end;
          r := mem[curp].hh.b1;
          s := mem[curp].hh.rh;
          while r > 0 do
          begin
            {871:}
if (s >= himemmin) then
            begin
              f := mem[s].hh.b0;
              activewidth[1] := activewidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s].hh.b1].qqqq.b0].int;
            end
            else
              case mem[s].hh.b0 of
                6:
                begin
                  f := mem[s + 1].hh.b0;
                  activewidth[1] := activewidth[1] + fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[s + 1].hh.b1].qqqq.b0].int;
                end;
                0, 1, 2, 11: activewidth[1] := activewidth[1] + mem[s + 1].int;
                others: confusion(937)
              end{:871}
;
            r := r - 1;
            s := mem[s].hh.rh;
          end;
          prevp := curp;
          curp := s;
          goto 35;
        end{:869}
;
        9:
        begin
          autobreaking := (mem[curp].hh.b1 = 1);
          begin
            if not (mem[curp].hh.rh >= himemmin) and autobreaking then
              if mem[mem[curp].hh.rh].hh.b0 = 10 then
                trybreak(0, 0);
            activewidth[1] := activewidth[1] + mem[curp + 1].int;
          end;
        end;
        12: trybreak(mem[curp + 1].int, 0);
        4, 3, 5: ;
        others: confusion(935)
      end;
      prevp := curp;
      curp := mem[curp].hh.rh;
      35: ;
    end{:866}
;
    if curp = 0 then{873:}

    begin
      trybreak(-10000, 1);
      if mem[29993].hh.rh <> 29993 then
      begin
        {874:}
r := mem[29993].hh.rh;
        fewestdemerits := 1073741823;
        repeat
          if mem[r].hh.b0 <> 2 then
            if mem[r + 2].int < fewestdemerits then
            begin
              fewestdemerits := mem[r + 2].int;
              bestbet := r;
            end;
          r := mem[r].hh.rh;
        until r = 29993;
        bestline := mem[bestbet + 1].hh.lh{:874}
;
        if eqtb[5282].int = 0 then
          goto 30;{875:}

        begin
          r := mem[29993].hh.rh;
          actuallooseness := 0;
          repeat
            if mem[r].hh.b0 <> 2 then
            begin
              linediff := mem[r + 1].hh.lh - bestline;
              if ((linediff < actuallooseness) and (eqtb[5282].int <= linediff)) or ((linediff > actuallooseness) and
                (eqtb[5282].int >= linediff)) then
              begin
                bestbet := r;
                actuallooseness := linediff;
                fewestdemerits := mem[r + 2].int;
              end
              else if (linediff = actuallooseness) and (mem[r + 2].int < fewestdemerits) then
              begin
                bestbet := r;
                fewestdemerits := mem[r + 2].int;
              end;
            end;
            r := mem[r].hh.rh;
          until r = 29993;
          bestline := mem[bestbet + 1].hh.lh;
        end{:875}
;
        if (actuallooseness = eqtb[5282].int) or finalpass then
          goto 30;
      end;
    end{:873}
;
    {865:}
q := mem[29993].hh.rh;
    while q <> 29993 do
    begin
      curp := mem[q].hh.rh;
      if mem[q].hh.b0 = 2 then
        freenode(q, 7)
      else
        freenode(q, 3);
      q := curp;
    end;
    q := passive;
    while q <> 0 do
    begin
      curp := mem[q].hh.rh;
      freenode(q, 2);
      q := curp;
    end{:865}
;
    if not secondpass then
    begin{if eqtb[5295].int>0 then printnl(933);}

      threshold := eqtb[5264].int;
      secondpass := true;
      finalpass := (eqtb[5850].int <= 0);
    end
    else
    begin{if eqtb[5295].int>0 then printnl(934);}

      background[2] := background[2] + eqtb[5850].int;
      finalpass := true;
    end;
  end;
  30:
{if eqtb[5295].int>0 then begin enddiagnostic(true);
normalizeselector;end;}
{:863}
;
  {876:}
postlinebreak(finalwidowpenalty){:876}
;
  {865:}
q := mem[29993].hh.rh;
  while q <> 29993 do
  begin
    curp := mem[q].hh.rh;
    if mem[q].hh.b0 = 2 then
      freenode(q, 7)
    else
      freenode(q, 3);
    q := curp;
  end;
  q := passive;
  while q <> 0 do
  begin
    curp := mem[q].hh.rh;
    freenode(q, 2);
    q := curp;
  end{:865}
;
  packbeginline := 0;
end;
