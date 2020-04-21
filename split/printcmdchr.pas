procedure printcmdchr(cmd: quarterword; chrcode: halfword);
begin
  case cmd of
    1:
    begin
      print(557);
      print(chrcode);
    end;
    2:
    begin
      print(558);
      print(chrcode);
    end;
    3:
    begin
      print(559);
      print(chrcode);
    end;
    6:
    begin
      print(560);
      print(chrcode);
    end;
    7:
    begin
      print(561);
      print(chrcode);
    end;
    8:
    begin
      print(562);
      print(chrcode);
    end;
    9: print(563);
    10:
    begin
      print(564);
      print(chrcode);
    end;
    11:
    begin
      print(565);
      print(chrcode);
    end;
    12:
    begin
      print(566);
      print(chrcode);
    end;
    {227:}
75, 76: if chrcode < 2900 then
        printskipparam(chrcode - 2882)
      else if chrcode < 3156 then
      begin
        printesc(395);
        printint(chrcode - 2900);
      end
      else
      begin
        printesc(396);
        printint(chrcode - 3156);
      end;
    {:227}
{231:}
72: if chrcode >= 3422 then
      begin
        printesc(407);
        printint(chrcode - 3422);
      end
      else
        case chrcode of
          3413: printesc(398);
          3414: printesc(399);
          3415: printesc(400);
          3416: printesc(401);
          3417: printesc(402);
          3418: printesc(403);
          3419: printesc(404);
          3420: printesc(405);
          others: printesc(406)
        end;
    {:231}
{239:}
73: if chrcode < 5318 then
        printparam(chrcode - 5263)
      else
      begin
        printesc(476);
        printint(chrcode - 5318);
      end;
    {:239}
{249:}
74: if chrcode < 5851 then
        printlengthparam(chrcode - 5830)
      else
      begin
        printesc(500);
        printint(chrcode - 5851);
      end;
    {:249}
{266:}
45: printesc(508);
    90: printesc(509);
    40: printesc(510);
    41: printesc(511);
    77: printesc(519);
    61: printesc(512);
    42: printesc(531);
    16: printesc(513);
    107: printesc(504);
    88: printesc(518);
    15: printesc(514);
    92: printesc(515);
    67: printesc(505);
    62: printesc(516);
    64: printesc(32);
    102: printesc(517);
    32: printesc(520);
    36: printesc(521);
    39: printesc(522);
    37: printesc(330);
    44: printesc(47);
    18: printesc(351);
    46: printesc(523);
    17: printesc(524);
    54: printesc(525);
    91: printesc(526);
    34: printesc(527);
    65: printesc(528);
    103: printesc(529);
    55: printesc(335);
    63: printesc(530);
    66: printesc(533);
    96: printesc(534);
    0: printesc(535);
    98: printesc(536);
    80: printesc(532);
    84: printesc(408);
    109: printesc(537);
    71: printesc(407);
    38: printesc(352);
    33: printesc(538);
    56: printesc(539);
    35: printesc(540);
    {:266}
{335:}
13: printesc(597);
    {:335}
{377:}
104: if chrcode = 0 then
        printesc(629)
      else
        printesc(630);
    {:377}
{385:}
110: case chrcode of
        1: printesc(632);
        2: printesc(633);
        3: printesc(634);
        4: printesc(635);
        others: printesc(631)
      end;
    {:385}
{412:}
89: if chrcode = 0 then
        printesc(476)
      else if chrcode = 1 then
        printesc(500)
      else if chrcode = 2 then
        printesc(395)
      else
        printesc(396);
    {:412}
{417:}
79: if chrcode = 1 then
        printesc(669)
      else
        printesc(668);
    82: if chrcode = 0 then
        printesc(670)
      else
        printesc(671);
    83: if chrcode = 1 then
        printesc(672)
      else if chrcode = 3 then
        printesc(673)
      else
        printesc(674);
    70: case chrcode of
        0: printesc(675);
        1: printesc(676);
        2: printesc(677);
        3: printesc(678);
        others: printesc(679)
      end;
    {:417}
{469:}
108: case chrcode of
        0: printesc(735);
        1: printesc(736);
        2: printesc(737);
        3: printesc(738);
        4: printesc(739);
        others: printesc(740)
      end;
    {:469}
{488:}
105: case chrcode of
        1: printesc(757);
        2: printesc(758);
        3: printesc(759);
        4: printesc(760);
        5: printesc(761);
        6: printesc(762);
        7: printesc(763);
        8: printesc(764);
        9: printesc(765);
        10: printesc(766);
        11: printesc(767);
        12: printesc(768);
        13: printesc(769);
        14: printesc(770);
        15: printesc(771);
        16: printesc(772);
        others: printesc(756)
      end;
    {:488}
{492:}
106: if chrcode = 2 then
        printesc(773)
      else if chrcode = 4 then
        printesc(774)
      else
        printesc(775);
    {:492}
{781:}
4: if chrcode = 256 then
        printesc(897)
      else
      begin
        print(901);
        print(chrcode);
      end;
    5: if chrcode = 257 then
        printesc(898)
      else
        printesc(899);
    {:781}
{984:}
81: case chrcode of
        0: printesc(969);
        1: printesc(970);
        2: printesc(971);
        3: printesc(972);
        4: printesc(973);
        5: printesc(974);
        6: printesc(975);
        others: printesc(976)
      end;
    {:984}
{1053:}
14: if chrcode = 1 then
        printesc(1025)
      else
        printesc(1024);
    {:1053}
{1059:}
26: case chrcode of
        4: printesc(1026);
        0: printesc(1027);
        1: printesc(1028);
        2: printesc(1029);
        others: printesc(1030)
      end;
    27: case chrcode of
        4: printesc(1031);
        0: printesc(1032);
        1: printesc(1033);
        2: printesc(1034);
        others: printesc(1035)
      end;
    28: printesc(336);
    29: printesc(340);
    30: printesc(342);
    {:1059}
{1072:}
21: if chrcode = 1 then
        printesc(1053)
      else
        printesc(1054);
    22: if chrcode = 1 then
        printesc(1055)
      else
        printesc(1056);
    20: case chrcode of
        0: printesc(409);
        1: printesc(1057);
        2: printesc(1058);
        3: printesc(964);
        4: printesc(1059);
        5: printesc(966);
        others: printesc(1060)
      end;
    31: if chrcode = 100 then
        printesc(1062)
      else if chrcode = 101 then
        printesc(
          1063)
      else if chrcode = 102 then
        printesc(1064)
      else
        printesc(1061);
    {:1072}
{1089:}
43: if chrcode = 0 then
        printesc(1080)
      else
        printesc(1079);
    {:1089}
{1108:}
25: if chrcode = 10 then
        printesc(1091)
      else if chrcode = 11 then
        printesc(1090)
      else
        printesc(1089);
    23: if chrcode = 1 then
        printesc(1093)
      else
        printesc(1092);
    24: if chrcode = 1 then
        printesc(1095)
      else
        printesc(1094);
    {:1108}
{1115:}
47: if chrcode = 1 then
        printesc(45)
      else
        printesc(349);
    {:1115}
{1143:}
48: if chrcode = 1 then
        printesc(1127)
      else
        printesc(1126);
    {:1143}
{1157:}
50: case chrcode of
        16: printesc(865);
        17: printesc(866);
        18: printesc(867);
        19: printesc(868);
        20: printesc(869);
        21: printesc(870);
        22: printesc(871);
        23: printesc(872);
        26: printesc(874);
        others: printesc(873)
      end;
    51: if chrcode = 1 then
        printesc(877)
      else if chrcode = 2 then
        printesc(878)
      else
        printesc(1128);
    {:1157}
{1170:}
53: printstyle(chrcode);
    {:1170}
{1179:}
52: case chrcode of
        1: printesc(1147);
        2: printesc(1148);
        3: printesc(1149);
        4: printesc(1150);
        5: printesc(1151);
        others: printesc(1146)
      end;
    {:1179}
{1189:}
49: if chrcode = 30 then
        printesc(875)
      else
        printesc(876);
    {:1189}
{1209:}
93: if chrcode = 1 then
        printesc(1170)
      else if chrcode = 2 then
        printesc(1171)
      else
        printesc(1172);
    97: if chrcode = 0 then
        printesc(1173)
      else if chrcode = 1 then
        printesc(1174)
      else if chrcode = 2 then
        printesc(1175)
      else
        printesc(1176);
    {:1209}
{1220:}
94: if chrcode <> 0 then
        printesc(1191)
      else
        printesc(1190);
    {:1220}
{1223:}
95: case chrcode of
        0: printesc(1192);
        1: printesc(1193);
        2: printesc(1194);
        3: printesc(1195);
        4: printesc(1196);
        5: printesc(1197);
        others: printesc(1198)
      end;
    68:
    begin
      printesc(513);
      printhex(chrcode);
    end;
    69:
    begin
      printesc(524);
      printhex(chrcode);
    end;
    {:1223}
{1231:}
85: if chrcode = 3983 then
        printesc(415)
      else if chrcode = 5007 then
        printesc(419)
      else if chrcode = 4239 then
        printesc(416)
      else if chrcode = 4495 then
        printesc(417)
      else if chrcode = 4751 then
        printesc(418)
      else
        printesc(477);
    86: printsize(chrcode - 3935);
    {:1231}
{1251:}
99: if chrcode = 1 then
        printesc(952)
      else
        printesc(940);
    {:1251}
{1255:}
78: if chrcode = 0 then
        printesc(1216)
      else
        printesc(1217);
    {:1255}
{1261:}
87:
    begin
      print(1225);
      slowprint(fontname[chrcode]);
      if fontsize[chrcode] <> fontdsize[chrcode] then
      begin
        print(741);
        printscaled(fontsize[chrcode]);
        print(397);
      end;
    end;
    {:1261}
{1263:}
100: case chrcode of
        0: printesc(274);
        1: printesc(275);
        2: printesc(276);
        others: printesc(1226)
      end;
    {:1263}
{1273:}
60: if chrcode = 0 then
        printesc(1228)
      else
        printesc(1227);
    {:1273}
{1278:}
58: if chrcode = 0 then
        printesc(1229)
      else
        printesc(1230);
    {:1278}
{1287:}
57: if chrcode = 4239 then
        printesc(1236)
      else
        printesc(1237);
    {:1287}
{1292:}
19: case chrcode of
        1: printesc(1239);
        2: printesc(1240);
        3: printesc(1241);
        others: printesc(1238)
      end;
    {:1292}
{1295:}
101: print(1248);
    111: print(1249);
    112: printesc(1250);
    113: printesc(1251);
    114:
    begin
      printesc(1170);
      printesc(1251);
    end;
    115: printesc(1252);
    {:1295}
{1346:}
59: case chrcode of
        0: printesc(1284);
        1: printesc(594);
        2: printesc(1285);
        3: printesc(1286);
        4: printesc(1287);
        5: printesc(1288);
        others: print(1289)
      end;
    {:1346}
others: print(567)
  end;
end;
