#include "issuemessage.h"
void issuemessage(void)
var
  oldsetting: 0..21;
  c: 0..1;
  s: strnumber;
begin
  c := curchr;
  mem[29988].hh.rh := scantoks(false, true);
  oldsetting := selector;
  selector := 21;
  tokenshow(defref);
  selector := oldsetting;
  flushlist(defref);
  begin
    if poolptr + 1 > poolsize then
      overflow(257, poolsize - initpoolptr);
  end;
  s := makestring;
  if c = 0 then{1280:}

  begin
    if termoffset + (strstart[s + 1] - strstart[s]) > maxprintline - 2 then
      println
    else if (termoffset > 0) or (fileoffset > 0) then
      printchar(32);
    slowprint(s);
    break(termout);
  end{:1280}

  else{1283:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(338);
    end;
    slowprint(s);
    if eqtb[3421].hh.rh <> 0 then
      useerrhelp := true
    else if longhelpseen then
    begin
      helpptr := 1;
      helpline[0] := 1231;
    end
    else
    begin
      if interaction < 3 then
        longhelpseen := true;
      begin
        helpptr := 4;
        helpline[3] := 1232;
        helpline[2] := 1233;
        helpline[1] := 1234;
        helpline[0] := 1235;
      end;
    end;
    error;
    useerrhelp := false;
  end{:1283}
;
  begin
    strptr := strptr - 1;
    poolptr := strstart[strptr];
  end;
end;
