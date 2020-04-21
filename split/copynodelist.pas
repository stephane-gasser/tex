function copynodelist(p: halfword): halfword;
var
  h: halfword;
  q: halfword;
  r: halfword;
  words: 0..5;
begin
  h := getavail;
  q := h;
  while p <> 0 do
  begin
    {205:}
words := 1;
    if (p >= himemmin) then
      r := getavail
    else
      {206:}
case mem[p].hh.b0 of
        0, 1, 13:
        begin
          r := getnode(7);
          mem[r + 6] := mem[p + 6];
          mem[r + 5] := mem[p + 5];
          mem[r + 5].hh.rh := copynodelist(mem[p + 5].hh.rh);
          words := 5;
        end;
        2:
        begin
          r := getnode(4);
          words := 4;
        end;
        3:
        begin
          r := getnode(5);
          mem[r + 4] := mem[p + 4];
          mem[mem[p + 4].hh.rh].hh.rh := mem[mem[p + 4].hh.rh].hh.rh + 1;
          mem[r + 4].hh.lh := copynodelist(mem[p + 4].hh.lh);
          words := 4;
        end;
        8:{1357:}
case mem[p].hh.b1 of
            0:
            begin
              r := getnode(3);
              words := 3;
            end;
            1, 3:
            begin
              r := getnode(2);
              mem[mem[p + 1].hh.rh].hh.lh := mem[mem[p + 1].hh.rh].hh.lh + 1;
              words := 2;
            end;
            2, 4:
            begin
              r := getnode(2);
              words := 2;
            end;
            others: confusion(1293)
          end{:1357}
;
        10:
        begin
          r := getnode(2);
          mem[mem[p + 1].hh.lh].hh.rh := mem[mem[p + 1].hh.lh].hh.rh + 1;
          mem[r + 1].hh.lh := mem[p + 1].hh.lh;
          mem[r + 1].hh.rh := copynodelist(mem[p + 1].hh.rh);
        end;
        11, 9, 12:
        begin
          r := getnode(2);
          words := 2;
        end;
        6:
        begin
          r := getnode(2);
          mem[r + 1] := mem[p + 1];
          mem[r + 1].hh.rh := copynodelist(mem[p + 1].hh.rh);
        end;
        7:
        begin
          r := getnode(2);
          mem[r + 1].hh.lh := copynodelist(mem[p + 1].hh.lh);
          mem[r + 1].hh.rh := copynodelist(mem[p + 1].hh.rh);
        end;
        4:
        begin
          r := getnode(2);
          mem[mem[p + 1].int].hh.lh := mem[mem[p + 1].int].hh.lh + 1;
          words := 2;
        end;
        5:
        begin
          r := getnode(2);
          mem[r + 1].int := copynodelist(mem[p + 1].int);
        end;
        others: confusion(354)
      end{:206}
;
    while words > 0 do
    begin
      words := words - 1;
      mem[r + words] := mem[p + words];
    end{:205}
;
    mem[q].hh.rh := r;
    q := r;
    p := mem[p].hh.rh;
  end;
  mem[q].hh.rh := 0;
  q := mem[h].hh.rh;
  begin
    mem[h].hh.rh := avail;
    avail := h;{dynused:=dynused-1;}

  end;
  copynodelist := q;
end;
