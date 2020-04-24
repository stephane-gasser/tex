#include "mlisttohlist.h"
void mlisttohlist(void)
label
  21, 82, 80, 81, 83, 30;
var
  mlist: halfword;
  penalties: boolean;
  style: smallnumber;
  savestyle: smallnumber;
  q: halfword;
  r: halfword;
  rtype: smallnumber;
  t: smallnumber;
  p, x, y, z: halfword;
  pen: integer;
  s: smallnumber;
  maxh, maxd: scaled;
  delta: scaled;
begin
  mlist := curmlist;
  penalties := mlistpenalties;
  style := curstyle;
  q := mlist;
  r := 0;
  rtype := 17;
  maxh := 0;
  maxd := 0;
  {703:}
begin
    if curstyle < 4 then
      cursize := 0
    else
      cursize := 16 * ((curstyle - 2) div 2);
    curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
  end{:703}
;
  while q <> 0 do{727:}

  begin
    {728:}
21:
      delta := 0;
    case mem[q].hh.b0 of
      18: case rtype of
          18, 17, 19, 20, 22, 30:
          begin
            mem[q].hh.
              b0 := 16;
            goto 21;
          end;
          others: end;
      19, 21, 22, 31:
      begin
        {729:}
if rtype = 18 then
          mem[r].hh.b0 := 16{:729}
;
        if mem[q].hh.b0 = 31 then
          goto 80;
      end;
      {733:}
30: goto 80;
      25:
      begin
        makefraction(q);
        goto 82;
      end;
      17:
      begin
        delta := makeop(q);
        if mem[q].hh.b1 = 1 then
          goto 82;
      end;
      16: makeord(q);
      20, 23: ;
      24: makeradical(q);
      27: makeover(q);
      26: makeunder(q);
      28: makemathaccent(q);
      29: makevcenter(q);
      {:733}
{730:}
14:
      begin
        curstyle := mem[q].hh.b1;
        {703:}
begin
          if curstyle < 4 then
            cursize := 0
          else
            cursize := 16 * ((curstyle - 2) div 2);
          curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
        end{:703}
;
        goto 81;
      end;
      15:{731:}

      begin
        case curstyle div 2 of
          0:
          begin
            p := mem[q + 1].hh.lh;
            mem[q + 1].hh.lh := 0;
          end;
          1:
          begin
            p := mem[q + 1].hh.rh;
            mem[q + 1].hh.rh := 0;
          end;
          2:
          begin
            p := mem[q + 2].hh.lh;
            mem[q + 2].hh.lh := 0;
          end;
          3:
          begin
            p := mem[q + 2].hh.rh;
            mem[q + 2].hh.rh := 0;
          end;
        end;
        flushnodelist(mem[q + 1].hh.lh);
        flushnodelist(mem[q + 1].hh.rh);
        flushnodelist(mem[q + 2].hh.lh);
        flushnodelist(mem[q + 2].hh.rh);
        mem[q].hh.b0 := 14;
        mem[q].hh.b1 := curstyle;
        mem[q + 1].int := 0;
        mem[q + 2].int := 0;
        if p <> 0 then
        begin
          z := mem[q].hh.rh;
          mem[q].hh.rh := p;
          while mem[p].hh.rh <> 0 do
            p := mem[p].hh.rh;
          mem[p].hh.rh := z;
        end;
        goto 81;
      end{:731}
;
      3, 4, 5, 8, 12, 7: goto 81;
      2:
      begin
        if mem[q + 3].int > maxh then
          maxh := mem[q + 3].int;
        if mem[q + 2].int > maxd then
          maxd := mem[q + 2].int;
        goto 81;
      end;
      10:
      begin
        {732:}
if mem[q].hh.b1 = 99 then
        begin
          x := mem[q + 1].hh.lh;
          y := mathglue(x, curmu);
          deleteglueref(x);
          mem[q + 1].hh.lh := y;
          mem[q].hh.b1 := 0;
        end
        else if (cursize <> 0) and (mem[q].hh.b1 = 98) then
        begin
          p := mem[q].hh.rh;
          if p <> 0 then
            if (mem[p].hh.b0 = 10) or (mem[p].hh.b0 = 11) then
            begin
              mem[q].hh.
                rh := mem[p].hh.rh;
              mem[p].hh.rh := 0;
              flushnodelist(p);
            end;
        end{:732}
;
        goto 81;
      end;
      11:
      begin
        mathkern(q, curmu);
        goto 81;
      end;
      {:730}
others: confusion(888)
    end;
    {754:}
