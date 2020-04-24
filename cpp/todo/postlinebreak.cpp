#include "postlinebreak.h"
void postlinebreak(int finalwidowpenalty)
label
  30, 31;
var
  q, r, s: halfword;
  discbreak: boolean;
  postdiscbreak: boolean;
  curwidth: scaled;
  curindent: scaled;
  t: quarterword;
  pen: integer;
  curline: halfword;
begin
  {878:}
q := mem[bestbet + 1].hh.rh;
  curp := 0;
  repeat
    r := q;
    q := mem[q + 1].hh.lh;
    mem[r + 1].hh.lh := curp;
    curp := r;
  until q = 0{:878}
;
  curline := curlist.pgfield + 1;
  repeat
    {880:}
{881:}
q := mem[curp + 1].hh.rh;
    discbreak := false;
    postdiscbreak := false;
    if q <> 0 then
      if mem[q].hh.b0 = 10 then
      begin
        deleteglueref(mem[q + 1].hh.lh);
        mem[q + 1].hh.lh := eqtb[2890].hh.rh;
        mem[q].hh.b1 := 9;
        mem[eqtb[2890].hh.rh].hh.rh := mem[eqtb[2890].hh.rh].hh.rh + 1;
        goto 30;
      end
      else
      begin
        if mem[q].hh.b0 = 7 then{882:}

        begin
          t := mem[q].hh.b1;
          {883:}
if t = 0 then
            r := mem[q].hh.rh
          else
          begin
            r := q;
            while t > 1 do
            begin
              r := mem[r].hh.rh;
              t := t - 1;
            end;
            s := mem[r].hh.rh;
            r := mem[s].hh.rh;
            mem[s].hh.rh := 0;
            flushnodelist(mem[q].hh.rh);
            mem[q].hh.b1 := 0;
          end{:883}
;
          if mem[q + 1].hh.rh <> 0 then{884:}

          begin
            s := mem[q + 1].hh.rh;
            while mem[s].hh.rh <> 0 do
              s := mem[s].hh.rh;
            mem[s].hh.rh := r;
            r := mem[q + 1].hh.rh;
            mem[q + 1].hh.rh := 0;
            postdiscbreak := true;
          end{:884}
;
          if mem[q + 1].hh.lh <> 0 then{885:}

          begin
            s := mem[q + 1].hh.lh;
            mem[q].hh.rh := s;
            while mem[s].hh.rh <> 0 do
              s := mem[s].hh.rh;
            mem[q + 1].hh.lh := 0;
            q := s;
          end{:885}
;
          mem[q].hh.rh := r;
          discbreak := true;
        end{:882}

        else if (mem[q].hh.b0 = 9) or (mem[q].hh.b0 = 11) then
          mem[q + 1].int := 0;
      end
    else
    begin
      q := 29997;
      while mem[q].hh.rh <> 0 do
        q := mem[q].hh.rh;
    end;
    {886:}
r := newparamglue(8);
    mem[r].hh.rh := mem[q].hh.rh;
    mem[q].hh.rh := r;
    q := r{:886}
;
    30:
    {:881}
;
    {887:}
r := mem[q].hh.rh;
    mem[q].hh.rh := 0;
    q := mem[29997].hh.rh;
    mem[29997].hh.rh := r;
    if eqtb[2889].hh.rh <> 0 then
    begin
      r := newparamglue(7);
      mem[r].hh.rh := q;
      q := r;
    end{:887}
;
    {889:}
if curline > lastspecialline then
    begin
      curwidth := secondwidth;
      curindent := secondindent;
    end
    else if eqtb[3412].hh.rh = 0 then
    begin
      curwidth := firstwidth;
      curindent := firstindent;
    end
    else
    begin
      curwidth := mem[eqtb[3412].hh.rh + 2 * curline].int;
      curindent := mem[eqtb[3412].hh.rh + 2 * curline - 1].int;
    end;
    adjusttail := 29995;
    justbox := hpack(q, curwidth, 0);
    mem[justbox + 4].int := curindent{:889}
;
    {888:}
appendtovlist(justbox);
    if 29995 <> adjusttail then
    begin
      mem[curlist.tailfield].hh.rh := mem[29995].hh.rh;
      curlist.tailfield := adjusttail;
    end;
    adjusttail := 0{:888}
;
    {890:}
if curline + 1 <> bestline then
    begin
      pen := eqtb[5276].int;
      if curline = curlist.pgfield + 1 then
        pen := pen + eqtb[5268].int;
      if curline + 2 = bestline then
        pen := pen + finalwidowpenalty;
      if discbreak then
        pen := pen + eqtb[5271].int;
      if pen <> 0 then
      begin
        r := newpenalty(pen);
        mem[curlist.tailfield].hh.rh := r;
        curlist.tailfield := r;
      end;
    end{:890}
{:880}
;
    curline := curline + 1;
    curp := mem[curp + 1].hh.lh;
    if curp <> 0 then
      if not postdiscbreak then{879:}

      begin
        r := 29997;
        while true do
        begin
          q := mem[r].hh.rh;
          if q = mem[curp + 1].hh.rh then
            goto 31;
          if (q >= himemmin) then
            goto 31;
          if (mem[q].hh.b0 < 9) then
            goto 31;
          if mem[q].hh.b0 = 11 then
            if mem[q].hh.b1 <> 1 then
              goto 31;
          r := q;
        end;
        31:
          if r <> 29997 then
          begin
            mem[r].hh.rh := 0;
            flushnodelist(mem[29997].hh.rh);
            mem[29997].hh.rh := q;
          end;
      end{:879}
;
  until curp = 0;
  if (curline <> bestline) or (mem[29997].hh.rh <> 0) then
    confusion(938);
  curlist.pgfield := bestline - 1;
end;
