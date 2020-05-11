/*mtype==t@&y@&p@&e //this is a \.//WEB coding trick:
start_of_TEX=1 //go here when \TeX's variables are initialized
end_of_TEX=9998 //go here to close files and terminate gracefully
final_end=9999 //this label marks the ending of the program
debug==@// //change this to `$\\//debug\equiv\null$' when debugging
gubed==@t@>@ //change this to `$\\//gubed\equiv\null$' when debugging
stat==@// //change this to `$\\//stat\equiv\null$' when gathering
tats==@t@>@ //change this to `$\\//tats\equiv\null$' when gathering
init== //change this to `$\\//init\equiv\.//@@\//$' in the production version
tini== //change this to `$\\//tini\equiv\.//@@\$' in the production version
othercases == others: //default for cases not listed explicitly
endcases == @+end //follows the default case in an extended |case| statement
exit=10 //go here to leave a procedure
restart=20 //go here to start a procedure again
reswitch=21 //go here to start a case statement again
continue=22 //go here to resume a loop
done=30 //go here to exit a loop
done1=31 //like |done|, when there is more than one loop
done2=32 //for exiting the second loop in a long block
done3=33 //for exiting the third loop in a very long block
done4=34 //for exiting the fourth loop in an extremely long block
done5=35 //for exiting the fifth loop in an immense block
done6=36 //for exiting the sixth loop in a block
found=40 //go here when you've found it
found1=41 //like |found|, when there's more than one per routine
found2=42 //like |found|, when there's more than two per routine
not_found=45 //go here when you've found nothing
common_ending=50 //go here when you want to merge with another branch
incr(#) == #:=#+1 //increase a variable by unity
decr(#) == #:=#-1 //decrease a variable by unity
negate(#) == #:=-# //change the sign of a variable
loop == @+ while true do@+ //repeat over and over until a |goto| happens
do_nothing == //empty statement
return == goto exit //terminate a procedure call*/
/*empty=0 //symbolic name for a null constant
text_char == char //the data type of characters in text files
first_text_char=0 //ordinal number of the smallest element of |text_char|
last_text_char=255 //ordinal number of the largest element of |text_char|
null_code=@'0 //ASCII code that might disappear
carriage_return=@'15 //ASCII code used at end of line
invalid_code=@'177 //ASCII code that many systems prohibit in text files
reset_OK(#)==erstat(#)=0
rewrite_OK(#)==erstat(#)=0
t_open_in==reset(term_in,'TTY:','/O/I') //open the terminal for text input
t_open_out==rewrite(term_out,'TTY:','/O') //open the terminal for text output
update_terminal == break(term_out) //empty the terminal output buffer
clear_terminal == break_in(term_in,true) //clear the terminal input buffer
wake_up_terminal == do_nothing //cancel the user's cancellation of output*/
/*si(#) == # //convert from |ASCII_code| to |packed_ASCII_code|
so(#) == # //convert from |packed_ASCII_code| to |ASCII_code|*/
/*wterm(#)==write(term_out,#)
wterm_ln(#)==write_ln(term_out,#)
wterm_cr==write_ln(term_out)
wlog(#)==write(log_file,#)
wlog_ln(#)==write_ln(log_file,#)
wlog_cr==write_ln(log_file)
print_ASCII == print
prompt_input(#)==begin wake_up_terminal; print(#); term_input;*/
/*print_err(#)==begin if interaction=error_stop_mode then wake_up_terminal;*/
/*hlp1(#)==help_line[0]:=#;@+end
hlp2(#)==help_line[1]:=#; hlp1
hlp3(#)==help_line[2]:=#; hlp2
hlp4(#)==help_line[3]:=#; hlp3
hlp5(#)==help_line[4]:=#; hlp4
hlp6(#)==help_line[5]:=#; hlp5
help0==help_ptr:=0 //sometimes there might be no help
help1==@+begin help_ptr:=1; hlp1 //use this with one help line
help2==@+begin help_ptr:=2; hlp2 //use this with two help lines
help3==@+begin help_ptr:=3; hlp3 //use this with three help lines
help4==@+begin help_ptr:=4; hlp4 //use this with four help lines
help5==@+begin help_ptr:=5; hlp5 //use this with five help lines
help6==@+begin help_ptr:=6; hlp6 //use this with six help lines
succumb==begin if interaction=error_stop_mode then*/
/*set_glue_ratio_zero(#) == #:=0.0 //store the representation of zero ratio
set_glue_ratio_one(#) == #:=1.0 //store the representation of unit ratio
float(#) == # //convert from |glue_ratio| to type |real|
unfloat(#) == # //convert from |real| to type |glue_ratio|
float_constant(#) == #.0 //convert |integer| constant to |real|
min_quarterword=0 //smallest allowable value in a |quarterword|
max_quarterword=255 //largest allowable value in a |quarterword|
min_halfword==0 //smallest allowable value in a |halfword|
max_halfword==65535 //largest allowable value in a |halfword|
qi(#)==#+min_quarterword
qo(#)==#-min_quarterword
hi(#)==#+min_halfword
ho(#)==#-min_halfword
sc==int //|scaled| data is equivalent to |integer|
pointer==halfword //a flag or a location in |mem| or |eqtb|
null==min_halfword //the null pointer*/
//do_all_six(#)==#(1);#(2);#(3);#(4);#(5);#(6)
//kern_base_offset==256*(128+min_quarterword)*/

