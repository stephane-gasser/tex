#include "printcmdchr.h"
#include "printesc.h"
#include "print.h"
#include "printscaled.h"
#include "slowprint.h"
#include "printhex.h"
#include "printsize.h"
#include "printint.h"
#include "printparam.h"
#include "printlengthparam.h"
#include "printstyle.h"
#include "printskipparam.h"

void printcmdchr(quarterword cmd, halfword chrcode)
{
	switch (cmd)
	{
		case 1:
			print(557); //begin-group character 
			print(chrcode);
			break;
		case 2:
			print(558); //end-group character 
			print(chrcode);
			break;
		case 3:
			print(559); //math shift character 
			print(chrcode);
			break;
		case 6:
			print(560); //macro parameter character 
			print(chrcode);
			break;
		case 7:
			print(561); //superscript character 
			print(chrcode);
			break;
		case 8:
			print(562); //subscript character 
			print(chrcode);
			break;
		case 9: 
			print(563); //end of alignment template
			break;
		case 10:
			print(564); //blank space 
			print(chrcode);
			break;
		case 11:
			print(565); //the letter 
			print(chrcode);
			break;
		case 12:
			print(566); //the character 
			print(chrcode);
			break;
		case 75:
		case 76: 
			if (chrcode < 2900)
				printskipparam(chrcode-2882);
			else 
				if (chrcode < 3156)
				{
					printesc(395); //skip
					printint(chrcode-2900);
				}
				else
				{
					printesc(396); //muskip
					printint(chrcode-3156);
				}
			break;
		case 72: 
			if (chrcode >= 3422)
			{
				printesc(407); //toks
				printint(chrcode-3422);
			}
			else
				switch (chrcode)
				{
					case 3413: 
						printesc(398); //output
						break;
					case 3414: 
						printesc(399); //everypar
						break;
					case 3415: 
						printesc(400); //everymath
						break;
					case 3416: 
						printesc(401); //everydisplay
						break;
					case 3417: 
						printesc(402); //everyhbox
						break;
					case 3418: 
						printesc(403); //everyvbox
						break;
					case 3419: 
						printesc(404); //everyjob
						break;
					case 3420: 
						printesc(405); //everycr
						break;
					default: 
						printesc(406); //errhelp
				}
			break;
		case 73: 
			if (chrcode < 5318)
				printparam(chrcode-5263);
			else
			{
				printesc(476); //count
				printint(chrcode-5318);
			}
			break;
		case 74: 
			if (chrcode < 5851)
				printlengthparam(chrcode-5830);
			else
			{
				printesc(500); //dimen
				printint(chrcode-5851);
			}
			break;
		case 45: 
			printesc(508); //accent
			break;
		case 90: 
			printesc(509); //advance
			break;
		case 40: 
			printesc(510); //afterassignment
			break;
		case 41: 
			printesc(511); //aftergroup
			break;
		case 77: 
			printesc(519); //fontdimen
			break;
		case 61: 
			printesc(512); //begingroup
			break;
		case 42: 
			printesc(531); //penalty
			break;
		case 16: 
			printesc(513); //char
			break;
		case 107: 
			printesc(504); //csname
			break;
		case 88: 
			printesc(518); //font
			break;
		case 15: 
			printesc(514); //delimiter
			break;
		case 92: 
			printesc(515); //divide
			break;
		case 67: 
			printesc(505); //endcsname
			break;
		case 62: 
			printesc(516); //endgroup
			break;
		case 64: 
			printesc(' ');
			break;
		case 102: 
			printesc(517); //expandafter
			break;
		case 32: 
			printesc(520); //halign
			break;
		case 36: 
			printesc(521); //hrule
			break;
		case 39: 
			printesc(522); //ignorespaces
			break;
		case 37: 
			printesc(330); //insert
			break;
		case 44: 
			printesc('/');
			break;
		case 18: 
			printesc(351); //mark
			break;
		case 46: 
			printesc(523); //mathaccent
			break;
		case 17: 
			printesc(524); //mathchar
			break;
		case 54: 
			printesc(525); //mathchoice
			break;
		case 91: 
			printesc(526); //multiply
			break;
		case 34: 
			printesc(527); //noalign
			break;
		case 65: 
			printesc(528); //noboundary
			break;
		case 103: 
			printesc(529); //noexpand
			break;
		case 55: 
			printesc(335); //nonscript
			break;
		case 63: 
			printesc(530); //omit
			break;
		case 66: 
			printesc(533); //radical
			break;
		case 96: 
			printesc(534); //read
			break;
		case 0: 
			printesc(535); //relax
			break;
		case 98: 
			printesc(536); //setbox
			break;
		case 80: 
			printesc(532); //prevgraf
			break;
		case 84: 
			printesc(408); //parshape
			break;
		case 109: 
			printesc(537); //the
			break;
		case 71: 
			printesc(407); //toks
			break;
		case 38: 
			printesc(352); //vadjust
			break;
		case 33: 
			printesc(538); //valign
			break;
		case 56: 
			printesc(539); //vcenter
			break;
		case 35: 
			printesc(540); //vrule
			break;
		case 13: 
			printesc(597); //par
			break;
		case 104: 
			if (chrcode == 0)
				printesc(629); //input
			else
				printesc(630); //endinput
			break;
		case 110: 
			switch (chrcode)
			{
				case 1: 
					printesc(632); //firstmark
					break;
				case 2: 
					printesc(633); //botmark
					break;
				case 3: 
					printesc(634); //splitfirstmark
					break;
				case 4: 
					printesc(635); //splitbotmark
					break;
				default: 
					printesc(631); //topmark
			}
			break;
		case 89: 
			if (chrcode == 0)
				printesc(476); //count
			else 
				if (chrcode == 1)
					printesc(500); //dimen
				else 
					if (chrcode == 2)
						printesc(395); //skip
					else
						printesc(396); //muskip
			break;
		case 79: 
			if (chrcode == 1)
				printesc(669); //prevdepth
			else
				printesc(668); //spacefactor
			break;
		case 82: 
			if (chrcode == 0)
				printesc(670); //deadcycles
			else
				printesc(671); //insertpenalties
			break;
		case 83: 
			if (chrcode == 1)
				printesc(672); //wd
			else 
				if (chrcode == 3)
					printesc(673); //ht
				else
					printesc(674); //dp
			break;
		case 70: 
			switch (chrcode)
			{
				case 0: 
					printesc(675); //lastpenalty
					break;
				case 1: 
					printesc(676); //lastkern
					break;
				case 2: 
					printesc(677); //lastskip
					break;
				case 3: 
					printesc(678); //inputlineno
					break;
				default: 
					printesc(679); //badness
			}
			break;
		case 108: 
			switch (chrcode)
			{
				case 0: 
					printesc(735); //number
					break;
				case 1: 
					printesc(736); //romannumeral
					break;
				case 2: 
					printesc(737); //string
					break;
				case 3: 
					printesc(738); //meaning
					break;
				case 4: 
					printesc(739); //fontname
					break;
				default: 
					printesc(740); //jobname
			}
			break;
		case 105: 
			switch (chrcode)
			{
				case 1: 
					printesc(757); //ifcat
					break;
				case 2: 
					printesc(758); //ifnum
					break;
				case 3: 
					printesc(759); //ifdim
					break;
				case 4: 
					printesc(760); //ifodd
					break;
				case 5: 
					printesc(761); //ifvmode
					break;
				case 6: 
					printesc(762); //ifhmode
					break;
				case 7: 
					printesc(763); //ifmmode
					break;
				case 8: 
					printesc(764); //ifinner
					break;
				case 9: 
					printesc(765); //ifvoid
					break;
				case 10: 
					printesc(766); //ifhbox
					break;
				case 11: 
					printesc(767); //ifvbox
					break;
				case 12: 
					printesc(768); //ifx
					break;
				case 13: 
					printesc(769); //ifeof
					break;
				case 14: 
					printesc(770); //iftrue
					break;
				case 15: 
					printesc(771); //iffalse
					break;
				case 16: 
					printesc(772); //ifcase
					break;
			default: 
				printesc(756); //if
			}
			break;
		case 106: 
			if (chrcode == 2)
				printesc(773); //fi
			else 
				if (chrcode == 4)
					printesc(774); //or
				else
					printesc(775); //else
			break;
		case 4: 
			if (chrcode == 256)
				printesc(897); //span
			else
			{
				print(901); //alignment tab character 
				print(chrcode);
			}
			break;
		case 5: 
			if (chrcode == 257)
				printesc(898); //cr
			else
				printesc(899); //crcr
			break;
		case 81: 
			switch (chrcode)
			{
				case 0: 
					printesc(969); //pagegoal
					break;
				case 1: 
					printesc(970); //pagetotal
					break;
				case 2: 
					printesc(971); //pagestretch
					break;
				case 3: 
					printesc(972); //pagefilstretch
					break;
				case 4: 
					printesc(973); //pagefillstretch
					break;
				case 5: 
					printesc(974); //pagefilllstretch
					break;
				case 6: 
					printesc(975); //pageshrink
					break;
				default: 
					printesc(976); //pagedepth
			}
			break;
		case 14: 
			if (chrcode == 1)
				printesc(1025); //dump
			else
				printesc(1024); //end
			break;
		case 26: 
			switch (chrcode)
			{
				case 4: 
					printesc(1026); //hskip
					break;
				case 0: 
					printesc(1027); //hfil
					break;
				case 1: 
					printesc(1028); //hfill
					break;
				case 2: 
					printesc(1029); //hss
					break;
				default: 
					printesc(1030); //hfilneg
			}
			break;
		case 27: 
			switch (chrcode)
			{
				case 4: 
					printesc(1031); //vskip
					break;
				case 0: 
					printesc(1032); //vfil
					break;
				case 1: 
					printesc(1033); //vfill
					break;
				case 2: 
					printesc(1034); //vss
					break;
				default: 
					printesc(1035); //vfilneg
			}
			break;
		case 28: 
			printesc(336); //mskip
			break;
		case 29: 
			printesc(340); //kern
			break;
		case 30: 
			printesc(342); //mkern
			break;
		case 21: 
			if (chrcode == 1)
				printesc(1053); //moveleft
			else
				printesc(1054); //moveright
			break;
		case 22: 
			if (chrcode == 1)
				printesc(1055); //raise
			else
				printesc(1056); //lower
			break;
		case 20: 
			switch (chrcode)
			{
				case 0: 
					printesc(409); //box
					break;
				case 1: 
					printesc(1057); //copy
					break;
				case 2: 
					printesc(1058); //lastbox
					break;
				case 3: 
					printesc(964); //vsplit
					break;
				case 4: 
					printesc(1059); //vtop
					break;
				case 5: 
					printesc(966); //vbox
					break;
				default: 
					printesc(1060); //hbox
			}
			break;
		case 31: 
			if (chrcode == 100)
				printesc(1062); //leaders
			else 
				if (chrcode == 101)
					printesc(1063); //cleaders
				else 
					if (chrcode == 102)
						printesc(1064); //xleaders
					else
						printesc(1061); //shipout
			break;
		case 43: 
			if (chrcode == 0)
				printesc(1080); //noindent
			else
				printesc(1079); //indent
			break;
		case 25: 
			if (chrcode == 10)
				printesc(1091); //unskip
				else 
					if (chrcode == 11)
						printesc(1090); //unkern
					else
						printesc(1089); //unpenalty
			break;
		case 23: 
			if (chrcode == 1)
				printesc(1093); //unhcopy
			else
				printesc(1092); //unhbox
			break;
		case 24: 
			if (chrcode == 1)
				printesc(1095); //unvcopy
			else
			printesc(1094); //unvbox
			break;
		case 47: 
			if (chrcode == 1)
				printesc('-');
			else
				printesc(349); //discretionary
			break;
		case 48: 
			if (chrcode == 1)
				printesc(1127); //leqno
			else
				printesc(1126); //eqno
			break;
		case 50: 
			switch (chrcode)
			{
				case 16: 
					printesc(865); //mathord
					break;
				case 17: 
					printesc(866); //mathop
					break;
				case 18: 
					printesc(867); //mathbin
					break;
				case 19: 
					printesc(868); //mathrel
					break;
				case 20: 
					printesc(869); //mathopen
					break;
				case 21: 
					printesc(870); //mathclose
					break;
				case 22: 
					printesc(871); //mathpunct
					break;
				case 23: 
					printesc(872); //mathinner
					break;
				case 26: 
					printesc(874); //overline
					break;
				default: 
					printesc(873); //underline
			}
			break;
		case 51: 
			if (chrcode == 1)
			printesc(877); //limits
			else 
				if (chrcode == 2)
					printesc(878); //nolimits
				else
				printesc(1128); //displaylimits
			break;
		case 53: 
			printstyle(chrcode);
			break;
		case 52: 
			switch (chrcode)
			{
				case 1: 
					printesc(1147); //over
					break;
				case 2: 
					printesc(1148); //atop
					break;
				case 3: 
					printesc(1149); //abovewithdelims
					break;
				case 4: 
					printesc(1150); //overwithdelims
					break;
				case 5: 
					printesc(1151); //atopwithdelims
					break;
				default: 
					printesc(1146); //above
			}
			break;
		case 49: 
			if (chrcode == 30)
				printesc(875); //left
			else
				printesc(876); //right
			break;
		case 93: 
			if (chrcode == 1)
				printesc(1170); //long
			else 
				if (chrcode == 2)
					printesc(1171); //outer
				else
					printesc(1172); //global
		case 97: 
			if (chrcode == 0)
				printesc(1173); //def
			else 
				if (chrcode == 1)
					printesc(1174); //gdef
				else 
					if (chrcode == 2)
						printesc(1175); //edef
					else
						printesc(1176); //xdef
			break;
		case 94: 
			if (chrcode)
				printesc(1191); //futurelet
			else
				printesc(1190); //let
			break;
		case 95: 
			switch (chrcode)
			{
				case 0: 
					printesc(1192); //chardef
					break;
				case 1: 
					printesc(1193); //mathchardef
					break;
				case 2: 
					printesc(1194); //countdef
					break;
				case 3: 
					printesc(1195); //dimendef
					break;
				case 4: 
					printesc(1196); //skipdef
					break;
				case 5: 
					printesc(1197); //muskipdef
					break;
				default: printesc(1198); //toksdef
			}
			break;
		case 68:
			printesc(513); //char
			printhex(chrcode);
			break;
		case 69:
			printesc(524); //delimiter
			printhex(chrcode);
			break;
		case 85: 
			if (chrcode == 3983)
				printesc(415); //catcode
			else 
				if (chrcode == 5007)
					printesc(419); //mathcode
				else 
					if (chrcode == 4239)
						printesc(416); //lccode
					else 
						if (chrcode == 4495)
							printesc(417); //uccode
						else 
							if (chrcode == 4751)
								printesc(418); //sfcode
							else
								printesc(477); //delcode
			break;
		case 86: 
			printsize(chrcode-3935);
			break;
		case 99: 
			if (chrcode == 1)
				printesc(952); //patterns
			else
				printesc(940); //hyphenation
			break;
		case 78: 
			if (chrcode == 0)
				printesc(1216); //hyphenchar
			else
				printesc(1217); //skewchar
			break;
		case 87:
			print(1225); //select font 
			slowprint(fontname[chrcode]);
			if (fontsize[chrcode] != fontdsize[chrcode])
			{
				print(741); // at 
				printscaled(fontsize[chrcode]);
				print(397); //pt
			}
			break;
		case 100: 
			switch (chrcode)
			{
				case 0: 
					printesc(274); //batchmode
					break;
				case 1: 
					printesc(275); //nonstopmode
					break;
				case 2: 
					printesc(276); //scrollmode
					break;
				default: 
					printesc(1226); //errorstopmode
			}
			break;
		case 60: 
			if (chrcode == 0)
				printesc(1228); //closein
			else
				printesc(1227); //openin
			break;
		case 58: 
			if (chrcode == 0)
				printesc(1229); //message
			else
				printesc(1230); //errmessage
			break;
		case 57: 
			if (chrcode == 4239)
				printesc(1236); //lowercase
			else
				printesc(1237); //uppercase
			break;
		case 19: 
			switch (chrcode)
			{
				case 1: 
					printesc(1239); //showbox
					break;
				case 2: 
					printesc(1240); //showthe
					break;
				case 3: 
					printesc(1241); //showlists
					break;
				default: 
					printesc(1238); //show
			}
			break;
		case 101: 
			print(1248); //undefined
			break;
		case 111: 
			print(1249); //macro
			break;
		case 112: 
			printesc(1250); //long macro
			break;
		case 113: 
			printesc(1251); //outer macro
			break;
		case 114:
			printesc(1170); //long
			printesc(1251); //outer macro
			break;
		case 115: 
			printesc(1252); //outer endtemplate
			break;
		case 59: 
			switch (chrcode)
			{
				case 0: 
					printesc(1284); //openout
					break;
				case 1: 
					printesc(594); //write
					break;
				case 2: 
					printesc(1285); //closeout
					break;
				case 3: 
					printesc(1286); //special
					break;
				case 4: 
					printesc(1287); //immediate
					break;
				case 5: 
					printesc(1288); //setlanguage
					break;
				default: 
					print(1289); //[unknown extension!]
			}
			break;
		default: 
			print(567); //[unknown command code!]
	}
}
