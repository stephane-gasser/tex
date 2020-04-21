procedure error;
label
  22, 10;
var
  c: ASCIIcode;
  s1, s2, s3, s4: integer;
begin
  if history < 2 then
    history := 2;
  printchar(46);
  showcontext;
  if interaction = 3 then
    {83:}
while true do
    begin
      22:
        clearforerrorprompt;
      begin
        ;
        print(264);
        terminput;
      end;
      if last = First then
        goto 10;
      c := buffer[First];
      if c >= 97 then
        c := c - 32;
      {84:}
case c of
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57: if deletionsallowed then
            {88:}
begin
            s1 := curtok;
            s2 := curcmd;
            s3 := curchr;
            s4 := alignstate;
            alignstate := 1000000;
            OKtointerrupt := false;
            if (last > First + 1) and (buffer[First + 1] >= 48) and (buffer[First + 1] <= 57) then
              c :=
                c * 10 + buffer[First + 1] - 48 * 11
            else
              c := c - 48;
            while c > 0 do
            begin
              gettoken;
              c := c - 1;
            end;
            curtok := s1;
            curcmd := s2;
            curchr := s3;
            alignstate := s4;
            OKtointerrupt := true;
            begin
              helpptr := 2;
              helpline[1] := 279;
              helpline[0] := 280;
            end;
            showcontext;
            goto 22;
          end{:88}
;{68:begin debughelp;goto 22;end;}

        69: if baseptr > 0 then
          begin
            printnl(265);
            slowprint(inputstack[baseptr].namefield);
            print(266);
            printint(line);
            interaction := 2;
            jumpout;
          end;
        72:{89:}

        begin
          if useerrhelp then
          begin
            giveerrhelp;
            useerrhelp := false;
          end
          else
          begin
            if helpptr = 0 then
            begin
              helpptr := 2;
              helpline[1] := 281;
              helpline[0] := 282;
            end;
            repeat
              helpptr := helpptr - 1;
              print(helpline[helpptr]);
              println;
            until helpptr = 0;
          end;
          begin
            helpptr := 4;
            helpline[3] := 283;
            helpline[2] := 282;
            helpline[1] := 284;
            helpline[0] := 285;
          end;
          goto 22;
        end{:89}
;
        73:{87:}

        begin
          beginfilereading;
          if last > First + 1 then
          begin
            curinput.locfield := First + 1;
            buffer[First] := 32;
          end
          else
          begin
            begin
              ;
              print(278);
              terminput;
            end;
            curinput.locfield := First;
          end;
          First := last;
          curinput.limitfield := last - 1;
          goto 10;
        end{:87}
;
        81, 82, 83:{86:}

        begin
          errorcount := 0;
          interaction := 0 + c - 81;
          print(273);
          case c of
            81:
            begin
              printesc(274);
              selector := selector - 1;
            end;
            82: printesc(275);
            83: printesc(276);
          end;
          print(277);
          println;
          break(termout);
          goto 10;
        end{:86}
;
        88:
        begin
          interaction := 2;
          jumpout;
        end;
        others: end;
      {85:}
begin
        print(267);
        printnl(268);
        printnl(269);
        if baseptr > 0 then
          print(270);
        if deletionsallowed then
          printnl(271);
        printnl(272);
      end{:85}
{:84}
;
    end{:83}
;
  errorcount := errorcount + 1;
  if errorcount = 100 then
  begin
    printnl(263);
    history := 3;
    jumpout;
  end;
  {90:}
if interaction > 0 then
    selector := selector - 1;
  if useerrhelp then
  begin
    println;
    giveerrhelp;
  end
  else
    while helpptr > 0 do
    begin
      helpptr := helpptr - 1;
      printnl(helpline[helpptr]);
    end;
  println;
  if interaction > 0 then
    selector := selector + 1;
  println{:90}
;
  10: ;
end;

{:82}
{93:}


