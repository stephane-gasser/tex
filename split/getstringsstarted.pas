function getstringsstarted: boolean;
label
  30, 10;
var
  k, l: 0..255;
  m, n: char;
  g: strnumber;
  a: integer;
  c: boolean;
begin
  poolptr := 0;
  strptr := 0;
  strstart[0] := 0;
  {48:}
for k := 0 to 255 do
  begin
    if ({49:}
(k < 32) or (k > 126){:49}
) then
    begin
      begin
        strpool[poolptr] := 94;
        poolptr := poolptr + 1;
      end;
      begin
        strpool[poolptr] := 94;
        poolptr := poolptr + 1;
      end;
      if k < 64 then
      begin
        strpool[poolptr] := k + 64;
        poolptr := poolptr + 1;
      end
      else if k < 128 then
      begin
        strpool[poolptr] := k - 64;
        poolptr := poolptr + 1;
      end
      else
      begin
        l := k div 16;
        if l < 10 then
        begin
          strpool[poolptr] := l + 48;
          poolptr := poolptr + 1;
        end
        else
        begin
          strpool[poolptr] := l + 87;
          poolptr := poolptr + 1;
        end;
        l := k mod 16;
        if l < 10 then
        begin
          strpool[poolptr] := l + 48;
          poolptr := poolptr + 1;
        end
        else
        begin
          strpool[poolptr] := l + 87;
          poolptr := poolptr + 1;
        end;
      end;
    end
    else
    begin
      strpool[poolptr] := k;
      poolptr := poolptr + 1;
    end;
    g := makestring;
  end{:48}
;
  {51:}
nameoffile := poolname;
  if aopenin(poolfile) then
  begin
    c := false;
    repeat{52:}

      begin
        if EOF(poolfile) then
        begin
          ;
          writeln(termout, '! TEX.POOL has no check sum.');
          aclose(poolfile);
          getstringsstarted := false;
          goto 10;
        end;
        read(poolfile, m, n);
        if m = '*' then{53:}

        begin
          a := 0;
          k := 1;
          while true do
          begin
            if (xord[n] < 48) or (xord[n] > 57) then
            begin
              ;
              writeln(termout, '! TEX.POOL check sum doesn''t have nine digits.');
              aclose(poolfile);
              getstringsstarted := false;
              goto 10;
            end;
            a := 10 * a + xord[n] - 48;
            if k = 9 then
              goto 30;
            k := k + 1;
            read(poolfile, n);
          end;
          30:
            if a <> 117275187 then
            begin
              ;
              writeln(termout, '! TEX.POOL doesn''t match; TANGLE me again.');
              aclose(poolfile);
              getstringsstarted := false;
              goto 10;
            end;
          c := true;
        end{:53}

        else
        begin
          if (xord[m] < 48) or (xord[m] > 57) or (xord[n] < 48) or (xord[n] > 57) then
          begin
            ;
            writeln(termout, '! TEX.POOL line doesn''t begin with two digits.');
            aclose(poolfile);
            getstringsstarted := false;
            goto 10;
          end;
          l := xord[m] * 10 + xord[n] - 48 * 11;
          if poolptr + l + stringvacancies > poolsize then
          begin
            ;
            writeln(termout, '! You have to increase POOLSIZE.');
            aclose(poolfile);
            getstringsstarted := false;
            goto 10;
          end;
          for k := 1 to l do
          begin
            if eoln(poolfile) then
              m := ' '
            else
              read(poolfile, m);
            begin
              strpool[poolptr] := xord[m];
              poolptr := poolptr + 1;
            end;
          end;
          readln(poolfile);
          g := makestring;
        end;
      end{:52}
;
    until c;
    aclose(poolfile);
    getstringsstarted := true;
  end
  else
  begin
    ;
    writeln(termout, '! I can''t read TEX.POOL.');
    aclose(poolfile);
    getstringsstarted := false;
    goto 10;
  end{:51}
;
  10: ;
end;

