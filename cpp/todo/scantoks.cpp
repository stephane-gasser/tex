#include "scantoks.h"
halfword scantoks(bool macrodef, bool  xpand)
label
  40, 30, 31, 32;
var
  t: halfword;
  s: halfword;
  p: halfword;
  q: halfword;
  unbalance: halfword;
  hashbrace: halfword;
begin
  if macrodef then
    scannerstatus := 2
  else
    scannerstatus := 5;
  warningindex := curcs;
  defref := getavail;
  mem[defref].hh.lh := 0;
  p := defref;
  hashbrace := 0;
  t := 3120;
  if macrodef then{474:}

  begin
    while true do
    begin
      gettoken;
      if curtok < 768 then
        goto 31;
      if curcmd = 6 then{476:}

      begin
        s := 3328 + curchr;
        gettoken;
        if curcmd = 1 then
        begin
          hashbrace := curtok;
          begin
            q := getavail;
            mem[p].hh.rh := q;
            mem[q].hh.lh := curtok;
            p := q;
          end;
          begin
            q := getavail;
            mem[p].hh.rh := q;
            mem[q].hh.lh := 3584;
            p := q;
          end;
          goto 30;
        end;
        if t = 3129 then
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(744);
          end;
          begin
            helpptr := 1;
            helpline[0] := 745;
          end;
          error;
        end
        else
        begin
          t := t + 1;
          if curtok <> t then
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(746);
            end;
            begin
              helpptr := 2;
              helpline[1] := 747;
              helpline[0] := 748;
            end;
            backerror;
          end;
          curtok := s;
        end;
      end{:476}
;
      begin
        q := getavail;
        mem[p].hh.rh := q;
        mem[q].hh.lh := curtok;
        p := q;
      end;
    end;
    31:
    begin
      q := getavail;
      mem[p].hh.rh := q;
      mem[q].hh.lh := 3584;
      p := q;
    end;
    if curcmd = 2 then{475:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(657);
      end;
      alignstate := alignstate + 1;
      begin
        helpptr := 2;
        helpline[1] := 742;
        helpline[0] := 743;
      end;
      error;
      goto 40;
    end{:475}
;
    30: ;
  end{:474}

  else
    scanleftbrace;
  {477:}
unbalance := 1;
  while true do
  begin
    if xpand then{478:}

    begin
      while true do
      begin
        getnext;
        if curcmd <= 100 then
          goto 32;
        if curcmd <> 109 then
          expand
        else
        begin
          q := thetoks;
          if mem[29997].hh.rh <> 0 then
          begin
            mem[p].hh.rh := mem[29997].hh.rh;
            p := q;
          end;
        end;
      end;
      32:
        xtoken;
    end{:478}

    else
      gettoken;
    if curtok < 768 then
      if curcmd < 2 then
        unbalance := unbalance + 1
      else
      begin
        unbalance := unbalance - 1;
        if unbalance = 0 then
          goto 40;
      end
    else if curcmd = 6 then
      if macrodef then{479:}

      begin
        s := curtok;
        if xpand then
          getxtoken
        else
          gettoken;
        if curcmd <> 6 then
          if (curtok <= 3120) or (curtok > t) then
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(749);
            end;
            sprintcs(warningindex);
            begin
              helpptr := 3;
              helpline[2] := 750;
              helpline[1] := 751;
              helpline[0] := 752;
            end;
            backerror;
            curtok := s;
          end
          else
            curtok := 1232 + curchr;
      end{:479}
;
    begin
      q := getavail;
      mem[p].hh.rh := q;
      mem[q].hh.lh := curtok;
      p := q;
    end;
  end{:477}
;
  40:
    scannerstatus := 0;
  if hashbrace <> 0 then
  begin
    q := getavail;
    mem[p].hh.rh := q;
    mem[q].hh.lh := hashbrace;
    p := q;
  end;
  scantoks := p;
end;
