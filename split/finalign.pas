procedure finalign;
var
  p, q, r, s, u, v: halfword;
  t, w: scaled;
  o: scaled;
  n: halfword;
  rulesave: scaled;
  auxsave: memoryword;
begin
  if curgroup <> 6 then
    confusion(914);
  unsave;
  if curgroup <> 6 then
    confusion(915);
  unsave;
  if nest[nestptr - 1].modefield = 203 then
    o := eqtb[5845].int
  else
    o := 0;
  {801:}
q := mem[mem[29992].hh.rh].hh.rh;
  repeat
    flushlist(mem[q + 3].int);
    flushlist(mem[q + 2].int);
    p := mem[mem[q].hh.rh].hh.rh;
    if mem[q + 1].int = -1073741824 then{802:}

    begin
      mem[q + 1].int := 0;
      r := mem[q].hh.rh;
      s := mem[r + 1].hh.lh;
      if s <> 0 then
      begin
        mem[0].hh.rh := mem[0].hh.rh + 1;
        deleteglueref(s);
        mem[r + 1].hh.lh := 0;
      end;
    end{:802}
;
    if mem[q].hh.lh <> 29991 then{803:}

    begin
      t := mem[q + 1].int + mem[mem[mem[q].hh.rh + 1].hh.lh + 1].int;
      r := mem[q].hh.lh;
      s := 29991;
      mem[s].hh.lh := p;
      n := 1;
      repeat
        mem[r + 1].int := mem[r + 1].int - t;
        u := mem[r].hh.lh;
        while mem[r].hh.rh > n do
        begin
          s := mem[s].hh.lh;
          n := mem[mem[s].hh.lh].hh.rh + 1;
        end;
        if mem[r].hh.rh < n then
        begin
          mem[r].hh.lh := mem[s].hh.lh;
          mem[s].hh.lh := r;
          mem[r].hh.rh := mem[r].hh.rh - 1;
          s := r;
        end
        else
        begin
          if mem[r + 1].int > mem[mem[s].hh.lh + 1].int then
            mem[mem[s].hh.lh + 1].int := mem[r + 1].int;
          freenode(r, 2);
        end;
        r := u;
      until r = 29991;
    end{:803}
;
    mem[q].hh.b0 := 13;
    mem[q].hh.b1 := 0;
    mem[q + 3].int := 0;
    mem[q + 2].int := 0;
    mem[q + 5].hh.b1 := 0;
    mem[q + 5].hh.b0 := 0;
    mem[q + 6].int := 0;
    mem[q + 4].int := 0;
    q := p;
  until q = 0{:801}
;
  {804:}
saveptr := saveptr - 2;
  packbeginline := -curlist.mlfield;
  if curlist.modefield = -1 then
  begin
    rulesave := eqtb[5846].int;
    eqtb[5846].int := 0;
    p := hpack(mem[29992].hh.rh, savestack[saveptr + 1].int, savestack[saveptr + 0].int);
    eqtb[5846].int := rulesave;
  end
  else
  begin
    q := mem[mem[29992].hh.rh].hh.rh;
    repeat
      mem[q + 3].int := mem[q + 1].int;
      mem[q + 1].int := 0;
      q := mem[mem[q].hh.rh].hh.rh;
    until q = 0;
    p := vpackage(mem[29992].hh.rh, savestack[saveptr + 1].int, savestack[saveptr + 0].int, 1073741823);
    q := mem[mem[29992].hh.rh].hh.rh;
    repeat
      mem[q + 1].int := mem[q + 3].int;
      mem[q + 3].int := 0;
      q := mem[mem[q].hh.rh].hh.rh;
    until q = 0;
  end;
  packbeginline := 0{:804}
;
  {805:}
q := mem[curlist.headfield].hh.rh;
  s := curlist.headfield;
  while q <> 0 do
  begin
    if not (q >= himemmin) then
      if mem[q].hh.b0 = 13 then
        {807:}
begin
        if curlist.modefield = -1 then
        begin
          mem[q].hh.b0 := 0;
          mem[q + 1].int := mem[p + 1].int;
        end
        else
        begin
          mem[q].hh.b0 := 1;
          mem[q + 3].int := mem[p + 3].int;
        end;
        mem[q + 5].hh.b1 := mem[p + 5].hh.b1;
        mem[q + 5].hh.b0 := mem[p + 5].hh.b0;
        mem[q + 6].gr := mem[p + 6].gr;
        mem[q + 4].int := o;
        r := mem[mem[q + 5].hh.rh].hh.rh;
        s := mem[mem[p + 5].hh.rh].hh.rh;
        repeat
          {808:}
n := mem[r].hh.b1;
          t := mem[s + 1].int;
          w := t;
          u := 29996;
          while n > 0 do
          begin
            n := n - 1;
            {809:}
s := mem[s].hh.rh;
            v := mem[s + 1].hh.lh;
            mem[u].hh.rh := newglue(v);
            u := mem[u].hh.rh;
            mem[u].hh.b1 := 12;
            t := t + mem[v + 1].int;
            if mem[p + 5].hh.b0 = 1 then
            begin
              if mem[v].hh.b0 = mem[p + 5].hh.b1 then
                t := t + round(mem[p + 6].gr * mem[v + 2].int);
            end
            else if mem[p + 5].hh.b0 = 2 then
              if mem[v].hh.b1 = mem[p + 5].hh.b1 then
                t := t - round(mem[p + 6].gr * mem[v + 3].int);
            s := mem[s].hh.rh;
            mem[u].hh.rh := newnullbox;
            u := mem[u].hh.rh;
            t := t + mem[s + 1].int;
            if curlist.modefield = -1 then
              mem[u + 1].int := mem[s + 1].int
            else
            begin
              mem[u].hh.b0 := 1;
              mem[u + 3].int := mem[s + 1].int;
            end{:809}
