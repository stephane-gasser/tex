#include "fmtfile.h"
#include "impression.h" 
#include "erreur.h"
#include "jumpout.h"
#include "equivalent.h"
#include "chaine.h"
#include "cesure.h"
#include "police.h"
#include "fichier.h"
#include <iostream>
#include <map>

static std::map<std::string, int> texte;

static int txt(const std::string&s)
{
	if (texte.find(s) != texte.end())
	{
		for (int i = 0; i < 256; i++)
			texte[std::string(1, i)] = i;
		texte["buffer size"] = 256;
		texte["pool size"] = 257;
		texte["number of strings"] = 258;
		texte["???"] = 259;
		texte["m2d5c2l5x2v5i"] = 260;
		texte["End of file on the terminal!"] = 261;
		texte["! "] = 262;
		texte["(That makes 100 errors; please try again.)"] = 263;
		texte["? "] = 264;
		texte["You want to edit file "] = 265;
		texte[" at line "] = 266;
		texte["Type <return> to proceed, S to scroll future error messages,"] = 267;
		texte["R to run without stopping, Q to run quietly,"] = 268;
		texte["I to insert something, "] = 269;
		texte["E to edit your file,"] = 270;
		texte["1 or ... or 9 to ignore the next 1 to 9 tokens of input,"] = 271;
		texte["H for help, X to quit."] = 272;
		texte["OK, entering "] = 273;
		texte["batchmode"] = 274;
		texte["nonstopmode"] = 275;
		texte["scrollmode"] = 276;
		texte["..."] = 277;
		texte["insert>"] = 278;
		texte["I have just deleted some text, as you asked."] = 279;
		texte["You can now delete more, or insert, or whatever."] = 280;
		texte["Sorry, I don't know how to help in this situation."] = 281;
		texte["Maybe you should try asking a human?"] = 282;
		texte["Sorry, I already gave what help I could..."] = 283;
		texte["An error might have occurred before I noticed any problems."] = 284;
		texte["``If all else fails, read the instructions.''"] = 285;
		texte[" ("] = 286;
		texte["Emergency stop"] = 287;
		texte["TeX capacity exceeded, sorry ["] = 288;
		texte["If you really absolutely need more capacity,"] = 289;
		texte["you can ask a wizard to enlarge me."] = 290;
		texte["This can't happen ("] = 291;
		texte["I'm broken. Please show this to someone who can fix can fix"] = 292;
		texte["I can't go on meeting you like this"] = 293;
		texte["One of your faux pas seems to have wounded me deeply..."] = 294;
		texte["in fact, I'm barely conscious. Please fix it and try again."] = 295;
		texte["Interruption"] = 296;
		texte["You rang?"] = 297;
		texte["Try to insert some instructions for me (e.g.,`I\\showlists'),"] = 298;
		texte["unless you just want to quit by typing `X'."] = 299;
		texte["main memory size"] = 300;
		texte["AVAIL list clobbered at "] = 301;
		texte["Double-AVAIL list clobbered at "] = 302;
		texte["Doubly free location at "] = 303;
		texte["Bad flag at "] = 304;
		texte["New busy locs:"] = 305;
		texte["LINK("] = 306;
		texte["INFO("] = 307;
		texte["[]"] = 308;
		texte["CLOBBERED."] = 309;
		texte["foul"] = 310;
		texte["fil"] = 311;
		texte[" plus "] = 312;
		texte[" minus "] = 313;
		texte[" []"] = 314;
		texte["Bad link, display aborted."] = 315;
		texte["etc."] = 316;
		texte["Unknown node type!"] = 317;
		texte["unset"] = 318;
		texte["box("] = 319;
		texte[")x"] = 320;
		texte[", shifted "] = 321;
		texte[" columns)"] = 322;
		texte[", stretch "] = 323;
		texte[", shrink "] = 324;
		texte[", glue set "] = 325;
		texte["- "] = 326;
		texte["?.?"] = 327;
		texte["< -"] = 328;
		texte["rule("] = 329;
		texte["insert"] = 330;
		texte[", natural size "] = 331;
		texte["; split("] = 332;
		texte["); float cost "] = 333;
		texte["glue"] = 334;
		texte["nonscript"] = 335;
		texte["mskip"] = 336;
		texte["mu"] = 337;
		texte[""] = 338;
		texte["leaders "] = 339;
		texte["kern"] = 340;
		texte[" (for accent)"] = 341;
		texte["mkern"] = 342;
		texte["math"] = 343;
		texte["on"] = 344;
		texte["off"] = 345;
		texte[", surrounded "] = 346;
		texte[" (ligature "] = 347;
		texte["penalty "] = 348;
		texte["discretionary"] = 349;
		texte[" replacing "] = 350;
		texte["mark"] = 351;
		texte["vadjust"] = 352;
		texte["flushing"] = 353;
		texte["copying"] = 354;
		texte["vertical"] = 355;
		texte["horizontal"] = 356;
		texte["display math"] = 357;
		texte["no"] = 358;
		texte["internal vertical"] = 359;
		texte["restricted horizontal"] = 360;
		texte[" mode"] = 361;
		texte["semantic nest size"] = 362;
		texte["### "] = 363;
		texte[" entered at line "] = 364;
		texte[" (language"] = 365;
		texte[":hyphenmin"] = 366;
		texte[" (\\output routine)"] = 367;
		texte["### recent contributions:"] = 368;
		texte["prevdepth "] = 369;
		texte["ignored"] = 370;
		texte[", prevgraf "] = 371;
		texte[" line"] = 372;
		texte["spacefactor "] = 373;
		texte[", current language "] = 374;
		texte["this will be denominator of:"] = 375;
		texte["lineskip"] = 376;
		texte["baselineskip"] = 377;
		texte["parskip"] = 378;
		texte["abovedisplayskip"] = 379;
		texte["belowdisplayskip"] = 380;
		texte["abovedisplayshortskip"] = 381;
		texte["belowdisplayshortskip"] = 382;
		texte["leftskip"] = 383;
		texte["rightskip"] = 384;
		texte["topskip"] = 385;
		texte["splittopskip"] = 386;
		texte["tabskip"] = 387;
		texte["spaceskip"] = 388;
		texte["xspaceskip"] = 389;
		texte["parfillskip"] = 390;
		texte["thinmuskip"] = 391;
		texte["medmuskip"] = 392;
		texte["thickmuskip"] = 393;
		texte["[unknown glue parameter!]"] = 394;
		texte["skip"] = 395;
		texte["muskip"] = 396;
		texte["pt"] = 397;
		texte["output"] = 398;
		texte["everypar"] = 399;
		texte["everymath"] = 400;
		texte["everydisplay"] = 401;
		texte["everyhbox"] = 402;
		texte["everyvbox"] = 403;
		texte["everyjob"] = 404;
		texte["everycr"] = 405;
		texte["errhelp"] = 406;
		texte["toks"] = 407;
		texte["parshape"] = 408;
		texte["box"] = 409;
		texte["void"] = 410;
		texte["current font"] = 411;
		texte["textfont"] = 412;
		texte["scriptfont"] = 413;
		texte["scriptscriptfont"] = 414;
		texte["catcode"] = 415;
		texte["lccode"] = 416;
		texte["uccode"] = 417;
		texte["sfcode"] = 418;
		texte["mathcode"] = 419;
		texte["pretolerance"] = 420;
		texte["tolerance"] = 421;
		texte["linepenalty"] = 422;
		texte["hyphenpenalty"] = 423;
		texte["exhyphenpenalty"] = 424;
		texte["clubpenalty"] = 425;
		texte["widowpenalty"] = 426;
		texte["displaywidowpenalty"] = 427;
		texte["brokenpenalty"] = 428;
		texte["binoppenalty"] = 429;
		texte["relpenalty"] = 430;
		texte["predisplaypenalty"] = 431;
		texte["postdisplaypenalty"] = 432;
		texte["interlinepenalty"] = 433;
		texte["doublehyphendemerits"] = 434;
		texte["finalhyphendemerits"] = 435;
		texte["adjdemerits"] = 436;
		texte["mag"] = 437;
		texte["delimiterfactor"] = 438;
		texte["looseness"] = 439;
		texte["time"] = 440;
		texte["day"] = 441;
		texte["month"] = 442;
		texte["year"] = 443;
		texte["showboxbreadth"] = 444;
		texte["showboxdepth"] = 445;
		texte["hbadness"] = 446;
		texte["vbadness"] = 447;
		texte["pausing"] = 448;
		texte["tracingonline"] = 449;
		texte["tracingmacros"] = 450;
		texte["tracingstats"] = 451;
		texte["tracingparagraphs"] = 452;
		texte["tracingpages"] = 453;
		texte["tracingoutput"] = 454;
		texte["tracinglostchars"] = 455;
		texte["tracingcommands"] = 456;
		texte["tracingrestores"] = 457;
		texte["uchyph"] = 458;
		texte["outputpenalty"] = 459;
		texte["maxdeadcycles"] = 460;
		texte["hangafter"] = 461;
		texte["floatingpenalty"] = 462;
		texte["globaldefs"] = 463;
		texte["fam"] = 464;
		texte["escapechar"] = 465;
		texte["defaulthyphenchar"] = 466;
		texte["defaultskewchar"] = 467;
		texte["endlinechar"] = 468;
		texte["newlinechar"] = 469;
		texte["language"] = 470;
		texte["lefthyphenmin"] = 471;
		texte["righthyphenmin"] = 472;
		texte["holdinginserts"] = 473;
		texte["errorcontextlines"] = 474;
		texte["[unknown integer parameter!]"] = 475;
		texte["count"] = 476;
		texte["delcode"] = 477;
		texte["parindent"] = 478;
		texte["mathsurround"] = 479;
		texte["lineskiplimit"] = 480;
		texte["hsize"] = 481;
		texte["vsize"] = 482;
		texte["maxdepth"] = 483;
		texte["splitmaxdepth"] = 484;
		texte["boxmaxdepth"] = 485;
		texte["hfuzz"] = 486;
		texte["vfuzz"] = 487;
		texte["delimitershortfall"] = 488;
		texte["nulldelimiterspace"] = 489;
		texte["scriptspace"] = 490;
		texte["predisplaysize"] = 491;
		texte["displaywidth"] = 492;
		texte["displayindent"] = 493;
		texte["overfullrule"] = 494;
		texte["hangindent"] = 495;
		texte["hoffset"] = 496;
		texte["voffset"] = 497;
		texte["emergencystretch"] = 498;
		texte["[unknown dimen parameter!]"] = 499;
		texte["dimen"] = 500;
		texte["EQUIV("] = 501;
		texte["notexpanded:"] = 502;
		texte["hash size"] = 503;
		texte["csname"] = 504;
		texte["endcsname"] = 505;
		texte["IMPOSSIBLE."] = 506;
		texte["NONEXISTENT."] = 507;
		texte["accent"] = 508;
		texte["advance"] = 509;
		texte["afterassignment"] = 510;
		texte["aftergroup"] = 511;
		texte["begingroup"] = 512;
		texte["char"] = 513;
		texte["delimiter"] = 514;
		texte["divide"] = 515;
		texte["endgroup"] = 516;
		texte["expandafter"] = 517;
		texte["font"] = 518;
		texte["fontdimen"] = 519;
		texte["halign"] = 520;
		texte["hrule"] = 521;
		texte["ignorespaces"] = 522;
		texte["mathaccent"] = 523;
		texte["mathchar"] = 524;
		texte["mathchoice"] = 525;
		texte["multiply"] = 526;
		texte["noalign"] = 527;
		texte["noboundary"] = 528;
		texte["noexpand"] = 529;
		texte["omit"] = 530;
		texte["penalty"] = 531;
		texte["prevgraf"] = 532;
		texte["radical"] = 533;
		texte["read"] = 534;
		texte["relax"] = 535;
		texte["setbox"] = 536;
		texte["the"] = 537;
		texte["valign"] = 538;
		texte["vcenter"] = 539;
		texte["vrule"] = 540;
		texte["save size"] = 541;
		texte["grouping levels"] = 542;
		texte["curlevel"] = 543;
		texte["retaining"] = 544;
		texte["restoring"] = 545;
		texte["SAVE("] = 546;
		texte["Incompatible magnification ("] = 547;
		texte[");"] = 548;
		texte[" the previous value will be retained"] = 549;
		texte["I can handle only one magnification ratio per job. So I've"] = 550;
		texte["reverted to the magnification you used earlier on this run."] = 551;
		texte["Illegal magnification has been changed to 1000"] = 552;
		texte["The magnification ratio must be between 1 and 32768."] = 553;
		texte["ETC."] = 554;
		texte["BAD."] = 555;
		texte["->"] = 556;
		texte["begin-group character "] = 557;
		texte["end-group character "] = 558;
		texte["math shift character "] = 559;
		texte["macro parameter character "] = 560;
		texte["superscript character "] = 561;
		texte["subscript character "] = 562;
		texte["end of alignment template"] = 563;
		texte["blank space "] = 564;
		texte["the letter "] = 565;
		texte["the character "] = 566;
		texte["[unknown command code!]"] = 567;
		texte[": "] = 568;
		texte["Runaway "] = 569;
		texte["definition"] = 570;
		texte["argument"] = 571;
		texte["preamble"] = 572;
		texte["text"] = 573;
		texte["<*>"] = 574;
		texte["<insert> "] = 575;
		texte["<read "] = 576;
		texte["l."] = 577;
		texte["<argument> "] = 578;
		texte["<template> "] = 579;
		texte["<recently read> "] = 580;
		texte["<to be read again> "] = 581;
		texte["<inserted text> "] = 582;
		texte["<output> "] = 583;
		texte["<everypar> "] = 584;
		texte["<everymath> "] = 585;
		texte["<everydisplay> "] = 586;
		texte["<everyhbox> "] = 587;
		texte["<everyvbox> "] = 588;
		texte["<everyjob> "] = 589;
		texte["<everycr> "] = 590;
		texte["<mark> "] = 591;
		texte["<write> "] = 592;
		texte["input stack size"] = 593;
		texte["write"] = 594;
		texte["(interwoven alignment preambles are not allowed)"] = 595;
		texte["text input levels"] = 596;
		texte["par"] = 597;
		texte["Incomplete "] = 598;
		texte["; all text was ignored after line "] = 599;
		texte["A forbidden control sequence occurred in skipped text."] = 600;
		texte["This kind of error happens when you say `\\if...' and forget"] = 601;
		texte["the matching `\\fi'. I've inserted a `\\fi'; this might work."] = 602;
		texte["The file ended while I was skipping conditional text."] = 603;
		texte["File ended"] = 604;
		texte["Forbidden control sequence found"] = 605;
		texte[" while scanning "] = 606;
		texte[" of "] = 607;
		texte["I suspect you have forgotten a `}', causing me"] = 608;
		texte["to read past where you wanted me to stop."] = 609;
		texte["I'll try to recover; but if the error is serious,"] = 610;
		texte["you'd better type `E' or `X' now and fix your file."] = 611;
		texte["use"] = 612;
		texte["Text line contains an invalid character"] = 613;
		texte["A funny symbol that I can't read has just been input."] = 614;
		texte["Continue, and I'll forget that it ever happened."] = 615;
		texte["(Please type a command or say `\\end')"] = 616;
		texte["*** (job aborted, no legal \\end found)"] = 617;
		texte["=>"] = 618;
		texte["Undefined control sequence"] = 619;
		texte["The control sequence at the end of the top line"] = 620;
		texte["of your error message was never \\def'ed. If you have"] = 621;
		texte["misspelled it (e.g., `\\hobx'), type `I' and the correct"] = 622;
		texte["spelling (e.g., `I\\hbox'). Otherwise just continue,"] = 623;
		texte["and I'll forget about whatever was undefined."] = 624;
		texte["Missing "] = 625;
		texte[" inserted"] = 626;
		texte["The control sequence marked <to be read again> should"] = 627;
		texte["not appear between \\csname and \\endcsname."] = 628;
		texte["input"] = 629;
		texte["endinput"] = 630;
		texte["topmark"] = 631;
		texte["firstmark"] = 632;
		texte["botmark"] = 633;
		texte["splitfirstmark"] = 634;
		texte["splitbotmark"] = 635;
		texte["parameter stack size"] = 636;
		texte["Argument of "] = 637;
		texte[" has an extra }"] = 638;
		texte["I've run across a `}' that doesn't seem to match anything."] = 639;
		texte["For example, `\\def\\a#1{...}' and `\\a}' would produce"] = 640;
		texte["this error. If you simply proceed now, the `\\par' that"] = 641;
		texte["I've just inserted will cause me to report a runaway"] = 642;
		texte["argument that might be the root of the problem. But if"] = 643;
		texte["your `}' was spurious, just type `2' and it will go away."] = 644;
		texte["Paragraph ended before "] = 645;
		texte[" was complete"] = 646;
		texte["I suspect you've forgotten a `}', causing me to apply this"] = 647;
		texte["control sequence to too much text. How can we recover?"] = 648;
		texte["My plan is to forget the whole thing and hope for the best."] = 649;
		texte["Use of "] = 650;
		texte[" doesn't match its definition"] = 651;
		texte["If you say, e.g., `\\def\\a1{...}', then you must always"] = 652;
		texte["put `1' after `\\a', since control sequence names are"] = 653;
		texte["made up of letters only. The macro here has not been"] = 654;
		texte["followed by the required stuff, so I'm ignoring it."] = 655;
		texte["<-"] = 656;
		texte["Missing { inserted"] = 657;
		texte["A left brace was mandatory here, so I've put one in."] = 658;
		texte["You might want to delete and/or insert some corrections"] = 659;
		texte["so that I will find a matching right brace soon."] = 660;
		texte["(If you're confused by all this, try typing `I}' now.)"] = 661;
		texte["Incompatible glue units"] = 662;
		texte["I'm going to assume that 1mu=1pt when they're mixed."] = 663;
		texte["Missing number, treated as zero"] = 664;
		texte["A number should have been here; I inserted `0'."] = 665;
		texte["(If you can't figure out why I needed to see a number,"] = 666;
		texte["look up `weird error' in the index to The TeXbook.)"] = 667;
		texte["spacefactor"] = 668;
		texte["prevdepth"] = 669;
		texte["deadcycles"] = 670;
		texte["insertpenalties"] = 671;
		texte["wd"] = 672;
		texte["ht"] = 673;
		texte["dp"] = 674;
		texte["lastpenalty"] = 675;
		texte["lastkern"] = 676;
		texte["lastskip"] = 677;
		texte["inputlineno"] = 678;
		texte["badness"] = 679;
		texte["Improper "] = 680;
		texte["You can refer to \\spacefactor only in horizontal mode;"] = 681;
		texte["you can refer to \\prevdepth only in vertical mode; and"] = 682;
		texte["neither of these is meaningful inside \\write. So"] = 683;
		texte["I'm forgetting what you said and using zero instead."] = 684;
		texte["You can't use `"] = 685;
		texte["' after "] = 686;
		texte["Bad register code"] = 687;
		texte["A register number must be between 0 and 255."] = 688;
		texte["I changed this one to zero."] = 689;
		texte["Bad character code"] = 690;
		texte["A character number must be between 0 and 255."] = 691;
		texte["Bad number"] = 692;
		texte["Since I expected to read a number between 0 and 15,"] = 693;
		texte["Bad mathchar"] = 694;
		texte["A mathchar number must be between 0 and 32767."] = 695;
		texte["Bad delimiter code"] = 696;
		texte["A numeric delimiter code must be between 0 and 2^{27}-1."] = 697;
		texte["Improper alphabetic constant"] = 698;
		texte["A one-character control sequence belongs after a ` mark."] = 699;
		texte["So I'm essentially inserting \\0 here."] = 700;
		texte["Number too big"] = 701;
		texte["I can only go up to 2147483647='17777777777=\"7FFFFFFF,"] = 702;
		texte["so I'm using that number instead of yours."] = 703;
		texte["true"] = 704;
		texte["Illegal unit of measure ("] = 705;
		texte["replaced by filll)"] = 706;
		texte["I dddon't go any higher than filll."] = 707;
		texte["em"] = 708;
		texte["ex"] = 709;
		texte["mu inserted)"] = 710;
		texte["The unit of measurement in math glue must be mu."] = 711;
		texte["To recover gracefully from this error, it's best to"] = 712;
		texte["delete the erroneous units; e.g., type `2' to delete"] = 713;
		texte["two letters. (See Chapter 27 of The TeXbook.)"] = 714;
		texte["in"] = 715;
		texte["pc"] = 716;
		texte["cm"] = 717;
		texte["mm"] = 718;
		texte["bp"] = 719;
		texte["dd"] = 720;
		texte["cc"] = 721;
		texte["sp"] = 722;
		texte["pt inserted)"] = 723;
		texte["Dimensions can be in units of em, ex, in, pt, pc,"] = 724;
		texte["cm, mm, dd, cc, bp, or sp; but yours is a new one!"] = 725;
		texte["I'll assume that you meant to say pt, for printer's points."] = 726;
		texte["Dimension too large"] = 727;
		texte["I can't work with sizes bigger than about 19 feet."] = 728;
		texte["Continue and I'll use the largest value I can."] = 729;
		texte["plus"] = 730;
		texte["minus"] = 731;
		texte["width"] = 732;
		texte["height"] = 733;
		texte["depth"] = 734;
		texte["number"] = 735;
		texte["romannumeral"] = 736;
		texte["string"] = 737;
		texte["meaning"] = 738;
		texte["fontname"] = 739;
		texte["jobname"] = 740;
		texte[" at "] = 741;
		texte["Where was the left brace? You said something like `\\def\\a}',"] = 742;
		texte["which I'm going to interpret as `\\def\\a{}'."] = 743;
		texte["You already have nine parameters"] = 744;
		texte["I'm going to ignore the # sign you just used."] = 745;
		texte["Parameters must be numbered consecutively"] = 746;
		texte["I've inserted the digit you should have used after the #."] = 747;
		texte["Type `1' to delete what you did use."] = 748;
		texte["Illegal parameter number in definition of "] = 749;
		texte["You meant to type ## instead of #, right?"] = 750;
		texte["Or maybe a } was forgotten somewhere earlier, and things"] = 751;
		texte["are all screwed up? I'm going to assume that you meant ##."] = 752;
		texte["*** (cannot \\read from terminal in nonstop modes)"] = 753;
		texte["File ended within "] = 754;
		texte["This \\read has unbalanced braces."] = 755;
		texte["if"] = 756;
		texte["ifcat"] = 757;
		texte["ifnum"] = 758;
		texte["ifdim"] = 759;
		texte["ifodd"] = 760;
		texte["ifvmode"] = 761;
		texte["ifhmode"] = 762;
		texte["ifmmode"] = 763;
		texte["ifinner"] = 764;
		texte["ifvoid"] = 765;
		texte["ifhbox"] = 766;
		texte["ifvbox"] = 767;
		texte["ifx"] = 768;
		texte["ifeof"] = 769;
		texte["iftrue"] = 770;
		texte["iffalse"] = 771;
		texte["ifcase"] = 772;
		texte["fi"] = 773;
		texte["or"] = 774;
		texte["else"] = 775;
		texte["Extra "] = 776;
		texte["I'm ignoring this; it doesn't match any \\if."] = 777;
		texte["{true}"] = 778;
		texte["{false}"] = 779;
		texte["Missing = inserted for "] = 780;
		texte["I was expecting to see `<', `=', or `>'. Didn't."] = 781;
		texte["{case "] = 782;
		texte["TeXinputs:"] = 783;
		texte["TeXfonts:"] = 784;
		texte[".fmt"] = 785;
		texte["input file name"] = 786;
		texte["I can't find file `"] = 787;
		texte["I can't write on file `"] = 788;
		texte["'."] = 789;
		texte[".tex"] = 790;
		texte["Please type another "] = 791;
		texte["*** (job aborted, file error in nonstop mode)"] = 792;
		texte[".dvi"] = 793;
		texte["file name for output"] = 794;
		texte["texput"] = 795;
		texte[".log"] = 796;
		texte["**"] = 797;
		texte["transcript file name"] = 798;
		texte["  "] = 799;
		texte["nullfont"] = 800;
		texte["Font "] = 801;
		texte[" scaled "] = 802;
		texte[" not loadable: Bad metric (TFM) file"] = 803;
		texte[" not loadable: Metric (TFM) file not found"] = 804;
		texte["I wasn't able to read the size data for this font,"] = 805;
		texte["so I will ignore the font specification."] = 806;
		texte["[Wizards can fix TFM files using TFtoPL/PLtoTF.]"] = 807;
		texte["You might try inserting a different font spec;"] = 808;
		texte["e.g., type `I\\font<same font id>=<substitute font name>'."] = 809;
		texte[".tfm"] = 810;
		texte[" not loaded: Not enough room left"] = 811;
		texte["I'm afraid I won't be able to make use of this font,"] = 812;
		texte["because my memory for character-size data is too small."] = 813;
		texte["If you're really stuck, ask a wizard to enlarge me."] = 814;
		texte["Or maybe try `I\\font<same font id>=<name of loaded font>'."] = 815;
		texte["Missing font identifier"] = 816;
		texte["I was looking for a control sequence whose"] = 817;
		texte["current meaning has been defined by \\font."] = 818;
		texte[" has only "] = 819;
		texte[" fontdimen parameters"] = 820;
		texte["To increase the number of font parameters, you must"] = 821;
		texte["use \\fontdimen immediately after the \\font is loaded."] = 822;
		texte["font memory"] = 823;
		texte["Missing character: There is no "] = 824;
		texte[" in font "] = 825;
		texte[" TeX output "] = 826;
		texte["vlistout"] = 827;
		texte["Completed box being shipped out"] = 828;
		texte["Memory usage before: "] = 829;
		texte[" after: "] = 830;
		texte["; still untouched: "] = 831;
		texte["Huge page cannot be shipped out"] = 832;
		texte["The page just created is more than 18 feet tall or"] = 833;
		texte["more than 18 feet wide, so I suspect something went wrong."] = 834;
		texte["The following box has been deleted:"] = 835;
		texte["No pages of output."] = 836;
		texte["Output written on "] = 837;
		texte[" page"] = 838;
		texte[", "] = 839;
		texte[" bytes)."] = 840;
		texte["to"] = 841;
		texte["spread"] = 842;
		texte["Underfull"] = 843;
		texte["Loose"] = 844;
		texte[" \\hbox (badness "] = 845;
		texte[") has occurred while \\output is active"] = 846;
		texte[") in paragraph at lines "] = 847;
		texte[") in alignment at lines "] = 848;
		texte["--"] = 849;
		texte[") detected at line "] = 850;
		texte["Overfull \\hbox ("] = 851;
		texte["pt too wide"] = 852;
		texte["Tight \\hbox (badness "] = 853;
		texte["vpack"] = 854;
		texte[" \\vbox (badness "] = 855;
		texte["Overfull \\vbox ("] = 856;
		texte["pt too high"] = 857;
		texte["Tight \\vbox (badness "] = 858;
		texte["{}"] = 859;
		texte["displaystyle"] = 860;
		texte["textstyle"] = 861;
		texte["scriptstyle"] = 862;
		texte["scriptscriptstyle"] = 863;
		texte["Unknown style!"] = 864;
		texte["mathord"] = 865;
		texte["mathop"] = 866;
		texte["mathbin"] = 867;
		texte["mathrel"] = 868;
		texte["mathopen"] = 869;
		texte["mathclose"] = 870;
		texte["mathpunct"] = 871;
		texte["mathinner"] = 872;
		texte["overline"] = 873;
		texte["underline"] = 874;
		texte["left"] = 875;
		texte["right"] = 876;
		texte["limits"] = 877;
		texte["nolimits"] = 878;
		texte["fraction, thickness "] = 879;
		texte["= default"] = 880;
		texte[", left-delimiter "] = 881;
		texte[", right-delimiter "] = 882;
		texte[" is undefined (character "] = 883;
		texte["Somewhere in the math formula just ended, you used the"] = 884;
		texte["stated character from an undefined font family. For example,"] = 885;
		texte["plain TeX doesn't allow \\it or \\sl in subscripts. Proceed,"] = 886;
		texte["and I'll try to forget that I needed that character."] = 887;
		texte["mlist1"] = 888;
		texte["mlist2"] = 889;
		texte["mlist3"] = 890;
		texte["0234000122*4000133**3**344*0400400*000000234000111*1111112341011"] = 891;
		texte["mlist4"] = 892;
		texte[" inside $$'s"] = 893;
		texte["Displays can use special alignments (like \\eqalignno)"] = 894;
		texte["only if nothing but the alignment itself is between $$'s."] = 895;
		texte["So I've deleted the formulas that preceded this alignment."] = 896;
		texte["span"] = 897;
		texte["cr"] = 898;
		texte["crcr"] = 899;
		texte["endtemplate"] = 900;
		texte["alignment tab character "] = 901;
		texte["Missing # inserted in alignment preamble"] = 902;
		texte["There should be exactly one # between &'s, when an"] = 903;
		texte["\\halign or \\valign is being set up. In this case you had"] = 904;
		texte["none, so I've put one in; maybe that will work."] = 905;
		texte["Only one # is allowed per tab"] = 906;
		texte["more than one, so I'm ignoring all but the first."] = 907;
		texte["endv"] = 908;
		texte["Extra alignment tab has been changed to "] = 909;
		texte["You have given more \\span or & marks than there were"] = 910;
		texte["in the preamble to the \\halign or \\valign now in progress."] = 911;
		texte["So I'll assume that you meant to type \\cr instead."] = 912;
		texte["256 spans"] = 913;
		texte["align1"] = 914;
		texte["align0"] = 915;
		texte["Infinite glue shrinkage found in a paragraph"] = 916;
		texte["The paragraph just ended includes some glue that has"] = 917;
		texte["infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'."] = 918;
		texte["Such glue doesn't belong there---it allows a paragraph"] = 919;
		texte["of any length to fit on one line. But it's safe to proceed,"] = 920;
		texte["since the offensive shrinkability has been made finite."] = 921;
		texte["disc1"] = 922;
		texte["disc2"] = 923;
		texte["@@"] = 924;
		texte[": line "] = 925;
		texte[" t="] = 926;
		texte[" -> @@"] = 927;
		texte[" via @@"] = 928;
		texte[" b="] = 929;
		texte[" p="] = 930;
		texte[" d="] = 931;
		texte["@firstpass"] = 932;
		texte["@secondpass"] = 933;
		texte["@emergencypass"] = 934;
		texte["paragraph"] = 935;
		texte["disc3"] = 936;
		texte["disc4"] = 937;
		texte["line breaking"] = 938;
		texte["HYPH("] = 939;
		texte["hyphenation"] = 940;
		texte[" will be flushed"] = 941;
		texte["Hyphenation exceptions must contain only letters"] = 942;
		texte["and hyphens. But continue; I'll forgive and forget."] = 943;
		texte["Not a letter"] = 944;
		texte["Letters in \\hyphenation words must have \\lccode>0."] = 945;
		texte["Proceed; I'll ignore the character I just read."] = 946;
		texte["exception dictionary"] = 947;
		texte["pattern memory ops"] = 948;
		texte["pattern memory ops per language"] = 949;
		texte["pattern memory"] = 950;
		texte["Too late for "] = 951;
		texte["patterns"] = 952;
		texte["All patterns must be given before typesetting begins."] = 953;
		texte["Bad "] = 954;
		texte["(See Appendix H.)"] = 955;
		texte["Nonletter"] = 956;
		texte["Duplicate pattern"] = 957;
		texte["pruning"] = 958;
		texte["vertbreak"] = 959;
		texte["Infinite glue shrinkage found in box being split"] = 960;
		texte["The box you are \\vsplitting contains some infinitely"] = 961;
		texte["shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'."] = 962;
		texte["Such glue doesn't belong there; but you can safely proceed,"] = 963;
		texte["vsplit"] = 964;
		texte[" needs a "] = 965;
		texte["vbox"] = 966;
		texte["The box you are trying to split is an \\hbox."] = 967;
		texte["I can't split such a box, so I'll leave it alone."] = 968;
		texte["pagegoal"] = 969;
		texte["pagetotal"] = 970;
		texte["pagestretch"] = 971;
		texte["pagefilstretch"] = 972;
		texte["pagefillstretch"] = 973;
		texte["pagefilllstretch"] = 974;
		texte["pageshrink"] = 975;
		texte["pagedepth"] = 976;
		texte["fill"] = 977;
		texte["filll"] = 978;
		texte["### current page:"] = 979;
		texte[" (held over for next output)"] = 980;
		texte["total height "] = 981;
		texte[" goal height "] = 982;
		texte[" adds "] = 983;
		texte[", #"] = 984;
		texte[" might split"] = 985;
		texte["%% goal height="] = 986;
		texte[", max depth="] = 987;
		texte["Insertions can only be added to a vbox"] = 988;
		texte["Tut tut: You're trying to \\insert into a"] = 989;
		texte["\\box register that now contains an \\hbox."] = 990;
		texte["Proceed, and I'll discard its present contents."] = 991;
		texte["page"] = 992;
		texte["Infinite glue shrinkage found on current page"] = 993;
		texte["The page about to be output contains some infinitely"] = 994;
		texte[" g="] = 995;
		texte[" c="] = 996;
		texte["Infinite glue shrinkage inserted from "] = 997;
		texte["The correction glue for page breaking with insertions"] = 998;
		texte["must have finite shrinkability. But you may proceed,"] = 999;
		texte["% split"] = 1000;
		texte[" to "] = 1001;
		texte["255 is not void"] = 1002;
		texte["You shouldn't use \\box255 except in \\output routines."] = 1003;
		texte["Output loop---"] = 1004;
		texte[" consecutive dead cycles"] = 1005;
		texte["I've concluded that your \\output is awry; it never does a"] = 1006;
		texte["\\shipout, so I'm shipping \\box255 out myself. Next time"] = 1007;
		texte["increase \\maxdeadcycles if you want me to be more patient!"] = 1008;
		texte["Unbalanced output routine"] = 1009;
		texte["Your sneaky output routine has problematic {'s and/or }'s."] = 1010;
		texte["I can't handle that very well; good luck."] = 1011;
		texte["Output routine didn't use all of "] = 1012;
		texte["Your \\output commands should empty \\box255,"] = 1013;
		texte["e.g., by saying `\\shipout\\box255'."] = 1014;
		texte["Proceed; I'll discard its present contents."] = 1015;
		texte["Missing $ inserted"] = 1016;
		texte["I've inserted a begin-math/end-math symbol since I think"] = 1017;
		texte["you left one out. Proceed, with fingers crossed."] = 1018;
		texte["' in "] = 1019;
		texte["Sorry, but I'm not programmed to handle this case;"] = 1020;
		texte["I'll just pretend that you didn't ask for it."] = 1021;
		texte["If you're in the wrong mode, you might be able to"] = 1022;
		texte["return to the right one by typing `I}' or `I$' or `I\\par'."] = 1023;
		texte["end"] = 1024;
		texte["dump"] = 1025;
		texte["hskip"] = 1026;
		texte["hfil"] = 1027;
		texte["hfill"] = 1028;
		texte["hss"] = 1029;
		texte["hfilneg"] = 1030;
		texte["vskip"] = 1031;
		texte["vfil"] = 1032;
		texte["vfill"] = 1033;
		texte["vss"] = 1034;
		texte["vfilneg"] = 1035;
		texte["I've inserted something that you may have forgotten."] = 1036;
		texte["(See the <inserted text> above.)"] = 1037;
		texte["With luck, this will get me unwedged. But if you"] = 1038;
		texte["really didn't forget anything, try typing `2' now; then"] = 1039;
		texte["my insertion and my current dilemma will both disappear."] = 1040;
		texte["right."] = 1041;
		texte["Things are pretty mixed up, but I think the worst is over."] = 1042;
		texte["Too many }'s"] = 1043;
		texte["You've closed more groups than you opened."] = 1044;
		texte["Such booboos are generally harmless, so keep going."] = 1045;
		texte["rightbrace"] = 1046;
		texte["Extra }, or forgotten "] = 1047;
		texte["I've deleted a group-closing symbol because it seems to be"] = 1048;
		texte["spurious, as in `$x}$'. But perhaps the } is legitimate and"] = 1049;
		texte["you forgot something else, as in `\\hbox{$x}'. In such cases"] = 1050;
		texte["the way to recover is to insert both the forgotten and the"] = 1051;
		texte["deleted material, e.g., by typing `I$}'."] = 1052;
		texte["moveleft"] = 1053;
		texte["moveright"] = 1054;
		texte["raise"] = 1055;
		texte["lower"] = 1056;
		texte["copy"] = 1057;
		texte["lastbox"] = 1058;
		texte["vtop"] = 1059;
		texte["hbox"] = 1060;
		texte["shipout"] = 1061;
		texte["leaders"] = 1062;
		texte["cleaders"] = 1063;
		texte["xleaders"] = 1064;
		texte["Leaders not followed by proper glue"] = 1065;
		texte["You should say `\\leaders <box or rule><hskip or vskip>'."] = 1066;
		texte["I found the <box or rule>, but there's no suitable"] = 1067;
		texte["<hskip or vskip>, so I'm ignoring these leaders."] = 1068;
		texte["Sorry; this \\lastbox will be void."] = 1069;
		texte["Sorry...I usually can't take things from the current page."] = 1070;
		texte["This \\lastbox will therefore be void."] = 1071;
		texte["Missing `to' inserted"] = 1072;
		texte["I'm working on `\\vsplit<box number> to <dimen>';"] = 1073;
		texte["will look for the <dimen> next."] = 1074;
		texte["A <box> was supposed to be here"] = 1075;
		texte["I was expecting to see \\hbox or \\vbox or \\copy or \\box or"] = 1076;
		texte["something like that. So you might find something missing in"] = 1077;
		texte["your output. But keep trying; you can fix this later."] = 1078;
		texte["indent"] = 1079;
		texte["noindent"] = 1080;
		texte["' here except with leaders"] = 1081;
		texte["To put a horizontal rule in an hbox or an alignment,"] = 1082;
		texte["you should use \\leaders or \\hrulefill (see The TeXbook)."] = 1083;
		texte["You can't "] = 1084;
		texte["I'm changing to \\insert0; box 255 is special."] = 1085;
		texte["Try `I\\vskip-\\lastskip' instead."] = 1086;
		texte["Try `I\\kern-\\lastkern' instead."] = 1087;
		texte["Perhaps you can make the output routine do it."] = 1088;
		texte["unpenalty"] = 1089;
		texte["unkern"] = 1090;
		texte["unskip"] = 1091;
		texte["unhbox"] = 1092;
		texte["unhcopy"] = 1093;
		texte["unvbox"] = 1094;
		texte["unvcopy"] = 1095;
		texte["Incompatible list can't be unboxed"] = 1096;
		texte["Sorry, Pandora. (You sneaky devil.)"] = 1097;
		texte["I refuse to unbox an \\hbox in vertical mode or vice versa."] = 1098;
		texte["And I can't open any boxes in math mode."] = 1099;
		texte["Illegal math "] = 1100;
		texte["Sorry: The third part of a discretionary break must be"] = 1101;
		texte["empty, in math formulas. I had to delete your third part."] = 1102;
		texte["Discretionary list is too long"] = 1103;
		texte["Wow---I never thought anybody would tweak me here."] = 1104;
		texte["You can't seriously need such a huge discretionary list?"] = 1105;
		texte["Improper discretionary list"] = 1106;
		texte["Discretionary lists must contain only boxes and kerns."] = 1107;
		texte["The following discretionary sublist has been deleted:"] = 1108;
		texte["Missing } inserted"] = 1109;
		texte["I've put in what seems to be necessary to fix"] = 1110;
		texte["the current column of the current alignment."] = 1111;
		texte["Try to go on, since this might almost work."] = 1112;
		texte["Misplaced "] = 1113;
		texte["I can't figure out why you would want to use a tab mark"] = 1114;
		texte["here. If you just want an ampersand, the remedy is"] = 1115;
		texte["simple: Just type `I\\&' now. But if some right brace"] = 1116;
		texte["up above has ended a previous alignment prematurely,"] = 1117;
		texte["you're probably due for more error messages, and you"] = 1118;
		texte["might try typing `S' now just to see what is salvageable."] = 1119;
		texte["or \\cr or \\span just now. If something like a right brace"] = 1120;
		texte["I expect to see \\noalign only after the \\cr of"] = 1121;
		texte["an alignment. Proceed, and I'll ignore this case."] = 1122;
		texte["I expect to see \\omit only after tab marks or the \\cr of"] = 1123;
		texte["I'm guessing that you meant to end an alignment here."] = 1124;
		texte["I'm ignoring this, since I wasn't doing a \\csname."] = 1125;
		texte["eqno"] = 1126;
		texte["leqno"] = 1127;
		texte["displaylimits"] = 1128;
		texte["Limit controls must follow a math operator"] = 1129;
		texte["I'm ignoring this misplaced \\limits or \\nolimits command."] = 1130;
		texte["Missing delimiter (. inserted)"] = 1131;
		texte["I was expecting to see something like `(' or `\\{' or"] = 1132;
		texte["`\\}' here. If you typed, e.g., `{' instead of `\\{', you"] = 1133;
		texte["should probably delete the `{' by typing `1' now, so that"] = 1134;
		texte["braces don't get unbalanced. Otherwise just proceed."] = 1135;
		texte["Acceptable delimiters are characters whose \\delcode is"] = 1136;
		texte["nonnegative, or you can use `\\delimiter <delimiter code>'."] = 1137;
		texte["Please use "] = 1138;
		texte[" for accents in math mode"] = 1139;
		texte["I'm changing \\accent to \\mathaccent here; wish me luck."] = 1140;
		texte["(Accents are not the same in formulas as they are in text.)"] = 1141;
		texte["Double superscript"] = 1142;
		texte["I treat `x^1^2' essentially like `x^1{}^2'."] = 1143;
		texte["Double subscript"] = 1144;
		texte["I treat `x_1_2' essentially like `x_1{}_2'."] = 1145;
		texte["above"] = 1146;
		texte["over"] = 1147;
		texte["atop"] = 1148;
		texte["abovewithdelims"] = 1149;
		texte["overwithdelims"] = 1150;
		texte["atopwithdelims"] = 1151;
		texte["Ambiguous; you need another { and }"] = 1152;
		texte["I'm ignoring this fraction specification, since I don't"] = 1153;
		texte["know whether a construction like `x \\over y \\over z'"] = 1154;
		texte["means `{x \\over y} \\over z' or `x \\over {y \\over z}'."] = 1155;
		texte["I'm ignoring a \\right that had no matching \\left."] = 1156;
		texte["Math formula deleted: Insufficient symbol fonts"] = 1157;
		texte["Sorry, but I can't typeset math unless \\textfont 2"] = 1158;
		texte["and \\scriptfont 2 and \\scriptscriptfont 2 have all"] = 1159;
		texte["the \\fontdimen values needed in math symbol fonts."] = 1160;
		texte["Math formula deleted: Insufficient extension fonts"] = 1161;
		texte["Sorry, but I can't typeset math unless \\textfont 3"] = 1162;
		texte["and \\scriptfont 3 and \\scriptscriptfont 3 have all"] = 1163;
		texte["the \\fontdimen values needed in math extension fonts."] = 1164;
		texte["Display math should end with $$"] = 1165;
		texte["The `$' that I just saw supposedly matches a previous `$$'."] = 1166;
		texte["So I shall assume that you typed `$$' both times."] = 1167;
		texte["display"] = 1168;
		texte["Missing $$ inserted"] = 1169;
		texte["long"] = 1170;
		texte["outer"] = 1171;
		texte["global"] = 1172;
		texte["def"] = 1173;
		texte["gdef"] = 1174;
		texte["edef"] = 1175;
		texte["xdef"] = 1176;
		texte["prefix"] = 1177;
		texte["You can't use a prefix with `"] = 1178;
		texte["I'll pretend you didn't say \\long or \\outer or \\global."] = 1179;
		texte["' or `"] = 1180;
		texte["' with `"] = 1181;
		texte["I'll pretend you didn't say \\long or \\outer here."] = 1182;
		texte["Missing control sequence inserted"] = 1183;
		texte["Please don't say `\\def cs{...}', say `\\def\\cs{...}'."] = 1184;
		texte["I've inserted an inaccessible control sequence so that your"] = 1185;
		texte["definition will be completed without mixing me up too badly."] = 1186;
		texte["You can recover graciously from this error, if you're"] = 1187;
		texte["careful; see exercise 27.2 in The TeXbook."] = 1188;
		texte["inaccessible"] = 1189;
		texte["let"] = 1190;
		texte["futurelet"] = 1191;
		texte["chardef"] = 1192;
		texte["mathchardef"] = 1193;
		texte["countdef"] = 1194;
		texte["dimendef"] = 1195;
		texte["skipdef"] = 1196;
		texte["muskipdef"] = 1197;
		texte["toksdef"] = 1198;
		texte["You should have said `\\read<number> to \\cs'."] = 1199;
		texte["I'm going to look for the \\cs now."] = 1200;
		texte["Invalid code ("] = 1201;
		texte["), should be in the range 0.."] = 1202;
		texte["), should be at most "] = 1203;
		texte["I'm going to use 0 instead of that illegal code value."] = 1204;
		texte["by"] = 1205;
		texte["Arithmetic overflow"] = 1206;
		texte["I can't carry out that multiplication or division,"] = 1207;
		texte["since the result is out of range."] = 1208;
		texte["I'm forgetting what you said and not changing anything."] = 1209;
		texte["Sorry, \\setbox is not allowed after \\halign in a display,"] = 1210;
		texte["or between \\accent and an accented character."] = 1211;
		texte["Bad space factor"] = 1212;
		texte["I allow only values in the range 1..32767 here."] = 1213;
		texte["I allow only nonnegative values here."] = 1214;
		texte["Patterns can be loaded only by INITEX"] = 1215;
		texte["hyphenchar"] = 1216;
		texte["skewchar"] = 1217;
		texte["FONT"] = 1218;
		texte["at"] = 1219;
		texte["scaled"] = 1220;
		texte["Improper `at' size ("] = 1221;
		texte["pt), replaced by 10pt"] = 1222;
		texte["I can only handle fonts at positive sizes that are"] = 1223;
		texte["less than 2048pt, so I've changed what you said to 10pt."] = 1224;
		texte["select font "] = 1225;
		texte["errorstopmode"] = 1226;
		texte["openin"] = 1227;
		texte["closein"] = 1228;
		texte["message"] = 1229;
		texte["errmessage"] = 1230;
		texte["(That was another \\errmessage.)"] = 1231;
		texte["This error message was generated by an \\errmessage"] = 1232;
		texte["command, so I can't give any explicit help."] = 1233;
		texte["Pretend that you're Hercule Poirot: Examine all clues,"] = 1234;
		texte["and deduce the truth by order and method."] = 1235;
		texte["lowercase"] = 1236;
		texte["uppercase"] = 1237;
		texte["show"] = 1238;
		texte["showbox"] = 1239;
		texte["showthe"] = 1240;
		texte["showlists"] = 1241;
		texte["This isn't an error message; I'm just \\showing something."] = 1242;
		texte["Type `I\\show...' to show more (e.g., \\show\\cs,"] = 1243;
		texte["\\showthe\\count10, \\showbox255, \\showlists)."] = 1244;
		texte["And type `I\\tracingonline=1\\show...' to show boxes and"] = 1245;
		texte["lists on your terminal as well as in the transcript file."] = 1246;
		texte["> "] = 1247;
		texte["undefined"] = 1248;
		texte["macro"] = 1249;
		texte["long macro"] = 1250;
		texte["outer macro"] = 1251;
		texte["outer endtemplate"] = 1252;
		texte["> \\box"] = 1253;
		texte["OK"] = 1254;
		texte[" (see the transcript file)"] = 1255;
		texte[" (INITEX)"] = 1256;
		texte["You can't dump inside a group"] = 1257;
		texte["`{...\\dump}' is a no-no."] = 1258;
		texte[" strings of total length "] = 1259;
		texte[" memory locations dumped; current usage is "] = 1260;
		texte[" multiletter control sequences"] = 1261;
		texte[" words of font info for "] = 1262;
		texte[" preloaded font"] = 1263;
		texte["\\font"] = 1264;
		texte[" hyphenation exception"] = 1265;
		texte["Hyphenation trie of length "] = 1266;
		texte[" has "] = 1267;
		texte[" op"] = 1268;
		texte[" out of "] = 1269;
		texte[" for language "] = 1270;
		texte[" (preloaded format="] = 1271;
		texte["format file name"] = 1272;
		texte["Beginning to dump on file "] = 1273;
		texte["Transcript written on "] = 1274;
		texte[" )"] = 1275;
		texte["end occurred "] = 1276;
		texte["inside a group at level "] = 1277;
		texte["when "] = 1278;
		texte[" on line "] = 1279;
		texte[" was incomplete)"] = 1280;
		texte["(see the transcript file for additional information)"] = 1281;
		texte["(\\dump is performed only by INITEX)"] = 1282;
		texte["debug # (-1 to exit):"] = 1283;
		texte["openout"] = 1284;
		texte["closeout"] = 1285;
		texte["special"] = 1286;
		texte["immediate"] = 1287;
		texte["setlanguage"] = 1288;
		texte["[unknown extension!]"] = 1289;
		texte["ext1"] = 1290;
		texte[" (hyphenmin "] = 1291;
		texte["whatsit?"] = 1292;
		texte["ext2"] = 1293;
		texte["ext3"] = 1294;
		texte["endwrite"] = 1295;
		texte["Unbalanced write command"] = 1296;
		texte["On this page there's a \\write with fewer real {'s than }'s."] = 1297;
		texte["ext4"] = 1298;
		texte["output file name"] = 1299;
	}
	return texte[s];
}

