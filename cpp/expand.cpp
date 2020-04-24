#include "expand.h"
void expand(void)
var
  t: halfword;
  p, q, r: halfword;
  j: 0..bufsize;
  cvbackup: integer;
  cvlbackup, radixbackup, cobackup: smallnumber;
  backupbackup: halfword;
  savescannerstatus: smallnumber;
begin
  cvbackup := curval;
  cvlbackup := curvallevel;
  radixbackup := radix;
  cobackup := curorder;
  backupbackup := mem[29987].hh.rh;
  if curcmd < 111 then{367:}

  begin
    if eqtb[5299].int > 1 then
      showcurcmdchr;
    case curcmd of
      110:{386:}
if curmark[curchr] <> 0 then
          begintokenlist(curmark[curchr], 14){:386}
;
      102:{368:}

      begin
        gettoken;
        t := curtok;
        gettoken;
        if curcmd > 100 then
          expand
        else
          backinput;
        curtok := t;
        backinput;
      end{:368}
;
      103:{369:}

      begin
        savescannerstatus := scannerstatus;
        scannerstatus := 0;
        gettoken;
        scannerstatus := savescannerstatus;
        t := curtok;
        backinput;
        if t >= 4095 then
        begin
          p := getavail;
          mem[p].hh.lh := 6718;
          mem[p].hh.rh := curinput.locfield;
          curinput.startfield := p;
          curinput.locfield := p;
        end;
      end{:369}
;
      107:{372:}

      begin
        r := getavail;
        p := r;
        repeat
          getxtoken;
          if curcs = 0 then
          begin
            q := getavail;
            mem[p].hh.rh := q;
            mem[q].hh.lh := curtok;
            p := q;
          end;
        until curcs <> 0;
        if curcmd <> 67 then{373:}

        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(625);
          end;
          printesc(505);
          print(626);
          begin
            helpptr := 2;
            helpline[1] := 627;
            helpline[0] := 628;
          end;
          backerror;
        end{:373}
;
        {374:}
j := First;
        p := mem[r].hh.rh;
        while p <> 0 do
        begin
          if j >= maxbufstack then
          begin
            maxbufstack := j + 1;
            if maxbufstack = bufsize then
              overflow(256, bufsize);
          end;
          buffer[j] := mem[p].hh.lh mod 256;
          j := j + 1;
          p := mem[p].hh.rh;
        end;
        if j > First + 1 then
        begin
          nonewcontrolsequence := false;
          curcs := idlookup(First, j - First);
          nonewcontrolsequence := true;
        end
        else if j = First then
          curcs := 513
        else
          curcs := 257 + buffer[First]{:374}
;
        flushlist(r);
        if eqtb[curcs].hh.b0 = 101 then
          eqdefine(curcs, 0, 256);
        curtok := curcs + 4095;
        backinput;
      end{:372}
;
      108: convtoks;
      109: insthetoks;
      105: conditional;
      106:{510:}
if curchr > iflimit then
          if iflimit = 1 then
            insertrelax
          else
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(776);
            end;
            printcmdchr(106, curchr);
            begin
              helpptr := 1;
              helpline[0] := 777;
            end;
            error;
          end
        else
        begin
          while curchr <> 2 do
            passtext;{496:}

          begin
            p := condptr;
            ifline := mem[p + 1].int;
            curif := mem[p].hh.b1;
            iflimit := mem[p].hh.b0;
            condptr := mem[p].hh.rh;
            freenode(p, 2);
          end{:496}
;
        end{:510}
;
      104:{378:}
if curchr > 0 then
          forceeof := true
        else if nameinprogress then
          insertrelax
        else
          startinput{:378}
;
      others:{370:}

      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(619);
        end;
        begin
          helpptr := 5;
          helpline[4] := 620;
          helpline[3] := 621;
          helpline[2] := 622;
          helpline[1] := 623;
          helpline[0] := 624;
        end;
        error;
      end{:370}

    end;
  end{:367}

  else if curcmd < 115 then
    macrocall
  else{375:}

  begin
    curtok := 6715;
    backinput;
  end{:375}
;
  curval := cvbackup;
  curvallevel := cvlbackup;
  radix := radixbackup;
  curorder := cobackup;
  mem[29987].hh.rh := backupbackup;
end;
