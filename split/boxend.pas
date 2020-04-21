procedure boxend(boxcontext: integer);
var
  p: halfword;
begin
  if boxcontext < 1073741824 then{1076:}

  begin
    if curbox <> 0 then
    begin
      mem[curbox + 4].int := boxcontext;
      if abs(curlist.modefield) = 1 then
      begin
        appendtovlist(curbox);
        if adjusttail <> 0 then
        begin
          if 29995 <> adjusttail then
          begin
            mem[curlist.tailfield].hh.rh := mem[29995].hh.rh;
            curlist.tailfield := adjusttail;
          end;
          adjusttail := 0;
        end;
        if curlist.modefield > 0 then
          buildpage;
      end
      else
      begin
        if abs(curlist.modefield) = 102 then
          curlist.auxfield.hh.lh := 1000
        else
        begin
          p := newnoad;
          mem[p + 1].hh.rh := 2;
          mem[p + 1].hh.lh := curbox;
          curbox := p;
        end;
        mem[curlist.tailfield].hh.rh := curbox;
        curlist.tailfield := curbox;
      end;
    end;
  end{:1076}

  else if boxcontext < 1073742336 then
    {1077:}
if boxcontext < 1073742080 then
      eqdefine(-1073738146 + boxcontext, 119, curbox)
    else
      geqdefine(-1073738402 + boxcontext, 119, curbox){:1077}

  else if curbox <> 0 then
    if boxcontext > 1073742336 then{1078:}

    begin
      {404:}
repeat
        getxtoken;
      until (curcmd <> 10) and (curcmd <> 0){:404}
;
      if ((curcmd = 26) and (abs(curlist.modefield) <> 1)) or ((curcmd = 27) and (abs(curlist.modefield) = 1)) then
      begin
        appendglue;
        mem[curlist.tailfield].hh.b1 := boxcontext - (1073742237);
        mem[curlist.tailfield + 1].hh.rh := curbox;
      end
      else
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1065);
        end;
        begin
          helpptr := 3;
          helpline[2] := 1066;
          helpline[1] := 1067;
          helpline[0] := 1068;
        end;
        backerror;
        flushnodelist(curbox);
      end;
    end{:1078}

    else
      shipout(curbox);
end;