case mem[q + 1].hh.rh of
      1, 4:{755:}

      begin
        fetch(q + 1);
        if (curi.b0 > 0) then
        begin
          delta := fontinfo[italicbase[curf] + (curi.b2 - 0) div 4].int;
          p := newcharacter(curf, curc - 0);
          if (mem[q + 1].hh.rh = 4) and (fontinfo[2 + parambase[curf]].int <> 0) then
            delta := 0;
          if (mem[q + 3].hh.rh = 0) and (delta <> 0) then
          begin
            mem[p].hh.rh := newkern(delta);
            delta := 0;
          end;
        end
        else
          p := 0;
      end{:755}
;
      0: p := 0;
      2: p := mem[q + 1].hh.lh;
      3:
      begin
        curmlist := mem[q + 1].hh.lh;
        savestyle := curstyle;
        mlistpenalties := false;
        mlisttohlist;
        curstyle := savestyle;
        {703:}
begin
          if curstyle < 4 then
            cursize := 0
          else
            cursize := 16 * ((curstyle - 2) div 2);
          curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
        end{:703}
;
        p := hpack(mem[29997].hh.rh, 0, 1);
      end;
      others: confusion(889)
    end;
    mem[q + 1].int := p;
    if (mem[q + 3].hh.rh = 0) and (mem[q + 2].hh.rh = 0) then
      goto 82;
    makescripts(q, delta){:754}
{:728}
;
    82:
      z := hpack(mem[q + 1].int, 0, 1);
    if mem[z + 3].int > maxh then
      maxh := mem[z + 3].int;
    if mem[z + 2].int > maxd then
      maxd := mem[z + 2].int;
    freenode(z, 7);
    80:
      r := q;
    rtype := mem[r].hh.b0;
    81:
      q := mem[q].hh.rh;
  end{:727}
;
  {729:}
if rtype = 18 then
    mem[r].hh.b0 := 16{:729}
;
  {760:}
p := 29997;
  mem[p].hh.rh := 0;
  q := mlist;
  rtype := 0;
  curstyle := style;
  {703:}
begin
    if curstyle < 4 then
      cursize := 0
    else
      cursize := 16 * ((curstyle - 2) div 2);
    curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
  end{:703}
;
  while q <> 0 do
  begin
    {761:}
t := 16;
    s := 4;
    pen := 10000;
    case mem[q].hh.b0 of
      17, 20, 21, 22, 23: t := mem[q].hh.b0;
      18:
      begin
        t := 18;
        pen := eqtb[5272].int;
      end;
      19:
      begin
        t := 19;
        pen := eqtb[5273].int;
      end;
      16, 29, 27, 26: ;
      24: s := 5;
      28: s := 5;
      25:
      begin
        t := 23;
        s := 6;
      end;
      30, 31: t := makeleftright(q, style, maxd, maxh);
      14:{763:}

      begin
        curstyle := mem[q].hh.b1;
        s := 3;
        {703:}
begin
          if curstyle < 4 then
            cursize := 0
          else
            cursize := 16 * ((curstyle - 2) div 2);
          curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
        end{:703}
;
        goto 83;
      end{:763}
;
      8, 12, 2, 7, 5, 3, 4, 10, 11:
      begin
        mem[p].hh.rh := q;
        p := q;
        q := mem[q].hh.rh;
        mem[p].hh.rh := 0;
        goto 30;
      end;
      others: confusion(890)
    end{:761}
;
    {766:}
if rtype > 0 then
    begin
      case strpool[rtype * 8 + t + magicoffset] of
        48: x :=
            0;
        49: if curstyle < 4 then
            x := 15
          else
            x := 0;
        50: x := 15;
        51: if curstyle < 4 then
            x := 16
          else
            x := 0;
        52: if curstyle < 4 then
            x := 17
          else
            x := 0;
        others: confusion(892)
      end;
      if x <> 0 then
      begin
        y := mathglue(eqtb[2882 + x].hh.rh, curmu);
        z := newglue(y);
        mem[y].hh.rh := 0;
        mem[p].hh.rh := z;
        p := z;
        mem[z].hh.b1 := x + 1;
      end;
    end{:766}
;
    {767:}
if mem[q + 1].int <> 0 then
    begin
      mem[p].hh.rh := mem[q + 1].int;
      repeat
        p := mem[p].hh.rh;
      until mem[p].hh.rh = 0;
    end;
    if penalties then
      if mem[q].hh.rh <> 0 then
        if pen < 10000 then
        begin
          rtype := mem[mem[q].hh.rh].hh.b0;
          if rtype <> 12 then
            if rtype <> 19 then
            begin
              z := newpenalty(pen);
              mem[p].hh.rh := z;
              p := z;
            end;
        end{:767}
;
    rtype := t;
    83:
      r := q;
    q := mem[q].hh.rh;
    freenode(r, s);
    30: ;
  end{:760}
;
end;
