#include "loadfmtfile.h"
bool loadfmtfile(void)
label
  6666, 10;
var
  j, k: integer;
  p, q: halfword;
  x: integer;
  w: fourquarters;
{
  
x = fmtfile^.int;
  if (x != 117275187)
    goto 6666;
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if (x != 0)
    goto 6666;
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if (x != 30000)
    goto 6666;
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if (x != 6106)
    goto 6666;
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if (x != 1777)
    goto 6666;
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if (x != 307)
    goto 6666
;
  
{
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 0)
      goto 6666;
    if (x > poolsize)
    {
      ;
      writeln(termout, '---! Must increase the ', 'string pool size');
      goto 6666;
    }
    else
      poolptr = x;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 0)
      goto 6666;
    if (x > maxstrings)
    {
      ;
      writeln(termout, '---! Must increase the ', 'max strings');
      goto 6666;
    }
    else
      strptr = x;
  }
  for k = 0 to strptr do
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (x > poolptr))
      goto 6666
    else
      strstart[k] = x;
  }
  k = 0;
  while k+4 < poolptr do
  {
    {
      get(fmtfile);
      w = fmtfile^.qqqq;
    }
    strpool[k] = w.b0-0;
    strpool[k+1] = w.b1-0;
    strpool[k+2] = w.b2-0;
    strpool[k+3] = w.b3-0;
    k = k+4;
  }
  k = poolptr-4;
  {
    get(fmtfile);
    w = fmtfile^.qqqq;
  }
  strpool[k] = w.b0-0;
  strpool[k+1] = w.b1-0;
  strpool[k+2] = w.b2-0;
  strpool[k+3] = w.b3-0;
  initstrptr = strptr;
  initpoolptr = poolptr
;

  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 1019) or (x > 29986))
      goto 6666
    else
      lomemmax = x;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 20) or (x > lomemmax))
      goto 6666
    else
      rover = x;
  }
  p = 0;
  q = rover;
  repeat
    for k = p to q+1 do
    {
      get(fmtfile);
      mem[k] = fmtfile^;
    }
    p = q+mem[q].hh.lh;
    if ((p > lomemmax) or ((q >= mem[q+1].hh.rh) and (mem[q+1].hh.rh != rover)))
      goto6666;
    q = mem[q+1].hh.rh;
  until q == rover;
  for k = p to lomemmax do
  {
    get(fmtfile);
    mem[k] = fmtfile^;
  }
  if (memmin < -2)
  {
    p = mem[rover+1].hh.lh;
    q = memmin+1;
    mem[memmin].hh.rh = 0;
    mem[memmin].hh.lh = 0;
    mem[p+1].hh.rh = q;
    mem[rover+1].hh.lh = q;
    mem[q+1].hh.rh = rover;
    mem[q+1].hh.lh = p;
    mem[q].hh.rh = 65535;
    mem[q].hh.lh = -0-q;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < lomemmax+1) or (x > 29987))
      goto 6666
    else
      himemmin = x;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (x > 30000))
      goto 6666
    else
      avail = x;
  }
  memend = 30000;
  for k = himemmin to memend do
  {
    get(fmtfile);
    mem[k] = fmtfile^;
  }
  {
    get(fmtfile);
    varused = fmtfile^.int;
  }
  {
    get(fmtfile);
    dynused = fmtfile^.int;
  }
;
  

k = 1;
  repeat
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 1) or (k+x > 6107))
      goto 6666;
    for j = k to k+x-1 do
    {
      get(fmtfile);
      eqtb[j] = fmtfile^;
    }
    k = k+x;
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (k+x > 6107))
      goto 6666;
    for j = k to k+x-1 do
      eqtb[j] = eqtb[k-1];
    k = k+x;
  until k > 6106
;
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 514) or (x > 2614))
      goto 6666
    else
      parloc = x;
  }
  partoken = 4095+parloc;
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 514) or (x > 2614))
      goto 6666
    else
      writeloc = x;
  }
  
