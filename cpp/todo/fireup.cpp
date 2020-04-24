#include "fireup.h"
void fireup(halfword c)
label
  10;
var
  p, q, r, s: halfword;
  prevp: halfword;
  n: 0..255;
  wait: boolean;
  savevbadness: integer;
  savevfuzz: scaled;
  savesplittopskip: halfword;
begin
  {1013:}
if mem[bestpagebreak].hh.b0 = 12 then
  begin
    geqworddefine(5302, mem[bestpagebreak + 1].int);
    mem[bestpagebreak + 1].int := 10000;
  end
  else
    geqworddefine(5302, 10000){:1013}
;
  if curmark[2] <> 0 then
  begin
    if curmark[0] <> 0 then
      deletetokenref(curmark[0]);
    curmark[0] := curmark[2];
    mem[curmark[0]].hh.lh := mem[curmark[0]].hh.lh + 1;
    deletetokenref(curmark[1]);
    curmark[1] := 0;
  end;
  {1014:}
if c = bestpagebreak then
    bestpagebreak := 0;
  {1015:}
if eqtb[3933].hh.rh <> 0 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(338);
    end;
    printesc(409);
    print(1002);
    begin
      helpptr := 2;
      helpline[1] := 1003;
      helpline[0] := 991;
    end;
    boxerror(255);
  end{:1015}
;
  insertpenalties := 0;
  savesplittopskip := eqtb[2892].hh.rh;
  if eqtb[5316].int <= 0 then{1018:}

  begin
    r := mem[30000].hh.rh;
    while r <> 30000 do
    begin
      if mem[r + 2].hh.lh <> 0 then
      begin
        n := mem[r].hh.b1 - 0;
        ensurevbox(n);
        if eqtb[3678 + n].hh.rh = 0 then
          eqtb[3678 + n].hh.rh := newnullbox;
        p := eqtb[3678 + n].hh.rh + 5;
        while mem[p].hh.rh <> 0 do
          p := mem[p].hh.rh;
        mem[r + 2].hh.rh := p;
      end;
      r := mem[r].hh.rh;
    end;
  end{:1018}
;
  q := 29996;
  mem[q].hh.rh := 0;
  prevp := 29998;
  p := mem[prevp].hh.rh;
  while p <> bestpagebreak do
  begin
    if mem[p].hh.b0 = 3 then
    begin
      if eqtb[5316].int <= 0 then{1020:}

      begin
        r := mem[30000].hh.rh;
        while mem[r].hh.b1 <> mem[p].hh.b1 do
          r := mem[r].hh.rh;
        if mem[r + 2].hh.lh = 0 then
          wait := true
        else
        begin
          wait := false;
          s := mem[r + 2].hh.rh;
          mem[s].hh.rh := mem[p + 4].hh.lh;
          if mem[r + 2].hh.lh = p then{1021:}

          begin
            if mem[r].hh.b0 = 1 then
              if (mem[r + 1].hh.lh = p) and (mem[r + 1].hh.rh <> 0) then
              begin
                while mem[s].hh.rh <> mem[r + 1].hh.rh do
                  s := mem[s].hh.rh;
                mem[s].hh.rh := 0;
                eqtb[2892].hh.rh := mem[p + 4].hh.rh;
                mem[p + 4].hh.lh := prunepagetop(mem[r + 1].hh.rh);
                if mem[p + 4].hh.lh <> 0 then
                begin
                  tempptr := vpackage(mem[p + 4].hh.lh, 0, 1, 1073741823);
                  mem[p + 3].int := mem[tempptr + 3].int + mem[tempptr + 2].int;
                  freenode(tempptr, 7);
                  wait := true;
                end;
              end;
            mem[r + 2].hh.lh := 0;
            n := mem[r].hh.b1 - 0;
            tempptr := mem[eqtb[3678 + n].hh.rh + 5].hh.rh;
            freenode(eqtb[3678 + n].hh.rh, 7);
            eqtb[3678 + n].hh.rh := vpackage(tempptr, 0, 1, 1073741823);
          end{:1021}

          else
          begin
            while mem[s].hh.rh <> 0 do
              s := mem[s].hh.rh;
            mem[r + 2].hh.rh := s;
          end;
        end;
        {1022:}
