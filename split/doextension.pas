procedure doextension;
var
  i, j, k: integer;
  p, q, r: halfword;
begin
  case curchr of
    0:{1351:}

    begin
      newwritewhatsit(3);
      scanoptionalequals;
      scanfilename;
      mem[curlist.tailfield + 1].hh.rh := curname;
      mem[curlist.tailfield + 2].hh.lh := curarea;
      mem[curlist.tailfield + 2].hh.rh := curext;
    end{:1351}
;
    1:{1352:}

    begin
      k := curcs;
      newwritewhatsit(2);
      curcs := k;
      p := scantoks(false, false);
      mem[curlist.tailfield + 1].hh.rh := defref;
    end{:1352}
;
    2:{1353:}

    begin
      newwritewhatsit(2);
      mem[curlist.tailfield + 1].hh.rh := 0;
    end{:1353}
;
    3:{1354:}

    begin
      newwhatsit(3, 2);
      mem[curlist.tailfield + 1].hh.lh := 0;
      p := scantoks(false, true);
      mem[curlist.tailfield + 1].hh.rh := defref;
    end{:1354}
;
    4:{1375:}

    begin
      getxtoken;
      if (curcmd = 59) and (curchr <= 2) then
      begin
        p := curlist.tailfield;
        doextension;
        outwhat(curlist.tailfield);
        flushnodelist(curlist.tailfield);
        curlist.tailfield := p;
        mem[p].hh.rh := 0;
      end
      else
        backinput;
    end{:1375}
;
    5:{1377:}
if abs(curlist.modefield) <> 102 then
        reportillegalcase
      else
      begin
        newwhatsit(4, 2);
        scanint;
        if curval <= 0 then
          curlist.auxfield.hh.rh := 0
        else if curval > 255 then
          curlist.auxfield.hh.rh := 0
        else
          curlist.auxfield.hh.rh := curval;
        mem[curlist.tailfield + 1].hh.rh := curlist.auxfield.hh.rh;
        mem[curlist.tailfield + 1].hh.b0 := normmin(eqtb[5314].int);
        mem[curlist.tailfield + 1].hh.b1 := normmin(eqtb[5315].int);
      end{:1377}
;
    others: confusion(1290)
  end;
end;