static wordfile fmtfile;
static halfword himemmin = hi_mem_stat_min;
static halfword lomemmax = lo_mem_stat_max+1+1000;
static halfword memend = mem_top;
static halfword rover = lo_mem_stat_max+1;
inline memoryword mem[memmax+1];
/*	for (int k = 1; k < 20; k++) // glues
		mem[k].int_ = 0;
	for (int k = hi_mem_stat_min; k <= mem_top; k++) // au-dessus de rover
		mem[k].int_ = 0;*/

static halfword& link(halfword p) { return mem[p].hh.rh; }
static halfword& info(halfword p) { return mem[p].hh.lh; }
static halfword& node_size(halfword p) { return mem[p].hh.lh; }
static halfword& rlink(halfword p) { return link(p+1); }
static halfword& llink(halfword p) { return info(p+1); }

static void openfmtfile(void)
{
	auto j = loc;
	if (buffer[loc] == '&')
	{
		loc++;
		buffer[last] = ' ';
		for (j = loc; buffer[j] != ' '; j++); //trim à droite
		auto fname = std::string(buffer+loc, buffer+j);
		if (wopenin(fmtfile, packbufferedname(none, fname)))
		{
			loc = j;
			return;
		}
		if (wopenin(fmtfile, packbufferedname(area, fname)))
		{
			loc = j;
			return;
		}
		std::cout << "Sorry, I can't find that format;\n will try PLAIN.\n" << std::flush;
	}
	if (wopenin(fmtfile, packbufferedname(area_name, "")))
	{
		loc = j;
		return;
	}
	std::cout << "I can't find the PLAIN format file!\n";
	throw std::string();
}

