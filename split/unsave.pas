procedure unsave;
label
  30;
var
  p: halfword;
  l: quarterword;
  t: halfword;
begin
  if curlevel > 1 then
  begin
    curlevel := curlevel - 1;
    {282:}
while true do
    begin
      saveptr := saveptr - 1;
      if savestack[saveptr].hh.b0 = 3 then
        goto 30;
      p := savestack[saveptr].hh.rh;
      if savestack[saveptr].hh.b0 = 2 then{326:}

      begin
        t := curtok;
        curtok := p;
        backinput;
        curtok := t;
      end{:326}

      else
      begin
        if savestack[saveptr].hh.b0 = 0 then
        begin
          l :=
            savestack[saveptr].hh.b1;
          saveptr := saveptr - 1;
        end
        else
          savestack[saveptr] := eqtb[2881];
        {283:}
if p < 5263 then
          if eqtb[p].hh.b1 = 1 then
            eqdestroy(savestack[saveptr]){if eqtb[5300].int>0 then restoretrace(p,544);}

          else
          begin
            eqdestroy(eqtb[p]);
            eqtb[p] := savestack[saveptr];
            {if eqtb[5300].int>0 then restoretrace(p,545);}

          end
        else if xeqlevel[p] <> 1 then
        begin
          eqtb[p] := savestack[saveptr];
          xeqlevel[p] := l;{if eqtb[5300].int>0 then restoretrace(p,545);}

        end
        else
          {if eqtb[5300].int>0 then restoretrace(p,544);}
{:283}
;
      end;
    end;
    30:
      curgroup := savestack[saveptr].hh.b1;
    curboundary := savestack[saveptr].hh.rh{:282}
;
  end
  else
    confusion(543);
end;
