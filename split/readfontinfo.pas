function readfontinfo(u: halfword; nom, aire: strnumber; s: scaled): internalfontnumber;
label
  30, 11, 45;
var
  k: fontindex;
  fileopened: boolean;
  lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np: halfword;
  f: internalfontnumber;
  g: internalfontnumber;
  a, b, c, d: eightbits;
  qw: fourquarters;
  sw: scaled;
  bchlabel: integer;
  bchar: 0..256;
  z: scaled;
  alpha: integer;
  beta: 1..16;
begin
  g := 0;
  {562:}
{563:}
fileopened := false;
  if aire = 338 then
    packfilename(nom, 784, 810)
  else
    packfilename(nom, aire, 810);
  if not bopenin(tfmfile) then
    goto 11;
  fileopened := true{:563}
;
  {565:}
begin
    begin
      lf := tfmfile^;
      if lf > 127 then
        goto 11;
      get(tfmfile);
      lf := lf * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      lh := tfmfile^;
      if lh > 127 then
        goto 11;
      get(tfmfile);
      lh := lh * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      bc := tfmfile^;
      if bc > 127 then
        goto 11;
      get(tfmfile);
      bc := bc * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      ec := tfmfile^;
      if ec > 127 then
        goto 11;
      get(tfmfile);
      ec := ec * 256 + tfmfile^;
    end;
    if (bc > ec + 1) or (ec > 255) then
      goto 11;
    if bc > 255 then
    begin
      bc := 1;
      ec := 0;
    end;
    get(tfmfile);
    begin
      nw := tfmfile^;
      if nw > 127 then
        goto 11;
      get(tfmfile);
      nw := nw * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      nh := tfmfile^;
      if nh > 127 then
        goto 11;
      get(tfmfile);
      nh := nh * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      nd := tfmfile^;
      if nd > 127 then
        goto 11;
      get(tfmfile);
      nd := nd * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      ni := tfmfile^;
      if ni > 127 then
        goto 11;
      get(tfmfile);
      ni := ni * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      nl := tfmfile^;
      if nl > 127 then
        goto 11;
      get(tfmfile);
      nl := nl * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      nk := tfmfile^;
      if nk > 127 then
        goto 11;
      get(tfmfile);
      nk := nk * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      ne := tfmfile^;
      if ne > 127 then
        goto 11;
      get(tfmfile);
      ne := ne * 256 + tfmfile^;
    end;
    get(tfmfile);
    begin
      np := tfmfile^;
      if np > 127 then
        goto 11;
      get(tfmfile);
      np := np * 256 + tfmfile^;
    end;
    if lf <> 6 + lh + (ec - bc + 1) + nw + nh + nd + ni + nl + nk + ne + np then
      goto 11;
    if (nw = 0) or (nh = 0) or (nd = 0) or (ni = 0) then
      goto 11;
  end{:565}
;
  {566:}
