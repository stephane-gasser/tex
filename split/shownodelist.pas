procedure shownodelist(p: integer);
label
  10;
var
  n: integer;
  g: real;
begin
  if (poolptr - strstart[strptr]) > depththreshold then
  begin
    if p > 0 then
      print(314);
    goto 10;
  end;
  n := 0;
  while p > memmin do
  begin
    println;
    printcurrentstring;
    if p > memend then
    begin
      print(315);
      goto 10;
    end;
    n := n + 1;
    if n > breadthmax then
    begin
      print(316);
      goto 10;
    end;
    {183:}
if (p >= himemmin) then
      printfontandchar(p)
    else
      case mem[p].hh.b0 of
        0, 1, 13:{184:}

        begin
          if mem[p].hh.b0 = 0 then
            printesc(104)
          else if mem[p].hh.b0 = 1 then
            printesc(118)
          else
            printesc(318);
          print(319);
          printscaled(mem[p + 3].int);
          printchar(43);
          printscaled(mem[p + 2].int);
          print(320);
          printscaled(mem[p + 1].int);
          if mem[p].hh.b0 = 13 then{185:}

          begin
            if mem[p].hh.b1 <> 0 then
            begin
              print(
                286);
              printint(mem[p].hh.b1 + 1);
              print(322);
            end;
            if mem[p + 6].int <> 0 then
            begin
              print(323);
              printglue(mem[p + 6].int, mem[p + 5].hh.b1, 0);
            end;
            if mem[p + 4].int <> 0 then
            begin
              print(324);
              printglue(mem[p + 4].int, mem[p + 5].hh.b0, 0);
            end;
          end{:185}

          else
          begin
            {186:}
g := mem[p + 6].gr;
            if (g <> 0.0) and (mem[p + 5].hh.b0 <> 0) then
            begin
              print(325);
              if mem[p + 5].hh.b0 = 2 then
                print(326);
              if abs(mem[p + 6].int) < 1048576 then
                print(327)
              else if abs(g) > 20000.0 then
              begin
                if g > 0.0 then
                  printchar(62)
                else
                  print(328);
                printglue(20000 * 65536, mem[p + 5].hh.b1, 0);
              end
              else
                printglue(round(65536 * g), mem[p + 5].hh.b1, 0);
            end{:186}
;
            if mem[p + 4].int <> 0 then
            begin
              print(321);
              printscaled(mem[p + 4].int);
            end;
          end;
          begin
            begin
              strpool[poolptr] := 46;
              poolptr := poolptr + 1;
            end;
            shownodelist(mem[p + 5].hh.rh);
            poolptr := poolptr - 1;
          end;
        end{:184}
;
        2:{187:}

        begin
          printesc(329);
          printruledimen(mem[p + 3].int);
          printchar(43);
          printruledimen(mem[p + 2].int);
          print(320);
          printruledimen(mem[p + 1].int);
        end{:187}
;
        3:{188:}

        begin
          printesc(330);
          printint(mem[p].hh.b1 - 0);
          print(331);
          printscaled(mem[p + 3].int);
          print(332);
          printspec(mem[p + 4].hh.rh, 0);
          printchar(44);
          printscaled(mem[p + 2].int);
          print(333);
          printint(mem[p + 1].int);
          begin
            begin
              strpool[poolptr] := 46;
              poolptr := poolptr + 1;
            end;
            shownodelist(mem[p + 4].hh.lh);
            poolptr := poolptr - 1;
          end;
        end{:188}
;
        8:{1356:}
case mem[p].hh.b1 of
            0:
            begin
              printwritewhatsit(1284, p);
              printchar(61);
              printfilename(mem[p + 1].hh.rh, mem[p + 2].hh.lh, mem[p + 2].hh.rh);
            end;
            1:
            begin
              printwritewhatsit(594, p);
              printmark(mem[p + 1].hh.rh);
            end;
            2: printwritewhatsit(1285, p);
            3:
            begin
              printesc(1286);
              printmark(mem[p + 1].hh.rh);
            end;
            4:
            begin
              printesc(1288);
              printint(mem[p + 1].hh.rh);
              print(1291);
              printint(mem[p + 1].hh.b0);
              printchar(44);
              printint(mem[p + 1].hh.b1);
              printchar(41);
            end;
            others: print(1292)
          end{:1356}
;
        10:{189:}
if mem[p].hh.b1 >= 100 then{190:}

          begin
            printesc(338);
            if mem[p].hh.b1 = 101 then
              printchar(99)
            else if mem[p].hh.b1 = 102 then
              printchar(120);
            print(339);
            printspec(mem[p + 1].hh.lh, 0);
            begin
              begin
                strpool[poolptr] := 46;
                poolptr := poolptr + 1;
              end;
              shownodelist(mem[p + 1].hh.rh);
              poolptr := poolptr - 1;
            end;
          end{:190}

          else
          begin
            printesc(334);
            if mem[p].hh.b1 <> 0 then
            begin
              printchar(40);
              if mem[p].hh.b1 < 98 then
                printskipparam(mem[p].hh.b1 - 1)
              else if mem[p].hh.b1 = 98 then
                printesc(335)
              else
                printesc(336);
              printchar(41);
            end;
            if mem[p].hh.b1 <> 98 then
            begin
              printchar(32);
              if mem[p].hh.b1 < 98 then
                printspec(mem[p + 1].hh.lh, 0)
              else
                printspec(mem[p + 1].hh.lh, 337);
            end;
          end{:189}
