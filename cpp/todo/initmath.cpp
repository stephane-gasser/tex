#include "initmath.h"
void initmath(void)
label
  21, 40, 45, 30;
var
  w: scaled;
  l: scaled;
  s: scaled;
  p: halfword;
  q: halfword;
  f: internalfontnumber;
  n: integer;
  v: scaled;
  d: scaled;
begin
  gettoken;
  if (curcmd = 3) and (curlist.modefield > 0) then{1145:}

  begin
    if curlist.headfield = curlist.tailfield then
    begin
      popnest;
      w := -1073741823;
    end
    else
    begin
      linebreak(eqtb[5270].int);
      {1146:}
v := mem[justbox + 4].int + 2 * fontinfo[6 + parambase[eqtb[3934].hh.rh]].int;
      w := -1073741823;
      p := mem[justbox + 5].hh.rh;
      while p <> 0 do
      begin
        {1147:}
21:
          if (p >= himemmin) then
          begin
            f := mem[p].hh.b0;
            d := fontinfo[widthbase[f] + fontinfo[charbase[f] + mem[p].hh.b1].qqqq.b0].int;
            goto 40;
          end;
        case mem[p].hh.b0 of
          0, 1, 2:
          begin
            d := mem[p + 1].int;
            goto 40;
          end;
          6:{652:}

          begin
            mem[29988] := mem[p + 1];
            mem[29988].hh.rh := mem[p].hh.rh;
            p := 29988;
            goto 21;
          end{:652}
;
          11, 9: d := mem[p + 1].int;
          10:{1148:}

          begin
            q := mem[p + 1].hh.lh;
            d := mem[q + 1].int;
            if mem[justbox + 5].hh.b0 = 1 then
            begin
              if (mem[justbox + 5].hh.b1 = mem[q].hh.b0) and (mem[q + 2].int <> 0) then
                v := 1073741823;
            end
            else if mem[justbox + 5].hh.b0 = 2 then
              if (mem[justbox + 5].hh.b1 = mem[q].hh.b1) and (mem[q + 3].int <> 0) then
                v := 1073741823;
            if mem[p].hh.b1 >= 100 then
              goto 40;
          end{:1148}
;
          8:{1361:}
d := 0{:1361}
;
          others: d := 0
        end{:1147}
;
        if v < 1073741823 then
          v := v + d;
        goto 45;
        40:
          if v < 1073741823 then
          begin
            v := v + d;
            w := v;
          end
          else
          begin
            w := 1073741823;
            goto 30;
          end;
        45:
          p := mem[p].hh.rh;
      end;
      30:
      {:1146}
;
    end;
    {1149:}
if eqtb[3412].hh.rh = 0 then
      if (eqtb[5847].int <> 0) and (((eqtb[5304].int >= 0) and (curlist.pgfield + 2 > eqtb[5304].int)) or
        (curlist.pgfield + 1 < -eqtb[5304].int)) then
      begin
        l := eqtb[5833].int - abs(eqtb[5847].int);
        if eqtb[5847].int > 0 then
          s := eqtb[5847].int
        else
          s := 0;
      end
      else
      begin
        l := eqtb[5833].int;
        s := 0;
      end
    else
    begin
      n := mem[eqtb[3412].hh.rh].hh.lh;
      if curlist.pgfield + 2 >= n then
        p := eqtb[3412].hh.rh + 2 * n
      else
        p := eqtb[3412].hh.rh + 2 * (curlist.pgfield + 2);
      s := mem[p - 1].int;
      l := mem[p].int;
    end{:1149}
;
    pushmath(15);
    curlist.modefield := 203;
    eqworddefine(5307, -1);
    eqworddefine(5843, w);
    eqworddefine(5844, l);
    eqworddefine(5845, s);
    if eqtb[3416].hh.rh <> 0 then
      begintokenlist(eqtb[3416].hh.rh, 9);
    if nestptr = 1 then
      buildpage;
  end{:1145}

  else
  begin
    backinput;
    {1139:}
begin
      pushmath(15);
      eqworddefine(5307, -1);
      if eqtb[3415].hh.rh <> 0 then
        begintokenlist(eqtb[3415].hh.rh, 8);
    end{:1139}
;
  end;
end;
