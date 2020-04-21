procedure flushnodelist(p: halfword);
label
  30;
var
  q: halfword;
begin
  while p <> 0 do
  begin
    q := mem[p].hh.rh;
    if (p >= himemmin) then
    begin
      mem[p].hh.rh := avail;
      avail := p;
      {dynused:=dynused-1;}

    end
    else
    begin
      case mem[p].hh.b0 of
        0, 1, 13:
        begin
          flushnodelist(mem[p + 5].hh.rh);
          freenode(p, 7);
          goto 30;
        end;
        2:
        begin
          freenode(p, 4);
          goto 30;
        end;
        3:
        begin
          flushnodelist(mem[p + 4].hh.lh);
          deleteglueref(mem[p + 4].hh.rh);
          freenode(p, 5);
          goto 30;
        end;
        8:{1358:}

        begin
          case mem[p].hh.b1 of
            0: freenode(p, 3);
            1, 3:
            begin
              deletetokenref(mem[p + 1].hh.rh);
              freenode(p, 2);
              goto 30;
            end;
            2, 4: freenode(p, 2);
            others: confusion(1294)
          end;
          goto 30;
        end{:1358}
;
        10:
        begin
          begin
            if mem[mem[p + 1].hh.lh].hh.rh = 0 then
              freenode(mem[p + 1].hh.lh, 4)
            else
              mem[mem[p + 1].hh.lh].hh.rh := mem[mem[p + 1].hh.lh].hh.rh - 1;
          end;
          if mem[p + 1].hh.rh <> 0 then
            flushnodelist(mem[p + 1].hh.rh);
        end;
        11, 9, 12: ;
        6: flushnodelist(mem[p + 1].hh.rh);
        4: deletetokenref(mem[p + 1].int);
        7:
        begin
          flushnodelist(mem[p + 1].hh.lh);
          flushnodelist(mem[p + 1].hh.rh);
        end;
        5: flushnodelist(mem[p + 1].int);
        {698:}
14:
        begin
          freenode(p, 3);
          goto 30;
        end;
        15:
        begin
          flushnodelist(mem[p + 1].hh.lh);
          flushnodelist(mem[p + 1].hh.rh);
          flushnodelist(mem[p + 2].hh.lh);
          flushnodelist(mem[p + 2].hh.rh);
          freenode(p, 3);
          goto 30;
        end;
        16, 17, 18, 19, 20, 21, 22, 23, 24, 27, 26, 29, 28:
        begin
          if mem[p + 1].hh.rh >= 2 then
            flushnodelist(mem[p + 1].hh.lh);
          if mem[p + 2].hh.rh >= 2 then
            flushnodelist(mem[p + 2].hh.lh);
          if mem[p + 3].hh.rh >= 2 then
            flushnodelist(mem[p + 3].hh.lh);
          if mem[p].hh.b0 = 24 then
            freenode(p, 5)
          else if mem[p].hh.b0 = 28 then
            freenode(p, 5)
          else
            freenode(p, 4);
          goto 30;
        end;
        30, 31:
        begin
          freenode(p, 4);
          goto 30;
        end;
        25:
        begin
          flushnodelist(mem[p + 2].hh.lh);
          flushnodelist(mem[p + 3].hh.lh);
          freenode(p, 6);
          goto 30;
        end;
        {:698}
others: confusion(353)
      end;
      freenode(p, 2);
      30: ;
    end;
    p := q;
  end;
end;

