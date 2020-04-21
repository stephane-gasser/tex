procedure beginbox(boxcontext: integer);
label
  10, 30;
var
  p, q: halfword;
  m: quarterword;
  k: halfword;
  n: eightbits;
begin
  case curchr of
    0:
    begin
      scaneightbitint;
      curbox := eqtb[3678 + curval].hh.rh;
      eqtb[3678 + curval].hh.rh := 0;
    end;
    1:
    begin
      scaneightbitint;
      curbox := copynodelist(eqtb[3678 + curval].hh.rh);
    end;
    2:{1080:}

    begin
      curbox := 0;
      if abs(curlist.modefield) = 203 then
      begin
        youcant;
        begin
          helpptr := 1;
          helpline[0] := 1069;
        end;
        error;
      end
      else if (curlist.modefield = 1) and (curlist.headfield = curlist.tailfield) then
      begin
        youcant;
        begin
          helpptr := 2;
          helpline[1] := 1070;
          helpline[0] := 1071;
        end;
        error;
      end
      else if not (curlist.tailfield >= himemmin) then
        if (mem[curlist.tailfield].hh.b0 = 0) or (mem[curlist.tailfield].hh.b0 = 1) then{1081:}

        begin
          q := curlist.headfield;
          repeat
            p := q;
            if not (q >= himemmin) then
              if mem[q].hh.b0 = 7 then
              begin
                for m := 1 to mem[q].hh.b1 do
                  p := mem[p].hh.rh;
                if p = curlist.tailfield then
                  goto 30;
              end;
            q := mem[p].hh.rh;
          until q = curlist.tailfield;
          curbox := curlist.tailfield;
          mem[curbox + 4].int := 0;
          curlist.tailfield := p;
          mem[p].hh.rh := 0;
          30: ;
        end{:1081}
;
    end{:1080}
;
    3:{1082:}

    begin
      scaneightbitint;
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
          helpline[1] := 1073;
          helpline[0] := 1074;
        end;
        error;
      end;
      scandimen(false, false, false);
      curbox := vsplit(n, curval);
    end{:1082}
;
    others:{1083:}

    begin
      k := curchr - 4;
      savestack[saveptr + 0].int := boxcontext;
      if k = 102 then
        if (boxcontext < 1073741824) and (abs(curlist.modefield) = 1) then
          scanspec(3, true)
        else
          scanspec(2, true)
      else
      begin
        if k = 1 then
          scanspec(4,
            true)
        else
        begin
          scanspec(5, true);
          k := 1;
        end;
        normalparagraph;
      end;
      pushnest;
      curlist.modefield := -k;
      if k = 1 then
      begin
        curlist.auxfield.int := -65536000;
        if eqtb[3418].hh.rh <> 0 then
          begintokenlist(eqtb[3418].hh.rh, 11);
      end
      else
      begin
        curlist.auxfield.hh.lh := 1000;
        if eqtb[3417].hh.rh <> 0 then
          begintokenlist(eqtb[3417].hh.rh, 10);
      end;
      goto 10;
    end{:1083}

  end;
  boxend(boxcontext);
  10: ;
end;