;
        11:{191:}
if mem[p].hh.b1 <> 99 then
          begin
            printesc(340);
            if mem[p].hh.b1 <> 0 then
              printchar(32);
            printscaled(mem[p + 1].int);
            if mem[p].hh.b1 = 2 then
              print(341);
          end
          else
          begin
            printesc(342);
            printscaled(mem[p + 1].int);
            print(337);
          end{:191}
;
        9:{192:}

        begin
          printesc(343);
          if mem[p].hh.b1 = 0 then
            print(344)
          else
            print(345);
          if mem[p + 1].int <> 0 then
          begin
            print(346);
            printscaled(mem[p + 1].int);
          end;
        end{:192}
;
        6:{193:}

        begin
          printfontandchar(p + 1);
          print(347);
          if mem[p].hh.b1 > 1 then
            printchar(124);
          fontinshortdisplay := mem[p + 1].hh.b0;
          shortdisplay(mem[p + 1].hh.rh);
          if odd(mem[p].hh.b1) then
            printchar(124);
          printchar(41);
        end{:193}
;
        12:{194:}

        begin
          printesc(348);
          printint(mem[p + 1].int);
        end{:194}
;
        7:{195:}

        begin
          printesc(349);
          if mem[p].hh.b1 > 0 then
          begin
            print(350);
            printint(mem[p].hh.b1);
          end;
          begin
            begin
              strpool[poolptr] := 46;
              poolptr := poolptr + 1;
            end;
            shownodelist(mem[p + 1].hh.lh);
            poolptr := poolptr - 1;
          end;
          begin
            strpool[poolptr] := 124;
            poolptr := poolptr + 1;
          end;
          shownodelist(mem[p + 1].hh.rh);
          poolptr := poolptr - 1;
        end{:195}
;
        4:{196:}

        begin
          printesc(351);
          printmark(mem[p + 1].int);
        end{:196}
;
        5:{197:}

        begin
          printesc(352);
          begin
            begin
              strpool[poolptr] := 46;
              poolptr := poolptr + 1;
            end;
            shownodelist(mem[p + 1].int);
            poolptr := poolptr - 1;
          end;
        end{:197}
;
        {690:}
14: printstyle(mem[p].hh.b1);
        15:{695:}

        begin
          printesc(525);
          begin
            strpool[poolptr] := 68;
            poolptr := poolptr + 1;
          end;
          shownodelist(mem[p + 1].hh.lh);
          poolptr := poolptr - 1;
          begin
            strpool[poolptr] := 84;
            poolptr := poolptr + 1;
          end;
          shownodelist(mem[p + 1].hh.rh);
          poolptr := poolptr - 1;
          begin
            strpool[poolptr] := 83;
            poolptr := poolptr + 1;
          end;
          shownodelist(mem[p + 2].hh.lh);
          poolptr := poolptr - 1;
          begin
            strpool[poolptr] := 115;
            poolptr := poolptr + 1;
          end;
          shownodelist(mem[p + 2].hh.rh);
          poolptr := poolptr - 1;
        end{:695}
;
        16, 17, 18, 19, 20, 21, 22, 23, 24, 27, 26, 29, 28, 30, 31:{696:}

        begin
          case mem[p].hh.b0 of
            16: printesc(865);
            17: printesc(866);
            18: printesc(867);
            19: printesc(868);
            20: printesc(869);
            21: printesc(870);
            22: printesc(871);
            23: printesc(872);
            27: printesc(873);
            26: printesc(874);
            29: printesc(539);
            24:
            begin
              printesc(533);
              printdelimiter(p + 4);
            end;
            28:
            begin
              printesc(508);
              printfamandchar(p + 4);
            end;
            30:
            begin
              printesc(875);
              printdelimiter(p + 1);
            end;
            31:
            begin
              printesc(876);
              printdelimiter(p + 1);
            end;
          end;
          if mem[p].hh.b1 <> 0 then
            if mem[p].hh.b1 = 1 then
              printesc(877)
            else
              printesc(878);
          if mem[p].hh.b0 < 30 then
            printsubsidiarydata(p + 1, 46);
          printsubsidiarydata(p + 2, 94);
          printsubsidiarydata(p + 3, 95);
        end{:696}
;
        25:{697:}

        begin
          printesc(879);
          if mem[p + 1].int = 1073741824 then
            print(880)
          else
            printscaled(mem[p + 1].int);
          if (mem[p + 4].qqqq.b0 <> 0) or (mem[p + 4].qqqq.b1 <> 0) or (mem[p + 4].qqqq.b2 <> 0) or (mem[p + 4].qqqq.b3 <> 0) then
          begin
            print(881);
            printdelimiter(p + 4);
          end;
          if (mem[p + 5].qqqq.b0 <> 0) or (mem[p + 5].qqqq.b1 <> 0) or (mem[p + 5].qqqq.b2 <> 0) or (mem[p + 5].qqqq.b3 <> 0) then
          begin
            print(882);
            printdelimiter(p + 5);
          end;
          printsubsidiarydata(p + 2, 92);
          printsubsidiarydata(p + 3, 47);
        end{:697}
;
        {:690}
others: print(317)
      end{:183}
;
    p := mem[p].hh.rh;
  end;
  10: ;
end;
