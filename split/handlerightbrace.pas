procedure handlerightbrace;
var
  p, q: halfword;
  d: scaled;
  f: integer;
begin
  case curgroup of
    1: unsave;
    0:
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1043);
      end;
      begin
        helpptr := 2;
        helpline[1] := 1044;
        helpline[0] := 1045;
      end;
      error;
    end;
    14, 15, 16: extrarightbrace;
    {1085:}
2: package(0);
    3:
    begin
      adjusttail := 29995;
      package(0);
    end;
    4:
    begin
      endgraf;
      package(0);
    end;
    5:
    begin
      endgraf;
      package(4);
    end;
    {:1085}
{1100:}
11:
    begin
      endgraf;
      q := eqtb[2892].hh.rh;
      mem[q].hh.rh := mem[q].hh.rh + 1;
      d := eqtb[5836].int;
      f := eqtb[5305].int;
      unsave;
      saveptr := saveptr - 1;
      p := vpackage(mem[curlist.headfield].hh.rh, 0, 1, 1073741823);
      popnest;
      if savestack[saveptr + 0].int < 255 then
      begin
        begin
          mem[curlist.tailfield].
            hh.rh := getnode(5);
          curlist.tailfield := mem[curlist.tailfield].hh.rh;
        end;
        mem[curlist.tailfield].hh.b0 := 3;
        mem[curlist.tailfield].hh.b1 := savestack[saveptr + 0].int + 0;
        mem[curlist.tailfield + 3].int := mem[p + 3].int + mem[p + 2].int;
        mem[curlist.tailfield + 4].hh.lh := mem[p + 5].hh.rh;
        mem[curlist.tailfield + 4].hh.rh := q;
        mem[curlist.tailfield + 2].int := d;
        mem[curlist.tailfield + 1].int := f;
      end
      else
      begin
        begin
          mem[curlist.tailfield].hh.rh := getnode(2);
          curlist.tailfield := mem[curlist.tailfield].hh.rh;
        end;
        mem[curlist.tailfield].hh.b0 := 5;
        mem[curlist.tailfield].hh.b1 := 0;
        mem[curlist.tailfield + 1].int := mem[p + 5].hh.rh;
        deleteglueref(q);
      end;
      freenode(p, 7);
      if nestptr = 0 then
        buildpage;
    end;
    8:{1026:}

    begin
      if (curinput.locfield <> 0) or ((curinput.indexfield <> 6) and (curinput.indexfield <> 3)) then{1027:}

      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1009);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1010;
          helpline[0] := 1011;
        end;
        error;
        repeat
          gettoken;
        until curinput.locfield = 0;
      end{:1027}
;
      endtokenlist;
      endgraf;
      unsave;
      outputactive := false;
      insertpenalties := 0;
      {1028:}
if eqtb[3933].hh.rh <> 0 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1012);
        end;
        printesc(409);
        printint(255);
        begin
          helpptr := 3;
          helpline[2] := 1013;
          helpline[1] := 1014;
          helpline[0] := 1015;
        end;
        boxerror(255);
      end{:1028}
;
      if curlist.tailfield <> curlist.headfield then
      begin
        mem[pagetail].hh.rh :=
          mem[curlist.headfield].hh.rh;
        pagetail := curlist.tailfield;
      end;
      if mem[29998].hh.rh <> 0 then
      begin
        if mem[29999].hh.rh = 0 then
          nest[0].
            tailfield := pagetail;
        mem[pagetail].hh.rh := mem[29999].hh.rh;
        mem[29999].hh.rh := mem[29998].hh.rh;
        mem[29998].hh.rh := 0;
        pagetail := 29998;
      end;
      popnest;
      buildpage;
    end{:1026}
;
    {:1100}
{1118:}
10: builddiscretionary;
    {:1118}
{1132:}
6:
    begin
      backinput;
      curtok := 6710;
      begin
        if interaction = 3 then;
        printnl(262);
        print(625);
      end;
      printesc(898);
      print(626);
      begin
        helpptr := 1;
        helpline[0] := 1124;
      end;
      inserror;
    end;
    {:1132}
{1133:}
7:
    begin
      endgraf;
      unsave;
      alignpeek;
    end;
    {:1133}
{1168:}
12:
    begin
      endgraf;
      unsave;
      saveptr := saveptr - 2;
      p := vpackage(mem[curlist.headfield].hh.rh, savestack[saveptr + 1].int, savestack[saveptr + 0].int, 1073741823);
      popnest;
      begin
        mem[curlist.tailfield].hh.rh := newnoad;
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      mem[curlist.tailfield].hh.b0 := 29;
      mem[curlist.tailfield + 1].hh.rh := 2;
      mem[curlist.tailfield + 1].hh.lh := p;
    end;
    {:1168}
{1173:}
13: buildchoices;
    {:1173}
{1186:}
9:
    begin
      unsave;
      saveptr := saveptr - 1;
      mem[savestack[saveptr + 0].int].hh.rh := 3;
      p := finmlist(0);
      mem[savestack[saveptr + 0].int].hh.lh := p;
      if p <> 0 then
        if mem[p].hh.rh = 0 then
          if mem[p].hh.b0 = 16 then
          begin
            if mem[p + 3].hh.rh = 0 then
              if mem[p + 2].hh.rh = 0 then
              begin
                mem[savestack[saveptr + 0].int].hh := mem[p + 1].hh;
                freenode(p, 4);
              end;
          end
          else if mem[p].hh.b0 = 28 then
            if savestack[saveptr + 0].int = curlist.tailfield + 1 then
              if mem[curlist.tailfield].hh.b0 = 16 then{1187:}

              begin
                q :=
                  curlist.headfield;
                while mem[q].hh.rh <> curlist.tailfield do
                  q := mem[q].hh.rh;
                mem[q].hh.rh := p;
                freenode(curlist.tailfield, 4);
                curlist.tailfield := p;
              end{:1187}
;
    end;
    {:1186}
others: confusion(1046)
  end;
end;
