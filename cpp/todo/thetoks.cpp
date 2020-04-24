#include "thetoks.h"
halfword thetoks(void)
var
  oldsetting: 0..21;
  p, q, r: halfword;
  b: poolpointer;
begin
  getxtoken;
  scansomethinginternal(5, false);
  if curvallevel >= 4 then{466:}

  begin
    p := 29997;
    mem[p].hh.rh := 0;
    if curvallevel = 4 then
    begin
      q := getavail;
      mem[p].hh.rh := q;
      mem[q].hh.lh := 4095 + curval;
      p := q;
    end
    else if curval <> 0 then
    begin
      r := mem[curval].hh.rh;
      while r <> 0 do
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
          mem[q].hh.lh := mem[r].hh.lh;
          p := q;
        end;
        r := mem[r].hh.rh;
      end;
    end;
    thetoks := p;
  end{:466}

  else
  begin
    oldsetting := selector;
    selector := 21;
    b := poolptr;
    case curvallevel of
      0: printint(curval);
      1:
      begin
        printscaled(curval);
        print(397);
      end;
      2:
      begin
        printspec(curval, 397);
        deleteglueref(curval);
      end;
      3:
      begin
        printspec(curval, 337);
        deleteglueref(curval);
      end;
    end;
    selector := oldsetting;
    thetoks := strtoks(b);
  end;
end;