void undump_hh(twohalves &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_wd(memoryword &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_wd(MemoryNode &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_qqqq(fourquarters &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }
void undump_int(int &num) { fmtfile.read(reinterpret_cast<char *>(&num), 4); }

void badFormatIf(bool b)
{
	if (b)
		throw 1;
}

void tooSmallIf(bool b, const std::string &s)
{
	if (b)
	{
		std::cout << "---! Must increase the \n" << s << "\n";
		throw 1;
	}
}

int undump(int min, int max)
{
	int x;
	undump_int(x);
	badFormatIf(x < min || x > max);
	return x;
}

int undump_size(int min, int max, const std::string &s)
{
	int x;
	undump_int(x);
	badFormatIf(x < min);
	tooSmallIf(x > max, s);
	return x;
}

static std::string pool;

void undump_four_ASCII(void)
{
	fourquarters w;
	undump_qqqq(w);
	pool.push_back(w.b0);
	pool.push_back(w.b1);
	pool.push_back(w.b2);
	pool.push_back(w.b3);
}

static int cscount = 0;
static int varused =lo_mem_stat_max+1-mem_bot, dynused = hi_mem_stat_usage;
static halfword avail = 0;
static std::vector<HyphenNode*> hyphlist(308, nullptr);
static std::vector<std::string> hyphword(308, "");
static hyphpointer hyphcount = 0;

// dummy
std::vector<int> trie, trieOp;

void loadfmtfile(void)
{
	link(rover) = empty_flag;
	node_size(rover) = 1000;
	llink(rover) = rover;
	rlink(rover) = rover;
	openfmtfile();
	try
	{
		int j, k;
		halfword p, q;
		int x;
		fourquarters w;
		undump_int(x);
		badFormatIf(x != CHECKSUM);
		undump_int(x);
		badFormatIf(x != mem_bot);
		undump_int(x);
		badFormatIf(x != mem_top);
		undump_int(x);	
		badFormatIf(x != eqtb_size);
		undump_int(x);	
		badFormatIf(x != hash_prime);
		undump_int(x);	
		badFormatIf(x != hyph_size);
		int poolptr = undump_size(0, poolsize, "string pool size");
		int strptr = undump_size(0,  maxstrings, "max strings");
		std::vector<int> strstart;
		for (k = 0; k <= strptr; k++)
			strstart.push_back(undump(0,  poolptr));
		for (k = 0; k < strptr; k++)
			strings.push_back(std::string(pool.begin()+strstart[k], pool.begin()+strstart[k+1]));
		for (k = 0; k+4 < poolptr; k = k+4)
			undump_four_ASCII();
		k = poolptr-4;
		undump_four_ASCII();
		lomemmax = undump(lo_mem_stat_max+1000, hi_mem_stat_min-1);
		rover = undump(lo_mem_stat_max+1, lomemmax);
		p = 0;
		q = rover;
		do
		{
			for (k = p; k <= q+1; k++)
				undump_wd(mem[k]);
			p = q+node_size(q);
			badFormatIf(p > lomemmax || (q >= rlink(q) && rlink(q) != rover));
			q = rlink(q);
		} while (q != rover);
		for (k = p; k <= lomemmax; k++)
			undump_wd(mem[k]);
		if (memmin < mem_bot-2)
		{
			p = llink(rover);
			q = memmin+1;
			link(memmin) = 0;
			info(memmin) = 0;
			rlink(p) = q;
			llink(rover) = q;
			rlink(q) = rover;
			llink(q) = p;
			link(q) = empty_flag;
			info(q) = mem_bot-q;
		}
		himemmin = undump(lomemmax+1, hi_mem_stat_min);
		avail = undump(0, mem_top);
		memend = mem_top;
		for (k = himemmin; k <= memend; k++)
			undump_wd(mem[k]);
		undump_int(varused);
		undump_int(dynused);
		k = active_base;
		do
		{
			auto x = undump(1, eqtb_size+1-k);
			for (j = k; j < k+x; j++)
				undump_wd(eqtb[j]);
			k += x;
			x = undump(0, eqtb_size+1-k);
			for (j = k; j < k+x; j++)
				eqtb[j] = eqtb[k-1];
			k += x;
		} while (k <= eqtb_size);
		parloc = undump(hash_base, frozen_control_sequence);
		partoken = cs_token_flag+parloc;
		writeloc = undump(hash_base, frozen_control_sequence);
		hashused = undump(hash_base, frozen_control_sequence);
		p = null_cs;
		do
		{
			p = undump(p+1, hashused);
			undump_hh(hash[p]);
		} while (p != hashused);
		for (p = hashused+1; p < undefined_control_sequence; p++)
			undump_hh(hash[p]);
		undump_int(cscount);
		Font::info.resize(undump_size(7, fontmemsize, "font mem size")+1);
		for (auto &fi: Font::info)
			undump_wd(fi);
		fonts.resize(undump_size(0, fontmax, "font max")+1);
		for (auto &ft: fonts)
		{
			undump_qqqq(ft.check);
			undump_int(ft.size);
			undump_int(ft.dsize);
			ft.params = undump(0, 1<<16-1);
			undump_int(ft.hyphenchar);
			undump_int(ft.skewchar);
			ft.name = strings[undump(0, strptr)];
			ft.area = strings[undump(0, strptr)];
			ft.bc = undump(0, 255);
			ft.ec = undump(0, 255);
			undump_int(ft.charbase);
			undump_int(ft.widthbase);
			undump_int(ft.heightbase);
			undump_int(ft.depthbase);
			undump_int(ft.italicbase);
			undump_int(ft.ligkernbase);
			undump_int(ft.kernbase);
			undump_int(ft.extenbase);
			undump_int(ft.parambase);
			/*ft.glue->num = undump(0, lomemmax);*/
			ft.bcharlabel = undump(0, Font::info.size()-1);
			ft.bchar = undump(0, non_char);
			ft.falsebchar = undump(0, non_char);
		}
		hyphcount = undump(0, hyph_size);
		for (k = 1; k <= hyphcount; k++)
		{
			j = undump(0, hyph_size);
			hyphword[j] = undump(0, strptr);
			/*hyphlist[j]->num = undump(0, 1<<16-1);*/
		}
		j = undump_size(0, triesize, "trie size");
		trie.resize(j+1);
		for (auto t: trie)
			;//undump_hh(t.hh);
		j = undump_size(0, trieopsize, "trie op size");
		trieOp.resize(j+1);
		for (k = 1; k < trieOp.size(); k++)
		{
			/*trieOp[k].hyfdistance = undump(0, 63);
			trieOp[k].hyfnum = undump(0, 63);
			trieOp[k].hyfnext = undump(0, 1<<8-1);*/
		}
		for (k = 0; k <= 255; k++)
			trieused[k] = 0;
		k = 256;
		while (j > 0)
		{
			k = undump(0, k-1);
			trieused[k] = undump(1, j);
			j -= trieused[k];
			opstart[k] = j;
		}
		trienotready = false;
		interaction = undump(batch_mode, error_stop_mode);
		formatident = undump(0, strptr);
		undump_int(x);
		badFormatIf(x != 69069 || fmtfile.eof());
	}
	catch(...)
	{
		std::cout << "(Fatal format file error; I''m stymied\n";
		wclose(fmtfile);
		throw std::string();
	}
	wclose(fmtfile);
}
static halfword getnode(void)
{
	halfword p = rover;
	do
	{ 
		halfword q;
		for (q = p+node_size(p); link(q) == empty_flag; q += node_size(q))
		{
			auto t = rlink(q);
			if (q == rover)
				rover = t;
			llink(t) = llink(q);
			rlink(llink(q)) = t;
		}
		node_size(p) = q-p;
		p = rlink(p);
	} while (p != rover);
	return empty_flag;
}

//! sorts the available variable-size nodes by location
static void sortavail(void)
{
	auto p = getnode();
	p = rlink(rover);
	rlink(rover) = empty_flag;
	halfword oldrover = rover;
	while (p != oldrover)
		if (p < rover)
		{
			auto q = p;
			p = rlink(q);
			rlink(q) = rover;
			rover = q;
		}
		else
		{
			halfword q = rover;
			while (rlink(q) < p)
				q = rlink(q);
			auto r = rlink(p);
			rlink(p) = rlink(q);
			rlink(q) = p;
			p = r;
		}
	p = rover;
	while (rlink(p) != empty_flag)
	{
		llink(rlink(p)) = p;
		p = rlink(p);
	}
	rlink(p) = rover;
	llink(rover) = p;
}

constexpr char format_extension[] = ".fmt"; //!< the extension, as a WEB constant

static void dump_hh(twohalves num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(memoryword num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_wd(MemoryNode num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_qqqq(fourquarters num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }
static void dump_int(std::uint32_t num) { fmtfile.write(reinterpret_cast<const char *>(&num), 4); }

static void dump_four_ASCII(int k)
{
	fourquarters w;
	w.b0 = pool[k];
	w.b1 = pool[k+1];
	w.b2 = pool[k+2];
	w.b3 = pool[k+3];
	dump_qqqq(w);
}

void storefmtfile(void)
{
	int j, k, l;
	halfword p, q;
	if (savestack.size())
		fatal("You can't dump_int inside a group", "`{...\\dump_int}' is a no-no.");
	formatident = " (preloaded format="+jobname+" "+std::to_string(year())+"."+std::to_string(month())+"."+std::to_string(day())+")";
	selector = interaction == batch_mode ? log_only : term_and_log;
	std::string fname;
	while (!wopenout(fmtfile, fname = packjobname(format_extension)))
		promptfilename("format file name", format_extension); 
	printnl("Beginning to dump_int on file ");
	print(fname);
	printnl(formatident);
	dump_int(CHECKSUM);
	dump_int(mem_bot);
	dump_int(mem_top);
	dump_int(eqtb_size);
	dump_int(hash_prime);
	dump_int(hyph_size);
	int poolptr = 0;
	std::vector<int> strstart;
	for (auto s: strings)
	{
		strstart.push_back(poolptr);
		for (auto c: s)
		{
			pool += c;
			poolptr++;
		}
	}
	strstart.push_back(poolptr);
	dump_int(poolptr);
	dump_int(strings.size());
	for (k = 0; k <= strings.size(); k++)
		dump_int(strstart[k]);
	for (k = 0; k+4 < poolptr; k += 4)
		dump_four_ASCII(k);
	k = poolptr-4;
	dump_four_ASCII(k);
	print("\n"+std::to_string(strings.size())+" strings of total length "+std::to_string(poolptr));
	sortavail();
	varused = 0;
	dump_int(lomemmax);
	dump_int(rover);
	p = 0;
	q = rover;
	int x = 0;
	do
	{
		for (k = p; k <= q+1; k++)
			dump_wd(mem[k]);
		x += q+2-p;
		varused += q-p;
		p = q+node_size(q);
		q = rlink(q);
	} while (q != rover);
	varused += lomemmax-p;
	dynused = memend+1-himemmin;
	for (k = p; k <= lomemmax; k++)
		dump_wd(mem[k]);
	x += lomemmax+1-p;
	dump_int(himemmin);
	dump_int(avail);
	for (k = himemmin; k <= memend; k++)
		dump_wd(mem[k]);
	x += memend+1-himemmin;
	p = avail;
	while (p)
	{
		dynused--;
		p = link(p);
	}
	dump_int(varused);
	dump_int(dynused);
	print("\n"+std::to_string(x)+" memory locations dump_inted; current usage is "+std::to_string(varused)+"&"+std::to_string(dynused));
	k = active_base;
	do
	{
		bool found1 = false;
		for (j = k; j < int_base-1; j++)
			if (eqtb[j] == eqtb[j+1])
			{
				found1 = true;
				break;
			}
		if (found1)
		{
			j++;
			l = j;
			for (;j < int_base-1; j++)
				if (eqtb[j] != eqtb[j+1])
					break;
		}
		else
			l = int_base;
		dump_int(l-k);
		for (;k < l; k++)
			dump_wd(eqtb[k]);
		k = j+1;
		dump_int(k-l);
	} while (k != int_base);
	do
	{
		bool found2 = false;
		for (j = k; j < eqtb_size; j++)
			if (eqtb[j].int_ == eqtb[j+1].int_)
			{
				found2 = true;
				break;
			}
		if (found2)
		{
			j++;
			l = j;
			for (;j < eqtb_size; j++)
				if (eqtb[j].int_ != eqtb[j+1].int_)
					break;
		}
		else
			l = eqtb_size+1;
		dump_int(l-k);
		for (;k < l; k++)
			dump_wd(eqtb[k]);
		k = j+1;
		dump_int(k-l);
	} while (k <= eqtb_size);
	dump_int(parloc);
	dump_int(writeloc);
	dump_int(hashused);
	cscount = frozen_control_sequence-1-hashused;
	for (p = hash_base; p <= hashused; p++)
		if (hash[p].rh)
		{
			dump_int(p);
			dump_hh(hash[p]);
			cscount++;
		}
	for (p = hashused+1; p < undefined_control_sequence; p++)
		dump_hh(hash[p]);
	dump_int(cscount);
	println();
	print(std::to_string(cscount)+" multiletter control sequences");
	dump_int(Font::info.size()-1);
	for (auto &fi: Font::info)
		dump_wd(fi);
	dump_int(fonts.size()-1);
	for (auto &ft: fonts)
	{
		dump_qqqq(ft.check);
		dump_int(ft.size);
		dump_int(ft.dsize);
		dump_int(ft.params);
		dump_int(ft.hyphenchar);
		dump_int(ft.skewchar);
		dump_int(txt(ft.name));
		dump_int(txt(ft.area));
		dump_int(ft.bc);
		dump_int(ft.ec);
		dump_int(ft.charbase);
		dump_int(ft.widthbase);
		dump_int(ft.heightbase);
		dump_int(ft.depthbase);
		dump_int(ft.italicbase);
		dump_int(ft.ligkernbase);
		dump_int(ft.kernbase);
		dump_int(ft.extenbase);
		dump_int(ft.parambase);
		/*dump_int(ft.glue->num);*/
		dump_int(ft.bcharlabel);
		dump_int(ft.bchar);
		dump_int(ft.falsebchar);
		printnl("\\font");
		print(esc(eqtb_cs[k+font_id_base-hash_base].text)+esc("FONT")+"="+asFilename(ft.name, ft.area, ""));
		if (ft.size != ft.dsize)
			print(" at "+asScaled(ft.size)+"pt");
	}
	println();
	print(std::to_string(Font::info.size()-7)+" words of font info for "+std::to_string(fonts.size()+1)+" preloaded font"+(fonts.size()+1 == 1 ? "" : "s"));
	dump_int(hyphcount);
	for (k = 0; k <= hyph_size; k++)
		if (hyphword[k] != "")
		{
			dump_int(k);
			dump_int(txt(hyphword[k]));
			/*dump_int(hyphlist[k]->num);*/
		}
	println();
	print(std::to_string(hyphcount)+" hyphenation exception"+(hyphcount == 1 ? "" : "s"));
	if (trienotready)
		inittrie();
	dump_int(trie.size()-1);
	for (auto t: trie)
		;//dump_hh(t.hh);
	dump_int(trieOp.size()-1);
	for (k = 1; k < trieOp.size(); k++)
	{
		/*dump_int(trieOp[k].hyfdistance);
		dump_int(trieOp[k].hyfnum);
		dump_int(trieOp[k].hyfnext);*/
	}
	printnl("Hyphenation trie of length "+std::to_string(trie.size()-1)+" has "+std::to_string(trieOp.size()-1)+" op"+(trieOp.size()-1 == 1 ? "" : "s")+" out of "+std::to_string(trieopsize));
	for (k = 255; k > -1; k--)
		if (trieused[k] > 0)
		{
			printnl("    "+std::to_string(trieused[k])+" for language "+std::to_string(k));
			dump_int(k);
			dump_int(trieused[k]);
		}
	dump_int(interaction);
	dump_int(txt(formatident));
	dump_int(69069);
	tracing_stats() = 0;
	wclose(fmtfile);
}