lf := lf - 6 - lh;
  if np < 7 then
    lf := lf + 7 - np;
  if (fontptr = fontmax) or (fmemptr + lf > fontmemsize) then{567:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(801);
    end;
    sprintcs(u);
    printchar(61);
    printfilename(nom, aire, 338);
    if s >= 0 then
    begin
      print(741);
      printscaled(s);
      print(397);
    end
    else if s <> -1000 then
    begin
      print(802);
      printint(-s);
    end;
    print(811);
    begin
      helpptr := 4;
      helpline[3] := 812;
      helpline[2] := 813;
      helpline[1] := 814;
      helpline[0] := 815;
    end;
    error;
    goto 30;
  end{:567}
;
  f := fontptr + 1;
  charbase[f] := fmemptr - bc;
  widthbase[f] := charbase[f] + ec + 1;
  heightbase[f] := widthbase[f] + nw;
  depthbase[f] := heightbase[f] + nh;
  italicbase[f] := depthbase[f] + nd;
  ligkernbase[f] := italicbase[f] + ni;
  kernbase[f] := ligkernbase[f] + nl - 256 * (128);
  extenbase[f] := kernbase[f] + 256 * (128) + nk;
  parambase[f] := extenbase[f] + ne{:566}
;{568:}

  begin
    if lh < 2 then
      goto 11;
    begin
      get(tfmfile);
      a := tfmfile^;
      qw.b0 := a + 0;
      get(tfmfile);
      b := tfmfile^;
      qw.b1 := b + 0;
      get(tfmfile);
      c := tfmfile^;
      qw.b2 := c + 0;
      get(tfmfile);
      d := tfmfile^;
      qw.b3 := d + 0;
      fontcheck[f] := qw;
    end;
    get(tfmfile);
    begin
      z := tfmfile^;
      if z > 127 then
        goto 11;
      get(tfmfile);
      z := z * 256 + tfmfile^;
    end;
    get(tfmfile);
    z := z * 256 + tfmfile^;
    get(tfmfile);
    z := (z * 16) + (tfmfile^ div 16);
    if z < 65536 then
      goto 11;
    while lh > 2 do
    begin
      get(tfmfile);
      get(tfmfile);
      get(tfmfile);
      get(tfmfile);
      lh := lh - 1;
    end;
    fontdsize[f] := z;
    if s <> -1000 then
      if s >= 0 then
        z := s
      else
        z := xnoverd(z, -s, 1000);
    fontsize[f] := z;
  end{:568}
;
  {569:}
for k := fmemptr to widthbase[f] - 1 do
  begin
    begin
      get(tfmfile);
      a := tfmfile^;
      qw.b0 := a + 0;
      get(tfmfile);
      b := tfmfile^;
      qw.b1 := b + 0;
      get(tfmfile);
      c := tfmfile^;
      qw.b2 := c + 0;
      get(tfmfile);
      d := tfmfile^;
      qw.b3 := d + 0;
      fontinfo[k].qqqq := qw;
    end;
    if (a >= nw) or (b div 16 >= nh) or (b mod 16 >= nd) or (c div 4 >= ni) then
      goto 11;
    case c mod 4 of
      1: if d >= nl then
          goto 11;
      3: if d >= ne then
          goto 11;
      2:{570:}

      begin
        begin
          if (d < bc) or (d > ec) then
            goto 11;
        end;
        while d < k + bc - fmemptr do
        begin
          qw := fontinfo[charbase[f] + d].qqqq;
          if ((qw.b2 - 0) mod 4) <> 2 then
            goto 45;
          d := qw.b3 - 0;
        end;
        if d = k + bc - fmemptr then
          goto 11;
        45: ;
      end{:570}
;
      others: end;
  end{:569}
;
  {571:}
begin{572:}

    begin
      alpha := 16;
      while z >= 8388608 do
      begin
        z := z div 2;
        alpha := alpha + alpha;
      end;
      beta := 256 div alpha;
      alpha := alpha * z;
    end{:572}
;
    for k := widthbase[f] to ligkernbase[f] - 1 do
    begin
      get(tfmfile);
      a := tfmfile^;
      get(tfmfile);
      b := tfmfile^;
      get(tfmfile);
      c := tfmfile^;
      get(tfmfile);
      d := tfmfile^;
      sw := (((((d * z) div 256) + (c * z)) div 256) + (b * z)) div beta;
      if a = 0 then
        fontinfo[k].int := sw
      else if a = 255 then
        fontinfo[k].int := sw - alpha
      else
        goto 11;
    end;
    if fontinfo[widthbase[f]].int <> 0 then
      goto 11;
    if fontinfo[heightbase[f]].int <> 0 then
      goto 11;
    if fontinfo[depthbase[f]].int <> 0 then
      goto 11;
    if fontinfo[italicbase[f]].int <> 0 then
      goto 11;
  end{:571}
;
  {573:}
bchlabel := 32767;
  bchar := 256;
  if nl > 0 then
  begin
    for k := ligkernbase[f] to kernbase[f] + 256 * (128) - 1 do
    begin
      begin
        get(tfmfile);
        a := tfmfile^;
        qw.b0 := a + 0;
        get(tfmfile);
        b := tfmfile^;
        qw.b1 := b + 0;
        get(tfmfile);
        c := tfmfile^;
        qw.b2 := c + 0;
        get(tfmfile);
        d := tfmfile^;
        qw.b3 := d + 0;
        fontinfo[k].qqqq := qw;
      end;
      if a > 128 then
      begin
        if 256 * c + d >= nl then
          goto 11;
        if a = 255 then
          if k = ligkernbase[f] then
            bchar := b;
      end
      else
      begin
        if b <> bchar then
        begin
          begin
            if (b < bc) or (b > ec) then
              goto 11;
          end;
          qw := fontinfo[charbase[f] + b].qqqq;
          if not (qw.b0 > 0) then
            goto 11;
        end;
        if c < 128 then
        begin
          begin
            if (d < bc) or (d > ec) then
              goto 11;
          end;
          qw := fontinfo[charbase[f] + d].qqqq;
          if not (qw.b0 > 0) then
            goto 11;
        end
        else if 256 * (c - 128) + d >= nk then
          goto 11;
        if a < 128 then
          if k - ligkernbase[f] + a + 1 >= nl then
            goto 11;
      end;
    end;
    if a = 255 then
      bchlabel := 256 * c + d;
  end;
  for k := kernbase[f] + 256 * (128) to extenbase[f] - 1 do
  begin
    get(tfmfile);
    a := tfmfile^;
    get(tfmfile);
    b := tfmfile^;
    get(tfmfile);
    c := tfmfile^;
    get(tfmfile);
    d := tfmfile^;
    sw := (((((d * z) div 256) + (c * z)) div 256) + (b * z)) div beta;
    if a = 0 then
      fontinfo[k].int := sw
    else if a = 255 then
      fontinfo[k].int := sw - alpha
    else
      goto 11;
  end;
  {:573}
;
  {574:}
for k := extenbase[f] to parambase[f] - 1 do
  begin
    begin
      get(tfmfile);
      a := tfmfile^;
      qw.b0 := a + 0;
      get(tfmfile);
      b := tfmfile^;
      qw.b1 := b + 0;
      get(tfmfile);
      c := tfmfile^;
      qw.b2 := c + 0;
      get(tfmfile);
      d := tfmfile^;
      qw.b3 := d + 0;
      fontinfo[k].qqqq := qw;
    end;
    if a <> 0 then
    begin
      begin
        if (a < bc) or (a > ec) then
          goto 11;
      end;
      qw := fontinfo[charbase[f] + a].qqqq;
      if not (qw.b0 > 0) then
        goto 11;
    end;
    if b <> 0 then
    begin
      begin
        if (b < bc) or (b > ec) then
          goto 11;
      end;
      qw := fontinfo[charbase[f] + b].qqqq;
      if not (qw.b0 > 0) then
        goto 11;
    end;
    if c <> 0 then
    begin
      begin
        if (c < bc) or (c > ec) then
          goto 11;
      end;
      qw := fontinfo[charbase[f] + c].qqqq;
      if not (qw.b0 > 0) then
        goto 11;
    end;
    begin
      begin
        if (d < bc) or (d > ec) then
          goto 11;
      end;
      qw := fontinfo[charbase[f] + d].qqqq;
      if not (qw.b0 > 0) then
        goto 11;
    end;
  end{:574}
;{575:}

  begin
    for k := 1 to np do
      if k = 1 then
      begin
        get(tfmfile);
        sw := tfmfile^;
        if sw > 127 then
          sw := sw - 256;
        get(tfmfile);
        sw := sw * 256 + tfmfile^;
        get(tfmfile);
        sw := sw * 256 + tfmfile^;
        get(tfmfile);
        fontinfo[parambase[f]].int := (sw * 16) + (tfmfile^ div 16);
      end
      else
      begin
        get(tfmfile);
        a := tfmfile^;
        get(tfmfile);
        b := tfmfile^;
        get(tfmfile);
        c := tfmfile^;
        get(tfmfile);
        d := tfmfile^;
        sw := (((((d * z) div 256) + (c * z)) div 256) + (b * z)) div beta;
        if a = 0 then
          fontinfo[parambase[f] + k - 1].int := sw
        else if a = 255 then
          fontinfo[parambase[f] + k - 1].int := sw - alpha
        else
          goto 11;
      end;
    if EOF(tfmfile) then
      goto 11;
    for k := np + 1 to 7 do
      fontinfo[parambase[f] + k - 1].int := 0;
  end{:575}
;
  {576:}
if np >= 7 then
    fontparams[f] := np
  else
    fontparams[f] := 7;
  hyphenchar[f] := eqtb[5309].int;
  skewchar[f] := eqtb[5310].int;
  if bchlabel < nl then
    bcharlabel[f] := bchlabel + ligkernbase[f]
  else
    bcharlabel[f] := 0;
  fontbchar[f] := bchar + 0;
  fontfalsebchar[f] := bchar + 0;
  if bchar <= ec then
    if bchar >= bc then
    begin
      qw := fontinfo[charbase[f] + bchar].qqqq;
      if (qw.b0 > 0) then
        fontfalsebchar[f] := 256;
    end;
  fontname[f] := nom;
  fontarea[f] := aire;
  fontbc[f] := bc;
  fontec[f] := ec;
  fontglue[f] := 0;
  charbase[f] := charbase[f] - 0;
  widthbase[f] := widthbase[f] - 0;
  ligkernbase[f] := ligkernbase[f] - 0;
  kernbase[f] := kernbase[f] - 0;
  extenbase[f] := extenbase[f] - 0;
  parambase[f] := parambase[f] - 1;
  fmemptr := fmemptr + lf;
  fontptr := f;
  g := f;
  goto 30{:576}
{:562}
;
  11:{561:}

  begin
    if interaction = 3 then;
    printnl(262);
    print(801);
  end;
  sprintcs(u);
  printchar(61);
  printfilename(nom, aire, 338);
  if s >= 0 then
  begin
    print(741);
    printscaled(s);
    print(397);
  end
  else if s <> -1000 then
  begin
    print(802);
    printint(-s);
  end;
  if fileopened then
    print(803)
  else
    print(804);
  begin
    helpptr := 5;
    helpline[4] := 805;
    helpline[3] := 806;
    helpline[2] := 807;
    helpline[1] := 808;
    helpline[0] := 809;
  end;
  error{:561}
;
  30:
    if fileopened then
      bclose(tfmfile);
  readfontinfo := g;
end;