;
          end;
          if curlist.modefield = -1 then{810:}

          begin
            mem[r + 3].int := mem[q + 3].int;
            mem[r + 2].int := mem[q + 2].int;
            if t = mem[r + 1].int then
            begin
              mem[r + 5].hh.b0 := 0;
              mem[r + 5].hh.b1 := 0;
              mem[r + 6].gr := 0.0;
            end
            else if t > mem[r + 1].int then
            begin
              mem[r + 5].hh.b0 := 1;
              if mem[r + 6].int = 0 then
                mem[r + 6].gr := 0.0
              else
                mem[r + 6].gr := (t - mem[r + 1].int) / mem[r + 6].int;
            end
            else
            begin
              mem[r + 5].hh.b1 := mem[r + 5].hh.b0;
              mem[r + 5].hh.b0 := 2;
              if mem[r + 4].int = 0 then
                mem[r + 6].gr := 0.0
              else if (mem[r + 5].hh.b1 = 0) and (mem[r + 1].int - t > mem[r + 4].int) then
                mem[r + 6].gr := 1.0
              else
                mem[r + 6].gr := (mem[r + 1].int - t) / mem[r + 4].int;
            end;
            mem[r + 1].int := w;
            mem[r].hh.b0 := 0;
          end{:810}

          else{811:}

          begin
            mem[r + 1].int := mem[q + 1].int;
            if t = mem[r + 3].int then
            begin
              mem[r + 5].hh.b0 := 0;
              mem[r + 5].hh.b1 := 0;
              mem[r + 6].gr := 0.0;
            end
            else if t > mem[r + 3].int then
            begin
              mem[r + 5].hh.b0 := 1;
              if mem[r + 6].int = 0 then
                mem[r + 6].gr := 0.0
              else
                mem[r + 6].gr := (t - mem[r + 3].int) / mem[r + 6].int;
            end
            else
            begin
              mem[r + 5].hh.b1 := mem[r + 5].hh.b0;
              mem[r + 5].hh.b0 := 2;
              if mem[r + 4].int = 0 then
                mem[r + 6].gr := 0.0
              else if (mem[r + 5].hh.b1 = 0) and (mem[r + 3].int - t > mem[r + 4].int) then
                mem[r + 6].gr := 1.0
              else
                mem[r + 6].gr := (mem[r + 3].int - t) / mem[r + 4].int;
            end;
            mem[r + 3].int := w;
            mem[r].hh.b0 := 1;
          end{:811}
;
          mem[r + 4].int := 0;
          if u <> 29996 then
          begin
            mem[u].hh.rh := mem[r].hh.rh;
            mem[r].hh.rh := mem[29996].hh.rh;
            r := u;
          end{:808}
;
          r := mem[mem[r].hh.rh].hh.rh;
          s := mem[mem[s].hh.rh].hh.rh;
        until r = 0;
      end{:807}

      else if mem[q].hh.b0 = 2 then{806:}

      begin
        if (mem[q + 1].int = -1073741824) then
          mem[q + 1].int := mem[p + 1].int;
        if (mem[q + 3].int = -1073741824) then
          mem[q + 3].int := mem[p + 3].int;
        if (mem[q + 2].int = -1073741824) then
          mem[q + 2].int := mem[p + 2].int;
        if o <> 0 then
        begin
          r := mem[q].hh.rh;
          mem[q].hh.rh := 0;
          q := hpack(q, 0, 1);
          mem[q + 4].int := o;
          mem[q].hh.rh := r;
          mem[s].hh.rh := q;
        end;
      end{:806}
;
    s := q;
    q := mem[q].hh.rh;
  end{:805}
;
  flushnodelist(p);
  popalignment;
  {812:}
auxsave := curlist.auxfield;
  p := mem[curlist.headfield].hh.rh;
  q := curlist.tailfield;
  popnest;
  if curlist.modefield = 203 then{1206:}

  begin
    doassignments;
    if curcmd <> 3 then{1207:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(1169);
      end;
      begin
        helpptr := 2;
        helpline[1] := 894;
        helpline[0] := 895;
      end;
      backerror;
    end{:1207}

    else{1197:}

    begin
      getxtoken;
      if curcmd <> 3 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1165);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1166;
          helpline[0] := 1167;
        end;
        backerror;
      end;
    end{:1197}
;
    popnest;
    begin
      mem[curlist.tailfield].hh.rh := newpenalty(eqtb[5274].int);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    begin
      mem[curlist.tailfield].hh.rh := newparamglue(3);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    mem[curlist.tailfield].hh.rh := p;
    if p <> 0 then
      curlist.tailfield := q;
    begin
      mem[curlist.tailfield].hh.rh := newpenalty(eqtb[5275].int);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    begin
      mem[curlist.tailfield].hh.rh := newparamglue(4);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    curlist.auxfield.int := auxsave.int;
    resumeafterdisplay;
  end{:1206}

  else
  begin
    curlist.auxfield := auxsave;
    mem[curlist.tailfield].hh.rh := p;
    if p <> 0 then
      curlist.tailfield := q;
    if curlist.modefield = 1 then
      buildpage;
  end{:812}
;
end;