{
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 514) or (x > 2614))
      goto 6666
    else
      hashused = x;
  }
  p = 513;
  repeat
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < p+1) or (x > hashused))
        goto 6666
      else
        p = x;
    }
    {
      get(fmtfile);
      hash[p] = fmtfile^.hh;
    }
  until p == hashused;
  for p = hashused+1 to 2880 do
  {
    get(fmtfile);
    hash[p] = fmtfile^.hh;
  }
  {
    get(fmtfile);
    cscount = fmtfile^.int;
  }

;
  
{
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 7)
      goto 6666;
    if (x > fontmemsize)
    {
      ;
      writeln(termout, '---! Must increase the ', 'font mem size');
      goto 6666;
    }
    else
      fmemptr = x;
  }
  for k = 0 to fmemptr-1 do
  {
    get(fmtfile);
    fontinfo[k] = fmtfile^;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 0)
      goto 6666;
    if (x > fontmax)
    {
      ;
      writeln(termout, '---! Must increase the ', 'font max');
      goto 6666;
    }
    else
      fontptr = x;
  }
  for k = 0 to fontptr do

  {
    {
      get(fmtfile);
      fontcheck[k] = fmtfile^.qqqq;
    }
    {
      get(fmtfile);
      fontsize[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      fontdsize[k] = fmtfile^.int;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 65535))
        goto 6666
      else
        fontparams[k] = x;
    }
    {
      get(fmtfile);
      hyphenchar[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      skewchar[k] = fmtfile^.int;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > strptr))
        goto 6666
      else
        fontname[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > strptr))
        goto 6666
      else
        fontarea[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 255))
        goto 6666
      else
        fontbc[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 255))
        goto 6666
      else
        fontec[k] = x;
    }
    {
      get(fmtfile);
      charbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      widthbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      heightbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      depthbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      italicbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      ligkernbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      kernbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      extenbase[k] = fmtfile^.int;
    }
    {
      get(fmtfile);
      parambase[k] = fmtfile^.int;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > lomemmax))
        goto 6666
      else
        fontglue[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > fmemptr-1))
        goto 6666
      else
        bcharlabel[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 256))
        goto 6666
      else
        fontbchar[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 256))
        goto 6666
      else
        fontfalsebchar[k] = x;
    }
  }

;

  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (x > 307))
      goto 6666
    else
      hyphcount = x;
  }
  for k = 1 to hyphcount do
  {
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 307))
        goto 6666
      else
        j = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > strptr))
        goto 6666
      else
        hyphword[j] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 65535))
        goto 6666
      else
        hyphlist[j] = x;
    }
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 0)
      goto 6666;
    if (x > triesize)
    {
      ;
      writeln(termout, '---! Must increase the ', 'trie size');
      goto 6666;
    }
    else
      j = x;
  }
  triemax = j;
  for k = 0 to j do
  {
    get(fmtfile);
    trie[k] = fmtfile^.hh;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if (x < 0)
      goto 6666;
    if (x > trieopsize)
    {
      ;
      writeln(termout, '---! Must increase the ', 'trie op size');
      goto 6666;
    }
    else
      j = x;
  }
  trieopptr = j;
  for k = 1 to j do
  {
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 63))
        goto 6666
      else
        hyfdistance[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 63))
        goto 6666
      else
        hyfnum[k] = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > 255))
        goto 6666
      else
        hyfnext[k] = x;
    }
  }
  for k = 0 to 255 do
    trieused[k] = 0;
  k = 256;
  while j > 0 do
  {
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 0) or (x > k-1))
        goto 6666
      else
        k = x;
    }
    {
      {
        get(fmtfile);
        x = fmtfile^.int;
      }
      if ((x < 1) or (x > j))
        goto 6666
      else
        x = x;
    }
    trieused[k] = x+0;
    j = j-x;
    opstart[k] = j-0;
  }
  trienotready = false
;
  
{
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (x > 3))
      goto 6666
    else
      interaction = x;
  }
  {
    {
      get(fmtfile);
      x = fmtfile^.int;
    }
    if ((x < 0) or (x > strptr))
      goto 6666
    else
      formatident = x;
  }
  {
    get(fmtfile);
    x = fmtfile^.int;
  }
  if ((x != 69069) or EOF(fmtfile))
    goto 6666
;
  loadfmtfile = true;
  goto 10;
  6666: ;
  writeln(termout, '(Fatal format file error; I''m stymied)');
  loadfmtfile = false;
  10: ;
}