mem[prevp].hh.rh := mem[p].hh.rh;
        mem[p].hh.rh := 0;
        if wait then
        begin
          mem[q].hh.rh := p;
          q := p;
          insertpenalties := insertpenalties + 1;
        end
        else
        begin
          deleteglueref(mem[p + 4].hh.rh);
          freenode(p, 5);
        end;
        p := prevp{:1022}
;
      end{:1020}
;
    end
    else if mem[p].hh.b0 = 4 then{1016:}

    begin
      if curmark[1] = 0 then
      begin
        curmark[1] := mem[p + 1].int;
        mem[curmark[1]].hh.lh := mem[curmark[1]].hh.lh + 1;
      end;
      if curmark[2] <> 0 then
        deletetokenref(curmark[2]);
      curmark[2] := mem[p + 1].int;
      mem[curmark[2]].hh.lh := mem[curmark[2]].hh.lh + 1;
    end{:1016}
;
    prevp := p;
    p := mem[prevp].hh.rh;
  end;
  eqtb[2892].hh.rh := savesplittopskip;
  {1017:}
if p <> 0 then
  begin
    if mem[29999].hh.rh = 0 then
      if nestptr = 0 then
        curlist.tailfield := pagetail
      else
        nest[0].tailfield := pagetail;
    mem[pagetail].hh.rh := mem[29999].hh.rh;
    mem[29999].hh.rh := p;
    mem[prevp].hh.rh := 0;
  end;
  savevbadness := eqtb[5290].int;
  eqtb[5290].int := 10000;
  savevfuzz := eqtb[5839].int;
  eqtb[5839].int := 1073741823;
  eqtb[3933].hh.rh := vpackage(mem[29998].hh.rh, bestsize, 0, pagemaxdepth);
  eqtb[5290].int := savevbadness;
  eqtb[5839].int := savevfuzz;
  if lastglue <> 65535 then
    deleteglueref(lastglue);
  {991:}
pagecontents := 0;
  pagetail := 29998;
  mem[29998].hh.rh := 0;
  lastglue := 65535;
  lastpenalty := 0;
  lastkern := 0;
  pagesofar[7] := 0;
  pagemaxdepth := 0{:991}
;
  if q <> 29996 then
  begin
    mem[29998].hh.rh := mem[29996].hh.rh;
    pagetail := q;
  end{:1017}
;
  {1019:}
r := mem[30000].hh.rh;
  while r <> 30000 do
  begin
    q := mem[r].hh.rh;
    freenode(r, 4);
    r := q;
  end;
  mem[30000].hh.rh := 30000{:1019}
{:1014}
;
  if (curmark[0] <> 0) and (curmark[1] = 0) then
  begin
    curmark[1] := curmark[0];
    mem[curmark[0]].hh.lh := mem[curmark[0]].hh.lh + 1;
  end;
  if eqtb[3413].hh.rh <> 0 then
    if deadcycles >= eqtb[5303].int then{1024:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1004);
      end;
      printint(deadcycles);
      print(1005);
      begin
        helpptr := 3;
        helpline[2] := 1006;
        helpline[1] := 1007;
        helpline[0] := 1008;
      end;
      error;
    end{:1024}

    else{1025:}

    begin
      outputactive := true;
      deadcycles := deadcycles + 1;
      pushnest;
      curlist.modefield := -1;
      curlist.auxfield.int := -65536000;
      curlist.mlfield := -line;
      begintokenlist(eqtb[3413].hh.rh, 6);
      newsavelevel(8);
      normalparagraph;
      scanleftbrace;
      goto 10;
    end{:1025}
;
  {1023:}
begin
    if mem[29998].hh.rh <> 0 then
    begin
      if mem[29999].hh.rh = 0 then
        if nestptr = 0 then
          curlist.tailfield := pagetail
        else
          nest[0].
            tailfield := pagetail
      else
        mem[pagetail].hh.rh := mem[29999].hh.rh;
      mem[29999].hh.rh := mem[29998].hh.rh;
      mem[29998].hh.rh := 0;
      pagetail := 29998;
    end;
    shipout(eqtb[3933].hh.rh);
    eqtb[3933].hh.rh := 0;
  end{:1023}
;
  10: ;
end;

