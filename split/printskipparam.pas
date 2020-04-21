procedure printskipparam(n: integer);
begin
  case n of
    0: printesc(376);
    1: printesc(377);
    2: printesc(378);
    3: printesc(379);
    4: printesc(380);
    5: printesc(381);
    6: printesc(382);
    7: printesc(383);
    8: printesc(384);
    9: printesc(385);
    10: printesc(386);
    11: printesc(387);
    12: printesc(388);
    13: printesc(389);
    14: printesc(390);
    15: printesc(391);
    16: printesc(392);
    17: printesc(393);
    others: print(394)
  end;
end;
