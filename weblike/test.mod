MODULE: 'Labels in the out...'
(*PASCAL module 6*)
start_of_TEX(*\hskip-2pt*), end_of_TEX(*\hskip-2pt*), final_end; 
  {key control points} 

MODULE: 'Initialize whatever...'
(*PASCAL module 8*)

INSERT: 'Set initial values of key variables'

 
init 
INSERT: 'Initialize table entries (done by \.{INITEX} only)'
;tini 

MODULE: 'Compiler directives'
(*PASCAL module 9*)
@{$C-,A+,D-@} {no range check, catch arithmetic overflow, no debug overhead} 
debug @{$C+,D+@} gubed {but turn everything on when debugging} 

MODULE: 'Constants... '
(*PASCAL module 11*)
mem_max=30000; {greatest index in \TeX's internal |mem| array; 
  must be strictly less than |max_halfword|; 
  must be equal to |mem_top| in \.[INITEX], otherwise |>=mem_top|} 
mem_min=0; {smallest index in \TeX's internal |mem| array; 
  must be |min_halfword| or more; 
  must be equal to |mem_bot| in \.[INITEX], otherwise |<=mem_bot|} 
buf_size=500; {maximum number of characters simultaneously present in 
  current lines of open files and in control sequences between 
  \.[\\csname] and \.[\\endcsname]; must not exceed |max_halfword|} 
error_line=72; {width of context lines on terminal error messages} 
half_error_line=42; {width of first lines of contexts in terminal 
  error messages; should be between 30 and |error_line-15|} 
max_print_line=79; {width of longest text lines output; should be at least 60} 
stack_size=200; {maximum number of simultaneous input sources} 
max_in_open=6; {maximum number of input files and error insertions that 
  can be going on simultaneously} 
font_max=75; {maximum internal font number; must not exceed |max_quarterword| 
  and must be at most |font_base+256|} 
font_mem_size=20000; {number of words of |font_info| for all fonts} 
param_size=60; {maximum number of simultaneous macro parameters} 
nest_size=40; {maximum number of semantic levels simultaneously active} 
max_strings=3000; {maximum number of strings; must not exceed |max_halfword|} 
string_vacancies=8000; {the minimum number of characters that should be 
  available for the user's control sequences and font names, 
  after \TeX's own error messages are stored} 
pool_size=32000; {maximum number of characters in strings, including all 
  error messages and help texts, and the names of all fonts and 
  control sequences; must exceed |string_vacancies| by the total 
  length of \TeX's own strings, which is currently about 23000} 
save_size=600; {space for saving values outside of current group; must be 
  at most |max_halfword|} 
trie_size=8000; {space for hyphenation patterns; should be larger for 
  \.[INITEX] than it is in production versions of \TeX} 
trie_op_size=500; {space for ``opcodes'' in the hyphenation patterns} 
dvi_buf_size=800; {size of the output buffer; must be a multiple of 8} 
file_name_size=40; {file names shouldn't be longer than this} 
pool_name='TeXformats:TEX.POOL                     '; 
  {string of length |file_name_size|; tells where the string pool appears} 
(*TeXformats*) 

MODULE: 'Glob... '
(*PASCAL module 13*)
bad:integer; {is some ``constant'' wrong?} 

MODULE: 'Check the ``constant'''' values for consistency'
(*PASCAL module 14*)
bad:=0; 
if (half_error_line<30)or(half_error_line>error_line-15) then bad:=1; 
if max_print_line<60 then bad:=2; 
if dvi_buf_size mod 8<>0 then bad:=3; 
if mem_bot+1100>mem_top then bad:=4; 
if hash_prime>hash_size then bad:=5; 
if max_in_open>=128 then bad:=6; 
if mem_top<256+11 then bad:=7; {we will want |null_list>255|} 

MODULE: 'Types... '
(*PASCAL module 18*)
ASCII_code=0..255; {eight-bit numbers} 

MODULE: 'Local variables for init...'
(*PASCAL module 19*)
i:integer; 

MODULE: 'Glob... '
(*PASCAL module 20*)
xord: array [text_char] of ASCII_code; 
  {specifies conversion of input characters} 
xchr: array [ASCII_code] of text_char; 
  {specifies conversion of output characters} 

MODULE: 'Set init...'
(*PASCAL module 21*)
xchr[32]:=' '; 
xchr[33]:='!'; 
xchr[34]:=''''; 
xchr[35]:='#'; 
xchr[36]:='$'; 
xchr[37]:='%'; 
xchr[38]:='&'; 
xchr[39]:='''';
 
xchr[40]:='('; 
xchr[41]:=')'; 
xchr[42]:='*'; 
xchr[43]:='+'; 
xchr[44]:=','; 
xchr[45]:='-'; 
xchr[46]:='.'; 
xchr[47]:='/';
 
xchr[48]:='0'; 
xchr[49]:='1'; 
xchr[50]:='2'; 
xchr[51]:='3'; 
xchr[52]:='4'; 
xchr[53]:='5'; 
xchr[54]:='6'; 
xchr[55]:='7';
 
xchr[56]:='8'; 
xchr[57]:='9'; 
xchr[58]:=':'; 
xchr[59]:=';'; 
xchr[60]:='<'; 
xchr[61]:='='; 
xchr[62]:='>'; 
xchr[63]:='?';
 
xchr[64]:='@'; 
xchr[65]:='A'; 
xchr[66]:='B'; 
xchr[67]:='C'; 
xchr[68]:='D'; 
xchr[69]:='E'; 
xchr[70]:='F'; 
xchr[71]:='G';
 
xchr[72]:='H'; 
xchr[73]:='I'; 
xchr[74]:='J'; 
xchr[75]:='K'; 
xchr[76]:='L'; 
xchr[77]:='M'; 
xchr[78]:='N'; 
xchr[79]:='O';
 
xchr[80]:='P'; 
xchr[81]:='Q'; 
xchr[82]:='R'; 
xchr[83]:='S'; 
xchr[84]:='T'; 
xchr[85]:='U'; 
xchr[86]:='V'; 
xchr[87]:='W';
 
xchr[88]:='X'; 
xchr[89]:='Y'; 
xchr[90]:='Z'; 
xchr[91]:='['; 
xchr[92]:='\'; 
xchr[93]:=']'; 
xchr[94]:='^'; 
xchr[95]:='_';
 
xchr[96]:='`'; 
xchr[97]:='a'; 
xchr[98]:='b'; 
xchr[99]:='c'; 
xchr[100]:='d'; 
xchr[101]:='e'; 
xchr[102]:='f'; 
xchr[103]:='g';
 
xchr[104]:='h'; 
xchr[105]:='i'; 
xchr[106]:='j'; 
xchr[107]:='k'; 
xchr[108]:='l'; 
xchr[109]:='m'; 
xchr[110]:='n'; 
xchr[111]:='o';
 
xchr[112]:='p'; 
xchr[113]:='q'; 
xchr[114]:='r'; 
xchr[115]:='s'; 
xchr[116]:='t'; 
xchr[117]:='u'; 
xchr[118]:='v'; 
xchr[119]:='w';
 
xchr[120]:='x'; 
xchr[121]:='y'; 
xchr[122]:='z'; 
xchr[123]:='{'; 
xchr[124]:='|'; 
xchr[125]:='}'; 
xchr[126]:='~';
 

MODULE: 'Set init...'
(*PASCAL module 23*)
for i:=0 to 31 do xchr[i]:=' '; 
for i:=127 to 255 do xchr[i]:=' '; 

MODULE: 'Set init...'
(*PASCAL module 24*)
for i:=first_text_char to last_text_char do xord[chr(i)]:=invalid_code; 
for i:=128 to 255 do xord[xchr[i]]:=i; 
for i:=0 to 126 do xord[xchr[i]]:=i; 

MODULE: 'Types... '
(*PASCAL module 25*)
eight_bits=0..255; {unsigned one-byte quantity} 
alpha_file=packed file of text_char; {files that contain textual data} 
byte_file=packed file of eight_bits; {files that contain binary data} 

MODULE: 'Glob... '
(*PASCAL module 26*)
name_of_file:packed array[1..file_name_size] of char;;
 
  {on some systems this may be a \&[record] variable} 
name_length:0..file_name_size;
{this many characters are actually 
  relevant in |name_of_file| (the rest are blank)} 

MODULE: 'Glob... '
(*PASCAL module 30*)
buffer:array[0..buf_size] of ASCII_code; {lines of characters being read} 
first:0..buf_size; {the first unused position in |buffer|} 
last:0..buf_size; {end of the line just input to |buffer|} 
max_buf_stack:0..buf_size; {largest index used in |buffer|} 

MODULE: 'Glob... '
(*PASCAL module 32*)
term_in:alpha_file; {the terminal as an input file} 
term_out:alpha_file; {the terminal as an output file} 

MODULE: 'Report overflow of the input buffer, and abort'
(*PASCAL module 35*)
if format_ident=0 then 
  begin write_ln(term_out,'Buffer size exceeded!'); goto final_end; 
(*Buffer size exceeded*) 
  end 
else begin cur_input.loc_field:=first; cur_input.limit_field:=last-1; 
  overflow('buffer size',buf_size); 
(*TeX capacity exceeded buffer size][\quad buffer size*) 
  end 

MODULE: 'Types... '
(*PASCAL module 38*)
pool_pointer = 0..pool_size; {for variables that point into |str_pool|} 
str_number = 0..max_strings; {for variables that point into |str_start|} 
packed_ASCII_code = 0..255; {elements of |str_pool| array} 

MODULE: 'Glob... '
(*PASCAL module 39*)
str_pool:packed array[pool_pointer] of packed_ASCII_code; {the characters} 
str_start : array[str_number] of pool_pointer; {the starting pointers} 
pool_ptr : pool_pointer; {first unused position in |str_pool|} 
str_ptr : str_number; {number of the current string being created} 
init_pool_ptr : pool_pointer; {the starting value of |pool_ptr|} 
init_str_ptr : str_number; {the starting value of |str_ptr|} 

MODULE: 'Make the first 256...'
(*PASCAL module 48*)
for k:=0 to 255 do 
  begin if (
INSERT: 'Character |k| cannot be printed'
) then 
    begin append_char('^'); append_char('^'); 
    if k<64 then append_char(k+64) 
    else if k<128 then append_char(k-64) 
    else begin app_lc_hex(k div 16); app_lc_hex(k mod 16); 
      end; 
    end 
  else append_char(k); 
  g:=make_string; 
  end 

MODULE: 'Character |k| cannot be printed'
(*PASCAL module 49*)
  (k<' ')or(k>'~') 

MODULE: 'Glob... '
(*PASCAL module 50*)
init pool_file:alpha_file; {the string-pool file output by \.[TANGLE]} 
tini 

MODULE: 'Read the other strings...'
(*PASCAL module 51*)
name_of_file:=pool_name; {we needn't set |name_length|} 
if a_open_in(pool_file) then 
  begin c:=false; 
  repeat 
INSERT: 'Read one string, but return |false| if the     string memory space is getting too tight for comfort'
; 
  until c; 
  a_close(pool_file); get_strings_started:=true; 
  end 
else  bad_pool('! I can''t read TEX.POOL.') 
(*I can''t read TEX.POOL*) 

MODULE: 'Read one string...'
(*PASCAL module 52*)
begin if eof(pool_file) then bad_pool('! TEX.POOL has no check sum.'); 
(*TEX.POOL has no check sum*) 
read(pool_file,m,n); {read two digits of string length} 
if m='*' then 
INSERT: 'Check the pool check sum'

else  begin if (xord[m]<'0')or(xord[m]>'9')or 
      (xord[n]<'0')or(xord[n]>'9') then 
    bad_pool('! TEX.POOL line doesn''t begin with two digits.'); 
(*TEX.POOL line doesn''t...*) 
  l:=xord[m]*10+xord[n]-'0'*11; {compute the length} 
  if pool_ptr+l+string_vacancies>pool_size then 
    bad_pool('! You have to increase POOLSIZE.'); 
(*You have to increase POOLSIZE*) 
  for k:=1 to l do 
    begin if eoln(pool_file) then m:=' 'else read(pool_file,m); 
    append_char(xord[m]); 
    end; 
  read_ln(pool_file); g:=make_string; 
  end; 
end 

MODULE: 'Check the pool check sum'
(*PASCAL module 53*)
begin a:=0; k:=1; 
loop  begin if (xord[n]<'0')or(xord[n]>'9') then 
  bad_pool('! TEX.POOL check sum doesn''t have nine digits.'); 
(*TEX.POOL check sum...*) 
  a:=10*a+xord[n]-'0'; 
  if k=9 then goto done; 
  incr(k); read(pool_file,n); 
  end; 
done: if a<>@$ then bad_pool('! TEX.POOL doesn''t match; TANGLE me again.'); 
(*TEX.POOL doesn''t match*) 
c:=true; 
end 

MODULE: 'Glob... '
(*PASCAL module 54*)
log_file : alpha_file; {transcript of \TeX\ session} 
selector : 0..max_selector; {where to print a message} 
dig : array[0..22] of 0..15; {digits in a number being output} 
tally : integer; {the number of characters recently printed} 
term_offset : 0..max_print_line; 
  {the number of characters on the current terminal line} 
file_offset : 0..max_print_line; 
  {the number of characters on the current file line} 
trick_buf:array[0..error_line] of ASCII_code; {circular buffer for 
  pseudoprinting} 
trick_count: integer; {threshold for pseudoprinting, explained later} 
first_count: integer; {another variable for pseudoprinting} 

MODULE: 'Initialize the output routines'
(*PASCAL module 55*)
selector:=term_only; tally:=0; term_offset:=0; file_offset:=0; 

MODULE: 'Basic print...'
(*PASCAL module 57*)
procedure print_ln; {prints an end-of-line} 
begin case selector of 
term_and_log: begin wterm_cr; wlog_cr; 
  term_offset:=0; file_offset:=0; 
  end; 
log_only: begin wlog_cr; file_offset:=0; 
  end; 
term_only: begin wterm_cr; term_offset:=0; 
  end; 
no_print,pseudo,new_string: do_nothing; 
othercases write_ln(write_file[selector]) 
endcases;
 
end; {|tally| is not affected} 

MODULE: 'Basic printing...'
(*PASCAL module 58*)
procedure print_char(s:ASCII_code); {prints a single character} 
label exit; 
begin if 
INSERT: 'Character |s| is the current new-line character'
 then 
 if selector<pseudo then 
  begin print_ln; return; 
  end; 
case selector of 
term_and_log: begin wterm(xchr[s]); wlog(xchr[s]); 
  incr(term_offset); incr(file_offset); 
  if term_offset=max_print_line then 
    begin wterm_cr; term_offset:=0; 
    end; 
  if file_offset=max_print_line then 
    begin wlog_cr; file_offset:=0; 
    end; 
  end; 
log_only: begin wlog(xchr[s]); incr(file_offset); 
  if file_offset=max_print_line then print_ln; 
  end; 
term_only: begin wterm(xchr[s]); incr(term_offset); 
  if term_offset=max_print_line then print_ln; 
  end; 
no_print: do_nothing; 
pseudo: if tally<trick_count then trick_buf[tally mod error_line]:=s; 
new_string: begin if pool_ptr<pool_size then append_char(s); 
  end; {we drop characters if the string space is full} 
othercases write(write_file[selector],xchr[s]) 
endcases;
 
incr(tally); 
exit:end; 

MODULE: 'Basic print...'
(*PASCAL module 59*)
procedure print(s:integer); {prints string |s|} 
label exit; 
var j:pool_pointer; {current character code position} 
nl:integer; {new-line character to restore} 
begin if s>=str_ptr then s:='???' {this can''t happen} 
(*???*) 
else if s<256 then 
  if s<0 then s:='???' {can''t happen} 
  else begin if selector>pseudo then 
      begin print_char(s); return; {internal strings are not expanded} 
      end; 
    if (
INSERT: 'Character |s| is the current new-line character'
) then 
      if selector<pseudo then 
        begin print_ln; return; 
        end; 
    nl:=new_line_char; new_line_char:=-1; 
      {temporarily disable new-line character} 
    j:=str_start[s]; 
    while j<str_start[s+1] do 
      begin print_char(so(str_pool[j])); incr(j); 
      end; 
    new_line_char:=nl; return; 
    end; 
j:=str_start[s]; 
while j<str_start[s+1] do 
  begin print_char(so(str_pool[j])); incr(j); 
  end; 
exit:end; 

MODULE: 'Basic print...'
(*PASCAL module 60*)
procedure slow_print(s:integer); {prints string |s|} 
var j:pool_pointer; {current character code position} 
begin if (s>=str_ptr) or (s<256) then print(s) 
else begin j:=str_start[s]; 
  while j<str_start[s+1] do 
    begin print(so(str_pool[j])); incr(j); 
    end; 
  end; 
end; 

MODULE: 'Initialize the output...'
(*PASCAL module 61*)
wterm(banner); 
if format_ident=0 then wterm_ln(' (no format preloaded)') 
else  begin slow_print(format_ident); print_ln; 
  end; 
update_terminal; 

MODULE: 'Basic print...'
(*PASCAL module 62*)
procedure print_nl(s:str_number); {prints string |s| at beginning of line} 
begin if ((term_offset>0)and(odd(selector)))or 
  ((file_offset>0)and(selector>=log_only)) then print_ln; 
print(s); 
end; 

MODULE: 'Basic print...'
(*PASCAL module 63*)
procedure print_esc(s:str_number); {prints escape character, then |s|} 
var c:integer; {the escape character code} 
begin  
INSERT: 'Set variable |c| to the current escape character'
; 
if c>=0 then if c<256 then print(c); 
slow_print(s); 
end; 

MODULE: 'Basic print...'
(*PASCAL module 64*)
procedure print_the_digs(k:eight_bits); 
  {prints |dig[k-1]|$\,\ldots\,$|dig[0]|} 
begin while k>0 do 
  begin decr(k); 
  if dig[k]<10 then print_char('0'+dig[k]) 
  else print_char('A'-10+dig[k]); 
  end; 
end; 

MODULE: 'Basic print...'
(*PASCAL module 65*)
procedure print_int(n:integer); {prints an integer in decimal form} 
var k:0..23; {index to current digit; we assume that $|n|<10^[23]$} 
m:integer; {used to negate |n| in possibly dangerous cases} 
begin k:=0; 
if n<0 then 
  begin print_char('-'); 
  if n>-100000000 then negate(n) 
  else  begin m:=-1-n; n:=m div 10; m:=(m mod 10)+1; k:=1; 
    if m<10 then dig[0]:=m 
    else  begin dig[0]:=0; incr(n); 
      end; 
    end; 
  end; 
repeat dig[k]:=n mod 10; n:=n div 10; incr(k); 
until n=0; 
print_the_digs(k); 
end; 

MODULE: 'Glob... '
(*PASCAL module 73*)
interaction:batch_mode..error_stop_mode; {current level of interaction} 

MODULE: 'Initialize the print |selector| based on |interaction|'
(*PASCAL module 75*)
if interaction=batch_mode then selector:=no_printelse selector:=term_only 

MODULE: 'Glob... '
(*PASCAL module 76*)
deletions_allowed:boolean; {is it safe for |error| to call |get_token|?} 
set_box_allowed:boolean; {is it safe to do a \.[\\setbox] assignment?} 
history:spotless..fatal_error_stop; {has the source input been clean so far?} 
error_count:-1..100; {the number of scrolled errors since the 
  last paragraph ended} 

MODULE: 'Set init...'
(*PASCAL module 77*)
deletions_allowed:=true; set_box_allowed:=true; 
error_count:=0; {|history| is initialized elsewhere} 

MODULE: 'Error handling...'
(*PASCAL module 78*)
procedure normalize_selector; forward;(*\2*)
 
procedure get_token; forward;(*\2*)
 
procedure term_input; forward;(*\2*)
 
procedure show_context; forward;(*\2*)
 
procedure begin_file_reading; forward;(*\2*)
 
procedure open_log_file; forward;(*\2*)
 
procedure close_files_and_terminate; forward;(*\2*)
 
procedure clear_for_error_prompt; forward;(*\2*)
 
procedure give_err_help; forward;(*\2*)
 
(*\4\hskip-\fontdimen2\font*);debugprocedure debug_help; 
  forward;;gubed 

MODULE: 'Glob... '
(*PASCAL module 79*)
help_line:array[0..5] of str_number; {helps for the next |error|} 
help_ptr:0..6; {the number of help lines present} 
use_err_help:boolean; {should the |err_help| list be shown?} 

MODULE: 'Set init...'
(*PASCAL module 80*)
help_ptr:=0; use_err_help:=false; 

MODULE: 'Error hand...'
(*PASCAL module 81*)
procedure jump_out; 
begin goto end_of_TEX; 
end; 

MODULE: 'Error hand...'
(*PASCAL module 82*)
procedure error; {completes the job of error reporting} 
label continue,exit; 
var c:ASCII_code; {what the user types} 
s1,s2,s3,s4:integer; 
  {used to save global variables when deleting tokens} 
begin if history<error_message_issued then history:=error_message_issued; 
print_char('.'); show_context; 
if interaction=error_stop_mode then 
INSERT: 'Get user''s advice and |return|'
; 
incr(error_count); 
if error_count=100 then 
  begin print_nl('(That makes 100 errors; please try again.)'); 
(*That makes 100 errors...*) 
  history:=fatal_error_stop; jump_out; 
  end; 

INSERT: 'Put help message on the transcript file'
; 
exit:end; 

MODULE: 'Get user''s advice...'
(*PASCAL module 83*)
loopbegin continue: clear_for_error_prompt; prompt_input('? '); 
(*?\relax*) 
  if last=first then return; 
  c:=buffer[first]; 
  if c>='a' then c:=c+'A'-'a'; {convert to uppercase} 
  
INSERT: 'Interpret code |c| and |return| if done'
; 
  end 

MODULE: 'Interpret code |c| and |return| if done'
(*PASCAL module 84*)
case c of 
'0','1','2','3','4','5','6','7','8','9': if deletions_allowed then 
  
INSERT: 'Delete \(c)|c-''0''| tokens and |goto continue|'
; 
(*\4\4*);debug 'D': begin debug_help; goto continue;end;gubed
 
'E': if base_ptr>0 then 
  begin print_nl('You want to edit file '); 
(*You want to edit file x*) 
  slow_print(input_stack[base_ptr].name_field); 
  print(' at line '); print_int(line); 
  interaction:=scroll_mode; jump_out; 
  end; 
'H': 
INSERT: 'Print the help information and |goto continue|'
; 
'I':
INSERT: 'Introduce new material from the terminal and |return|'
; 
'Q','R','S':
INSERT: 'Change the interaction level and |return|'
; 
'X':begin interaction:=scroll_mode; jump_out; 
  end; 
othercases do_nothing 
endcases;
 

INSERT: 'Print the menu of available options'


MODULE: 'Print the menu...'
(*PASCAL module 85*)
begin print('Type <return> to proceed, S to scroll future error messages,');
 
(*Type <return> to proceed...*) 
print_nl('R to run without stopping, Q to run quietly,');
 
print_nl('I to insert something, '); 
if base_ptr>0 then print('E to edit your file,'); 
if deletions_allowed then 
  print_nl('1 or ... or 9 to ignore the next 1 to 9 tokens of input,'); 
print_nl('H for help, X to quit.'); 
end 

MODULE: 'Change the interaction...'
(*PASCAL module 86*)
begin error_count:=0; interaction:=batch_mode+c-'Q'; 
print('OK, entering '); 
case c of 
'Q':begin print_esc('batchmode'); decr(selector); 
  end; 
'R':print_esc('nonstopmode'); 
'S':print_esc('scrollmode'); 
end; {there are no other cases} 
print('...'); print_ln; update_terminal; return; 
end 

MODULE: 'Introduce new material...'
(*PASCAL module 87*)
begin begin_file_reading; {enter a new syntactic level for terminal input} 
{now |state=mid_line|, so an initial blank space will count as a blank} 
if last>first+1 then 
  begin loc:=first+1; buffer[first]:=' '; 
  end 
else  begin prompt_input('insert>'); loc:=first; 
(*insert>*) 
  end; 
first:=last; 
cur_input.limit_field:=last-1; {no |end_line_char| ends this line} 
return; 
end 

MODULE: 'Delete \(c)|c-''0''| tokens...'
(*PASCAL module 88*)
begin s1:=cur_tok; s2:=cur_cmd; s3:=cur_chr; s4:=align_state; 
align_state:=1000000; OK_to_interrupt:=false; 
if (last>first+1) and (buffer[first+1]>='0')and(buffer[first+1]<='9') then 
  c:=c*10+buffer[first+1]-'0'*11 
else c:=c-'0'; 
while c>0 do 
  begin get_token; {one-level recursive call of |error| is possible} 
  decr(c); 
  end; 
cur_tok:=s1; cur_cmd:=s2; cur_chr:=s3; align_state:=s4; OK_to_interrupt:=true; 
help2('I have just deleted some text, as you asked.')
 
('You can now delete more, or insert, or whatever.'); 
show_context; goto continue; 
end 

MODULE: 'Print the help info...'
(*PASCAL module 89*)
begin if use_err_help then 
  begin give_err_help; use_err_help:=false; 
  end 
else  begin if help_ptr=0 then 
    help2('Sorry, I don''t know how to help in this situation.')
 
    (*\kern1em*)('Maybe you should try asking a human?'); 
  repeat decr(help_ptr); print(help_line[help_ptr]); print_ln; 
  until help_ptr=0; 
  end; 
help4('Sorry, I already gave what help I could...')
 
  ('Maybe you should try asking a human?')
 
  ('An error might have occurred before I noticed any problems.')
 
  ('``If all else fails, read the instructions.''''');
 
goto continue; 
end 

MODULE: 'Put help message on the transcript file'
(*PASCAL module 90*)
if interaction>batch_mode then decr(selector); {avoid terminal output} 
if use_err_help then 
  begin print_ln; give_err_help; 
  end 
else while help_ptr>0 do 
  begin decr(help_ptr); print_nl(help_line[help_ptr]); 
  end; 
print_ln; 
if interaction>batch_mode then incr(selector); {re-enable terminal output} 
print_ln 

MODULE: 'Error hand...'
(*PASCAL module 93*)
procedure fatal_error(s:str_number); {prints |s|, and that's it} 
begin normalize_selector;
 
print_err('Emergency stop'); help1(s); succumb; 
(*Emergency stop*) 
end; 

MODULE: 'Error hand...'
(*PASCAL module 94*)
procedure overflow(s:str_number;n:integer); {stop due to finiteness} 
begin normalize_selector; 
print_err('TeX capacity exceeded, sorry ['); 
(*TeX capacity exceeded ...*) 
print(s); print_char('='); print_int(n); print_char(']'); 
help2('If you really absolutely need more capacity,')
 
  ('you can ask a wizard to enlarge me.'); 
succumb; 
end; 

MODULE: 'Error hand...'
(*PASCAL module 95*)
procedure confusion(s:str_number); 
  {consistency check violated; |s| tells where} 
begin normalize_selector; 
if history<error_message_issued then 
  begin print_err('This can''t happen ('); print(s); print_char(')'); 
(*This can''t happen*) 
  help1('I''m broken. Please show this to someone who can fix can fix'); 
  end 
else  begin print_err('I can''t go on meeting you like this'); 
(*I can''t go on...*) 
  help2('One of your faux pas seems to have wounded me deeply...')
 
    ('in fact, I''m barely conscious. Please fix it and try again.'); 
  end; 
succumb; 
end; 

MODULE: 'Global... '
(*PASCAL module 96*)
interrupt:integer; {should \TeX\ pause for instructions?} 
OK_to_interrupt:boolean; {should interrupts be observed?} 

MODULE: 'Set init...'
(*PASCAL module 97*)
interrupt:=0; OK_to_interrupt:=true; 

MODULE: 'Types... '
(*PASCAL module 101*)
scaled = integer; {this type is used for scaled integers} 
nonnegative_integer=0..2147483647; {$0\L x<2^[31]$} 
small_number=0..63; {this type is self-explanatory} 

MODULE: 'Glob... '
(*PASCAL module 104*)
arith_error:boolean; {has arithmetic overflow occurred recently?} 
remainder:scaled; {amount subtracted to get an exact division} 

MODULE: 'Types... '
(*PASCAL module 109*)
glue_ratio=real; {one-word representation of a glue expansion factor} 

MODULE: 'Check the ``constant''''...'
(*PASCAL module 111*)
init if (mem_min<>mem_bot)or(mem_max<>mem_top) then bad:=10;tini;
 
if (mem_min>mem_bot)or(mem_max<mem_top) then bad:=10; 
if (min_quarterword>0)or(max_quarterword<127) then bad:=11; 
if (min_halfword>0)or(max_halfword<32767) then bad:=12; 
if (min_quarterword<min_halfword)or 
  (max_quarterword>max_halfword) then bad:=13; 
if (mem_min<min_halfword)or(mem_max>=max_halfword)or 
  (mem_bot-mem_min>max_halfword+1) then bad:=14; 
if (font_base<min_quarterword)or(font_max>max_quarterword) then bad:=15; 
if font_max>font_base+256 then bad:=16; 
if (save_size>max_halfword)or(max_strings>max_halfword) then bad:=17; 
if buf_size>max_halfword then bad:=18; 
if max_quarterword-min_quarterword<255 then bad:=19; 

MODULE: 'Types... '
(*PASCAL module 113*)
quarterword = min_quarterword..max_quarterword; {1/4 of a word} 
halfword=min_halfword..max_halfword; {1/2 of a word} 
two_choices = 1..2; {used when there are two variants in a record} 
four_choices = 1..4; {used when there are four variants in a record} 
two_halves = packed record;
 
  rh:halfword; 
  case two_choices of 
  1: (lh:halfword); 
  2: (b0:quarterword; b1:quarterword); 
  end; 
four_quarters = packed record;
 
  b0:quarterword; 
  b1:quarterword; 
  b2:quarterword; 
  b3:quarterword; 
  end; 
memory_word = record;
 
  case four_choices of 
  1: (int:integer); 
  2: (gr:glue_ratio); 
  3: (hh:two_halves); 
  4: (qqqq:four_quarters); 
  end; 
word_file = file of memory_word; 

MODULE: 'Glob... '
(*PASCAL module 115*)
temp_ptr:pointer; {a pointer variable for occasional emergency use} 

MODULE: 'Glob... '
(*PASCAL module 116*)
mem : array[mem_min..mem_max] of memory_word; {the big dynamic storage area} 
lo_mem_max : pointer; {the largest location of variable-size memory in use} 
hi_mem_min : pointer; {the smallest location of one-word memory in use} 

MODULE: 'Glob... '
(*PASCAL module 117*)
var_used, dyn_used : integer; {how much memory is in use} 

MODULE: 'Glob... '
(*PASCAL module 118*)
avail : pointer; {head of the list of available one-word nodes} 
mem_end : pointer; {the last one-word node used in |mem|} 

MODULE: 'Glob... '
(*PASCAL module 124*)
rover : pointer; {points to some node in the list of empties} 

MODULE: 'Grow more variable-size memory and |goto restart|'
(*PASCAL module 126*)
begin if hi_mem_min-lo_mem_max>=1998 then t:=lo_mem_max+1000 
else t:=lo_mem_max+1+(hi_mem_min-lo_mem_max) div 2; 
  {|lo_mem_max+2<=t<hi_mem_min|} 
p:=llink(rover); q:=lo_mem_max; rlink(p):=q; llink(rover):=q;
 
if t>mem_bot+max_halfword then t:=mem_bot+max_halfword; 
rlink(q):=rover; llink(q):=p; link(q):=empty_flag; node_size(q):=t-lo_mem_max;
 
lo_mem_max:=t; link(lo_mem_max):=null; info(lo_mem_max):=null; 
rover:=q; goto restart; 
end 

MODULE: 'Try to allocate...'
(*PASCAL module 127*)
q:=p+node_size(p); {find the physical successor} 
(*inner loop*) 
while is_empty(q) do {merge node |p| with node |q|} 
  begin t:=rlink(q); 
  if q=rover then rover:=t; 
  llink(t):=llink(q); rlink(llink(q)):=t;
 
  q:=q+node_size(q); 
  end; 
r:=q-s; 
if r>p+1 then 
INSERT: 'Allocate from the top of node |p| and |goto found|'
; 
if r=p then if rlink(p)<>p then 
  
INSERT: 'Allocate entire node |p| and |goto found|'
; 
node_size(p):=q-p {reset the size in case it grew} 

MODULE: 'Allocate from the top...'
(*PASCAL module 128*)
begin node_size(p):=r-p; {store the remaining size} 
(*inner loop*) 
rover:=p; {start searching here next time} 
goto found; 
end 

MODULE: 'Allocate entire...'
(*PASCAL module 129*)
begin rover:=rlink(p); t:=llink(p); 
llink(rover):=t; rlink(t):=rover; 
goto found; 
end 

MODULE: 'Sort \(p)|p|...'
(*PASCAL module 132*)
if p<rover then 
  begin q:=p; p:=rlink(q); rlink(q):=rover; rover:=q; 
  end 
else  begin q:=rover; 
  while rlink(q)<p do q:=rlink(q); 
  r:=rlink(p); rlink(p):=rlink(q); rlink(q):=p; p:=r; 
  end 

MODULE: 'Types... '
(*PASCAL module 150*)
glue_ord=normal..filll; {infinity to the 0, 1, 2, or 3 power} 

MODULE: 'Local variables for init...'
(*PASCAL module 163*)
k:integer; {index into |mem|, |eqtb|, etc.} 

MODULE: 'Initialize table entries...'
(*PASCAL module 164*)
for k:=mem_bot+1 to lo_mem_stat_max do mem[k].sc:=0; 
  {all glue dimensions are zeroed} 
(*data structure assumptions*) 
k:=mem_bot;while k<=lo_mem_stat_max do 
    {set first words of glue specifications} 
  begin glue_ref_count(k):=null+1; 
  stretch_order(k):=normal; shrink_order(k):=normal; 
  k:=k+glue_spec_size; 
  end; 
stretch(fil_glue):=unity; stretch_order(fil_glue):=fil;
 
stretch(fill_glue):=unity; stretch_order(fill_glue):=fill;
 
stretch(ss_glue):=unity; stretch_order(ss_glue):=fil;
 
shrink(ss_glue):=unity; shrink_order(ss_glue):=fil;
 
stretch(fil_neg_glue):=-unity; stretch_order(fil_neg_glue):=fil;
 
rover:=lo_mem_stat_max+1; 
link(rover):=empty_flag; {now initialize the dynamic memory} 
node_size(rover):=1000; {which is a 1000-word available node} 
llink(rover):=rover; rlink(rover):=rover;
 
lo_mem_max:=rover+1000; link(lo_mem_max):=null; info(lo_mem_max):=null;
 
for k:=hi_mem_stat_min to mem_top do 
  mem[k]:=mem[lo_mem_max]; {clear list heads} 

INSERT: 'Initialize the special list heads and constant nodes'
; 
avail:=null; mem_end:=mem_top; 
hi_mem_min:=hi_mem_stat_min; {initialize the one-word memory} 
var_used:=lo_mem_stat_max+1-mem_bot; dyn_used:=hi_mem_stat_usage; 
  {initialize statistics} 

MODULE: 'Glob... '
(*PASCAL module 165*)
debug free: packed array [mem_min..mem_max] of boolean; {free cells} 
(*\hskip10pt*)was_free: packed array [mem_min..mem_max] of boolean; 
  {previously free cells} 
(*\hskip10pt*)was_mem_end,was_lo_max,was_hi_min: pointer; 
  {previous |mem_end|, |lo_mem_max|, and |hi_mem_min|} 
(*\hskip10pt*)panicking:boolean; {do we want to check memory constantly?} 
gubed 

MODULE: 'Set initial...'
(*PASCAL module 166*)
debug was_mem_end:=mem_min; {indicate that everything was previously free} 
was_lo_max:=mem_min; was_hi_min:=mem_max; 
panicking:=false; 
gubed 

MODULE: 'Check single-word...'
(*PASCAL module 168*)
p:=avail; q:=null; clobbered:=false; 
while p<>null do 
  begin if (p>mem_end)or(p<hi_mem_min) then clobbered:=true 
  else if free[p] then clobbered:=true; 
  if clobbered then 
    begin print_nl('AVAIL list clobbered at '); 
(*AVAIL list clobbered...*) 
    print_int(q); goto done1; 
    end; 
  free[p]:=true; q:=p; p:=link(q); 
  end; 
done1: 

MODULE: 'Check variable-size...'
(*PASCAL module 169*)
p:=rover; q:=null; clobbered:=false; 
repeat if (p>=lo_mem_max)or(p<mem_min) then clobbered:=true 
  else if (rlink(p)>=lo_mem_max)or(rlink(p)<mem_min) then clobbered:=true 
  else if  not(is_empty(p))or(node_size(p)<2)or 
   (p+node_size(p)>lo_mem_max)or (llink(rlink(p))<>p) then clobbered:=true; 
  if clobbered then 
  begin print_nl('Double-AVAIL list clobbered at '); 
  print_int(q); goto done2; 
  end; 
for q:=p to p+node_size(p)-1 do {mark all locations free} 
  begin if free[q] then 
    begin print_nl('Doubly free location at '); 
(*Doubly free location...*) 
    print_int(q); goto done2; 
    end; 
  free[q]:=true; 
  end; 
q:=p; p:=rlink(p); 
until p=rover; 
done2: 

MODULE: 'Check flags...'
(*PASCAL module 170*)
p:=mem_min; 
while p<=lo_mem_max do {node |p| should not be empty} 
  begin if is_empty(p) then 
    begin print_nl('Bad flag at '); print_int(p); 
(*Bad flag...*) 
    end; 
  while (p<=lo_mem_max) and not free[p] do incr(p); 
  while (p<=lo_mem_max) and free[p] do incr(p); 
  end 

MODULE: 'Print newly busy...'
(*PASCAL module 171*)
begin print_nl('New busy locs:'); 
for p:=mem_min to lo_mem_max do 
  if not free[p] and ((p>was_lo_max) or was_free[p]) then 
    begin print_char(' '); print_int(p); 
    end; 
for p:=hi_mem_min to mem_end do 
  if not free[p] and 
   ((p<was_hi_min) or (p>was_mem_end) or was_free[p]) then 
    begin print_char(' '); print_int(p); 
    end; 
end 

MODULE: 'Glob... '
(*PASCAL module 173*)
font_in_short_display:integer; {an internal font number} 

MODULE: 'Print a short indication of the contents of node |p|'
(*PASCAL module 175*)
case type(p) of 
hlist_node,vlist_node,ins_node,whatsit_node,mark_node,adjust_node, 
  unset_node: print('[]'); 
rule_node: print_char('|'); 
glue_node: if glue_ptr(p)<>zero_glue then print_char(' '); 
math_node: print_char('$'); 
ligature_node: short_display(lig_ptr(p)); 
disc_node: begin short_display(pre_break(p)); 
  short_display(post_break(p));
 
  n:=replace_count(p); 
  while n>0 do 
    begin if link(p)<>null then p:=link(p); 
    decr(n); 
    end; 
  end; 
othercases do_nothing 
endcases 

MODULE: 'Glob... '
(*PASCAL module 181*)
depth_threshold : integer; {maximum nesting depth in box displays} 
breadth_max : integer; {maximum number of items shown at the same list level} 

MODULE: 'Display node |p|'
(*PASCAL module 183*)
if is_char_node(p) then print_font_and_char(p) 
else  case type(p) of 
  hlist_node,vlist_node,unset_node: 
INSERT: 'Display box |p|'
; 
  rule_node: 
INSERT: 'Display rule |p|'
; 
  ins_node: 
INSERT: 'Display insertion |p|'
; 
  whatsit_node: 
INSERT: 'Display the whatsit node |p|'
; 
  glue_node: 
INSERT: 'Display glue |p|'
; 
  kern_node: 
INSERT: 'Display kern |p|'
; 
  math_node: 
INSERT: 'Display math node |p|'
; 
  ligature_node: 
INSERT: 'Display ligature |p|'
; 
  penalty_node: 
INSERT: 'Display penalty |p|'
; 
  disc_node: 
INSERT: 'Display discretionary |p|'
; 
  mark_node: 
INSERT: 'Display mark |p|'
; 
  adjust_node: 
INSERT: 'Display adjustment |p|'
; 
  (*\4*)
INSERT: 'Cases of |show_node_list| that arise in mlists only'
; 
  othercases print('Unknown node type!') 
  endcases 

MODULE: 'Display box |p|'
(*PASCAL module 184*)
begin if type(p)=hlist_node then print_esc('h') 
else if type(p)=vlist_node then print_esc('v') 
else print_esc('unset'); 
print('box('); print_scaled(height(p)); print_char('+'); 
print_scaled(depth(p)); print(')x'); print_scaled(width(p)); 
if type(p)=unset_node then 
  
INSERT: 'Display special fields of the unset node |p|'

else  begin 
INSERT: 'Display the value of |glue_set(p)|'
; 
  if shift_amount(p)<>0 then 
    begin print(', shifted '); print_scaled(shift_amount(p)); 
    end; 
  end; 
node_list_display(list_ptr(p)); {recursive call} 
end 

MODULE: 'Display special fields of the unset node |p|'
(*PASCAL module 185*)
begin if span_count(p)<>min_quarterword then 
  begin print(' ('); print_int(qo(span_count(p))+1); 
  print(' columns)'); 
  end; 
if glue_stretch(p)<>0 then 
  begin print(', stretch '); print_glue(glue_stretch(p),glue_order(p),0); 
  end; 
if glue_shrink(p)<>0 then 
  begin print(', shrink '); print_glue(glue_shrink(p),glue_sign(p),0); 
  end; 
end 

MODULE: 'Display the value of |glue_set(p)|'
(*PASCAL module 186*)
g:=float(glue_set(p)); 
if (g<>float_constant(0))and(glue_sign(p)<>normal) then 
  begin print(', glue set '); 
  if glue_sign(p)=shrinking then print('- '); 
  if abs(mem[p+glue_offset].int)<1048576 then print('?.?') 
  else if abs(g)>float_constant(20000) then 
    begin if g>float_constant(0) then print_char('>') 
    else print('< -'); 
    print_glue(20000*unity,glue_order(p),0); 
    end 
  else print_glue(round(unity*g),glue_order(p),0); 
(*real multiplication*) 
  end 

MODULE: 'Display rule |p|'
(*PASCAL module 187*)
begin print_esc('rule('); print_rule_dimen(height(p)); print_char('+'); 
print_rule_dimen(depth(p)); print(')x'); print_rule_dimen(width(p)); 
end 

MODULE: 'Display insertion |p|'
(*PASCAL module 188*)
begin print_esc('insert'); print_int(qo(subtype(p))); 
print(', natural size '); print_scaled(height(p)); 
print('; split('); print_spec(split_top_ptr(p),0); 
print_char(','); print_scaled(depth(p)); 
print('); float cost '); print_int(float_cost(p)); 
node_list_display(ins_ptr(p)); {recursive call} 
end 

MODULE: 'Display glue |p|'
(*PASCAL module 189*)
if subtype(p)>=a_leaders then 
INSERT: 'Display leaders |p|'

else  begin print_esc('glue'); 
  if subtype(p)<>normal then 
    begin print_char('('); 
    if subtype(p)<cond_math_glue then 
      print_skip_param(subtype(p)-1) 
    else if subtype(p)=cond_math_glue then print_esc('nonscript') 
    else print_esc('mskip'); 
    print_char(')'); 
    end; 
  if subtype(p)<>cond_math_glue then 
    begin print_char(' '); 
    if subtype(p)<cond_math_glue then print_spec(glue_ptr(p),0) 
    else print_spec(glue_ptr(p),'mu'); 
    end; 
  end 

MODULE: 'Display leaders |p|'
(*PASCAL module 190*)
begin print_esc(''); 
if subtype(p)=c_leaders then print_char('c') 
else if subtype(p)=x_leaders then print_char('x'); 
print('leaders '); print_spec(glue_ptr(p),0); 
node_list_display(leader_ptr(p)); {recursive call} 
end 

MODULE: 'Display kern |p|'
(*PASCAL module 191*)
if subtype(p)<>mu_glue then 
  begin print_esc('kern'); 
  if subtype(p)<>normal then print_char(' '); 
  print_scaled(width(p)); 
  if subtype(p)=acc_kern then print(' (for accent)'); 
(*for accent*) 
  end 
else  begin print_esc('mkern'); print_scaled(width(p)); print('mu'); 
  end 

MODULE: 'Display math node |p|'
(*PASCAL module 192*)
begin print_esc('math'); 
if subtype(p)=before then print('on') 
else print('off'); 
if width(p)<>0 then 
  begin print(', surrounded '); print_scaled(width(p)); 
  end; 
end 

MODULE: 'Display ligature |p|'
(*PASCAL module 193*)
begin print_font_and_char(lig_char(p)); print(' (ligature '); 
if subtype(p)>1 then print_char('|'); 
font_in_short_display:=font(lig_char(p)); short_display(lig_ptr(p)); 
if odd(subtype(p)) then print_char('|'); 
print_char(')'); 
end 

MODULE: 'Display penalty |p|'
(*PASCAL module 194*)
begin print_esc('penalty '); print_int(penalty(p)); 
end 

MODULE: 'Display discretionary |p|'
(*PASCAL module 195*)
begin print_esc('discretionary'); 
if replace_count(p)>0 then 
  begin print(' replacing '); print_int(replace_count(p)); 
  end; 
node_list_display(pre_break(p)); {recursive call} 
append_char('|'); show_node_list(post_break(p)); flush_char; {recursive call} 
end 

MODULE: 'Display mark |p|'
(*PASCAL module 196*)
begin print_esc('mark'); print_mark(mark_ptr(p)); 
end 

MODULE: 'Display adjustment |p|'
(*PASCAL module 197*)
begin print_esc('vadjust'); node_list_display(adjust_ptr(p)); {recursive call} 
end 

MODULE: 'Make a copy of node |p|...'
(*PASCAL module 205*)
words:=1; {this setting occurs in more branches than any other} 
if is_char_node(p) then r:=get_avail 
else 
INSERT: 'Case statement to copy different types and set |words| to the number   of initial words not yet copied'
; 
while words>0 do 
  begin decr(words); mem[r+words]:=mem[p+words]; 
  end 

MODULE: 'Case statement to copy...'
(*PASCAL module 206*)
case type(p) of 
hlist_node,vlist_node,unset_node: begin r:=get_node(box_node_size); 
  mem[r+6]:=mem[p+6]; mem[r+5]:=mem[p+5]; {copy the last two words} 
  list_ptr(r):=copy_node_list(list_ptr(p)); {this affects |mem[r+5]|} 
  words:=5; 
  end; 
rule_node: begin r:=get_node(rule_node_size); words:=rule_node_size; 
  end; 
ins_node: begin r:=get_node(ins_node_size); mem[r+4]:=mem[p+4]; 
  add_glue_ref(split_top_ptr(p)); 
  ins_ptr(r):=copy_node_list(ins_ptr(p)); {this affects |mem[r+4]|} 
  words:=ins_node_size-1; 
  end; 
whatsit_node:
INSERT: 'Make a partial copy of the whatsit node |p| and make |r|   point to it; set |words| to the number of initial words not yet copied'
; 
glue_node: begin r:=get_node(small_node_size); add_glue_ref(glue_ptr(p)); 
  glue_ptr(r):=glue_ptr(p); leader_ptr(r):=copy_node_list(leader_ptr(p)); 
  end; 
kern_node,math_node,penalty_node: begin r:=get_node(small_node_size); 
  words:=small_node_size; 
  end; 
ligature_node: begin r:=get_node(small_node_size); 
  mem[lig_char(r)]:=mem[lig_char(p)]; {copy |font| and |character|} 
  lig_ptr(r):=copy_node_list(lig_ptr(p)); 
  end; 
disc_node: begin r:=get_node(small_node_size); 
  pre_break(r):=copy_node_list(pre_break(p)); 
  post_break(r):=copy_node_list(post_break(p)); 
  end; 
mark_node: begin r:=get_node(small_node_size); add_token_ref(mark_ptr(p)); 
  words:=small_node_size; 
  end; 
adjust_node: begin r:=get_node(small_node_size); 
  adjust_ptr(r):=copy_node_list(adjust_ptr(p)); 
  end; {|words=1=small_node_size-1|} 
othercases confusion('copying') 
(*this can''t happen copying][\quad copying*) 
endcases 

MODULE: 'Types... '
(*PASCAL module 212*)
list_state_record=recordmode_field:-mmode..mmode; 
  head_field,tail_field: pointer; 
  pg_field,ml_field: integer; 
  aux_field: memory_word; 
  end; 

MODULE: 'Glob... '
(*PASCAL module 213*)
nest:array[0..nest_size] of list_state_record; 
nest_ptr:0..nest_size; {first unused location of |nest|} 
max_nest_stack:0..nest_size; {maximum of |nest_ptr| when pushing} 
cur_list:list_state_record; {the ``top'' semantic state} 
shown_mode:-mmode..mmode; {most recent mode shown by \.[\\tracingcommands]} 

MODULE: 'Set init...'
(*PASCAL module 215*)
nest_ptr:=0; max_nest_stack:=0; 
mode:=vmode; head:=contrib_head; tail:=contrib_head; 
prev_depth:=ignore_depth; mode_line:=0; 
prev_graf:=0; shown_mode:=0; 

INSERT: 'Start a new current page'
; 

MODULE: 'Show the auxiliary...'
(*PASCAL module 219*)
case abs(m) div (max_command+1) of 
0: begin print_nl('prevdepth '); 
  if a.sc<=ignore_depth then print('ignored') 
  else print_scaled(a.sc); 
  if nest[p].pg_field<>0 then 
    begin print(', prevgraf '); 
    print_int(nest[p].pg_field); print(' line'); 
    if nest[p].pg_field<>1 then print_char('s'); 
    end; 
  end; 
1: begin print_nl('spacefactor '); print_int(a.hh.lh); 
  if m>0 then if a.hh.rh>0 then 
    begin print(', current language '); print_int(a.hh.rh); 
    end; 
  end; 
2: if a.int<>null then 
  begin print('this will be denominator of:'); show_box(a.int); 
  end; 
end {there are no other cases} 

MODULE: 'Initialize table entries...'
(*PASCAL module 222*)
eq_type(undefined_control_sequence):=undefined_cs; 
equiv(undefined_control_sequence):=null; 
eq_level(undefined_control_sequence):=level_zero; 
for k:=active_base to undefined_control_sequence-1 do 
  eqtb[k]:=eqtb[undefined_control_sequence]; 

MODULE: 'Show equivalent |n|, in region 1 or 2'
(*PASCAL module 223*)
begin sprint_cs(n); print_char('='); print_cmd_chr(eq_type(n),equiv(n)); 
if eq_type(n)>=call then 
  begin print_char(':'); show_token_list(link(equiv(n)),null,32); 
  end; 
end 

MODULE: 'Declare the procedure called |print_skip_param|'
(*PASCAL module 225*)
procedure print_skip_param(n:integer); 
begin case n of 
line_skip_code: print_esc('lineskip'); 
baseline_skip_code: print_esc('baselineskip'); 
par_skip_code: print_esc('parskip'); 
above_display_skip_code: print_esc('abovedisplayskip'); 
below_display_skip_code: print_esc('belowdisplayskip'); 
above_display_short_skip_code: print_esc('abovedisplayshortskip'); 
below_display_short_skip_code: print_esc('belowdisplayshortskip'); 
left_skip_code: print_esc('leftskip'); 
right_skip_code: print_esc('rightskip'); 
top_skip_code: print_esc('topskip'); 
split_top_skip_code: print_esc('splittopskip'); 
tab_skip_code: print_esc('tabskip'); 
space_skip_code: print_esc('spaceskip'); 
xspace_skip_code: print_esc('xspaceskip'); 
par_fill_skip_code: print_esc('parfillskip'); 
thin_mu_skip_code: print_esc('thinmuskip'); 
med_mu_skip_code: print_esc('medmuskip'); 
thick_mu_skip_code: print_esc('thickmuskip'); 
othercases print('[unknown glue parameter!]') 
endcases; 
end; 

MODULE: 'Put each of \TeX''s primitives into the hash table'
(*PASCAL module 226*)
primitive('lineskip',assign_glue,glue_base+line_skip_code);
 
(*line_skip_][\.{\\lineskip} primitive*) 
primitive('baselineskip',assign_glue,glue_base+baseline_skip_code);
 
(*baseline_skip_][\.{\\baselineskip} primitive*) 
primitive('parskip',assign_glue,glue_base+par_skip_code);
 
(*par_skip_][\.{\\parskip} primitive*) 
primitive('abovedisplayskip',assign_glue,glue_base+above_display_skip_code);
 
(*above_display_skip_][\.{\\abovedisplayskip} primitive*) 
primitive('belowdisplayskip',assign_glue,glue_base+below_display_skip_code);
 
(*below_display_skip_][\.{\\belowdisplayskip} primitive*) 
primitive('abovedisplayshortskip', 
  assign_glue,glue_base+above_display_short_skip_code);
 
(*above_display_short_skip_][\.{\\abovedisplayshortskip} primitive*) 
primitive('belowdisplayshortskip', 
  assign_glue,glue_base+below_display_short_skip_code);
 
(*below_display_short_skip_][\.{\\belowdisplayshortskip} primitive*) 
primitive('leftskip',assign_glue,glue_base+left_skip_code);
 
(*left_skip_][\.{\\leftskip} primitive*) 
primitive('rightskip',assign_glue,glue_base+right_skip_code);
 
(*right_skip_][\.{\\rightskip} primitive*) 
primitive('topskip',assign_glue,glue_base+top_skip_code);
 
(*top_skip_][\.{\\topskip} primitive*) 
primitive('splittopskip',assign_glue,glue_base+split_top_skip_code);
 
(*split_top_skip_][\.{\\splittopskip} primitive*) 
primitive('tabskip',assign_glue,glue_base+tab_skip_code);
 
(*tab_skip_][\.{\\tabskip} primitive*) 
primitive('spaceskip',assign_glue,glue_base+space_skip_code);
 
(*space_skip_][\.{\\spaceskip} primitive*) 
primitive('xspaceskip',assign_glue,glue_base+xspace_skip_code);
 
(*xspace_skip_][\.{\\xspaceskip} primitive*) 
primitive('parfillskip',assign_glue,glue_base+par_fill_skip_code);
 
(*par_fill_skip_][\.{\\parfillskip} primitive*) 
primitive('thinmuskip',assign_mu_glue,glue_base+thin_mu_skip_code);
 
(*thin_mu_skip_][\.{\\thinmuskip} primitive*) 
primitive('medmuskip',assign_mu_glue,glue_base+med_mu_skip_code);
 
(*med_mu_skip_][\.{\\medmuskip} primitive*) 
primitive('thickmuskip',assign_mu_glue,glue_base+thick_mu_skip_code);
 
(*thick_mu_skip_][\.{\\thickmuskip} primitive*) 

MODULE: 'Cases of |print_cmd_chr| for symbolic printing of primitives'
(*PASCAL module 227*)
assign_glue,assign_mu_glue: if chr_code<skip_base then 
    print_skip_param(chr_code-glue_base) 
  else if chr_code<mu_skip_base then 
    begin print_esc('skip'); print_int(chr_code-skip_base); 
    end 
  else  begin print_esc('muskip'); print_int(chr_code-mu_skip_base); 
    end; 

MODULE: 'Initialize table entries...'
(*PASCAL module 228*)
equiv(glue_base):=zero_glue; eq_level(glue_base):=level_one; 
eq_type(glue_base):=glue_ref; 
for k:=glue_base+1 to local_base-1 do eqtb[k]:=eqtb[glue_base]; 
glue_ref_count(zero_glue):=glue_ref_count(zero_glue)+local_base-glue_base; 

MODULE: 'Show equivalent |n|, in region 3'
(*PASCAL module 229*)
if n<skip_base then 
  begin print_skip_param(n-glue_base); print_char('='); 
  if n<glue_base+thin_mu_skip_code then print_spec(equiv(n),'pt') 
  else print_spec(equiv(n),'mu'); 
  end 
else if n<mu_skip_base then 
  begin print_esc('skip'); print_int(n-skip_base); print_char('='); 
  print_spec(equiv(n),'pt'); 
  end 
else  begin print_esc('muskip'); print_int(n-mu_skip_base); print_char('='); 
  print_spec(equiv(n),'mu'); 
  end 

MODULE: 'Put each...'
(*PASCAL module 230*)
primitive('output',assign_toks,output_routine_loc); 
(*output_][\.{\\output} primitive*) 
primitive('everypar',assign_toks,every_par_loc); 
(*every_par_][\.{\\everypar} primitive*) 
primitive('everymath',assign_toks,every_math_loc); 
(*every_math_][\.{\\everymath} primitive*) 
primitive('everydisplay',assign_toks,every_display_loc); 
(*every_display_][\.{\\everydisplay} primitive*) 
primitive('everyhbox',assign_toks,every_hbox_loc); 
(*every_hbox_][\.{\\everyhbox} primitive*) 
primitive('everyvbox',assign_toks,every_vbox_loc); 
(*every_vbox_][\.{\\everyvbox} primitive*) 
primitive('everyjob',assign_toks,every_job_loc); 
(*every_job_][\.{\\everyjob} primitive*) 
primitive('everycr',assign_toks,every_cr_loc); 
(*every_cr_][\.{\\everycr} primitive*) 
primitive('errhelp',assign_toks,err_help_loc); 
(*err_help_][\.{\\errhelp} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 231*)
assign_toks: if chr_code>=toks_base then 
  begin print_esc('toks'); print_int(chr_code-toks_base); 
  end 
else  case chr_code of 
  output_routine_loc: print_esc('output'); 
  every_par_loc: print_esc('everypar'); 
  every_math_loc: print_esc('everymath'); 
  every_display_loc: print_esc('everydisplay'); 
  every_hbox_loc: print_esc('everyhbox'); 
  every_vbox_loc: print_esc('everyvbox'); 
  every_job_loc: print_esc('everyjob'); 
  every_cr_loc: print_esc('everycr'); 
  othercases print_esc('errhelp') 
  endcases; 

MODULE: 'Initialize table entries...'
(*PASCAL module 232*)
par_shape_ptr:=null; eq_type(par_shape_loc):=shape_ref; 
eq_level(par_shape_loc):=level_one;
 
for k:=output_routine_loc to toks_base+255 do 
  eqtb[k]:=eqtb[undefined_control_sequence]; 
box(0):=null; eq_type(box_base):=box_ref; eq_level(box_base):=level_one; 
for k:=box_base+1 to box_base+255 do eqtb[k]:=eqtb[box_base]; 
cur_font:=null_font; eq_type(cur_font_loc):=data; 
eq_level(cur_font_loc):=level_one;
 
for k:=math_font_base to math_font_base+47 do eqtb[k]:=eqtb[cur_font_loc]; 
equiv(cat_code_base):=0; eq_type(cat_code_base):=data; 
eq_level(cat_code_base):=level_one;
 
for k:=cat_code_base+1 to int_base-1 do eqtb[k]:=eqtb[cat_code_base]; 
for k:=0 to 255 do 
  begin cat_code(k):=other_char; math_code(k):=hi(k); sf_code(k):=1000; 
  end; 
cat_code(carriage_return):=car_ret; cat_code(' '):=spacer; 
cat_code('\'):=escape; cat_code('%'):=comment; 
cat_code(invalid_code):=invalid_char; cat_code(null_code):=ignore; 
for k:='0' to '9' do math_code(k):=hi(k+var_code); 
for k:='A' to 'Z' do 
  begin cat_code(k):=letter; cat_code(k+'a'-'A'):=letter;
 
  math_code(k):=hi(k+var_code+64); 
  math_code(k+'a'-'A'):=hi(k+'a'-'A'+var_code+64);
 
  lc_code(k):=k+'a'-'A'; lc_code(k+'a'-'A'):=k+'a'-'A';
 
  uc_code(k):=k; uc_code(k+'a'-'A'):=k;
 
  sf_code(k):=999; 
  end; 

MODULE: 'Show equivalent |n|, in region 4'
(*PASCAL module 233*)
if n=par_shape_loc then 
  begin print_esc('parshape'); print_char('='); 
  if par_shape_ptr=null then print_char('0') 
  else print_int(info(par_shape_ptr)); 
  end 
else if n<toks_base then 
  begin print_cmd_chr(assign_toks,n); print_char('='); 
  if equiv(n)<>null then show_token_list(link(equiv(n)),null,32); 
  end 
else if n<box_base then 
  begin print_esc('toks'); print_int(n-toks_base); print_char('='); 
  if equiv(n)<>null then show_token_list(link(equiv(n)),null,32); 
  end 
else if n<cur_font_loc then 
  begin print_esc('box'); print_int(n-box_base); print_char('='); 
  if equiv(n)=null then print('void') 
  else  begin depth_threshold:=0; breadth_max:=1; show_node_list(equiv(n)); 
    end; 
  end 
else if n<cat_code_base then 
INSERT: 'Show the font identifier in |eqtb[n]|'

else 
INSERT: 'Show the halfword code in |eqtb[n]|'


MODULE: 'Show the font identifier in |eqtb[n]|'
(*PASCAL module 234*)
begin if n=cur_font_loc then print('current font') 
else if n<math_font_base+16 then 
  begin print_esc('textfont'); print_int(n-math_font_base); 
  end 
else if n<math_font_base+32 then 
  begin print_esc('scriptfont'); print_int(n-math_font_base-16); 
  end 
else  begin print_esc('scriptscriptfont'); print_int(n-math_font_base-32); 
  end; 
print_char('=');
 
print_esc(hash[font_id_base+equiv(n)].rh); 
  {that's |font_id_text(equiv(n))|} 
end 

MODULE: 'Show the halfword code in |eqtb[n]|'
(*PASCAL module 235*)
if n<math_code_base then 
  begin if n<lc_code_base then 
    begin print_esc('catcode'); print_int(n-cat_code_base); 
    end 
  else if n<uc_code_base then 
    begin print_esc('lccode'); print_int(n-lc_code_base); 
    end 
  else if n<sf_code_base then 
    begin print_esc('uccode'); print_int(n-uc_code_base); 
    end 
  else  begin print_esc('sfcode'); print_int(n-sf_code_base); 
    end; 
  print_char('='); print_int(equiv(n)); 
  end 
else  begin print_esc('mathcode'); print_int(n-math_code_base); 
  print_char('='); print_int(ho(equiv(n))); 
  end 

MODULE: 'Assign the values |depth_threshold:=show_box_depth|...'
(*PASCAL module 236*)
depth_threshold:=show_box_depth; 
breadth_max:=show_box_breadth 

MODULE: 'Put each...'
(*PASCAL module 238*)
primitive('pretolerance',assign_int,int_base+pretolerance_code);
 
(*pretolerance_][\.{\\pretolerance} primitive*) 
primitive('tolerance',assign_int,int_base+tolerance_code);
 
(*tolerance_][\.{\\tolerance} primitive*) 
primitive('linepenalty',assign_int,int_base+line_penalty_code);
 
(*line_penalty_][\.{\\linepenalty} primitive*) 
primitive('hyphenpenalty',assign_int,int_base+hyphen_penalty_code);
 
(*hyphen_penalty_][\.{\\hyphenpenalty} primitive*) 
primitive('exhyphenpenalty',assign_int,int_base+ex_hyphen_penalty_code);
 
(*ex_hyphen_penalty_][\.{\\exhyphenpenalty} primitive*) 
primitive('clubpenalty',assign_int,int_base+club_penalty_code);
 
(*club_penalty_][\.{\\clubpenalty} primitive*) 
primitive('widowpenalty',assign_int,int_base+widow_penalty_code);
 
(*widow_penalty_][\.{\\widowpenalty} primitive*) 
primitive('displaywidowpenalty', 
  assign_int,int_base+display_widow_penalty_code);
 
(*display_widow_penalty_][\.{\\displaywidowpenalty} primitive*) 
primitive('brokenpenalty',assign_int,int_base+broken_penalty_code);
 
(*broken_penalty_][\.{\\brokenpenalty} primitive*) 
primitive('binoppenalty',assign_int,int_base+bin_op_penalty_code);
 
(*bin_op_penalty_][\.{\\binoppenalty} primitive*) 
primitive('relpenalty',assign_int,int_base+rel_penalty_code);
 
(*rel_penalty_][\.{\\relpenalty} primitive*) 
primitive('predisplaypenalty',assign_int,int_base+pre_display_penalty_code);
 
(*pre_display_penalty_][\.{\\predisplaypenalty} primitive*) 
primitive('postdisplaypenalty',assign_int,int_base+post_display_penalty_code);
 
(*post_display_penalty_][\.{\\postdisplaypenalty} primitive*) 
primitive('interlinepenalty',assign_int,int_base+inter_line_penalty_code);
 
(*inter_line_penalty_][\.{\\interlinepenalty} primitive*) 
primitive('doublehyphendemerits', 
  assign_int,int_base+double_hyphen_demerits_code);
 
(*double_hyphen_demerits_][\.{\\doublehyphendemerits} primitive*) 
primitive('finalhyphendemerits', 
  assign_int,int_base+final_hyphen_demerits_code);
 
(*final_hyphen_demerits_][\.{\\finalhyphendemerits} primitive*) 
primitive('adjdemerits',assign_int,int_base+adj_demerits_code);
 
(*adj_demerits_][\.{\\adjdemerits} primitive*) 
primitive('mag',assign_int,int_base+mag_code);
 
(*mag_][\.{\\mag} primitive*) 
primitive('delimiterfactor',assign_int,int_base+delimiter_factor_code);
 
(*delimiter_factor_][\.{\\delimiterfactor} primitive*) 
primitive('looseness',assign_int,int_base+looseness_code);
 
(*looseness_][\.{\\looseness} primitive*) 
primitive('time',assign_int,int_base+time_code);
 
(*time_][\.{\\time} primitive*) 
primitive('day',assign_int,int_base+day_code);
 
(*day_][\.{\\day} primitive*) 
primitive('month',assign_int,int_base+month_code);
 
(*month_][\.{\\month} primitive*) 
primitive('year',assign_int,int_base+year_code);
 
(*year_][\.{\\year} primitive*) 
primitive('showboxbreadth',assign_int,int_base+show_box_breadth_code);
 
(*show_box_breadth_][\.{\\showboxbreadth} primitive*) 
primitive('showboxdepth',assign_int,int_base+show_box_depth_code);
 
(*show_box_depth_][\.{\\showboxdepth} primitive*) 
primitive('hbadness',assign_int,int_base+hbadness_code);
 
(*hbadness_][\.{\\hbadness} primitive*) 
primitive('vbadness',assign_int,int_base+vbadness_code);
 
(*vbadness_][\.{\\vbadness} primitive*) 
primitive('pausing',assign_int,int_base+pausing_code);
 
(*pausing_][\.{\\pausing} primitive*) 
primitive('tracingonline',assign_int,int_base+tracing_online_code);
 
(*tracing_online_][\.{\\tracingonline} primitive*) 
primitive('tracingmacros',assign_int,int_base+tracing_macros_code);
 
(*tracing_macros_][\.{\\tracingmacros} primitive*) 
primitive('tracingstats',assign_int,int_base+tracing_stats_code);
 
(*tracing_stats_][\.{\\tracingstats} primitive*) 
primitive('tracingparagraphs',assign_int,int_base+tracing_paragraphs_code);
 
(*tracing_paragraphs_][\.{\\tracingparagraphs} primitive*) 
primitive('tracingpages',assign_int,int_base+tracing_pages_code);
 
(*tracing_pages_][\.{\\tracingpages} primitive*) 
primitive('tracingoutput',assign_int,int_base+tracing_output_code);
 
(*tracing_output_][\.{\\tracingoutput} primitive*) 
primitive('tracinglostchars',assign_int,int_base+tracing_lost_chars_code);
 
(*tracing_lost_chars_][\.{\\tracinglostchars} primitive*) 
primitive('tracingcommands',assign_int,int_base+tracing_commands_code);
 
(*tracing_commands_][\.{\\tracingcommands} primitive*) 
primitive('tracingrestores',assign_int,int_base+tracing_restores_code);
 
(*tracing_restores_][\.{\\tracingrestores} primitive*) 
primitive('uchyph',assign_int,int_base+uc_hyph_code);
 
(*uc_hyph_][\.{\\uchyph} primitive*) 
primitive('outputpenalty',assign_int,int_base+output_penalty_code);
 
(*output_penalty_][\.{\\outputpenalty} primitive*) 
primitive('maxdeadcycles',assign_int,int_base+max_dead_cycles_code);
 
(*max_dead_cycles_][\.{\\maxdeadcycles} primitive*) 
primitive('hangafter',assign_int,int_base+hang_after_code);
 
(*hang_after_][\.{\\hangafter} primitive*) 
primitive('floatingpenalty',assign_int,int_base+floating_penalty_code);
 
(*floating_penalty_][\.{\\floatingpenalty} primitive*) 
primitive('globaldefs',assign_int,int_base+global_defs_code);
 
(*global_defs_][\.{\\globaldefs} primitive*) 
primitive('fam',assign_int,int_base+cur_fam_code);
 
(*fam_][\.{\\fam} primitive*) 
primitive('escapechar',assign_int,int_base+escape_char_code);
 
(*escape_char_][\.{\\escapechar} primitive*) 
primitive('defaulthyphenchar',assign_int,int_base+default_hyphen_char_code);
 
(*default_hyphen_char_][\.{\\defaulthyphenchar} primitive*) 
primitive('defaultskewchar',assign_int,int_base+default_skew_char_code);
 
(*default_skew_char_][\.{\\defaultskewchar} primitive*) 
primitive('endlinechar',assign_int,int_base+end_line_char_code);
 
(*end_line_char_][\.{\\endlinechar} primitive*) 
primitive('newlinechar',assign_int,int_base+new_line_char_code);
 
(*new_line_char_][\.{\\newlinechar} primitive*) 
primitive('language',assign_int,int_base+language_code);
 
(*language_][\.{\\language} primitive*) 
primitive('lefthyphenmin',assign_int,int_base+left_hyphen_min_code);
 
(*left_hyphen_min_][\.{\\lefthyphenmin} primitive*) 
primitive('righthyphenmin',assign_int,int_base+right_hyphen_min_code);
 
(*right_hyphen_min_][\.{\\righthyphenmin} primitive*) 
primitive('holdinginserts',assign_int,int_base+holding_inserts_code);
 
(*holding_inserts_][\.{\\holdinginserts} primitive*) 
primitive('errorcontextlines',assign_int,int_base+error_context_lines_code);
 
(*error_context_lines_][\.{\\errorcontextlines} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 239*)
assign_int: if chr_code<count_base then print_param(chr_code-int_base) 
  else  begin print_esc('count'); print_int(chr_code-count_base); 
    end; 

MODULE: 'Initialize table entries...'
(*PASCAL module 240*)
for k:=int_base to del_code_base-1 do eqtb[k].int:=0; 
mag:=1000; tolerance:=10000; hang_after:=1; max_dead_cycles:=25; 
escape_char:='\'; end_line_char:=carriage_return; 
for k:=0 to 255 do del_code(k):=-1; 
del_code('.'):=0; {this null delimiter is used in error recovery} 

MODULE: 'Show equivalent |n|, in region 5'
(*PASCAL module 242*)
begin if n<count_base then print_param(n-int_base) 
else if  n<del_code_base then 
  begin print_esc('count'); print_int(n-count_base); 
  end 
else  begin print_esc('delcode'); print_int(n-del_code_base); 
  end; 
print_char('='); print_int(eqtb[n].int); 
end 

MODULE: 'Glob... '
(*PASCAL module 246*)
old_setting:0..max_selector; 

MODULE: 'Put each...'
(*PASCAL module 248*)
primitive('parindent',assign_dimen,dimen_base+par_indent_code);
 
(*par_indent_][\.{\\parindent} primitive*) 
primitive('mathsurround',assign_dimen,dimen_base+math_surround_code);
 
(*math_surround_][\.{\\mathsurround} primitive*) 
primitive('lineskiplimit',assign_dimen,dimen_base+line_skip_limit_code);
 
(*line_skip_limit_][\.{\\lineskiplimit} primitive*) 
primitive('hsize',assign_dimen,dimen_base+hsize_code);
 
(*hsize_][\.{\\hsize} primitive*) 
primitive('vsize',assign_dimen,dimen_base+vsize_code);
 
(*vsize_][\.{\\vsize} primitive*) 
primitive('maxdepth',assign_dimen,dimen_base+max_depth_code);
 
(*max_depth_][\.{\\maxdepth} primitive*) 
primitive('splitmaxdepth',assign_dimen,dimen_base+split_max_depth_code);
 
(*split_max_depth_][\.{\\splitmaxdepth} primitive*) 
primitive('boxmaxdepth',assign_dimen,dimen_base+box_max_depth_code);
 
(*box_max_depth_][\.{\\boxmaxdepth} primitive*) 
primitive('hfuzz',assign_dimen,dimen_base+hfuzz_code);
 
(*hfuzz_][\.{\\hfuzz} primitive*) 
primitive('vfuzz',assign_dimen,dimen_base+vfuzz_code);
 
(*vfuzz_][\.{\\vfuzz} primitive*) 
primitive('delimitershortfall', 
  assign_dimen,dimen_base+delimiter_shortfall_code);
 
(*delimiter_shortfall_][\.{\\delimitershortfall} primitive*) 
primitive('nulldelimiterspace', 
  assign_dimen,dimen_base+null_delimiter_space_code);
 
(*null_delimiter_space_][\.{\\nulldelimiterspace} primitive*) 
primitive('scriptspace',assign_dimen,dimen_base+script_space_code);
 
(*script_space_][\.{\\scriptspace} primitive*) 
primitive('predisplaysize',assign_dimen,dimen_base+pre_display_size_code);
 
(*pre_display_size_][\.{\\predisplaysize} primitive*) 
primitive('displaywidth',assign_dimen,dimen_base+display_width_code);
 
(*display_width_][\.{\\displaywidth} primitive*) 
primitive('displayindent',assign_dimen,dimen_base+display_indent_code);
 
(*display_indent_][\.{\\displayindent} primitive*) 
primitive('overfullrule',assign_dimen,dimen_base+overfull_rule_code);
 
(*overfull_rule_][\.{\\overfullrule} primitive*) 
primitive('hangindent',assign_dimen,dimen_base+hang_indent_code);
 
(*hang_indent_][\.{\\hangindent} primitive*) 
primitive('hoffset',assign_dimen,dimen_base+h_offset_code);
 
(*h_offset_][\.{\\hoffset} primitive*) 
primitive('voffset',assign_dimen,dimen_base+v_offset_code);
 
(*v_offset_][\.{\\voffset} primitive*) 
primitive('emergencystretch',assign_dimen,dimen_base+emergency_stretch_code);
 
(*emergency_stretch_][\.{\\emergencystretch} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 249*)
assign_dimen: if chr_code<scaled_base then 
    print_length_param(chr_code-dimen_base) 
  else  begin print_esc('dimen'); print_int(chr_code-scaled_base); 
    end; 

MODULE: 'Initialize table entries...'
(*PASCAL module 250*)
for k:=dimen_base to eqtb_size do eqtb[k].sc:=0; 

MODULE: 'Show equivalent |n|, in region 6'
(*PASCAL module 251*)
begin if n<scaled_base then print_length_param(n-dimen_base) 
else  begin print_esc('dimen'); print_int(n-scaled_base); 
  end; 
print_char('='); print_scaled(eqtb[n].sc); print('pt'); 
end 

MODULE: 'Glob... '
(*PASCAL module 253*)
eqtb:array[active_base..eqtb_size] of memory_word; 
xeq_level:array[int_base..eqtb_size] of quarterword; 

MODULE: 'Set init...'
(*PASCAL module 254*)
for k:=int_base to eqtb_size do xeq_level[k]:=level_one; 

MODULE: 'Search |eqtb| for equivalents equal to |p|'
(*PASCAL module 255*)
for q:=active_base to box_base+255 do 
  begin if equiv(q)=p then 
    begin print_nl('EQUIV('); print_int(q); print_char(')'); 
    end; 
  end 

MODULE: 'Glob... '
(*PASCAL module 256*)
hash: array[hash_base..undefined_control_sequence-1] of two_halves; 
  {the hash table} 
hash_used:pointer; {allocation pointer for |hash|} 
no_new_control_sequence:boolean; {are new identifiers legal?} 
cs_count:integer; {total number of known identifiers} 

MODULE: 'Set init...'
(*PASCAL module 257*)
no_new_control_sequence:=true; {new identifiers are usually forbidden} 
next(hash_base):=0; text(hash_base):=0; 
for k:=hash_base+1 to undefined_control_sequence-1 do hash[k]:=hash[hash_base]; 

MODULE: 'Initialize table entries...'
(*PASCAL module 258*)
hash_used:=frozen_control_sequence; {nothing is used} 
cs_count:=0; 
eq_type(frozen_dont_expand):=dont_expand; 
text(frozen_dont_expand):='notexpanded:'; 
(*notexpanded:*) 

MODULE: 'Insert a new control...'
(*PASCAL module 260*)
begin if text(p)>0 then 
  begin repeat if hash_is_full then overflow('hash size',hash_size); 
(*TeX capacity exceeded hash size][\quad hash size*) 
  decr(hash_used); 
  until text(hash_used)=0; {search for an empty location in |hash|} 
  next(p):=hash_used; p:=hash_used; 
  end; 
str_room(l); d:=cur_length; 
while pool_ptr>str_start[str_ptr] do 
  begin decr(pool_ptr); str_pool[pool_ptr+l]:=str_pool[pool_ptr]; 
  end; {move current string up to make room for another} 
for k:=j to j+l-1 do append_char(buffer[k]); 
text(p):=make_string; pool_ptr:=pool_ptr+d; 
stat incr(cs_count);tats;
 
end 

MODULE: 'Compute the hash code |h|'
(*PASCAL module 261*)
h:=buffer[j]; 
for k:=j+1 to j+l-1 do 
  begin h:=h+h+buffer[k]; 
  while h>=hash_prime do h:=h-hash_prime; 
  end 

MODULE: 'Basic printing...'
(*PASCAL module 262*)
procedure print_cs(p:integer); {prints a purported control sequence} 
begin if p<hash_base then {single character} 
  if p>=single_base then 
    if p=null_cs then 
      begin print_esc('csname'); print_esc('endcsname'); print_char(' '); 
      end 
    else  begin print_esc(p-single_base); 
      if cat_code(p-single_base)=letter then print_char(' '); 
      end 
  else if p<active_base then print_esc('IMPOSSIBLE.') 
(*IMPOSSIBLE*) 
  else print(p-active_base) 
else if p>=undefined_control_sequence then print_esc('IMPOSSIBLE.') 
else if (text(p)<0)or(text(p)>=str_ptr) then print_esc('NONEXISTENT.') 
(*NONEXISTENT*) 
else  begin print_esc(text(p)); 
  print_char(' '); 
  end; 
end; 

MODULE: 'Basic printing procedures'
(*PASCAL module 263*)
procedure sprint_cs(p:pointer); {prints a control sequence} 
begin if p<hash_base then 
  if p<single_base then print(p-active_base) 
  else  if p<null_cs then print_esc(p-single_base) 
    else  begin print_esc('csname'); print_esc('endcsname'); 
      end 
else print_esc(text(p)); 
end; 

MODULE: 'Put each of \TeX''s primitives into the hash table'
(*PASCAL module 265*)
primitive(' ',ex_space,0);
 
(*Single-character primitives /][\quad\.{\\\ }*) 
primitive('/',ital_corr,0);
 
(*Single-character primitives /][\quad\.{\\/}*) 
primitive('accent',accent,0);
 
(*accent_][\.{\\accent} primitive*) 
primitive('advance',advance,0);
 
(*advance_][\.{\\advance} primitive*) 
primitive('afterassignment',after_assignment,0);
 
(*after_assignment_][\.{\\afterassignment} primitive*) 
primitive('aftergroup',after_group,0);
 
(*after_group_][\.{\\aftergroup} primitive*) 
primitive('begingroup',begin_group,0);
 
(*begin_group_][\.{\\begingroup} primitive*) 
primitive('char',char_num,0);
 
(*char_][\.{\\char} primitive*) 
primitive('csname',cs_name,0);
 
(*cs_name_][\.{\\csname} primitive*) 
primitive('delimiter',delim_num,0);
 
(*delimiter_][\.{\\delimiter} primitive*) 
primitive('divide',divide,0);
 
(*divide_][\.{\\divide} primitive*) 
primitive('endcsname',end_cs_name,0);
 
(*end_cs_name_][\.{\\endcsname} primitive*) 
primitive('endgroup',end_group,0); 
(*end_group_][\.{\\endgroup} primitive*) 
text(frozen_end_group):='endgroup'; eqtb[frozen_end_group]:=eqtb[cur_val];
 
primitive('expandafter',expand_after,0);
 
(*expand_after_][\.{\\expandafter} primitive*) 
primitive('font',def_font,0);
 
(*font_][\.{\\font} primitive*) 
primitive('fontdimen',assign_font_dimen,0);
 
(*font_dimen_][\.{\\fontdimen} primitive*) 
primitive('halign',halign,0);
 
(*halign_][\.{\\halign} primitive*) 
primitive('hrule',hrule,0);
 
(*hrule_][\.{\\hrule} primitive*) 
primitive('ignorespaces',ignore_spaces,0);
 
(*ignore_spaces_][\.{\\ignorespaces} primitive*) 
primitive('insert',insert,0);
 
(*insert_][\.{\\insert} primitive*) 
primitive('mark',mark,0);
 
(*mark_][\.{\\mark} primitive*) 
primitive('mathaccent',math_accent,0);
 
(*math_accent_][\.{\\mathaccent} primitive*) 
primitive('mathchar',math_char_num,0);
 
(*math_char_][\.{\\mathchar} primitive*) 
primitive('mathchoice',math_choice,0);
 
(*math_choice_][\.{\\mathchoice} primitive*) 
primitive('multiply',multiply,0);
 
(*multiply_][\.{\\multiply} primitive*) 
primitive('noalign',no_align,0);
 
(*no_align_][\.{\\noalign} primitive*) 
primitive('noboundary',no_boundary,0);
 
(*no_boundary_][\.{\\noboundary} primitive*) 
primitive('noexpand',no_expand,0);
 
(*no_expand_][\.{\\noexpand} primitive*) 
primitive('nonscript',non_script,0);
 
(*non_script_][\.{\\nonscript} primitive*) 
primitive('omit',omit,0);
 
(*omit_][\.{\\omit} primitive*) 
primitive('parshape',set_shape,0);
 
(*par_shape_][\.{\\parshape} primitive*) 
primitive('penalty',break_penalty,0);
 
(*penalty_][\.{\\penalty} primitive*) 
primitive('prevgraf',set_prev_graf,0);
 
(*prev_graf_][\.{\\prevgraf} primitive*) 
primitive('radical',radical,0);
 
(*radical_][\.{\\radical} primitive*) 
primitive('read',read_to_cs,0);
 
(*read_][\.{\\read} primitive*) 
primitive('relax',relax,256); {cf.\ |scan_file_name|} 
(*relax_][\.{\\relax} primitive*) 
text(frozen_relax):='relax'; eqtb[frozen_relax]:=eqtb[cur_val];
 
primitive('setbox',set_box,0);
 
(*set_box_][\.{\\setbox} primitive*) 
primitive('the',the,0);
 
(*the_][\.{\\the} primitive*) 
primitive('toks',toks_register,0);
 
(*toks_][\.{\\toks} primitive*) 
primitive('vadjust',vadjust,0);
 
(*vadjust_][\.{\\vadjust} primitive*) 
primitive('valign',valign,0);
 
(*valign_][\.{\\valign} primitive*) 
primitive('vcenter',vcenter,0);
 
(*vcenter_][\.{\\vcenter} primitive*) 
primitive('vrule',vrule,0);
 
(*vrule_][\.{\\vrule} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 266*)
accent: print_esc('accent'); 
advance: print_esc('advance'); 
after_assignment: print_esc('afterassignment'); 
after_group: print_esc('aftergroup'); 
assign_font_dimen: print_esc('fontdimen'); 
begin_group: print_esc('begingroup'); 
break_penalty: print_esc('penalty'); 
char_num: print_esc('char'); 
cs_name: print_esc('csname'); 
def_font: print_esc('font'); 
delim_num: print_esc('delimiter'); 
divide: print_esc('divide'); 
end_cs_name: print_esc('endcsname'); 
end_group: print_esc('endgroup'); 
ex_space: print_esc(' '); 
expand_after: print_esc('expandafter'); 
halign: print_esc('halign'); 
hrule: print_esc('hrule'); 
ignore_spaces: print_esc('ignorespaces'); 
insert: print_esc('insert'); 
ital_corr: print_esc('/'); 
mark: print_esc('mark'); 
math_accent: print_esc('mathaccent'); 
math_char_num: print_esc('mathchar'); 
math_choice: print_esc('mathchoice'); 
multiply: print_esc('multiply'); 
no_align: print_esc('noalign'); 
no_boundary:print_esc('noboundary'); 
no_expand: print_esc('noexpand'); 
non_script: print_esc('nonscript'); 
omit: print_esc('omit'); 
radical: print_esc('radical'); 
read_to_cs: print_esc('read'); 
relax: print_esc('relax'); 
set_box: print_esc('setbox'); 
set_prev_graf: print_esc('prevgraf'); 
set_shape: print_esc('parshape'); 
the: print_esc('the'); 
toks_register: print_esc('toks'); 
vadjust: print_esc('vadjust'); 
valign: print_esc('valign'); 
vcenter: print_esc('vcenter'); 
vrule: print_esc('vrule'); 

MODULE: 'Print the font identifier for |font(p)|'
(*PASCAL module 267*)
print_esc(font_id_text(font(p))) 

MODULE: 'Types... '
(*PASCAL module 269*)
group_code=0..max_group_code; {|save_level| for a level boundary} 

MODULE: 'Glob... '
(*PASCAL module 271*)
save_stack : array[0..save_size] of memory_word; 
save_ptr : 0..save_size; {first unused entry on |save_stack|} 
max_save_stack:0..save_size; {maximum usage of save stack} 
cur_level: quarterword; {current nesting level for groups} 
cur_group: group_code; {current group type} 
cur_boundary: 0..save_size; {where the current level begins} 

MODULE: 'Set init...'
(*PASCAL module 272*)
save_ptr:=0; cur_level:=level_one; cur_group:=bottom_level; cur_boundary:=0; 
max_save_stack:=0; 

MODULE: 'Clear off...'
(*PASCAL module 282*)
loopbegin decr(save_ptr); 
  if save_type(save_ptr)=level_boundary then goto done; 
  p:=save_index(save_ptr); 
  if save_type(save_ptr)=insert_token then 
    
INSERT: 'Insert token |p| into \TeX''s input'

  else  begin if save_type(save_ptr)=restore_old_value then 
      begin l:=save_level(save_ptr); decr(save_ptr); 
      end 
    else save_stack[save_ptr]:=eqtb[undefined_control_sequence]; 
    
INSERT: 'Store \(s)|save_stack[save_ptr]| in |eqtb[p]|, unless       |eqtb[p]| holds a global value'
; 
    end; 
  end; 
done: cur_group:=save_level(save_ptr); cur_boundary:=save_index(save_ptr) 

MODULE: 'Store \(s)|save...'
(*PASCAL module 283*)
if p<int_base then 
  if eq_level(p)=level_one then 
    begin eq_destroy(save_stack[save_ptr]); {destroy the saved value} 
    stat if tracing_restores>0 then restore_trace(p,'retaining');tats;
 
    end 
  else  begin eq_destroy(eqtb[p]); {destroy the current value} 
    eqtb[p]:=save_stack[save_ptr]; {restore the saved value} 
    stat if tracing_restores>0 then restore_trace(p,'restoring');tats;
 
    end 
else if xeq_level[p]<>level_one then 
  begin eqtb[p]:=save_stack[save_ptr]; xeq_level[p]:=l; 
  stat if tracing_restores>0 then restore_trace(p,'restoring');tats;
 
  end 
else  begin 
  stat if tracing_restores>0 then restore_trace(p,'retaining');tats;
 
  end 

MODULE: 'Declare the procedure called |restore_trace|'
(*PASCAL module 284*)
stat procedure restore_trace(p:pointer;s:str_number); 
  {|eqtb[p]| has just been restored or retained} 
begin begin_diagnostic; print_char('{'); print(s); print_char(' '); 
show_eqtb(p); print_char('}'); 
end_diagnostic(false); 
end; 
tats 

MODULE: 'Search |save_stack| for equivalents that point to |p|'
(*PASCAL module 285*)
if save_ptr>0 then for q:=0 to save_ptr-1 do 
  begin if equiv_field(save_stack[q])=p then 
    begin print_nl('SAVE('); print_int(q); print_char(')'); 
    end; 
  end 

MODULE: 'Glob... '
(*PASCAL module 286*)
mag_set:integer; {if nonzero, this magnification should be used henceforth} 

MODULE: 'Set init...'
(*PASCAL module 287*)
mag_set:=0; 

MODULE: 'Check the ``constant''''...'
(*PASCAL module 290*)
if cs_token_flag+undefined_control_sequence>max_halfword then bad:=21; 

MODULE: 'Declare the procedure called |show_token_list|'
(*PASCAL module 292*)
procedure show_token_list(p,q:integer;l:integer); 
label exit; 
var m,c:integer; {pieces of a token} 
match_chr:ASCII_code; {character used in a `|match|'} 
n:ASCII_code; {the highest parameter number, as an ASCII digit} 
begin match_chr:='#'; n:='0'; tally:=0; 
while (p<>null) and (tally<l) do 
  begin if p=q then 
INSERT: 'Do magic computation'
; 
  
INSERT: 'Display token |p|, and |return| if there are problems'
; 
  p:=link(p); 
  end; 
if p<>null then print_esc('ETC.'); 
(*ETC*) 
exit: 
end; 

MODULE: 'Display token |p|...'
(*PASCAL module 293*)
if (p<hi_mem_min) or (p>mem_end) then 
  begin print_esc('CLOBBERED.'); return; 
(*CLOBBERED*) 
  end; 
if info(p)>=cs_token_flag then print_cs(info(p)-cs_token_flag) 
else  begin m:=info(p) div 256; c:=info(p) mod 256; 
  if info(p)<0 then print_esc('BAD.') 
(*BAD*) 
  else 
INSERT: 'Display the token $(|m|,|c|)$'
; 
  end 

MODULE: 'Display the token ...'
(*PASCAL module 294*)
case m of 
left_brace,right_brace,math_shift,tab_mark,sup_mark,sub_mark,spacer, 
  letter,other_char: print(c); 
mac_param: begin print(c); print(c); 
  end; 
out_param: begin print(match_chr); 
  if c<=9 then print_char(c+'0') 
  else  begin print_char('!'); return; 
    end; 
  end; 
match: begin match_chr:=c; print(c); incr(n); print_char(n); 
  if n>'9' then return; 
  end; 
end_match: print('->'); 
(*->*) 
othercases print_esc('BAD.') 
(*BAD*) 
endcases 

MODULE: 'Glob... '
(*PASCAL module 297*)
cur_cmd: eight_bits; {current command set by |get_next|} 
cur_chr: halfword; {operand of current command} 
cur_cs: pointer; {control sequence found here, zero if none found} 
cur_tok: halfword; {packed representative of |cur_cmd| and |cur_chr|} 

MODULE: 'Declare the procedure called |print_cmd_chr|'
(*PASCAL module 298*)
procedure print_cmd_chr(cmd:quarterword;chr_code:halfword); 
begin case cmd of 
left_brace: chr_cmd('begin-group character '); 
right_brace: chr_cmd('end-group character '); 
math_shift: chr_cmd('math shift character '); 
mac_param: chr_cmd('macro parameter character '); 
sup_mark: chr_cmd('superscript character '); 
sub_mark: chr_cmd('subscript character '); 
endv: print('end of alignment template'); 
spacer: chr_cmd('blank space '); 
letter: chr_cmd('the letter '); 
other_char: chr_cmd('the character '); 
(*\4*)
INSERT: 'Cases of |print_cmd_chr| for symbolic printing of primitives'

 
othercases print('[unknown command code!]') 
endcases; 
end; 

MODULE: 'Types... '
(*PASCAL module 300*)
in_state_record = record 
  state_field, index_field: quarterword; 
  start_field,loc_field, limit_field, name_field: halfword; 
  end; 

MODULE: 'Glob... '
(*PASCAL module 301*)
input_stack : array[0..stack_size] of in_state_record; 
input_ptr : 0..stack_size; {first unused location of |input_stack|} 
max_in_stack: 0..stack_size; {largest value of |input_ptr| when pushing} 
cur_input : in_state_record; 
  {the ``top'' input state, according to convention (1)} 

MODULE: 'Glob... '
(*PASCAL module 304*)
in_open : 0..max_in_open; {the number of lines in the buffer, less one} 
open_parens : 0..max_in_open; {the number of open text files} 
input_file : array[1..max_in_open] of alpha_file; 
line : integer; {current line number in the current source file} 
line_stack : array[1..max_in_open] of integer; 

MODULE: 'Glob... '
(*PASCAL module 305*)
scanner_status : normal..absorbing; {can a subfile end now?} 
warning_index : pointer; {identifier relevant to non-|normal| scanner status} 
def_ref : pointer; {reference count of token list being defined} 

MODULE: 'Declare the procedure called |runaway|'
(*PASCAL module 306*)
procedure runaway; 
var p:pointer; {head of runaway list} 
begin if scanner_status>skipping then 
  begin print_nl('Runaway '); 
(*Runaway...*) 
  case scanner_status of 
  defining: begin print('definition'); p:=def_ref; 
    end; 
  matching: begin print('argument'); p:=temp_head; 
    end; 
  aligning: begin print('preamble'); p:=hold_head; 
    end; 
  absorbing: begin print('text'); p:=def_ref; 
    end; 
  end; {there are no other cases} 
  print_char('?');print_ln; show_token_list(link(p),null,error_line-10); 
  end; 
end; 

MODULE: 'Glob... '
(*PASCAL module 308*)
param_stack:array [0..param_size] of pointer; 
  {token list pointers for parameters} 
param_ptr:0..param_size; {first unused entry in |param_stack|} 
max_param_stack:integer; 
  {largest value of |param_ptr|, will be |<=param_size+9|} 

MODULE: 'Glob... '
(*PASCAL module 309*)
align_state:integer; {group level with respect to current alignment} 

MODULE: 'Glob... '
(*PASCAL module 310*)
base_ptr:0..stack_size; {shallowest level shown by |show_context|} 

MODULE: 'Display the current context'
(*PASCAL module 312*)
begin if (base_ptr=input_ptr) or (state<>token_list) or 
   (token_type<>backed_up) or (loc<>null) then 
    {we omit backed-up token lists that have already been read} 
  begin tally:=0; {get ready to count characters} 
  old_setting:=selector; 
  if state<>token_list then 
    begin 
INSERT: 'Print location of current line'
; 
    
INSERT: 'Pseudoprint the line'
; 
    end 
  else  begin 
INSERT: 'Print type of token list'
; 
    
INSERT: 'Pseudoprint the token list'
; 
    end; 
  selector:=old_setting; {stop pseudoprinting} 
  
INSERT: 'Print two lines using the tricky pseudoprinted information'
; 
  incr(nn); 
  end; 
end 

MODULE: 'Print location of current line'
(*PASCAL module 313*)
if name<=17 then 
  if terminal_input then 
    if base_ptr=0 then print_nl('<*>') else print_nl('<insert> ') 
  else  begin print_nl('<read '); 
    if name=17 then print_char('*')else print_int(name-1); 
(**\relax*) 
    print_char('>'); 
    end 
else  begin print_nl('l.'); print_int(line); 
  end; 
print_char(' ') 

MODULE: 'Print type of token list'
(*PASCAL module 314*)
case token_type of 
parameter: print_nl('<argument> '); 
u_template,v_template: print_nl('<template> '); 
backed_up: if loc=null then print_nl('<recently read> ') 
  else print_nl('<to be read again> '); 
inserted: print_nl('<inserted text> '); 
macro: begin print_ln; print_cs(name); 
  end; 
output_text: print_nl('<output> '); 
every_par_text: print_nl('<everypar> '); 
every_math_text: print_nl('<everymath> '); 
every_display_text: print_nl('<everydisplay> '); 
every_hbox_text: print_nl('<everyhbox> '); 
every_vbox_text: print_nl('<everyvbox> '); 
every_job_text: print_nl('<everyjob> '); 
every_cr_text: print_nl('<everycr> '); 
mark_text: print_nl('<mark> '); 
write_text: print_nl('<write> '); 
othercases print_nl('?') {this should never happen} 
endcases 

MODULE: 'Local variables for formatting...'
(*PASCAL module 315*)
i:0..buf_size; {index into |buffer|} 
j:0..buf_size; {end of current line in |buffer|} 
l:0..half_error_line; {length of descriptive information on line 1} 
m:integer; {context information gathered for line 2} 
n:0..error_line; {length of line 1} 
p: integer; {starting or ending place in |trick_buf|} 
q: integer; {temporary index} 

MODULE: 'Print two lines using the tricky pseudoprinted information'
(*PASCAL module 317*)
if trick_count=1000000 then set_trick_count; 
  {|set_trick_count| must be performed} 
if tally<trick_count then m:=tally-first_count 
else m:=trick_count-first_count; {context on line 2} 
if l+first_count<=half_error_line then 
  begin p:=0; n:=l+first_count; 
  end 
else  begin print('...'); p:=l+first_count-half_error_line+3; 
  n:=half_error_line; 
  end; 
for q:=p to first_count-1 do print_char(trick_buf[q mod error_line]); 
print_ln; 
for q:=1 to n do print_char(' '); {print |n| spaces to begin line~2} 
if m+n<=error_line then p:=first_count+m else p:=first_count+(error_line-n-3); 
for q:=first_count to p-1 do print_char(trick_buf[q mod error_line]); 
if m+n>error_line then print('...') 

MODULE: 'Pseudoprint the line'
(*PASCAL module 318*)
begin_pseudoprint; 
if buffer[limit]=end_line_char then j:=limit 
else j:=limit+1; {determine the effective end of the line} 
if j>0 then for i:=start to j-1 do 
  begin if i=loc then set_trick_count; 
  print(buffer[i]); 
  end 

MODULE: 'Pseudoprint the token list'
(*PASCAL module 319*)
begin_pseudoprint; 
if token_type<macro then show_token_list(start,loc,100000) 
else show_token_list(link(start),loc,100000) {avoid reference count} 

MODULE: 'Insert token |p| into \TeX''s input'
(*PASCAL module 326*)
begin t:=cur_tok; cur_tok:=p; back_input; cur_tok:=t; 
end 

MODULE: 'Initialize the input routines'
(*PASCAL module 331*)
begin input_ptr:=0; max_in_stack:=0; 
in_open:=0; open_parens:=0; max_buf_stack:=0; 
param_ptr:=0; max_param_stack:=0; 
first:=buf_size; repeat buffer[first]:=0; decr(first); until first=0; 
scanner_status:=normal; warning_index:=null; first:=1; 
state:=new_line; start:=1; index:=0; line:=0; name:=0; 
force_eof:=false; 
align_state:=1000000;
 
if not init_terminal then goto final_end; 
limit:=last; first:=last+1; {|init_terminal| has set |loc| and |last|} 
end 

MODULE: 'Glob... '
(*PASCAL module 333*)
par_loc:pointer; {location of `\.[\\par]' in |eqtb|} 
par_token:halfword; {token representing `\.[\\par]'} 

MODULE: 'Put each...'
(*PASCAL module 334*)
primitive('par',par_end,256); {cf.\ |scan_file_name|} 
(*par_][\.{\\par} primitive*) 
par_loc:=cur_val; par_token:=cs_token_flag+par_loc; 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 335*)
par_end:print_esc('par'); 

MODULE: 'Back up an outer control sequence so that it can be reread'
(*PASCAL module 337*)
if cur_cs<>0 then 
  begin if (state=token_list)or(name<1)or(name>17) then 
    begin p:=get_avail; info(p):=cs_token_flag+cur_cs; 
    back_list(p); {prepare to read the control sequence again} 
    end; 
  cur_cmd:=spacer; cur_chr:=' '; {replace it by a space} 
  end 

MODULE: 'Tell the user what has run away...'
(*PASCAL module 338*)
begin runaway; {print a definition, argument, or preamble} 
if cur_cs=0 then print_err('File ended') 
(*File ended while scanning...*) 
else  begin cur_cs:=0; print_err('Forbidden control sequence found'); 
(*Forbidden control sequence...*) 
  end; 
print(' while scanning '); 

INSERT: 'Print either `\.{definition}'' or `\.{use}'' or `\.{preamble}'' or `\.{text}'',   and insert tokens that should lead to recovery'
; 
print(' of '); sprint_cs(warning_index); 
help4('I suspect you have forgotten a `}'', causing me')
 
('to read past where you wanted me to stop.')
 
('I''ll try to recover; but if the error is serious,')
 
('you''d better type `E'' or `X'' now and fix your file.');
 
error; 
end 

MODULE: 'Print either `\.{definition}'' or ...'
(*PASCAL module 339*)
p:=get_avail; 
case scanner_status of 
defining:begin print('definition'); info(p):=right_brace_token+'}'; 
  end; 
matching:begin print('use'); info(p):=par_token; long_state:=outer_call; 
  end; 
aligning:begin print('preamble'); info(p):=right_brace_token+'}'; q:=p; 
  p:=get_avail; link(p):=q; info(p):=cs_token_flag+frozen_cr; 
  align_state:=-1000000; 
  end; 
absorbing:begin print('text'); info(p):=right_brace_token+'}'; 
  end; 
end; {there are no other cases} 
ins_list(p) 

MODULE: 'If an alignment entry has just ended, take appropriate action'
(*PASCAL module 342*)
if cur_cmd<=car_ret then if cur_cmd>=tab_mark then if align_state=0 then 
  
INSERT: 'Insert the \(v)\<v_j> template and |goto restart|'


MODULE: 'Input from external file, |goto restart| if no input found'
(*PASCAL module 343*)
(*inner loop*) 
begin switch: if loc<=limit then {current line not yet finished} 
  begin cur_chr:=buffer[loc]; incr(loc); 
  reswitch: cur_cmd:=cat_code(cur_chr); 
  
INSERT: 'Change state if necessary, and |goto switch| if the     current character should be ignored,     or |goto reswitch| if the current character     changes to another'
; 
  end 
else  begin state:=new_line;
 
  
INSERT: 'Move to next line of file,     or |goto restart| if there is no next line,     or |return| if a \.{\\read} line has finished'
; 
  check_interrupt; 
  goto switch; 
  end; 
end 

MODULE: 'Change state if necessary...'
(*PASCAL module 344*)
case state+cur_cmd of 

INSERT: 'Cases where character is ignored'
: goto switch; 
any_state_plus(escape): 
INSERT: 'Scan a control sequence   and set |state:=skip_blanks| or |mid_line|'
; 
any_state_plus(active_char): 
INSERT: 'Process an active-character control sequence   and set |state:=mid_line|'
; 
any_state_plus(sup_mark): 
INSERT: 'If this |sup_mark| starts an expanded character   like~\.{\^\^A} or~\.{\^\^df}, then |goto reswitch|,   otherwise set |state:=mid_line|'
; 
any_state_plus(invalid_char): 
INSERT: 'Decry the invalid character and   |goto restart|'
; 
(*\4*)
INSERT: 'Handle situations involving spaces, braces, changes of state'
; 
othercases do_nothing 
endcases 

MODULE: 'Cases where character is ignored'
(*PASCAL module 345*)
any_state_plus(ignore),skip_blanks+spacer,new_line+spacer 

MODULE: 'Decry the invalid...'
(*PASCAL module 346*)
begin print_err('Text line contains an invalid character'); 
(*Text line contains...*) 
help2('A funny symbol that I can''t read has just been input.')
 
('Continue, and I''ll forget that it ever happened.');
 
deletions_allowed:=false; error; deletions_allowed:=true; 
goto restart; 
end 

MODULE: 'Handle situations involving spaces, braces, changes of state'
(*PASCAL module 347*)
mid_line+spacer:
INSERT: 'Enter |skip_blanks| state, emit a space'
; 
mid_line+car_ret:
INSERT: 'Finish line, emit a space'
; 
skip_blanks+car_ret,any_state_plus(comment): 
  
INSERT: 'Finish line, |goto switch|'
; 
new_line+car_ret:
INSERT: 'Finish line, emit a \.{\\par}'
; 
mid_line+left_brace: incr(align_state); 
skip_blanks+left_brace,new_line+left_brace: begin 
  state:=mid_line; incr(align_state); 
  end; 
mid_line+right_brace: decr(align_state); 
skip_blanks+right_brace,new_line+right_brace: begin 
  state:=mid_line; decr(align_state); 
  end; 
add_delims_to(skip_blanks),add_delims_to(new_line): state:=mid_line; 

MODULE: 'Finish line, emit a space'
(*PASCAL module 348*)
begin loc:=limit+1; cur_cmd:=spacer; cur_chr:=' '; 
end 

MODULE: 'Enter |skip_blanks| state, emit a space'
(*PASCAL module 349*)
begin state:=skip_blanks; cur_chr:=' '; 
end 

MODULE: 'Finish line, |goto switch|'
(*PASCAL module 350*)
begin loc:=limit+1; goto switch; 
end 

MODULE: 'Finish line, emit a \.{\\par}'
(*PASCAL module 351*)
begin loc:=limit+1; cur_cs:=par_loc; cur_cmd:=eq_type(cur_cs); 
cur_chr:=equiv(cur_cs); 
if cur_cmd>=outer_call then check_outer_validity; 
end 

MODULE: 'If this |sup_mark| starts an expanded character...'
(*PASCAL module 352*)
begin if cur_chr=buffer[loc] then if loc<limit then 
  begin c:=buffer[loc+1]; if c<128 then {yes we have an expanded char} 
    begin loc:=loc+2; 
    if is_hex(c) then if loc<=limit then 
      begin cc:=buffer[loc]; if is_hex(cc) then 
        begin incr(loc); hex_to_cur_chr; goto reswitch; 
        end; 
      end; 
    if c<64 then cur_chr:=c+64 else cur_chr:=c-64; 
    goto reswitch; 
    end; 
  end; 
state:=mid_line; 
end 

MODULE: 'Process an active-character...'
(*PASCAL module 353*)
begin cur_cs:=cur_chr+active_base; 
cur_cmd:=eq_type(cur_cs); cur_chr:=equiv(cur_cs); state:=mid_line; 
if cur_cmd>=outer_call then check_outer_validity; 
end 

MODULE: 'Scan a control...'
(*PASCAL module 354*)
begin if loc>limit then cur_cs:=null_cs {|state| is irrelevant in this case} 
else  begin start_cs: k:=loc; cur_chr:=buffer[k]; cat:=cat_code(cur_chr); 
  incr(k); 
  if cat=letter then state:=skip_blanks 
  else if cat=spacer then state:=skip_blanks 
  else state:=mid_line; 
  if (cat=letter)and(k<=limit) then 
    
INSERT: 'Scan ahead in the buffer until finding a nonletter;     if an expanded code is encountered, reduce it     and |goto start_cs|; otherwise if a multiletter control     sequence is found, adjust |cur_cs| and |loc|, and     |goto found|'

  else 
INSERT: 'If an expanded code is present, reduce it and |goto start_cs|'
; 
  cur_cs:=single_base+buffer[loc]; incr(loc); 
  end; 
found: cur_cmd:=eq_type(cur_cs); cur_chr:=equiv(cur_cs); 
if cur_cmd>=outer_call then check_outer_validity; 
end 

MODULE: 'If an expanded...'
(*PASCAL module 355*)
begin if buffer[k]=cur_chr then if cat=sup_mark then if k<limit then 
  begin c:=buffer[k+1]; if c<128 then {yes, one is indeed present} 
    begin d:=2; 
    if is_hex(c) then if k+2<=limit then 
      begin cc:=buffer[k+2]; if is_hex(cc) then incr(d); 
      end; 
    if d>2 then 
      begin hex_to_cur_chr; buffer[k-1]:=cur_chr; 
      end 
    else if c<64 then buffer[k-1]:=c+64 
    else buffer[k-1]:=c-64; 
    limit:=limit-d; first:=first-d; 
    while k<=limit do 
      begin buffer[k]:=buffer[k+d]; incr(k); 
      end; 
    goto start_cs; 
    end; 
  end; 
end 

MODULE: 'Scan ahead in the buffer...'
(*PASCAL module 356*)
begin repeat cur_chr:=buffer[k]; cat:=cat_code(cur_chr); incr(k); 
until (cat<>letter)or(k>limit); 

INSERT: 'If an expanded...'
; 
if cat<>letter then decr(k); 
  {now |k| points to first nonletter} 
if k>loc+1 then {multiletter control sequence has been scanned} 
  begin cur_cs:=id_lookup(loc,k-loc); loc:=k; goto found; 
  end; 
end 

MODULE: 'Input from token list, |goto restart| if end of list or   if a parameter needs to be expanded'
(*PASCAL module 357*)
if loc<>null then {list not exhausted} 
(*inner loop*) 
  begin t:=info(loc); loc:=link(loc); {move to next} 
  if t>=cs_token_flag then {a control sequence token} 
    begin cur_cs:=t-cs_token_flag; 
    cur_cmd:=eq_type(cur_cs); cur_chr:=equiv(cur_cs); 
    if cur_cmd>=outer_call then 
      if cur_cmd=dont_expand then 
        
INSERT: 'Get the next token, suppressing expansion'

      else check_outer_validity; 
    end 
  else  begin cur_cmd:=t div 256; cur_chr:=t mod 256; 
    case cur_cmd of 
    left_brace: incr(align_state); 
    right_brace: decr(align_state); 
    out_param: 
INSERT: 'Insert macro parameter and |goto restart|'
; 
    othercases do_nothing 
    endcases; 
    end; 
  end 
else  begin {we are done with this token list} 
  end_token_list; goto restart; {resume previous level} 
  end 

MODULE: 'Get the next token, suppressing expansion'
(*PASCAL module 358*)
begin cur_cs:=info(loc)-cs_token_flag; loc:=null;
 
cur_cmd:=eq_type(cur_cs); cur_chr:=equiv(cur_cs); 
if cur_cmd>max_command then 
  begin cur_cmd:=relax; cur_chr:=no_expand_flag; 
  end; 
end 

MODULE: 'Insert macro parameter...'
(*PASCAL module 359*)
begin begin_token_list(param_stack[param_start+cur_chr-1],parameter); 
goto restart; 
end 

MODULE: 'Move to next line of file, or |goto restart|...'
(*PASCAL module 360*)
if name>17 then 
INSERT: 'Read next line of file into |buffer|, or   |goto restart| if the file has ended'

else  begin if not terminal_input then {\.[\\read] line has ended} 
    begin cur_cmd:=0; cur_chr:=0; return; 
    end; 
  if input_ptr>0 then {text was inserted during error recovery} 
    begin end_file_reading; goto restart; {resume previous level} 
    end; 
  if selector<log_only then open_log_file; 
  if interaction>nonstop_mode then 
    begin if end_line_char_inactive then incr(limit); 
    if limit=start then {previous line was empty} 
      print_nl('(Please type a command or say `\end'')'); 
(*Please type...*) 
    print_ln; first:=start; 
    prompt_input('*'); {input on-line into |buffer|} 
(**\relax*) 
    limit:=last; 
    if end_line_char_inactive then decr(limit) 
    else  buffer[limit]:=end_line_char; 
    first:=limit+1; 
    loc:=start; 
    end 
  else fatal_error('*** (job aborted, no legal \end found)'); 
(*job aborted*) 
    {nonstop mode, which is intended for overnight batch processing, 
    never waits for on-line input} 
  end 

MODULE: 'Glob... '
(*PASCAL module 361*)
force_eof:boolean; {should the next \.[\\input] be aborted early?} 

MODULE: 'Read next line of file into |buffer|, or   |goto restart| if the file has ended'
(*PASCAL module 362*)
begin incr(line); first:=start; 
if not force_eof then 
  begin if input_ln(cur_file,true) then {not end of file} 
    firm_up_the_line {this sets |limit|} 
  else force_eof:=true; 
  end; 
if force_eof then 
  begin print_char(')'); decr(open_parens); 
  update_terminal; {show user that file has been read} 
  force_eof:=false; 
  end_file_reading; {resume previous level} 
  check_outer_validity; goto restart; 
  end; 
if end_line_char_inactive then decr(limit) 
else  buffer[limit]:=end_line_char; 
first:=limit+1; loc:=start; {ready to read} 
end 

MODULE: 'Expand a nonmacro'
(*PASCAL module 367*)
begin if tracing_commands>1 then show_cur_cmd_chr; 
case cur_cmd of 
top_bot_mark:
INSERT: 'Insert the \(a)appropriate mark text into the scanner'
; 
expand_after:
INSERT: 'Expand the token after the next token'
; 
no_expand:
INSERT: 'Suppress expansion of the next token'
; 
cs_name:
INSERT: 'Manufacture a control sequence name'
; 
convert:conv_toks; {this procedure is discussed in Part 27 below} 
the:ins_the_toks; {this procedure is discussed in Part 27 below} 
if_test:conditional; {this procedure is discussed in Part 28 below} 
fi_or_else:
INSERT: 'Terminate the current conditional and skip to \.{\\fi}'
; 
input:
INSERT: 'Initiate or terminate input from a file'
; 
othercases 
INSERT: 'Complain about an undefined macro'

endcases; 
end 

MODULE: 'Expand the token after...'
(*PASCAL module 368*)
begin get_token; t:=cur_tok; get_token; 
if cur_cmd>max_command then expandelse back_input; 
cur_tok:=t; back_input; 
end 

MODULE: 'Suppress expansion...'
(*PASCAL module 369*)
begin save_scanner_status:=scanner_status; scanner_status:=normal; 
get_token; scanner_status:=save_scanner_status; t:=cur_tok; 
back_input; {now |start| and |loc| point to the backed-up token |t|} 
if t>=cs_token_flag then 
  begin p:=get_avail; info(p):=cs_token_flag+frozen_dont_expand; 
  link(p):=loc; start:=p; loc:=p; 
  end; 
end 

MODULE: 'Complain about an undefined macro'
(*PASCAL module 370*)
begin print_err('Undefined control sequence'); 
(*Undefined control sequence*) 
help5('The control sequence at the end of the top line')
 
('of your error message was never \def''ed. If you have')
 
('misspelled it (e.g., `\hobx''), type `I'' and the correct')
 
('spelling (e.g., `I\hbox''). Otherwise just continue,')
 
('and I''ll forget about whatever was undefined.'); 
error; 
end 

MODULE: 'Manufacture a control...'
(*PASCAL module 372*)
begin r:=get_avail; p:=r; {head of the list of characters} 
repeat get_x_token; 
if cur_cs=0 then store_new_token(cur_tok); 
until cur_cs<>0; 
if cur_cmd<>end_cs_name then 
INSERT: 'Complain about missing \.{\\endcsname}'
; 

INSERT: 'Look up the characters of list |r| in the hash table, and set |cur_cs|'
; 
flush_list(r); 
if eq_type(cur_cs)=undefined_cs then 
  begin eq_define(cur_cs,relax,256); {N.B.: The |save_stack| might change} 
  end; {the control sequence will now match `\.[\\relax]'} 
cur_tok:=cur_cs+cs_token_flag; back_input; 
end 

MODULE: 'Complain about missing \.{\\endcsname}'
(*PASCAL module 373*)
begin print_err('Missing '); print_esc('endcsname'); print(' inserted'); 
(*Missing \\endcsname...*) 
help2('The control sequence marked <to be read again> should')
 
  ('not appear between \csname and \endcsname.'); 
back_error; 
end 

MODULE: 'Look up the characters of list |r| in the hash table...'
(*PASCAL module 374*)
j:=first; p:=link(r); 
while p<>null do 
  begin if j>=max_buf_stack then 
    begin max_buf_stack:=j+1; 
    if max_buf_stack=buf_size then 
      overflow('buffer size',buf_size); 
(*TeX capacity exceeded buffer size][\quad buffer size*) 
    end; 
  buffer[j]:=info(p) mod 256; incr(j); p:=link(p); 
  end; 
if j>first+1 then 
  begin no_new_control_sequence:=false; cur_cs:=id_lookup(first,j-first); 
  no_new_control_sequence:=true; 
  end 
else if j=first then cur_cs:=null_cs {the list is empty} 
else cur_cs:=single_base+buffer[first] {the list has length one} 

MODULE: 'Insert a token containing |frozen_endv|'
(*PASCAL module 375*)
begin cur_tok:=cs_token_flag+frozen_endv; back_input; 
end 

MODULE: 'Put each...'
(*PASCAL module 376*)
primitive('input',input,0);
 
(*input_][\.{\\input} primitive*) 
primitive('endinput',input,1);
 
(*end_input_][\.{\\endinput} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 377*)
input: if chr_code=0 then print_esc('input')else print_esc('endinput'); 

MODULE: 'Initiate or terminate input...'
(*PASCAL module 378*)
if cur_chr>0 then force_eof:=true 
else if name_in_progress then insert_relax 
else start_input 

MODULE: 'Declare the procedure called |insert_relax|'
(*PASCAL module 379*)
procedure insert_relax; 
begin cur_tok:=cs_token_flag+cur_cs; back_input; 
cur_tok:=cs_token_flag+frozen_relax; back_input; token_type:=inserted; 
end; 

MODULE: 'Glob... '
(*PASCAL module 382*)
cur_mark:array[top_mark_code..split_bot_mark_code] of pointer; 
  {token lists for marks} 

MODULE: 'Set init...'
(*PASCAL module 383*)
top_mark:=null; first_mark:=null; bot_mark:=null; 
split_first_mark:=null; split_bot_mark:=null; 

MODULE: 'Put each...'
(*PASCAL module 384*)
primitive('topmark',top_bot_mark,top_mark_code); 
(*top_mark_][\.{\\topmark} primitive*) 
primitive('firstmark',top_bot_mark,first_mark_code); 
(*first_mark_][\.{\\firstmark} primitive*) 
primitive('botmark',top_bot_mark,bot_mark_code); 
(*bot_mark_][\.{\\botmark} primitive*) 
primitive('splitfirstmark',top_bot_mark,split_first_mark_code); 
(*split_first_mark_][\.{\\splitfirstmark} primitive*) 
primitive('splitbotmark',top_bot_mark,split_bot_mark_code); 
(*split_bot_mark_][\.{\\splitbotmark} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 385*)
top_bot_mark: case chr_code of 
  first_mark_code: print_esc('firstmark'); 
  bot_mark_code: print_esc('botmark'); 
  split_first_mark_code: print_esc('splitfirstmark'); 
  split_bot_mark_code: print_esc('splitbotmark'); 
  othercases print_esc('topmark') 
  endcases; 

MODULE: 'Insert the \(a)appropriate mark text into the scanner'
(*PASCAL module 386*)
begin if cur_mark[cur_chr]<>null then 
  begin_token_list(cur_mark[cur_chr],mark_text); 
end 

MODULE: 'Glob... '
(*PASCAL module 387*)
long_state:call..long_outer_call; {governs the acceptance of \.[\\par]} 

MODULE: 'Glob... '
(*PASCAL module 388*)
pstack:array[0..8] of pointer; {arguments supplied to a macro} 

MODULE: 'Declare the procedure called |macro_call|'
(*PASCAL module 389*)
procedure macro_call; {invokes a user-defined control sequence} 
label exit, continue, done, done1, found; 
var r:pointer; {current node in the macro's token list} 
p:pointer; {current node in parameter token list being built} 
q:pointer; {new node being put into the token list} 
s:pointer; {backup pointer for parameter matching} 
t:pointer; {cycle pointer for backup recovery} 
u,v:pointer; {auxiliary pointers for backup recovery} 
rbrace_ptr:pointer; {one step before the last |right_brace| token} 
n:small_number; {the number of parameters scanned} 
unbalance:halfword; {unmatched left braces in current parameter} 
m:halfword; {the number of tokens or groups (usually)} 
ref_count:pointer; {start of the token list} 
save_scanner_status:small_number; {|scanner_status| upon entry} 
save_warning_index:pointer; {|warning_index| upon entry} 
match_chr:ASCII_code; {character used in parameter} 
begin save_scanner_status:=scanner_status; save_warning_index:=warning_index; 
warning_index:=cur_cs; ref_count:=cur_chr; r:=link(ref_count); n:=0; 
if tracing_macros>0 then 
INSERT: 'Show the text of the macro being expanded'
; 
if info(r)<>end_match_token then 
  
INSERT: 'Scan the parameters and make |link(r)| point to the macro body; but     |return| if an illegal \.{\\par} is detected'
; 

INSERT: 'Feed the macro body and its parameters to the scanner'
; 
exit:scanner_status:=save_scanner_status; warning_index:=save_warning_index; 
end; 

MODULE: 'Feed the macro body and its parameters to the scanner'
(*PASCAL module 390*)
while (state=token_list)and(loc=null)and(token_type<>v_template) do 
  end_token_list; {conserve stack space} 
begin_token_list(ref_count,macro); name:=warning_index; loc:=link(r); 
if n>0 then 
  begin if param_ptr+n>max_param_stack then 
    begin max_param_stack:=param_ptr+n; 
    if max_param_stack>param_size then 
      overflow('parameter stack size',param_size); 
(*TeX capacity exceeded parameter stack size][\quad parameter stack size*) 
    end; 
  for m:=0 to n-1 do param_stack[param_ptr+m]:=pstack[m]; 
  param_ptr:=param_ptr+n; 
  end 

MODULE: 'Scan the parameters and make |link(r)| point to the macro body...'
(*PASCAL module 391*)
begin scanner_status:=matching; unbalance:=0; 
long_state:=eq_type(cur_cs); 
if long_state>=outer_call then long_state:=long_state-2; 
repeat link(temp_head):=null; 
if (info(r)>match_token+255)or(info(r)<match_token) then s:=null 
else  begin match_chr:=info(r)-match_token; s:=link(r); r:=s; 
  p:=temp_head; m:=0; 
  end; 

INSERT: 'Scan a parameter until its delimiter string has been found; or, if |s=null|,   simply scan the delimiter string'
;
 
{now |info(r)| is a token whose command code is either |match| or |end_match|} 
until info(r)=end_match_token; 
end 

MODULE: 'Scan a parameter until its delimiter string has been found; or, ...'
(*PASCAL module 392*)
continue: get_token; {set |cur_tok| to the next token of input} 
if cur_tok=info(r) then 
  
INSERT: 'Advance \(r)|r|; |goto found| if the parameter delimiter has been     fully matched, otherwise |goto continue|'
; 

INSERT: 'Contribute the recently matched tokens to the current parameter, and   |goto continue| if a partial match is still in effect;   but abort if |s=null|'
; 
if cur_tok=par_token then if long_state<>long_call then 
  
INSERT: 'Report a runaway argument and abort'
; 
if cur_tok<right_brace_limit then 
  if cur_tok<left_brace_limit then 
    
INSERT: 'Contribute an entire group to the current parameter'

  else 
INSERT: 'Report an extra right brace and |goto continue|'

else 
INSERT: 'Store the current token, but |goto continue| if it is    a blank space that would become an undelimited parameter'
; 
incr(m); 
if info(r)>end_match_token then goto continue; 
if info(r)<match_token then goto continue; 
found: if s<>null then 
INSERT: 'Tidy up the parameter just scanned, and tuck it away'


MODULE: 'Store the current token, but |goto continue| if it is...'
(*PASCAL module 393*)
begin if cur_tok=space_token then 
  if info(r)<=end_match_token then 
    if info(r)>=match_token then goto continue; 
store_new_token(cur_tok); 
end 

MODULE: 'Advance \(r)|r|; |goto found| if the parameter delimiter has been fully...'
(*PASCAL module 394*)
begin r:=link(r); 
if (info(r)>=match_token)and(info(r)<=end_match_token) then 
  begin if cur_tok<left_brace_limit then decr(align_state); 
  goto found; 
  end 
else goto continue; 
end 

MODULE: 'Report an extra right brace and |goto continue|'
(*PASCAL module 395*)
begin back_input; print_err('Argument of '); sprint_cs(warning_index); 
(*Argument of \\x has...*) 
print(' has an extra }'); 
help6('I''ve run across a `}'' that doesn''t seem to match anything.')
 
  ('For example, `\def\a#1{...}'' and `\a}'' would produce')
 
  ('this error. If you simply proceed now, the `\par'' that')
 
  ('I''ve just inserted will cause me to report a runaway')
 
  ('argument that might be the root of the problem. But if')
 
  ('your `}'' was spurious, just type `2'' and it will go away.'); 
incr(align_state); long_state:=call; cur_tok:=par_token; ins_error; 
goto continue; 
end {a white lie; the \.[\\par] won't always trigger a runaway} 

MODULE: 'Report a runaway argument and abort'
(*PASCAL module 396*)
begin if long_state=call then 
  begin runaway; print_err('Paragraph ended before '); 
(*Paragraph ended before...*) 
  sprint_cs(warning_index); print(' was complete'); 
  help3('I suspect you''ve forgotten a `}'', causing me to apply this')
 
    ('control sequence to too much text. How can we recover?')
 
    ('My plan is to forget the whole thing and hope for the best.'); 
  back_error; 
  end; 
pstack[n]:=link(temp_head); align_state:=align_state-unbalance; 
for m:=0 to n do flush_list(pstack[m]); 
return; 
end 

MODULE: 'Contribute the recently matched tokens to the current parameter...'
(*PASCAL module 397*)
if s<>r then 
  if s=null then 
INSERT: 'Report an improper use of the macro and abort'

  else  begin t:=s; 
    repeat store_new_token(info(t)); incr(m); u:=link(t); v:=s; 
    loop  begin if u=r then 
        if cur_tok<>info(v) then goto done 
        else  begin r:=link(v); goto continue; 
          end; 
      if info(u)<>info(v) then goto done; 
      u:=link(u); v:=link(v); 
      end; 
    done: t:=link(t); 
    until t=r; 
    r:=s; {at this point, no tokens are recently matched} 
    end 

MODULE: 'Report an improper use...'
(*PASCAL module 398*)
begin print_err('Use of '); sprint_cs(warning_index); 
(*Use of x doesn''t match...*) 
print(' doesn''t match its definition'); 
help4('If you say, e.g., `\def\a1{...}'', then you must always')
 
  ('put `1'' after `\a'', since control sequence names are')
 
  ('made up of letters only. The macro here has not been')
 
  ('followed by the required stuff, so I''m ignoring it.'); 
error; return; 
end 

MODULE: 'Contribute an entire group to the current parameter'
(*PASCAL module 399*)
begin unbalance:=1; 
(*inner loop*) 
loop  begin fast_store_new_token(cur_tok); get_token; 
  if cur_tok=par_token then if long_state<>long_call then 
    
INSERT: 'Report a runaway argument and abort'
; 
  if cur_tok<right_brace_limit then 
    if cur_tok<left_brace_limit then incr(unbalance) 
    else  begin decr(unbalance); 
      if unbalance=0 then goto done1; 
      end; 
  end; 
done1: rbrace_ptr:=p; store_new_token(cur_tok); 
end 

MODULE: 'Tidy up the parameter just scanned, and tuck it away'
(*PASCAL module 400*)
begin if (m=1)and(info(p)<right_brace_limit)and(p<>temp_head) then 
  begin link(rbrace_ptr):=null; free_avail(p); 
  p:=link(temp_head); pstack[n]:=link(p); free_avail(p); 
  end 
else pstack[n]:=link(temp_head); 
incr(n); 
if tracing_macros>0 then 
  begin begin_diagnostic; print_nl(match_chr); print_int(n); 
  print('<-'); show_token_list(pstack[n-1],null,1000); 
  end_diagnostic(false); 
  end; 
end 

MODULE: 'Show the text of the macro being expanded'
(*PASCAL module 401*)
begin begin_diagnostic; print_ln; print_cs(warning_index); 
token_show(ref_count); end_diagnostic(false); 
end 

MODULE: 'Get the next non-blank non-relax non-call token'
(*PASCAL module 404*)
repeat get_x_token; 
until (cur_cmd<>spacer)and(cur_cmd<>relax) 

MODULE: 'Get the next non-blank non-call token'
(*PASCAL module 406*)
repeat get_x_token; 
until cur_cmd<>spacer 

MODULE: 'Glob... '
(*PASCAL module 410*)
cur_val:integer; {value returned by numeric scanners} 
cur_val_level:int_val..tok_val; {the ``level'' of this value} 

MODULE: 'Put each...'
(*PASCAL module 411*)
primitive('count',register,int_val); 
(*count_][\.{\\count} primitive*) 
primitive('dimen',register,dimen_val); 
(*dimen_][\.{\\dimen} primitive*) 
primitive('skip',register,glue_val); 
(*skip_][\.{\\skip} primitive*) 
primitive('muskip',register,mu_val); 
(*mu_skip_][\.{\\muskip} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 412*)
register: if chr_code=int_val then print_esc('count') 
  else if chr_code=dimen_val then print_esc('dimen') 
  else if chr_code=glue_val then print_esc('skip') 
  else print_esc('muskip'); 

MODULE: 'Fetch a character code from some table'
(*PASCAL module 414*)
begin scan_char_num; 
if m=math_code_base then scanned_result(ho(math_code(cur_val)))(int_val) 
else if m<math_code_base then scanned_result(equiv(m+cur_val))(int_val) 
else scanned_result(eqtb[m+cur_val].int)(int_val); 
end 

MODULE: 'Fetch a token list...'
(*PASCAL module 415*)
if level<>tok_val then 
  begin print_err('Missing number, treated as zero'); 
(*Missing number...*) 
  help3('A number should have been here; I inserted `0''.')
 
    ('(If you can''t figure out why I needed to see a number,')
 
    ('look up `weird error'' in the index to The TeXbook.)'); 
(*TeXbook][\sl The \TeX book*) 
  back_error; scanned_result(0)(dimen_val); 
  end 
else if cur_cmd<=assign_toks then 
  begin if cur_cmd<assign_toks then {|cur_cmd=toks_register|} 
    begin scan_eight_bit_int; m:=toks_base+cur_val; 
    end; 
  scanned_result(equiv(m))(tok_val); 
  end 
else  begin back_input; scan_font_ident; 
  scanned_result(font_id_base+cur_val)(ident_val); 
  end 

MODULE: 'Put each...'
(*PASCAL module 416*)
primitive('spacefactor',set_aux,hmode); 
(*space_factor_][\.{\\spacefactor} primitive*) 
primitive('prevdepth',set_aux,vmode);
 
(*prev_depth_][\.{\\prevdepth} primitive*) 
primitive('deadcycles',set_page_int,0); 
(*dead_cycles_][\.{\\deadcycles} primitive*) 
primitive('insertpenalties',set_page_int,1); 
(*insert_penalties_][\.{\\insertpenalties} primitive*) 
primitive('wd',set_box_dimen,width_offset); 
(*wd_][\.{\\wd} primitive*) 
primitive('ht',set_box_dimen,height_offset); 
(*ht_][\.{\\ht} primitive*) 
primitive('dp',set_box_dimen,depth_offset); 
(*dp_][\.{\\dp} primitive*) 
primitive('lastpenalty',last_item,int_val); 
(*last_penalty_][\.{\\lastpenalty} primitive*) 
primitive('lastkern',last_item,dimen_val); 
(*last_kern_][\.{\\lastkern} primitive*) 
primitive('lastskip',last_item,glue_val); 
(*last_skip_][\.{\\lastskip} primitive*) 
primitive('inputlineno',last_item,input_line_no_code); 
(*input_line_no_][\.{\\inputlineno} primitive*) 
primitive('badness',last_item,badness_code); 
(*badness_][\.{\\badness} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 417*)
set_aux: if chr_code=vmode then print_esc('prevdepth') 
else print_esc('spacefactor'); 
set_page_int: if chr_code=0 then print_esc('deadcycles') 
else print_esc('insertpenalties'); 
set_box_dimen: if chr_code=width_offset then print_esc('wd') 
else if chr_code=height_offset then print_esc('ht') 
else print_esc('dp'); 
last_item: case chr_code of 
  int_val: print_esc('lastpenalty'); 
  dimen_val: print_esc('lastkern'); 
  glue_val: print_esc('lastskip'); 
  input_line_no_code: print_esc('inputlineno'); 
  othercases print_esc('badness') 
  endcases; 

MODULE: 'Fetch the |space_factor| or the |prev_depth|'
(*PASCAL module 418*)
if abs(mode)<>m then 
  begin print_err('Improper '); print_cmd_chr(set_aux,m); 
(*Improper \\spacefactor*) 
(*Improper \\prevdepth*) 
  help4('You can refer to \spacefactor only in horizontal mode;')
 
    ('you can refer to \prevdepth only in vertical mode; and')
 
    ('neither of these is meaningful inside \write. So')
 
    ('I''m forgetting what you said and using zero instead.'); 
  error; 
  if level<>tok_val then scanned_result(0)(dimen_val) 
  else scanned_result(0)(int_val); 
  end 
else if m=vmode then scanned_result(prev_depth)(dimen_val) 
else scanned_result(space_factor)(int_val) 

MODULE: 'Fetch the |dead_cycles| or the |insert_penalties|'
(*PASCAL module 419*)
begin if m=0 then cur_val:=dead_cycleselse cur_val:=insert_penalties; 
cur_val_level:=int_val; 
end 

MODULE: 'Fetch a box dimension'
(*PASCAL module 420*)
begin scan_eight_bit_int; 
if box(cur_val)=null then cur_val:=0 else cur_val:=mem[box(cur_val)+m].sc; 
cur_val_level:=dimen_val; 
end 

MODULE: 'Fetch something on the |page_so_far|'
(*PASCAL module 421*)
begin if (page_contents=empty) and (not output_active) then 
  if m=0 then cur_val:=max_dimenelse cur_val:=0 
else cur_val:=page_so_far[m]; 
cur_val_level:=dimen_val; 
end 

MODULE: 'Fetch the |prev_graf|'
(*PASCAL module 422*)
if mode=0 then scanned_result(0)(int_val) {|prev_graf=0| within \.[\\write]} 
else begin nest[nest_ptr]:=cur_list; p:=nest_ptr; 
  while abs(nest[p].mode_field)<>vmode do decr(p); 
  scanned_result(nest[p].pg_field)(int_val); 
  end 

MODULE: 'Fetch the |par_shape| size'
(*PASCAL module 423*)
begin if par_shape_ptr=null then cur_val:=0 
else cur_val:=info(par_shape_ptr); 
cur_val_level:=int_val; 
end 

MODULE: 'Fetch an item in the current node...'
(*PASCAL module 424*)
if cur_chr>glue_val then 
  begin if cur_chr=input_line_no_code then cur_val:=line 
  else cur_val:=last_badness; {|cur_chr=badness_code|} 
  cur_val_level:=int_val; 
  end 
else begin if cur_chr=glue_val then cur_val:=zero_glueelse cur_val:=0; 
  cur_val_level:=cur_chr; 
  if not is_char_node(tail)and(mode<>0) then 
    case cur_chr of 
    int_val: if type(tail)=penalty_node then cur_val:=penalty(tail); 
    dimen_val: if type(tail)=kern_node then cur_val:=width(tail); 
    glue_val: if type(tail)=glue_node then 
      begin cur_val:=glue_ptr(tail); 
      if subtype(tail)=mu_glue then cur_val_level:=mu_val; 
      end; 
    end {there are no other cases} 
  else if (mode=vmode)and(tail=head) then 
    case cur_chr of 
    int_val: cur_val:=last_penalty; 
    dimen_val: cur_val:=last_kern; 
    glue_val: if last_glue<>max_halfword then cur_val:=last_glue; 
    end; {there are no other cases} 
  end 

MODULE: 'Fetch a font dimension'
(*PASCAL module 425*)
begin find_font_dimen(false); font_info[fmem_ptr].sc:=0; 
scanned_result(font_info[cur_val].sc)(dimen_val); 
end 

MODULE: 'Fetch a font integer'
(*PASCAL module 426*)
begin scan_font_ident; 
if m=0 then scanned_result(hyphen_char[cur_val])(int_val) 
else scanned_result(skew_char[cur_val])(int_val); 
end 

MODULE: 'Fetch a register'
(*PASCAL module 427*)
begin scan_eight_bit_int; 
case m of 
int_val:cur_val:=count(cur_val); 
dimen_val:cur_val:=dimen(cur_val); 
glue_val: cur_val:=skip(cur_val); 
mu_val: cur_val:=mu_skip(cur_val); 
end; {there are no other cases} 
cur_val_level:=m; 
end 

MODULE: 'Complain that \.{\\the} can''t do this; give zero result'
(*PASCAL module 428*)
begin print_err('You can''t use `'); print_cmd_chr(cur_cmd,cur_chr); 
(*You can''t use x after ...*) 
print(''' after '); print_esc('the'); 
help1('I''m forgetting what you said and using zero instead.'); 
error; 
if level<>tok_val then scanned_result(0)(dimen_val) 
else scanned_result(0)(int_val); 
end 

MODULE: 'Convert \(c)|cur_val| to a lower level'
(*PASCAL module 429*)
begin if cur_val_level=glue_val then cur_val:=width(cur_val) 
else if cur_val_level=mu_val then mu_error; 
decr(cur_val_level); 
end 

MODULE: 'Fix the reference count, if any, ...'
(*PASCAL module 430*)
if negative then 
  if cur_val_level>=glue_val then 
    begin cur_val:=new_spec(cur_val); 
    
INSERT: 'Negate all three glue components of |cur_val|'
; 
    end 
  else negate(cur_val) 
else if (cur_val_level>=glue_val)and(cur_val_level<=mu_val) then 
  add_glue_ref(cur_val) 

MODULE: 'Negate all three...'
(*PASCAL module 431*)
begin negate(width(cur_val)); 
negate(stretch(cur_val)); 
negate(shrink(cur_val)); 
end 

MODULE: 'Declare procedures that scan restricted classes of integers'
(*PASCAL module 433*)
procedure scan_eight_bit_int; 
begin scan_int; 
if (cur_val<0)or(cur_val>255) then 
  begin print_err('Bad register code'); 
(*Bad register code*) 
  help2('A register number must be between 0 and 255.')
 
    ('I changed this one to zero.'); int_error(cur_val); cur_val:=0; 
  end; 
end; 

MODULE: 'Declare procedures that scan restricted classes of integers'
(*PASCAL module 434*)
procedure scan_char_num; 
begin scan_int; 
if (cur_val<0)or(cur_val>255) then 
  begin print_err('Bad character code'); 
(*Bad character code*) 
  help2('A character number must be between 0 and 255.')
 
    ('I changed this one to zero.'); int_error(cur_val); cur_val:=0; 
  end; 
end; 

MODULE: 'Declare procedures that scan restricted classes of integers'
(*PASCAL module 435*)
procedure scan_four_bit_int; 
begin scan_int; 
if (cur_val<0)or(cur_val>15) then 
  begin print_err('Bad number'); 
(*Bad number*) 
  help2('Since I expected to read a number between 0 and 15,')
 
    ('I changed this one to zero.'); int_error(cur_val); cur_val:=0; 
  end; 
end; 

MODULE: 'Declare procedures that scan restricted classes of integers'
(*PASCAL module 436*)
procedure scan_fifteen_bit_int; 
begin scan_int; 
if (cur_val<0)or(cur_val>32767) then 
  begin print_err('Bad mathchar'); 
(*Bad mathchar*) 
  help2('A mathchar number must be between 0 and 32767.')
 
    ('I changed this one to zero.'); int_error(cur_val); cur_val:=0; 
  end; 
end; 

MODULE: 'Declare procedures that scan restricted classes of integers'
(*PASCAL module 437*)
procedure scan_twenty_seven_bit_int; 
begin scan_int; 
if (cur_val<0)or(cur_val>134217727) then 
  begin print_err('Bad delimiter code'); 
(*Bad delimiter code*) 
  help2('A numeric delimiter code must be between 0 and 2^{27}-1.')
 
    ('I changed this one to zero.'); int_error(cur_val); cur_val:=0; 
  end; 
end; 

MODULE: 'Glob... '
(*PASCAL module 438*)
radix:small_number; {|scan_int| sets this to 8, 10, 16, or zero} 

MODULE: 'Set init...'
(*PASCAL module 439*)
cur_val:=0; cur_val_level:=int_val; radix:=0; cur_order:=normal; 

MODULE: 'Get the next non-blank non-sign token...'
(*PASCAL module 441*)
negative:=false; 
repeat 
INSERT: 'Get the next non-blank non-call token'
; 
if cur_tok=other_token+'-' then 
  begin negative := not negative; cur_tok:=other_token+'+'; 
  end; 
until cur_tok<>other_token+'+' 

MODULE: 'Scan an alphabetic character code into |cur_val|'
(*PASCAL module 442*)
begin get_token; {suppress macro expansion} 
if cur_tok<cs_token_flag then 
  begin cur_val:=cur_chr; 
  if cur_cmd<=right_brace then 
    if cur_cmd=right_brace then incr(align_state) 
    else decr(align_state); 
  end 
else if cur_tok<cs_token_flag+single_base then 
  cur_val:=cur_tok-cs_token_flag-active_base 
else cur_val:=cur_tok-cs_token_flag-single_base; 
if cur_val>255 then 
  begin print_err('Improper alphabetic constant'); 
(*Improper alphabetic constant*) 
  help2('A one-character control sequence belongs after a ` mark.')
 
    ('So I''m essentially inserting \0 here.'); 
  cur_val:='0'; back_error; 
  end 
else 
INSERT: 'Scan an optional space'
; 
end 

MODULE: 'Scan an optional space'
(*PASCAL module 443*)
begin get_x_token; if cur_cmd<>spacer then back_input; 
end 

MODULE: 'Scan a numeric constant'
(*PASCAL module 444*)
begin radix:=10; m:=214748364; 
if cur_tok=octal_token then 
  begin radix:=8; m:=268435456; get_x_token; 
  end 
else if cur_tok=hex_token then 
  begin radix:=16; m:=134217728; get_x_token; 
  end; 
vacuous:=true; cur_val:=0;
 

INSERT: 'Accumulate the constant until |cur_tok| is not a suitable digit'
; 
if vacuous then 
INSERT: 'Express astonishment that no number was here'

else if cur_cmd<>spacer then back_input; 
end 

MODULE: 'Accumulate the constant...'
(*PASCAL module 445*)
loop  begin if (cur_tok<zero_token+radix)and(cur_tok>=zero_token)and 
    (cur_tok<=zero_token+9) then d:=cur_tok-zero_token 
  else if radix=16 then 
    if (cur_tok<=A_token+5)and(cur_tok>=A_token) then d:=cur_tok-A_token+10 
    else if (cur_tok<=other_A_token+5)and(cur_tok>=other_A_token) then 
      d:=cur_tok-other_A_token+10 
    else goto done 
  else goto done; 
  vacuous:=false; 
  if (cur_val>=m)and((cur_val>m)or(d>7)or(radix<>10)) then 
    begin if OK_so_far then 
      begin print_err('Number too big'); 
(*Number too big*) 
      help2('I can only go up to 2147483647=''17777777777=''7FFFFFFF,')
 
        ('so I''m using that number instead of yours.'); 
      error; cur_val:=infinity; OK_so_far:=false; 
      end; 
    end 
  else cur_val:=cur_val*radix+d; 
  get_x_token; 
  end; 
done: 

MODULE: 'Express astonishment...'
(*PASCAL module 446*)
begin print_err('Missing number, treated as zero'); 
(*Missing number...*) 
help3('A number should have been here; I inserted `0''.')
 
  ('(If you can''t figure out why I needed to see a number,')
 
  ('look up `weird error'' in the index to The TeXbook.)'); 
(*TeXbook][\sl The \TeX book*) 
back_error; 
end 

MODULE: 'Glob... '
(*PASCAL module 447*)
cur_order:glue_ord; {order of infinity found by |scan_dimen|} 

MODULE: 'Fetch an internal dimension and |goto attach_sign|...'
(*PASCAL module 449*)
if mu then 
  begin scan_something_internal(mu_val,false); 
  
INSERT: 'Coerce glue to a dimension'
; 
  if cur_val_level=mu_val then goto attach_sign; 
  if cur_val_level<>int_val then mu_error; 
  end 
else  begin scan_something_internal(dimen_val,false); 
  if cur_val_level=dimen_val then goto attach_sign; 
  end 

MODULE: 'Local variables for dimension calculations'
(*PASCAL module 450*)
num,denom:1..65536; {conversion ratio for the scanned units} 
k,kk:small_number; {number of digits in a decimal fraction} 
p,q:pointer; {top of decimal digit stack} 
v:scaled; {an internal dimension} 
save_cur_val:integer; {temporary storage of |cur_val|} 

MODULE: 'Coerce glue to a dimension'
(*PASCAL module 451*)
if cur_val_level>=glue_val then 
  begin v:=width(cur_val); delete_glue_ref(cur_val); cur_val:=v; 
  end 

MODULE: 'Scan decimal fraction'
(*PASCAL module 452*)
begin k:=0; p:=null; get_token; {|point_token| is being re-scanned} 
loop  begin get_x_token; 
  if (cur_tok>zero_token+9)or(cur_tok<zero_token) then goto done1; 
  if k<17 then {digits for |k>=17| cannot affect the result} 
    begin q:=get_avail; link(q):=p; info(q):=cur_tok-zero_token; 
    p:=q; incr(k); 
    end; 
  end; 
done1: for kk:=k downto 1 do 
  begin dig[kk-1]:=info(p); q:=p; p:=link(p); free_avail(q); 
  end; 
f:=round_decimals(k); 
if cur_cmd<>spacer then back_input; 
end 

MODULE: 'Scan units and set |cur_val| to $x\cdot(|cur_val|+f/2^{16})$...'
(*PASCAL module 453*)
if inf then 
INSERT: 'Scan for \(f)\.{fil} units; |goto attach_fraction| if found'
; 

INSERT: 'Scan for \(u)units that are internal dimensions;   |goto attach_sign| with |cur_val| set if found'
; 
if mu then 
INSERT: 'Scan for \(m)\.{mu} units and |goto attach_fraction|'
; 
if scan_keyword('true') then 
INSERT: 'Adjust \(f)for the magnification ratio'
; 
(*true*) 
if scan_keyword('pt') then goto attach_fraction; {the easy case} 
(*pt*) 

INSERT: 'Scan for \(a)all other units and adjust |cur_val| and |f| accordingly;   |goto done| in the case of scaled points'
; 
attach_fraction: if cur_val>=16384 then arith_error:=true 
else cur_val:=cur_val*unity+f; 
done: 

MODULE: 'Scan for \(f)\.{fil} units...'
(*PASCAL module 454*)
if scan_keyword('fil') then 
(*fil*) 
  begin cur_order:=fil; 
  while scan_keyword('l') do 
    begin if cur_order=filll then 
      begin print_err('Illegal unit of measure ('); 
(*Illegal unit of measure*) 
      print('replaced by filll)'); 
      help1('I dddon''t go any higher than filll.'); error; 
      end 
    else incr(cur_order); 
    end; 
  goto attach_fraction; 
  end 

MODULE: 'Scan for \(u)units that are internal dimensions...'
(*PASCAL module 455*)
save_cur_val:=cur_val; 

INSERT: 'Get the next non-blank non-call...'
; 
if (cur_cmd<min_internal)or(cur_cmd>max_internal) then back_input 
else  begin if mu then 
    begin scan_something_internal(mu_val,false); 
INSERT: 'Coerce glue...'
; 
    if cur_val_level<>mu_val then mu_error; 
    end 
  else scan_something_internal(dimen_val,false); 
  v:=cur_val; goto found; 
  end; 
if mu then goto not_found; 
if scan_keyword('em') then v:=(
INSERT: 'The em width for |cur_font|'
) 
(*em*) 
else if scan_keyword('ex') then v:=(
INSERT: 'The x-height for |cur_font|'
) 
(*ex*) 
else goto not_found; 

INSERT: 'Scan an optional space'
; 
found:cur_val:=nx_plus_y(save_cur_val,v,xn_over_d(v,f,65536)); 
goto attach_sign; 
not_found: 

MODULE: 'Scan for \(m)\.{mu} units and |goto attach_fraction|'
(*PASCAL module 456*)
if scan_keyword('mu') then goto attach_fraction 
(*mu*) 
else  begin print_err('Illegal unit of measure ('); print('mu inserted)'); 
(*Illegal unit of measure*) 
  help4('The unit of measurement in math glue must be mu.')
 
    ('To recover gracefully from this error, it''s best to')
 
    ('delete the erroneous units; e.g., type `2'' to delete')
 
    ('two letters. (See Chapter 27 of The TeXbook.)'); 
(*TeXbook][\sl The \TeX book*) 
  error; goto attach_fraction; 
  end 

MODULE: 'Adjust \(f)for the magnification ratio'
(*PASCAL module 457*)
begin prepare_mag; 
if mag<>1000 then 
  begin cur_val:=xn_over_d(cur_val,1000,mag); 
  f:=(1000*f+65536*remainder) div mag; 
  cur_val:=cur_val+(f div 65536); f:=f mod 65536; 
  end; 
end 

MODULE: 'Scan for \(a)all other units and adjust |cur_val| and |f|...'
(*PASCAL module 458*)
if scan_keyword('in') then set_conversion(7227)(100) 
(*in*) 
else if scan_keyword('pc') then set_conversion(12)(1) 
(*pc*) 
else if scan_keyword('cm') then set_conversion(7227)(254) 
(*cm*) 
else if scan_keyword('mm') then set_conversion(7227)(2540) 
(*mm*) 
else if scan_keyword('bp') then set_conversion(7227)(7200) 
(*bp*) 
else if scan_keyword('dd') then set_conversion(1238)(1157) 
(*dd*) 
else if scan_keyword('cc') then set_conversion(14856)(1157) 
(*cc*) 
else if scan_keyword('sp') then goto done 
(*sp*) 
else 
INSERT: 'Complain about unknown unit and |goto done2|'
; 
cur_val:=xn_over_d(cur_val,num,denom); 
f:=(num*f+65536*remainder) div denom;
 
cur_val:=cur_val+(f div 65536); f:=f mod 65536; 
done2: 

MODULE: 'Complain about unknown unit...'
(*PASCAL module 459*)
begin print_err('Illegal unit of measure ('); print('pt inserted)'); 
(*Illegal unit of measure*) 
help6('Dimensions can be in units of em, ex, in, pt, pc,')
 
  ('cm, mm, dd, cc, bp, or sp; but yours is a new one!')
 
  ('I''ll assume that you meant to say pt, for printer''s points.')
 
  ('To recover gracefully from this error, it''s best to')
 
  ('delete the erroneous units; e.g., type `2'' to delete')
 
  ('two letters. (See Chapter 27 of The TeXbook.)'); 
(*TeXbook][\sl The \TeX book*) 
error; goto done2; 
end 


MODULE: 'Report that this dimension is out of range'
(*PASCAL module 460*)
begin print_err('Dimension too large'); 
(*Dimension too large*) 
help2('I can''t work with sizes bigger than about 19 feet.')
 
  ('Continue and I''ll use the largest value I can.');
 
error; cur_val:=max_dimen; arith_error:=false; 
end 

MODULE: 'Create a new glue specification whose width is |cur_val|...'
(*PASCAL module 462*)
q:=new_spec(zero_glue); width(q):=cur_val; 
if scan_keyword('plus') then 
(*plus*) 
  begin scan_dimen(mu,true,false); 
  stretch(q):=cur_val; stretch_order(q):=cur_order; 
  end; 
if scan_keyword('minus') then 
(*minus*) 
  begin scan_dimen(mu,true,false); 
  shrink(q):=cur_val; shrink_order(q):=cur_order; 
  end; 
cur_val:=q 

MODULE: 'Copy the token list'
(*PASCAL module 466*)
begin p:=temp_head; link(p):=null; 
if cur_val_level=ident_val then store_new_token(cs_token_flag+cur_val) 
else if cur_val<>null then 
  begin r:=link(cur_val); {do not copy the reference count} 
  while r<>null do 
    begin fast_store_new_token(info(r)); r:=link(r); 
    end; 
  end; 
the_toks:=p; 
end 

MODULE: 'Put each...'
(*PASCAL module 468*)
primitive('number',convert,number_code);
 
(*number_][\.{\\number} primitive*) 
primitive('romannumeral',convert,roman_numeral_code);
 
(*roman_numeral_][\.{\\romannumeral} primitive*) 
primitive('string',convert,string_code);
 
(*string_][\.{\\string} primitive*) 
primitive('meaning',convert,meaning_code);
 
(*meaning_][\.{\\meaning} primitive*) 
primitive('fontname',convert,font_name_code);
 
(*font_name_][\.{\\fontname} primitive*) 
primitive('jobname',convert,job_name_code);
 
(*job_name_][\.{\\jobname} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 469*)
convert: case chr_code of 
  number_code: print_esc('number'); 
  roman_numeral_code: print_esc('romannumeral'); 
  string_code: print_esc('string'); 
  meaning_code: print_esc('meaning'); 
  font_name_code: print_esc('fontname'); 
  othercases print_esc('jobname') 
  endcases; 

MODULE: 'Scan the argument for command |c|'
(*PASCAL module 471*)
case c of 
number_code,roman_numeral_code: scan_int; 
string_code, meaning_code: begin save_scanner_status:=scanner_status; 
  scanner_status:=normal; get_token; scanner_status:=save_scanner_status; 
  end; 
font_name_code: scan_font_ident; 
job_name_code: if job_name=0 then open_log_file; 
end {there are no other cases} 

MODULE: 'Print the result of command |c|'
(*PASCAL module 472*)
case c of 
number_code: print_int(cur_val); 
roman_numeral_code: print_roman_int(cur_val); 
string_code:if cur_cs<>0 then sprint_cs(cur_cs) 
  else print_char(cur_chr); 
meaning_code: print_meaning; 
font_name_code: begin print(font_name[cur_val]); 
  if font_size[cur_val]<>font_dsize[cur_val] then 
    begin print(' at '); print_scaled(font_size[cur_val]); 
    print('pt'); 
    end; 
  end; 
job_name_code: print(job_name); 
end {there are no other cases} 

MODULE: 'Scan and build the parameter part...'
(*PASCAL module 474*)
begin loop begin get_token; {set |cur_cmd|, |cur_chr|, |cur_tok|} 
  if cur_tok<right_brace_limit then goto done1; 
  if cur_cmd=mac_param then 
    
INSERT: 'If the next character is a parameter number, make |cur_tok|       a |match| token; but if it is a left brace, store       `|left_brace|, |end_match|'', set |hash_brace|, and |goto done|'
; 
  store_new_token(cur_tok); 
  end; 
done1: store_new_token(end_match_token); 
if cur_cmd=right_brace then 
  
INSERT: 'Express shock at the missing left brace; |goto found|'
; 
done: end 

MODULE: 'Express shock...'
(*PASCAL module 475*)
begin print_err('Missing { inserted'); incr(align_state); 
(*Missing \[
inserted*) 
help2('Where was the left brace? You said something like `\def\a}'',')
 
  ('which I''m going to interpret as `\def\a{}''.'); error; goto found; 
end 

MODULE: 'If the next character is a parameter number...'
(*PASCAL module 476*)
begin s:=match_token+cur_chr; get_token; 
if cur_cmd=left_brace then 
  begin hash_brace:=cur_tok; 
  store_new_token(cur_tok); store_new_token(end_match_token); 
  goto done; 
  end; 
if t=zero_token+9 then 
  begin print_err('You already have nine parameters'); 
(*You already have nine...*) 
  help1('I''m going to ignore the # sign you just used.'); error; 
  end 
else  begin incr(t); 
  if cur_tok<>t then 
    begin print_err('Parameters must be numbered consecutively'); 
(*Parameters...consecutively*) 
    help2('I''ve inserted the digit you should have used after the #.')
 
      ('Type `1'' to delete what you did use.'); back_error; 
    end; 
  cur_tok:=s; 
  end; 
end 

MODULE: 'Scan and build the body of the token list; |goto found| when finished'
(*PASCAL module 477*)
unbalance:=1; 
loop  begin if xpand then 
INSERT: 'Expand the next part of the input'

  else get_token; 
  if cur_tok<right_brace_limit then 
    if cur_cmd<right_brace then incr(unbalance) 
    else  begin decr(unbalance); 
      if unbalance=0 then goto found; 
      end 
  else if cur_cmd=mac_param then 
    if macro_def then 
INSERT: 'Look for parameter number or \.{\#\#}'
; 
  store_new_token(cur_tok); 
  end 

MODULE: 'Expand the next part of the input'
(*PASCAL module 478*)
begin loop begin get_next; 
  if cur_cmd<=max_command then goto done2; 
  if cur_cmd<>the then expand 
  else  begin q:=the_toks; 
    if link(temp_head)<>null then 
      begin link(p):=link(temp_head); p:=q; 
      end; 
    end; 
  end; 
done2: x_token 
end 

MODULE: 'Look for parameter number...'
(*PASCAL module 479*)
begin s:=cur_tok; 
if xpand then get_x_token else get_token; 
if cur_cmd<>mac_param then 
  if (cur_tok<=zero_token)or(cur_tok>t) then 
    begin print_err('Illegal parameter number in definition of '); 
(*Illegal parameter number...*) 
    sprint_cs(warning_index); 
    help3('You meant to type ## instead of #, right?')
 
    ('Or maybe a } was forgotten somewhere earlier, and things')
 
    ('are all screwed up? I''m going to assume that you meant ##.'); 
    back_error; cur_tok:=s; 
    end 
  else cur_tok:=out_param_token-'0'+cur_chr; 
end 

MODULE: 'Glob... '
(*PASCAL module 480*)
read_file:array[0..15] of alpha_file; {used for \.[\\read]} 
read_open:array[0..16] of normal..closed; {state of |read_file[n]|} 

MODULE: 'Set init...'
(*PASCAL module 481*)
for k:=0 to 16 do read_open[k]:=closed; 

MODULE: 'Input and store tokens from the next line of the file'
(*PASCAL module 483*)
begin_file_reading; name:=m+1; 
if read_open[m]=closed then 
INSERT: 'Input for \.{\\read} from the terminal'

else if read_open[m]=just_open then 
INSERT: 'Input the first line of |read_file[m]|'

else 
INSERT: 'Input the next line of |read_file[m]|'
; 
limit:=last; 
if end_line_char_inactive then decr(limit) 
else  buffer[limit]:=end_line_char; 
first:=limit+1; loc:=start; state:=new_line;
 
loop  begin get_token; 
  if cur_tok=0 then goto done; 
    {|cur_cmd=cur_chr=0| will occur at the end of the line} 
  if align_state<1000000 then {unmatched `\.\]' 
aborts the line} 
    begin repeat get_token; until cur_tok=0; 
    align_state:=1000000; goto done; 
    end; 
  store_new_token(cur_tok); 
  end; 
done: end_file_reading 

MODULE: 'Input for \.{\\read} from the terminal'
(*PASCAL module 484*)
if interaction>nonstop_mode then 
  if n<0 then prompt_input('') 
  else  begin wake_up_terminal; 
    print_ln; sprint_cs(r); prompt_input('='); n:=-1; 
    end 
else fatal_error('*** (cannot \read from terminal in nonstop modes)') 
(*cannot \\read*) 

MODULE: 'Input the first line of |read_file[m]|'
(*PASCAL module 485*)
if input_ln(read_file[m],false) then read_open[m]:=normal 
else  begin a_close(read_file[m]); read_open[m]:=closed; 
  end 

MODULE: 'Input the next line of |read_file[m]|'
(*PASCAL module 486*)
begin if not input_ln(read_file[m],true) then 
  begin a_close(read_file[m]); read_open[m]:=closed; 
  if align_state<>1000000 then 
    begin runaway; 
    print_err('File ended within '); print_esc('read'); 
(*File ended within \\read*) 
    help1('This \read has unbalanced braces.'); 
    align_state:=1000000; error; 
    end; 
  end; 
end 

MODULE: 'Put each...'
(*PASCAL module 487*)
primitive('if',if_test,if_char_code); 
(*if_char_][\.{\\if} primitive*) 
primitive('ifcat',if_test,if_cat_code); 
(*if_cat_code_][\.{\\ifcat} primitive*) 
primitive('ifnum',if_test,if_int_code); 
(*if_int_][\.{\\ifnum} primitive*) 
primitive('ifdim',if_test,if_dim_code); 
(*if_dim_][\.{\\ifdim} primitive*) 
primitive('ifodd',if_test,if_odd_code); 
(*if_odd_][\.{\\ifodd} primitive*) 
primitive('ifvmode',if_test,if_vmode_code); 
(*if_vmode_][\.{\\ifvmode} primitive*) 
primitive('ifhmode',if_test,if_hmode_code); 
(*if_hmode_][\.{\\ifhmode} primitive*) 
primitive('ifmmode',if_test,if_mmode_code); 
(*if_mmode_][\.{\\ifmmode} primitive*) 
primitive('ifinner',if_test,if_inner_code); 
(*if_inner_][\.{\\ifinner} primitive*) 
primitive('ifvoid',if_test,if_void_code); 
(*if_void_][\.{\\ifvoid} primitive*) 
primitive('ifhbox',if_test,if_hbox_code); 
(*if_hbox_][\.{\\ifhbox} primitive*) 
primitive('ifvbox',if_test,if_vbox_code); 
(*if_vbox_][\.{\\ifvbox} primitive*) 
primitive('ifx',if_test,ifx_code); 
(*ifx_][\.{\\ifx} primitive*) 
primitive('ifeof',if_test,if_eof_code); 
(*if_eof_][\.{\\ifeof} primitive*) 
primitive('iftrue',if_test,if_true_code); 
(*if_true_][\.{\\iftrue} primitive*) 
primitive('iffalse',if_test,if_false_code); 
(*if_false_][\.{\\iffalse} primitive*) 
primitive('ifcase',if_test,if_case_code); 
(*if_case_][\.{\\ifcase} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 488*)
if_test: case chr_code of 
  if_cat_code:print_esc('ifcat'); 
  if_int_code:print_esc('ifnum'); 
  if_dim_code:print_esc('ifdim'); 
  if_odd_code:print_esc('ifodd'); 
  if_vmode_code:print_esc('ifvmode'); 
  if_hmode_code:print_esc('ifhmode'); 
  if_mmode_code:print_esc('ifmmode'); 
  if_inner_code:print_esc('ifinner'); 
  if_void_code:print_esc('ifvoid'); 
  if_hbox_code:print_esc('ifhbox'); 
  if_vbox_code:print_esc('ifvbox'); 
  ifx_code:print_esc('ifx'); 
  if_eof_code:print_esc('ifeof'); 
  if_true_code:print_esc('iftrue'); 
  if_false_code:print_esc('iffalse'); 
  if_case_code:print_esc('ifcase'); 
  othercases print_esc('if') 
  endcases; 

MODULE: 'Glob... '
(*PASCAL module 489*)
cond_ptr:pointer; {top of the condition stack} 
if_limit:normal..or_code; {upper bound on |fi_or_else| codes} 
cur_if:small_number; {type of conditional being worked on} 
if_line:integer; {line where that conditional began} 

MODULE: 'Set init...'
(*PASCAL module 490*)
cond_ptr:=null; if_limit:=normal; cur_if:=0; if_line:=0; 

MODULE: 'Put each...'
(*PASCAL module 491*)
primitive('fi',fi_or_else,fi_code); 
(*fi_][\.{\\fi} primitive*) 
text(frozen_fi):='fi'; eqtb[frozen_fi]:=eqtb[cur_val]; 
primitive('or',fi_or_else,or_code); 
(*or_][\.{\\or} primitive*) 
primitive('else',fi_or_else,else_code); 
(*else_][\.{\\else} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 492*)
fi_or_else: if chr_code=fi_code then print_esc('fi') 
  else if chr_code=or_code then print_esc('or') 
  else print_esc('else'); 

MODULE: 'Glob... '
(*PASCAL module 493*)
skip_line:integer; {skipping began here} 

MODULE: 'Push the condition stack'
(*PASCAL module 495*)
begin p:=get_node(if_node_size); link(p):=cond_ptr; type(p):=if_limit; 
subtype(p):=cur_if; if_line_field(p):=if_line; 
cond_ptr:=p; cur_if:=cur_chr; if_limit:=if_code; if_line:=line; 
end 

MODULE: 'Pop the condition stack'
(*PASCAL module 496*)
begin p:=cond_ptr; if_line:=if_line_field(p); 
cur_if:=subtype(p); if_limit:=type(p); cond_ptr:=link(p); 
free_node(p,if_node_size); 
end 

MODULE: 'Skip to \.{\\else} or \.{\\fi}...'
(*PASCAL module 500*)
loop  begin pass_text; 
  if cond_ptr=save_cond_ptr then 
    begin if cur_chr<>or_code then goto common_ending; 
    print_err('Extra '); print_esc('or'); 
(*Extra \\or*) 
    help1('I''m ignoring this; it doesn''t match any \if.'); 
    error; 
    end 
  else if cur_chr=fi_code then 
INSERT: 'Pop the condition stack'
; 
  end 

MODULE: 'Either process \.{\\ifcase} or set |b|...'
(*PASCAL module 501*)
case this_if of 
if_char_code, if_cat_code: 
INSERT: 'Test if two characters match'
; 
if_int_code, if_dim_code: 
INSERT: 'Test relation between integers or dimensions'
; 
if_odd_code: 
INSERT: 'Test if an integer is odd'
; 
if_vmode_code: b:=(abs(mode)=vmode); 
if_hmode_code: b:=(abs(mode)=hmode); 
if_mmode_code: b:=(abs(mode)=mmode); 
if_inner_code: b:=(mode<0); 
if_void_code, if_hbox_code, if_vbox_code: 
INSERT: 'Test box register status'
; 
ifx_code: 
INSERT: 'Test if two tokens match'
; 
if_eof_code: begin scan_four_bit_int; b:=(read_open[cur_val]=closed); 
  end; 
if_true_code: b:=true; 
if_false_code: b:=false; 
if_case_code: 
INSERT: 'Select the appropriate case   and |return| or |goto common_ending|'
; 
end {there are no other cases} 

MODULE: 'Display the value of |b|'
(*PASCAL module 502*)
begin begin_diagnostic; 
if b then print('{true}')else print('{false}'); 
end_diagnostic(false); 
end 

MODULE: 'Test relation between integers or dimensions'
(*PASCAL module 503*)
begin if this_if=if_int_code then scan_intelse scan_normal_dimen; 
n:=cur_val; 
INSERT: 'Get the next non-blank non-call...'
; 
if (cur_tok>=other_token+'<')and(cur_tok<=other_token+'>') then 
  r:=cur_tok-other_token 
else  begin print_err('Missing = inserted for '); 
(*Missing = inserted*) 
  print_cmd_chr(if_test,this_if); 
  help1('I was expecting to see `<'', `='', or `>''. Didn''t.'); 
  back_error; r:='='; 
  end; 
if this_if=if_int_code then scan_intelse scan_normal_dimen; 
case r of 
'<': b:=(n<cur_val); 
'=': b:=(n=cur_val); 
'>': b:=(n>cur_val); 
end; 
end 

MODULE: 'Test if an integer is odd'
(*PASCAL module 504*)
begin scan_int; b:=odd(cur_val); 
end 

MODULE: 'Test box register status'
(*PASCAL module 505*)
begin scan_eight_bit_int; p:=box(cur_val); 
if this_if=if_void_code then b:=(p=null) 
else if p=null then b:=false 
else if this_if=if_hbox_code then b:=(type(p)=hlist_node) 
else b:=(type(p)=vlist_node); 
end 

MODULE: 'Test if two characters match'
(*PASCAL module 506*)
begin get_x_token_or_active_char; 
if (cur_cmd>active_char)or(cur_chr>255) then {not a character} 
  begin m:=relax; n:=256; 
  end 
else  begin m:=cur_cmd; n:=cur_chr; 
  end; 
get_x_token_or_active_char; 
if (cur_cmd>active_char)or(cur_chr>255) then 
  begin cur_cmd:=relax; cur_chr:=256; 
  end; 
if this_if=if_char_code then b:=(n=cur_chr)else b:=(m=cur_cmd); 
end 

MODULE: 'Test if two tokens match'
(*PASCAL module 507*)
begin save_scanner_status:=scanner_status; scanner_status:=normal; 
get_next; n:=cur_cs; p:=cur_cmd; q:=cur_chr; 
get_next; if cur_cmd<>p then b:=false 
else if cur_cmd<call then b:=(cur_chr=q) 
else 
INSERT: 'Test if two macro texts match'
; 
scanner_status:=save_scanner_status; 
end 

MODULE: 'Test if two macro texts match'
(*PASCAL module 508*)
begin p:=link(cur_chr); q:=link(equiv(n)); {omit reference counts} 
if p=q then b:=true 
else begin while (p<>null)and(q<>null) do 
    if info(p)<>info(q) then p:=null 
    else  begin p:=link(p); q:=link(q); 
      end; 
  b:=((p=null)and(q=null)); 
  end; 
end 

MODULE: 'Select the appropriate case and |return| or |goto common_ending|'
(*PASCAL module 509*)
begin scan_int; n:=cur_val; {|n| is the number of cases to pass} 
if tracing_commands>1 then 
  begin begin_diagnostic; print('{case '); print_int(n); print_char('}'); 
  end_diagnostic(false); 
  end; 
while n<>0 do 
  begin pass_text; 
  if cond_ptr=save_cond_ptr then 
    if cur_chr=or_code then decr(n) 
    else goto common_ending 
  else if cur_chr=fi_code then 
INSERT: 'Pop the condition stack'
; 
  end; 
change_if_limit(or_code,save_cond_ptr); 
return; {wait for \.[\\or], \.[\\else], or \.[\\fi]} 
end 

MODULE: 'Terminate the current conditional and skip to \.{\\fi}'
(*PASCAL module 510*)
if cur_chr>if_limit then 
  if if_limit=if_code then insert_relax {condition not yet evaluated} 
  else  begin print_err('Extra '); print_cmd_chr(fi_or_else,cur_chr); 
(*Extra \\or*) 
(*Extra \\else*) 
(*Extra \\fi*) 
    help1('I''m ignoring this; it doesn''t match any \if.'); 
    error; 
    end 
else  begin while cur_chr<>fi_code do pass_text; {skip to \.[\\fi]} 
  
INSERT: 'Pop the condition stack'
; 
  end 

MODULE: 'Glob... '
(*PASCAL module 512*)
cur_name:str_number; {name of file just scanned} 
cur_area:str_number; {file area just scanned, or \.['']} 
cur_ext:str_number; {file extension just scanned, or \.['']} 

MODULE: 'Glob... '
(*PASCAL module 513*)
area_delimiter:pool_pointer; {the most recent `\.>' or `\.:', if any} 
ext_delimiter:pool_pointer; {the relevant `\..', if any} 

MODULE: 'Basic printing...'
(*PASCAL module 518*)
procedure print_file_name(n,a,e:integer); 
begin slow_print(a); slow_print(n); slow_print(e); 
end; 

MODULE: 'Glob... '
(*PASCAL module 520*)
TEX_format_default:packed array[1..format_default_length] of char; 

MODULE: 'Set init...'
(*PASCAL module 521*)
TEX_format_default:='TeXformats:plain.fmt'; 
(*TeXformats*) 
(*plain*) 
(*system dependencies*) 

MODULE: 'Check the ``constant'''' values for consistency'
(*PASCAL module 522*)
if format_default_length>file_name_size then bad:=31; 

MODULE: 'Declare the function called |open_fmt_file|'
(*PASCAL module 524*)
function open_fmt_file:boolean; 
label found,exit; 
var j:0..buf_size; {the first space after the format file name} 
begin j:=loc; 
if buffer[loc]='&' then 
  begin incr(loc); j:=loc; buffer[last]:=' '; 
  while buffer[j]<>' ' do incr(j); 
  pack_buffered_name(0,loc,j-1); {try first without the system file area} 
  if w_open_in(fmt_file) then goto found; 
  pack_buffered_name(format_area_length,loc,j-1); 
    {now try the system format file area} 
  if w_open_in(fmt_file) then goto found; 
  wake_up_terminal; 
  wterm_ln('Sorry, I can''t find that format;',' will try PLAIN.'); 
(*Sorry, I can''t find...*) 
  update_terminal; 
  end; 
  {now pull out all the stops: try for the system \.[plain] file} 
pack_buffered_name(format_default_length-format_ext_length,1,0); 
if not w_open_in(fmt_file) then 
  begin wake_up_terminal; 
  wterm_ln('I can''t find the PLAIN format file!'); 
(*I can''t find PLAIN...*) 
(*plain*) 
  open_fmt_file:=false; return; 
  end; 
found:loc:=j; open_fmt_file:=true; 
exit:end; 

MODULE: 'Glob... '
(*PASCAL module 527*)
name_in_progress:boolean; {is a file name being scanned?} 
job_name:str_number; {principal file name} 
log_opened:boolean; {has the transcript file been opened?} 

MODULE: 'Initialize the output...'
(*PASCAL module 528*)
job_name:=0; name_in_progress:=false; log_opened:=false; 

MODULE: 'Scan file name in the buffer'
(*PASCAL module 531*)
begin begin_name; k:=first; 
while (buffer[k]=' ')and(k<last) do incr(k); 
loop  begin if k=last then goto done; 
  if not more_name(buffer[k]) then goto done; 
  incr(k); 
  end; 
done:end_name; 
end 

MODULE: 'Glob... '
(*PASCAL module 532*)
dvi_file: byte_file; {the device-independent output goes here} 
output_file_name: str_number; {full name of the output file} 
log_name:str_number; {full name of the log file} 

MODULE: 'Try to get a different log file name'
(*PASCAL module 535*)
begin selector:=term_only; 
prompt_file_name('transcript file name','.log'); 
end 

MODULE: 'Print the banner...'
(*PASCAL module 536*)
begin wlog(banner); 
slow_print(format_ident); print('  '); 
print_int(day); print_char(' '); 
months:='JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC'; 
for k:=3*month-2 to 3*month do wlog(months[k]); 
print_char(' '); print_int(year); print_char(' '); 
print_two(time div 60); print_char(':'); print_two(time mod 60); 
end 

MODULE: 'Read the first line...'
(*PASCAL module 538*)
begin line:=1; 
if input_ln(cur_file,false) then do_nothing; 
firm_up_the_line; 
if end_line_char_inactive then decr(limit) 
else  buffer[limit]:=end_line_char; 
first:=limit+1; loc:=start; 
end 

MODULE: 'Glob... '
(*PASCAL module 539*)
tfm_file:byte_file; 

MODULE: 'Types... '
(*PASCAL module 548*)
internal_font_number=font_base..font_max; {|font| in a |char_node|} 
font_index=0..font_mem_size; {index into |font_info|} 

MODULE: 'Glob... '
(*PASCAL module 549*)
font_info:array[font_index] of memory_word; 
  {the big collection of font data} 
fmem_ptr:font_index; {first unused word of |font_info|} 
font_ptr:internal_font_number; {largest internal font number in use} 
font_check:array[internal_font_number] of four_quarters; {check sum} 
font_size:array[internal_font_number] of scaled; {``at'' size} 
font_dsize:array[internal_font_number] of scaled; {``design'' size} 
font_params:array[internal_font_number] of font_index; {how many font 
  parameters are present} 
font_name:array[internal_font_number] of str_number; {name of the font} 
font_area:array[internal_font_number] of str_number; {area of the font} 
font_bc:array[internal_font_number] of eight_bits; 
  {beginning (smallest) character code} 
font_ec:array[internal_font_number] of eight_bits; 
  {ending (largest) character code} 
font_glue:array[internal_font_number] of pointer; 
  {glue specification for interword space, |null| if not allocated} 
font_used:array[internal_font_number] of boolean; 
  {has a character from this font actually appeared in the output?} 
hyphen_char:array[internal_font_number] of integer; 
  {current \.[\\hyphenchar] values} 
skew_char:array[internal_font_number] of integer; 
  {current \.[\\skewchar] values} 
bchar_label:array[internal_font_number] of font_index; 
  {start of |lig_kern| program for left boundary character, 
  |non_address| if there is none} 
font_bchar:array[internal_font_number] of min_quarterword..non_char; 
  {right boundary character, |non_char| if there is none} 
font_false_bchar:array[internal_font_number] of min_quarterword..non_char; 
  {|font_bchar| if it doesn't exist in the font, otherwise |non_char|} 

MODULE: 'Glob... '
(*PASCAL module 550*)
char_base:array[internal_font_number] of integer; 
  {base addresses for |char_info|} 
width_base:array[internal_font_number] of integer; 
  {base addresses for widths} 
height_base:array[internal_font_number] of integer; 
  {base addresses for heights} 
depth_base:array[internal_font_number] of integer; 
  {base addresses for depths} 
italic_base:array[internal_font_number] of integer; 
  {base addresses for italic corrections} 
lig_kern_base:array[internal_font_number] of integer; 
  {base addresses for ligature/kerning programs} 
kern_base:array[internal_font_number] of integer; 
  {base addresses for kerns} 
exten_base:array[internal_font_number] of integer; 
  {base addresses for extensible recipes} 
param_base:array[internal_font_number] of integer; 
  {base addresses for font parameters} 

MODULE: 'Set init...'
(*PASCAL module 551*)
for k:=font_base to font_max do font_used[k]:=false; 

MODULE: 'Initialize table...'
(*PASCAL module 552*)
font_ptr:=null_font; fmem_ptr:=7; 
font_name[null_font]:='nullfont'; font_area[null_font]:=''; 
hyphen_char[null_font]:='-'; skew_char[null_font]:=-1; 
bchar_label[null_font]:=non_address; 
font_bchar[null_font]:=non_char; font_false_bchar[null_font]:=non_char; 
font_bc[null_font]:=1; font_ec[null_font]:=0; 
font_size[null_font]:=0; font_dsize[null_font]:=0; 
char_base[null_font]:=0; width_base[null_font]:=0; 
height_base[null_font]:=0; depth_base[null_font]:=0; 
italic_base[null_font]:=0; lig_kern_base[null_font]:=0; 
kern_base[null_font]:=0; exten_base[null_font]:=0; 
font_glue[null_font]:=null; font_params[null_font]:=7; 
param_base[null_font]:=-1; 
for k:=0 to 6 do font_info[k].sc:=0; 

MODULE: 'Put each...'
(*PASCAL module 553*)
primitive('nullfont',set_font,null_font); 
(*null_font_][\.{\\nullfont} primitive*) 
text(frozen_null_font):='nullfont'; eqtb[frozen_null_font]:=eqtb[cur_val]; 

MODULE: 'Glob... '
(*PASCAL module 555*)
null_character:four_quarters; {nonexistent character information} 

MODULE: 'Set init...'
(*PASCAL module 556*)
null_character.b0:=min_quarterword; null_character.b1:=min_quarterword; 
null_character.b2:=min_quarterword; null_character.b3:=min_quarterword; 

MODULE: 'Report that the font won''t be loaded'
(*PASCAL module 561*)
start_font_error_message; 
(*Font x=xx not loadable...*) 
if file_opened then print(' not loadable: Bad metric (TFM) file') 
else print(' not loadable: Metric (TFM) file not found'); 
help5('I wasn''t able to read the size data for this font,')
 
('so I will ignore the font specification.')
 
('[Wizards can fix TFM files using TFtoPL/PLtoTF.]')
 
('You might try inserting a different font spec;')
 
('e.g., type `I\font<same font id>=<substitute font name>''.'); 
error 

MODULE: 'Read and check...'
(*PASCAL module 562*)

INSERT: 'Open |tfm_file| for input'
; 

INSERT: 'Read the {\.{TFM}} size fields'
; 

INSERT: 'Use size fields to allocate font information'
; 

INSERT: 'Read the {\.{TFM}} header'
; 

INSERT: 'Read character data'
; 

INSERT: 'Read box dimensions'
; 

INSERT: 'Read ligature/kern program'
; 

INSERT: 'Read extensible character recipes'
; 

INSERT: 'Read font parameters'
; 

INSERT: 'Make final adjustments and |goto done|'


MODULE: 'Open |tfm_file| for input'
(*PASCAL module 563*)
file_opened:=false; 
if aire='' then pack_file_name(nom,TEX_font_area,'.tfm') 
else pack_file_name(nom,aire,'.tfm'); 
if not b_open_in(tfm_file) then abort; 
file_opened:=true 

MODULE: 'Read the {\.{TFM}} size fields'
(*PASCAL module 565*)
begin read_sixteen(lf); 
fget; read_sixteen(lh); 
fget; read_sixteen(bc); 
fget; read_sixteen(ec); 
if (bc>ec+1)or(ec>255) then abort; 
if bc>255 then {|bc=256| and |ec=255|} 
  begin bc:=1; ec:=0; 
  end; 
fget; read_sixteen(nw); 
fget; read_sixteen(nh); 
fget; read_sixteen(nd); 
fget; read_sixteen(ni); 
fget; read_sixteen(nl); 
fget; read_sixteen(nk); 
fget; read_sixteen(ne); 
fget; read_sixteen(np); 
if lf<>6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np then abort; 
if (nw=0)or(nh=0)or(nd=0)or(ni=0) then abort; 
end 

MODULE: 'Use size fields to allocate font information'
(*PASCAL module 566*)
lf:=lf-6-lh; {|lf| words should be loaded into |font_info|} 
if np<7 then lf:=lf+7-np; {at least seven parameters will appear} 
if (font_ptr=font_max)or(fmem_ptr+lf>font_mem_size) then 
  
INSERT: 'Apologize for not loading the font, |goto done|'
; 
f:=font_ptr+1; 
char_base[f]:=fmem_ptr-bc; 
width_base[f]:=char_base[f]+ec+1; 
height_base[f]:=width_base[f]+nw; 
depth_base[f]:=height_base[f]+nh; 
italic_base[f]:=depth_base[f]+nd; 
lig_kern_base[f]:=italic_base[f]+ni; 
kern_base[f]:=lig_kern_base[f]+nl-kern_base_offset; 
exten_base[f]:=kern_base[f]+kern_base_offset+nk; 
param_base[f]:=exten_base[f]+ne 

MODULE: 'Apologize for not loading...'
(*PASCAL module 567*)
begin start_font_error_message; 
print(' not loaded: Not enough room left'); 
(*Font x=xx not loaded...*) 
help4('I''m afraid I won''t be able to make use of this font,')
 
('because my memory for character-size data is too small.')
 
('If you''re really stuck, ask a wizard to enlarge me.')
 
('Or maybe try `I\font<same font id>=<name of loaded font>''.'); 
error; goto done; 
end 

MODULE: 'Read the {\.{TFM}} header'
(*PASCAL module 568*)
begin if lh<2 then abort; 
store_four_quarters(font_check[f]); 
fget; read_sixteen(z); {this rejects a negative design size} 
fget; z:=z*256+fbyte; fget; z:=(z*16)+(fbyte div16); 
if z<unity then abort; 
while lh>2 do 
  begin fget;fget;fget;fget;decr(lh); {ignore the rest of the header} 
  end; 
font_dsize[f]:=z; 
if s<>-1000 then 
  if s>=0 then z:=s 
  else z:=xn_over_d(z,-s,1000); 
font_size[f]:=z; 
end 

MODULE: 'Read character data'
(*PASCAL module 569*)
for k:=fmem_ptr to width_base[f]-1 do 
  begin store_four_quarters(font_info[k].qqqq); 
  if (a>=nw)or(b div 16>=nh)or(b mod 16>=nd)or 
    (c div 4>=ni) then abort; 
  case c mod 4 of 
  lig_tag: if d>=nl then abort; 
  ext_tag: if d>=ne then abort; 
  list_tag: 
INSERT: 'Check for charlist cycle'
; 
  othercases do_nothing {|no_tag|} 
  endcases; 
  end 

MODULE: 'Check for charlist cycle'
(*PASCAL module 570*)
begin check_byte_range(d); 
while d<current_character_being_worked_on do 
  begin qw:=char_info(f)(d); 
  {N.B.: not |qi(d)|, since |char_base[f]| hasn't been adjusted yet} 
  if char_tag(qw)<>list_tag then goto not_found; 
  d:=qo(rem_byte(qw)); {next character on the list} 
  end; 
if d=current_character_being_worked_on then abort; {yes, there's a cycle} 
not_found:end 

MODULE: 'Read box dimensions'
(*PASCAL module 571*)
begin 
INSERT: 'Replace |z| by $|z|^\prime$ and compute $\alpha,\beta$'
; 
for k:=width_base[f] to lig_kern_base[f]-1 do 
  store_scaled(font_info[k].sc); 
if font_info[width_base[f]].sc<>0 then abort; {\\[width][0] must be zero} 
if font_info[height_base[f]].sc<>0 then abort; {\\[height][0] must be zero} 
if font_info[depth_base[f]].sc<>0 then abort; {\\[depth][0] must be zero} 
if font_info[italic_base[f]].sc<>0 then abort; {\\[italic][0] must be zero} 
end 

MODULE: 'Replace |z|...'
(*PASCAL module 572*)
begin alpha:=16; 
while z>=8388608 do 
  begin z:=z div 2; alpha:=alpha+alpha; 
  end; 
beta:=256 div alpha; alpha:=alpha*z; 
end 

MODULE: 'Read ligature/kern program'
(*PASCAL module 573*)
bch_label:=32767; bchar:=256; 
if nl>0 then 
  begin for k:=lig_kern_base[f] to kern_base[f]+kern_base_offset-1 do 
    begin store_four_quarters(font_info[k].qqqq); 
    if a>128 then 
      begin if 256*c+d>=nl then abort; 
      if a=255 then if k=lig_kern_base[f] then bchar:=b; 
      end 
    else begin if b<>bchar then check_existence(b); 
      if c<128 then check_existence(d) {check ligature} 
      else if 256*(c-128)+d>=nk then abort; {check kern} 
      if a<128 then if k-lig_kern_base[f]+a+1>=nl then abort; 
      end; 
    end; 
  if a=255 then bch_label:=256*c+d; 
  end; 
for k:=kern_base[f]+kern_base_offset to exten_base[f]-1 do 
  store_scaled(font_info[k].sc); 

MODULE: 'Read extensible character recipes'
(*PASCAL module 574*)
for k:=exten_base[f] to param_base[f]-1 do 
  begin store_four_quarters(font_info[k].qqqq); 
  if a<>0 then check_existence(a); 
  if b<>0 then check_existence(b); 
  if c<>0 then check_existence(c); 
  check_existence(d); 
  end 

MODULE: 'Read font parameters'
(*PASCAL module 575*)
begin for k:=1 to np do 
  if k=1 then {the |slant| parameter is a pure number} 
    begin fget; sw:=fbyte; if sw>127 then sw:=sw-256; 
    fget; sw:=sw*256+fbyte; fget; sw:=sw*256+fbyte; 
    fget; font_info[param_base[f]].sc:= 
      (sw*16)+(fbyte div16); 
    end 
  else store_scaled(font_info[param_base[f]+k-1].sc); 
if eof(tfm_file) then abort; 
for k:=np+1 to 7 do font_info[param_base[f]+k-1].sc:=0; 
end 

MODULE: 'Make final adjustments...'
(*PASCAL module 576*)
if np>=7 then font_params[f]:=npelse font_params[f]:=7; 
hyphen_char[f]:=default_hyphen_char; skew_char[f]:=default_skew_char; 
if bch_label<nl then bchar_label[f]:=bch_label+lig_kern_base[f] 
else bchar_label[f]:=non_address; 
font_bchar[f]:=qi(bchar); 
font_false_bchar[f]:=qi(bchar); 
if bchar<=ec then if bchar>=bc then 
  begin qw:=char_info(f)(bchar); {N.B.: not |qi(bchar)|} 
  if char_exists(qw) then font_false_bchar[f]:=non_char; 
  end; 
font_name[f]:=nom; 
font_area[f]:=aire; 
font_bc[f]:=bc; font_ec[f]:=ec; font_glue[f]:=null; 
adjust(char_base); adjust(width_base); adjust(lig_kern_base); 
adjust(kern_base); adjust(exten_base); 
decr(param_base[f]); 
fmem_ptr:=fmem_ptr+lf; font_ptr:=f; g:=f; goto done 

MODULE: 'Declare procedures that scan font-related stuff'
(*PASCAL module 577*)
procedure scan_font_ident; 
var f:internal_font_number; 
m:halfword; 
begin 
INSERT: 'Get the next non-blank non-call...'
; 
if cur_cmd=def_font then f:=cur_font 
else if cur_cmd=set_font then f:=cur_chr 
else if cur_cmd=def_family then 
  begin m:=cur_chr; scan_four_bit_int; f:=equiv(m+cur_val); 
  end 
else  begin print_err('Missing font identifier'); 
(*Missing font identifier*) 
  help2('I was looking for a control sequence whose')
 
  ('current meaning has been defined by \font.'); 
  back_error; f:=null_font; 
  end; 
cur_val:=f; 
end; 

MODULE: 'Declare procedures that scan font-related stuff'
(*PASCAL module 578*)
procedure find_font_dimen(writing:boolean); 
  {sets |cur_val| to |font_info| location} 
var f:internal_font_number; 
n:integer; {the parameter number} 
begin scan_int; n:=cur_val; scan_font_ident; f:=cur_val; 
if n<=0 then cur_val:=fmem_ptr 
else  begin if writing and(n<=space_shrink_code)and 
    (n>=space_code)and(font_glue[f]<>null) then 
    begin delete_glue_ref(font_glue[f]); 
    font_glue[f]:=null; 
    end; 
  if n>font_params[f] then 
    if f<font_ptr then cur_val:=fmem_ptr 
    else 
INSERT: 'Increase the number of parameters in the last font'

  else cur_val:=n+param_base[f]; 
  end; 

INSERT: 'Issue an error message if |cur_val=fmem_ptr|'
; 
end; 

MODULE: 'Issue an error message if |cur_val=fmem_ptr|'
(*PASCAL module 579*)
if cur_val=fmem_ptr then 
  begin print_err('Font '); print_esc(font_id_text(f)); 
  print(' has only '); print_int(font_params[f]); 
  print(' fontdimen parameters'); 
(*Font x has only...*) 
  help2('To increase the number of font parameters, you must')
 
    ('use \fontdimen immediately after the \font is loaded.'); 
  error; 
  end 

MODULE: 'Increase the number of parameters...'
(*PASCAL module 580*)
begin repeat if fmem_ptr=font_mem_size then 
  overflow('font memory',font_mem_size); 
(*TeX capacity exceeded font memory][\quad font memory*) 
font_info[fmem_ptr].sc:=0; incr(fmem_ptr); incr(font_params[f]); 
until n=font_params[f]; 
cur_val:=fmem_ptr-1; {this equals |param_base[f]+font_params[f]|} 
end 

MODULE: 'Glob... '
(*PASCAL module 592*)
total_pages:integer; {the number of pages that have been shipped out} 
max_v:scaled; {maximum height-plus-depth of pages shipped so far} 
max_h:scaled; {maximum width of pages shipped so far} 
max_push:integer; {deepest nesting of |push| commands encountered so far} 
last_bop:integer; {location of previous |bop| in the \.[DVI] output} 
dead_cycles:integer; {recent outputs that didn't ship anything out} 
doing_leaders:boolean; {are we inside a leader box?} 


 
c,f:quarterword; {character and font in current |char_node|} 
rule_ht,rule_dp,rule_wd:scaled; {size of current rule being output} 
g:pointer; {current glue specification} 
lq,lr:integer; {quantities used in calculations for leaders} 

MODULE: 'Set init...'
(*PASCAL module 593*)
total_pages:=0; max_v:=0; max_h:=0; max_push:=0; last_bop:=-1; 
doing_leaders:=false; dead_cycles:=0; cur_s:=-1; 

MODULE: 'Types... '
(*PASCAL module 594*)
dvi_index=0..dvi_buf_size; {an index into the output buffer} 

MODULE: 'Glob... '
(*PASCAL module 595*)
dvi_buf:array[dvi_index] of eight_bits; {buffer for \.[DVI] output} 
half_buf:dvi_index; {half of |dvi_buf_size|} 
dvi_limit:dvi_index; {end of the current half buffer} 
dvi_ptr:dvi_index; {the next available buffer address} 
dvi_offset:integer; {|dvi_buf_size| times the number of times the 
  output buffer has been fully emptied} 
dvi_gone:integer; {the number of bytes already output to |dvi_file|} 

MODULE: 'Set init...'
(*PASCAL module 596*)
half_buf:=dvi_buf_size div 2; dvi_limit:=dvi_buf_size; dvi_ptr:=0; 
dvi_offset:=0; dvi_gone:=0; 

MODULE: 'Empty the last bytes out of |dvi_buf|'
(*PASCAL module 599*)
if dvi_limit=half_buf then write_dvi(half_buf,dvi_buf_size-1); 
if dvi_ptr>0 then write_dvi(0,dvi_ptr-1) 

MODULE: 'Output the font name whose internal number is |f|'
(*PASCAL module 603*)
for k:=str_start[font_area[f]] to str_start[font_area[f]+1]-1 do 
  dvi_out(so(str_pool[k])); 
for k:=str_start[font_name[f]] to str_start[font_name[f]+1]-1 do 
  dvi_out(so(str_pool[k])) 

MODULE: 'Glob... '
(*PASCAL module 605*)
down_ptr,right_ptr:pointer; {heads of the down and right stacks} 

MODULE: 'Set init...'
(*PASCAL module 606*)
down_ptr:=null; right_ptr:=null; 

MODULE: 'Generate a |y0| or |z0| command...'
(*PASCAL module 609*)
info(q):=info(p); 
if info(q)=y_here then 
  begin dvi_out(o+y0-down1); {|y0| or |w0|} 
  while link(q)<>p do 
    begin q:=link(q); 
    case info(q) of 
    yz_OK: info(q):=z_OK; 
    y_OK: info(q):=d_fixed; 
    othercases do_nothing 
    endcases; 
    end; 
  end 
else  begin dvi_out(o+z0-down1); {|z0| or |x0|} 
  while link(q)<>p do 
    begin q:=link(q); 
    case info(q) of 
    yz_OK: info(q):=y_OK; 
    z_OK: info(q):=d_fixed; 
    othercases do_nothing 
    endcases; 
    end; 
  end 

MODULE: 'Generate a |down| or |right|...'
(*PASCAL module 610*)
info(q):=yz_OK; 
if abs(w)>=8388608 then 
  begin dvi_out(o+3); {|down4| or |right4|} 
  dvi_four(w); return; 
  end; 
if abs(w)>=32768 then 
  begin dvi_out(o+2); {|down3| or |right3|} 
  if w<0 then w:=w+16777216; 
  dvi_out(w div 65536); w:=w mod 65536; goto 2; 
  end; 
if abs(w)>=128 then 
  begin dvi_out(o+1); {|down2| or |right2|} 
  if w<0 then w:=w+65536; 
  goto 2; 
  end; 
dvi_out(o); {|down1| or |right1|} 
if w<0 then w:=w+256; 
goto 1; 
2: dvi_out(w div 256); 
1: dvi_out(w mod 256); return 

MODULE: 'Look at the other stack entries until deciding...'
(*PASCAL module 611*)
p:=link(q); mstate:=none_seen; 
while p<>null do 
  begin if width(p)=w then 
INSERT: 'Consider a node with matching width;     |goto found| if it''s a hit'

  else  case mstate+info(p) of 
    none_seen+y_here: mstate:=y_seen; 
    none_seen+z_here: mstate:=z_seen; 
    y_seen+z_here,z_seen+y_here: goto not_found; 
    othercases do_nothing 
    endcases; 
  p:=link(p); 
  end; 
not_found: 

MODULE: 'Consider a node with matching width...'
(*PASCAL module 612*)
case mstate+info(p) of 
none_seen+yz_OK,none_seen+y_OK,z_seen+yz_OK,z_seen+y_OK:(**);
 
  if location(p)<dvi_gone then goto not_found 
  else 
INSERT: 'Change buffered instruction to |y| or |w| and |goto found|'
; 
none_seen+z_OK,y_seen+yz_OK,y_seen+z_OK:(**);
 
  if location(p)<dvi_gone then goto not_found 
  else 
INSERT: 'Change buffered instruction to |z| or |x| and |goto found|'
; 
none_seen+y_here,none_seen+z_here,y_seen+z_here,z_seen+y_here: goto found; 
othercases do_nothing 
endcases 

MODULE: 'Change buffered instruction to |y| or |w| and |goto found|'
(*PASCAL module 613*)
begin k:=location(p)-dvi_offset; 
if k<0 then k:=k+dvi_buf_size; 
dvi_buf[k]:=dvi_buf[k]+y1-down1; 
info(p):=y_here; goto found; 
end 

MODULE: 'Change buffered instruction to |z| or |x| and |goto found|'
(*PASCAL module 614*)
begin k:=location(p)-dvi_offset; 
if k<0 then k:=k+dvi_buf_size; 
dvi_buf[k]:=dvi_buf[k]+z1-down1; 
info(p):=z_here; goto found; 
end 

MODULE: 'Glob... '
(*PASCAL module 616*)
dvi_h,dvi_v:scaled; {a \.[DVI] reader program thinks we are here} 
cur_h,cur_v:scaled; {\TeX\ thinks we are here} 
dvi_f:internal_font_number; {the current font} 
cur_s:integer; {current depth of output box nesting, initially $-1$} 

MODULE: 'Initialize variables as |ship_out| begins'
(*PASCAL module 617*)
dvi_h:=0; dvi_v:=0; cur_h:=h_offset; dvi_f:=null_font; 
ensure_dvi_open; 
if total_pages=0 then 
  begin dvi_out(pre); dvi_out(id_byte); {output the preamble} 
(*preamble of \.{DVI} file*) 
  dvi_four(25400000); dvi_four(473628672); {conversion ratio for sp} 
  prepare_mag; dvi_four(mag); {magnification factor is frozen} 
  old_setting:=selector; selector:=new_string; 
  print(' TeX output '); print_int(year); print_char('.'); 
  print_two(month); print_char('.'); print_two(day); 
  print_char(':'); print_two(time div 60); 
  print_two(time mod 60); 
  selector:=old_setting; dvi_out(cur_length); 
  for s:=str_start[str_ptr] to pool_ptr-1 do dvi_out(so(str_pool[s])); 
  pool_ptr:=str_start[str_ptr]; {flush the current string} 
  end 

MODULE: 'Output node |p| for |hlist_out|...'
(*PASCAL module 620*)
reswitch: if is_char_node(p) then 
  begin synch_h; synch_v; 
  repeat f:=font(p); c:=character(p); 
  if f<>dvi_f then 
INSERT: 'Change font |dvi_f| to |f|'
; 
  if c>=qi(128) then dvi_out(set1); 
  dvi_out(qo(c));
 
  cur_h:=cur_h+char_width(f)(char_info(f)(c)); 
  p:=link(p); 
  until not is_char_node(p); 
  dvi_h:=cur_h; 
  end 
else 
INSERT: 'Output the non-|char_node| |p| for |hlist_out|     and move to the next node'


MODULE: 'Change font |dvi_f| to |f|'
(*PASCAL module 621*)
begin if not font_used[f] then 
  begin dvi_font_def(f); font_used[f]:=true; 
  end; 
if f<=64+font_base then dvi_out(f-font_base-1+fnt_num_0) 
else  begin dvi_out(fnt1); dvi_out(f-font_base-1); 
  end; 
dvi_f:=f; 
end 

MODULE: 'Output the non-|char_node| |p| for |hlist_out|...'
(*PASCAL module 622*)
begin case type(p) of 
hlist_node,vlist_node:
INSERT: 'Output a box in an hlist'
; 
rule_node: begin rule_ht:=height(p); rule_dp:=depth(p); rule_wd:=width(p); 
  goto fin_rule; 
  end; 
whatsit_node: 
INSERT: 'Output the whatsit node |p| in an hlist'
; 
glue_node: 
INSERT: 'Move right or output leaders'
; 
kern_node,math_node:cur_h:=cur_h+width(p); 
ligature_node: 
INSERT: 'Make node |p| look like a |char_node| and |goto reswitch|'
; 
othercases do_nothing 
endcases;
 
goto next_p; 
fin_rule: 
INSERT: 'Output a rule in an hlist'
; 
move_past: cur_h:=cur_h+rule_wd; 
next_p:p:=link(p); 
end 

MODULE: 'Output a box in an hlist'
(*PASCAL module 623*)
if list_ptr(p)=null then cur_h:=cur_h+width(p) 
else  begin save_h:=dvi_h; save_v:=dvi_v; 
  cur_v:=base_line+shift_amount(p); {shift the box down} 
  temp_ptr:=p; edge:=cur_h; 
  if type(p)=vlist_node then vlist_outelse hlist_out; 
  dvi_h:=save_h; dvi_v:=save_v; 
  cur_h:=edge+width(p); cur_v:=base_line; 
  end 

MODULE: 'Output a rule in an hlist'
(*PASCAL module 624*)
if is_running(rule_ht) then rule_ht:=height(this_box); 
if is_running(rule_dp) then rule_dp:=depth(this_box); 
rule_ht:=rule_ht+rule_dp; {this is the rule thickness} 
if (rule_ht>0)and(rule_wd>0) then {we don't output empty rules} 
  begin synch_h; cur_v:=base_line+rule_dp; synch_v; 
  dvi_out(set_rule); dvi_four(rule_ht); dvi_four(rule_wd); 
  cur_v:=base_line; dvi_h:=dvi_h+rule_wd; 
  end 

MODULE: 'Move right or output leaders'
(*PASCAL module 625*)
begin g:=glue_ptr(p); rule_wd:=width(g)-cur_g; 
if g_sign<>normal then 
  begin if g_sign=stretching then 
    begin if stretch_order(g)=g_order then 
      begin cur_glue:=cur_glue+stretch(g); 
      vet_glue(float(glue_set(this_box))*cur_glue); 
(*real multiplication*) 
      cur_g:=round(glue_temp); 
      end; 
    end 
  else if shrink_order(g)=g_order then 
      begin cur_glue:=cur_glue-shrink(g); 
      vet_glue(float(glue_set(this_box))*cur_glue); 
      cur_g:=round(glue_temp); 
      end; 
  end; 
rule_wd:=rule_wd+cur_g; 
if subtype(p)>=a_leaders then 
  
INSERT: 'Output leaders in an hlist, |goto fin_rule| if a rule     or to |next_p| if done'
; 
goto move_past; 
end 

MODULE: 'Output leaders in an hlist...'
(*PASCAL module 626*)
begin leader_box:=leader_ptr(p); 
if type(leader_box)=rule_node then 
  begin rule_ht:=height(leader_box); rule_dp:=depth(leader_box); 
  goto fin_rule; 
  end; 
leader_wd:=width(leader_box); 
if (leader_wd>0)and(rule_wd>0) then 
  begin rule_wd:=rule_wd+10; {compensate for floating-point rounding} 
  edge:=cur_h+rule_wd; lx:=0; 
  
INSERT: 'Let |cur_h| be the position of the first box, and set |leader_wd+lx|     to the spacing between corresponding parts of boxes'
; 
  while cur_h+leader_wd<=edge do 
    
INSERT: 'Output a leader box at |cur_h|,       then advance |cur_h| by |leader_wd+lx|'
; 
  cur_h:=edge-10; goto next_p; 
  end; 
end 

MODULE: 'Let |cur_h| be the position of the first box, ...'
(*PASCAL module 627*)
if subtype(p)=a_leaders then 
  begin save_h:=cur_h; 
  cur_h:=left_edge+leader_wd*((cur_h-left_edge)div leader_wd); 
  if cur_h<save_h then cur_h:=cur_h+leader_wd; 
  end 
else  begin lq:=rule_wd div leader_wd; {the number of box copies} 
  lr:=rule_wd mod leader_wd; {the remaining space} 
  if subtype(p)=c_leaders then cur_h:=cur_h+(lr div 2) 
  else  begin lx:=lr div (lq+1); 
    cur_h:=cur_h+((lr-(lq-1)*lx) div 2); 
    end; 
  end 

MODULE: 'Output a leader box at |cur_h|, ...'
(*PASCAL module 628*)
begin cur_v:=base_line+shift_amount(leader_box); synch_v; save_v:=dvi_v;
 
synch_h; save_h:=dvi_h; temp_ptr:=leader_box; 
outer_doing_leaders:=doing_leaders; doing_leaders:=true; 
if type(leader_box)=vlist_node then vlist_outelse hlist_out; 
doing_leaders:=outer_doing_leaders; 
dvi_v:=save_v; dvi_h:=save_h; cur_v:=base_line; 
cur_h:=save_h+leader_wd+lx; 
end 

MODULE: 'Output node |p| for |vlist_out|...'
(*PASCAL module 630*)
begin if is_char_node(p) then confusion('vlistout') 
(*this can''t happen vlistout][\quad vlistout*) 
else 
INSERT: 'Output the non-|char_node| |p| for |vlist_out|'
; 
next_p:p:=link(p); 
end 

MODULE: 'Output the non-|char_node| |p| for |vlist_out|'
(*PASCAL module 631*)
begin case type(p) of 
hlist_node,vlist_node:
INSERT: 'Output a box in a vlist'
; 
rule_node: begin rule_ht:=height(p); rule_dp:=depth(p); rule_wd:=width(p); 
  goto fin_rule; 
  end; 
whatsit_node: 
INSERT: 'Output the whatsit node |p| in a vlist'
; 
glue_node: 
INSERT: 'Move down or output leaders'
; 
kern_node:cur_v:=cur_v+width(p); 
othercases do_nothing 
endcases;
 
goto next_p; 
fin_rule: 
INSERT: 'Output a rule in a vlist, |goto next_p|'
; 
move_past: cur_v:=cur_v+rule_ht; 
end 

MODULE: 'Output a box in a vlist'
(*PASCAL module 632*)
if list_ptr(p)=null then cur_v:=cur_v+height(p)+depth(p) 
else  begin cur_v:=cur_v+height(p); synch_v; 
  save_h:=dvi_h; save_v:=dvi_v; 
  cur_h:=left_edge+shift_amount(p); {shift the box right} 
  temp_ptr:=p; 
  if type(p)=vlist_node then vlist_outelse hlist_out; 
  dvi_h:=save_h; dvi_v:=save_v; 
  cur_v:=save_v+depth(p); cur_h:=left_edge; 
  end 

MODULE: 'Output a rule in a vlist...'
(*PASCAL module 633*)
if is_running(rule_wd) then rule_wd:=width(this_box); 
rule_ht:=rule_ht+rule_dp; {this is the rule thickness} 
cur_v:=cur_v+rule_ht; 
if (rule_ht>0)and(rule_wd>0) then {we don't output empty rules} 
  begin synch_h; synch_v; 
  dvi_out(put_rule); dvi_four(rule_ht); dvi_four(rule_wd); 
  end; 
goto next_p 

MODULE: 'Move down or output leaders'
(*PASCAL module 634*)
begin g:=glue_ptr(p); rule_ht:=width(g)-cur_g; 
if g_sign<>normal then 
  begin if g_sign=stretching then 
    begin if stretch_order(g)=g_order then 
      begin cur_glue:=cur_glue+stretch(g); 
      vet_glue(float(glue_set(this_box))*cur_glue); 
(*real multiplication*) 
      cur_g:=round(glue_temp); 
      end; 
    end 
  else if shrink_order(g)=g_order then 
      begin cur_glue:=cur_glue-shrink(g); 
      vet_glue(float(glue_set(this_box))*cur_glue); 
      cur_g:=round(glue_temp); 
      end; 
  end; 
rule_ht:=rule_ht+cur_g; 
if subtype(p)>=a_leaders then 
  
INSERT: 'Output leaders in a vlist, |goto fin_rule| if a rule     or to |next_p| if done'
; 
goto move_past; 
end 

MODULE: 'Output leaders in a vlist...'
(*PASCAL module 635*)
begin leader_box:=leader_ptr(p); 
if type(leader_box)=rule_node then 
  begin rule_wd:=width(leader_box); rule_dp:=0; 
  goto fin_rule; 
  end; 
leader_ht:=height(leader_box)+depth(leader_box); 
if (leader_ht>0)and(rule_ht>0) then 
  begin rule_ht:=rule_ht+10; {compensate for floating-point rounding} 
  edge:=cur_v+rule_ht; lx:=0; 
  
INSERT: 'Let |cur_v| be the position of the first box, and set |leader_ht+lx|     to the spacing between corresponding parts of boxes'
; 
  while cur_v+leader_ht<=edge do 
    
INSERT: 'Output a leader box at |cur_v|,       then advance |cur_v| by |leader_ht+lx|'
; 
  cur_v:=edge-10; goto next_p; 
  end; 
end 

MODULE: 'Let |cur_v| be the position of the first box, ...'
(*PASCAL module 636*)
if subtype(p)=a_leaders then 
  begin save_v:=cur_v; 
  cur_v:=top_edge+leader_ht*((cur_v-top_edge)div leader_ht); 
  if cur_v<save_v then cur_v:=cur_v+leader_ht; 
  end 
else  begin lq:=rule_ht div leader_ht; {the number of box copies} 
  lr:=rule_ht mod leader_ht; {the remaining space} 
  if subtype(p)=c_leaders then cur_v:=cur_v+(lr div 2) 
  else  begin lx:=lr div (lq+1); 
    cur_v:=cur_v+((lr-(lq-1)*lx) div 2); 
    end; 
  end 

MODULE: 'Output a leader box at |cur_v|, ...'
(*PASCAL module 637*)
begin cur_h:=left_edge+shift_amount(leader_box); synch_h; save_h:=dvi_h;
 
cur_v:=cur_v+height(leader_box); synch_v; save_v:=dvi_v; 
temp_ptr:=leader_box; 
outer_doing_leaders:=doing_leaders; doing_leaders:=true; 
if type(leader_box)=vlist_node then vlist_outelse hlist_out; 
doing_leaders:=outer_doing_leaders; 
dvi_v:=save_v; dvi_h:=save_h; cur_h:=left_edge; 
cur_v:=save_v-height(leader_box)+leader_ht+lx; 
end 

MODULE: 'Flush the box from memory, showing statistics if requested'
(*PASCAL module 639*)
stat if tracing_stats>1 then 
  begin print_nl('Memory usage before: '); 
(*Memory usage...*) 
  print_int(var_used); print_char('&'); 
  print_int(dyn_used); print_char(';'); 
  end; 
tats
 
flush_node_list(p); 
stat if tracing_stats>1 then 
  begin print(' after: '); 
  print_int(var_used); print_char('&'); 
  print_int(dyn_used); print('; still untouched: '); 
  print_int(hi_mem_min-lo_mem_max-1); print_ln; 
  end; 
tats 

MODULE: 'Ship box |p| out'
(*PASCAL module 640*)

INSERT: 'Update the values of |max_h| and |max_v|; but if the page is too large,   |goto done|'
; 

INSERT: 'Initialize variables as |ship_out| begins'
; 
page_loc:=dvi_offset+dvi_ptr; 
dvi_out(bop); 
for k:=0 to 9 do dvi_four(count(k)); 
dvi_four(last_bop); last_bop:=page_loc; 
cur_v:=height(p)+v_offset; temp_ptr:=p; 
if type(p)=vlist_node then vlist_outelse hlist_out; 
dvi_out(eop); incr(total_pages); cur_s:=-1; 
done: 

MODULE: 'Update the values of |max_h| and |max_v|; but if the page is too large...'
(*PASCAL module 641*)
if (height(p)>max_dimen)or(depth(p)>max_dimen)or 
   (height(p)+depth(p)+v_offset>max_dimen)or 
   (width(p)+h_offset>max_dimen) then 
  begin print_err('Huge page cannot be shipped out'); 
(*Huge page...*) 
  help2('The page just created is more than 18 feet tall or')
 
   ('more than 18 feet wide, so I suspect something went wrong.'); 
  error; 
  if tracing_output<=0 then 
    begin begin_diagnostic; 
    print_nl('The following box has been deleted:'); 
(*The following...deleted*) 
    show_box(p); 
    end_diagnostic(true); 
    end; 
  goto done; 
  end; 
if height(p)+depth(p)+v_offset>max_v then max_v:=height(p)+depth(p)+v_offset; 
if width(p)+h_offset>max_h then max_h:=width(p)+h_offset 

MODULE: 'Finish the \.{DVI} file'
(*PASCAL module 642*)
while cur_s>-1 do 
  begin if cur_s>0 then dvi_out(pop) 
  else  begin dvi_out(eop); incr(total_pages); 
    end; 
  decr(cur_s); 
  end; 
if total_pages=0 then print_nl('No pages of output.') 
(*No pages of output*) 
else  begin dvi_out(post); {beginning of the postamble} 
  dvi_four(last_bop); last_bop:=dvi_offset+dvi_ptr-5; {|post| location} 
  dvi_four(25400000); dvi_four(473628672); {conversion ratio for sp} 
  prepare_mag; dvi_four(mag); {magnification factor} 
  dvi_four(max_v); dvi_four(max_h);
 
  dvi_out(max_push div 256); dvi_out(max_push mod 256);
 
  dvi_out((total_pages div 256) mod 256); dvi_out(total_pages mod 256);
 
  
INSERT: 'Output the font definitions for all fonts that were used'
; 
  dvi_out(post_post); dvi_four(last_bop); dvi_out(id_byte);
 
  k:=4+((dvi_buf_size-dvi_ptr) mod 4); {the number of 223's} 
  while k>0 do 
    begin dvi_out(223); decr(k); 
    end; 
  
INSERT: 'Empty the last bytes out of |dvi_buf|'
; 
  print_nl('Output written on '); slow_print(output_file_name); 
(*Output written on x*) 
  print(' ('); print_int(total_pages); print(' page'); 
  if total_pages<>1 then print_char('s'); 
  print(', '); print_int(dvi_offset+dvi_ptr); print(' bytes).'); 
  b_close(dvi_file); 
  end 

MODULE: 'Output the font definitions...'
(*PASCAL module 643*)
while font_ptr>font_base do 
  begin if font_used[font_ptr] then dvi_font_def(font_ptr); 
  decr(font_ptr); 
  end 

MODULE: 'Glob... '
(*PASCAL module 646*)
total_stretch, total_shrink: array[glue_ord] of scaled; 
  {glue found by |hpack| or |vpack|} 
last_badness:integer; {badness of the most recently packaged box} 

MODULE: 'Glob...'
(*PASCAL module 647*)
adjust_tail:pointer; {tail of adjustment list} 

MODULE: 'Clear dimensions to zero'
(*PASCAL module 650*)
d:=0; x:=0; 
total_stretch[normal]:=0; total_shrink[normal]:=0; 
total_stretch[fil]:=0; total_shrink[fil]:=0; 
total_stretch[fill]:=0; total_shrink[fill]:=0; 
total_stretch[filll]:=0; total_shrink[filll]:=0 

MODULE: 'Examine node |p| in the hlist, taking account of its effect...'
(*PASCAL module 651*)
(*inner loop*) 
begin reswitch: while is_char_node(p) do 
  
INSERT: 'Incorporate character dimensions into the dimensions of     the hbox that will contain~it, then move to the next node'
; 
if p<>null then 
  begin case type(p) of 
  hlist_node,vlist_node,rule_node,unset_node: 
    
INSERT: 'Incorporate box dimensions into the dimensions of       the hbox that will contain~it'
; 
  ins_node,mark_node,adjust_node: if adjust_tail<>null then 
    
INSERT: 'Transfer node |p| to the adjustment list'
; 
  whatsit_node:
INSERT: 'Incorporate a whatsit node into an hbox'
; 
  glue_node:
INSERT: 'Incorporate glue into the horizontal totals'
; 
  kern_node,math_node: x:=x+width(p); 
  ligature_node: 
INSERT: 'Make node |p| look like a |char_node|     and |goto reswitch|'
; 
  othercases do_nothing 
  endcases;
 
  p:=link(p); 
  end; 
end 


MODULE: 'Make node |p| look like a |char_node| and |goto reswitch|'
(*PASCAL module 652*)
begin mem[lig_trick]:=mem[lig_char(p)]; link(lig_trick):=link(p); 
p:=lig_trick; goto reswitch; 
end 

MODULE: 'Incorporate box dimensions into the dimensions of the hbox...'
(*PASCAL module 653*)
begin x:=x+width(p); 
if type(p)>=rule_node then s:=0 else s:=shift_amount(p); 
if height(p)-s>h then h:=height(p)-s; 
if depth(p)+s>d then d:=depth(p)+s; 
end 

MODULE: 'Incorporate character dimensions into the dimensions of the hbox...'
(*PASCAL module 654*)
begin f:=font(p); i:=char_info(f)(character(p)); hd:=height_depth(i); 
x:=x+char_width(f)(i);
 
s:=char_height(f)(hd);if s>h then h:=s; 
s:=char_depth(f)(hd);if s>d then d:=s; 
p:=link(p); 
end 

MODULE: 'Transfer node |p| to the adjustment list'
(*PASCAL module 655*)
begin while link(q)<>p do q:=link(q); 
if type(p)=adjust_node then 
  begin link(adjust_tail):=adjust_ptr(p); 
  while link(adjust_tail)<>null do adjust_tail:=link(adjust_tail); 
  p:=link(p); free_node(link(q),small_node_size); 
  end 
else  begin link(adjust_tail):=p; adjust_tail:=p; p:=link(p); 
  end; 
link(q):=p; p:=q; 
end 

MODULE: 'Incorporate glue into the horizontal totals'
(*PASCAL module 656*)
begin g:=glue_ptr(p); x:=x+width(g);
 
o:=stretch_order(g); total_stretch[o]:=total_stretch[o]+stretch(g); 
o:=shrink_order(g); total_shrink[o]:=total_shrink[o]+shrink(g); 
if subtype(p)>=a_leaders then 
  begin g:=leader_ptr(p); 
  if height(g)>h then h:=height(g); 
  if depth(g)>d then d:=depth(g); 
  end; 
end 

MODULE: 'Determine the value of |width(r)| and the appropriate glue setting...'
(*PASCAL module 657*)
if m=additional then w:=x+w; 
width(r):=w; x:=w-x; {now |x| is the excess to be made up} 
if x=0 then 
  begin glue_sign(r):=normal; glue_order(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); 
  return; 
  end 
else if x>0 then 
INSERT: 'Determine horizontal glue stretch setting, then |return|     or \hbox{|goto common_ending|}'

else 
INSERT: 'Determine horizontal glue shrink setting, then |return|     or \hbox{|goto common_ending|}'


MODULE: 'Determine horizontal glue stretch setting...'
(*PASCAL module 658*)
begin 
INSERT: 'Determine the stretch order'
; 
glue_order(r):=o; glue_sign(r):=stretching; 
if total_stretch[o]<>0 then glue_set(r):=unfloat(x/total_stretch[o]) 
(*real division*) 
else  begin glue_sign(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); {there's nothing to stretch} 
  end; 
if o=normal then if list_ptr(r)<>null then 
  
INSERT: 'Report an underfull hbox and |goto common_ending|, if this box     is sufficiently bad'
; 
return; 
end 

MODULE: 'Determine the stretch order'
(*PASCAL module 659*)
if total_stretch[filll]<>0 then o:=filll 
else if total_stretch[fill]<>0 then o:=fill 
else if total_stretch[fil]<>0 then o:=fil 
else o:=normal 

MODULE: 'Report an underfull hbox and |goto common_ending|, if...'
(*PASCAL module 660*)
begin last_badness:=badness(x,total_stretch[normal]); 
if last_badness>hbadness then 
  begin print_ln; 
  if last_badness>100 then print_nl('Underfull')else print_nl('Loose'); 
  print(' \hbox (badness '); print_int(last_badness); 
(*Underfull \\hbox...*) 
(*Loose \\hbox...*) 
  goto common_ending; 
  end; 
end 

MODULE: 'Glob... '
(*PASCAL module 661*)
pack_begin_line:integer; {source file line where the current paragraph 
  or alignment began; a negative value denotes alignment} 

MODULE: 'Set init...'
(*PASCAL module 662*)
pack_begin_line:=0; 

MODULE: 'Finish issuing a diagnostic message for an overfull or underfull hbox'
(*PASCAL module 663*)
if output_active then print(') has occurred while \output is active') 
else  begin if pack_begin_line<>0 then 
    begin if pack_begin_line>0 then print(') in paragraph at lines ') 
    else print(') in alignment at lines '); 
    print_int(abs(pack_begin_line)); 
    print('--'); 
    end 
  else print(') detected at line '); 
  print_int(line); 
  end; 
print_ln;
 
font_in_short_display:=null_font; short_display(list_ptr(r)); print_ln;
 
begin_diagnostic; show_box(r); end_diagnostic(true) 

MODULE: 'Determine horizontal glue shrink setting...'
(*PASCAL module 664*)
begin 
INSERT: 'Determine the shrink order'
; 
glue_order(r):=o; glue_sign(r):=shrinking; 
if total_shrink[o]<>0 then glue_set(r):=unfloat((-x)/total_shrink[o]) 
(*real division*) 
else  begin glue_sign(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); {there's nothing to shrink} 
  end; 
if (total_shrink[o]<-x)and(o=normal)and(list_ptr(r)<>null) then 
  begin last_badness:=1000000; 
  set_glue_ratio_one(glue_set(r)); {use the maximum shrinkage} 
  
INSERT: 'Report an overfull hbox and |goto common_ending|, if this box     is sufficiently bad'
; 
  end 
else if o=normal then if list_ptr(r)<>null then 
  
INSERT: 'Report a tight hbox and |goto common_ending|, if this box     is sufficiently bad'
; 
return; 
end 

MODULE: 'Determine the shrink order'
(*PASCAL module 665*)
if total_shrink[filll]<>0 then o:=filll 
else if total_shrink[fill]<>0 then o:=fill 
else if total_shrink[fil]<>0 then o:=fil 
else o:=normal 

MODULE: 'Report an overfull hbox and |goto common_ending|, if...'
(*PASCAL module 666*)
if (-x-total_shrink[normal]>hfuzz)or(hbadness<100) then 
  begin if (overfull_rule>0)and(-x-total_shrink[normal]>hfuzz) then 
    begin while link(q)<>null do q:=link(q); 
    link(q):=new_rule; 
    width(link(q)):=overfull_rule; 
    end; 
  print_ln; print_nl('Overfull \hbox ('); 
(*Overfull \\hbox...*) 
  print_scaled(-x-total_shrink[normal]); print('pt too wide'); 
  goto common_ending; 
  end 

MODULE: 'Report a tight hbox and |goto common_ending|, if...'
(*PASCAL module 667*)
begin last_badness:=badness(-x,total_shrink[normal]); 
if last_badness>hbadness then 
  begin print_ln; print_nl('Tight \hbox (badness '); print_int(last_badness); 
(*Tight \\hbox...*) 
  goto common_ending; 
  end; 
end 

MODULE: 'Examine node |p| in the vlist, taking account of its effect...'
(*PASCAL module 669*)
begin if is_char_node(p) then confusion('vpack') 
(*this can''t happen vpack][\quad vpack*) 
else  case type(p) of 
  hlist_node,vlist_node,rule_node,unset_node: 
    
INSERT: 'Incorporate box dimensions into the dimensions of       the vbox that will contain~it'
; 
  whatsit_node:
INSERT: 'Incorporate a whatsit node into a vbox'
; 
  glue_node: 
INSERT: 'Incorporate glue into the vertical totals'
; 
  kern_node: begin x:=x+d+width(p); d:=0; 
    end; 
  othercases do_nothing 
  endcases; 
p:=link(p); 
end 

MODULE: 'Incorporate box dimensions into the dimensions of the vbox...'
(*PASCAL module 670*)
begin x:=x+d+height(p); d:=depth(p); 
if type(p)>=rule_node then s:=0 else s:=shift_amount(p); 
if width(p)+s>w then w:=width(p)+s; 
end 

MODULE: 'Incorporate glue into the vertical totals'
(*PASCAL module 671*)
begin x:=x+d; d:=0;
 
g:=glue_ptr(p); x:=x+width(g);
 
o:=stretch_order(g); total_stretch[o]:=total_stretch[o]+stretch(g); 
o:=shrink_order(g); total_shrink[o]:=total_shrink[o]+shrink(g); 
if subtype(p)>=a_leaders then 
  begin g:=leader_ptr(p); 
  if width(g)>w then w:=width(g); 
  end; 
end 

MODULE: 'Determine the value of |height(r)| and the appropriate glue setting...'
(*PASCAL module 672*)
if m=additional then h:=x+h; 
height(r):=h; x:=h-x; {now |x| is the excess to be made up} 
if x=0 then 
  begin glue_sign(r):=normal; glue_order(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); 
  return; 
  end 
else if x>0 then 
INSERT: 'Determine vertical glue stretch setting, then |return|     or \hbox{|goto common_ending|}'

else 
INSERT: 'Determine vertical glue shrink setting, then |return|     or \hbox{|goto common_ending|}'


MODULE: 'Determine vertical glue stretch setting...'
(*PASCAL module 673*)
begin 
INSERT: 'Determine the stretch order'
; 
glue_order(r):=o; glue_sign(r):=stretching; 
if total_stretch[o]<>0 then glue_set(r):=unfloat(x/total_stretch[o]) 
(*real division*) 
else  begin glue_sign(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); {there's nothing to stretch} 
  end; 
if o=normal then if list_ptr(r)<>null then 
  
INSERT: 'Report an underfull vbox and |goto common_ending|, if this box     is sufficiently bad'
; 
return; 
end 

MODULE: 'Report an underfull vbox and |goto common_ending|, if...'
(*PASCAL module 674*)
begin last_badness:=badness(x,total_stretch[normal]); 
if last_badness>vbadness then 
  begin print_ln; 
  if last_badness>100 then print_nl('Underfull')else print_nl('Loose'); 
  print(' \vbox (badness '); print_int(last_badness); 
(*Underfull \\vbox...*) 
(*Loose \\vbox...*) 
  goto common_ending; 
  end; 
end 

MODULE: 'Finish issuing a diagnostic message for an overfull or underfull vbox'
(*PASCAL module 675*)
if output_active then print(') has occurred while \output is active') 
else  begin if pack_begin_line<>0 then {it's actually negative} 
    begin print(') in alignment at lines '); 
    print_int(abs(pack_begin_line)); 
    print('--'); 
    end 
  else print(') detected at line '); 
  print_int(line); 
  print_ln;
 
  end; 
begin_diagnostic; show_box(r); end_diagnostic(true) 

MODULE: 'Determine vertical glue shrink setting...'
(*PASCAL module 676*)
begin 
INSERT: 'Determine the shrink order'
; 
glue_order(r):=o; glue_sign(r):=shrinking; 
if total_shrink[o]<>0 then glue_set(r):=unfloat((-x)/total_shrink[o]) 
(*real division*) 
else  begin glue_sign(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); {there's nothing to shrink} 
  end; 
if (total_shrink[o]<-x)and(o=normal)and(list_ptr(r)<>null) then 
  begin last_badness:=1000000; 
  set_glue_ratio_one(glue_set(r)); {use the maximum shrinkage} 
  
INSERT: 'Report an overfull vbox and |goto common_ending|, if this box     is sufficiently bad'
; 
  end 
else if o=normal then if list_ptr(r)<>null then 
  
INSERT: 'Report a tight vbox and |goto common_ending|, if this box     is sufficiently bad'
; 
return; 
end 

MODULE: 'Report an overfull vbox and |goto common_ending|, if...'
(*PASCAL module 677*)
if (-x-total_shrink[normal]>vfuzz)or(vbadness<100) then 
  begin print_ln; print_nl('Overfull \vbox ('); 
(*Overfull \\vbox...*) 
  print_scaled(-x-total_shrink[normal]); print('pt too high'); 
  goto common_ending; 
  end 

MODULE: 'Report a tight vbox and |goto common_ending|, if...'
(*PASCAL module 678*)
begin last_badness:=badness(-x,total_shrink[normal]); 
if last_badness>vbadness then 
  begin print_ln; print_nl('Tight \vbox (badness '); print_int(last_badness); 
(*Tight \\vbox...*) 
  goto common_ending; 
  end; 
end 

MODULE: 'Glob... '
(*PASCAL module 684*)
empty_field:two_halves; 
null_delimiter:four_quarters; 

MODULE: 'Set init...'
(*PASCAL module 685*)
empty_field.rh:=empty; empty_field.lh:=null;
 
null_delimiter.b0:=0; null_delimiter.b1:=min_quarterword;
 
null_delimiter.b2:=0; null_delimiter.b3:=min_quarterword; 

MODULE: 'Cases of |show_node_list| that arise...'
(*PASCAL module 690*)
style_node:print_style(subtype(p)); 
choice_node:
INSERT: 'Display choice node |p|'
; 
ord_noad,op_noad,bin_noad,rel_noad,open_noad,close_noad,punct_noad,inner_noad, 
  radical_noad,over_noad,under_noad,vcenter_noad,accent_noad, 
  left_noad,right_noad:
INSERT: 'Display normal noad |p|'
; 
fraction_noad:
INSERT: 'Display fraction noad |p|'
; 

MODULE: 'Declare procedures needed for displaying the elements of mlists'
(*PASCAL module 691*)
procedure print_fam_and_char(p:pointer); {prints family and character} 
begin print_esc('fam'); print_int(fam(p)); print_char(' '); 
print_ASCII(qo(character(p))); 
end; 


 
procedure print_delimiter(p:pointer); {prints a delimiter as 24-bit hex value} 
var a:integer; {accumulator} 
begin a:=small_fam(p)*256+qo(small_char(p)); 
a:=a*512+large_fam(p)*256+qo(large_char(p)); 
if a<0 then print_int(a) {this should never happen} 
else print_hex(a); 
end; 

MODULE: 'Declare procedures needed for displaying...'
(*PASCAL module 692*)
procedure show_info; forward;(*\2*) {|show_node_list(info(temp_ptr))|} 
procedure print_subsidiary_data(p:pointer;c:ASCII_code); 
  {display a noad field} 
begin if cur_length>=depth_threshold then 
  begin if math_type(p)<>empty then print(' []'); 
  end 
else  begin append_char(c); {include |c| in the recursion history} 
  temp_ptr:=p; {prepare for |show_info| if recursion is needed} 
  case math_type(p) of 
  math_char: begin print_ln; print_current_string; print_fam_and_char(p); 
    end; 
  sub_box: show_info; {recursive call} 
  sub_mlist: if info(p)=null then 
      begin print_ln; print_current_string; print('{}'); 
      end 
    else show_info; {recursive call} 
  othercases do_nothing {|empty|} 
  endcases;
 
  flush_char; {remove |c| from the recursion history} 
  end; 
end; 

MODULE: 'Declare procedures needed for displaying...'
(*PASCAL module 694*)
procedure print_style(c:integer); 
begin case c div 2 of 
0: print_esc('displaystyle'); {|display_style=0|} 
1: print_esc('textstyle'); {|text_style=2|} 
2: print_esc('scriptstyle'); {|script_style=4|} 
3: print_esc('scriptscriptstyle'); {|script_script_style=6|} 
othercases print('Unknown style!') 
endcases; 
end; 

MODULE: 'Display choice node |p|'
(*PASCAL module 695*)
begin print_esc('mathchoice'); 
append_char('D'); show_node_list(display_mlist(p)); flush_char; 
append_char('T'); show_node_list(text_mlist(p)); flush_char; 
append_char('S'); show_node_list(script_mlist(p)); flush_char; 
append_char('s'); show_node_list(script_script_mlist(p)); flush_char; 
end 

MODULE: 'Display normal noad |p|'
(*PASCAL module 696*)
begin case type(p) of 
ord_noad: print_esc('mathord'); 
op_noad: print_esc('mathop'); 
bin_noad: print_esc('mathbin'); 
rel_noad: print_esc('mathrel'); 
open_noad: print_esc('mathopen'); 
close_noad: print_esc('mathclose'); 
punct_noad: print_esc('mathpunct'); 
inner_noad: print_esc('mathinner'); 
over_noad: print_esc('overline'); 
under_noad: print_esc('underline'); 
vcenter_noad: print_esc('vcenter'); 
radical_noad: begin print_esc('radical'); print_delimiter(left_delimiter(p)); 
  end; 
accent_noad: begin print_esc('accent'); print_fam_and_char(accent_chr(p)); 
  end; 
left_noad: begin print_esc('left'); print_delimiter(delimiter(p)); 
  end; 
right_noad: begin print_esc('right'); print_delimiter(delimiter(p)); 
  end; 
end; 
if subtype(p)<>normal then 
  if subtype(p)=limits then print_esc('limits') 
  else print_esc('nolimits'); 
if type(p)<left_noad then print_subsidiary_data(nucleus(p),'.'); 
print_subsidiary_data(supscr(p),'^'); 
print_subsidiary_data(subscr(p),'_'); 
end 

MODULE: 'Display fraction noad |p|'
(*PASCAL module 697*)
begin print_esc('fraction, thickness '); 
if thickness(p)=default_code then print('= default') 
else print_scaled(thickness(p)); 
if (small_fam(left_delimiter(p))<>0)or 
  (small_char(left_delimiter(p))<>min_quarterword)or 
  (large_fam(left_delimiter(p))<>0)or 
  (large_char(left_delimiter(p))<>min_quarterword) then 
  begin print(', left-delimiter '); print_delimiter(left_delimiter(p)); 
  end; 
if (small_fam(right_delimiter(p))<>0)or 
  (small_char(right_delimiter(p))<>min_quarterword)or 
  (large_fam(right_delimiter(p))<>0)or 
  (large_char(right_delimiter(p))<>min_quarterword) then 
  begin print(', right-delimiter '); print_delimiter(right_delimiter(p)); 
  end; 
print_subsidiary_data(numerator(p),'\'); 
print_subsidiary_data(denominator(p),'/'); 
end 

MODULE: 'Cases of |flush_node_list| that arise...'
(*PASCAL module 698*)
style_node: begin free_node(p,style_node_size); goto done; 
  end; 
choice_node:begin flush_node_list(display_mlist(p)); 
  flush_node_list(text_mlist(p)); 
  flush_node_list(script_mlist(p)); 
  flush_node_list(script_script_mlist(p)); 
  free_node(p,style_node_size); goto done; 
  end; 
ord_noad,op_noad,bin_noad,rel_noad,open_noad,close_noad,punct_noad,inner_noad, 
  radical_noad,over_noad,under_noad,vcenter_noad,accent_noad:(**);
 
  begin if math_type(nucleus(p))>=sub_box then 
    flush_node_list(info(nucleus(p))); 
  if math_type(supscr(p))>=sub_box then 
    flush_node_list(info(supscr(p))); 
  if math_type(subscr(p))>=sub_box then 
    flush_node_list(info(subscr(p))); 
  if type(p)=radical_noad then free_node(p,radical_noad_size) 
  else if type(p)=accent_noad then free_node(p,accent_noad_size) 
  else free_node(p,noad_size); 
  goto done; 
  end; 
left_noad,right_noad: begin free_node(p,noad_size); goto done; 
  end; 
fraction_noad: begin flush_node_list(info(numerator(p))); 
  flush_node_list(info(denominator(p))); 
  free_node(p,fraction_noad_size); goto done; 
  end; 

MODULE: 'Basic printing procedures'
(*PASCAL module 699*)
procedure print_size(s:integer); 
begin if s=text_size then print_esc('textfont') 
else if s=script_size then print_esc('scriptfont') 
else print_esc('scriptscriptfont'); 
end; 

MODULE: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
(*PASCAL module 703*)
begin if cur_style<script_style then cur_size:=text_size 
else cur_size:=16*((cur_style-text_style) div 2); 
cur_mu:=x_over_n(math_quad(cur_size),18); 
end 

MODULE: 'Look at the variants of |(z,x)|; set |f| and |c|...'
(*PASCAL module 707*)
if (z<>0)or(x<>min_quarterword) then 
  begin z:=z+s+16; 
  repeat z:=z-16; g:=fam_fnt(z); 
  if g<>null_font then 
    
INSERT: 'Look at the list of characters starting with |x| in       font |g|; set |f| and |c| whenever       a better character is found; |goto found| as soon as a       large enough variant is encountered'
; 
  until z<16; 
  end 

MODULE: 'Look at the list of characters starting with |x|...'
(*PASCAL module 708*)
begin y:=x; 
if (qo(y)>=font_bc[g])and(qo(y)<=font_ec[g]) then 
  begin continue: q:=char_info(g)(y); 
  if char_exists(q) then 
    begin if char_tag(q)=ext_tag then 
      begin f:=g; c:=y; goto found; 
      end; 
    hd:=height_depth(q); 
    u:=char_height(g)(hd)+char_depth(g)(hd); 
    if u>w then 
      begin f:=g; c:=y; w:=u; 
      if u>=v then goto found; 
      end; 
    if char_tag(q)=list_tag then 
      begin y:=rem_byte(q); goto continue; 
      end; 
    end; 
  end; 
end 

MODULE: 'Declare subprocedures for |var_delimiter|'
(*PASCAL module 709*)
function char_box(f:internal_font_number;c:quarterword):pointer; 
var q:four_quarters; 
hd:eight_bits; {|height_depth| byte} 
b,p:pointer; {the new box and its character node} 
begin q:=char_info(f)(c); hd:=height_depth(q); 
b:=new_null_box; width(b):=char_width(f)(q)+char_italic(f)(q); 
height(b):=char_height(f)(hd); depth(b):=char_depth(f)(hd); 
p:=get_avail; character(p):=c; font(p):=f; list_ptr(b):=p; char_box:=b; 
end; 

MODULE: 'Make variable |b| point to a box for |(f,c)|'
(*PASCAL module 710*)
if char_tag(q)=ext_tag then 
  
INSERT: 'Construct an extensible character in a new box |b|,     using recipe |rem_byte(q)| and font |f|'

else b:=char_box(f,c) 

MODULE: 'Declare subprocedures for |var_delimiter|'
(*PASCAL module 711*)
procedure stack_into_box(b:pointer;f:internal_font_number; 
  c:quarterword); 
var p:pointer; {new node placed into |b|} 
begin p:=char_box(f,c); link(p):=list_ptr(b); list_ptr(b):=p; 
height(b):=height(p); 
end; 

MODULE: 'Declare subprocedures for |var_delimiter|'
(*PASCAL module 712*)
function height_plus_depth(f:internal_font_number;c:quarterword):scaled; 
var q:four_quarters; 
hd:eight_bits; {|height_depth| byte} 
begin q:=char_info(f)(c); hd:=height_depth(q); 
height_plus_depth:=char_height(f)(hd)+char_depth(f)(hd); 
end; 

MODULE: 'Construct an extensible...'
(*PASCAL module 713*)
begin b:=new_null_box; 
type(b):=vlist_node; 
r:=font_info[exten_base[f]+rem_byte(q)].qqqq;
 

INSERT: 'Compute the minimum suitable height, |w|, and the corresponding   number of extension steps, |n|; also set |width(b)|'
; 
c:=ext_bot(r); 
if c<>min_quarterword then stack_into_box(b,f,c); 
c:=ext_rep(r); 
for m:=1 to n do stack_into_box(b,f,c); 
c:=ext_mid(r); 
if c<>min_quarterword then 
  begin stack_into_box(b,f,c); c:=ext_rep(r); 
  for m:=1 to n do stack_into_box(b,f,c); 
  end; 
c:=ext_top(r); 
if c<>min_quarterword then stack_into_box(b,f,c); 
depth(b):=w-height(b); 
end 

MODULE: 'Compute the minimum suitable height, |w|, and...'
(*PASCAL module 714*)
c:=ext_rep(r); u:=height_plus_depth(f,c); 
w:=0; q:=char_info(f)(c); width(b):=char_width(f)(q)+char_italic(f)(q);
 
c:=ext_bot(r);if c<>min_quarterword then w:=w+height_plus_depth(f,c); 
c:=ext_mid(r);if c<>min_quarterword then w:=w+height_plus_depth(f,c); 
c:=ext_top(r);if c<>min_quarterword then w:=w+height_plus_depth(f,c); 
n:=0; 
if u>0 then while w<v do 
  begin w:=w+u; incr(n); 
  if ext_mid(r)<>min_quarterword then w:=w+u; 
  end 

MODULE: 'Glob... '
(*PASCAL module 719*)
cur_mlist:pointer; {beginning of mlist to be translated} 
cur_style:small_number; {style code at current place in the list} 
cur_size:small_number; {size code corresponding to |cur_style|} 
cur_mu:scaled; {the math unit width corresponding to |cur_size|} 
mlist_penalties:boolean; {should |mlist_to_hlist| insert penalties?} 

MODULE: 'Simplify a trivial box'
(*PASCAL module 721*)
q:=list_ptr(x); 
if is_char_node(q) then 
  begin r:=link(q); 
  if r<>null then if link(r)=null then if not is_char_node(r) then 
   if type(r)=kern_node then {unneeded italic correction} 
    begin free_node(r,small_node_size); link(q):=null; 
    end; 
  end 

MODULE: 'Complain about an undefined family...'
(*PASCAL module 723*)
begin print_err(''); print_size(cur_size); print_char(' '); 
print_int(fam(a)); print(' is undefined (character '); 
print_ASCII(qo(cur_c)); print_char(')'); 
help4('Somewhere in the math formula just ended, you used the')
 
('stated character from an undefined font family. For example,')
 
('plain TeX doesn''t allow \it or \sl in subscripts. Proceed,')
 
('and I''ll try to forget that I needed that character.'); 
error; cur_i:=null_character; math_type(a):=empty; 
end 

MODULE: 'Glob... '
(*PASCAL module 724*)
cur_f:internal_font_number; {the |font| field of a |math_char|} 
cur_c:quarterword; {the |character| field of a |math_char|} 
cur_i:four_quarters; {the |char_info| of a |math_char|, 
  or a lig/kern instruction} 

MODULE: 'Process node-or-noad...'
(*PASCAL module 727*)
begin 
INSERT: 'Do first-pass processing based on |type(q)|; |goto done_with_noad|   if a noad has been fully processed, |goto check_dimensions| if it   has been translated into |new_hlist(q)|, or |goto done_with_node|   if a node has been fully processed'
; 
check_dimensions: z:=hpack(new_hlist(q),natural); 
if height(z)>max_h then max_h:=height(z); 
if depth(z)>max_d then max_d:=depth(z); 
free_node(z,box_node_size); 
done_with_noad: r:=q; r_type:=type(r); 
done_with_node: q:=link(q); 
end 

MODULE: 'Do first-pass processing...'
(*PASCAL module 728*)
reswitch: delta:=0; 
case type(q) of 
bin_noad: case r_type of 
  bin_noad,op_noad,rel_noad,open_noad,punct_noad,left_noad: 
    begin type(q):=ord_noad; goto reswitch; 
    end; 
  othercases do_nothing 
  endcases; 
rel_noad,close_noad,punct_noad,right_noad: begin(**);
 
  
INSERT: 'Convert \(a)a final |bin_noad| to an |ord_noad|'
; 
  if type(q)=right_noad then goto done_with_noad; 
  end; 
(*\4*)
INSERT: 'Cases for noads that can follow a |bin_noad|'
; 
(*\4*)
INSERT: 'Cases for nodes that can appear in an mlist, after which we   |goto done_with_node|'
; 
othercases confusion('mlist1') 
(*this can''t happen mlist1][\quad mlist1*) 
endcases;
 

INSERT: 'Convert \(n)|nucleus(q)| to an hlist and attach the sub/superscripts'


MODULE: 'Convert \(a)a final |bin_noad| to an |ord_noad|'
(*PASCAL module 729*)
if r_type=bin_noad then type(r):=ord_noad 

MODULE: 'Cases for nodes that can appear in an mlist...'
(*PASCAL module 730*)
style_node: begin cur_style:=subtype(q); 
  
INSERT: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
; 
  goto done_with_node; 
  end; 
choice_node: 
INSERT: 'Change this node to a style node followed by the correct choice,    then |goto done_with_node|'
; 
ins_node,mark_node,adjust_node, 
  whatsit_node,penalty_node,disc_node: goto done_with_node; 
rule_node: begin if height(q)>max_h then max_h:=height(q); 
  if depth(q)>max_d then max_d:=depth(q); goto done_with_node; 
  end; 
glue_node: begin 
INSERT: 'Convert \(m)math glue to ordinary glue'
; 
  goto done_with_node; 
  end; 
kern_node: begin math_kern(q,cur_mu); goto done_with_node; 
  end; 

MODULE: 'Change this node to a style node...'
(*PASCAL module 731*)
begin case cur_style div 2 of 
0: choose_mlist(display_mlist); {|display_style=0|} 
1: choose_mlist(text_mlist); {|text_style=2|} 
2: choose_mlist(script_mlist); {|script_style=4|} 
3: choose_mlist(script_script_mlist); {|script_script_style=6|} 
end; {there are no other cases} 
flush_node_list(display_mlist(q)); 
flush_node_list(text_mlist(q)); 
flush_node_list(script_mlist(q)); 
flush_node_list(script_script_mlist(q));
 
type(q):=style_node; subtype(q):=cur_style; width(q):=0; depth(q):=0; 
if p<>null then 
  begin z:=link(q); link(q):=p; 
  while link(p)<>null do p:=link(p); 
  link(p):=z; 
  end; 
goto done_with_node; 
end 

MODULE: 'Convert \(m)math glue to ordinary glue'
(*PASCAL module 732*)
if subtype(q)=mu_glue then 
  begin x:=glue_ptr(q); 
  y:=math_glue(x,cur_mu); delete_glue_ref(x); glue_ptr(q):=y; 
  subtype(q):=normal; 
  end 
else if (cur_size<>text_size)and(subtype(q)=cond_math_glue) then 
  begin p:=link(q); 
  if p<>null then if (type(p)=glue_node)or(type(p)=kern_node) then 
    begin link(q):=link(p); link(p):=null; flush_node_list(p); 
    end; 
  end 

MODULE: 'Cases for noads that can follow a |bin_noad|'
(*PASCAL module 733*)
left_noad: goto done_with_noad; 
fraction_noad: begin make_fraction(q); goto check_dimensions; 
  end; 
op_noad: begin delta:=make_op(q); 
  if subtype(q)=limits then goto check_dimensions; 
  end; 
ord_noad: make_ord(q); 
open_noad,inner_noad: do_nothing; 
radical_noad: make_radical(q); 
over_noad: make_over(q); 
under_noad: make_under(q); 
accent_noad: make_math_accent(q); 
vcenter_noad: make_vcenter(q); 

MODULE: 'Declare math...'
(*PASCAL module 734*)
procedure make_over(q:pointer); 
begin info(nucleus(q)):= 
  overbar(clean_box(nucleus(q),cramped_style(cur_style)), 
  3*default_rule_thickness,default_rule_thickness); 
math_type(nucleus(q)):=sub_box; 
end; 

MODULE: 'Declare math...'
(*PASCAL module 735*)
procedure make_under(q:pointer); 
var p,x,y: pointer; {temporary registers for box construction} 
delta:scaled; {overall height plus depth} 
begin x:=clean_box(nucleus(q),cur_style); 
p:=new_kern(3*default_rule_thickness); link(x):=p; 
link(p):=fraction_rule(default_rule_thickness); 
y:=vpack(x,natural); 
delta:=height(y)+depth(y)+default_rule_thickness; 
height(y):=height(x); depth(y):=delta-height(y); 
info(nucleus(q)):=y; math_type(nucleus(q)):=sub_box; 
end; 

MODULE: 'Declare math...'
(*PASCAL module 736*)
procedure make_vcenter(q:pointer); 
var v:pointer; {the box that should be centered vertically} 
delta:scaled; {its height plus depth} 
begin v:=info(nucleus(q)); 
if type(v)<>vlist_node then confusion('vcenter'); 
(*this can''t happen vcenter][\quad vcenter*) 
delta:=height(v)+depth(v); 
height(v):=axis_height(cur_size)+half(delta); 
depth(v):=delta-height(v); 
end; 

MODULE: 'Declare math...'
(*PASCAL module 737*)
procedure make_radical(q:pointer); 
var x,y:pointer; {temporary registers for box construction} 
delta,clr:scaled; {dimensions involved in the calculation} 
begin x:=clean_box(nucleus(q),cramped_style(cur_style)); 
if cur_style<text_style then {display style} 
  clr:=default_rule_thickness+(abs(math_x_height(cur_size)) div 4) 
else  begin clr:=default_rule_thickness; clr:=clr + (abs(clr) div 4); 
  end; 
y:=var_delimiter(left_delimiter(q),cur_size,height(x)+depth(x)+clr+ 
  default_rule_thickness); 
delta:=depth(y)-(height(x)+depth(x)+clr); 
if delta>0 then clr:=clr+half(delta); {increase the actual clearance} 
shift_amount(y):=-(height(x)+clr); 
link(y):=overbar(x,clr,height(y)); 
info(nucleus(q)):=hpack(y,natural); math_type(nucleus(q)):=sub_box; 
end; 

MODULE: 'Declare math...'
(*PASCAL module 738*)
procedure make_math_accent(q:pointer); 
label done,done1; 
var p,x,y:pointer; {temporary registers for box construction} 
a:integer; {address of lig/kern instruction} 
c:quarterword; {accent character} 
f:internal_font_number; {its font} 
i:four_quarters; {its |char_info|} 
s:scaled; {amount to skew the accent to the right} 
h:scaled; {height of character being accented} 
delta:scaled; {space to remove between accent and accentee} 
w:scaled; {width of the accentee, not including sub/superscripts} 
begin fetch(accent_chr(q)); 
if char_exists(cur_i) then 
  begin i:=cur_i; c:=cur_c; f:=cur_f;
 
  
INSERT: 'Compute the amount of skew'
; 
  x:=clean_box(nucleus(q),cramped_style(cur_style)); w:=width(x); h:=height(x); 
  
INSERT: 'Switch to a larger accent if available and appropriate'
; 
  if h<x_height(f) then delta:=helse delta:=x_height(f); 
  if (math_type(supscr(q))<>empty)or(math_type(subscr(q))<>empty) then 
    if math_type(nucleus(q))=math_char then 
      
INSERT: 'Swap the subscript and superscript into box |x|'
; 
  y:=char_box(f,c); 
  shift_amount(y):=s+half(w-width(y)); 
  width(y):=0; p:=new_kern(-delta); link(p):=x; link(y):=p; 
  y:=vpack(y,natural); width(y):=width(x); 
  if height(y)<h then 
INSERT: 'Make the height of box |y| equal to |h|'
; 
  info(nucleus(q)):=y; 
  math_type(nucleus(q)):=sub_box; 
  end; 
end; 

MODULE: 'Make the height of box |y|...'
(*PASCAL module 739*)
begin p:=new_kern(h-height(y)); link(p):=list_ptr(y); list_ptr(y):=p; 
height(y):=h; 
end 

MODULE: 'Switch to a larger accent if available and appropriate'
(*PASCAL module 740*)
loop  begin if char_tag(i)<>list_tag then goto done; 
  y:=rem_byte(i); 
  i:=char_info(f)(y); 
  if not char_exists(i) then goto done; 
  if char_width(f)(i)>w then goto done; 
  c:=y; 
  end; 
done: 

MODULE: 'Compute the amount of skew'
(*PASCAL module 741*)
s:=0; 
if math_type(nucleus(q))=math_char then 
  begin fetch(nucleus(q)); 
  if char_tag(cur_i)=lig_tag then 
    begin a:=lig_kern_start(cur_f)(cur_i); 
    cur_i:=font_info[a].qqqq; 
    if skip_byte(cur_i)>stop_flag then 
      begin a:=lig_kern_restart(cur_f)(cur_i); 
      cur_i:=font_info[a].qqqq; 
      end; 
    loop begin if qo(next_char(cur_i))=skew_char[cur_f] then 
        begin if op_byte(cur_i)>=kern_flag then 
          if skip_byte(cur_i)<=stop_flag then s:=char_kern(cur_f)(cur_i); 
        goto done1; 
        end; 
      if skip_byte(cur_i)>=stop_flag then goto done1; 
      a:=a+qo(skip_byte(cur_i))+1; 
      cur_i:=font_info[a].qqqq; 
      end; 
    end; 
  end; 
done1: 

MODULE: 'Swap the subscript and superscript into box |x|'
(*PASCAL module 742*)
begin flush_node_list(x); x:=new_noad; 
mem[nucleus(x)]:=mem[nucleus(q)]; 
mem[supscr(x)]:=mem[supscr(q)]; 
mem[subscr(x)]:=mem[subscr(q)];
 
mem[supscr(q)].hh:=empty_field; 
mem[subscr(q)].hh:=empty_field;
 
math_type(nucleus(q)):=sub_mlist; info(nucleus(q)):=x; 
x:=clean_box(nucleus(q),cur_style); delta:=delta+height(x)-h; h:=height(x); 
end 

MODULE: 'Declare math...'
(*PASCAL module 743*)
procedure make_fraction(q:pointer); 
var p,v,x,y,z:pointer; {temporary registers for box construction} 
delta,delta1,delta2,shift_up,shift_down,clr:scaled; 
  {dimensions for box calculations} 
begin if thickness(q)=default_code then thickness(q):=default_rule_thickness; 

INSERT: 'Create equal-width boxes |x| and |z| for the numerator and denominator,   and compute the default amounts |shift_up| and |shift_down| by which they   are displaced from the baseline'
; 
if thickness(q)=0 then 
INSERT: 'Adjust \(s)|shift_up| and |shift_down| for the case   of no fraction line'

else 
INSERT: 'Adjust \(s)|shift_up| and |shift_down| for the case of a fraction line'
; 

INSERT: 'Construct a vlist box for the fraction, according to |shift_up| and   |shift_down|'
; 

INSERT: 'Put the \(f)fraction into a box with its delimiters, and make |new_hlist(q)|   point to it'
; 
end; 

MODULE: 'Create equal-width boxes |x| and |z| for the numerator and denom...'
(*PASCAL module 744*)
x:=clean_box(numerator(q),num_style(cur_style)); 
z:=clean_box(denominator(q),denom_style(cur_style)); 
if width(x)<width(z) then x:=rebox(x,width(z)) 
else z:=rebox(z,width(x)); 
if cur_style<text_style then {display style} 
  begin shift_up:=num1(cur_size); shift_down:=denom1(cur_size); 
  end 
else  begin shift_down:=denom2(cur_size); 
  if thickness(q)<>0 then shift_up:=num2(cur_size) 
  else shift_up:=num3(cur_size); 
  end 

MODULE: 'Adjust \(s)|shift_up| and |shift_down| for the case of no fraction line'
(*PASCAL module 745*)
begin if cur_style<text_style then clr:=7*default_rule_thickness 
else clr:=3*default_rule_thickness; 
delta:=half(clr-((shift_up-depth(x))-(height(z)-shift_down))); 
if delta>0 then 
  begin shift_up:=shift_up+delta; 
  shift_down:=shift_down+delta; 
  end; 
end 

MODULE: 'Adjust \(s)|shift_up| and |shift_down| for the case of a fraction line'
(*PASCAL module 746*)
begin if cur_style<text_style then clr:=3*thickness(q) 
else clr:=thickness(q); 
delta:=half(thickness(q)); 
delta1:=clr-((shift_up-depth(x))-(axis_height(cur_size)+delta)); 
delta2:=clr-((axis_height(cur_size)-delta)-(height(z)-shift_down)); 
if delta1>0 then shift_up:=shift_up+delta1; 
if delta2>0 then shift_down:=shift_down+delta2; 
end 

MODULE: 'Construct a vlist box for the fraction...'
(*PASCAL module 747*)
v:=new_null_box; type(v):=vlist_node; 
height(v):=shift_up+height(x); depth(v):=depth(z)+shift_down; 
width(v):=width(x); {this also equals |width(z)|} 
if thickness(q)=0 then 
  begin p:=new_kern((shift_up-depth(x))-(height(z)-shift_down)); 
  link(p):=z; 
  end 
else  begin y:=fraction_rule(thickness(q));
 
  p:=new_kern((axis_height(cur_size)-delta)-(height(z)-shift_down));
 
  link(y):=p; link(p):=z;
 
  p:=new_kern((shift_up-depth(x))-(axis_height(cur_size)+delta)); 
  link(p):=y; 
  end; 
link(x):=p; list_ptr(v):=x 

MODULE: 'Put the \(f)fraction into a box with its delimiters...'
(*PASCAL module 748*)
if cur_style<text_style then delta:=delim1(cur_size) 
else delta:=delim2(cur_size); 
x:=var_delimiter(left_delimiter(q), cur_size, delta); link(x):=v;
 
z:=var_delimiter(right_delimiter(q), cur_size, delta); link(v):=z;
 
new_hlist(q):=hpack(x,natural) 

MODULE: 'Declare math...'
(*PASCAL module 749*)
function make_op(q:pointer):scaled; 
var delta:scaled; {offset between subscript and superscript} 
p,v,x,y,z:pointer; {temporary registers for box construction} 
c:quarterword;i:four_quarters; {registers for character examination} 
shift_up,shift_down:scaled; {dimensions for box calculation} 
begin if (subtype(q)=normal)and(cur_style<text_style) then 
  subtype(q):=limits; 
if math_type(nucleus(q))=math_char then 
  begin fetch(nucleus(q)); 
  if (cur_style<text_style)and(char_tag(cur_i)=list_tag) then {make it larger} 
    begin c:=rem_byte(cur_i); i:=char_info(cur_f)(c); 
    if char_exists(i) then 
      begin cur_c:=c; cur_i:=i; character(nucleus(q)):=c; 
      end; 
    end; 
  delta:=char_italic(cur_f)(cur_i); x:=clean_box(nucleus(q),cur_style); 
  if (math_type(subscr(q))<>empty)and(subtype(q)<>limits) then 
    width(x):=width(x)-delta; {remove italic correction} 
  shift_amount(x):=half(height(x)-depth(x)) - axis_height(cur_size); 
    {center vertically} 
  math_type(nucleus(q)):=sub_box; info(nucleus(q)):=x; 
  end 
else delta:=0; 
if subtype(q)=limits then 
  
INSERT: 'Construct a box with limits above and below it, skewed by |delta|'
; 
make_op:=delta; 
end; 

MODULE: 'Construct a box with limits above and below it...'
(*PASCAL module 750*)
begin x:=clean_box(supscr(q),sup_style(cur_style)); 
y:=clean_box(nucleus(q),cur_style); 
z:=clean_box(subscr(q),sub_style(cur_style)); 
v:=new_null_box; type(v):=vlist_node; width(v):=width(y); 
if width(x)>width(v) then width(v):=width(x); 
if width(z)>width(v) then width(v):=width(z); 
x:=rebox(x,width(v)); y:=rebox(y,width(v)); z:=rebox(z,width(v));
 
shift_amount(x):=half(delta); shift_amount(z):=-shift_amount(x); 
height(v):=height(y); depth(v):=depth(y); 

INSERT: 'Attach the limits to |y| and adjust |height(v)|, |depth(v)| to   account for their presence'
; 
new_hlist(q):=v; 
end 

MODULE: 'Attach the limits to |y| and adjust |height(v)|, |depth(v)|...'
(*PASCAL module 751*)
if math_type(supscr(q))=empty then 
  begin free_node(x,box_node_size); list_ptr(v):=y; 
  end 
else  begin shift_up:=big_op_spacing3-depth(x); 
  if shift_up<big_op_spacing1 then shift_up:=big_op_spacing1; 
  p:=new_kern(shift_up); link(p):=y; link(x):=p;
 
  p:=new_kern(big_op_spacing5); link(p):=x; list_ptr(v):=p; 
  height(v):=height(v)+big_op_spacing5+height(x)+depth(x)+shift_up; 
  end; 
if math_type(subscr(q))=empty then free_node(z,box_node_size) 
else  begin shift_down:=big_op_spacing4-height(z); 
  if shift_down<big_op_spacing2 then shift_down:=big_op_spacing2; 
  p:=new_kern(shift_down); link(y):=p; link(p):=z;
 
  p:=new_kern(big_op_spacing5); link(z):=p; 
  depth(v):=depth(v)+big_op_spacing5+height(z)+depth(z)+shift_down; 
  end 

MODULE: 'Declare math...'
(*PASCAL module 752*)
procedure make_ord(q:pointer); 
label restart,exit; 
var a:integer; {address of lig/kern instruction} 
p,r:pointer; {temporary registers for list manipulation} 
begin restart:(**);
 
if math_type(subscr(q))=empty then if math_type(supscr(q))=empty then 
 if math_type(nucleus(q))=math_char then 
  begin p:=link(q); 
  if p<>null then if (type(p)>=ord_noad)and(type(p)<=punct_noad) then 
    if math_type(nucleus(p))=math_char then 
    if fam(nucleus(p))=fam(nucleus(q)) then 
      begin math_type(nucleus(q)):=math_text_char; 
      fetch(nucleus(q)); 
      if char_tag(cur_i)=lig_tag then 
        begin a:=lig_kern_start(cur_f)(cur_i); 
        cur_c:=character(nucleus(p)); 
        cur_i:=font_info[a].qqqq; 
        if skip_byte(cur_i)>stop_flag then 
          begin a:=lig_kern_restart(cur_f)(cur_i); 
          cur_i:=font_info[a].qqqq; 
          end; 
        loop begin 
INSERT: 'If instruction |cur_i| is a kern with |cur_c|, attach             the kern after~|q|; or if it is a ligature with |cur_c|, combine             noads |q| and~|p| appropriately; then |return| if the cursor has             moved past a noad, or |goto restart|'
; 
          if skip_byte(cur_i)>=stop_flag then return; 
          a:=a+qo(skip_byte(cur_i))+1; 
          cur_i:=font_info[a].qqqq; 
          end; 
        end; 
      end; 
  end; 
exit:end; 

MODULE: 'If instruction |cur_i| is a kern with |cur_c|, ...'
(*PASCAL module 753*)
if next_char(cur_i)=cur_c then if skip_byte(cur_i)<=stop_flag then 
  if op_byte(cur_i)>=kern_flag then 
    begin p:=new_kern(char_kern(cur_f)(cur_i)); 
    link(p):=link(q); link(q):=p; return; 
    end 
  else  begin check_interrupt; {allow a way out of infinite ligature loop} 
    case op_byte(cur_i) of 
  qi(1),qi(5): character(nucleus(q)):=rem_byte(cur_i); {\.[=:\?], \.[=:\?>]} 
  qi(2),qi(6): character(nucleus(p)):=rem_byte(cur_i); {\.[\?=:], \.[\?=:>]} 
  qi(3),qi(7),qi(11):begin r:=new_noad; {\.[\?=:\?], \.[\?=:\?>], \.[\?=:\?>>]} 
      character(nucleus(r)):=rem_byte(cur_i); 
      fam(nucleus(r)):=fam(nucleus(q));
 
      link(q):=r; link(r):=p; 
      if op_byte(cur_i)<qi(11) then math_type(nucleus(r)):=math_char 
      else math_type(nucleus(r)):=math_text_char; {prevent combination} 
      end; 
    othercases begin link(q):=link(p); 
      character(nucleus(q)):=rem_byte(cur_i); {\.[=:]} 
      mem[subscr(q)]:=mem[subscr(p)]; mem[supscr(q)]:=mem[supscr(p)];
 
      free_node(p,noad_size); 
      end 
    endcases; 
    if op_byte(cur_i)>qi(3) then return; 
    math_type(nucleus(q)):=math_char; goto restart; 
    end 

MODULE: 'Convert \(n)|nucleus(q)| to an hlist and attach the sub/superscripts'
(*PASCAL module 754*)
case math_type(nucleus(q)) of 
math_char, math_text_char: 
  
INSERT: 'Create a character node |p| for |nucleus(q)|, possibly followed   by a kern node for the italic correction, and set |delta| to the   italic correction if a subscript is present'
; 
empty: p:=null; 
sub_box: p:=info(nucleus(q)); 
sub_mlist: begin cur_mlist:=info(nucleus(q)); save_style:=cur_style; 
  mlist_penalties:=false; mlist_to_hlist; {recursive call} 
(*recursion*) 
  cur_style:=save_style; 
INSERT: 'Set up the values...'
; 
  p:=hpack(link(temp_head),natural); 
  end; 
othercases confusion('mlist2') 
(*this can''t happen mlist2][\quad mlist2*) 
endcases;
 
new_hlist(q):=p; 
if (math_type(subscr(q))=empty)and(math_type(supscr(q))=empty) then 
  goto check_dimensions; 
make_scripts(q,delta) 

MODULE: 'Create a character node |p| for |nucleus(q)|...'
(*PASCAL module 755*)
begin fetch(nucleus(q)); 
if char_exists(cur_i) then 
  begin delta:=char_italic(cur_f)(cur_i); p:=new_character(cur_f,qo(cur_c)); 
  if (math_type(nucleus(q))=math_text_char)and(space(cur_f)<>0) then 
    delta:=0; {no italic correction in mid-word of text font} 
  if (math_type(subscr(q))=empty)and(delta<>0) then 
    begin link(p):=new_kern(delta); delta:=0; 
    end; 
  end 
else p:=null; 
end 

MODULE: 'Declare math...'
(*PASCAL module 756*)
procedure make_scripts(q:pointer;delta:scaled); 
var p,x,y,z:pointer; {temporary registers for box construction} 
shift_up,shift_down,clr:scaled; {dimensions in the calculation} 
t:small_number; {subsidiary size code} 
begin p:=new_hlist(q); 
if is_char_node(p) then 
  begin shift_up:=0; shift_down:=0; 
  end 
else  begin z:=hpack(p,natural); 
  if cur_style<script_style then t:=script_sizeelse t:=script_script_size; 
  shift_up:=height(z)-sup_drop(t); 
  shift_down:=depth(z)+sub_drop(t); 
  free_node(z,box_node_size); 
  end; 
if math_type(supscr(q))=empty then 
  
INSERT: 'Construct a subscript box |x| when there is no superscript'

else  begin 
INSERT: 'Construct a superscript box |x|'
; 
  if math_type(subscr(q))=empty then shift_amount(x):=-shift_up 
  else 
INSERT: 'Construct a sub/superscript combination box |x|, with the     superscript offset by |delta|'
; 
  end; 
if new_hlist(q)=null then new_hlist(q):=x 
else  begin p:=new_hlist(q); 
  while link(p)<>null do p:=link(p); 
  link(p):=x; 
  end; 
end; 

MODULE: 'Construct a subscript box |x| when there is no superscript'
(*PASCAL module 757*)
begin x:=clean_box(subscr(q),sub_style(cur_style)); 
width(x):=width(x)+script_space; 
if shift_down<sub1(cur_size) then shift_down:=sub1(cur_size); 
clr:=height(x)-(abs(math_x_height(cur_size)*4) div 5); 
if shift_down<clr then shift_down:=clr; 
shift_amount(x):=shift_down; 
end 

MODULE: 'Construct a superscript box |x|'
(*PASCAL module 758*)
begin x:=clean_box(supscr(q),sup_style(cur_style)); 
width(x):=width(x)+script_space; 
if odd(cur_style) then clr:=sup3(cur_size) 
else if cur_style<text_style then clr:=sup1(cur_size) 
else clr:=sup2(cur_size); 
if shift_up<clr then shift_up:=clr; 
clr:=depth(x)+(abs(math_x_height(cur_size)) div 4); 
if shift_up<clr then shift_up:=clr; 
end 

MODULE: 'Construct a sub/superscript combination box |x|...'
(*PASCAL module 759*)
begin y:=clean_box(subscr(q),sub_style(cur_style)); 
width(y):=width(y)+script_space; 
if shift_down<sub2(cur_size) then shift_down:=sub2(cur_size); 
clr:=4*default_rule_thickness- 
  ((shift_up-depth(x))-(height(y)-shift_down)); 
if clr>0 then 
  begin shift_down:=shift_down+clr; 
  clr:=(abs(math_x_height(cur_size)*4) div 5)-(shift_up-depth(x)); 
  if clr>0 then 
    begin shift_up:=shift_up+clr; 
    shift_down:=shift_down-clr; 
    end; 
  end; 
shift_amount(x):=delta; {superscript is |delta| to the right of the subscript} 
p:=new_kern((shift_up-depth(x))-(height(y)-shift_down)); link(x):=p; link(p):=y; 
x:=vpack(x,natural); shift_amount(x):=shift_down; 
end 

MODULE: 'Make a second pass over the mlist, ...'
(*PASCAL module 760*)
p:=temp_head; link(p):=null; q:=mlist; r_type:=0; cur_style:=style; 

INSERT: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
; 
while q<>null do 
  begin 
INSERT: 'If node |q| is a style node, change the style and |goto delete_q|;     otherwise if it is not a noad, put it into the hlist,     advance |q|, and |goto done|; otherwise set |s| to the size     of noad |q|, set |t| to the associated type (|ord_noad..     inner_noad|), and set |pen| to the associated penalty'
; 
  
INSERT: 'Append inter-element spacing based on |r_type| and |t|'
; 
  
INSERT: 'Append any |new_hlist| entries for |q|, and any appropriate penalties'
; 
  r_type:=t; 
  delete_q: r:=q; q:=link(q); free_node(r,s); 
  done: end 

MODULE: 'If node |q| is a style node, change the style...'
(*PASCAL module 761*)
t:=ord_noad; s:=noad_size; pen:=inf_penalty; 
case type(q) of 
op_noad,open_noad,close_noad,punct_noad,inner_noad: t:=type(q); 
bin_noad: begin t:=bin_noad; pen:=bin_op_penalty; 
  end; 
rel_noad: begin t:=rel_noad; pen:=rel_penalty; 
  end; 
ord_noad,vcenter_noad,over_noad,under_noad: do_nothing; 
radical_noad: s:=radical_noad_size; 
accent_noad: s:=accent_noad_size; 
fraction_noad: begin t:=inner_noad; s:=fraction_noad_size; 
  end; 
left_noad,right_noad: t:=make_left_right(q,style,max_d,max_h); 
style_node: 
INSERT: 'Change the current style and |goto delete_q|'
; 
whatsit_node,penalty_node,rule_node,disc_node,adjust_node,ins_node,mark_node, 
 glue_node,kern_node:(**);
 
  begin link(p):=q; p:=q; q:=link(q); link(p):=null; goto done; 
  end; 
othercases confusion('mlist3') 
(*this can''t happen mlist3][\quad mlist3*) 
endcases 

MODULE: 'Declare math...'
(*PASCAL module 762*)
function make_left_right(q:pointer;style:small_number; 
  max_d,max_h:scaled):small_number; 
var delta,delta1,delta2:scaled; {dimensions used in the calculation} 
begin if style<script_style then cur_size:=text_size 
else cur_size:=16*((style-text_style) div 2); 
delta2:=max_d+axis_height(cur_size); 
delta1:=max_h+max_d-delta2; 
if delta2>delta1 then delta1:=delta2; {|delta1| is max distance from axis} 
delta:=(delta1 div 500)*delimiter_factor; 
delta2:=delta1+delta1-delimiter_shortfall; 
if delta<delta2 then delta:=delta2; 
new_hlist(q):=var_delimiter(delimiter(q),cur_size,delta); 
make_left_right:=type(q)-(left_noad-open_noad); {|open_noad| or |close_noad|} 
end; 

MODULE: 'Change the current style and |goto delete_q|'
(*PASCAL module 763*)
begin cur_style:=subtype(q); s:=style_node_size; 

INSERT: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
; 
goto delete_q; 
end 

MODULE: 'Glob... '
(*PASCAL module 764*)
magic_offset:integer; {used to find inter-element spacing} 

MODULE: 'Compute the magic offset'
(*PASCAL module 765*)
magic_offset:=str_start[math_spacing]-9*ord_noad 

MODULE: 'Append inter-element spacing based on |r_type| and |t|'
(*PASCAL module 766*)
if r_type>0 then {not the first noad} 
  begin case so(str_pool[r_type*8+t+magic_offset]) of 
  '0': x:=0; 
  '1': if cur_style<script_style then x:=thin_mu_skip_codeelse x:=0; 
  '2': x:=thin_mu_skip_code; 
  '3': if cur_style<script_style then x:=med_mu_skip_codeelse x:=0; 
  '4': if cur_style<script_style then x:=thick_mu_skip_codeelse x:=0; 
  othercases confusion('mlist4') 
(*this can''t happen mlist4][\quad mlist4*) 
  endcases; 
  if x<>0 then 
    begin y:=math_glue(glue_par(x),cur_mu); 
    z:=new_glue(y); glue_ref_count(y):=null; link(p):=z; p:=z;
 
    subtype(z):=x+1; {store a symbolic subtype} 
    end; 
  end 

MODULE: 'Append any |new_hlist| entries for |q|, and any appropriate penalties'
(*PASCAL module 767*)
if new_hlist(q)<>null then 
  begin link(p):=new_hlist(q); 
  repeat p:=link(p); 
  until link(p)=null; 
  end; 
if penalties then if link(q)<>null then if pen<inf_penalty then 
  begin r_type:=type(link(q)); 
  if r_type<>penalty_node then if r_type<>rel_noad then 
    begin z:=new_penalty(pen); link(p):=z; p:=z; 
    end; 
  end 

MODULE: 'Glob... '
(*PASCAL module 770*)
cur_align:pointer; {current position in preamble list} 
cur_span:pointer; {start of currently spanned columns in preamble list} 
cur_loop:pointer; {place to copy when extending a periodic preamble} 
align_ptr:pointer; {most recently pushed-down alignment stack node} 
cur_head,cur_tail:pointer; {adjustment list pointers} 

MODULE: 'Set init...'
(*PASCAL module 771*)
align_ptr:=null; cur_align:=null; cur_span:=null; cur_loop:=null; 
cur_head:=null; cur_tail:=null; 

MODULE: 'Change current mode...'
(*PASCAL module 775*)
if mode=mmode then 
  begin mode:=-vmode; prev_depth:=nest[nest_ptr-2].aux_field.sc; 
  end 
else if mode>0 then negate(mode) 

MODULE: 'Check for improper alignment in displayed math'
(*PASCAL module 776*)
if (mode=mmode)and((tail<>head)or(incompleat_noad<>null)) then 
  begin print_err('Improper '); print_esc('halign'); print(' inside $$''s'); 
(*Improper \\halign...*) 
  help3('Displays can use special alignments (like \eqalignno)')
 
  ('only if nothing but the alignment itself is between $$''s.')
 
  ('So I''ve deleted the formulas that preceded this alignment.'); 
  error; flush_math; 
  end 

MODULE: 'Scan the preamble and record it in the |preamble| list'
(*PASCAL module 777*)
preamble:=null; cur_align:=align_head; cur_loop:=null; scanner_status:=aligning; 
warning_index:=save_cs_ptr; align_state:=-1000000; 
  {at this point, |cur_cmd=left_brace|} 
loop  begin 
INSERT: 'Append the current tabskip glue to the preamble list'
; 
  if cur_cmd=car_ret then goto done; {\.[\\cr] ends the preamble} 
  
INSERT: 'Scan preamble text until |cur_cmd| is |tab_mark| or |car_ret|,     looking for changes in the tabskip glue; append an     alignrecord to the preamble list'
; 
  end; 
done: scanner_status:=normal 

MODULE: 'Append the current tabskip glue to the preamble list'
(*PASCAL module 778*)
link(cur_align):=new_param_glue(tab_skip_code); 
cur_align:=link(cur_align) 

MODULE: 'Scan preamble text until |cur_cmd| is |tab_mark| or |car_ret|...'
(*PASCAL module 779*)

INSERT: 'Scan the template \<u_j>, putting the resulting token list in |hold_head|'
; 
link(cur_align):=new_null_box; cur_align:=link(cur_align); {a new alignrecord} 
info(cur_align):=end_span; width(cur_align):=null_flag; 
u_part(cur_align):=link(hold_head); 

INSERT: 'Scan the template \<v_j>, putting the resulting token list in |hold_head|'
; 
v_part(cur_align):=link(hold_head) 

MODULE: 'Put each of \TeX''s primitives into the hash table'
(*PASCAL module 780*)
primitive('span',tab_mark,span_code);
 
(*span_][\.{\\span} primitive*) 
primitive('cr',car_ret,cr_code); 
(*cr_][\.{\\cr} primitive*) 
text(frozen_cr):='cr'; eqtb[frozen_cr]:=eqtb[cur_val];
 
primitive('crcr',car_ret,cr_cr_code); 
(*cr_cr_][\.{\\crcr} primitive*) 
text(frozen_end_template):='endtemplate'; text(frozen_endv):='endtemplate'; 
eq_type(frozen_endv):=endv; equiv(frozen_endv):=null_list; 
eq_level(frozen_endv):=level_one;
 
eqtb[frozen_end_template]:=eqtb[frozen_endv]; 
eq_type(frozen_end_template):=end_template; 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 781*)
tab_mark: if chr_code=span_code then print_esc('span') 
  else chr_cmd('alignment tab character '); 
car_ret: if chr_code=cr_code then print_esc('cr') 
  else print_esc('crcr'); 

MODULE: 'Declare the procedure called |get_preamble_token|'
(*PASCAL module 782*)
procedure get_preamble_token; 
label restart; 
begin restart: get_token; 
while (cur_chr=span_code)and(cur_cmd=tab_mark) do 
  begin get_token; {this token will be expanded once} 
  if cur_cmd>max_command then 
    begin expand; get_token; 
    end; 
  end; 
if cur_cmd=endv then 
  fatal_error('(interwoven alignment preambles are not allowed)'); 
(*interwoven alignment preambles...*) 
if (cur_cmd=assign_glue)and(cur_chr=glue_base+tab_skip_code) then 
  begin scan_optional_equals; scan_glue(glue_val); 
  if global_defs>0 then geq_define(glue_base+tab_skip_code,glue_ref,cur_val) 
  else eq_define(glue_base+tab_skip_code,glue_ref,cur_val); 
  goto restart; 
  end; 
end; 

MODULE: 'Scan the template \<u_j>...'
(*PASCAL module 783*)
p:=hold_head; link(p):=null; 
loop  begin get_preamble_token; 
  if cur_cmd=mac_param then goto done1; 
  if (cur_cmd<=car_ret)and(cur_cmd>=tab_mark)and(align_state=-1000000) then 
   if (p=hold_head)and(cur_loop=null)and(cur_cmd=tab_mark) 
    then cur_loop:=cur_align 
   else  begin print_err('Missing # inserted in alignment preamble'); 
(*Missing \# inserted...*) 
    help3('There should be exactly one # between &''s, when an')
 
    ('\halign or \valign is being set up. In this case you had')
 
    ('none, so I''ve put one in; maybe that will work.'); 
    back_error; goto done1; 
    end 
  else if (cur_cmd<>spacer)or(p<>hold_head) then 
    begin link(p):=get_avail; p:=link(p); info(p):=cur_tok; 
    end; 
  end; 
done1: 

MODULE: 'Scan the template \<v_j>...'
(*PASCAL module 784*)
p:=hold_head; link(p):=null; 
loop  begin continue: get_preamble_token; 
  if (cur_cmd<=car_ret)and(cur_cmd>=tab_mark)and(align_state=-1000000) then 
    goto done2; 
  if cur_cmd=mac_param then 
    begin print_err('Only one # is allowed per tab'); 
(*Only one \# is allowed...*) 
    help3('There should be exactly one # between &''s, when an')
 
    ('\halign or \valign is being set up. In this case you had')
 
    ('more than one, so I''m ignoring all but the first.'); 
    error; goto continue; 
    end; 
  link(p):=get_avail; p:=link(p); info(p):=cur_tok; 
  end; 
done2: link(p):=get_avail; p:=link(p); 
info(p):=end_template_token {put \.[\\endtemplate] at the end} 

MODULE: 'Declare the procedure called |align_peek|'
(*PASCAL module 785*)
procedure align_peek; 
label restart; 
begin restart: align_state:=1000000; 
INSERT: 'Get the next non-blank non-call token'
; 
if cur_cmd=no_align then 
  begin scan_left_brace; new_save_level(no_align_group); 
  if mode=-vmode then normal_paragraph; 
  end 
else if cur_cmd=right_brace then fin_align 
else if (cur_cmd=car_ret)and(cur_chr=cr_cr_code) then 
  goto restart {ignore \.[\\crcr]} 
else  begin init_row; {start a new row} 
  init_col; {start a new column and replace what we peeked at} 
  end; 
end; 

MODULE: 'Declare the procedure called |init_span|'
(*PASCAL module 787*)
procedure init_span(p:pointer); 
begin push_nest; 
if mode=-hmode then space_factor:=1000 
else  begin prev_depth:=ignore_depth; normal_paragraph; 
  end; 
cur_span:=p; 
end; 

MODULE: 'Insert the \(v)\<v_j>...'
(*PASCAL module 789*)
begin if (scanner_status=aligning) or (cur_align=null) then 
  fatal_error('(interwoven alignment preambles are not allowed)'); 
(*interwoven alignment preambles...*) 
cur_cmd:=extra_info(cur_align); extra_info(cur_align):=cur_chr; 
if cur_cmd=omit then begin_token_list(omit_template,v_template) 
else begin_token_list(v_part(cur_align),v_template); 
align_state:=1000000; goto restart; 
end 

MODULE: 'Initialize the special...'
(*PASCAL module 790*)
info(omit_template):=end_template_token; {|link(omit_template)=null|} 

MODULE: 'If the preamble list has been traversed, check that the row has ended'
(*PASCAL module 792*)
if (p=null)and(extra_info(cur_align)<cr_code) then 
 if cur_loop<>null then 
INSERT: 'Lengthen the preamble periodically'

 else  begin print_err('Extra alignment tab has been changed to '); 
(*Extra alignment tab...*) 
  print_esc('cr'); 
  help3('You have given more \span or & marks than there were')
 
  ('in the preamble to the \halign or \valign now in progress.')
 
  ('So I''ll assume that you meant to type \cr instead.'); 
  extra_info(cur_align):=cr_code; error; 
  end 

MODULE: 'Lengthen the preamble...'
(*PASCAL module 793*)
begin link(q):=new_null_box; p:=link(q); {a new alignrecord} 
info(p):=end_span; width(p):=null_flag; cur_loop:=link(cur_loop); 

INSERT: 'Copy the templates from node |cur_loop| into node |p|'
; 
cur_loop:=link(cur_loop); 
link(p):=new_glue(glue_ptr(cur_loop)); 
end 

MODULE: 'Copy the templates from node |cur_loop| into node |p|'
(*PASCAL module 794*)
q:=hold_head; r:=u_part(cur_loop); 
while r<>null do 
  begin link(q):=get_avail; q:=link(q); info(q):=info(r); r:=link(r); 
  end; 
link(q):=null; u_part(p):=link(hold_head); 
q:=hold_head; r:=v_part(cur_loop); 
while r<>null do 
  begin link(q):=get_avail; q:=link(q); info(q):=info(r); r:=link(r); 
  end; 
link(q):=null; v_part(p):=link(hold_head) 

MODULE: 'Copy the tabskip glue...'
(*PASCAL module 795*)
tail_append(new_glue(glue_ptr(link(cur_align)))); 
subtype(tail):=tab_skip_code+1 

MODULE: 'Package an unset...'
(*PASCAL module 796*)
begin if mode=-hmode then 
  begin adjust_tail:=cur_tail; u:=hpack(link(head),natural); w:=width(u); 
  cur_tail:=adjust_tail; adjust_tail:=null; 
  end 
else  begin u:=vpackage(link(head),natural,0); w:=height(u); 
  end; 
n:=min_quarterword; {this represents a span count of 1} 
if cur_span<>cur_align then 
INSERT: 'Update width entry for spanned columns'

else if w>width(cur_align) then width(cur_align):=w; 
type(u):=unset_node; span_count(u):=n;
 

INSERT: 'Determine the stretch order'
; 
glue_order(u):=o; glue_stretch(u):=total_stretch[o];
 

INSERT: 'Determine the shrink order'
; 
glue_sign(u):=o; glue_shrink(u):=total_shrink[o];
 
pop_nest; link(tail):=u; tail:=u; 
end 

MODULE: 'Initialize the special list heads...'
(*PASCAL module 797*)
link(end_span):=max_quarterword+1; info(end_span):=null; 

MODULE: 'Update width entry for spanned columns'
(*PASCAL module 798*)
begin q:=cur_span; 
repeat incr(n); q:=link(link(q)); 
until q=cur_align; 
if n>max_quarterword then confusion('256 spans'); {this can happen, but won''t} 
(*system dependencies*) 
(*this can''t happen 256 spans][\quad 256 spans*) 
q:=cur_span; while link(info(q))<n do q:=info(q); 
if link(info(q))>n then 
  begin s:=get_node(span_node_size); info(s):=info(q); link(s):=n; 
  info(q):=s; width(s):=w; 
  end 
else if width(info(q))<w then width(info(q)):=w; 
end 

MODULE: 'Go through the preamble list,...'
(*PASCAL module 801*)
q:=link(preamble); 
repeat flush_list(u_part(q)); flush_list(v_part(q)); 
p:=link(link(q)); 
if width(q)=null_flag then 
  
INSERT: 'Nullify |width(q)| and the tabskip glue following this column'
; 
if info(q)<>end_span then 
  
INSERT: 'Merge the widths in the span nodes of |q| with those of |p|,     destroying the span nodes of |q|'
; 
type(q):=unset_node; span_count(q):=min_quarterword; height(q):=0; 
depth(q):=0; glue_order(q):=normal; glue_sign(q):=normal; 
glue_stretch(q):=0; glue_shrink(q):=0; q:=p; 
until q=null 

MODULE: 'Nullify |width(q)| and the tabskip glue following this column'
(*PASCAL module 802*)
begin width(q):=0; r:=link(q); s:=glue_ptr(r); 
if s<>zero_glue then 
  begin add_glue_ref(zero_glue); delete_glue_ref(s); 
  glue_ptr(r):=zero_glue; 
  end; 
end 

MODULE: 'Merge the widths...'
(*PASCAL module 803*)
begin t:=width(q)+width(glue_ptr(link(q))); 
r:=info(q); s:=end_span; info(s):=p; n:=min_quarterword+1; 
repeat width(r):=width(r)-t; u:=info(r); 
while link(r)>n do 
  begin s:=info(s); n:=link(info(s))+1; 
  end; 
if link(r)<n then 
  begin info(r):=info(s); info(s):=r; decr(link(r)); s:=r; 
  end 
else  begin if width(r)>width(info(s)) then width(info(s)):=width(r); 
  free_node(r,span_node_size); 
  end; 
r:=u; 
until r=end_span; 
end 

MODULE: 'Package the preamble list...'
(*PASCAL module 804*)
save_ptr:=save_ptr-2; pack_begin_line:=-mode_line; 
if mode=-vmode then 
  begin rule_save:=overfull_rule; 
  overfull_rule:=0; {prevent rule from being packaged} 
  p:=hpack(preamble,saved(1),saved(0)); overfull_rule:=rule_save; 
  end 
else  begin q:=link(preamble); 
  repeat height(q):=width(q); width(q):=0; q:=link(link(q)); 
  until q=null; 
  p:=vpack(preamble,saved(1),saved(0)); 
  q:=link(preamble); 
  repeat width(q):=height(q); height(q):=0; q:=link(link(q)); 
  until q=null; 
  end; 
pack_begin_line:=0 

MODULE: 'Set the glue in all the unset...'
(*PASCAL module 805*)
q:=link(head); s:=head; 
while q<>null do 
  begin if not is_char_node(q) then 
    if type(q)=unset_node then 
      
INSERT: 'Set the unset box |q| and the unset boxes in it'

    else if type(q)=rule_node then 
      
INSERT: 'Make the running dimensions in rule |q| extend to the         boundaries of the alignment'
; 
  s:=q; q:=link(q); 
  end 

MODULE: 'Make the running dimensions in rule |q| extend...'
(*PASCAL module 806*)
begin if is_running(width(q)) then width(q):=width(p); 
if is_running(height(q)) then height(q):=height(p); 
if is_running(depth(q)) then depth(q):=depth(p); 
if o<>0 then 
  begin r:=link(q); link(q):=null; q:=hpack(q,natural); 
  shift_amount(q):=o; link(q):=r; link(s):=q; 
  end; 
end 

MODULE: 'Set the unset box |q| and the unset boxes in it'
(*PASCAL module 807*)
begin if mode=-vmode then 
  begin type(q):=hlist_node; width(q):=width(p); 
  end 
else  begin type(q):=vlist_node; height(q):=height(p); 
  end; 
glue_order(q):=glue_order(p); glue_sign(q):=glue_sign(p); 
glue_set(q):=glue_set(p); shift_amount(q):=o; 
r:=link(list_ptr(q)); s:=link(list_ptr(p)); 
repeat 
INSERT: 'Set the glue in node |r| and change it from an unset node'
; 
r:=link(link(r)); s:=link(link(s)); 
until r=null; 
end 

MODULE: 'Set the glue in node |r|...'
(*PASCAL module 808*)
n:=span_count(r); t:=width(s); w:=t; u:=hold_head; 
while n>min_quarterword do 
  begin decr(n); 
  
INSERT: 'Append tabskip glue and an empty box to list |u|,     and update |s| and |t| as the prototype nodes are passed'
; 
  end; 
if mode=-vmode then 
  
INSERT: 'Make the unset node |r| into an |hlist_node| of width |w|,     setting the glue as if the width were |t|'

else 
INSERT: 'Make the unset node |r| into a |vlist_node| of height |w|,     setting the glue as if the height were |t|'
; 
shift_amount(r):=0; 
if u<>hold_head then {append blank boxes to account for spanned nodes} 
  begin link(u):=link(r); link(r):=link(hold_head); r:=u; 
  end 

MODULE: 'Append tabskip glue and an empty box to list |u|...'
(*PASCAL module 809*)
s:=link(s); v:=glue_ptr(s); link(u):=new_glue(v); u:=link(u); 
subtype(u):=tab_skip_code+1; t:=t+width(v); 
if glue_sign(p)=stretching then 
  begin if stretch_order(v)=glue_order(p) then 
    t:=t+round(float(glue_set(p))*stretch(v)); 
(*real multiplication*) 
  end 
else if glue_sign(p)=shrinking then 
  begin if shrink_order(v)=glue_order(p) then 
    t:=t-round(float(glue_set(p))*shrink(v)); 
  end; 
s:=link(s); link(u):=new_null_box; u:=link(u); t:=t+width(s); 
if mode=-vmode then width(u):=width(s)else 
  begin type(u):=vlist_node; height(u):=width(s); 
  end 

MODULE: 'Make the unset node |r| into an |hlist_node| of width |w|...'
(*PASCAL module 810*)
begin height(r):=height(q); depth(r):=depth(q); 
if t=width(r) then 
  begin glue_sign(r):=normal; glue_order(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); 
  end 
else if t>width(r) then 
  begin glue_sign(r):=stretching; 
  if glue_stretch(r)=0 then set_glue_ratio_zero(glue_set(r)) 
  else glue_set(r):=unfloat((t-width(r))/glue_stretch(r)); 
(*real division*) 
  end 
else  begin glue_order(r):=glue_sign(r); glue_sign(r):=shrinking; 
  if glue_shrink(r)=0 then set_glue_ratio_zero(glue_set(r)) 
  else if (glue_order(r)=normal)and(width(r)-t>glue_shrink(r)) then 
    set_glue_ratio_one(glue_set(r)) 
  else glue_set(r):=unfloat((width(r)-t)/glue_shrink(r)); 
  end; 
width(r):=w; type(r):=hlist_node; 
end 

MODULE: 'Make the unset node |r| into a |vlist_node| of height |w|...'
(*PASCAL module 811*)
begin width(r):=width(q); 
if t=height(r) then 
  begin glue_sign(r):=normal; glue_order(r):=normal; 
  set_glue_ratio_zero(glue_set(r)); 
  end 
else if t>height(r) then 
  begin glue_sign(r):=stretching; 
  if glue_stretch(r)=0 then set_glue_ratio_zero(glue_set(r)) 
  else glue_set(r):=unfloat((t-height(r))/glue_stretch(r)); 
(*real division*) 
  end 
else  begin glue_order(r):=glue_sign(r); glue_sign(r):=shrinking; 
  if glue_shrink(r)=0 then set_glue_ratio_zero(glue_set(r)) 
  else if (glue_order(r)=normal)and(height(r)-t>glue_shrink(r)) then 
    set_glue_ratio_one(glue_set(r)) 
  else glue_set(r):=unfloat((height(r)-t)/glue_shrink(r)); 
  end; 
height(r):=w; type(r):=vlist_node; 
end 

MODULE: 'Insert the \(c)current list into its environment'
(*PASCAL module 812*)
aux_save:=aux; p:=link(head); q:=tail; pop_nest; 
if mode=mmode then 
INSERT: 'Finish an alignment in a display'

else  begin aux:=aux_save; link(tail):=p; 
  if p<>null then tail:=q; 
  if mode=vmode then build_page; 
  end 

MODULE: 'Glob... '
(*PASCAL module 814*)
just_box:pointer; {the |hlist_node| for the last line of the new paragraph} 

MODULE: 'Get ready to start...'
(*PASCAL module 816*)
link(temp_head):=link(head); 
if is_char_node(tail) then tail_append(new_penalty(inf_penalty)) 
else if type(tail)<>glue_node then tail_append(new_penalty(inf_penalty)) 
else  begin type(tail):=penalty_node; delete_glue_ref(glue_ptr(tail)); 
  flush_node_list(leader_ptr(tail)); penalty(tail):=inf_penalty; 
  end; 
link(tail):=new_param_glue(par_fill_skip_code); 
init_cur_lang:=prev_graf mod 65536; 
init_l_hyf:=prev_graf div 4194304; 
init_r_hyf:=(prev_graf div 65536) mod 64; 
pop_nest; 

MODULE: 'Initialize the special list heads...'
(*PASCAL module 820*)
type(last_active):=hyphenated; line_number(last_active):=max_halfword; 
subtype(last_active):=0; {the |subtype| is never examined by the algorithm} 

MODULE: 'Glob... '
(*PASCAL module 821*)
passive:pointer; {most recent node on passive list} 
printed_node:pointer; {most recent node that has been printed} 
pass_number:halfword; {the number of passive nodes allocated on this pass} 

MODULE: 'Glob... '
(*PASCAL module 823*)
active_width:array[1..6] of scaled; 
  {distance from first active node to~|cur_p|} 
cur_active_width:array[1..6] of scaled; {distance from current active node} 
background:array[1..6] of scaled; {length of an ``empty'' line} 
break_width:array[1..6] of scaled; {length being computed after current break} 

MODULE: 'Glob... '
(*PASCAL module 825*)
no_shrink_error_yet:boolean; {have we complained about infinite shrinkage?} 

MODULE: 'Declare subprocedures for |line_break|'
(*PASCAL module 826*)
function finite_shrink(p:pointer):pointer; {recovers from infinite shrinkage} 
var q:pointer; {new glue specification} 
begin if no_shrink_error_yet then 
  begin no_shrink_error_yet:=false; 
  print_err('Infinite glue shrinkage found in a paragraph'); 
(*Infinite glue shrinkage...*) 
  help5('The paragraph just ended includes some glue that has')
 
  ('infinite shrinkability, e.g., `\hskip 0pt minus 1fil''.')
 
  ('Such glue doesn''t belong there---it allows a paragraph')
 
  ('of any length to fit on one line. But it''s safe to proceed,')
 
  ('since the offensive shrinkability has been made finite.'); 
  error; 
  end; 
q:=new_spec(p); shrink_order(q):=normal; 
delete_glue_ref(p); finite_shrink:=q; 
end; 

MODULE: 'Get ready to start...'
(*PASCAL module 827*)
no_shrink_error_yet:=true;
 
check_shrinkage(left_skip); check_shrinkage(right_skip);
 
q:=left_skip; r:=right_skip; background[1]:=width(q)+width(r);
 
background[2]:=0; background[3]:=0; background[4]:=0; background[5]:=0;
 
background[2+stretch_order(q)]:=stretch(q);
 
background[2+stretch_order(r)]:=background[2+stretch_order(r)]+stretch(r);
 
background[6]:=shrink(q)+shrink(r); 

MODULE: 'Glob... '
(*PASCAL module 828*)
cur_p:pointer; {the current breakpoint under consideration} 
second_pass:boolean; {is this our second attempt to break this paragraph?} 
final_pass:boolean; {is this our final attempt to break this paragraph?} 
threshold:integer; {maximum badness on feasible lines} 

MODULE: 'Declare subprocedures for |line_break|'
(*PASCAL module 829*)
procedure try_break(pi:integer;break_type:small_number); 
label exit,done,done1,continue,deactivate; 
var r:pointer; {runs through the active list} 
prev_r:pointer; {stays a step behind |r|} 
old_l:halfword; {maximum line number in current equivalence class of lines} 
no_break_yet:boolean; {have we found a feasible break at |cur_p|?} 

INSERT: 'Other local variables for |try_break|'
; 
begin 
INSERT: 'Make sure that |pi| is in the proper range'
; 
no_break_yet:=true; prev_r:=active; old_l:=0; 
do_all_six(copy_to_cur_active); 
loop  begin continue: r:=link(prev_r); 
  
INSERT: 'If node |r| is of type |delta_node|, update |cur_active_width|,     set |prev_r| and |prev_prev_r|, then |goto continue|'
; 
  
INSERT: 'If a line number class has ended, create new active nodes for     the best feasible breaks in that class; then |return|     if |r=last_active|, otherwise compute the new |line_width|'
; 
  
INSERT: 'Consider the demerits for a line from |r| to |cur_p|;     deactivate node |r| if it should no longer be active;     then |goto continue| if a line from |r| to |cur_p| is infeasible,     otherwise record a new feasible break'
; 
  end; 
exit: stat 
INSERT: 'Update the value of |printed_node| for   symbolic displays'
tats; 
end; 

MODULE: 'Other local variables for |try_break|'
(*PASCAL module 830*)
prev_prev_r:pointer; {a step behind |prev_r|, if |type(prev_r)=delta_node|} 
s:pointer; {runs through nodes ahead of |cur_p|} 
q:pointer; {points to a new node being created} 
v:pointer; {points to a glue specification or a node ahead of |cur_p|} 
t:integer; {node count, if |cur_p| is a discretionary node} 
f:internal_font_number; {used in character width calculation} 
l:halfword; {line number of current active node} 
node_r_stays_active:boolean; {should node |r| remain in the active list?} 
line_width:scaled; {the current line will be justified to this width} 
fit_class:very_loose_fit..tight_fit; {possible fitness class of test line} 
b:halfword; {badness of test line} 
d:integer; {demerits of test line} 
artificial_demerits:boolean; {has |d| been forced to zero?} 
save_link:pointer; {temporarily holds value of |link(cur_p)|} 
shortfall:scaled; {used in badness calculations} 

MODULE: 'Make sure that |pi| is in the proper range'
(*PASCAL module 831*)
if abs(pi)>=inf_penalty then 
  if pi>0 then return {this breakpoint is inhibited by infinite penalty} 
  else pi:=eject_penalty {this breakpoint will be forced} 

MODULE: 'If node |r|...'
(*PASCAL module 832*)
(*inner loop*) 
if type(r)=delta_node then 
  begin do_all_six(update_width); 
  prev_prev_r:=prev_r; prev_r:=r; goto continue; 
  end 

MODULE: 'Global... '
(*PASCAL module 833*)
minimal_demerits:array[very_loose_fit..tight_fit] of integer; {best total 
  demerits known for current line class and position, given the fitness} 
minimum_demerits:integer; {best total demerits known for current line class 
  and position} 
best_place:array[very_loose_fit..tight_fit] of pointer; {how to achieve 
  |minimal_demerits|} 
best_pl_line:array[very_loose_fit..tight_fit] of halfword; {corresponding 
  line number} 

MODULE: 'Get ready to start...'
(*PASCAL module 834*)
minimum_demerits:=awful_bad; 
minimal_demerits[tight_fit]:=awful_bad; 
minimal_demerits[decent_fit]:=awful_bad; 
minimal_demerits[loose_fit]:=awful_bad; 
minimal_demerits[very_loose_fit]:=awful_bad; 

MODULE: 'If a line number class...'
(*PASCAL module 835*)
begin l:=line_number(r); 
if l>old_l then 
  begin {now we are no longer in the inner loop} 
  if (minimum_demerits<awful_bad)and 
      ((old_l<>easy_line)or(r=last_active)) then 
    
INSERT: 'Create new active nodes for the best feasible breaks       just found'
; 
  if r=last_active then return; 
  
INSERT: 'Compute the new line width'
; 
  end; 
end 

MODULE: 'Create new active nodes...'
(*PASCAL module 836*)
begin if no_break_yet then 
INSERT: 'Compute the values of |break_width|'
; 

INSERT: 'Insert a delta node to prepare for breaks at |cur_p|'
; 
if abs(adj_demerits)>=awful_bad-minimum_demerits then 
  minimum_demerits:=awful_bad-1 
else minimum_demerits:=minimum_demerits+abs(adj_demerits); 
for fit_class:=very_loose_fit to tight_fit do 
  begin if minimal_demerits[fit_class]<=minimum_demerits then 
    
INSERT: 'Insert a new active node       from |best_place[fit_class]| to |cur_p|'
; 
  minimal_demerits[fit_class]:=awful_bad; 
  end; 
minimum_demerits:=awful_bad; 

INSERT: 'Insert a delta node to prepare for the next active node'
; 
end 

MODULE: 'Compute the values of |break...'
(*PASCAL module 837*)
begin no_break_yet:=false; do_all_six(set_break_width_to_background); 
s:=cur_p; 
if break_type>unhyphenated then if cur_p<>null then 
  
INSERT: 'Compute the discretionary |break_width| values'
; 
while s<>null do 
  begin if is_char_node(s) then goto done; 
  case type(s) of 
  glue_node:
INSERT: 'Subtract glue from |break_width|'
; 
  penalty_node: do_nothing; 
  math_node: break_width[1]:=break_width[1]-width(s); 
  kern_node: if subtype(s)<>explicit then goto done 
    else break_width[1]:=break_width[1]-width(s); 
  othercases goto done 
  endcases;
 
  s:=link(s); 
  end; 
done: end 

MODULE: 'Subtract glue from |break...'
(*PASCAL module 838*)
begin v:=glue_ptr(s); break_width[1]:=break_width[1]-width(v); 
break_width[2+stretch_order(v)]:=break_width[2+stretch_order(v)]-stretch(v); 
break_width[6]:=break_width[6]-shrink(v); 
end 

MODULE: 'Glob... '
(*PASCAL module 839*)
disc_width:scaled; {the length of discretionary material preceding a break} 

MODULE: 'Compute the discretionary |break...'
(*PASCAL module 840*)
begin t:=replace_count(cur_p); v:=cur_p; s:=post_break(cur_p); 
while t>0 do 
  begin decr(t); v:=link(v); 
  
INSERT: 'Subtract the width of node |v| from |break_width|'
; 
  end; 
while s<>null do 
  begin 
INSERT: 'Add the width of node |s| to |break_width|'
; 
  s:=link(s); 
  end; 
break_width[1]:=break_width[1]+disc_width; 
if post_break(cur_p)=null then s:=link(v); 
          {nodes may be discardable after the break} 
end 

MODULE: 'Subtract the width of node |v|...'
(*PASCAL module 841*)
if is_char_node(v) then 
  begin f:=font(v); 
  break_width[1]:=break_width[1]-char_width(f)(char_info(f)(character(v))); 
  end 
else  case type(v) of 
  ligature_node: begin f:=font(lig_char(v));
 
    break_width[1]:=break_width[1]- 
      char_width(f)(char_info(f)(character(lig_char(v)))); 
    end; 
  hlist_node,vlist_node,rule_node,kern_node: 
    break_width[1]:=break_width[1]-width(v); 
  othercases confusion('disc1') 
(*this can''t happen disc1][\quad disc1*) 
  endcases 

MODULE: 'Add the width of node |s| to |b...'
(*PASCAL module 842*)
if is_char_node(s) then 
  begin f:=font(s); 
  break_width[1]:=break_width[1]+char_width(f)(char_info(f)(character(s))); 
  end 
else  case type(s) of 
  ligature_node: begin f:=font(lig_char(s)); 
    break_width[1]:=break_width[1]+ 
      char_width(f)(char_info(f)(character(lig_char(s)))); 
    end; 
  hlist_node,vlist_node,rule_node,kern_node: 
    break_width[1]:=break_width[1]+width(s); 
  othercases confusion('disc2') 
(*this can''t happen disc2][\quad disc2*) 
  endcases 

MODULE: 'Insert a delta node to prepare for breaks at |cur_p|'
(*PASCAL module 843*)
if type(prev_r)=delta_node then {modify an existing delta node} 
  begin do_all_six(convert_to_break_width); 
  end 
else if prev_r=active then {no delta node needed at the beginning} 
  begin do_all_six(store_break_width); 
  end 
else  begin q:=get_node(delta_node_size); link(q):=r; type(q):=delta_node;
 
  subtype(q):=0; {the |subtype| is not used} 
  do_all_six(new_delta_to_break_width); 
  link(prev_r):=q; prev_prev_r:=prev_r; prev_r:=q; 
  end 

MODULE: 'Insert a delta node to prepare for the next active node'
(*PASCAL module 844*)
if r<>last_active then 
  begin q:=get_node(delta_node_size); link(q):=r; type(q):=delta_node;
 
  subtype(q):=0; {the |subtype| is not used} 
  do_all_six(new_delta_from_break_width); 
  link(prev_r):=q; prev_prev_r:=prev_r; prev_r:=q; 
  end 

MODULE: 'Insert a new active node from |best_place[fit_class]| to |cur_p|'
(*PASCAL module 845*)
begin q:=get_node(passive_node_size); 
link(q):=passive; passive:=q; cur_break(q):=cur_p; 
stat incr(pass_number); serial(q):=pass_number;tats;
 
prev_break(q):=best_place[fit_class];
 
q:=get_node(active_node_size); break_node(q):=passive; 
line_number(q):=best_pl_line[fit_class]+1; 
fitness(q):=fit_class; type(q):=break_type; 
total_demerits(q):=minimal_demerits[fit_class]; 
link(q):=r; link(prev_r):=q; prev_r:=q; 
stat if tracing_paragraphs>0 then 
  
INSERT: 'Print a symbolic description of the new break node'
; 
tats;
 
end 

MODULE: 'Print a symbolic description of the new break node'
(*PASCAL module 846*)
begin print_nl('@'); print_int(serial(passive)); 
(*\AT!\AT!*) 
print(': line '); print_int(line_number(q)-1); 
print_char('.'); print_int(fit_class); 
if break_type=hyphenated then print_char('-'); 
print(' t='); print_int(total_demerits(q)); 
print(' -> @'); 
if prev_break(passive)=null then print_char('0') 
else print_int(serial(prev_break(passive))); 
end 

MODULE: 'Glob... '
(*PASCAL module 847*)
easy_line:halfword; {line numbers |>easy_line| are equivalent in break nodes} 
last_special_line:halfword; {line numbers |>last_special_line| all have 
  the same width} 
first_width:scaled; {the width of all lines |<=last_special_line|, if 
  no \.[\\parshape] has been specified} 
second_width:scaled; {the width of all lines |>last_special_line|} 
first_indent:scaled; {left margin to go with |first_width|} 
second_indent:scaled; {left margin to go with |second_width|} 

MODULE: 'Get ready to start...'
(*PASCAL module 848*)
if par_shape_ptr=null then 
  if hang_indent=0 then 
    begin last_special_line:=0; second_width:=hsize; 
    second_indent:=0; 
    end 
  else 
INSERT: 'Set line length parameters in preparation for hanging indentation'

else  begin last_special_line:=info(par_shape_ptr)-1; 
  second_width:=mem[par_shape_ptr+2*(last_special_line+1)].sc; 
  second_indent:=mem[par_shape_ptr+2*last_special_line+1].sc; 
  end; 
if looseness=0 then easy_line:=last_special_line 
else easy_line:=max_halfword 

MODULE: 'Set line length parameters in preparation for hanging indentation'
(*PASCAL module 849*)
begin last_special_line:=abs(hang_after); 
if hang_after<0 then 
  begin first_width:=hsize-abs(hang_indent); 
  if hang_indent>=0 then first_indent:=hang_indent 
  else first_indent:=0; 
  second_width:=hsize; second_indent:=0; 
  end 
else  begin first_width:=hsize; first_indent:=0; 
  second_width:=hsize-abs(hang_indent); 
  if hang_indent>=0 then second_indent:=hang_indent 
  else second_indent:=0; 
  end; 
end 

MODULE: 'Compute the new line width'
(*PASCAL module 850*)
if l>easy_line then 
  begin line_width:=second_width; old_l:=max_halfword-1; 
  end 
else  begin old_l:=l; 
  if l>last_special_line then line_width:=second_width 
  else if par_shape_ptr=null then line_width:=first_width 
  else line_width:=mem[par_shape_ptr+2*l ].sc; 
  end 

MODULE: 'Consider the demerits for a line from |r| to |cur_p|...'
(*PASCAL module 851*)
begin artificial_demerits:=false;
 
(*inner loop*) 
shortfall:=line_width-cur_active_width[1]; {we're this much too short} 
if shortfall>0 then 
  
INSERT: 'Set the value of |b| to the badness for stretching the line,     and compute the corresponding |fit_class|'

else 
INSERT: 'Set the value of |b| to the badness for shrinking the line,     and compute the corresponding |fit_class|'
; 
if (b>inf_bad)or(pi=eject_penalty) then 
  
INSERT: 'Prepare to deactivate node~|r|, and |goto deactivate| unless     there is a reason to consider lines of text from |r| to |cur_p|'

else  begin prev_r:=r; 
  if b>threshold then goto continue; 
  node_r_stays_active:=true; 
  end; 

INSERT: 'Record a new feasible break'
; 
if node_r_stays_active then goto continue; {|prev_r| has been set to |r|} 
deactivate: 
INSERT: 'Deactivate node |r|'
; 
end 

MODULE: 'Set the value of |b| to the badness for stretching...'
(*PASCAL module 852*)
if (cur_active_width[3]<>0)or(cur_active_width[4]<>0)or 
  (cur_active_width[5]<>0) then 
  begin b:=0; fit_class:=decent_fit; {infinite stretch} 
  end 
else  begin if shortfall>7230584 then if cur_active_width[2]<1663497 then 
    begin b:=inf_bad; fit_class:=very_loose_fit; goto done1; 
    end; 
  b:=badness(shortfall,cur_active_width[2]); 
  if b>12 then 
    if b>99 then fit_class:=very_loose_fit 
    else fit_class:=loose_fit 
  else fit_class:=decent_fit; 
  done1: 
  end 

MODULE: 'Set the value of |b| to the badness for shrinking...'
(*PASCAL module 853*)
begin if -shortfall>cur_active_width[6] then b:=inf_bad+1 
else b:=badness(-shortfall,cur_active_width[6]); 
if b>12 then fit_class:=tight_fitelse fit_class:=decent_fit; 
end 

MODULE: 'Prepare to deactivate node~|r|, and |goto deactivate| unless...'
(*PASCAL module 854*)
begin if final_pass and (minimum_demerits=awful_bad) and 
   (link(r)=last_active) and 
   (prev_r=active) then 
  artificial_demerits:=true {set demerits zero, this break is forced} 
else if b>threshold then goto deactivate; 
node_r_stays_active:=false; 
end 

MODULE: 'Record a new feasible break'
(*PASCAL module 855*)
if artificial_demerits then d:=0 
else 
INSERT: 'Compute the demerits, |d|, from |r| to |cur_p|'
; 
stat if tracing_paragraphs>0 then 
  
INSERT: 'Print a symbolic description of this feasible break'
; 
tats;
 
d:=d+total_demerits(r); {this is the minimum total demerits 
  from the beginning to |cur_p| via |r|} 
if d<=minimal_demerits[fit_class] then 
  begin minimal_demerits[fit_class]:=d; 
  best_place[fit_class]:=break_node(r); best_pl_line[fit_class]:=l; 
  if d<minimum_demerits then minimum_demerits:=d; 
  end 

MODULE: 'Print a symbolic description of this feasible break'
(*PASCAL module 856*)
begin if printed_node<>cur_p then 
  
INSERT: 'Print the list between |printed_node| and |cur_p|,     then set |printed_node:=cur_p|'
; 
print_nl('@'); 
(*\AT!*) 
if cur_p=null then print_esc('par') 
else if type(cur_p)<>glue_node then 
  begin if type(cur_p)=penalty_node then print_esc('penalty') 
  else if type(cur_p)=disc_node then print_esc('discretionary') 
  else if type(cur_p)=kern_node then print_esc('kern') 
  else print_esc('math'); 
  end; 
print(' via @'); 
if break_node(r)=null then print_char('0') 
else print_int(serial(break_node(r))); 
print(' b='); 
if b>inf_bad then print_char('*')else print_int(b); 
(**\relax*) 
print(' p='); print_int(pi); print(' d='); 
if artificial_demerits then print_char('*')else print_int(d); 
end 

MODULE: 'Print the list between |printed_node| and |cur_p|...'
(*PASCAL module 857*)
begin print_nl(''); 
if cur_p=null then short_display(link(printed_node)) 
else  begin save_link:=link(cur_p); 
  link(cur_p):=null; print_nl(''); short_display(link(printed_node)); 
  link(cur_p):=save_link; 
  end; 
printed_node:=cur_p; 
end 

MODULE: 'Update the value of |printed_node|...'
(*PASCAL module 858*)
if cur_p=printed_node then if cur_p<>null then if type(cur_p)=disc_node then 
  begin t:=replace_count(cur_p); 
  while t>0 do 
    begin decr(t); printed_node:=link(printed_node); 
    end; 
  end 

MODULE: 'Compute the demerits, |d|, from |r| to |cur_p|'
(*PASCAL module 859*)
begin d:=line_penalty+b; 
if abs(d)>=10000 then d:=100000000else d:=d*d; 
if pi<>0 then 
  if pi>0 then d:=d+pi*pi 
  else if pi>eject_penalty then d:=d-pi*pi; 
if (break_type=hyphenated)and(type(r)=hyphenated) then 
  if cur_p<>null then d:=d+double_hyphen_demerits 
  else d:=d+final_hyphen_demerits; 
if abs(fit_class-fitness(r))>1 then d:=d+adj_demerits; 
end 

MODULE: 'Deactivate node |r|'
(*PASCAL module 860*)
link(prev_r):=link(r); free_node(r,active_node_size); 
if prev_r=active then 
INSERT: 'Update the active widths, since the first active   node has been deleted'

else if type(prev_r)=delta_node then 
  begin r:=link(prev_r); 
  if r=last_active then 
    begin do_all_six(downdate_width); 
    link(prev_prev_r):=last_active; 
    free_node(prev_r,delta_node_size); prev_r:=prev_prev_r; 
    end 
  else if type(r)=delta_node then 
    begin do_all_six(update_width); 
    do_all_six(combine_two_deltas); 
    link(prev_r):=link(r); free_node(r,delta_node_size); 
    end; 
  end 

MODULE: 'Update the active widths,...'
(*PASCAL module 861*)
begin r:=link(active); 
if type(r)=delta_node then 
  begin do_all_six(update_active); 
  do_all_six(copy_to_cur_active); 
  link(active):=link(r); free_node(r,delta_node_size); 
  end; 
end 

MODULE: 'Local variables for line breaking'
(*PASCAL module 862*)
auto_breaking:boolean; {is node |cur_p| outside a formula?} 
prev_p:pointer; {helps to determine when glue nodes are breakpoints} 
q,r,s,prev_s:pointer; {miscellaneous nodes of temporary interest} 
f:internal_font_number; {used when calculating character widths} 

MODULE: 'Find optimal breakpoints'
(*PASCAL module 863*)
threshold:=pretolerance; 
if threshold>=0 then 
  begin stat if tracing_paragraphs>0 then 
    begin begin_diagnostic; print_nl('@firstpass');end;;tats;
 
  second_pass:=false; final_pass:=false; 
  end 
else  begin threshold:=tolerance; second_pass:=true; 
  final_pass:=(emergency_stretch<=0); 
  stat if tracing_paragraphs>0 then begin_diagnostic;tats; 
  end; 
loop  begin if threshold>inf_bad then threshold:=inf_bad; 
  if second_pass then 
INSERT: 'Initialize for hyphenating a paragraph'
; 
  
INSERT: 'Create an active breakpoint representing the beginning of the paragraph'
; 
  cur_p:=link(temp_head); auto_breaking:=true;
 
  prev_p:=cur_p; {glue at beginning is not a legal breakpoint} 
  while (cur_p<>null)and(link(active)<>last_active) do 
    
INSERT: 'Call |try_break| if |cur_p| is a legal breakpoint;     on the second pass, also try to hyphenate the next     word, if |cur_p| is a glue node;     then advance |cur_p| to the next node of the paragraph     that could possibly be a legal breakpoint'
; 
  if cur_p=null then 
    
INSERT: 'Try the final line break at the end of the paragraph,     and |goto done| if the desired breakpoints have been found'
; 
  
INSERT: 'Clean up the memory by removing the break nodes'
; 
  if not second_pass then 
    beginstat if tracing_paragraphs>0 then print_nl('@secondpass');;tats
 
    threshold:=tolerance; second_pass:=true; final_pass:=(emergency_stretch<=0); 
    end {if at first you don't succeed, \dots} 
  else begin stat if tracing_paragraphs>0 then 
      print_nl('@emergencypass');;tats
 
    background[2]:=background[2]+emergency_stretch; final_pass:=true; 
    end; 
  end; 
done: stat if tracing_paragraphs>0 then 
  begin end_diagnostic(true); normalize_selector; 
  end;tats
 

MODULE: 'Create an active breakpoint representing the beginning of the paragraph'
(*PASCAL module 864*)
q:=get_node(active_node_size); 
type(q):=unhyphenated; fitness(q):=decent_fit; 
link(q):=last_active; break_node(q):=null; 
line_number(q):=prev_graf+1; total_demerits(q):=0; link(active):=q; 
do_all_six(store_background);
 
passive:=null; printed_node:=temp_head; pass_number:=0; 
font_in_short_display:=null_font 

MODULE: 'Clean... '
(*PASCAL module 865*)
q:=link(active); 
while q<>last_active do 
  begin cur_p:=link(q); 
  if type(q)=delta_node then free_node(q,delta_node_size) 
  else free_node(q,active_node_size); 
  q:=cur_p; 
  end; 
q:=passive; 
while q<>null do 
  begin cur_p:=link(q); 
  free_node(q,passive_node_size); 
  q:=cur_p; 
  end 

MODULE: 'Call |try_break| if |cur_p| is a legal breakpoint...'
(*PASCAL module 866*)
begin if is_char_node(cur_p) then 
  
INSERT: 'Advance \(c)|cur_p| to the node following the present     string of characters'
; 
case type(cur_p) of 
hlist_node,vlist_node,rule_node: act_width:=act_width+width(cur_p); 
whatsit_node: 
INSERT: 'Advance \(p)past a whatsit node in the \(l)|line_break| loop'
; 
glue_node: begin 
INSERT: 'If node |cur_p| is a legal breakpoint, call |try_break|;   then update the active widths by including the glue in |glue_ptr(cur_p)|'
; 
  if second_pass and auto_breaking then 
    
INSERT: 'Try to hyphenate the following word'
; 
  end; 
kern_node: if subtype(cur_p)=explicit then kern_break 
  else act_width:=act_width+width(cur_p); 
ligature_node: begin f:=font(lig_char(cur_p)); 
  act_width:=act_width+char_width(f)(char_info(f)(character(lig_char(cur_p)))); 
  end; 
disc_node: 
INSERT: 'Try to break after a discretionary fragment, then |goto done5|'
; 
math_node: begin auto_breaking:=(subtype(cur_p)=after); kern_break; 
  end; 
penalty_node: try_break(penalty(cur_p),unhyphenated); 
mark_node,ins_node,adjust_node: do_nothing; 
othercases confusion('paragraph') 
(*this can''t happen paragraph][\quad paragraph*) 
endcases;
 
prev_p:=cur_p; cur_p:=link(cur_p); 
done5:end 

MODULE: 'Advance \(c)|cur_p| to the node following the present string...'
(*PASCAL module 867*)
begin prev_p:=cur_p; 
repeat f:=font(cur_p); 
act_width:=act_width+char_width(f)(char_info(f)(character(cur_p))); 
cur_p:=link(cur_p); 
until not is_char_node(cur_p); 
end 

MODULE: 'If node |cur_p| is a legal breakpoint, call...'
(*PASCAL module 868*)
if auto_breaking then 
  begin if is_char_node(prev_p) then try_break(0,unhyphenated) 
  else if precedes_break(prev_p) then try_break(0,unhyphenated) 
  else if (type(prev_p)=kern_node)and(subtype(prev_p)<>explicit) then 
    try_break(0,unhyphenated); 
  end; 
check_shrinkage(glue_ptr(cur_p)); q:=glue_ptr(cur_p); 
act_width:=act_width+width(q); 
active_width[2+stretch_order(q)]:= 
  active_width[2+stretch_order(q)]+stretch(q);
 
active_width[6]:=active_width[6]+shrink(q) 

MODULE: 'Try to break after a discretionary fragment...'
(*PASCAL module 869*)
begin s:=pre_break(cur_p); disc_width:=0; 
if s=null then try_break(ex_hyphen_penalty,hyphenated) 
else  begin repeat 
INSERT: 'Add the width of node |s| to |disc_width|'
; 
    s:=link(s); 
  until s=null; 
  act_width:=act_width+disc_width; 
  try_break(hyphen_penalty,hyphenated); 
  act_width:=act_width-disc_width; 
  end; 
r:=replace_count(cur_p); s:=link(cur_p); 
while r>0 do 
  begin 
INSERT: 'Add the width of node |s| to |act_width|'
; 
  decr(r); s:=link(s); 
  end; 
prev_p:=cur_p; cur_p:=s; goto done5; 
end 

MODULE: 'Add the width of node |s| to |disc_width|'
(*PASCAL module 870*)
if is_char_node(s) then 
  begin f:=font(s); 
  disc_width:=disc_width+char_width(f)(char_info(f)(character(s))); 
  end 
else  case type(s) of 
  ligature_node: begin f:=font(lig_char(s)); 
    disc_width:=disc_width+ 
      char_width(f)(char_info(f)(character(lig_char(s)))); 
    end; 
  hlist_node,vlist_node,rule_node,kern_node: 
    disc_width:=disc_width+width(s); 
  othercases confusion('disc3') 
(*this can''t happen disc3][\quad disc3*) 
  endcases 

MODULE: 'Add the width of node |s| to |act_width|'
(*PASCAL module 871*)
if is_char_node(s) then 
  begin f:=font(s); 
  act_width:=act_width+char_width(f)(char_info(f)(character(s))); 
  end 
else  case type(s) of 
  ligature_node: begin f:=font(lig_char(s)); 
    act_width:=act_width+ 
      char_width(f)(char_info(f)(character(lig_char(s)))); 
    end; 
  hlist_node,vlist_node,rule_node,kern_node: 
    act_width:=act_width+width(s); 
  othercases confusion('disc4') 
(*this can''t happen disc4][\quad disc4*) 
  endcases 

MODULE: 'Glob... '
(*PASCAL module 872*)
best_bet:pointer; {use this passive node and its predecessors} 
fewest_demerits:integer; {the demerits associated with |best_bet|} 
best_line:halfword; {line number following the last line of the new paragraph} 
actual_looseness:integer; {the difference between |line_number(best_bet)| 
  and the optimum |best_line|} 
line_diff:integer; {the difference between the current line number and 
  the optimum |best_line|} 

MODULE: 'Try the final line break at the end of the paragraph...'
(*PASCAL module 873*)
begin try_break(eject_penalty,hyphenated); 
if link(active)<>last_active then 
  begin 
INSERT: 'Find an active node with fewest demerits'
; 
  if looseness=0 then goto done; 
  
INSERT: 'Find the best active node for the desired looseness'
; 
  if (actual_looseness=looseness)or final_pass then goto done; 
  end; 
end 

MODULE: 'Find an active node...'
(*PASCAL module 874*)
r:=link(active); fewest_demerits:=awful_bad; 
repeat if type(r)<>delta_node then if total_demerits(r)<fewest_demerits then 
  begin fewest_demerits:=total_demerits(r); best_bet:=r; 
  end; 
r:=link(r); 
until r=last_active; 
best_line:=line_number(best_bet) 

MODULE: 'Find the best active node...'
(*PASCAL module 875*)
begin r:=link(active); actual_looseness:=0; 
repeat if type(r)<>delta_node then 
  begin line_diff:=line_number(r)-best_line; 
  if ((line_diff<actual_looseness)and(looseness<=line_diff))or 
  ((line_diff>actual_looseness)and(looseness>=line_diff)) then 
    begin best_bet:=r; actual_looseness:=line_diff; 
    fewest_demerits:=total_demerits(r); 
    end 
  else if (line_diff=actual_looseness)and 
    (total_demerits(r)<fewest_demerits) then 
    begin best_bet:=r; fewest_demerits:=total_demerits(r); 
    end; 
  end; 
r:=link(r); 
until r=last_active; 
best_line:=line_number(best_bet); 
end 

MODULE: 'Break the paragraph at the chosen...'
(*PASCAL module 876*)
post_line_break(final_widow_penalty) 

MODULE: 'Declare subprocedures for |line_break|'
(*PASCAL module 877*)
procedure post_line_break(final_widow_penalty:integer); 
label done,done1; 
var q,r,s:pointer; {temporary registers for list manipulation} 
disc_break:boolean; {was the current break at a discretionary node?} 
post_disc_break:boolean; {and did it have a nonempty post-break part?} 
cur_width:scaled; {width of line number |cur_line|} 
cur_indent:scaled; {left margin of line number |cur_line|} 
t:quarterword; {used for replacement counts in discretionary nodes} 
pen:integer; {use when calculating penalties between lines} 
cur_line: halfword; {the current line number being justified} 
begin 
INSERT: 'Reverse the links of the relevant passive nodes, setting |cur_p| to the   first breakpoint'
; 
cur_line:=prev_graf+1; 
repeat 
INSERT: 'Justify the line ending at breakpoint |cur_p|, and append it to the   current vertical list, together with associated penalties and other   insertions'
; 
incr(cur_line); cur_p:=next_break(cur_p); 
if cur_p<>null then if not post_disc_break then 
  
INSERT: 'Prune unwanted nodes at the beginning of the next line'
; 
until cur_p=null; 
if (cur_line<>best_line)or(link(temp_head)<>null) then 
  confusion('line breaking'); 
(*this can''t happen line breaking][\quad line breaking*) 
prev_graf:=best_line-1; 
end; 

MODULE: 'Reverse the links of the relevant passive nodes...'
(*PASCAL module 878*)
q:=break_node(best_bet); cur_p:=null; 
repeat r:=q; q:=prev_break(q); next_break(r):=cur_p; cur_p:=r; 
until q=null 

MODULE: 'Prune unwanted nodes at the beginning of the next line'
(*PASCAL module 879*)
begin r:=temp_head; 
loop  begin q:=link(r); 
  if q=cur_break(cur_p) then goto done1; 
    {|cur_break(cur_p)| is the next breakpoint} 
  {now |q| cannot be |null|} 
  if is_char_node(q) then goto done1; 
  if non_discardable(q) then goto done1; 
  if type(q)=kern_node then if subtype(q)<>explicit then goto done1; 
  r:=q; {now |type(q)=glue_node|, |kern_node|, |math_node| or |penalty_node|} 
  end; 
done1: if r<>temp_head then 
  begin link(r):=null; flush_node_list(link(temp_head)); 
  link(temp_head):=q; 
  end; 
end 

MODULE: 'Justify the line ending at breakpoint |cur_p|, and append it...'
(*PASCAL module 880*)

INSERT: 'Modify the end of the line to reflect the nature of the break and to include   \.{\\rightskip}; also set the proper value of |disc_break|'
; 

INSERT: 'Put the \(l)\.{\\leftskip} glue at the left and detach this line'
; 

INSERT: 'Call the packaging subroutine, setting |just_box| to the justified box'
; 

INSERT: 'Append the new box to the current vertical list, followed by the list of   special nodes taken out of the box by the packager'
; 

INSERT: 'Append a penalty node, if a nonzero penalty is appropriate'


MODULE: 'Modify the end of the line...'
(*PASCAL module 881*)
q:=cur_break(cur_p); disc_break:=false; post_disc_break:=false; 
if q<>null then {|q| cannot be a |char_node|} 
  if type(q)=glue_node then 
    begin delete_glue_ref(glue_ptr(q)); 
    glue_ptr(q):=right_skip; 
    subtype(q):=right_skip_code+1; add_glue_ref(right_skip); 
    goto done; 
    end 
  else  begin if type(q)=disc_node then 
      
INSERT: 'Change discretionary to compulsory and set         |disc_break:=true|'

    else if (type(q)=math_node)or(type(q)=kern_node) then width(q):=0; 
    end 
else  begin q:=temp_head; 
  while link(q)<>null do q:=link(q); 
  end; 

INSERT: 'Put the \(r)\.{\\rightskip} glue after node |q|'
; 
done: 

MODULE: 'Change discretionary to compulsory...'
(*PASCAL module 882*)
begin t:=replace_count(q); 

INSERT: 'Destroy the |t| nodes following |q|, and    make |r| point to the following node'
; 
if post_break(q)<>null then 
INSERT: 'Transplant the post-break list'
; 
if pre_break(q)<>null then 
INSERT: 'Transplant the pre-break list'
; 
link(q):=r; disc_break:=true; 
end 

MODULE: 'Destroy the |t| nodes following |q|...'
(*PASCAL module 883*)
if t=0 then r:=link(q) 
else  begin r:=q; 
  while t>1 do 
    begin r:=link(r); decr(t); 
    end; 
  s:=link(r); 
  r:=link(s); link(s):=null; 
  flush_node_list(link(q)); replace_count(q):=0; 
  end 

MODULE: 'Transplant the post-break list'
(*PASCAL module 884*)
begin s:=post_break(q); 
while link(s)<>null do s:=link(s); 
link(s):=r; r:=post_break(q); post_break(q):=null; post_disc_break:=true; 
end 

MODULE: 'Transplant the pre-break list'
(*PASCAL module 885*)
begin s:=pre_break(q); link(q):=s; 
while link(s)<>null do s:=link(s); 
pre_break(q):=null; q:=s; 
end 

MODULE: 'Put the \(r)\.{\\rightskip} glue after node |q|'
(*PASCAL module 886*)
r:=new_param_glue(right_skip_code); link(r):=link(q); link(q):=r; q:=r 

MODULE: 'Put the \(l)\.{\\leftskip} glue at the left...'
(*PASCAL module 887*)
r:=link(q); link(q):=null; q:=link(temp_head); link(temp_head):=r; 
if left_skip<>zero_glue then 
  begin r:=new_param_glue(left_skip_code); 
  link(r):=q; q:=r; 
  end 

MODULE: 'Append the new box to the current vertical list...'
(*PASCAL module 888*)
append_to_vlist(just_box); 
if adjust_head<>adjust_tail then 
  begin link(tail):=link(adjust_head); tail:=adjust_tail; 
   end; 
adjust_tail:=null 

MODULE: 'Call the packaging subroutine...'
(*PASCAL module 889*)
if cur_line>last_special_line then 
  begin cur_width:=second_width; cur_indent:=second_indent; 
  end 
else if par_shape_ptr=null then 
  begin cur_width:=first_width; cur_indent:=first_indent; 
  end 
else  begin cur_width:=mem[par_shape_ptr+2*cur_line].sc; 
  cur_indent:=mem[par_shape_ptr+2*cur_line-1].sc; 
  end; 
adjust_tail:=adjust_head; just_box:=hpack(q,cur_width,exactly); 
shift_amount(just_box):=cur_indent 

MODULE: 'Append a penalty node, if a nonzero penalty is appropriate'
(*PASCAL module 890*)
if cur_line+1<>best_line then 
  begin pen:=inter_line_penalty; 
  if cur_line=prev_graf+1 then pen:=pen+club_penalty; 
  if cur_line+2=best_line then pen:=pen+final_widow_penalty; 
  if disc_break then pen:=pen+broken_penalty; 
  if pen<>0 then 
    begin r:=new_penalty(pen); 
    link(tail):=r; tail:=r; 
    end; 
  end 

MODULE: 'Initialize for hyphenating...'
(*PASCAL module 891*)
begin init if trie_not_ready then init_trie;tini;
 
cur_lang:=init_cur_lang; l_hyf:=init_l_hyf; r_hyf:=init_r_hyf; 
end 

MODULE: 'Glob... '
(*PASCAL module 892*)
hc:array[0..65] of 0..256; {word to be hyphenated} 
hn:small_number; {the number of positions occupied in |hc|} 
ha,hb:pointer; {nodes |ha..hb| should be replaced by the hyphenated result} 
hf:internal_font_number; {font number of the letters in |hc|} 
hu:array[0..63] of 0..256; {like |hc|, before conversion to lowercase} 
hyf_char:integer; {hyphen character of the relevant font} 
cur_lang,init_cur_lang:ASCII_code; {current hyphenation table of interest} 
l_hyf,r_hyf,init_l_hyf,init_r_hyf:integer; {limits on fragment sizes} 
hyf_bchar:halfword; {boundary character after $c_n$} 

MODULE: 'Local variables for line...'
(*PASCAL module 893*)
j:small_number; {an index into |hc| or |hu|} 
c:0..255; {character being considered for hyphenation} 

MODULE: 'Try to hyphenate...'
(*PASCAL module 894*)
begin prev_s:=cur_p; s:=link(prev_s); 
if s<>null then 
  begin 
INSERT: 'Skip to node |ha|, or |goto done1| if no hyphenation     should be attempted'
; 
  if l_hyf+r_hyf>63 then goto done1; 
  
INSERT: 'Skip to node |hb|, putting letters into |hu| and |hc|'
; 
  
INSERT: 'Check that the nodes following |hb| permit hyphenation and that at least     |l_hyf+r_hyf| letters have been found, otherwise |goto done1|'
; 
  hyphenate; 
  end; 
done1: end 

MODULE: 'Declare subprocedures for |line_break|'
(*PASCAL module 895*)
(*\4*)
INSERT: 'Declare the function called |reconstitute|'

procedure hyphenate; 
label common_ending,done,found,found1,found2,not_found,exit; 
var 
INSERT: 'Local variables for hyphenation'
; 
begin 
INSERT: 'Find hyphen locations for the word in |hc|, or |return|'
; 

INSERT: 'If no hyphens were found, |return|'
; 

INSERT: 'Replace nodes |ha..hb| by a sequence of nodes that includes   the discretionary hyphens'
; 
exit:end; 

MODULE: 'Skip to node |ha|, or |goto done1|...'
(*PASCAL module 896*)
loop  begin if is_char_node(s) then 
    begin c:=qo(character(s)); hf:=font(s); 
    end 
  else if type(s)=ligature_node then 
    if lig_ptr(s)=null then goto continue 
    else begin q:=lig_ptr(s); c:=qo(character(q)); hf:=font(q); 
      end 
  else if (type(s)=kern_node)and(subtype(s)=normal) then goto continue 
  else if type(s)=whatsit_node then 
    begin 
INSERT: 'Advance \(p)past a whatsit node in the \(p)pre-hyphenation loop'
; 
    goto continue; 
    end 
  else goto done1; 
  if lc_code(c)<>0 then 
    if (lc_code(c)=c)or(uc_hyph>0) then goto done2 
    else goto done1; 
continue: prev_s:=s; s:=link(prev_s); 
  end; 
done2: hyf_char:=hyphen_char[hf]; 
if hyf_char<0 then goto done1; 
if hyf_char>255 then goto done1; 
ha:=prev_s 

MODULE: 'Skip to node |hb|, putting letters...'
(*PASCAL module 897*)
hn:=0; 
loop  begin if is_char_node(s) then 
    begin if font(s)<>hf then goto done3; 
    hyf_bchar:=character(s); c:=qo(hyf_bchar); 
    if lc_code(c)=0 then goto done3; 
    if hn=63 then goto done3; 
    hb:=s; incr(hn); hu[hn]:=c; hc[hn]:=lc_code(c); hyf_bchar:=non_char; 
    end 
  else if type(s)=ligature_node then 
    
INSERT: 'Move the characters of a ligature node to |hu| and |hc|;       but |goto done3| if they are not all letters'

  else if (type(s)=kern_node)and(subtype(s)=normal) then 
    begin hb:=s; 
    hyf_bchar:=font_bchar[hf]; 
    end 
  else goto done3; 
  s:=link(s); 
  end; 
done3: 

MODULE: 'Move the characters of a ligature node to |hu| and |hc|...'
(*PASCAL module 898*)
begin if font(lig_char(s))<>hf then goto done3; 
j:=hn; q:=lig_ptr(s);if q>null then hyf_bchar:=character(q); 
while q>null do 
  begin c:=qo(character(q)); 
  if lc_code(c)=0 then goto done3; 
  if j=63 then goto done3; 
  incr(j); hu[j]:=c; hc[j]:=lc_code(c);
 
  q:=link(q); 
  end; 
hb:=s; hn:=j; 
if odd(subtype(s)) then hyf_bchar:=font_bchar[hf]else hyf_bchar:=non_char; 
end 

MODULE: 'Check that the nodes following |hb| permit hyphenation...'
(*PASCAL module 899*)
if hn<l_hyf+r_hyf then goto done1; {|l_hyf| and |r_hyf| are |>=1|} 
loop  begin if not(is_char_node(s)) then 
    case type(s) of 
    ligature_node: do_nothing; 
    kern_node: if subtype(s)<>normal then goto done4; 
    whatsit_node,glue_node,penalty_node,ins_node,adjust_node,mark_node: 
      goto done4; 
    othercases goto done1 
    endcases; 
  s:=link(s); 
  end; 
done4: 

MODULE: 'Glob... '
(*PASCAL module 900*)
hyf:array [0..64] of 0..9; {odd values indicate discretionary hyphens} 
init_list:pointer; {list of punctuation characters preceding the word} 
init_lig:boolean; {does |init_list| represent a ligature?} 
init_lft:boolean; {if so, did the ligature involve a left boundary?} 

MODULE: 'Local variables for hyphenation'
(*PASCAL module 901*)
i,j,l:0..65; {indices into |hc| or |hu|} 
q,r,s:pointer; {temporary registers for list manipulation} 
bchar:halfword; {right boundary character of hyphenated word, or |non_char|} 

MODULE: 'If no hyphens were found, |return|'
(*PASCAL module 902*)
for j:=l_hyf to hn-r_hyf do if odd(hyf[j]) then goto found1; 
return; 
found1: 

MODULE: 'Replace nodes |ha..hb| by a sequence of nodes...'
(*PASCAL module 903*)
q:=link(hb); link(hb):=null; r:=link(ha); link(ha):=null; bchar:=hyf_bchar; 
if is_char_node(ha) then 
  if font(ha)<>hf then goto found2 
  else begin init_list:=ha; init_lig:=false; hu[0]:=qo(character(ha)); 
    end 
else if type(ha)=ligature_node then 
  if font(lig_char(ha))<>hf then goto found2 
  else begin init_list:=lig_ptr(ha); init_lig:=true; init_lft:=(subtype(ha)>1); 
    hu[0]:=qo(character(lig_char(ha))); 
    if init_list=null then if init_lft then 
      begin hu[0]:=256; init_lig:=false; 
      end; {in this case a ligature will be reconstructed from scratch} 
    free_node(ha,small_node_size); 
    end 
else begin {no punctuation found; look for left boundary} 
  if not is_char_node(r) then if type(r)=ligature_node then 
   if subtype(r)>1 then goto found2; 
  j:=1; s:=ha; init_list:=null; goto common_ending; 
  end; 
s:=cur_p; {we have |cur_p<>ha| because |type(cur_p)=glue_node|} 
while link(s)<>ha do s:=link(s); 
j:=0; goto common_ending; 
found2: s:=ha; j:=0; hu[0]:=256; init_lig:=false; init_list:=null; 
common_ending: flush_node_list(r); 

INSERT: 'Reconstitute nodes for the hyphenated word, inserting discretionary hyphens'
; 
flush_list(init_list) 

MODULE: 'Glob... '
(*PASCAL module 905*)
hyphen_passed:small_number; {first hyphen in a ligature, if any} 

MODULE: 'Declare the function called |reconstitute|'
(*PASCAL module 906*)
function reconstitute(j,n:small_number;bchar,hchar:halfword): 
  small_number; 
label continue,done; 
var p:pointer; {temporary register for list manipulation} 
t:pointer; {a node being appended to} 
q:four_quarters; {character information or a lig/kern instruction} 
cur_rh:halfword; {hyphen character for ligature testing} 
test_char:halfword; {hyphen or other character for ligature testing} 
w:scaled; {amount of kerning} 
k:font_index; {position of current lig/kern instruction} 
begin hyphen_passed:=0; t:=hold_head; w:=0; link(hold_head):=null; 
 {at this point |ligature_present=lft_hit=rt_hit=false|} 

INSERT: 'Set up data structures with the cursor following position |j|'
; 
continue:
INSERT: 'If there''s a ligature or kern at the cursor position, update the data   structures, possibly advancing~|j|; continue until the cursor moves'
; 

INSERT: 'Append a ligature and/or kern to the translation;   |goto continue| if the stack of inserted ligatures is nonempty'
; 
reconstitute:=j; 
end; 

MODULE: 'Glob... '
(*PASCAL module 907*)
cur_l,cur_r:halfword; {characters before and after the cursor} 
cur_q:pointer; {where a ligature should be detached} 
lig_stack:pointer; {unfinished business to the right of the cursor} 
ligature_present:boolean; {should a ligature node be made for |cur_l|?} 
lft_hit,rt_hit:boolean; {did we hit a ligature with a boundary character?} 

MODULE: 'Set up data structures with the cursor following position |j|'
(*PASCAL module 908*)
cur_l:=qi(hu[j]); cur_q:=t; 
if j=0 then 
  begin ligature_present:=init_lig; p:=init_list; 
  if ligature_present then lft_hit:=init_lft; 
  while p>null do 
    begin append_charnode_to_t(character(p)); p:=link(p); 
    end; 
  end 
else if cur_l<non_char then append_charnode_to_t(cur_l); 
lig_stack:=null; set_cur_r 

MODULE: 'If there''s a ligature or kern at the cursor position, update...'
(*PASCAL module 909*)
if cur_l=non_char then 
  begin k:=bchar_label[hf]; 
  if k=non_address then goto doneelse q:=font_info[k].qqqq; 
  end 
else begin q:=char_info(hf)(cur_l); 
  if char_tag(q)<>lig_tag then goto done; 
  k:=lig_kern_start(hf)(q); q:=font_info[k].qqqq; 
  if skip_byte(q)>stop_flag then 
    begin k:=lig_kern_restart(hf)(q); q:=font_info[k].qqqq; 
    end; 
  end; {now |k| is the starting address of the lig/kern program} 
if cur_rh<non_char then test_char:=cur_rhelse test_char:=cur_r; 
loopbegin if next_char(q)=test_char then if skip_byte(q)<=stop_flag then 
    if cur_rh<non_char then 
      begin hyphen_passed:=j; hchar:=non_char; cur_rh:=non_char; 
      goto continue; 
      end 
    else begin if hchar<non_char then if odd(hyf[j]) then 
        begin hyphen_passed:=j; hchar:=non_char; 
        end; 
      if op_byte(q)<kern_flag then 
      
INSERT: 'Carry out a ligature replacement, updating the cursor structure         and possibly advancing~|j|; |goto continue| if the cursor doesn''t         advance, otherwise |goto done|'
; 
      w:=char_kern(hf)(q); goto done; {this kern will be inserted below} 
     end; 
  if skip_byte(q)>=stop_flag then 
    if cur_rh=non_char then goto done 
    else begin cur_rh:=non_char; goto continue; 
      end; 
  k:=k+qo(skip_byte(q))+1; q:=font_info[k].qqqq; 
  end; 
done: 

MODULE: 'Append a ligature and/or kern to the translation...'
(*PASCAL module 910*)
wrap_lig(rt_hit); 
if w<>0 then 
  begin link(t):=new_kern(w); t:=link(t); w:=0; 
  end; 
if lig_stack>null then 
  begin cur_q:=t; cur_l:=character(lig_stack); ligature_present:=true; 
  pop_lig_stack; goto continue; 
  end 

MODULE: 'Carry out a ligature replacement, updating the cursor structure...'
(*PASCAL module 911*)
begin if cur_l=non_char then lft_hit:=true; 
if j=n then if lig_stack=null then rt_hit:=true; 
check_interrupt; {allow a way out in case there's an infinite ligature loop} 
case op_byte(q) of 
qi(1),qi(5):begin cur_l:=rem_byte(q); {\.[=:\?], \.[=:\?>]} 
  ligature_present:=true; 
  end; 
qi(2),qi(6):begin cur_r:=rem_byte(q); {\.[\?=:], \.[\?=:>]} 
  if lig_stack>null then character(lig_stack):=cur_r 
  else begin lig_stack:=new_lig_item(cur_r); 
    if j=n then bchar:=non_char 
    else begin p:=get_avail; lig_ptr(lig_stack):=p; 
      character(p):=qi(hu[j+1]); font(p):=hf; 
      end; 
    end; 
  end; 
qi(3):begin cur_r:=rem_byte(q); {\.[\?=:\?]} 
  p:=lig_stack; lig_stack:=new_lig_item(cur_r); link(lig_stack):=p; 
  end; 
qi(7),qi(11):begin wrap_lig(false); {\.[\?=:\?>], \.[\?=:\?>>]} 
  cur_q:=t; cur_l:=rem_byte(q); ligature_present:=true; 
  end; 
othercases begin cur_l:=rem_byte(q); ligature_present:=true; {\.[=:]} 
  if lig_stack>null then pop_lig_stack 
  else if j=n then goto done 
  else begin append_charnode_to_t(cur_r); incr(j); set_cur_r; 
    end; 
  end 
endcases; 
if op_byte(q)>qi(4) then if op_byte(q)<>qi(7) then goto done; 
goto continue; 
end 

MODULE: 'Local variables for hyph...'
(*PASCAL module 912*)
major_tail,minor_tail:pointer; {the end of lists in the main and 
  discretionary branches being reconstructed} 
c:ASCII_code; {character temporarily replaced by a hyphen} 
c_loc:0..63; {where that character came from} 
r_count:integer; {replacement count for discretionary} 
hyf_node:pointer; {the hyphen, if it exists} 

MODULE: 'Reconstitute nodes for the hyphenated word...'
(*PASCAL module 913*)
repeat l:=j; j:=reconstitute(j,hn,bchar,qi(hyf_char))+1; 
if hyphen_passed=0 then 
  begin link(s):=link(hold_head); 
  while link(s)>null do s:=link(s); 
  if odd(hyf[j-1]) then 
    begin l:=j; hyphen_passed:=j-1; link(hold_head):=null; 
    end; 
  end; 
if hyphen_passed>0 then 
  
INSERT: 'Create and append a discretionary node as an alternative to the     unhyphenated word, and continue to develop both branches until they     become equivalent'
; 
until j>hn; 
link(s):=q 

MODULE: 'Create and append a discretionary node as an alternative...'
(*PASCAL module 914*)
repeat r:=get_node(small_node_size); 
link(r):=link(hold_head); type(r):=disc_node; 
major_tail:=r; r_count:=0; 
while link(major_tail)>null do advance_major_tail; 
i:=hyphen_passed; hyf[i]:=0; 

INSERT: 'Put the \(c)characters |hu[l..i]| and a hyphen into |pre_break(r)|'
; 

INSERT: 'Put the \(c)characters |hu[i+1..@,]| into |post_break(r)|, appending to this   list and to |major_tail| until synchronization has been achieved'
; 

INSERT: 'Move pointer |s| to the end of the current list, and set |replace_count(r)|   appropriately'
; 
hyphen_passed:=j-1; link(hold_head):=null; 
until not odd(hyf[j-1]) 

MODULE: 'Put the \(c)characters |hu[l..i]| and a hyphen into |pre_break(r)|'
(*PASCAL module 915*)
minor_tail:=null; pre_break(r):=null; hyf_node:=new_character(hf,hyf_char); 
if hyf_node<>null then 
  begin incr(i); c:=hu[i]; hu[i]:=hyf_char; free_avail(hyf_node); 
  end; 
while l<=i do 
  begin l:=reconstitute(l,i,font_bchar[hf],non_char)+1; 
  if link(hold_head)>null then 
    begin if minor_tail=null then pre_break(r):=link(hold_head) 
    else link(minor_tail):=link(hold_head); 
    minor_tail:=link(hold_head); 
    while link(minor_tail)>null do minor_tail:=link(minor_tail); 
    end; 
  end; 
if hyf_node<>null then 
  begin hu[i]:=c; {restore the character in the hyphen position} 
  l:=i; decr(i); 
  end 

MODULE: 'Put the \(c)characters |hu[i+1..@,]| into |post_break(r)|...'
(*PASCAL module 916*)
minor_tail:=null; post_break(r):=null; c_loc:=0; 
if bchar_label[hf]<>non_address then {put left boundary at beginning of new line} 
  begin decr(l); c:=hu[l]; c_loc:=l; hu[l]:=256; 
  end; 
while l<j do 
  begin repeat l:=reconstitute(l,hn,bchar,non_char)+1; 
  if c_loc>0 then 
    begin hu[c_loc]:=c; c_loc:=0; 
    end; 
  if link(hold_head)>null then 
    begin if minor_tail=null then post_break(r):=link(hold_head) 
    else link(minor_tail):=link(hold_head); 
    minor_tail:=link(hold_head); 
    while link(minor_tail)>null do minor_tail:=link(minor_tail); 
    end; 
  until l>=j; 
  while l>j do 
    
INSERT: 'Append characters of |hu[j..@,]| to |major_tail|, advancing~|j|'
; 
  end 

MODULE: 'Append characters of |hu[j..@,]|...'
(*PASCAL module 917*)
begin j:=reconstitute(j,hn,bchar,non_char)+1; 
link(major_tail):=link(hold_head); 
while link(major_tail)>null do advance_major_tail; 
end 

MODULE: 'Move pointer |s| to the end of the current list...'
(*PASCAL module 918*)
if r_count>127 then {we have to forget the discretionary hyphen} 
  begin link(s):=link(r); link(r):=null; flush_node_list(r); 
  end 
else begin link(s):=r; replace_count(r):=r_count; 
  end; 
s:=major_tail 

MODULE: 'Types... '
(*PASCAL module 920*)
trie_pointer=0..trie_size; {an index into |trie|} 

MODULE: 'Glob... '
(*PASCAL module 921*)
trie:array[trie_pointer] of two_halves; {|trie_link|, |trie_char|, |trie_op|} 
hyf_distance:array[1..trie_op_size] of small_number; {position |k-j| of $n_j$} 
hyf_num:array[1..trie_op_size] of small_number; {value of $n_j$} 
hyf_next:array[1..trie_op_size] of quarterword; {continuation code} 
op_start:array[ASCII_code] of 0..trie_op_size; {offset for current language} 

MODULE: 'Local variables for hyph...'
(*PASCAL module 922*)
z:trie_pointer; {an index into |trie|} 
v:integer; {an index into |hyf_distance|, etc.} 

MODULE: 'Find hyphen locations for the word in |hc|...'
(*PASCAL module 923*)
for j:=0 to hn do hyf[j]:=0; 

INSERT: 'Look for the word |hc[1..hn]| in the exception table, and |goto found| (with   |hyf| containing the hyphens) if an entry is found'
; 
if trie_char(cur_lang+1)<>qi(cur_lang) then return; {no patterns for |cur_lang|} 
hc[0]:=0; hc[hn+1]:=0; hc[hn+2]:=256; {insert delimiters} 
for j:=0 to hn-r_hyf+1 do 
  begin z:=trie_link(cur_lang+1)+hc[j]; l:=j; 
  while hc[l]=qo(trie_char(z)) do 
    begin if trie_op(z)<>min_quarterword then 
      
INSERT: 'Store \(m)maximum values in the |hyf| table'
; 
    incr(l); z:=trie_link(z)+hc[l]; 
    end; 
  end; 
found: for j:=0 to l_hyf-1 do hyf[j]:=0; 
for j:=0 to r_hyf-1 do hyf[hn-j]:=0 

MODULE: 'Store \(m)maximum values in the |hyf| table'
(*PASCAL module 924*)
begin v:=trie_op(z); 
repeat v:=v+op_start[cur_lang]; i:=l-hyf_distance[v]; 
if hyf_num[v]>hyf[i] then hyf[i]:=hyf_num[v]; 
v:=hyf_next[v]; 
until v=min_quarterword; 
end 

MODULE: 'Types... '
(*PASCAL module 925*)
hyph_pointer=0..hyph_size; {an index into the ordered hash table} 

MODULE: 'Glob... '
(*PASCAL module 926*)
hyph_word:array[hyph_pointer] of str_number; {exception words} 
hyph_list:array[hyph_pointer] of pointer; {lists of hyphen positions} 
hyph_count:hyph_pointer; {the number of words in the exception dictionary} 

MODULE: 'Local variables for init...'
(*PASCAL module 927*)
z:hyph_pointer; {runs through the exception dictionary} 

MODULE: 'Set init...'
(*PASCAL module 928*)
for z:=0 to hyph_size do 
  begin hyph_word[z]:=0; hyph_list[z]:=null; 
  end; 
hyph_count:=0; 

MODULE: 'Local variables for hyph...'
(*PASCAL module 929*)
h:hyph_pointer; {an index into |hyph_word| and |hyph_list|} 
k:str_number; {an index into |str_start|} 
u:pool_pointer; {an index into |str_pool|} 

MODULE: 'Look for the word |hc[1...'
(*PASCAL module 930*)
h:=hc[1]; incr(hn); hc[hn]:=cur_lang; 
for j:=2 to hn do h:=(h+h+hc[j]) mod hyph_size; 
loop  begin 
INSERT: 'If the string |hyph_word[h]| is less than \(hc)|hc[1..hn]|,     |goto not_found|; but if the two strings are equal,     set |hyf| to the hyphen positions and |goto found|'
; 
  if h>0 then decr(h)else h:=hyph_size; 
  end; 
not_found: decr(hn) 

MODULE: 'If the string |hyph_word[h]| is less than \(hc)...'
(*PASCAL module 931*)
k:=hyph_word[h]; if k=0 then goto not_found; 
if length(k)<hn then goto not_found; 
if length(k)=hn then 
  begin j:=1; u:=str_start[k]; 
  repeat if so(str_pool[u])<hc[j] then goto not_found; 
  if so(str_pool[u])>hc[j] then goto done; 
  incr(j); incr(u); 
  until j>hn; 
  
INSERT: 'Insert hyphens as specified in |hyph_list[h]|'
; 
  decr(hn); goto found; 
  end; 
done: 

MODULE: 'Insert hyphens as specified...'
(*PASCAL module 932*)
s:=hyph_list[h]; 
while s<>null do 
  begin hyf[info(s)]:=1; s:=link(s); 
  end 

MODULE: 'Search |hyph_list| for pointers to |p|'
(*PASCAL module 933*)
for q:=0 to hyph_size do 
  begin if hyph_list[q]=p then 
    begin print_nl('HYPH('); print_int(q); print_char(')'); 
    end; 
  end 

MODULE: 'Enter as many...'
(*PASCAL module 935*)
n:=0; p:=null; 
loop  begin get_x_token; 
  reswitch: case cur_cmd of 
  letter,other_char,char_given:
INSERT: 'Append a new letter or hyphen'
; 
  char_num: begin scan_char_num; cur_chr:=cur_val; cur_cmd:=char_given; 
    goto reswitch; 
    end; 
  spacer,right_brace: begin if n>1 then 
INSERT: 'Enter a hyphenation exception'
; 
    if cur_cmd=right_brace then return; 
    n:=0; p:=null; 
    end; 
  othercases 
INSERT: 'Give improper \.{\\hyphenation} error'

  endcases; 
  end 

MODULE: 'Give improper \.{\\hyph...'
(*PASCAL module 936*)
begin print_err('Improper '); print_esc('hyphenation'); 
(*Improper \\hyphenation...*) 
  print(' will be flushed'); 
help2('Hyphenation exceptions must contain only letters')
 
  ('and hyphens. But continue; I''ll forgive and forget.'); 
error; 
end 

MODULE: 'Append a new letter or hyphen'
(*PASCAL module 937*)
if cur_chr='-' then 
INSERT: 'Append the value |n| to list |p|'

else  begin if lc_code(cur_chr)=0 then 
    begin print_err('Not a letter'); 
(*Not a letter*) 
    help2('Letters in \hyphenation words must have \lccode>0.')
 
      ('Proceed; I''ll ignore the character I just read.'); 
    error; 
    end 
  else if n<63 then 
    begin incr(n); hc[n]:=lc_code(cur_chr); 
    end; 
  end 

MODULE: 'Append the value |n| to list |p|'
(*PASCAL module 938*)
begin if n<63 then 
  begin q:=get_avail; link(q):=p; info(q):=n; p:=q; 
  end; 
end 

MODULE: 'Enter a hyphenation exception'
(*PASCAL module 939*)
begin incr(n); hc[n]:=cur_lang; str_room(n); h:=0; 
for j:=1 to n do 
  begin h:=(h+h+hc[j]) mod hyph_size; 
  append_char(hc[j]); 
  end; 
s:=make_string; 

INSERT: 'Insert the \(p)pair |(s,p)| into the exception table'
; 
end 

MODULE: 'Insert the \(p)pair |(s,p)|...'
(*PASCAL module 940*)
if hyph_count=hyph_size then overflow('exception dictionary',hyph_size); 
(*TeX capacity exceeded exception dictionary][\quad exception dictionary*) 
incr(hyph_count); 
while hyph_word[h]<>0 do 
  begin 
INSERT: 'If the string |hyph_word[h]| is less than \(or)or equal to   |s|, interchange |(hyph_word[h],hyph_list[h])| with |(s,p)|'
; 
  if h>0 then decr(h)else h:=hyph_size; 
  end; 
hyph_word[h]:=s; hyph_list[h]:=p 

MODULE: 'If the string |hyph_word[h]| is less than \(or)...'
(*PASCAL module 941*)
k:=hyph_word[h]; 
if length(k)<length(s) then goto found; 
if length(k)>length(s) then goto not_found; 
u:=str_start[k]; v:=str_start[s]; 
repeat if str_pool[u]<str_pool[v] then goto found; 
if str_pool[u]>str_pool[v] then goto not_found; 
incr(u); incr(v); 
until u=str_start[k+1]; 
found:q:=hyph_list[h]; hyph_list[h]:=p; p:=q;
 
t:=hyph_word[h]; hyph_word[h]:=s; s:=t; 
not_found: 

MODULE: 'Declare subprocedures for |line_break|'
(*PASCAL module 942*)
init 
INSERT: 'Declare procedures for preprocessing hyphenation patterns'
; 
tini 

MODULE: 'Glob... '
(*PASCAL module 943*)
init trie_op_hash:array[-trie_op_size..trie_op_size] of 0..trie_op_size; 
  {trie op codes for quadruples} 
trie_used:array[ASCII_code] of quarterword; 
  {largest opcode used so far for this language} 
trie_op_lang:array[1..trie_op_size] of ASCII_code; 
  {language part of a hashed quadruple} 
trie_op_val:array[1..trie_op_size] of quarterword; 
  {opcode corresponding to a hashed quadruple} 
trie_op_ptr:0..trie_op_size; {number of stored ops so far} 
tini 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 944*)
function new_trie_op(d,n:small_number;v:quarterword):quarterword; 
label exit; 
var h:-trie_op_size..trie_op_size; {trial hash location} 
u:quarterword; {trial op code} 
l:0..trie_op_size; {pointer to stored data} 
begin h:=abs(n+313*d+361*v+1009*cur_lang) mod (trie_op_size+trie_op_size) 
  - trie_op_size; 
loop  begin l:=trie_op_hash[h]; 
  if l=0 then {empty position found for a new op} 
    begin if trie_op_ptr=trie_op_size then 
      overflow('pattern memory ops',trie_op_size); 
    u:=trie_used[cur_lang]; 
    if u=max_quarterword then 
      overflow('pattern memory ops per language', 
        max_quarterword-min_quarterword); 
    incr(trie_op_ptr); incr(u); trie_used[cur_lang]:=u; 
    hyf_distance[trie_op_ptr]:=d; 
    hyf_num[trie_op_ptr]:=n; hyf_next[trie_op_ptr]:=v; 
    trie_op_lang[trie_op_ptr]:=cur_lang; trie_op_hash[h]:=trie_op_ptr; 
    trie_op_val[trie_op_ptr]:=u; new_trie_op:=u; return; 
    end; 
  if (hyf_distance[l]=d)and(hyf_num[l]=n)and(hyf_next[l]=v) 
   and(trie_op_lang[l]=cur_lang) then 
    begin new_trie_op:=trie_op_val[l]; return; 
    end; 
  if h>-trie_op_size then decr(h)else h:=trie_op_size; 
  end; 
exit:end; 

MODULE: 'Sort \(t)the hyphenation op tables into proper order'
(*PASCAL module 945*)
op_start[0]:=-min_quarterword; 
for j:=1 to 255 do op_start[j]:=op_start[j-1]+qo(trie_used[j-1]); 
for j:=1 to trie_op_ptr do 
  trie_op_hash[j]:=op_start[trie_op_lang[j]]+trie_op_val[j]; {destination} 
for j:=1 to trie_op_ptr do while trie_op_hash[j]>j do 
  begin k:=trie_op_hash[j];
 
  t:=hyf_distance[k]; hyf_distance[k]:=hyf_distance[j]; hyf_distance[j]:=t;
 
  t:=hyf_num[k]; hyf_num[k]:=hyf_num[j]; hyf_num[j]:=t;
 
  t:=hyf_next[k]; hyf_next[k]:=hyf_next[j]; hyf_next[j]:=t;
 
  trie_op_hash[j]:=trie_op_hash[k]; trie_op_hash[k]:=k; 
  end 

MODULE: 'Initialize table entries...'
(*PASCAL module 946*)
for k:=-trie_op_size to trie_op_size do trie_op_hash[k]:=0; 
for k:=0 to 255 do trie_used[k]:=min_quarterword; 
trie_op_ptr:=0; 

MODULE: 'Glob... '
(*PASCAL module 947*)
init trie_c:packed array[trie_pointer] of packed_ASCII_code; 
  {characters to match} 
(*\hskip10pt*)trie_o:packed array[trie_pointer] of quarterword; 
  {operations to perform} 
(*\hskip10pt*)trie_l:packed array[trie_pointer] of trie_pointer; 
  {left subtrie links} 
(*\hskip10pt*)trie_r:packed array[trie_pointer] of trie_pointer; 
  {right subtrie links} 
(*\hskip10pt*)trie_ptr:trie_pointer; {the number of nodes in the trie} 
(*\hskip10pt*)trie_hash:packed array[trie_pointer] of trie_pointer; 
  {used to identify equivalent subtries} 
tini 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 948*)
function trie_node(p:trie_pointer):trie_pointer; {converts 
  to a canonical form} 
label exit; 
var h:trie_pointer; {trial hash location} 
q:trie_pointer; {trial trie node} 
begin h:=abs(trie_c[p]+1009*trie_o[p]+ 
    2718*trie_l[p]+3142*trie_r[p]) mod trie_size; 
loop  begin q:=trie_hash[h]; 
  if q=0 then 
    begin trie_hash[h]:=p; trie_node:=p; return; 
    end; 
  if (trie_c[q]=trie_c[p])and(trie_o[q]=trie_o[p])and 
    (trie_l[q]=trie_l[p])and(trie_r[q]=trie_r[p]) then 
    begin trie_node:=q; return; 
    end; 
  if h>0 then decr(h)else h:=trie_size; 
  end; 
exit:end; 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 949*)
function compress_trie(p:trie_pointer):trie_pointer; 
begin if p=0 then compress_trie:=0 
else  begin trie_l[p]:=compress_trie(trie_l[p]); 
  trie_r[p]:=compress_trie(trie_r[p]); 
  compress_trie:=trie_node(p); 
  end; 
end; 

MODULE: 'Glob... '
(*PASCAL module 950*)
inittrie_taken:packed array[1..trie_size] of boolean; 
  {does a family start here?} 
(*\hskip10pt*)trie_min:array[ASCII_code] of trie_pointer; 
  {the first possible slot for each character} 
(*\hskip10pt*)trie_max:trie_pointer; {largest location used in |trie|} 
(*\hskip10pt*)trie_not_ready:boolean; {is the trie still in linked form?} 
tini 

MODULE: 'Initialize table entries...'
(*PASCAL module 951*)
trie_not_ready:=true; trie_root:=0; trie_c[0]:=si(0); trie_ptr:=0; 

MODULE: 'Get ready to compress the trie'
(*PASCAL module 952*)

INSERT: 'Sort \(t)the hyphenation...'
; 
for p:=0 to trie_size do trie_hash[p]:=0; 
trie_root:=compress_trie(trie_root); {identify equivalent subtries} 
for p:=0 to trie_ptr do trie_ref[p]:=0; 
for p:=0 to 255 do trie_min[p]:=p+1; 
trie_link(0):=1; trie_max:=0 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 953*)
procedure first_fit(p:trie_pointer); {packs a family into |trie|} 
label not_found,found; 
var h:trie_pointer; {candidate for |trie_ref[p]|} 
z:trie_pointer; {runs through holes} 
q:trie_pointer; {runs through the family starting at |p|} 
c:ASCII_code; {smallest character in the family} 
l,r:trie_pointer; {left and right neighbors} 
ll:1..256; {upper limit of |trie_min| updating} 
begin c:=so(trie_c[p]); 
z:=trie_min[c]; {get the first conceivably good hole} 
loop  begin h:=z-c;
 
  
INSERT: 'Ensure that |trie_max>=h+256|'
; 
  if trie_taken[h] then goto not_found; 
  
INSERT: 'If all characters of the family fit relative to |h|, then     |goto found|,\30\ otherwise |goto not_found|'
; 
  not_found: z:=trie_link(z); {move to the next hole} 
  end; 
found: 
INSERT: 'Pack the family into |trie| relative to |h|'
; 
end; 

MODULE: 'Ensure that |trie_max>=h+256|'
(*PASCAL module 954*)
if trie_max<h+256 then 
  begin if trie_size<=h+256 then overflow('pattern memory',trie_size); 
(*TeX capacity exceeded pattern memory][\quad pattern memory*) 
  repeat incr(trie_max); trie_taken[trie_max]:=false; 
  trie_link(trie_max):=trie_max+1; trie_back(trie_max):=trie_max-1; 
  until trie_max=h+256; 
  end 

MODULE: 'If all characters of the family fit relative to |h|...'
(*PASCAL module 955*)
q:=trie_r[p]; 
while q>0 do 
  begin if trie_link(h+so(trie_c[q]))=0 then goto not_found; 
  q:=trie_r[q]; 
  end; 
goto found 

MODULE: 'Pack the family into |trie| relative to |h|'
(*PASCAL module 956*)
trie_taken[h]:=true; trie_ref[p]:=h; q:=p; 
repeat z:=h+so(trie_c[q]); l:=trie_back(z); r:=trie_link(z); 
trie_back(r):=l; trie_link(l):=r; trie_link(z):=0; 
if l<256 then 
  begin if z<256 then ll:=z else ll:=256; 
  repeat trie_min[l]:=r; incr(l); 
  until l=ll; 
  end; 
q:=trie_r[q]; 
until q=0 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 957*)
procedure trie_pack(p:trie_pointer); {pack subtries of a family} 
var q:trie_pointer; {a local variable that need not be saved on recursive calls} 
begin repeat q:=trie_l[p]; 
if (q>0)and(trie_ref[q]=0) then 
  begin first_fit(q); trie_pack(q); 
  end; 
p:=trie_r[p]; 
until p=0; 
end; 

MODULE: 'Move the data into |trie|'
(*PASCAL module 958*)
h.rh:=0; h.b0:=min_quarterword; h.b1:=min_quarterword; {|trie_link:=0|, 
  |trie_op:=min_quarterword|, |trie_char:=qi(0)|} 
if trie_root=0 then {no patterns were given} 
  begin for r:=0 to 256 do trie[r]:=h; 
  trie_max:=256; 
  end 
else begin trie_fix(trie_root); {this fixes the non-holes in |trie|} 
  r:=0; {now we will zero out all the holes} 
  repeat s:=trie_link(r); trie[r]:=h; r:=s; 
  until r>trie_max; 
  end; 
trie_char(0):=qi('?'); {make |trie_char(c)<>c| for all |c|} 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 959*)
procedure trie_fix(p:trie_pointer); {moves |p| and its siblings into |trie|} 
var q:trie_pointer; {a local variable that need not be saved on recursive calls} 
c:ASCII_code; {another one that need not be saved} 
z:trie_pointer; {|trie| reference; this local variable must be saved} 
begin z:=trie_ref[p]; 
repeat q:=trie_l[p]; c:=so(trie_c[p]); 
trie_link(z+c):=trie_ref[q]; trie_char(z+c):=qi(c); trie_op(z+c):=trie_o[p]; 
if q>0 then trie_fix(q); 
p:=trie_r[p]; 
until p=0; 
end; 

MODULE: 'Declare procedures for preprocessing hyph...'
(*PASCAL module 960*)
procedure new_patterns; {initializes the hyphenation pattern data} 
label done, done1; 
var k,l:0..64; {indices into |hc| and |hyf|; 
                  not always in |small_number| range} 
digit_sensed:boolean; {should the next digit be treated as a letter?} 
v:quarterword; {trie op code} 
p,q:trie_pointer; {nodes of trie traversed during insertion} 
first_child:boolean; {is |p=trie_l[q]|?} 
c:ASCII_code; {character being inserted} 
begin if trie_not_ready then 
  begin set_cur_lang; scan_left_brace; {a left brace must follow \.[\\patterns]} 
  
INSERT: 'Enter all of the patterns into a linked trie, until coming to a right   brace'
; 
  end 
else begin print_err('Too late for '); print_esc('patterns'); 
  help1('All patterns must be given before typesetting begins.'); 
  error; link(garbage):=scan_toks(false,false); flush_list(def_ref); 
  end; 
end; 

MODULE: 'Enter all of the patterns into a linked trie...'
(*PASCAL module 961*)
k:=0; hyf[0]:=0; digit_sensed:=false; 
loop  begin get_x_token; 
  case cur_cmd of 
  letter,other_char:
INSERT: 'Append a new letter or a hyphen level'
; 
  spacer,right_brace: begin if k>0 then 
      
INSERT: 'Insert a new pattern into the linked trie'
; 
    if cur_cmd=right_brace then goto done; 
    k:=0; hyf[0]:=0; digit_sensed:=false; 
    end; 
  othercases begin print_err('Bad '); print_esc('patterns'); 
(*Bad \\patterns*) 
    help1('(See Appendix H.)'); error; 
    end 
  endcases; 
  end; 
done: 

MODULE: 'Append a new letter or a hyphen level'
(*PASCAL module 962*)
if digit_sensed or(cur_chr<'0')or(cur_chr>'9') then 
  begin if cur_chr='.' then cur_chr:=0 {edge-of-word delimiter} 
  else  begin cur_chr:=lc_code(cur_chr); 
    if cur_chr=0 then 
      begin print_err('Nonletter'); 
(*Nonletter*) 
      help1('(See Appendix H.)'); error; 
      end; 
    end; 
  if k<63 then 
    begin incr(k); hc[k]:=cur_chr; hyf[k]:=0; digit_sensed:=false; 
    end; 
  end 
else if k<63 then 
  begin hyf[k]:=cur_chr-'0'; digit_sensed:=true; 
  end 

MODULE: 'Insert a new pattern into the linked trie'
(*PASCAL module 963*)
begin 
INSERT: 'Compute the trie op code, |v|, and set |l:=0|'
; 
q:=0; hc[0]:=cur_lang; 
while l<=k do 
  begin c:=hc[l]; incr(l); p:=trie_l[q]; first_child:=true; 
  while (p>0)and(c>so(trie_c[p])) do 
    begin q:=p; p:=trie_r[q]; first_child:=false; 
    end; 
  if (p=0)or(c<so(trie_c[p])) then 
    
INSERT: 'Insert a new trie node between |q| and |p|, and       make |p| point to it'
; 
  q:=p; {now node |q| represents $p_1\ldots p_[l-1]$} 
  end; 
if trie_o[q]<>min_quarterword then 
  begin print_err('Duplicate pattern'); 
(*Duplicate pattern*) 
  help1('(See Appendix H.)'); error; 
  end; 
trie_o[q]:=v; 
end 

MODULE: 'Insert a new trie node between |q| and |p|...'
(*PASCAL module 964*)
begin if trie_ptr=trie_size then overflow('pattern memory',trie_size); 
(*TeX capacity exceeded pattern memory][\quad pattern memory*) 
incr(trie_ptr); trie_r[trie_ptr]:=p; p:=trie_ptr; trie_l[p]:=0; 
if first_child then trie_l[q]:=pelse trie_r[q]:=p; 
trie_c[p]:=si(c); trie_o[p]:=min_quarterword; 
end 

MODULE: 'Compute the trie op code, |v|...'
(*PASCAL module 965*)
if hc[1]=0 then hyf[0]:=0; 
if hc[k]=0 then hyf[k]:=0; 
l:=k; v:=min_quarterword; 
loop  begin if hyf[l]<>0 then v:=new_trie_op(k-l,hyf[l],v); 
  if l>0 then decr(l)else goto done1; 
  end; 
done1: 

MODULE: 'Declare procedures for preprocessing hyphenation patterns'
(*PASCAL module 966*)
procedure init_trie; 
var p:trie_pointer; {pointer for initialization} 
j,k,t:integer; {all-purpose registers for initialization} 
r,s:trie_pointer; {used to clean up the packed |trie|} 
h:two_halves; {template used to zero out |trie|'s holes} 
begin 
INSERT: 'Get ready to compress the trie'
; 
if trie_root<>0 then 
  begin first_fit(trie_root); trie_pack(trie_root); 
  end; 

INSERT: 'Move the data into |trie|'
; 
trie_not_ready:=false; 
end; 

MODULE: 'Insert glue for |split_top_skip|...'
(*PASCAL module 969*)
begin q:=new_skip_param(split_top_skip_code); link(prev_p):=q; link(q):=p; 
  {now |temp_ptr=glue_ptr(q)|} 
if width(temp_ptr)>height(p) then width(temp_ptr):=width(temp_ptr)-height(p) 
else width(temp_ptr):=0; 
p:=null; 
end 

MODULE: 'Glob... '
(*PASCAL module 971*)
best_height_plus_depth:scaled; {height of the best box, without stretching or 
  shrinking} 

MODULE: 'If node |p| is a legal breakpoint, check...'
(*PASCAL module 972*)
if p=null then pi:=eject_penalty 
else  
INSERT: 'Use node |p| to update the current height and depth measurements;     if this node is not a legal breakpoint, |goto not_found|     or |update_heights|,     otherwise set |pi| to the associated penalty at the break'
; 

INSERT: 'Check if node |p| is a new champion breakpoint; then \(go)|goto done|   if |p| is a forced break or if the page-so-far is already too full'
; 
if (type(p)<glue_node)or(type(p)>kern_node) then goto not_found; 
update_heights: 
INSERT: 'Update the current height and depth measurements with   respect to a glue or kern node~|p|'
; 
not_found: if prev_dp>d then 
    begin cur_height:=cur_height+prev_dp-d; 
    prev_dp:=d; 
    end; 

MODULE: 'Use node |p| to update the current height and depth measurements...'
(*PASCAL module 973*)
case type(p) of 
hlist_node,vlist_node,rule_node: begin(**);
 
  cur_height:=cur_height+prev_dp+height(p); prev_dp:=depth(p); 
  goto not_found; 
  end; 
whatsit_node:
INSERT: 'Process whatsit |p| in |vert_break| loop, |goto not_found|'
; 
glue_node: if precedes_break(prev_p) then pi:=0 
  else goto update_heights; 
kern_node: begin if link(p)=null then t:=penalty_node 
  else t:=type(link(p)); 
  if t=glue_node then pi:=0else goto update_heights; 
  end; 
penalty_node: pi:=penalty(p); 
mark_node,ins_node: goto not_found; 
othercases confusion('vertbreak') 
(*this can''t happen vertbreak][\quad vertbreak*) 
endcases 

MODULE: 'Check if node |p| is a new champion breakpoint; then \(go)...'
(*PASCAL module 974*)
if pi<inf_penalty then 
  begin 
INSERT: 'Compute the badness, |b|, using |awful_bad|     if the box is too full'
; 
  if b<awful_bad then 
    if pi<=eject_penalty then b:=pi 
    else if b<inf_bad then b:=b+pi 
      else b:=deplorable; 
  if b<=least_cost then 
    begin best_place:=p; least_cost:=b; 
    best_height_plus_depth:=cur_height+prev_dp; 
    end; 
  if (b=awful_bad)or(pi<=eject_penalty) then goto done; 
  end 

MODULE: 'Compute the badness, |b|, using |awful_bad| if the box is too full'
(*PASCAL module 975*)
if cur_height<h then 
  if (active_height[3]<>0) or (active_height[4]<>0) or 
    (active_height[5]<>0) then b:=0 
  else b:=badness(h-cur_height,active_height[2]) 
else if cur_height-h>active_height[6] then b:=awful_bad 
else b:=badness(cur_height-h,active_height[6]) 

MODULE: 'Update the current height and depth measurements with...'
(*PASCAL module 976*)
if type(p)=kern_node then q:=p 
else  begin q:=glue_ptr(p); 
  active_height[2+stretch_order(q)]:= 
    active_height[2+stretch_order(q)]+stretch(q);
 
  active_height[6]:=active_height[6]+shrink(q); 
  if (shrink_order(q)<>normal)and(shrink(q)<>0) then 
    begin(**);
 
    print_err('Infinite glue shrinkage found in box being split');
 
(*Infinite glue shrinkage...*) 
    help4('The box you are \vsplitting contains some infinitely')
 
      ('shrinkable glue, e.g., `\vss'' or `\vskip 0pt minus 1fil''.')
 
      ('Such glue doesn''t belong there; but you can safely proceed,')
 
      ('since the offensive shrinkability has been made finite.'); 
    error; r:=new_spec(q); shrink_order(r):=normal; delete_glue_ref(q); 
    glue_ptr(p):=r; q:=r; 
    end; 
  end; 
cur_height:=cur_height+prev_dp+width(q); prev_dp:=0 

MODULE: 'Dispense with trivial cases of void or bad boxes'
(*PASCAL module 978*)
if v=null then 
  begin vsplit:=null; return; 
  end; 
if type(v)<>vlist_node then 
  begin print_err(''); print_esc('vsplit'); print(' needs a '); 
  print_esc('vbox'); 
(*vsplit_][\.{\\vsplit needs a \\vbox}*) 
  help2('The box you are trying to split is an \hbox.')
 
  ('I can''t split such a box, so I''ll leave it alone.'); 
  error; vsplit:=null; return; 
  end 

MODULE: 'Look at all the marks...'
(*PASCAL module 979*)
p:=list_ptr(v); 
if p=q then list_ptr(v):=null 
else loopbegin if type(p)=mark_node then 
    if split_first_mark=null then 
      begin split_first_mark:=mark_ptr(p); 
      split_bot_mark:=split_first_mark; 
      token_ref_count(split_first_mark):= 
        token_ref_count(split_first_mark)+2; 
      end 
    else  begin delete_token_ref(split_bot_mark); 
      split_bot_mark:=mark_ptr(p); 
      add_token_ref(split_bot_mark); 
      end; 
  if link(p)=q then 
    begin link(p):=null; goto done; 
    end; 
  p:=link(p); 
  end; 
done: 

MODULE: 'Glob... '
(*PASCAL module 980*)
page_tail:pointer; {the final node on the current page} 
page_contents:empty..box_there; {what is on the current page so far?} 
page_max_depth:scaled; {maximum box depth on page being built} 
best_page_break:pointer; {break here to get the best page known so far} 
least_page_cost:integer; {the score for this currently best page} 
best_size:scaled; {its |page_goal|} 

MODULE: 'Initialize the special list heads...'
(*PASCAL module 981*)
subtype(page_ins_head):=qi(255); 
type(page_ins_head):=split_up; link(page_ins_head):=page_ins_head; 

MODULE: 'Glob... '
(*PASCAL module 982*)
page_so_far:array [0..7] of scaled; {height and glue of the current page} 
last_glue:pointer; {used to implement \.[\\lastskip]} 
last_penalty:integer; {used to implement \.[\\lastpenalty]} 
last_kern:scaled; {used to implement \.[\\lastkern]} 
insert_penalties:integer; {sum of the penalties for held-over insertions} 

MODULE: 'Put each...'
(*PASCAL module 983*)
primitive('pagegoal',set_page_dimen,0); 
(*page_goal_][\.{\\pagegoal} primitive*) 
primitive('pagetotal',set_page_dimen,1); 
(*page_total_][\.{\\pagetotal} primitive*) 
primitive('pagestretch',set_page_dimen,2); 
(*page_stretch_][\.{\\pagestretch} primitive*) 
primitive('pagefilstretch',set_page_dimen,3); 
(*page_fil_stretch_][\.{\\pagefilstretch} primitive*) 
primitive('pagefillstretch',set_page_dimen,4); 
(*page_fill_stretch_][\.{\\pagefillstretch} primitive*) 
primitive('pagefilllstretch',set_page_dimen,5); 
(*page_filll_stretch_][\.{\\pagefilllstretch} primitive*) 
primitive('pageshrink',set_page_dimen,6); 
(*page_shrink_][\.{\\pageshrink} primitive*) 
primitive('pagedepth',set_page_dimen,7); 
(*page_depth_][\.{\\pagedepth} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 984*)
set_page_dimen: case chr_code of 
0: print_esc('pagegoal'); 
1: print_esc('pagetotal'); 
2: print_esc('pagestretch'); 
3: print_esc('pagefilstretch'); 
4: print_esc('pagefillstretch'); 
5: print_esc('pagefilllstretch'); 
6: print_esc('pageshrink'); 
othercases print_esc('pagedepth') 
endcases; 

MODULE: 'Show the status of the current page'
(*PASCAL module 986*)
if page_head<>page_tail then 
  begin print_nl('### current page:'); 
  if output_active then print(' (held over for next output)'); 
(*held over for next output*) 
  show_box(link(page_head)); 
  if page_contents>empty then 
    begin print_nl('total height '); print_totals; 
(*total_height][\.{total height}*) 
    print_nl(' goal height '); print_scaled(page_goal); 
(*goal height*) 
    r:=link(page_ins_head); 
    while r<>page_ins_head do 
      begin print_ln; print_esc('insert'); t:=qo(subtype(r)); 
      print_int(t); print(' adds '); 
      if count(t)=1000 then t:=height(r) 
      else t:=x_over_n(height(r),1000)*count(t); 
      print_scaled(t); 
      if type(r)=split_up then 
        begin q:=page_head; t:=0; 
        repeat q:=link(q); 
        if (type(q)=ins_node)and(subtype(q)=subtype(r)) then incr(t); 
        until q=broken_ins(r); 
        print(', #'); print_int(t); print(' might split'); 
        end; 
      r:=link(r); 
      end; 
    end; 
  end 

MODULE: 'Initialize the special list...'
(*PASCAL module 988*)
type(page_head):=glue_node; subtype(page_head):=normal; 

MODULE: 'Glob... '
(*PASCAL module 989*)
output_active:boolean; {are we in the midst of an output routine?} 

MODULE: 'Set init...'
(*PASCAL module 990*)
output_active:=false; insert_penalties:=0; 

MODULE: 'Start a new current page'
(*PASCAL module 991*)
page_contents:=empty; page_tail:=page_head; link(page_head):=null;
 
last_glue:=max_halfword; last_penalty:=0; last_kern:=0; 
page_depth:=0; page_max_depth:=0 

MODULE: 'Make the contribution list empty...'
(*PASCAL module 995*)
if nest_ptr=0 then tail:=contrib_head {vertical mode} 
else contrib_tail:=contrib_head {other modes} 

MODULE: 'Update the values of |last_glue|...'
(*PASCAL module 996*)
if last_glue<>max_halfword then delete_glue_ref(last_glue); 
last_penalty:=0; last_kern:=0; 
if type(p)=glue_node then 
  begin last_glue:=glue_ptr(p); add_glue_ref(last_glue); 
  end 
else  begin last_glue:=max_halfword; 
  if type(p)=penalty_node then last_penalty:=penalty(p) 
  else if type(p)=kern_node then last_kern:=width(p); 
  end 

MODULE: 'Move node |p| to the current page; ...'
(*PASCAL module 997*)

INSERT: 'If the current page is empty and node |p| is to be deleted, |goto done1|;   otherwise use node |p| to update the state of the current page;   if this node is an insertion, |goto contribute|; otherwise if this node   is not a legal breakpoint, |goto contribute| or |update_heights|;   otherwise set |pi| to the penalty associated with this breakpoint'
; 

INSERT: 'Check if node |p| is a new champion breakpoint; then \(if)if it is time for   a page break, prepare for output, and either fire up the user''s   output routine and |return| or ship out the page and |goto done|'
; 
if (type(p)<glue_node)or(type(p)>kern_node) then goto contribute; 
update_heights:
INSERT: 'Update the current page measurements with respect to the   glue or kern specified by node~|p|'
; 
contribute: 
INSERT: 'Make sure that |page_max_depth| is not exceeded'
; 

INSERT: 'Link node |p| into the current page and |goto done|'
; 
done1:
INSERT: 'Recycle node |p|'
; 
done: 

MODULE: 'Link node |p| into the current page and |goto done|'
(*PASCAL module 998*)
link(page_tail):=p; page_tail:=p; 
link(contrib_head):=link(p); link(p):=null; goto done 

MODULE: 'Recycle node |p|'
(*PASCAL module 999*)
link(contrib_head):=link(p); link(p):=null; flush_node_list(p) 

MODULE: 'If the current page is empty...'
(*PASCAL module 1000*)
case type(p) of 
hlist_node,vlist_node,rule_node: if page_contents<box_there then 
    
INSERT: 'Initialize the current page, insert the \.{\\topskip} glue       ahead of |p|, and |goto continue|'

  else 
INSERT: 'Prepare to move a box or rule node to the current page,     then |goto contribute|'
; 
whatsit_node: 
INSERT: 'Prepare to move whatsit |p| to the current page,   then |goto contribute|'
; 
glue_node: if page_contents<box_there then goto done1 
  else if precedes_break(page_tail) then pi:=0 
  else goto update_heights; 
kern_node: if page_contents<box_there then goto done1 
  else if link(p)=null then return 
  else if type(link(p))=glue_node then pi:=0 
  else goto update_heights; 
penalty_node: if page_contents<box_there then goto done1else pi:=penalty(p); 
mark_node: goto contribute; 
ins_node: 
INSERT: 'Append an insertion to the current page and |goto contribute|'
; 
othercases confusion('page') 
(*this can''t happen page][\quad page*) 
endcases 

MODULE: 'Initialize the current page, insert the \.{\\topskip} glue...'
(*PASCAL module 1001*)
begin if page_contents=empty then freeze_page_specs(box_there) 
else page_contents:=box_there; 
q:=new_skip_param(top_skip_code); {now |temp_ptr=glue_ptr(q)|} 
if width(temp_ptr)>height(p) then width(temp_ptr):=width(temp_ptr)-height(p) 
else width(temp_ptr):=0; 
link(q):=p; link(contrib_head):=q; goto continue; 
end 

MODULE: 'Prepare to move a box or rule node to the current page...'
(*PASCAL module 1002*)
begin page_total:=page_total+page_depth+height(p); 
page_depth:=depth(p); 
goto contribute; 
end 

MODULE: 'Make sure that |page_max_depth| is not exceeded'
(*PASCAL module 1003*)
if page_depth>page_max_depth then 
  begin page_total:= 
    page_total+page_depth-page_max_depth;
 
  page_depth:=page_max_depth; 
  end; 

MODULE: 'Update the current page measurements with respect to the glue...'
(*PASCAL module 1004*)
if type(p)=kern_node then q:=p 
else begin q:=glue_ptr(p); 
  page_so_far[2+stretch_order(q)]:= 
    page_so_far[2+stretch_order(q)]+stretch(q);
 
  page_shrink:=page_shrink+shrink(q); 
  if (shrink_order(q)<>normal)and(shrink(q)<>0) then 
    begin(**);
 
    print_err('Infinite glue shrinkage found on current page');
 
(*Infinite glue shrinkage...*) 
    help4('The page about to be output contains some infinitely')
 
      ('shrinkable glue, e.g., `\vss'' or `\vskip 0pt minus 1fil''.')
 
      ('Such glue doesn''t belong there; but you can safely proceed,')
 
      ('since the offensive shrinkability has been made finite.'); 
    error; 
    r:=new_spec(q); shrink_order(r):=normal; delete_glue_ref(q); 
    glue_ptr(p):=r; q:=r; 
    end; 
  end; 
page_total:=page_total+page_depth+width(q); page_depth:=0 

MODULE: 'Check if node |p| is a new champion breakpoint; then \(if)...'
(*PASCAL module 1005*)
if pi<inf_penalty then 
  begin 
INSERT: 'Compute the badness, |b|, of the current page,     using |awful_bad| if the box is too full'
; 
  if b<awful_bad then 
    if pi<=eject_penalty then c:=pi 
    else  if b<inf_bad then c:=b+pi+insert_penalties 
      else c:=deplorable 
  else c:=b; 
  if insert_penalties>=10000 then c:=awful_bad; 
  stat if tracing_pages>0 then 
INSERT: 'Display the page break cost'
;tats;
 
  if c<=least_page_cost then 
    begin best_page_break:=p; best_size:=page_goal; 
    least_page_cost:=c; 
    r:=link(page_ins_head); 
    while r<>page_ins_head do 
      begin best_ins_ptr(r):=last_ins_ptr(r); 
      r:=link(r); 
      end; 
    end; 
  if (c=awful_bad)or(pi<=eject_penalty) then 
    begin fire_up(p); {output the current page at the best place} 
    if output_active then return; {user's output routine will act} 
    goto done; {the page has been shipped out by default output routine} 
    end; 
  end 

MODULE: 'Display the page break cost'
(*PASCAL module 1006*)
begin begin_diagnostic; print_nl('%'); 
print(' t='); print_totals;
 
print(' g='); print_scaled(page_goal);
 
print(' b='); 
if b=awful_bad then print_char('*')else print_int(b); 
(**\relax*) 
print(' p='); print_int(pi); 
print(' c='); 
if c=awful_bad then print_char('*')else print_int(c); 
if c<=least_page_cost then print_char('#'); 
end_diagnostic(false); 
end 

MODULE: 'Compute the badness, |b|, of the current page...'
(*PASCAL module 1007*)
if page_total<page_goal then 
  if (page_so_far[3]<>0) or (page_so_far[4]<>0) or 
    (page_so_far[5]<>0) then b:=0 
  else b:=badness(page_goal-page_total,page_so_far[2]) 
else if page_total-page_goal>page_shrink then b:=awful_bad 
else b:=badness(page_total-page_goal,page_shrink) 

MODULE: 'Append an insertion to the current page and |goto contribute|'
(*PASCAL module 1008*)
begin if page_contents=empty then freeze_page_specs(inserts_only); 
n:=subtype(p); r:=page_ins_head; 
while n>=subtype(link(r)) do r:=link(r); 
n:=qo(n); 
if subtype(r)<>qi(n) then 
  
INSERT: 'Create a page insertion node with |subtype(r)=qi(n)|, and     include the glue correction for box |n| in the     current page state'
; 
if type(r)=split_up then insert_penalties:=insert_penalties+float_cost(p) 
else  begin last_ins_ptr(r):=p; 
  delta:=page_goal-page_total-page_depth+page_shrink; 
    {this much room is left if we shrink the maximum} 
  if count(n)=1000 then h:=height(p) 
  else h:=x_over_n(height(p),1000)*count(n); {this much room is needed} 
  if ((h<=0)or(h<=delta))and(height(p)+height(r)<=dimen(n)) then 
    begin page_goal:=page_goal-h; height(r):=height(r)+height(p); 
    end 
  else 
INSERT: 'Find the best way to split the insertion, and change     |type(r)| to |split_up|'
; 
  end; 
goto contribute; 
end 

MODULE: 'Create a page insertion node...'
(*PASCAL module 1009*)
begin q:=get_node(page_ins_node_size); link(q):=link(r); link(r):=q; r:=q; 
subtype(r):=qi(n); type(r):=inserting; ensure_vbox(n); 
if box(n)=null then height(r):=0 
else height(r):=height(box(n))+depth(box(n)); 
best_ins_ptr(r):=null;
 
q:=skip(n); 
if count(n)=1000 then h:=height(r) 
else h:=x_over_n(height(r),1000)*count(n); 
page_goal:=page_goal-h-width(q);
 
page_so_far[2+stretch_order(q)]:=page_so_far[2+stretch_order(q)]+stretch(q);
 
page_shrink:=page_shrink+shrink(q); 
if (shrink_order(q)<>normal)and(shrink(q)<>0) then 
  begin print_err('Infinite glue shrinkage inserted from '); print_esc('skip'); 
(*Infinite glue shrinkage...*) 
  print_int(n); 
  help3('The correction glue for page breaking with insertions')
 
    ('must have finite shrinkability. But you may proceed,')
 
    ('since the offensive shrinkability has been made finite.'); 
  error; 
  end; 
end 

MODULE: 'Find the best way to split the insertion...'
(*PASCAL module 1010*)
begin if count(n)<=0 then w:=max_dimen 
else  begin w:=page_goal-page_total-page_depth; 
  if count(n)<>1000 then w:=x_over_n(w,count(n))*1000; 
  end; 
if w>dimen(n)-height(r) then w:=dimen(n)-height(r); 
q:=vert_break(ins_ptr(p),w,depth(p)); 
height(r):=height(r)+best_height_plus_depth; 
stat if tracing_pages>0 then 
INSERT: 'Display the insertion split cost'
;tats;
 
if count(n)<>1000 then 
  best_height_plus_depth:=x_over_n(best_height_plus_depth,1000)*count(n); 
page_goal:=page_goal-best_height_plus_depth; 
type(r):=split_up; broken_ptr(r):=q; broken_ins(r):=p; 
if q=null then insert_penalties:=insert_penalties+eject_penalty 
else if type(q)=penalty_node then insert_penalties:=insert_penalties+penalty(q); 
end 

MODULE: 'Display the insertion split cost'
(*PASCAL module 1011*)
begin begin_diagnostic; print_nl('% split'); print_int(n); 
(*split*) 
print(' to '); print_scaled(w); 
print_char(','); print_scaled(best_height_plus_depth);
 
print(' p='); 
if q=null then print_int(eject_penalty) 
else if type(q)=penalty_node then print_int(penalty(q)) 
else print_char('0'); 
end_diagnostic(false); 
end 

MODULE: 'Declare the procedure called |fire_up|'
(*PASCAL module 1012*)
procedure fire_up(c:pointer); 
label exit; 
var p,q,r,s:pointer; {nodes being examined and/or changed} 
prev_p:pointer; {predecessor of |p|} 
n:min_quarterword..255; {insertion box number} 
wait:boolean; {should the present insertion be held over?} 
save_vbadness:integer; {saved value of |vbadness|} 
save_vfuzz: scaled; {saved value of |vfuzz|} 
save_split_top_skip: pointer; {saved value of |split_top_skip|} 
begin 
INSERT: 'Set the value of |output_penalty|'
; 
if bot_mark<>null then 
  begin if top_mark<>null then delete_token_ref(top_mark); 
  top_mark:=bot_mark; add_token_ref(top_mark); 
  delete_token_ref(first_mark); first_mark:=null; 
  end; 

INSERT: 'Put the \(o)optimal current page into box 255, update |first_mark| and   |bot_mark|, append insertions to their boxes, and put the   remaining nodes back on the contribution list'
; 
if (top_mark<>null)and(first_mark=null) then 
  begin first_mark:=top_mark; add_token_ref(top_mark); 
  end; 
if output_routine<>null then 
  if dead_cycles>=max_dead_cycles then 
    
INSERT: 'Explain that too many dead cycles have occurred in a row'

  else 
INSERT: 'Fire up the user''s output routine and |return|'
; 

INSERT: 'Perform the default output routine'
; 
exit:end; 

MODULE: 'Set the value of |output_penalty|'
(*PASCAL module 1013*)
if type(best_page_break)=penalty_node then 
  begin geq_word_define(int_base+output_penalty_code,penalty(best_page_break)); 
  penalty(best_page_break):=inf_penalty; 
  end 
else geq_word_define(int_base+output_penalty_code,inf_penalty) 

MODULE: 'Put the \(o)optimal current page into box 255...'
(*PASCAL module 1014*)
if c=best_page_break then best_page_break:=null; {|c| not yet linked in} 

INSERT: 'Ensure that box 255 is empty before output'
; 
insert_penalties:=0; {this will count the number of insertions held over} 
save_split_top_skip:=split_top_skip; 
if holding_inserts<=0 then 
  
INSERT: 'Prepare all the boxes involved in insertions to act as queues'
; 
q:=hold_head; link(q):=null; prev_p:=page_head; p:=link(prev_p); 
while p<>best_page_break do 
  begin if type(p)=ins_node then 
    begin if holding_inserts<=0 then 
       
INSERT: 'Either insert the material specified by node |p| into the          appropriate box, or hold it for the next page;          also delete node |p| from the current page'
; 
    end 
  else if type(p)=mark_node then 
INSERT: 'Update the values of     |first_mark| and |bot_mark|'
; 
  prev_p:=p; p:=link(prev_p); 
  end; 
split_top_skip:=save_split_top_skip; 

INSERT: 'Break the current page at node |p|, put it in box~255,   and put the remaining nodes on the contribution list'
; 

INSERT: 'Delete \(t)the page-insertion nodes'


MODULE: 'Ensure that box 255 is empty before output'
(*PASCAL module 1015*)
if box(255)<>null then 
  begin print_err(''); print_esc('box'); print('255 is not void'); 
(*box255][\.{\\box255 is not void}*) 
  help2('You shouldn''t use \box255 except in \output routines.')
 
    ('Proceed, and I''ll discard its present contents.'); 
  box_error(255); 
  end 

MODULE: 'Update the values of |first_mark| and |bot_mark|'
(*PASCAL module 1016*)
begin if first_mark=null then 
  begin first_mark:=mark_ptr(p); 
  add_token_ref(first_mark); 
  end; 
if bot_mark<>null then delete_token_ref(bot_mark); 
bot_mark:=mark_ptr(p); add_token_ref(bot_mark); 
end 

MODULE: 'Break the current page at node |p|, put it...'
(*PASCAL module 1017*)
if p<>null then 
  begin if link(contrib_head)=null then 
    if nest_ptr=0 then tail:=page_tail 
    else contrib_tail:=page_tail; 
  link(page_tail):=link(contrib_head); 
  link(contrib_head):=p; 
  link(prev_p):=null; 
  end; 
save_vbadness:=vbadness; vbadness:=inf_bad; 
save_vfuzz:=vfuzz; vfuzz:=max_dimen; {inhibit error messages} 
box(255):=vpackage(link(page_head),best_size,exactly,page_max_depth); 
vbadness:=save_vbadness; vfuzz:=save_vfuzz; 
if last_glue<>max_halfword then delete_glue_ref(last_glue); 

INSERT: 'Start a new current page'
; {this sets |last_glue:=max_halfword|} 
if q<>hold_head then 
  begin link(page_head):=link(hold_head); page_tail:=q; 
  end 

MODULE: 'Prepare all the boxes involved in insertions to act as queues'
(*PASCAL module 1018*)
begin r:=link(page_ins_head); 
while r<>page_ins_head do 
  begin if best_ins_ptr(r)<>null then 
    begin n:=qo(subtype(r)); ensure_vbox(n); 
    if box(n)=null then box(n):=new_null_box; 
    p:=box(n)+list_offset; 
    while link(p)<>null do p:=link(p); 
    last_ins_ptr(r):=p; 
    end; 
  r:=link(r); 
  end; 
end 

MODULE: 'Delete \(t)the page-insertion nodes'
(*PASCAL module 1019*)
r:=link(page_ins_head); 
while r<>page_ins_head do 
  begin q:=link(r); free_node(r,page_ins_node_size); r:=q; 
  end; 
link(page_ins_head):=page_ins_head 

MODULE: 'Either insert the material specified by node |p| into...'
(*PASCAL module 1020*)
begin r:=link(page_ins_head); 
while subtype(r)<>subtype(p) do r:=link(r); 
if best_ins_ptr(r)=null then wait:=true 
else  begin wait:=false; s:=last_ins_ptr(r); link(s):=ins_ptr(p); 
  if best_ins_ptr(r)=p then 
    
INSERT: 'Wrap up the box specified by node |r|, splitting node |p| if     called for; set |wait:=true| if node |p| holds a remainder after     splitting'

  else  begin while link(s)<>null do s:=link(s); 
    last_ins_ptr(r):=s; 
    end; 
  end; 

INSERT: 'Either append the insertion node |p| after node |q|, and remove it   from the current page, or delete |node(p)|'
; 
end 

MODULE: 'Wrap up the box specified by node |r|, splitting node |p| if...'
(*PASCAL module 1021*)
begin if type(r)=split_up then 
  if (broken_ins(r)=p)and(broken_ptr(r)<>null) then 
    begin while link(s)<>broken_ptr(r) do s:=link(s); 
    link(s):=null; 
    split_top_skip:=split_top_ptr(p); 
    ins_ptr(p):=prune_page_top(broken_ptr(r)); 
    if ins_ptr(p)<>null then 
      begin temp_ptr:=vpack(ins_ptr(p),natural); 
      height(p):=height(temp_ptr)+depth(temp_ptr); 
      free_node(temp_ptr,box_node_size); wait:=true; 
      end; 
    end; 
best_ins_ptr(r):=null; 
n:=qo(subtype(r)); 
temp_ptr:=list_ptr(box(n)); 
free_node(box(n),box_node_size); 
box(n):=vpack(temp_ptr,natural); 
end 

MODULE: 'Either append the insertion node |p|...'
(*PASCAL module 1022*)
link(prev_p):=link(p); link(p):=null; 
if wait then 
  begin link(q):=p; q:=p; incr(insert_penalties); 
  end 
else  begin delete_glue_ref(split_top_ptr(p)); 
  free_node(p,ins_node_size); 
  end; 
p:=prev_p 

MODULE: 'Perform the default output routine'
(*PASCAL module 1023*)
begin if link(page_head)<>null then 
  begin if link(contrib_head)=null then 
    if nest_ptr=0 then tail:=page_tailelse contrib_tail:=page_tail 
  else link(page_tail):=link(contrib_head); 
  link(contrib_head):=link(page_head); 
  link(page_head):=null; page_tail:=page_head; 
  end; 
ship_out(box(255)); box(255):=null; 
end 

MODULE: 'Explain that too many dead cycles have occurred in a row'
(*PASCAL module 1024*)
begin print_err('Output loop---'); print_int(dead_cycles); 
(*Output loop...*) 
print(' consecutive dead cycles'); 
help3('I''ve concluded that your \output is awry; it never does a')
 
('\shipout, so I''m shipping \box255 out myself. Next time')
 
('increase \maxdeadcycles if you want me to be more patient!'); error; 
end 

MODULE: 'Fire up the user''s output routine and |return|'
(*PASCAL module 1025*)
begin output_active:=true; 
incr(dead_cycles); 
push_nest; mode:=-vmode; prev_depth:=ignore_depth; mode_line:=-line; 
begin_token_list(output_routine,output_text); 
new_save_level(output_group); normal_paragraph; 
scan_left_brace; 
return; 
end 

MODULE: 'Resume the page builder after an output routine has come to an end'
(*PASCAL module 1026*)
begin if (loc<>null) or 
 ((token_type<>output_text)and(token_type<>backed_up)) then 
  
INSERT: 'Recover from an unbalanced output routine'
; 
end_token_list; {conserve stack space in case more outputs are triggered} 
end_graf; unsave; output_active:=false; insert_penalties:=0;
 

INSERT: 'Ensure that box 255 is empty after output'
; 
if tail<>head then {current list goes after heldover insertions} 
  begin link(page_tail):=link(head); 
  page_tail:=tail; 
  end; 
if link(page_head)<>null then {and both go before heldover contributions} 
  begin if link(contrib_head)=null then contrib_tail:=page_tail; 
  link(page_tail):=link(contrib_head); 
  link(contrib_head):=link(page_head); 
  link(page_head):=null; page_tail:=page_head; 
  end; 
pop_nest; build_page; 
end 

MODULE: 'Recover from an unbalanced output routine'
(*PASCAL module 1027*)
begin print_err('Unbalanced output routine'); 
(*Unbalanced output routine*) 
help2('Your sneaky output routine has problematic {''s and/or }''s.')
 
('I can''t handle that very well; good luck.'); error; 
repeat get_token; 
until loc=null; 
end {loops forever if reading from a file, since |null=min_halfword<=0|} 

MODULE: 'Ensure that box 255 is empty after output'
(*PASCAL module 1028*)
if box(255)<>null then 
  begin print_err('Output routine didn''t use all of '); 
  print_esc('box'); print_int(255); 
(*Output routine didn''t use...*) 
  help3('Your \output commands should empty \box255,')
 
    ('e.g., by saying `\shipout\box255''.')
 
    ('Proceed; I''ll discard its present contents.'); 
  box_error(255); 
  end 

MODULE: 'Give diagnostic information, if requested'
(*PASCAL module 1031*)
if interrupt<>0 then if OK_to_interrupt then 
  begin back_input; check_interrupt; goto big_switch; 
  end; 
debug if panicking then check_mem(false);;gubed 
if tracing_commands>0 then show_cur_cmd_chr 

MODULE: 'Glob... '
(*PASCAL module 1032*)
main_f:internal_font_number; {the current font} 
main_i:four_quarters; {character information bytes for |cur_l|} 
main_j:four_quarters; {ligature/kern command} 
main_k:font_index; {index into |font_info|} 
main_p:pointer; {temporary register for list manipulation} 
main_s:integer; {space factor value} 
bchar:halfword; {right boundary character of current font, or |non_char|} 
false_bchar:halfword; {nonexistent character matching |bchar|, or |non_char|} 
cancel_boundary:boolean; {should the left boundary be ignored?} 
ins_disc:boolean; {should we insert a discretionary node?} 

MODULE: 'Set init...'
(*PASCAL module 1033*)
ligature_present:=false; cancel_boundary:=false; lft_hit:=false; rt_hit:=false; 
ins_disc:=false; 

MODULE: 'Append character |cur_chr|...'
(*PASCAL module 1034*)
adjust_space_factor;
 
main_f:=cur_font; 
bchar:=font_bchar[main_f]; false_bchar:=font_false_bchar[main_f]; 
if mode>0 then if language<>clang then fix_language; 
fast_get_avail(lig_stack); font(lig_stack):=main_f; cur_l:=qi(cur_chr); 
character(lig_stack):=cur_l;
 
cur_q:=tail; 
if cancel_boundary then 
  begin cancel_boundary:=false; main_k:=non_address; 
  end 
else main_k:=bchar_label[main_f]; 
if main_k=non_address then goto main_loop_move+2; {no left boundary processing} 
cur_r:=cur_l; cur_l:=non_char; 
goto main_lig_loop+1; {begin with cursor after left boundary} 


 
main_loop_wrapup:
INSERT: 'Make a ligature node, if |ligature_present|;   insert a null discretionary, if appropriate'
; 
main_loop_move:
INSERT: 'If the cursor is immediately followed by the right boundary,   |goto reswitch|; if it''s followed by an invalid character, |goto big_switch|;   otherwise move the cursor one step to the right and |goto main_lig_loop|'
; 
main_loop_lookahead:
INSERT: 'Look ahead for another character, or leave |lig_stack|   empty if there''s none there'
; 
main_lig_loop:
INSERT: 'If there''s a ligature/kern command relevant to |cur_l| and   |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup|'
; 
main_loop_move_lig:
INSERT: 'Move the cursor past a pseudo-ligature, then   |goto main_loop_lookahead| or |main_lig_loop|'


MODULE: 'Make a ligature node, if |ligature_present|;...'
(*PASCAL module 1035*)
wrapup(rt_hit) 

MODULE: 'If the cursor is immediately followed by the right boundary...'
(*PASCAL module 1036*)
(*inner loop*) 
if lig_stack=null then goto reswitch; 
cur_q:=tail; cur_l:=character(lig_stack); 
main_loop_move+1:if not is_char_node(lig_stack) then goto main_loop_move_lig; 
main_loop_move+2:if(cur_chr<font_bc[main_f])or(cur_chr>font_ec[main_f]) then 
  begin char_warning(main_f,cur_chr); free_avail(lig_stack); goto big_switch; 
  end; 
main_i:=char_info(main_f)(cur_l); 
if not char_exists(main_i) then 
  begin char_warning(main_f,cur_chr); free_avail(lig_stack); goto big_switch; 
  end; 
link(tail):=lig_stack; tail:=lig_stack {|main_loop_lookahead| is next} 

MODULE: 'Move the cursor past a pseudo-ligature...'
(*PASCAL module 1037*)
main_p:=lig_ptr(lig_stack); 
if main_p>null then tail_append(main_p); {append a single character} 
temp_ptr:=lig_stack; lig_stack:=link(temp_ptr); 
free_node(temp_ptr,small_node_size); 
main_i:=char_info(main_f)(cur_l); ligature_present:=true; 
if lig_stack=null then 
  if main_p>null then goto main_loop_lookahead 
  else cur_r:=bchar 
else cur_r:=character(lig_stack); 
goto main_lig_loop 

MODULE: 'Look ahead for another character...'
(*PASCAL module 1038*)
get_next; {set only |cur_cmd| and |cur_chr|, for speed} 
if cur_cmd=letter then goto main_loop_lookahead+1; 
if cur_cmd=other_char then goto main_loop_lookahead+1; 
if cur_cmd=char_given then goto main_loop_lookahead+1; 
x_token; {now expand and set |cur_cmd|, |cur_chr|, |cur_tok|} 
if cur_cmd=letter then goto main_loop_lookahead+1; 
if cur_cmd=other_char then goto main_loop_lookahead+1; 
if cur_cmd=char_given then goto main_loop_lookahead+1; 
if cur_cmd=char_num then 
  begin scan_char_num; cur_chr:=cur_val; goto main_loop_lookahead+1; 
  end; 
if cur_cmd=no_boundary then bchar:=non_char; 
cur_r:=bchar; lig_stack:=null; goto main_lig_loop; 
main_loop_lookahead+1: adjust_space_factor; 
fast_get_avail(lig_stack); font(lig_stack):=main_f; 
cur_r:=qi(cur_chr); character(lig_stack):=cur_r; 
if cur_r=false_bchar then cur_r:=non_char {this prevents spurious ligatures} 

MODULE: 'If there''s a ligature/kern command...'
(*PASCAL module 1039*)
if char_tag(main_i)<>lig_tag then goto main_loop_wrapup; 
if cur_r=non_char then goto main_loop_wrapup; 
main_k:=lig_kern_start(main_f)(main_i); main_j:=font_info[main_k].qqqq; 
if skip_byte(main_j)<=stop_flag then goto main_lig_loop+2; 
main_k:=lig_kern_restart(main_f)(main_j); 
main_lig_loop+1:main_j:=font_info[main_k].qqqq; 
main_lig_loop+2:if next_char(main_j)=cur_r then 
 if skip_byte(main_j)<=stop_flag then 
  
INSERT: 'Do ligature or kern command, returning to |main_lig_loop|   or |main_loop_wrapup| or |main_loop_move|'
; 
if skip_byte(main_j)=qi(0) then incr(main_k) 
else begin if skip_byte(main_j)>=stop_flag then goto main_loop_wrapup; 
  main_k:=main_k+qo(skip_byte(main_j))+1; 
  end; 
goto main_lig_loop+1 

MODULE: 'Do ligature or kern command...'
(*PASCAL module 1040*)
begin if op_byte(main_j)>=kern_flag then 
  begin wrapup(rt_hit); 
  tail_append(new_kern(char_kern(main_f)(main_j))); goto main_loop_move; 
  end; 
if cur_l=non_char then lft_hit:=true 
else if lig_stack=null then rt_hit:=true; 
check_interrupt; {allow a way out in case there's an infinite ligature loop} 
case op_byte(main_j) of 
qi(1),qi(5):begin cur_l:=rem_byte(main_j); {\.[=:\?], \.[=:\?>]} 
  main_i:=char_info(main_f)(cur_l); ligature_present:=true; 
  end; 
qi(2),qi(6):begin cur_r:=rem_byte(main_j); {\.[\?=:], \.[\?=:>]} 
  if lig_stack=null then {right boundary character is being consumed} 
    begin lig_stack:=new_lig_item(cur_r); bchar:=non_char; 
    end 
  else if is_char_node(lig_stack) then {|link(lig_stack)=null|} 
    begin main_p:=lig_stack; lig_stack:=new_lig_item(cur_r); 
    lig_ptr(lig_stack):=main_p; 
    end 
  else character(lig_stack):=cur_r; 
  end; 
qi(3):begin cur_r:=rem_byte(main_j); {\.[\?=:\?]} 
  main_p:=lig_stack; lig_stack:=new_lig_item(cur_r); 
  link(lig_stack):=main_p; 
  end; 
qi(7),qi(11):begin wrapup(false); {\.[\?=:\?>], \.[\?=:\?>>]} 
  cur_q:=tail; cur_l:=rem_byte(main_j); 
  main_i:=char_info(main_f)(cur_l); ligature_present:=true; 
  end; 
othercases begin cur_l:=rem_byte(main_j); ligature_present:=true; {\.[=:]} 
  if lig_stack=null then goto main_loop_wrapup 
  else goto main_loop_move+1; 
  end 
endcases; 
if op_byte(main_j)>qi(4) then 
  if op_byte(main_j)<>qi(7) then goto main_loop_wrapup; 
if cur_l<non_char then goto main_lig_loop; 
main_k:=bchar_label[main_f]; goto main_lig_loop+1; 
end 

MODULE: 'Append a normal inter-word space...'
(*PASCAL module 1041*)
if space_skip=zero_glue then 
  begin 
INSERT: 'Find the glue specification, |main_p|, for     text spaces in the current font'
; 
  temp_ptr:=new_glue(main_p); 
  end 
else temp_ptr:=new_param_glue(space_skip_code); 
link(tail):=temp_ptr; tail:=temp_ptr; 
goto big_switch 

MODULE: 'Find the glue specification...'
(*PASCAL module 1042*)
begin main_p:=font_glue[cur_font]; 
if main_p=null then 
  begin main_p:=new_spec(zero_glue); main_k:=param_base[cur_font]+space_code; 
  width(main_p):=font_info[main_k].sc; {that's |space(cur_font)|} 
  stretch(main_p):=font_info[main_k+1].sc; {and |space_stretch(cur_font)|} 
  shrink(main_p):=font_info[main_k+2].sc; {and |space_shrink(cur_font)|} 
  font_glue[cur_font]:=main_p; 
  end; 
end 

MODULE: 'Declare act...'
(*PASCAL module 1043*)
procedure app_space; {handle spaces when |space_factor<>1000|} 
varq:pointer; {glue node} 
begin if (space_factor>=2000)and(xspace_skip<>zero_glue) then 
  q:=new_param_glue(xspace_skip_code) 
else  begin if space_skip<>zero_glue then main_p:=space_skip 
  else 
INSERT: 'Find the glue specification...'
; 
  main_p:=new_spec(main_p); 
  
INSERT: 'Modify the glue specification in |main_p| according to the space factor'
; 
  q:=new_glue(main_p); glue_ref_count(main_p):=null; 
  end; 
link(tail):=q; tail:=q; 
end; 

MODULE: 'Modify the glue specification in |main_p| according to the space factor'
(*PASCAL module 1044*)
if space_factor>=2000 then width(main_p):=width(main_p)+extra_space(cur_font); 
stretch(main_p):=xn_over_d(stretch(main_p),space_factor,1000); 
shrink(main_p):=xn_over_d(shrink(main_p),1000,space_factor) 

MODULE: 'Cases of |main_control| that are not part of the inner loop'
(*PASCAL module 1045*)
any_mode(relax),vmode+spacer,mmode+spacer,mmode+no_boundary:do_nothing; 
any_mode(ignore_spaces): begin 
INSERT: 'Get the next non-blank non-call...'
; 
  goto reswitch; 
  end; 
vmode+stop: if its_all_over then return; {this is the only way out} 
(*\4*)
INSERT: 'Forbidden cases detected in |main_control|'
 any_mode(mac_param): 
  report_illegal_case; 

INSERT: 'Math-only cases in non-math modes, or vice versa'
: insert_dollar_sign; 
(*\4*)
INSERT: 'Cases of |main_control| that build boxes and lists'
; 
(*\4*)
INSERT: 'Cases of |main_control| that don''t depend on |mode|'
; 
(*\4*)
INSERT: 'Cases of |main_control| that are for extensions to \TeX'
; 

MODULE: 'Math-only cases in non-math modes...'
(*PASCAL module 1046*)
non_math(sup_mark), non_math(sub_mark), non_math(math_char_num), 
non_math(math_given), non_math(math_comp), non_math(delim_num), 
non_math(left_right), non_math(above), non_math(radical), 
non_math(math_style), non_math(math_choice), non_math(vcenter), 
non_math(non_script), non_math(mkern), non_math(limit_switch), 
non_math(mskip), non_math(math_accent), 
mmode+endv, mmode+par_end, mmode+stop, mmode+vskip, mmode+un_vbox, 
mmode+valign, mmode+hrule 

MODULE: 'Declare action...'
(*PASCAL module 1047*)
procedure insert_dollar_sign; 
begin back_input; cur_tok:=math_shift_token+'$'; 
print_err('Missing $ inserted'); 
(*Missing \$ inserted*) 
help2('I''ve inserted a begin-math/end-math symbol since I think')
 
('you left one out. Proceed, with fingers crossed.'); ins_error; 
end; 

MODULE: 'Forbidden cases...'
(*PASCAL module 1048*)
vmode+vmove,hmode+hmove,mmode+hmove,any_mode(last_item), 

MODULE: 'Declare action...'
(*PASCAL module 1049*)
procedure you_cant; 
begin print_err('You can''t use `'); 
(*You can''t use x in y mode*) 
print_cmd_chr(cur_cmd,cur_chr); 
print(''' in '); print_mode(mode); 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1050*)
procedure report_illegal_case; 
begin you_cant; 
help4('Sorry, but I''m not programmed to handle this case;')
 
('I''ll just pretend that you didn''t ask for it.')
 
('If you''re in the wrong mode, you might be able to')
 
('return to the right one by typing `I}'' or `I$'' or `I\par''.');
 
error; 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1051*)
function privileged:boolean; 
begin if mode>0 then privileged:=true 
else  begin report_illegal_case; privileged:=false; 
  end; 
end; 

MODULE: 'Put each...'
(*PASCAL module 1052*)
primitive('end',stop,0);
 
(*end_][\.{\\end} primitive*) 
primitive('dump',stop,1);
 
(*dump_][\.{\\dump} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1053*)
stop:if chr_code=1 then print_esc('dump')else print_esc('end'); 

MODULE: 'Declare act...'
(*PASCAL module 1054*)
function its_all_over:boolean; {do this when \.[\\end] or \.[\\dump] occurs} 
label exit; 
begin if privileged then 
  begin if (page_head=page_tail)and(head=tail)and(dead_cycles=0) then 
    begin its_all_over:=true; return; 
    end; 
  back_input; {we will try to end again after ejecting residual material} 
  tail_append(new_null_box); 
  width(tail):=hsize; 
  tail_append(new_glue(fill_glue)); 
  tail_append(new_penalty(-1073741824));
 
  build_page; {append \.[\\hbox to \\hsize\[\]\\vfill\\penalty-'10000000000]} 
  end; 
its_all_over:=false; 
exit:end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1056*)
vmode+hrule,hmode+vrule,mmode+vrule: begin tail_append(scan_rule_spec); 
  if abs(mode)=vmode then prev_depth:=ignore_depth 
  else if abs(mode)=hmode then space_factor:=1000; 
  end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1057*)
vmode+vskip,hmode+hskip,mmode+hskip,mmode+mskip: append_glue; 
any_mode(kern),mmode+mkern: append_kern; 

MODULE: 'Put each...'
(*PASCAL module 1058*)
primitive('hskip',hskip,skip_code);
 
(*hskip_][\.{\\hskip} primitive*) 
primitive('hfil',hskip,fil_code); 
(*hfil_][\.{\\hfil} primitive*) 
primitive('hfill',hskip,fill_code);
 
(*hfill_][\.{\\hfill} primitive*) 
primitive('hss',hskip,ss_code); 
(*hss_][\.{\\hss} primitive*) 
primitive('hfilneg',hskip,fil_neg_code);
 
(*hfil_neg_][\.{\\hfilneg} primitive*) 
primitive('vskip',vskip,skip_code);
 
(*vskip_][\.{\\vskip} primitive*) 
primitive('vfil',vskip,fil_code); 
(*vfil_][\.{\\vfil} primitive*) 
primitive('vfill',vskip,fill_code);
 
(*vfill_][\.{\\vfill} primitive*) 
primitive('vss',vskip,ss_code); 
(*vss_][\.{\\vss} primitive*) 
primitive('vfilneg',vskip,fil_neg_code);
 
(*vfil_neg_][\.{\\vfilneg} primitive*) 
primitive('mskip',mskip,mskip_code);
 
(*mskip_][\.{\\mskip} primitive*) 
primitive('kern',kern,explicit); 
(*kern_][\.{\\kern} primitive*) 
primitive('mkern',mkern,mu_glue);
 
(*mkern_][\.{\\mkern} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1059*)
hskip: case chr_code of 
  skip_code:print_esc('hskip'); 
  fil_code:print_esc('hfil'); 
  fill_code:print_esc('hfill'); 
  ss_code:print_esc('hss'); 
  othercases print_esc('hfilneg') 
  endcases; 
vskip: case chr_code of 
  skip_code:print_esc('vskip'); 
  fil_code:print_esc('vfil'); 
  fill_code:print_esc('vfill'); 
  ss_code:print_esc('vss'); 
  othercases print_esc('vfilneg') 
  endcases; 
mskip: print_esc('mskip'); 
kern: print_esc('kern'); 
mkern: print_esc('mkern'); 

MODULE: 'Declare action...'
(*PASCAL module 1060*)
procedure append_glue; 
var s:small_number; {modifier of skip command} 
begin s:=cur_chr; 
case s of 
fil_code: cur_val:=fil_glue; 
fill_code: cur_val:=fill_glue; 
ss_code: cur_val:=ss_glue; 
fil_neg_code: cur_val:=fil_neg_glue; 
skip_code: scan_glue(glue_val); 
mskip_code: scan_glue(mu_val); 
end; {now |cur_val| points to the glue specification} 
tail_append(new_glue(cur_val)); 
if s>=skip_code then 
  begin decr(glue_ref_count(cur_val)); 
  if s>skip_code then subtype(tail):=mu_glue; 
  end; 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1061*)
procedure append_kern; 
var s:quarterword; {|subtype| of the kern node} 
begin s:=cur_chr; scan_dimen(s=mu_glue,false,false); 
tail_append(new_kern(cur_val)); subtype(tail):=s; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1063*)
non_math(left_brace): new_save_level(simple_group); 
any_mode(begin_group): new_save_level(semi_simple_group); 
any_mode(end_group): if cur_group=semi_simple_group then unsave 
  else off_save; 

MODULE: 'Declare act...'
(*PASCAL module 1064*)
procedure off_save; 
var p:pointer; {inserted token} 
begin if cur_group=bottom_level then 
  
INSERT: 'Drop current token and complain that it was unmatched'

else  begin back_input; p:=get_avail; link(temp_head):=p; 
  print_err('Missing '); 
  
INSERT: 'Prepare to insert a token that matches |cur_group|,     and print what it is'
; 
  print(' inserted'); ins_list(link(temp_head)); 
  help5('I''ve inserted something that you may have forgotten.')
 
  ('(See the <inserted text> above.)')
 
  ('With luck, this will get me unwedged. But if you')
 
  ('really didn''t forget anything, try typing `2'' now; then')
 
  ('my insertion and my current dilemma will both disappear.'); 
  error; 
  end; 
end; 

MODULE: 'Prepare to insert a token that matches |cur_group|...'
(*PASCAL module 1065*)
case cur_group of 
semi_simple_group: begin info(p):=cs_token_flag+frozen_end_group; 
  print_esc('endgroup'); 
(*Missing \\endgroup inserted*) 
  end; 
math_shift_group: begin info(p):=math_shift_token+'$'; print_char('$'); 
(*Missing \$ inserted*) 
  end; 
math_left_group: begin info(p):=cs_token_flag+frozen_right; link(p):=get_avail; 
  p:=link(p); info(p):=other_token+'.'; print_esc('right.'); 
(*Missing \\right\hbox{.} inserted*) 
(*null delimiter*) 
  end; 
othercases begin info(p):=right_brace_token+'}'; print_char('}'); 
(*Missing \] 
inserted*) 
  end 
endcases 

MODULE: 'Drop current token and complain that it was unmatched'
(*PASCAL module 1066*)
begin print_err('Extra '); print_cmd_chr(cur_cmd,cur_chr); 
(*Extra x*) 
help1('Things are pretty mixed up, but I think the worst is over.');
 
error; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1067*)
any_mode(right_brace): handle_right_brace; 

MODULE: 'Declare the procedure called |handle_right_brace|'
(*PASCAL module 1068*)
procedure handle_right_brace; 
var p,q:pointer; {for short-term use} 
d:scaled; {holds |split_max_depth| in |insert_group|} 
f:integer; {holds |floating_penalty| in |insert_group|} 
begin case cur_group of 
simple_group: unsave; 
bottom_level: begin print_err('Too many }''s'); 
(*Too many \]''s*) 

  help2('You''ve closed more groups than you opened.')
 
  ('Such booboos are generally harmless, so keep going.'); error; 
  end; 
semi_simple_group,math_shift_group,math_left_group: extra_right_brace; 
(*\4*)
INSERT: 'Cases of |handle_right_brace| where a |right_brace| triggers   a delayed action'
; 
othercases confusion('rightbrace') 
(*this can''t happen rightbrace][\quad rightbrace*) 
endcases; 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1069*)
procedure extra_right_brace; 
begin print_err('Extra }, or forgotten '); 
(*Extra \], 
or forgotten x*) 
case cur_group of 
semi_simple_group: print_esc('endgroup'); 
math_shift_group: print_char('$'); 
math_left_group: print_esc('right'); 
end;
 
help5('I''ve deleted a group-closing symbol because it seems to be')
 
('spurious, as in `$x}$''. But perhaps the } is legitimate and')
 
('you forgot something else, as in `\hbox{$x}''. In such cases')
 
('the way to recover is to insert both the forgotten and the')
 
('deleted material, e.g., by typing `I$}''.'); error; 
incr(align_state); 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1070*)
procedure normal_paragraph; 
begin if looseness<>0 then eq_word_define(int_base+looseness_code,0); 
if hang_indent<>0 then eq_word_define(dimen_base+hang_indent_code,0); 
if hang_after<>1 then eq_word_define(int_base+hang_after_code,1); 
if par_shape_ptr<>null then eq_define(par_shape_loc,shape_ref,null); 
end; 

MODULE: 'Put each...'
(*PASCAL module 1071*)
primitive('moveleft',hmove,1); 
(*move_left_][\.{\\moveleft} primitive*) 
primitive('moveright',hmove,0);
 
(*move_right_][\.{\\moveright} primitive*) 
primitive('raise',vmove,1); 
(*raise_][\.{\\raise} primitive*) 
primitive('lower',vmove,0); 
(*lower_][\.{\\lower} primitive*) 


 
primitive('box',make_box,box_code); 
(*box_][\.{\\box} primitive*) 
primitive('copy',make_box,copy_code); 
(*copy_][\.{\\copy} primitive*) 
primitive('lastbox',make_box,last_box_code); 
(*last_box_][\.{\\lastbox} primitive*) 
primitive('vsplit',make_box,vsplit_code); 
(*vsplit_][\.{\\vsplit} primitive*) 
primitive('vtop',make_box,vtop_code);
 
(*vtop_][\.{\\vtop} primitive*) 
primitive('vbox',make_box,vtop_code+vmode); 
(*vbox_][\.{\\vbox} primitive*) 
primitive('hbox',make_box,vtop_code+hmode);
 
(*hbox_][\.{\\hbox} primitive*) 
primitive('shipout',leader_ship,a_leaders-1); {|ship_out_flag=leader_flag-1|} 
(*ship_out_][\.{\\shipout} primitive*) 
primitive('leaders',leader_ship,a_leaders); 
(*leaders_][\.{\\leaders} primitive*) 
primitive('cleaders',leader_ship,c_leaders); 
(*c_leaders_][\.{\\cleaders} primitive*) 
primitive('xleaders',leader_ship,x_leaders); 
(*x_leaders_][\.{\\xleaders} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1072*)
hmove: if chr_code=1 then print_esc('moveleft')else print_esc('moveright'); 
vmove: if chr_code=1 then print_esc('raise')else print_esc('lower'); 
make_box: case chr_code of 
  box_code: print_esc('box'); 
  copy_code: print_esc('copy'); 
  last_box_code: print_esc('lastbox'); 
  vsplit_code: print_esc('vsplit'); 
  vtop_code: print_esc('vtop'); 
  vtop_code+vmode: print_esc('vbox'); 
  othercases print_esc('hbox') 
  endcases; 
leader_ship: if chr_code=a_leaders then print_esc('leaders') 
  else if chr_code=c_leaders then print_esc('cleaders') 
  else if chr_code=x_leaders then print_esc('xleaders') 
  else print_esc('shipout'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1073*)
vmode+hmove,hmode+vmove,mmode+vmove: begin t:=cur_chr; 
  scan_normal_dimen; 
  if t=0 then scan_box(cur_val)else scan_box(-cur_val); 
  end; 
any_mode(leader_ship): scan_box(leader_flag-a_leaders+cur_chr); 
any_mode(make_box): begin_box(0); 

MODULE: 'Glob... '
(*PASCAL module 1074*)
cur_box:pointer; {box to be placed into its context} 

MODULE: 'Declare act...'
(*PASCAL module 1075*)
procedure box_end(box_context:integer); 
var p:pointer; {|ord_noad| for new box in math mode} 
begin if box_context<box_flag then 
INSERT: 'Append box |cur_box| to the current list,     shifted by |box_context|'

else if box_context<ship_out_flag then 
INSERT: 'Store \(c)|cur_box| in a box register'

else if cur_box<>null then 
  if box_context>ship_out_flag then 
INSERT: 'Append a new leader node that       uses |cur_box|'

  else ship_out(cur_box); 
end; 

MODULE: 'Append box |cur_box| to the current...'
(*PASCAL module 1076*)
begin if cur_box<>null then 
  begin shift_amount(cur_box):=box_context; 
  if abs(mode)=vmode then 
    begin append_to_vlist(cur_box); 
    if adjust_tail<>null then 
      begin if adjust_head<>adjust_tail then 
        begin link(tail):=link(adjust_head); tail:=adjust_tail; 
        end; 
      adjust_tail:=null; 
      end; 
    if mode>0 then build_page; 
    end 
  else  begin if abs(mode)=hmode then space_factor:=1000 
    else  begin p:=new_noad; 
      math_type(nucleus(p)):=sub_box; 
      info(nucleus(p)):=cur_box; cur_box:=p; 
      end; 
    link(tail):=cur_box; tail:=cur_box; 
    end; 
  end; 
end 

MODULE: 'Store \(c)|cur_box| in a box register'
(*PASCAL module 1077*)
if box_context<box_flag+256 then 
  eq_define(box_base-box_flag+box_context,box_ref,cur_box) 
else geq_define(box_base-box_flag-256+box_context,box_ref,cur_box) 

MODULE: 'Append a new leader node ...'
(*PASCAL module 1078*)
begin 
INSERT: 'Get the next non-blank non-relax...'
; 
if ((cur_cmd=hskip)and(abs(mode)<>vmode))or 
   ((cur_cmd=vskip)and(abs(mode)=vmode)) then 
  begin append_glue; subtype(tail):=box_context-(leader_flag-a_leaders); 
  leader_ptr(tail):=cur_box; 
  end 
else  begin print_err('Leaders not followed by proper glue'); 
(*Leaders not followed by...*) 
  help3('You should say `\leaders <box or rule><hskip or vskip>''.')
 
  ('I found the <box or rule>, but there''s no suitable')
 
  ('<hskip or vskip>, so I''m ignoring these leaders.'); back_error; 
  flush_node_list(cur_box); 
  end; 
end 

MODULE: 'Declare act...'
(*PASCAL module 1079*)
procedure begin_box(box_context:integer); 
label exit, done; 
var p,q:pointer; {run through the current list} 
m:quarterword; {the length of a replacement list} 
k:halfword; {0 or |vmode| or |hmode|} 
n:eight_bits; {a box number} 
begin case cur_chr of 
box_code: begin scan_eight_bit_int; cur_box:=box(cur_val); 
  box(cur_val):=null; {the box becomes void, at the same level} 
  end; 
copy_code: begin scan_eight_bit_int; cur_box:=copy_node_list(box(cur_val)); 
  end; 
last_box_code: 
INSERT: 'If the current list ends with a box node, delete it from   the list and make |cur_box| point to it; otherwise set |cur_box:=null|'
; 
vsplit_code: 
INSERT: 'Split off part of a vertical box, make |cur_box| point to it'
; 
othercases 
INSERT: 'Initiate the construction of an hbox or vbox, then |return|'

endcases;
 
box_end(box_context); {in simple cases, we use the box immediately} 
exit:end; 

MODULE: 'If the current list ends with a box node, delete it...'
(*PASCAL module 1080*)
begin cur_box:=null; 
if abs(mode)=mmode then 
  begin you_cant; help1('Sorry; this \lastbox will be void.'); error; 
  end 
else if (mode=vmode)and(head=tail) then 
  begin you_cant; 
  help2('Sorry...I usually can''t take things from the current page.')
 
    ('This \lastbox will therefore be void.'); error; 
  end 
else  begin if not is_char_node(tail) then 
    if (type(tail)=hlist_node)or(type(tail)=vlist_node) then 
      
INSERT: 'Remove the last box, unless it''s part of a discretionary'
; 
  end; 
end 

MODULE: 'Remove the last box...'
(*PASCAL module 1081*)
begin q:=head; 
repeat p:=q; 
if not is_char_node(q) then if type(q)=disc_node then 
  begin for m:=1 to replace_count(q) do p:=link(p); 
  if p=tail then goto done; 
  end; 
q:=link(p); 
until q=tail; 
cur_box:=tail; shift_amount(cur_box):=0; 
tail:=p; link(p):=null; 
done:end 

MODULE: 'Split off part of a vertical box, make |cur_box| point to it'
(*PASCAL module 1082*)
begin scan_eight_bit_int; n:=cur_val; 
if not scan_keyword('to') then 
(*to*) 
  begin print_err('Missing `to'' inserted'); 
(*Missing `to'' inserted*) 
  help2('I''m working on `\vsplit<box number> to <dimen>'';')
 
  ('will look for the <dimen> next.'); error; 
  end; 
scan_normal_dimen; 
cur_box:=vsplit(n,cur_val); 
end 

MODULE: 'Initiate the construction of an hbox or vbox, then |return|'
(*PASCAL module 1083*)
begin k:=cur_chr-vtop_code; saved(0):=box_context; 
if k=hmode then 
  if (box_context<box_flag)and(abs(mode)=vmode) then 
    scan_spec(adjusted_hbox_group,true) 
  else scan_spec(hbox_group,true) 
else  begin if k=vmode then scan_spec(vbox_group,true) 
  else  begin scan_spec(vtop_group,true); k:=vmode; 
    end; 
  normal_paragraph; 
  end; 
push_nest; mode:=-k; 
if k=vmode then 
  begin prev_depth:=ignore_depth; 
  if every_vbox<>null then begin_token_list(every_vbox,every_vbox_text); 
  end 
else  begin space_factor:=1000; 
  if every_hbox<>null then begin_token_list(every_hbox,every_hbox_text); 
  end; 
return; 
end 

MODULE: 'Declare act...'
(*PASCAL module 1084*)
procedure scan_box(box_context:integer); 
  {the next input should specify a box or perhaps a rule} 
begin 
INSERT: 'Get the next non-blank non-relax...'
; 
if cur_cmd=make_box then begin_box(box_context) 
else if (box_context>=leader_flag)and((cur_cmd=hrule)or(cur_cmd=vrule)) then 
  begin cur_box:=scan_rule_spec; box_end(box_context); 
  end 
else  begin(**);
 
  print_err('A <box> was supposed to be here');
 
(*A <box> was supposed to...*) 
  help3('I was expecting to see \hbox or \vbox or \copy or \box or')
 
  ('something like that. So you might find something missing in')
 
  ('your output. But keep trying; you can fix this later.'); back_error; 
  end; 
end; 

MODULE: 'Cases of |handle...'
(*PASCAL module 1085*)
hbox_group: package(0); 
adjusted_hbox_group: begin adjust_tail:=adjust_head; package(0); 
  end; 
vbox_group: begin end_graf; package(0); 
  end; 
vtop_group: begin end_graf; package(vtop_code); 
  end; 

MODULE: 'Declare action...'
(*PASCAL module 1086*)
procedure package(c:small_number); 
var h:scaled; {height of box} 
p:pointer; {first node in a box} 
d:scaled; {max depth} 
begin d:=box_max_depth; unsave; save_ptr:=save_ptr-3; 
if mode=-hmode then cur_box:=hpack(link(head),saved(2),saved(1)) 
else  begin cur_box:=vpackage(link(head),saved(2),saved(1),d); 
  if c=vtop_code then 
INSERT: 'Readjust the height and depth of |cur_box|,     for \.{\\vtop}'
; 
  end; 
pop_nest; box_end(saved(0)); 
end; 

MODULE: 'Readjust the height...'
(*PASCAL module 1087*)
begin h:=0; p:=list_ptr(cur_box); 
if p<>null then if type(p)<=rule_node then h:=height(p); 
depth(cur_box):=depth(cur_box)-h+height(cur_box); height(cur_box):=h; 
end 

MODULE: 'Put each...'
(*PASCAL module 1088*)
primitive('indent',start_par,1); 
(*indent_][\.{\\indent} primitive*) 
primitive('noindent',start_par,0); 
(*no_indent_][\.{\\noindent} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1089*)
start_par: if chr_code=0 then print_esc('noindent') else print_esc('indent'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1090*)
vmode+start_par: new_graf(cur_chr>0); 
vmode+letter,vmode+other_char,vmode+char_num,vmode+char_given, 
   vmode+math_shift,vmode+un_hbox,vmode+vrule, 
   vmode+accent,vmode+discretionary,vmode+hskip,vmode+valign, 
   vmode+ex_space,vmode+no_boundary:(**);
 
  begin back_input; new_graf(true); 
  end; 

MODULE: 'Declare act...'
(*PASCAL module 1091*)
function norm_min(h:integer):small_number; 
begin if h<=0 then norm_min:=1else if h>=63 then norm_min:=63 
else norm_min:=h; 
end; 


 
procedure new_graf(indented:boolean); 
begin prev_graf:=0; 
if (mode=vmode)or(head<>tail) then 
  tail_append(new_param_glue(par_skip_code)); 
push_nest; mode:=hmode; space_factor:=1000; set_cur_lang; clang:=cur_lang; 
prev_graf:=(norm_min(left_hyphen_min)*64+norm_min(right_hyphen_min)) 
             *65536+cur_lang; 
if indented then 
  begin tail:=new_null_box; link(head):=tail; width(tail):=par_indent; 
  end; 
if every_par<>null then begin_token_list(every_par,every_par_text); 
if nest_ptr=1 then build_page; {put |par_skip| glue on current page} 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1092*)
hmode+start_par,mmode+start_par: indent_in_hmode; 

MODULE: 'Declare act...'
(*PASCAL module 1093*)
procedure indent_in_hmode; 
var p,q:pointer; 
begin if cur_chr>0 then {\.[\\indent]} 
  begin p:=new_null_box; width(p):=par_indent; 
  if abs(mode)=hmode then space_factor:=1000 
  else  begin q:=new_noad; math_type(nucleus(q)):=sub_box; 
    info(nucleus(q)):=p; p:=q; 
    end; 
  tail_append(p); 
  end; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1094*)
vmode+par_end: begin normal_paragraph; 
  if mode>0 then build_page; 
  end; 
hmode+par_end: begin if align_state<0 then off_save; {this tries to 
    recover from an alignment that didn't end properly} 
  end_graf; {this takes us to the enclosing mode, if |mode>0|} 
  if mode=vmode then build_page; 
  end; 
hmode+stop,hmode+vskip,hmode+hrule,hmode+un_vbox,hmode+halign: head_for_vmode; 

MODULE: 'Declare act...'
(*PASCAL module 1095*)
procedure head_for_vmode; 
begin if mode<0 then 
  if cur_cmd<>hrule then off_save 
  else  begin print_err('You can''t use `'); 
    print_esc('hrule'); print(''' here except with leaders'); 
(*You can''t use \\hrule...*) 
    help2('To put a horizontal rule in an hbox or an alignment,')
 
      ('you should use \leaders or \hrulefill (see The TeXbook).'); 
    error; 
    end 
else  begin back_input; cur_tok:=par_token; back_input; token_type:=inserted; 
  end; 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1096*)
procedure end_graf; 
begin if mode=hmode then 
  begin if head=tail then pop_nest {null paragraphs are ignored} 
  else line_break(widow_penalty); 
  normal_paragraph; 
  error_count:=0; 
  end; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1097*)
any_mode(insert),hmode+vadjust,mmode+vadjust: begin_insert_or_adjust; 
any_mode(mark): make_mark; 

MODULE: 'Forbidden... '
(*PASCAL module 1098*)
vmode+vadjust, 

MODULE: 'Declare act...'
(*PASCAL module 1099*)
procedure begin_insert_or_adjust; 
begin if cur_cmd=vadjust then cur_val:=255 
else  begin scan_eight_bit_int; 
  if cur_val=255 then 
    begin print_err('You can''t '); print_esc('insert'); print_int(255); 
(*You can''t \\insert255*) 
    help1('I''m changing to \insert0; box 255 is special.'); 
    error; cur_val:=0; 
    end; 
  end; 
saved(0):=cur_val; incr(save_ptr); 
new_save_level(insert_group); scan_left_brace; normal_paragraph; 
push_nest; mode:=-vmode; prev_depth:=ignore_depth; 
end; 

MODULE: 'Cases of |handle...'
(*PASCAL module 1100*)
insert_group: begin end_graf; q:=split_top_skip; add_glue_ref(q); 
  d:=split_max_depth; f:=floating_penalty; unsave; decr(save_ptr); 
  {now |saved(0)| is the insertion number, or 255 for |vadjust|} 
  p:=vpack(link(head),natural); pop_nest; 
  if saved(0)<255 then 
    begin tail_append(get_node(ins_node_size)); 
    type(tail):=ins_node; subtype(tail):=qi(saved(0)); 
    height(tail):=height(p)+depth(p); ins_ptr(tail):=list_ptr(p); 
    split_top_ptr(tail):=q; depth(tail):=d; float_cost(tail):=f; 
    end 
  else  begin tail_append(get_node(small_node_size)); 
    type(tail):=adjust_node;
 
    subtype(tail):=0; {the |subtype| is not used} 
    adjust_ptr(tail):=list_ptr(p); delete_glue_ref(q); 
    end; 
  free_node(p,box_node_size); 
  if nest_ptr=0 then build_page; 
  end; 
output_group: 
INSERT: 'Resume the page builder...'
; 

MODULE: 'Declare act...'
(*PASCAL module 1101*)
procedure make_mark; 
var p:pointer; {new node} 
begin p:=scan_toks(false,true); p:=get_node(small_node_size); 
type(p):=mark_node; subtype(p):=0; {the |subtype| is not used} 
mark_ptr(p):=def_ref; link(tail):=p; tail:=p; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1102*)
any_mode(break_penalty): append_penalty; 

MODULE: 'Declare action...'
(*PASCAL module 1103*)
procedure append_penalty; 
begin scan_int; tail_append(new_penalty(cur_val)); 
if mode=vmode then build_page; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1104*)
any_mode(remove_item): delete_last; 

MODULE: 'Declare action...'
(*PASCAL module 1105*)
procedure delete_last; 
label exit; 
var p,q:pointer; {run through the current list} 
m:quarterword; {the length of a replacement list} 
begin if (mode=vmode)and(tail=head) then 
  
INSERT: 'Apologize for inability to do the operation now,     unless \.{\\unskip} follows non-glue'

else  begin if not is_char_node(tail) then if type(tail)=cur_chr then 
    begin q:=head; 
    repeat p:=q; 
    if not is_char_node(q) then if type(q)=disc_node then 
      begin for m:=1 to replace_count(q) do p:=link(p); 
      if p=tail then return; 
      end; 
    q:=link(p); 
    until q=tail; 
    link(p):=null; flush_node_list(tail); tail:=p; 
    end; 
  end; 
exit:end; 

MODULE: 'Apologize for inability to do the operation...'
(*PASCAL module 1106*)
begin if (cur_chr<>glue_node)or(last_glue<>max_halfword) then 
  begin you_cant; 
  help2('Sorry...I usually can''t take things from the current page.')
 
    ('Try `I\vskip-\lastskip'' instead.'); 
  if cur_chr=kern_node then help_line[0]:= 
    ('Try `I\kern-\lastkern'' instead.') 
  else if cur_chr<>glue_node then help_line[0]:= 
    ('Perhaps you can make the output routine do it.'); 
  error; 
  end; 
end 

MODULE: 'Put each...'
(*PASCAL module 1107*)
primitive('unpenalty',remove_item,penalty_node);
 
(*un_penalty_][\.{\\unpenalty} primitive*) 
primitive('unkern',remove_item,kern_node);
 
(*un_kern_][\.{\\unkern} primitive*) 
primitive('unskip',remove_item,glue_node);
 
(*un_skip_][\.{\\unskip} primitive*) 
primitive('unhbox',un_hbox,box_code);
 
(*un_hbox_][\.{\\unhbox} primitive*) 
primitive('unhcopy',un_hbox,copy_code);
 
(*un_hcopy_][\.{\\unhcopy} primitive*) 
primitive('unvbox',un_vbox,box_code);
 
(*un_vbox_][\.{\\unvbox} primitive*) 
primitive('unvcopy',un_vbox,copy_code);
 
(*un_vcopy_][\.{\\unvcopy} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1108*)
remove_item: if chr_code=glue_node then print_esc('unskip') 
  else if chr_code=kern_node then print_esc('unkern') 
  else print_esc('unpenalty'); 
un_hbox: if chr_code=copy_code then print_esc('unhcopy') 
  else print_esc('unhbox'); 
un_vbox: if chr_code=copy_code then print_esc('unvcopy') 
  else print_esc('unvbox'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1109*)
vmode+un_vbox,hmode+un_hbox,mmode+un_hbox: unpackage; 

MODULE: 'Declare act...'
(*PASCAL module 1110*)
procedure unpackage; 
label exit; 
var p:pointer; {the box} 
c:box_code..copy_code; {should we copy?} 
begin c:=cur_chr; scan_eight_bit_int; p:=box(cur_val); 
if p=null then return; 
if (abs(mode)=mmode)or((abs(mode)=vmode)and(type(p)<>vlist_node))or 
   ((abs(mode)=hmode)and(type(p)<>hlist_node)) then 
  begin print_err('Incompatible list can''t be unboxed'); 
(*Incompatible list...*) 
  help3('Sorry, Pandora. (You sneaky devil.)')
 
  ('I refuse to unbox an \hbox in vertical mode or vice versa.')
 
  ('And I can''t open any boxes in math mode.');
 
  error; return; 
  end; 
if c=copy_code then link(tail):=copy_node_list(list_ptr(p)) 
else  begin link(tail):=list_ptr(p); box(cur_val):=null; 
  free_node(p,box_node_size); 
  end; 
while link(tail)<>null do tail:=link(tail); 
exit:end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1112*)
hmode+ital_corr: append_italic_correction; 
mmode+ital_corr: tail_append(new_kern(0)); 

MODULE: 'Declare act...'
(*PASCAL module 1113*)
procedure append_italic_correction; 
label exit; 
var p:pointer; {|char_node| at the tail of the current list} 
f:internal_font_number; {the font in the |char_node|} 
begin if tail<>head then 
  begin if is_char_node(tail) then p:=tail 
  else if type(tail)=ligature_node then p:=lig_char(tail) 
  else return; 
  f:=font(p); 
  tail_append(new_kern(char_italic(f)(char_info(f)(character(p))))); 
  subtype(tail):=explicit; 
  end; 
exit:end; 

MODULE: 'Put each...'
(*PASCAL module 1114*)
primitive('-',discretionary,1); 
(*Single-character primitives -][\quad\.{\\-}*) 
primitive('discretionary',discretionary,0); 
(*discretionary_][\.{\\discretionary} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1115*)
discretionary: if chr_code=1 then 
  print_esc('-')else print_esc('discretionary'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1116*)
hmode+discretionary,mmode+discretionary: append_discretionary; 

MODULE: 'Declare act...'
(*PASCAL module 1117*)
procedure append_discretionary; 
var c:integer; {hyphen character} 
begin tail_append(new_disc); 
if cur_chr=1 then 
  begin c:=hyphen_char[cur_font]; 
  if c>=0 then if c<256 then pre_break(tail):=new_character(cur_font,c); 
  end 
else  begin incr(save_ptr); saved(-1):=0; new_save_level(disc_group); 
  scan_left_brace; push_nest; mode:=-hmode; space_factor:=1000; 
  end; 
end; 

MODULE: 'Cases of |handle...'
(*PASCAL module 1118*)
disc_group: build_discretionary; 

MODULE: 'Declare act...'
(*PASCAL module 1119*)
procedure build_discretionary; 
label done,exit; 
var p,q:pointer; {for link manipulation} 
n:integer; {length of discretionary list} 
begin unsave; 

INSERT: 'Prune the current list, if necessary, until it contains only   |char_node|, |kern_node|, |hlist_node|, |vlist_node|, |rule_node|,   and |ligature_node| items; set |n| to the length of the list,   and set |q| to the list''s tail'
; 
p:=link(head); pop_nest; 
case saved(-1) of 
0:pre_break(tail):=p; 
1:post_break(tail):=p; 
2:
INSERT: 'Attach list |p| to the current list, and record its length;   then finish up and |return|'
; 
end; {there are no other cases} 
incr(saved(-1)); new_save_level(disc_group); scan_left_brace; 
push_nest; mode:=-hmode; space_factor:=1000; 
exit:end; 

MODULE: 'Attach list |p| to the current...'
(*PASCAL module 1120*)
begin if (n>0)and(abs(mode)=mmode) then 
  begin print_err('Illegal math '); print_esc('discretionary'); 
(*Illegal math \\disc...*) 
  help2('Sorry: The third part of a discretionary break must be')
 
  ('empty, in math formulas. I had to delete your third part.'); 
  flush_node_list(p); n:=0; error; 
  end 
else link(tail):=p; 
if n<=max_quarterword then replace_count(tail):=n 
else  begin print_err('Discretionary list is too long'); 
(*Discretionary list is too long*) 
  help2('Wow---I never thought anybody would tweak me here.')
 
  ('You can''t seriously need such a huge discretionary list?'); 
  error; 
  end; 
if n>0 then tail:=q; 
decr(save_ptr); return; 
end 

MODULE: 'Prune the current list, if necessary...'
(*PASCAL module 1121*)
q:=head; p:=link(q); n:=0; 
while p<>null do 
  begin if not is_char_node(p) then if type(p)>rule_node then 
    if type(p)<>kern_node then if type(p)<>ligature_node then 
      begin print_err('Improper discretionary list'); 
(*Improper discretionary list*) 
      help1('Discretionary lists must contain only boxes and kerns.');
 
      error; 
      begin_diagnostic; 
      print_nl('The following discretionary sublist has been deleted:'); 
(*The following...deleted*) 
      show_box(p); 
      end_diagnostic(true); 
      flush_node_list(p); link(q):=null; goto done; 
      end; 
  q:=p; p:=link(q); incr(n); 
  end; 
done: 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1122*)
hmode+accent: make_accent; 

MODULE: 'Declare act...'
(*PASCAL module 1123*)
procedure make_accent; 
var s,t: real; {amount of slant} 
p,q,r:pointer; {character, box, and kern nodes} 
f:internal_font_number; {relevant font} 
a,h,x,w,delta:scaled; {heights and widths, as explained above} 
i:four_quarters; {character information} 
begin scan_char_num; f:=cur_font; p:=new_character(f,cur_val); 
if p<>null then 
  begin x:=x_height(f); s:=slant(f)/float_constant(65536); 
(*real division*) 
  a:=char_width(f)(char_info(f)(character(p)));
 
  do_assignments;
 
  
INSERT: 'Create a character node |q| for the next character,     but set |q:=null| if problems arise'
; 
  if q<>null then 
INSERT: 'Append the accent with appropriate kerns,       then set |p:=q|'
; 
  link(tail):=p; tail:=p; space_factor:=1000; 
  end; 
end; 

MODULE: 'Create a character node |q| for the next...'
(*PASCAL module 1124*)
q:=null; f:=cur_font; 
if (cur_cmd=letter)or(cur_cmd=other_char)or(cur_cmd=char_given) then 
  q:=new_character(f,cur_chr) 
else if cur_cmd=char_num then 
  begin scan_char_num; q:=new_character(f,cur_val); 
  end 
else back_input 

MODULE: 'Append the accent with appropriate kerns...'
(*PASCAL module 1125*)
begin t:=slant(f)/float_constant(65536); 
(*real division*) 
i:=char_info(f)(character(q)); 
w:=char_width(f)(i); h:=char_height(f)(height_depth(i)); 
if h<>x then {the accent must be shifted up or down} 
  begin p:=hpack(p,natural); shift_amount(p):=x-h; 
  end; 
delta:=round((w-a)/float_constant(2)+h*t-x*s); 
(*real multiplication*) 
(*real addition*) 
r:=new_kern(delta); subtype(r):=acc_kern; link(tail):=r; link(r):=p; 
tail:=new_kern(-a-delta); subtype(tail):=acc_kern; link(p):=tail; p:=q; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1126*)
any_mode(car_ret), any_mode(tab_mark): align_error; 
any_mode(no_align): no_align_error; 
any_mode(omit): omit_error; 

MODULE: 'Declare act...'
(*PASCAL module 1127*)
procedure align_error; 
begin if abs(align_state)>2 then 
  
INSERT: 'Express consternation over the fact that no alignment is in progress'

else  begin back_input; 
  if align_state<0 then 
    begin print_err('Missing { inserted'); 
(*Missing \[
inserted*) 
    incr(align_state); cur_tok:=left_brace_token+'{'; 
    end 
  else  begin print_err('Missing } inserted'); 
(*Missing \] 
inserted*) 
    decr(align_state); cur_tok:=right_brace_token+'}'; 
    end; 
  help3('I''ve put in what seems to be necessary to fix')
 
    ('the current column of the current alignment.')
 
    ('Try to go on, since this might almost work.'); ins_error; 
  end; 
end; 

MODULE: 'Express consternation...'
(*PASCAL module 1128*)
begin print_err('Misplaced '); print_cmd_chr(cur_cmd,cur_chr); 
(*Misplaced \&*) 
(*Misplaced \\span*) 
(*Misplaced \\cr*) 
if cur_tok=tab_token+'&' then 
  begin help6('I can''t figure out why you would want to use a tab mark')
 
  ('here. If you just want an ampersand, the remedy is')
 
  ('simple: Just type `I\&'' now. But if some right brace')
 
  ('up above has ended a previous alignment prematurely,')
 
  ('you''re probably due for more error messages, and you')
 
  ('might try typing `S'' now just to see what is salvageable.'); 
  end 
else  begin help5('I can''t figure out why you would want to use a tab mark')
 
  ('or \cr or \span just now. If something like a right brace')
 
  ('up above has ended a previous alignment prematurely,')
 
  ('you''re probably due for more error messages, and you')
 
  ('might try typing `S'' now just to see what is salvageable.'); 
  end; 
error; 
end 

MODULE: 'Declare act...'
(*PASCAL module 1129*)
procedure no_align_error; 
begin print_err('Misplaced '); print_esc('noalign'); 
(*Misplaced \\noalign*) 
help2('I expect to see \noalign only after the \cr of')
 
  ('an alignment. Proceed, and I''ll ignore this case.'); error; 
end; 
procedure omit_error; 
begin print_err('Misplaced '); print_esc('omit'); 
(*Misplaced \\omit*) 
help2('I expect to see \omit only after tab marks or the \cr of')
 
  ('an alignment. Proceed, and I''ll ignore this case.'); error; 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1130*)
vmode+halign,hmode+valign:init_align; 
mmode+halign: if privileged then 
  if cur_group=math_shift_group then init_align 
  else off_save; 
vmode+endv,hmode+endv: do_endv; 

MODULE: 'Declare act...'
(*PASCAL module 1131*)
procedure do_endv; 
begin base_ptr:=input_ptr; input_stack[base_ptr]:=cur_input; 
while (input_stack[base_ptr].index_field<>v_template) and 
      (input_stack[base_ptr].loc_field=null) and 
      (input_stack[base_ptr].state_field=token_list) do decr(base_ptr); 
if (input_stack[base_ptr].index_field<>v_template) or 
      (input_stack[base_ptr].loc_field<>null) or 
      (input_stack[base_ptr].state_field<>token_list) then 
  fatal_error('(interwoven alignment preambles are not allowed)'); 
(*interwoven alignment preambles...*) 
 if cur_group=align_group then 
  begin end_graf; 
  if fin_col then fin_row; 
  end 
else off_save; 
end; 

MODULE: 'Cases of |handle_right_brace|...'
(*PASCAL module 1132*)
align_group: begin back_input; cur_tok:=cs_token_flag+frozen_cr; 
  print_err('Missing '); print_esc('cr'); print(' inserted'); 
(*Missing \\cr inserted*) 
  help1('I''m guessing that you meant to end an alignment here.'); 
  ins_error; 
  end; 

MODULE: 'Cases of |handle_right_brace|...'
(*PASCAL module 1133*)
no_align_group: begin end_graf; unsave; align_peek; 
  end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1134*)
any_mode(end_cs_name): cs_error; 

MODULE: 'Declare act...'
(*PASCAL module 1135*)
procedure cs_error; 
begin print_err('Extra '); print_esc('endcsname'); 
(*Extra \\endcsname*) 
help1('I''m ignoring this, since I wasn''t doing a \csname.'); 
error; 
end; 

MODULE: 'Declare act...'
(*PASCAL module 1136*)
procedure push_math(c:group_code); 
begin push_nest; mode:=-mmode; incompleat_noad:=null; new_save_level(c); 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1137*)
hmode+math_shift:init_math; 

MODULE: 'Declare act...'
(*PASCAL module 1138*)
procedure init_math; 
label reswitch,found,not_found,done; 
var w:scaled; {new or partial |pre_display_size|} 
l:scaled; {new |display_width|} 
s:scaled; {new |display_indent|} 
p:pointer; {current node when calculating |pre_display_size|} 
q:pointer; {glue specification when calculating |pre_display_size|} 
f:internal_font_number; {font in current |char_node|} 
n:integer; {scope of paragraph shape specification} 
v:scaled; {|w| plus possible glue amount} 
d:scaled; {increment to |v|} 
begin get_token; {|get_x_token| would fail on \.[\\ifmmode]\thinspace!} 
if (cur_cmd=math_shift)and(mode>0) then 
INSERT: 'Go into display math mode'

else  begin back_input; 
INSERT: 'Go into ordinary math mode'
; 
  end; 
end; 

MODULE: 'Go into ordinary math mode'
(*PASCAL module 1139*)
begin push_math(math_shift_group); eq_word_define(int_base+cur_fam_code,-1); 
if every_math<>null then begin_token_list(every_math,every_math_text); 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1140*)
mmode+eq_no: if privileged then 
  if cur_group=math_shift_group then start_eq_no 
  else off_save; 

MODULE: 'Put each...'
(*PASCAL module 1141*)
primitive('eqno',eq_no,0); 
(*eq_no_][\.{\\eqno} primitive*) 
primitive('leqno',eq_no,1); 
(*leq_no_][\.{\\leqno} primitive*) 

MODULE: 'Declare act...'
(*PASCAL module 1142*)
procedure start_eq_no; 
begin saved(0):=cur_chr; incr(save_ptr); 

INSERT: 'Go into ordinary math mode'
; 
end; 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1143*)
eq_no:if chr_code=1 then print_esc('leqno')else print_esc('eqno'); 

MODULE: 'Go into display math mode'
(*PASCAL module 1145*)
begin if head=tail then {`\.[\\noindent\$\$]' or `\.[\$\$[ ]\$\$]'} 
  begin pop_nest; w:=-max_dimen; 
  end 
else  begin line_break(display_widow_penalty);
 
  
INSERT: 'Calculate the natural width, |w|, by which the characters of the     final line extend to the right of the reference point,     plus two ems; or set |w:=max_dimen| if the non-blank information     on that line is affected by stretching or shrinking'
; 
  end; 
{now we are in vertical mode, working on the list that will contain the display} 

INSERT: 'Calculate the length, |l|, and the shift amount, |s|, of the display lines'
; 
push_math(math_shift_group); mode:=mmode; 
eq_word_define(int_base+cur_fam_code,-1);
 
eq_word_define(dimen_base+pre_display_size_code,w); 
eq_word_define(dimen_base+display_width_code,l); 
eq_word_define(dimen_base+display_indent_code,s); 
if every_display<>null then begin_token_list(every_display,every_display_text); 
if nest_ptr=1 then build_page; 
end 

MODULE: 'Calculate the natural width, |w|, by which...'
(*PASCAL module 1146*)
v:=shift_amount(just_box)+2*quad(cur_font); w:=-max_dimen; 
p:=list_ptr(just_box); 
while p<>null do 
  begin 
INSERT: 'Let |d| be the natural width of node |p|;     if the node is ``visible,'''' |goto found|;     if the node is glue that stretches or shrinks, set |v:=max_dimen|'
; 
  if v<max_dimen then v:=v+d; 
  goto not_found; 
  found: if v<max_dimen then 
    begin v:=v+d; w:=v; 
    end 
  else  begin w:=max_dimen; goto done; 
    end; 
  not_found: p:=link(p); 
  end; 
done: 

MODULE: 'Let |d| be the natural width of node |p|...'
(*PASCAL module 1147*)
reswitch: if is_char_node(p) then 
  begin f:=font(p); d:=char_width(f)(char_info(f)(character(p))); 
  goto found; 
  end; 
case type(p) of 
hlist_node,vlist_node,rule_node: begin d:=width(p); goto found; 
  end; 
ligature_node:
INSERT: 'Make node |p| look like a |char_node|...'
; 
kern_node,math_node: d:=width(p); 
glue_node:
INSERT: 'Let |d| be the natural width of this glue; if stretching   or shrinking, set |v:=max_dimen|; |goto found| in the case of leaders'
; 
whatsit_node: 
INSERT: 'Let |d| be the width of the whatsit |p|'
; 
othercases d:=0 
endcases 

MODULE: 'Let |d| be the natural width of this glue...'
(*PASCAL module 1148*)
begin q:=glue_ptr(p); d:=width(q); 
if glue_sign(just_box)=stretching then 
  begin if (glue_order(just_box)=stretch_order(q))and 
     (stretch(q)<>0) then 
    v:=max_dimen; 
  end 
else if glue_sign(just_box)=shrinking then 
  begin if (glue_order(just_box)=shrink_order(q))and 
     (shrink(q)<>0) then 
    v:=max_dimen; 
  end; 
if subtype(p)>=a_leaders then goto found; 
end 

MODULE: 'Calculate the length, |l|, ...'
(*PASCAL module 1149*)
if par_shape_ptr=null then 
  if (hang_indent<>0)and 
   (((hang_after>=0)and(prev_graf+2>hang_after))or 
    (prev_graf+1<-hang_after)) then 
    begin l:=hsize-abs(hang_indent); 
    if hang_indent>0 then s:=hang_indentelse s:=0; 
    end 
  else  begin l:=hsize; s:=0; 
    end 
else  begin n:=info(par_shape_ptr); 
  if prev_graf+2>=n then p:=par_shape_ptr+2*n 
  else p:=par_shape_ptr+2*(prev_graf+2); 
  s:=mem[p-1].sc; l:=mem[p].sc; 
  end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1150*)
mmode+left_brace: begin tail_append(new_noad); 
  back_input; scan_math(nucleus(tail)); 
  end; 

MODULE: 'Declare act...'
(*PASCAL module 1151*)
procedure scan_math(p:pointer); 
label restart,reswitch,exit; 
var c:integer; {math character code} 
begin restart:
INSERT: 'Get the next non-blank non-relax...'
; 
reswitch:case cur_cmd of 
letter,other_char,char_given: begin c:=ho(math_code(cur_chr)); 
    if c=32768 then 
      begin 
INSERT: 'Treat |cur_chr| as an active character'
; 
      goto restart; 
      end; 
    end; 
char_num: begin scan_char_num; cur_chr:=cur_val; cur_cmd:=char_given; 
  goto reswitch; 
  end; 
math_char_num: begin scan_fifteen_bit_int; c:=cur_val; 
  end; 
math_given: c:=cur_chr; 
delim_num: begin scan_twenty_seven_bit_int; c:=cur_val div 4096; 
  end; 
othercases 
INSERT: 'Scan a subformula enclosed in braces and |return|'

endcases;
 
math_type(p):=math_char; character(p):=qi(c mod 256); 
if (c>=var_code)and fam_in_range then fam(p):=cur_fam 
else fam(p):=(c div 256) mod 16; 
exit:end; 

MODULE: 'Treat |cur_chr|...'
(*PASCAL module 1152*)
begin cur_cs:=cur_chr+active_base; 
cur_cmd:=eq_type(cur_cs); cur_chr:=equiv(cur_cs); 
x_token; back_input; 
end 

MODULE: 'Scan a subformula...'
(*PASCAL module 1153*)
begin back_input; scan_left_brace;
 
saved(0):=p; incr(save_ptr); push_math(math_group); return; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1154*)
mmode+letter,mmode+other_char,mmode+char_given: 
  set_math_char(ho(math_code(cur_chr))); 
mmode+char_num: begin scan_char_num; cur_chr:=cur_val; 
  set_math_char(ho(math_code(cur_chr))); 
  end; 
mmode+math_char_num: begin scan_fifteen_bit_int; set_math_char(cur_val); 
  end; 
mmode+math_given: set_math_char(cur_chr); 
mmode+delim_num: begin scan_twenty_seven_bit_int; 
  set_math_char(cur_val div 4096); 
  end; 

MODULE: 'Declare act...'
(*PASCAL module 1155*)
procedure set_math_char(c:integer); 
var p:pointer; {the new noad} 
begin if c>=32768 then 
  
INSERT: 'Treat |cur_chr|...'

else  begin p:=new_noad; math_type(nucleus(p)):=math_char; 
  character(nucleus(p)):=qi(c mod 256); 
  fam(nucleus(p)):=(c div 256) mod 16; 
  if c>=var_code then 
    begin if fam_in_range then fam(nucleus(p)):=cur_fam; 
    type(p):=ord_noad; 
    end 
  else  type(p):=ord_noad+(c div 4096); 
  link(tail):=p; tail:=p; 
  end; 
end; 

MODULE: 'Put each...'
(*PASCAL module 1156*)
primitive('mathord',math_comp,ord_noad); 
(*math_ord_][\.{\\mathord} primitive*) 
primitive('mathop',math_comp,op_noad); 
(*math_op_][\.{\\mathop} primitive*) 
primitive('mathbin',math_comp,bin_noad); 
(*math_bin_][\.{\\mathbin} primitive*) 
primitive('mathrel',math_comp,rel_noad); 
(*math_rel_][\.{\\mathrel} primitive*) 
primitive('mathopen',math_comp,open_noad); 
(*math_open_][\.{\\mathopen} primitive*) 
primitive('mathclose',math_comp,close_noad); 
(*math_close_][\.{\\mathclose} primitive*) 
primitive('mathpunct',math_comp,punct_noad); 
(*math_punct_][\.{\\mathpunct} primitive*) 
primitive('mathinner',math_comp,inner_noad); 
(*math_inner_][\.{\\mathinner} primitive*) 
primitive('underline',math_comp,under_noad); 
(*underline_][\.{\\underline} primitive*) 
primitive('overline',math_comp,over_noad);
 
(*overline_][\.{\\overline} primitive*) 
primitive('displaylimits',limit_switch,normal); 
(*display_limits_][\.{\\displaylimits} primitive*) 
primitive('limits',limit_switch,limits); 
(*limits_][\.{\\limits} primitive*) 
primitive('nolimits',limit_switch,no_limits); 
(*no_limits_][\.{\\nolimits} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1157*)
math_comp: case chr_code of 
  ord_noad: print_esc('mathord'); 
  op_noad: print_esc('mathop'); 
  bin_noad: print_esc('mathbin'); 
  rel_noad: print_esc('mathrel'); 
  open_noad: print_esc('mathopen'); 
  close_noad: print_esc('mathclose'); 
  punct_noad: print_esc('mathpunct'); 
  inner_noad: print_esc('mathinner'); 
  under_noad: print_esc('underline'); 
  othercases print_esc('overline') 
  endcases; 
limit_switch: if chr_code=limits then print_esc('limits') 
  else if chr_code=no_limits then print_esc('nolimits') 
  else print_esc('displaylimits'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1158*)
mmode+math_comp: begin tail_append(new_noad); 
  type(tail):=cur_chr; scan_math(nucleus(tail)); 
  end; 
mmode+limit_switch: math_limit_switch; 

MODULE: 'Declare act...'
(*PASCAL module 1159*)
procedure math_limit_switch; 
label exit; 
begin if head<>tail then if type(tail)=op_noad then 
  begin subtype(tail):=cur_chr; return; 
  end; 
print_err('Limit controls must follow a math operator'); 
(*Limit controls must follow...*) 
help1('I''m ignoring this misplaced \limits or \nolimits command.'); error; 
exit:end; 

MODULE: 'Declare act...'
(*PASCAL module 1160*)
procedure scan_delimiter(p:pointer;r:boolean); 
begin if r then scan_twenty_seven_bit_int 
else  begin 
INSERT: 'Get the next non-blank non-relax...'
; 
  case cur_cmd of 
  letter,other_char: cur_val:=del_code(cur_chr); 
  delim_num: scan_twenty_seven_bit_int; 
  othercases cur_val:=-1 
  endcases; 
  end; 
if cur_val<0 then 
INSERT: 'Report that an invalid delimiter code is being changed    to null; set~|cur_val:=0|'
; 
small_fam(p):=(cur_val div 1048576) mod 16; 
small_char(p):=qi((cur_val div 4096) mod 256); 
large_fam(p):=(cur_val div 256) mod 16; 
large_char(p):=qi(cur_val mod 256); 
end; 

MODULE: 'Report that an invalid delimiter...'
(*PASCAL module 1161*)
begin print_err('Missing delimiter (. inserted)'); 
(*Missing delimiter...*) 
help6('I was expecting to see something like `('' or `\{'' or')
 
  ('`\}'' here. If you typed, e.g., `{'' instead of `\{'', you')
 
  ('should probably delete the `{'' by typing `1'' now, so that')
 
  ('braces don''t get unbalanced. Otherwise just proceed.')
 
  ('Acceptable delimiters are characters whose \delcode is')
 
  ('nonnegative, or you can use `\delimiter <delimiter code>''.'); 
back_error; cur_val:=0; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1162*)
mmode+radical:math_radical; 

MODULE: 'Declare act...'
(*PASCAL module 1163*)
procedure math_radical; 
begin tail_append(get_node(radical_noad_size)); 
type(tail):=radical_noad; subtype(tail):=normal; 
mem[nucleus(tail)].hh:=empty_field; 
mem[subscr(tail)].hh:=empty_field; 
mem[supscr(tail)].hh:=empty_field; 
scan_delimiter(left_delimiter(tail),true); scan_math(nucleus(tail)); 
end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1164*)
mmode+accent,mmode+math_accent:math_ac; 

MODULE: 'Declare act...'
(*PASCAL module 1165*)
procedure math_ac; 
begin if cur_cmd=accent then 
  
INSERT: 'Complain that the user should have said \.{\\mathaccent}'
; 
tail_append(get_node(accent_noad_size)); 
type(tail):=accent_noad; subtype(tail):=normal; 
mem[nucleus(tail)].hh:=empty_field; 
mem[subscr(tail)].hh:=empty_field; 
mem[supscr(tail)].hh:=empty_field; 
math_type(accent_chr(tail)):=math_char; 
scan_fifteen_bit_int; 
character(accent_chr(tail)):=qi(cur_val mod 256); 
if (cur_val>=var_code)and fam_in_range then fam(accent_chr(tail)):=cur_fam 
else fam(accent_chr(tail)):=(cur_val div 256) mod 16; 
scan_math(nucleus(tail)); 
end; 

MODULE: 'Complain that the user should have said \.{\\mathaccent}'
(*PASCAL module 1166*)
begin print_err('Please use '); print_esc('mathaccent'); 
print(' for accents in math mode'); 
(*Please use \\mathaccent...*) 
help2('I''m changing \accent to \mathaccent here; wish me luck.')
 
  ('(Accents are not the same in formulas as they are in text.)'); 
error; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1167*)
mmode+vcenter: begin scan_spec(vcenter_group,false); normal_paragraph; 
  push_nest; mode:=-vmode; prev_depth:=ignore_depth; 
  if every_vbox<>null then begin_token_list(every_vbox,every_vbox_text); 
  end; 

MODULE: 'Cases of |handle...'
(*PASCAL module 1168*)
vcenter_group: begin end_graf; unsave; save_ptr:=save_ptr-2; 
  p:=vpack(link(head),saved(1),saved(0)); pop_nest; 
  tail_append(new_noad); type(tail):=vcenter_noad; 
  math_type(nucleus(tail)):=sub_box; info(nucleus(tail)):=p; 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1169*)
primitive('displaystyle',math_style,display_style); 
(*display_style_][\.{\\displaystyle} primitive*) 
primitive('textstyle',math_style,text_style); 
(*text_style_][\.{\\textstyle} primitive*) 
primitive('scriptstyle',math_style,script_style); 
(*script_style_][\.{\\scriptstyle} primitive*) 
primitive('scriptscriptstyle',math_style,script_script_style); 
(*script_script_style_][\.{\\scriptscriptstyle} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1170*)
math_style: print_style(chr_code); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1171*)
mmode+math_style: tail_append(new_style(cur_chr)); 
mmode+non_script: begin tail_append(new_glue(zero_glue)); 
  subtype(tail):=cond_math_glue; 
  end; 
mmode+math_choice: append_choices; 

MODULE: 'Declare act...'
(*PASCAL module 1172*)
procedure append_choices; 
begin tail_append(new_choice); incr(save_ptr); saved(-1):=0; 
push_math(math_choice_group); scan_left_brace; 
end; 

MODULE: 'Cases of |handle_right_brace|...'
(*PASCAL module 1173*)
math_choice_group: build_choices; 

MODULE: 'Declare act...'
(*PASCAL module 1174*)
(*\4*)
INSERT: 'Declare the function called |fin_mlist|'
(*@>;
*)(*@>;
*) 
procedure build_choices; 
label exit; 
var p:pointer; {the current mlist} 
begin unsave; p:=fin_mlist(null); 
case saved(-1) of 
0:display_mlist(tail):=p; 
1:text_mlist(tail):=p; 
2:script_mlist(tail):=p; 
3:begin script_script_mlist(tail):=p; decr(save_ptr); return; 
  end; 
end; {there are no other cases} 
incr(saved(-1)); push_math(math_choice_group); scan_left_brace; 
exit:end; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1175*)
mmode+sub_mark,mmode+sup_mark: sub_sup; 

MODULE: 'Declare act...'
(*PASCAL module 1176*)
procedure sub_sup; 
var t:small_number; {type of previous sub/superscript} 
p:pointer; {field to be filled by |scan_math|} 
begin t:=empty; p:=null; 
if tail<>head then if scripts_allowed(tail) then 
  begin p:=supscr(tail)+cur_cmd-sup_mark; {|supscr| or |subscr|} 
  t:=math_type(p); 
  end; 
if (p=null)or(t<>empty) then 
INSERT: 'Insert a dummy noad to be sub/superscripted'
; 
scan_math(p); 
end; 

MODULE: 'Insert a dummy...'
(*PASCAL module 1177*)
begin tail_append(new_noad); 
p:=supscr(tail)+cur_cmd-sup_mark; {|supscr| or |subscr|} 
if t<>empty then 
  begin if cur_cmd=sup_mark then 
    begin print_err('Double superscript'); 
(*Double superscript*) 
    help1('I treat `x^1^2'' essentially like `x^1{}^2''.'); 
    end 
  else  begin print_err('Double subscript'); 
(*Double subscript*) 
    help1('I treat `x_1_2'' essentially like `x_1{}_2''.'); 
    end; 
  error; 
  end; 
end 

MODULE: 'Put each...'
(*PASCAL module 1178*)
primitive('above',above,above_code);
 
(*above_][\.{\\above} primitive*) 
primitive('over',above,over_code);
 
(*over_][\.{\\over} primitive*) 
primitive('atop',above,atop_code);
 
(*atop_][\.{\\atop} primitive*) 
primitive('abovewithdelims',above,delimited_code+above_code);
 
(*above_with_delims_][\.{\\abovewithdelims} primitive*) 
primitive('overwithdelims',above,delimited_code+over_code);
 
(*over_with_delims_][\.{\\overwithdelims} primitive*) 
primitive('atopwithdelims',above,delimited_code+atop_code); 
(*atop_with_delims_][\.{\\atopwithdelims} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1179*)
above: case chr_code of 
  over_code:print_esc('over'); 
  atop_code:print_esc('atop'); 
  delimited_code+above_code:print_esc('abovewithdelims'); 
  delimited_code+over_code:print_esc('overwithdelims'); 
  delimited_code+atop_code:print_esc('atopwithdelims'); 
  othercases print_esc('above') 
  endcases; 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1180*)
mmode+above: math_fraction; 

MODULE: 'Declare act...'
(*PASCAL module 1181*)
procedure math_fraction; 
var c:small_number; {the type of generalized fraction we are scanning} 
begin c:=cur_chr; 
if incompleat_noad<>null then 
  
INSERT: 'Ignore the fraction operation and complain about this ambiguous case'

else  begin incompleat_noad:=get_node(fraction_noad_size); 
  type(incompleat_noad):=fraction_noad; 
  subtype(incompleat_noad):=normal; 
  math_type(numerator(incompleat_noad)):=sub_mlist; 
  info(numerator(incompleat_noad)):=link(head); 
  mem[denominator(incompleat_noad)].hh:=empty_field; 
  mem[left_delimiter(incompleat_noad)].qqqq:=null_delimiter; 
  mem[right_delimiter(incompleat_noad)].qqqq:=null_delimiter;
 
  link(head):=null; tail:=head; 
  
INSERT: 'Use code |c| to distinguish between generalized fractions'
; 
  end; 
end; 

MODULE: 'Use code |c|...'
(*PASCAL module 1182*)
if c>=delimited_code then 
  begin scan_delimiter(left_delimiter(incompleat_noad),false); 
  scan_delimiter(right_delimiter(incompleat_noad),false); 
  end; 
case c mod delimited_code of 
above_code: begin scan_normal_dimen; 
  thickness(incompleat_noad):=cur_val; 
  end; 
over_code: thickness(incompleat_noad):=default_code; 
atop_code: thickness(incompleat_noad):=0; 
end {there are no other cases} 

MODULE: 'Ignore the fraction...'
(*PASCAL module 1183*)
begin if c>=delimited_code then 
  begin scan_delimiter(garbage,false); scan_delimiter(garbage,false); 
  end; 
if c mod delimited_code=above_code then scan_normal_dimen; 
print_err('Ambiguous; you need another { and }'); 
(*Ambiguous...*) 
help3('I''m ignoring this fraction specification, since I don''t')
 
  ('know whether a construction like `x \over y \over z''')
 
  ('means `{x \over y} \over z'' or `x \over {y \over z}''.'); 
error; 
end 

MODULE: 'Declare the function called |fin_mlist|'
(*PASCAL module 1184*)
function fin_mlist(p:pointer):pointer; 
var q:pointer; {the mlist to return} 
begin if incompleat_noad<>null then 
INSERT: 'Compleat the incompleat noad'

else  begin link(tail):=p; q:=link(head); 
  end; 
pop_nest; fin_mlist:=q; 
end; 

MODULE: 'Compleat... '
(*PASCAL module 1185*)
begin math_type(denominator(incompleat_noad)):=sub_mlist; 
info(denominator(incompleat_noad)):=link(head); 
if p=null then q:=incompleat_noad 
else  begin q:=info(numerator(incompleat_noad)); 
  if type(q)<>left_noad then confusion('right'); 
(*this can''t happen right][\quad right*) 
  info(numerator(incompleat_noad)):=link(q); 
  link(q):=incompleat_noad; link(incompleat_noad):=p; 
  end; 
end 

MODULE: 'Cases of |handle...'
(*PASCAL module 1186*)
math_group: begin unsave; decr(save_ptr);
 
  math_type(saved(0)):=sub_mlist; p:=fin_mlist(null); info(saved(0)):=p; 
  if p<>null then if link(p)=null then 
   if type(p)=ord_noad then 
    begin if math_type(subscr(p))=empty then 
     if math_type(supscr(p))=empty then 
      begin mem[saved(0)].hh:=mem[nucleus(p)].hh; 
      free_node(p,noad_size); 
      end; 
    end 
  else if type(p)=accent_noad then if saved(0)=nucleus(tail) then 
   if type(tail)=ord_noad then 
INSERT: 'Replace the tail of the list by |p|'
; 
  end; 

MODULE: 'Replace the tail...'
(*PASCAL module 1187*)
begin q:=head; while link(q)<>tail do q:=link(q); 
link(q):=p; free_node(tail,noad_size); tail:=p; 
end 

MODULE: 'Put each...'
(*PASCAL module 1188*)
primitive('left',left_right,left_noad); 
(*left_][\.{\\left} primitive*) 
primitive('right',left_right,right_noad); 
(*right_][\.{\\right} primitive*) 
text(frozen_right):='right'; eqtb[frozen_right]:=eqtb[cur_val]; 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1189*)
left_right: if chr_code=left_noad then print_esc('left') 
else print_esc('right'); 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1190*)
mmode+left_right: math_left_right; 

MODULE: 'Declare act...'
(*PASCAL module 1191*)
procedure math_left_right; 
var t:small_number; {|left_noad| or |right_noad|} 
p:pointer; {new noad} 
begin t:=cur_chr; 
if (t=right_noad)and(cur_group<>math_left_group) then 
  
INSERT: 'Try to recover from mismatched \.{\\right}'

else  begin p:=new_noad; type(p):=t; 
  scan_delimiter(delimiter(p),false); 
  if t=left_noad then 
    begin push_math(math_left_group); link(head):=p; tail:=p; 
    end 
  else  begin p:=fin_mlist(p); unsave; {end of |math_left_group|} 
    tail_append(new_noad); type(tail):=inner_noad; 
    math_type(nucleus(tail)):=sub_mlist; 
    info(nucleus(tail)):=p; 
    end; 
  end; 
end; 

MODULE: 'Try to recover from mismatch...'
(*PASCAL module 1192*)
begin if cur_group=math_shift_group then 
  begin scan_delimiter(garbage,false); 
  print_err('Extra '); print_esc('right'); 
(*Extra \\right.*) 
  help1('I''m ignoring a \right that had no matching \left.'); 
  error; 
  end 
else off_save; 
end 

MODULE: 'Cases of |main_control| that build...'
(*PASCAL module 1193*)
mmode+math_shift: if cur_group=math_shift_group then after_math 
  else off_save; 

MODULE: 'Declare act...'
(*PASCAL module 1194*)
procedure after_math; 
var l:boolean; {`\.[\\leqno]' instead of `\.[\\eqno]'} 
danger:boolean; {not enough symbol fonts are present} 
m:integer; {|mmode| or |-mmode|} 
p:pointer; {the formula} 
a:pointer; {box containing equation number} 

INSERT: 'Local variables for finishing a displayed formula'
; 
begin danger:=false; 

INSERT: 'Check that the necessary fonts for math symbols are present;   if not, flush the current math lists and set |danger:=true|'
; 
m:=mode; l:=false; p:=fin_mlist(null); {this pops the nest} 
if mode=-m then {end of equation number} 
  begin 
INSERT: 'Check that another \.\$ follows'
; 
  cur_mlist:=p; cur_style:=text_style; mlist_penalties:=false; 
  mlist_to_hlist; a:=hpack(link(temp_head),natural); 
  unsave; decr(save_ptr); {now |cur_group=math_shift_group|} 
  if saved(0)=1 then l:=true; 
  danger:=false; 
  
INSERT: 'Check that the necessary fonts for math symbols are present;     if not, flush the current math lists and set |danger:=true|'
; 
  m:=mode; p:=fin_mlist(null); 
  end 
else a:=null; 
if m<0 then 
INSERT: 'Finish math in text'

else  begin if a=null then 
INSERT: 'Check that another \.\$ follows'
; 
  
INSERT: 'Finish displayed math'
; 
  end; 
end; 

MODULE: 'Check that the necessary fonts...'
(*PASCAL module 1195*)
if (font_params[fam_fnt(2+text_size)]<total_mathsy_params)or 
   (font_params[fam_fnt(2+script_size)]<total_mathsy_params)or 
   (font_params[fam_fnt(2+script_script_size)]<total_mathsy_params) then 
  begin print_err('Math formula deleted: Insufficient symbol fonts');
 
(*Math formula deleted...*) 
  help3('Sorry, but I can''t typeset math unless \textfont 2')
 
    ('and \scriptfont 2 and \scriptscriptfont 2 have all')
 
    ('the \fontdimen values needed in math symbol fonts.'); 
  error; flush_math; danger:=true; 
  end 
else if (font_params[fam_fnt(3+text_size)]<total_mathex_params)or 
   (font_params[fam_fnt(3+script_size)]<total_mathex_params)or 
   (font_params[fam_fnt(3+script_script_size)]<total_mathex_params) then 
  begin print_err('Math formula deleted: Insufficient extension fonts');
 
  help3('Sorry, but I can''t typeset math unless \textfont 3')
 
    ('and \scriptfont 3 and \scriptscriptfont 3 have all')
 
    ('the \fontdimen values needed in math extension fonts.'); 
  error; flush_math; danger:=true; 
  end 

MODULE: 'Finish math in text'
(*PASCAL module 1196*)
begin tail_append(new_math(math_surround,before)); 
cur_mlist:=p; cur_style:=text_style; mlist_penalties:=(mode>0); mlist_to_hlist; 
link(tail):=link(temp_head); 
while link(tail)<>null do tail:=link(tail); 
tail_append(new_math(math_surround,after)); 
space_factor:=1000; unsave; 
end 

MODULE: 'Check that another \.\$ follows'
(*PASCAL module 1197*)
begin get_x_token; 
if cur_cmd<>math_shift then 
  begin print_err('Display math should end with $$'); 
(*Display math...with \$\$*) 
  help2('The `$'' that I just saw supposedly matches a previous `$$''.')
 
    ('So I shall assume that you typed `$$'' both times.'); 
  back_error; 
  end; 
end 

MODULE: 'Local variables for finishing...'
(*PASCAL module 1198*)
b:pointer; {box containing the equation} 
w:scaled; {width of the equation} 
z:scaled; {width of the line} 
e:scaled; {width of equation number} 
q:scaled; {width of equation number plus space to separate from equation} 
d:scaled; {displacement of equation in the line} 
s:scaled; {move the line right this much} 
g1,g2:small_number; {glue parameter codes for before and after} 
r:pointer; {kern node used to position the display} 
t:pointer; {tail of adjustment list} 

MODULE: 'Finish displayed math'
(*PASCAL module 1199*)
cur_mlist:=p; cur_style:=display_style; mlist_penalties:=false; 
mlist_to_hlist; p:=link(temp_head);
 
adjust_tail:=adjust_head; b:=hpack(p,natural); p:=list_ptr(b); 
t:=adjust_tail; adjust_tail:=null;
 
w:=width(b); z:=display_width; s:=display_indent; 
if (a=null)or danger then 
  begin e:=0; q:=0; 
  end 
else  begin e:=width(a); q:=e+math_quad(text_size); 
  end; 
if w+q>z then 
  
INSERT: 'Squeeze the equation as much as possible; if there is an equation     number that should go on a separate line by itself,     set~|e:=0|'
; 

INSERT: 'Determine the displacement, |d|, of the left edge of the equation, with   respect to the line size |z|, assuming that |l=false|'
; 

INSERT: 'Append the glue or equation number preceding the display'
; 

INSERT: 'Append the display and perhaps also the equation number'
; 

INSERT: 'Append the glue or equation number following the display'
; 
resume_after_display 

MODULE: 'Declare act...'
(*PASCAL module 1200*)
procedure resume_after_display; 
begin if cur_group<>math_shift_group then confusion('display'); 
(*this can''t happen display][\quad display*) 
unsave; prev_graf:=prev_graf+3; 
push_nest; mode:=hmode; space_factor:=1000; set_cur_lang; clang:=cur_lang; 
prev_graf:=(norm_min(left_hyphen_min)*64+norm_min(right_hyphen_min)) 
             *65536+cur_lang; 

INSERT: 'Scan an optional space'
; 
if nest_ptr=1 then build_page; 
end; 

MODULE: 'Squeeze the equation as much as possible...'
(*PASCAL module 1201*)
begin if (e<>0)and((w-total_shrink[normal]+q<=z)or 
   (total_shrink[fil]<>0)or(total_shrink[fill]<>0)or 
   (total_shrink[filll]<>0)) then 
  begin free_node(b,box_node_size); 
  b:=hpack(p,z-q,exactly); 
  end 
else  begin e:=0; 
  if w>z then 
    begin free_node(b,box_node_size); 
    b:=hpack(p,z,exactly); 
    end; 
  end; 
w:=width(b); 
end 

MODULE: 'Determine the displacement, |d|, of the left edge of the equation...'
(*PASCAL module 1202*)
d:=half(z-w); 
if (e>0)and(d<2*e) then {too close} 
  begin d:=half(z-w-e); 
  if p<>null then if not is_char_node(p) then if type(p)=glue_node then d:=0; 
  end 

MODULE: 'Append the glue or equation number preceding the display'
(*PASCAL module 1203*)
tail_append(new_penalty(pre_display_penalty));
 
if (d+s<=pre_display_size)or l then {not enough clearance} 
  begin g1:=above_display_skip_code; g2:=below_display_skip_code; 
  end 
else  begin g1:=above_display_short_skip_code; 
  g2:=below_display_short_skip_code; 
  end; 
if l and(e=0) then {it follows that |type(a)=hlist_node|} 
  begin shift_amount(a):=s; append_to_vlist(a); 
  tail_append(new_penalty(inf_penalty)); 
  end 
else tail_append(new_param_glue(g1)) 

MODULE: 'Append the display and perhaps also the equation number'
(*PASCAL module 1204*)
if e<>0 then 
  begin r:=new_kern(z-w-e-d); 
  if l then 
    begin link(a):=r; link(r):=b; b:=a; d:=0; 
    end 
  else  begin link(b):=r; link(r):=a; 
    end; 
  b:=hpack(b,natural); 
  end; 
shift_amount(b):=s+d; append_to_vlist(b) 

MODULE: 'Append the glue or equation number following the display'
(*PASCAL module 1205*)
if (a<>null)and(e=0)and not l then 
  begin tail_append(new_penalty(inf_penalty)); 
  shift_amount(a):=s+z-width(a); 
  append_to_vlist(a); 
  g2:=0; 
  end; 
if t<>adjust_head then {migrating material comes after equation number} 
  begin link(tail):=link(adjust_head); tail:=t; 
  end; 
tail_append(new_penalty(post_display_penalty)); 
if g2>0 then tail_append(new_param_glue(g2)) 

MODULE: 'Finish an alignment in a display'
(*PASCAL module 1206*)
begin do_assignments; 
if cur_cmd<>math_shift then 
INSERT: 'Pontificate about improper alignment in display'

else 
INSERT: 'Check that another \.\$ follows'
; 
pop_nest; 
tail_append(new_penalty(pre_display_penalty)); 
tail_append(new_param_glue(above_display_skip_code)); 
link(tail):=p; 
if p<>null then tail:=q; 
tail_append(new_penalty(post_display_penalty)); 
tail_append(new_param_glue(below_display_skip_code)); 
prev_depth:=aux_save.sc; resume_after_display; 
end 

MODULE: 'Pontificate... '
(*PASCAL module 1207*)
begin print_err('Missing $$ inserted'); 
(*Missing {\$\$} inserted*) 
help2('Displays can use special alignments (like \eqalignno)')
 
  ('only if nothing but the alignment itself is between $$''s.'); 
back_error; 
end 

MODULE: 'Put each...'
(*PASCAL module 1208*)
primitive('long',prefix,1); 
(*long_][\.{\\long} primitive*) 
primitive('outer',prefix,2); 
(*outer_][\.{\\outer} primitive*) 
primitive('global',prefix,4); 
(*global_][\.{\\global} primitive*) 
primitive('def',def,0); 
(*def_][\.{\\def} primitive*) 
primitive('gdef',def,1); 
(*gdef_][\.{\\gdef} primitive*) 
primitive('edef',def,2); 
(*edef_][\.{\\edef} primitive*) 
primitive('xdef',def,3); 
(*xdef_][\.{\\xdef} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1209*)
prefix: if chr_code=1 then print_esc('long') 
  else if chr_code=2 then print_esc('outer') 
  else print_esc('global'); 
def: if chr_code=0 then print_esc('def') 
  else if chr_code=1 then print_esc('gdef') 
  else if chr_code=2 then print_esc('edef') 
  else print_esc('xdef'); 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1210*)
any_mode(toks_register), 
any_mode(assign_toks), 
any_mode(assign_int), 
any_mode(assign_dimen), 
any_mode(assign_glue), 
any_mode(assign_mu_glue), 
any_mode(assign_font_dimen), 
any_mode(assign_font_int), 
any_mode(set_aux), 
any_mode(set_prev_graf), 
any_mode(set_page_dimen), 
any_mode(set_page_int), 
any_mode(set_box_dimen), 
any_mode(set_shape), 
any_mode(def_code), 
any_mode(def_family), 
any_mode(set_font), 
any_mode(def_font), 
any_mode(register), 
any_mode(advance), 
any_mode(multiply), 
any_mode(divide), 
any_mode(prefix), 
any_mode(let), 
any_mode(shorthand_def), 
any_mode(read_to_cs), 
any_mode(def), 
any_mode(set_box), 
any_mode(hyph_data), 
any_mode(set_interaction):prefixed_command; 

MODULE: 'Declare act...'
(*PASCAL module 1211*)
(*\4*)
INSERT: 'Declare subprocedures for |prefixed_command|'
(*@>;
*)(*@>;
*) 
procedure prefixed_command; 
label done,exit; 
var a:small_number; {accumulated prefix codes so far} 
f:internal_font_number; {identifies a font} 
j:halfword; {index into a \.[\\parshape] specification} 
k:font_index; {index into |font_info|} 
p,q:pointer; {for temporary short-term use} 
n:integer; {ditto} 
e:boolean; {should a definition be expanded? or was \.[\\let] not done?} 
begin a:=0; 
while cur_cmd=prefix do 
  begin if not odd(a div cur_chr) then a:=a+cur_chr; 
  
INSERT: 'Get the next non-blank non-relax...'
; 
  if cur_cmd<=max_non_prefixed_command then 
    
INSERT: 'Discard erroneous prefixes and |return|'
; 
  end; 

INSERT: 'Discard the prefixes \.{\\long} and \.{\\outer} if they are irrelevant'
; 

INSERT: 'Adjust \(f)for the setting of \.{\\globaldefs}'
; 
case cur_cmd of 
(*\4*)
INSERT: 'Assignments '
; 
othercases confusion('prefix') 
(*this can''t happen prefix][\quad prefix*) 
endcases; 
done: 
INSERT: 'Insert a token saved by \.{\\afterassignment}, if any'
; 
exit:end; 

MODULE: 'Discard erroneous...'
(*PASCAL module 1212*)
begin print_err('You can''t use a prefix with `'); 
(*You can''t use a prefix with x*) 
print_cmd_chr(cur_cmd,cur_chr); print_char(''''); 
help1('I''ll pretend you didn''t say \long or \outer or \global.'); 
back_error; return; 
end 

MODULE: 'Discard the prefixes...'
(*PASCAL module 1213*)
if (cur_cmd<>def)and(a mod 4<>0) then 
  begin print_err('You can''t use `'); print_esc('long'); print(''' or `'); 
  print_esc('outer'); print(''' with `'); 
(*You can''t use \\long...*) 
  print_cmd_chr(cur_cmd,cur_chr); print_char(''''); 
  help1('I''ll pretend you didn''t say \long or \outer here.'); 
  error; 
  end 

MODULE: 'Adjust \(f)for the setting of \.{\\globaldefs}'
(*PASCAL module 1214*)
if global_defs<>0 then 
  if global_defs<0 then 
    begin if global then a:=a-4; 
    end 
  else  begin if not global then a:=a+4; 
    end 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1215*)
procedure get_r_token; 
label restart; 
begin restart: repeat get_token; 
until cur_tok<>space_token; 
if (cur_cs=0)or(cur_cs>frozen_control_sequence) then 
  begin print_err('Missing control sequence inserted'); 
(*Missing control...*) 
  help5('Please don''t say `\def cs{...}'', say `\def\cs{...}''.')
 
  ('I''ve inserted an inaccessible control sequence so that your')
 
  ('definition will be completed without mixing me up too badly.')
 
  ('You can recover graciously from this error, if you''re')
 
  ('careful; see exercise 27.2 in The TeXbook.'); 
(*TeXbook][\sl The \TeX book*) 
  if cur_cs=0 then back_input; 
  cur_tok:=cs_token_flag+frozen_protection; ins_error; goto restart; 
  end; 
end; 

MODULE: 'Initialize table entries...'
(*PASCAL module 1216*)
text(frozen_protection):='inaccessible'; 

MODULE: 'Assignments '
(*PASCAL module 1217*)
set_font: define(cur_font_loc,data,cur_chr); 

MODULE: 'Assignments '
(*PASCAL module 1218*)
def: begin if odd(cur_chr)and not global and(global_defs>=0) then a:=a+4; 
  e:=(cur_chr>=2); get_r_token; p:=cur_cs; 
  q:=scan_toks(true,e); define(p,call+(a mod 4),def_ref); 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1219*)
primitive('let',let,normal);
 
(*let_][\.{\\let} primitive*) 
primitive('futurelet',let,normal+1);
 
(*future_let_][\.{\\futurelet} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1220*)
let: if chr_code<>normal then print_esc('futurelet')else print_esc('let'); 

MODULE: 'Assignments '
(*PASCAL module 1221*)
let:  begin n:=cur_chr; 
  get_r_token; p:=cur_cs; 
  if n=normal then 
    begin repeat get_token; 
    until cur_cmd<>spacer; 
    if cur_tok=other_token+'=' then 
      begin get_token; 
      if cur_cmd=spacer then get_token; 
      end; 
    end 
  else  begin get_token; q:=cur_tok; get_token; back_input; 
    cur_tok:=q; back_input; {look ahead, then back up} 
    end; {note that |back_input| doesn't affect |cur_cmd|, |cur_chr|} 
  if cur_cmd>=call then add_token_ref(cur_chr); 
  define(p,cur_cmd,cur_chr); 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1222*)
primitive('chardef',shorthand_def,char_def_code);
 
(*char_def_][\.{\\chardef} primitive*) 
primitive('mathchardef',shorthand_def,math_char_def_code);
 
(*math_char_def_][\.{\\mathchardef} primitive*) 
primitive('countdef',shorthand_def,count_def_code);
 
(*count_def_][\.{\\countdef} primitive*) 
primitive('dimendef',shorthand_def,dimen_def_code);
 
(*dimen_def_][\.{\\dimendef} primitive*) 
primitive('skipdef',shorthand_def,skip_def_code);
 
(*skip_def_][\.{\\skipdef} primitive*) 
primitive('muskipdef',shorthand_def,mu_skip_def_code);
 
(*mu_skip_def_][\.{\\muskipdef} primitive*) 
primitive('toksdef',shorthand_def,toks_def_code);
 
(*toks_def_][\.{\\toksdef} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1223*)
shorthand_def: case chr_code of 
  char_def_code: print_esc('chardef'); 
  math_char_def_code: print_esc('mathchardef'); 
  count_def_code: print_esc('countdef'); 
  dimen_def_code: print_esc('dimendef'); 
  skip_def_code: print_esc('skipdef'); 
  mu_skip_def_code: print_esc('muskipdef'); 
  othercases print_esc('toksdef') 
  endcases; 
char_given: begin print_esc('char'); print_hex(chr_code); 
  end; 
math_given: begin print_esc('mathchar'); print_hex(chr_code); 
  end; 

MODULE: 'Assignments '
(*PASCAL module 1224*)
shorthand_def: begin n:=cur_chr; get_r_token; p:=cur_cs; define(p,relax,256); 
  scan_optional_equals; 
  case n of 
  char_def_code: begin scan_char_num; define(p,char_given,cur_val); 
    end; 
  math_char_def_code: begin scan_fifteen_bit_int; define(p,math_given,cur_val); 
    end; 
  othercases begin scan_eight_bit_int; 
    case n of 
    count_def_code: define(p,assign_int,count_base+cur_val); 
    dimen_def_code: define(p,assign_dimen,scaled_base+cur_val); 
    skip_def_code: define(p,assign_glue,skip_base+cur_val); 
    mu_skip_def_code: define(p,assign_mu_glue,mu_skip_base+cur_val); 
    toks_def_code: define(p,assign_toks,toks_base+cur_val); 
    end; {there are no other cases} 
    end 
  endcases; 
  end; 

MODULE: 'Assignments '
(*PASCAL module 1225*)
read_to_cs: begin scan_int; n:=cur_val; 
  if not scan_keyword('to') then 
(*to*) 
    begin print_err('Missing `to'' inserted'); 
(*Missing `to''...*) 
    help2('You should have said `\read<number> to \cs''.')
 
    ('I''m going to look for the \cs now.'); error; 
    end; 
  get_r_token; 
  p:=cur_cs; read_toks(n,p); define(p,call,cur_val); 
  end; 

MODULE: 'Assignments '
(*PASCAL module 1226*)
toks_register,assign_toks: begin q:=cur_cs; 
  if cur_cmd=toks_register then 
    begin scan_eight_bit_int; p:=toks_base+cur_val; 
    end 
  else p:=cur_chr; {|p=every_par_loc| or |output_routine_loc| or \dots} 
  scan_optional_equals; 
  
INSERT: 'Get the next non-blank non-relax non-call token'
; 
  if cur_cmd<>left_brace then 
INSERT: 'If the right-hand side is a token parameter       or token register, finish the assignment and |goto done|'
; 
  back_input; cur_cs:=q; q:=scan_toks(false,false); 
  if link(def_ref)=null then {empty list: revert to the default} 
    begin define(p,undefined_cs,null); free_avail(def_ref); 
    end 
  else  begin if p=output_routine_loc then {enclose in curlies} 
      begin link(q):=get_avail; q:=link(q); 
      info(q):=right_brace_token+'}'; 
      q:=get_avail; info(q):=left_brace_token+'{'; 
      link(q):=link(def_ref); link(def_ref):=q; 
      end; 
    define(p,call,def_ref); 
    end; 
  end; 

MODULE: 'If the right-hand side is a token parameter...'
(*PASCAL module 1227*)
begin if cur_cmd=toks_register then 
  begin scan_eight_bit_int; cur_cmd:=assign_toks; cur_chr:=toks_base+cur_val; 
  end; 
if cur_cmd=assign_toks then 
  begin q:=equiv(cur_chr); 
  if q=null then define(p,undefined_cs,null) 
  else  begin add_token_ref(q); define(p,call,q); 
    end; 
  goto done; 
  end; 
end 

MODULE: 'Assignments '
(*PASCAL module 1228*)
assign_int: begin p:=cur_chr; scan_optional_equals; scan_int; 
  word_define(p,cur_val); 
  end; 
assign_dimen: begin p:=cur_chr; scan_optional_equals; 
  scan_normal_dimen; word_define(p,cur_val); 
  end; 
assign_glue,assign_mu_glue: begin p:=cur_chr; n:=cur_cmd; scan_optional_equals; 
  if n=assign_mu_glue then scan_glue(mu_val)else scan_glue(glue_val); 
  trap_zero_glue; 
  define(p,glue_ref,cur_val); 
  end; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1229*)
procedure trap_zero_glue; 
begin if (width(cur_val)=0)and(stretch(cur_val)=0)and(shrink(cur_val)=0) then 
  begin add_glue_ref(zero_glue); 
  delete_glue_ref(cur_val); cur_val:=zero_glue; 
  end; 
end; 

MODULE: 'Put each...'
(*PASCAL module 1230*)
primitive('catcode',def_code,cat_code_base); 
(*cat_code_][\.{\\catcode} primitive*) 
primitive('mathcode',def_code,math_code_base); 
(*math_code_][\.{\\mathcode} primitive*) 
primitive('lccode',def_code,lc_code_base); 
(*lc_code_][\.{\\lccode} primitive*) 
primitive('uccode',def_code,uc_code_base); 
(*uc_code_][\.{\\uccode} primitive*) 
primitive('sfcode',def_code,sf_code_base); 
(*sf_code_][\.{\\sfcode} primitive*) 
primitive('delcode',def_code,del_code_base); 
(*del_code_][\.{\\delcode} primitive*) 
primitive('textfont',def_family,math_font_base); 
(*text_font_][\.{\\textfont} primitive*) 
primitive('scriptfont',def_family,math_font_base+script_size); 
(*script_font_][\.{\\scriptfont} primitive*) 
primitive('scriptscriptfont',def_family,math_font_base+script_script_size); 
(*script_script_font_][\.{\\scriptscriptfont} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1231*)
def_code: if chr_code=cat_code_base then print_esc('catcode') 
  else if chr_code=math_code_base then print_esc('mathcode') 
  else if chr_code=lc_code_base then print_esc('lccode') 
  else if chr_code=uc_code_base then print_esc('uccode') 
  else if chr_code=sf_code_base then print_esc('sfcode') 
  else print_esc('delcode'); 
def_family: print_size(chr_code-math_font_base); 

MODULE: 'Assignments '
(*PASCAL module 1232*)
def_code: begin 
INSERT: 'Let |n| be the largest legal code value, based on |cur_chr|'
; 
  p:=cur_chr; scan_char_num; p:=p+cur_val; scan_optional_equals; 
  scan_int; 
  if ((cur_val<0)and(p<del_code_base))or(cur_val>n) then 
    begin print_err('Invalid code ('); print_int(cur_val); 
(*Invalid code*) 
    if p<del_code_base then print('), should be in the range 0..') 
    else print('), should be at most '); 
    print_int(n); 
    help1('I''m going to use 0 instead of that illegal code value.');
 
    error; cur_val:=0; 
    end; 
  if p<math_code_base then define(p,data,cur_val) 
  else if p<del_code_base then define(p,data,hi(cur_val)) 
  else word_define(p,cur_val); 
  end; 

MODULE: 'Let |n| be the largest...'
(*PASCAL module 1233*)
if cur_chr=cat_code_base then n:=max_char_code 
else if cur_chr=math_code_base then n:=32768 
else if cur_chr=sf_code_base then n:=32767 
else if cur_chr=del_code_base then n:=16777215 
else n:=255 

MODULE: 'Assignments '
(*PASCAL module 1234*)
def_family: begin p:=cur_chr; scan_four_bit_int; p:=p+cur_val; 
  scan_optional_equals; scan_font_ident; define(p,data,cur_val); 
  end; 

MODULE: 'Assignments '
(*PASCAL module 1235*)
register,advance,multiply,divide: do_register_command(a); 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1236*)
procedure do_register_command(a:small_number); 
label found,exit; 
var l,q,r,s:pointer; {for list manipulation} 
p:int_val..mu_val; {type of register involved} 
begin q:=cur_cmd; 

INSERT: 'Compute the register location |l| and its type |p|; but |return| if invalid'
; 
if q=register then scan_optional_equals 
else if scan_keyword('by') then do_nothing; {optional `\.[by]''} 
(*by*) 
arith_error:=false; 
if q<multiply then 
INSERT: 'Compute result of |register| or     |advance|, put it in |cur_val|'

else 
INSERT: 'Compute result of |multiply| or |divide|, put it in |cur_val|'
; 
if arith_error then 
  begin print_err('Arithmetic overflow'); 
(*Arithmetic overflow*) 
  help2('I can''t carry out that multiplication or division,')
 
    ('since the result is out of range.'); 
  if p>=glue_val then delete_glue_ref(cur_val); 
  error; return; 
  end; 
if p<glue_val then word_define(l,cur_val) 
else  begin trap_zero_glue; define(l,glue_ref,cur_val); 
  end; 
exit: end; 

MODULE: 'Compute the register location |l| and its type |p|...'
(*PASCAL module 1237*)
begin if q<>register then 
  begin get_x_token; 
  if (cur_cmd>=assign_int)and(cur_cmd<=assign_mu_glue) then 
    begin l:=cur_chr; p:=cur_cmd-assign_int; goto found; 
    end; 
  if cur_cmd<>register then 
    begin print_err('You can''t use `'); print_cmd_chr(cur_cmd,cur_chr); 
(*You can''t use x after ...*) 
    print(''' after '); print_cmd_chr(q,0); 
    help1('I''m forgetting what you said and not changing anything.'); 
    error; return; 
    end; 
  end; 
p:=cur_chr; scan_eight_bit_int; 
case p of 
int_val: l:=cur_val+count_base; 
dimen_val: l:=cur_val+scaled_base; 
glue_val: l:=cur_val+skip_base; 
mu_val: l:=cur_val+mu_skip_base; 
end; {there are no other cases} 
end; 
found: 

MODULE: 'Compute result of |register| or |advance|...'
(*PASCAL module 1238*)
if p<glue_val then 
  begin if p=int_val then scan_intelse scan_normal_dimen; 
  if q=advance then cur_val:=cur_val+eqtb[l].int; 
  end 
else  begin scan_glue(p); 
  if q=advance then 
INSERT: 'Compute the sum of two glue specs'
; 
  end 

MODULE: 'Compute the sum of two glue specs'
(*PASCAL module 1239*)
begin q:=new_spec(cur_val); r:=equiv(l); 
delete_glue_ref(cur_val); 
width(q):=width(q)+width(r); 
if stretch(q)=0 then stretch_order(q):=normal; 
if stretch_order(q)=stretch_order(r) then stretch(q):=stretch(q)+stretch(r) 
else if (stretch_order(q)<stretch_order(r))and(stretch(r)<>0) then 
  begin stretch(q):=stretch(r); stretch_order(q):=stretch_order(r); 
  end; 
if shrink(q)=0 then shrink_order(q):=normal; 
if shrink_order(q)=shrink_order(r) then shrink(q):=shrink(q)+shrink(r) 
else if (shrink_order(q)<shrink_order(r))and(shrink(r)<>0) then 
  begin shrink(q):=shrink(r); shrink_order(q):=shrink_order(r); 
  end; 
cur_val:=q; 
end 

MODULE: 'Compute result of |multiply| or |divide|...'
(*PASCAL module 1240*)
begin scan_int; 
if p<glue_val then 
  if q=multiply then 
    if p=int_val then cur_val:=mult_integers(eqtb[l].int,cur_val) 
    else cur_val:=nx_plus_y(eqtb[l].int,cur_val,0) 
  else cur_val:=x_over_n(eqtb[l].int,cur_val) 
else  begin s:=equiv(l); r:=new_spec(s); 
  if q=multiply then 
    begin width(r):=nx_plus_y(width(s),cur_val,0); 
    stretch(r):=nx_plus_y(stretch(s),cur_val,0); 
    shrink(r):=nx_plus_y(shrink(s),cur_val,0); 
    end 
  else  begin width(r):=x_over_n(width(s),cur_val); 
    stretch(r):=x_over_n(stretch(s),cur_val); 
    shrink(r):=x_over_n(shrink(s),cur_val); 
    end; 
  cur_val:=r; 
  end; 
end 

MODULE: 'Assignments '
(*PASCAL module 1241*)
set_box: begin scan_eight_bit_int; 
  if global then n:=256+cur_valelse n:=cur_val; 
  scan_optional_equals; 
  if set_box_allowed then scan_box(box_flag+n) 
  else begin print_err('Improper '); print_esc('setbox'); 
(*Improper \\setbox*) 
    help2('Sorry, \setbox is not allowed after \halign in a display,')
 
    ('or between \accent and an accented character.'); error; 
    end; 
  end; 

MODULE: 'Assignments '
(*PASCAL module 1242*)
set_aux:alter_aux; 
set_prev_graf:alter_prev_graf; 
set_page_dimen:alter_page_so_far; 
set_page_int:alter_integer; 
set_box_dimen:alter_box_dimen; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1243*)
procedure alter_aux; 
var c:halfword; {|hmode| or |vmode|} 
begin if cur_chr<>abs(mode) then report_illegal_case 
else  begin c:=cur_chr; scan_optional_equals; 
  if c=vmode then 
    begin scan_normal_dimen; prev_depth:=cur_val; 
    end 
  else  begin scan_int; 
    if (cur_val<=0)or(cur_val>32767) then 
      begin print_err('Bad space factor'); 
(*Bad space factor*) 
      help1('I allow only values in the range 1..32767 here.'); 
      int_error(cur_val); 
      end 
    else space_factor:=cur_val; 
    end; 
  end; 
end; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1244*)
procedure alter_prev_graf; 
var p:0..nest_size; {index into |nest|} 
begin nest[nest_ptr]:=cur_list; p:=nest_ptr; 
while abs(nest[p].mode_field)<>vmode do decr(p); 
scan_optional_equals; scan_int; 
if cur_val<0 then 
  begin print_err('Bad '); print_esc('prevgraf'); 
(*Bad \\prevgraf*) 
  help1('I allow only nonnegative values here.'); 
  int_error(cur_val); 
  end 
else  begin nest[p].pg_field:=cur_val; cur_list:=nest[nest_ptr]; 
  end; 
end; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1245*)
procedure alter_page_so_far; 
var c:0..7; {index into |page_so_far|} 
begin c:=cur_chr; scan_optional_equals; scan_normal_dimen; 
page_so_far[c]:=cur_val; 
end; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1246*)
procedure alter_integer; 
var c:0..1; {0 for \.[\\deadcycles], 1 for \.[\\insertpenalties]} 
begin c:=cur_chr; scan_optional_equals; scan_int; 
if c=0 then dead_cycles:=cur_val 
else insert_penalties:=cur_val; 
end; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1247*)
procedure alter_box_dimen; 
var c:small_number; {|width_offset| or |height_offset| or |depth_offset|} 
b:eight_bits; {box number} 
begin c:=cur_chr; scan_eight_bit_int; b:=cur_val; scan_optional_equals; 
scan_normal_dimen; 
if box(b)<>null then mem[box(b)+c].sc:=cur_val; 
end; 

MODULE: 'Assignments '
(*PASCAL module 1248*)
set_shape: begin scan_optional_equals; scan_int; n:=cur_val; 
  if n<=0 then p:=null 
  else  begin p:=get_node(2*n+1); info(p):=n; 
    for j:=1 to n do 
      begin scan_normal_dimen; 
      mem[p+2*j-1].sc:=cur_val; {indentation} 
      scan_normal_dimen; 
      mem[p+2*j].sc:=cur_val; {width} 
      end; 
    end; 
  define(par_shape_loc,shape_ref,p); 
  end; 

MODULE: 'Check the ``constant''''...'
(*PASCAL module 1249*)
if 2*max_halfword<mem_top-mem_min then bad:=41; 

MODULE: 'Put each...'
(*PASCAL module 1250*)
primitive('hyphenation',hyph_data,0); 
(*hyphenation_][\.{\\hyphenation} primitive*) 
primitive('patterns',hyph_data,1); 
(*patterns_][\.{\\patterns} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1251*)
hyph_data: if chr_code=1 then print_esc('patterns') 
  else print_esc('hyphenation'); 

MODULE: 'Assignments '
(*PASCAL module 1252*)
hyph_data: if cur_chr=1 then 
    begin init new_patterns; goto done;;tini
 
    print_err('Patterns can be loaded only by INITEX'); 
(*Patterns can be...*) 
    help0; error; 
    repeat get_token; until cur_cmd=right_brace; {flush the patterns} 
    return; 
    end 
  else  begin new_hyph_exceptions; goto done; 
    end; 

MODULE: 'Assignments '
(*PASCAL module 1253*)
assign_font_dimen: begin find_font_dimen(true); k:=cur_val; 
  scan_optional_equals; scan_normal_dimen; font_info[k].sc:=cur_val; 
  end; 
assign_font_int: begin n:=cur_chr; scan_font_ident; f:=cur_val; 
  scan_optional_equals; scan_int; 
  if n=0 then hyphen_char[f]:=cur_valelse skew_char[f]:=cur_val; 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1254*)
primitive('hyphenchar',assign_font_int,0); 
(*hyphen_char_][\.{\\hyphenchar} primitive*) 
primitive('skewchar',assign_font_int,1); 
(*skew_char_][\.{\\skewchar} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1255*)
assign_font_int: if chr_code=0 then print_esc('hyphenchar') 
  else print_esc('skewchar'); 

MODULE: 'Assignments '
(*PASCAL module 1256*)
def_font: new_font(a); 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1257*)
procedure new_font(a:small_number); 
label common_ending; 
var u:pointer; {user's font identifier} 
s:scaled; {stated ``at'' size, or negative of scaled magnification} 
f:internal_font_number; {runs through existing fonts} 
t:str_number; {name for the frozen font identifier} 
old_setting:0..max_selector; {holds |selector| setting} 
flushable_string:str_number; {string not yet referenced} 
begin if job_name=0 then open_log_file; 
  {avoid confusing \.[texput] with the font name} 
(*texput*) 
get_r_token; u:=cur_cs; 
if u>=hash_base then t:=text(u) 
else if u>=single_base then 
  if u=null_cs then t:='FONT'else t:=u-single_base 
else  begin old_setting:=selector; selector:=new_string; 
  print('FONT'); print(u-active_base); selector:=old_setting; 
(*FONTx*) 
  str_room(1); t:=make_string; 
  end; 
define(u,set_font,null_font); scan_optional_equals; scan_file_name; 

INSERT: 'Scan the font size specification'
; 

INSERT: 'If this font has already been loaded, set |f| to the internal   font number and |goto common_ending|'
; 
f:=read_font_info(u,cur_name,cur_area,s); 
common_ending: equiv(u):=f; eqtb[font_id_base+f]:=eqtb[u]; font_id_text(f):=t; 
end; 

MODULE: 'Scan the font size specification'
(*PASCAL module 1258*)
name_in_progress:=true; {this keeps |cur_name| from being changed} 
if scan_keyword('at') then 
INSERT: 'Put the \(p)(positive) `at'''' size into |s|'

(*at*) 
else if scan_keyword('scaled') then 
(*scaled*) 
  begin scan_int; s:=-cur_val; 
  if (cur_val<=0)or(cur_val>32768) then 
    begin print_err('Illegal magnification has been changed to 1000');
 
(*Illegal magnification...*) 
    help1('The magnification ratio must be between 1 and 32768.'); 
    int_error(cur_val); s:=-1000; 
    end; 
  end 
else s:=-1000; 
name_in_progress:=false 

MODULE: 'Put the \(p)(positive) `at'' size into |s|'
(*PASCAL module 1259*)
begin scan_normal_dimen; s:=cur_val; 
if (s<=0)or(s>=134217728) then 
  begin print_err('Improper `at'' size ('); 
  print_scaled(s); print('pt), replaced by 10pt'); 
(*Improper `at'' size...*) 
  help2('I can only handle fonts at positive sizes that are')
 
  ('less than 2048pt, so I''ve changed what you said to 10pt.'); 
  error; s:=10*unity; 
  end; 
end 

MODULE: 'If this font has already been loaded...'
(*PASCAL module 1260*)
flushable_string:=str_ptr-1; 
for f:=font_base+1 to font_ptr do 
  if str_eq_str(font_name[f],cur_name)and str_eq_str(font_area[f],cur_area) then 
    begin if cur_name=flushable_string then 
      begin flush_string; cur_name:=font_name[f]; 
      end; 
    if s>0 then 
      begin if s=font_size[f] then goto common_ending; 
      end 
    else if font_size[f]=xn_over_d(font_dsize[f],-s,1000) then 
      goto common_ending; 
    end 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1261*)
set_font:begin print('select font '); slow_print(font_name[chr_code]); 
  if font_size[chr_code]<>font_dsize[chr_code] then 
    begin print(' at '); print_scaled(font_size[chr_code]); 
    print('pt'); 
    end; 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1262*)
primitive('batchmode',set_interaction,batch_mode); 
(*batch_mode_][\.{\\batchmode} primitive*) 
primitive('nonstopmode',set_interaction,nonstop_mode); 
(*nonstop_mode_][\.{\\nonstopmode} primitive*) 
primitive('scrollmode',set_interaction,scroll_mode); 
(*scroll_mode_][\.{\\scrollmode} primitive*) 
primitive('errorstopmode',set_interaction,error_stop_mode); 
(*error_stop_mode_][\.{\\errorstopmode} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1263*)
set_interaction: case chr_code of 
  batch_mode: print_esc('batchmode'); 
  nonstop_mode: print_esc('nonstopmode'); 
  scroll_mode: print_esc('scrollmode'); 
  othercases print_esc('errorstopmode') 
  endcases; 

MODULE: 'Assignments '
(*PASCAL module 1264*)
set_interaction: new_interaction; 

MODULE: 'Declare subprocedures for |prefixed_command|'
(*PASCAL module 1265*)
procedure new_interaction; 
begin print_ln; 
interaction:=cur_chr; 

INSERT: 'Initialize the print |selector| based on |interaction|'
; 
if log_opened then selector:=selector+2; 
end; 

MODULE: 'Glob... '
(*PASCAL module 1266*)
after_token:halfword; {zero, or a saved token} 

MODULE: 'Set init...'
(*PASCAL module 1267*)
after_token:=0; 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1268*)
any_mode(after_assignment):begin get_token; after_token:=cur_tok; 
  end; 

MODULE: 'Insert a token saved by \.{\\afterassignment}, if any'
(*PASCAL module 1269*)
if after_token<>0 then 
  begin cur_tok:=after_token; back_input; after_token:=0; 
  end 

MODULE: 'Declare act...'
(*PASCAL module 1270*)
procedure do_assignments; 
label exit; 
begin loop begin 
INSERT: 'Get the next non-blank non-relax...'
; 
  if cur_cmd<=max_non_prefixed_command then return; 
  set_box_allowed:=false; prefixed_command; set_box_allowed:=true; 
  end; 
exit:end; 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1271*)
any_mode(after_group):begin get_token; save_for_after(cur_tok); 
  end; 

MODULE: 'Put each...'
(*PASCAL module 1272*)
primitive('openin',in_stream,1); 
(*open_in_][\.{\\openin} primitive*) 
primitive('closein',in_stream,0); 
(*close_in_][\.{\\closein} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1273*)
in_stream: if chr_code=0 then print_esc('closein') 
  else print_esc('openin'); 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1274*)
any_mode(in_stream): open_or_close_in; 

MODULE: 'Declare act...'
(*PASCAL module 1275*)
procedure open_or_close_in; 
var c:0..1; {1 for \.[\\openin], 0 for \.[\\closein]} 
n:0..15; {stream number} 
begin c:=cur_chr; scan_four_bit_int; n:=cur_val; 
if read_open[n]<>closed then 
  begin a_close(read_file[n]); read_open[n]:=closed; 
  end; 
if c<>0 then 
  begin scan_optional_equals; scan_file_name; 
  if cur_ext='' then cur_ext:='.tex'; 
  pack_cur_name; 
  if a_open_in(read_file[n]) then read_open[n]:=just_open; 
  end; 
end; 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1276*)
any_mode(message):issue_message; 

MODULE: 'Put each...'
(*PASCAL module 1277*)
primitive('message',message,0); 
(*message_][\.{\\message} primitive*) 
primitive('errmessage',message,1); 
(*err_message_][\.{\\errmessage} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1278*)
message: if chr_code=0 then print_esc('message') 
  else print_esc('errmessage'); 

MODULE: 'Declare act...'
(*PASCAL module 1279*)
procedure issue_message; 
var old_setting:0..max_selector; {holds |selector| setting} 
c:0..1; {identifies \.[\\message] and \.[\\errmessage]} 
s:str_number; {the message} 
begin c:=cur_chr; link(garbage):=scan_toks(false,true); 
old_setting:=selector; selector:=new_string; 
token_show(def_ref); selector:=old_setting; 
flush_list(def_ref); 
str_room(1); s:=make_string; 
if c=0 then 
INSERT: 'Print string |s| on the terminal'

else 
INSERT: 'Print string |s| as an error message'
; 
flush_string; 
end; 

MODULE: 'Print string |s| on the terminal'
(*PASCAL module 1280*)
begin if term_offset+length(s)>max_print_line-2 then print_ln 
else if (term_offset>0)or(file_offset>0) then print_char(' '); 
slow_print(s); update_terminal; 
end 

MODULE: 'Glob... '
(*PASCAL module 1281*)
long_help_seen:boolean; {has the long \.[\\errmessage] help been used?} 

MODULE: 'Print string |s| as an error message'
(*PASCAL module 1283*)
begin print_err(''); slow_print(s); 
if err_help<>null then use_err_help:=true 
else if long_help_seen then help1('(That was another \errmessage.)') 
else  begin if interaction<error_stop_mode then long_help_seen:=true; 
  help4('This error message was generated by an \errmessage')
 
  ('command, so I can''t give any explicit help.')
 
  ('Pretend that you''re Hercule Poirot: Examine all clues,')
 
(*Poirot, Hercule*) 
  ('and deduce the truth by order and method.'); 
  end; 
error; use_err_help:=false; 
end 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1285*)
any_mode(case_shift):shift_case; 

MODULE: 'Put each...'
(*PASCAL module 1286*)
primitive('lowercase',case_shift,lc_code_base); 
(*lowercase_][\.{\\lowercase} primitive*) 
primitive('uppercase',case_shift,uc_code_base); 
(*uppercase_][\.{\\uppercase} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1287*)
case_shift:if chr_code=lc_code_base then print_esc('lowercase') 
  else print_esc('uppercase'); 

MODULE: 'Declare act...'
(*PASCAL module 1288*)
procedure shift_case; 
var b:pointer; {|lc_code_base| or |uc_code_base|} 
p:pointer; {runs through the token list} 
t:halfword; {token} 
c:eight_bits; {character code} 
begin b:=cur_chr; p:=scan_toks(false,false); p:=link(def_ref); 
while p<>null do 
  begin 
INSERT: 'Change the case of the token in |p|, if a change is appropriate'
; 
  p:=link(p); 
  end; 
back_list(link(def_ref)); free_avail(def_ref); {omit reference count} 
end; 

MODULE: 'Change the case of the token in |p|, if a change is appropriate'
(*PASCAL module 1289*)
t:=info(p); 
if t<cs_token_flag+single_base then 
  begin c:=t mod 256; 
  if equiv(b+c)<>0 then info(p):=t-c+equiv(b+c); 
  end 

MODULE: 'Cases of |main_control| that don''t...'
(*PASCAL module 1290*)
any_mode(xray): show_whatever; 

MODULE: 'Put each...'
(*PASCAL module 1291*)
primitive('show',xray,show_code); 
(*show_][\.{\\show} primitive*) 
primitive('showbox',xray,show_box_code); 
(*show_box_][\.{\\showbox} primitive*) 
primitive('showthe',xray,show_the_code); 
(*show_the_][\.{\\showthe} primitive*) 
primitive('showlists',xray,show_lists); 
(*show_lists_][\.{\\showlists} primitive*) 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1292*)
xray: case chr_code of 
  show_box_code:print_esc('showbox'); 
  show_the_code:print_esc('showthe'); 
  show_lists:print_esc('showlists'); 
  othercases print_esc('show') 
  endcases; 

MODULE: 'Declare act...'
(*PASCAL module 1293*)
procedure show_whatever; 
label common_ending; 
var p:pointer; {tail of a token list to show} 
begin case cur_chr of 
show_lists: begin begin_diagnostic; show_activities; 
  end; 
show_box_code: 
INSERT: 'Show the current contents of a box'
; 
show_code: 
INSERT: 'Show the current meaning of a token, then |goto common_ending|'
; 
othercases 
INSERT: 'Show the current value of some parameter or register,   then |goto common_ending|'

endcases;
 

INSERT: 'Complete a potentially long \.{\\show} command'
; 
common_ending: if interaction<error_stop_mode then 
  begin help0; decr(error_count); 
  end 
else if tracing_online>0 then 
  begin(**);
 
  help3('This isn''t an error message; I''m just \showing something.')
 
  ('Type `I\show...'' to show more (e.g., \show\cs,')
 
  ('\showthe\count10, \showbox255, \showlists).'); 
  end 
else  begin(**);
 
  help5('This isn''t an error message; I''m just \showing something.')
 
  ('Type `I\show...'' to show more (e.g., \show\cs,')
 
  ('\showthe\count10, \showbox255, \showlists).')
 
  ('And type `I\tracingonline=1\show...'' to show boxes and')
 
  ('lists on your terminal as well as in the transcript file.'); 
  end; 
error; 
end; 

MODULE: 'Show the current meaning of a token...'
(*PASCAL module 1294*)
begin get_token; 
if interaction=error_stop_mode then wake_up_terminal; 
print_nl('> '); 
if cur_cs<>0 then 
  begin sprint_cs(cur_cs); print_char('='); 
  end; 
print_meaning; goto common_ending; 
end 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1295*)
undefined_cs: print('undefined'); 
call: print('macro'); 
long_call: print_esc('long macro'); 
outer_call: print_esc('outer macro'); 
long_outer_call: begin print_esc('long'); print_esc('outer macro'); 
  end; 
end_template: print_esc('outer endtemplate'); 

MODULE: 'Show the current contents of a box'
(*PASCAL module 1296*)
begin scan_eight_bit_int; begin_diagnostic; 
print_nl('> \box'); print_int(cur_val); print_char('='); 
if box(cur_val)=null then print('void') 
else show_box(box(cur_val)); 
end 

MODULE: 'Show the current value of some parameter...'
(*PASCAL module 1297*)
begin p:=the_toks; 
if interaction=error_stop_mode then wake_up_terminal; 
print_nl('> '); token_show(temp_head); 
flush_list(link(temp_head)); goto common_ending; 
end 

MODULE: 'Complete a potentially long \.{\\show} command'
(*PASCAL module 1298*)
end_diagnostic(true); print_err('OK'); 
(*OK*) 
if selector=term_and_log then if tracing_online<=0 then 
  begin selector:=term_only; print(' (see the transcript file)'); 
  selector:=term_and_log; 
  end 

MODULE: 'Glob... '
(*PASCAL module 1299*)
format_ident:str_number; 

MODULE: 'Set init...'
(*PASCAL module 1300*)
format_ident:=0; 

MODULE: 'Initialize table entries...'
(*PASCAL module 1301*)
format_ident:=' (INITEX)'; 

MODULE: 'Declare act...'
(*PASCAL module 1302*)
init procedure store_fmt_file; 
label found1,found2,done1,done2; 
var j,k,l:integer; {all-purpose indices} 
p,q: pointer; {all-purpose pointers} 
x: integer; {something to dump} 
w: four_quarters; {four ASCII codes} 
begin 
INSERT: 'If dumping is not allowed, abort'
; 

INSERT: 'Create the |format_ident|, open the format file,   and inform the user that dumping has begun'
; 

INSERT: 'Dump constants for consistency check'
; 

INSERT: 'Dump the string pool'
; 

INSERT: 'Dump the dynamic memory'
; 

INSERT: 'Dump the table of equivalents'
; 

INSERT: 'Dump the font information'
; 

INSERT: 'Dump the hyphenation tables'
; 

INSERT: 'Dump a couple more things and the closing check word'
; 

INSERT: 'Close the format file'
; 
end; 
tini 

MODULE: 'If dumping is not allowed, abort'
(*PASCAL module 1304*)
if save_ptr<>0 then 
  begin print_err('You can''t dump inside a group'); 
(*You can''t dump...*) 
  help1('`{...\dump}'' is a no-no.'); succumb; 
  end 

MODULE: 'Glob... '
(*PASCAL module 1305*)
fmt_file:word_file; {for input or output of format information} 

MODULE: 'Dump constants for consistency check'
(*PASCAL module 1307*)
dump_int(@$);
 
dump_int(mem_bot);
 
dump_int(mem_top);
 
dump_int(eqtb_size);
 
dump_int(hash_prime);
 
dump_int(hyph_size) 

MODULE: 'Undump constants for consistency check'
(*PASCAL module 1308*)
x:=fmt_file^.int; 
if x<>@$ then goto bad_fmt; {check that strings are the same} 
undump_int(x); 
if x<>mem_bot then goto bad_fmt; 
undump_int(x); 
if x<>mem_top then goto bad_fmt; 
undump_int(x); 
if x<>eqtb_size then goto bad_fmt; 
undump_int(x); 
if x<>hash_prime then goto bad_fmt; 
undump_int(x); 
if x<>hyph_size then goto bad_fmt 

MODULE: 'Dump the string pool'
(*PASCAL module 1309*)
dump_int(pool_ptr); 
dump_int(str_ptr); 
for k:=0 to str_ptr do dump_int(str_start[k]); 
k:=0; 
while k+4<pool_ptr do 
  begin dump_four_ASCII; k:=k+4; 
  end; 
k:=pool_ptr-4; dump_four_ASCII; 
print_ln; print_int(str_ptr); print(' strings of total length '); 
print_int(pool_ptr) 

MODULE: 'Undump the string pool'
(*PASCAL module 1310*)
undump_size(0)(pool_size)('string pool size')(pool_ptr); 
undump_size(0)(max_strings)('max strings')(str_ptr); 
for k:=0 to str_ptr do undump(0)(pool_ptr)(str_start[k]); 
k:=0; 
while k+4<pool_ptr do 
  begin undump_four_ASCII; k:=k+4; 
  end; 
k:=pool_ptr-4; undump_four_ASCII; 
init_str_ptr:=str_ptr; init_pool_ptr:=pool_ptr 

MODULE: 'Dump the dynamic memory'
(*PASCAL module 1311*)
sort_avail; var_used:=0; 
dump_int(lo_mem_max); dump_int(rover); 
p:=mem_bot; q:=rover; x:=0; 
repeat for k:=p to q+1 do dump_wd(mem[k]); 
x:=x+q+2-p; var_used:=var_used+q-p; 
p:=q+node_size(q); q:=rlink(q); 
until q=rover; 
var_used:=var_used+lo_mem_max-p; dyn_used:=mem_end+1-hi_mem_min;
 
for k:=p to lo_mem_max do dump_wd(mem[k]); 
x:=x+lo_mem_max+1-p; 
dump_int(hi_mem_min); dump_int(avail); 
for k:=hi_mem_min to mem_end do dump_wd(mem[k]); 
x:=x+mem_end+1-hi_mem_min; 
p:=avail; 
while p<>null do 
  begin decr(dyn_used); p:=link(p); 
  end; 
dump_int(var_used); dump_int(dyn_used); 
print_ln; print_int(x); 
print(' memory locations dumped; current usage is '); 
print_int(var_used); print_char('&'); print_int(dyn_used) 

MODULE: 'Undump the dynamic memory'
(*PASCAL module 1312*)
undump(lo_mem_stat_max+1000)(hi_mem_stat_min-1)(lo_mem_max); 
undump(lo_mem_stat_max+1)(lo_mem_max)(rover); 
p:=mem_bot; q:=rover; 
repeat for k:=p to q+1 do undump_wd(mem[k]); 
p:=q+node_size(q); 
if (p>lo_mem_max)or((q>=rlink(q))and(rlink(q)<>rover)) then goto bad_fmt; 
q:=rlink(q); 
until q=rover; 
for k:=p to lo_mem_max do undump_wd(mem[k]); 
if mem_min<mem_bot-2 then {make more low memory available} 
  begin p:=llink(rover); q:=mem_min+1; 
  link(mem_min):=null; info(mem_min):=null; {we don't use the bottom word} 
  rlink(p):=q; llink(rover):=q;
 
  rlink(q):=rover; llink(q):=p; link(q):=empty_flag; 
  node_size(q):=mem_bot-q; 
  end; 
undump(lo_mem_max+1)(hi_mem_stat_min)(hi_mem_min); 
undump(null)(mem_top)(avail); mem_end:=mem_top; 
for k:=hi_mem_min to mem_end do undump_wd(mem[k]); 
undump_int(var_used); undump_int(dyn_used) 

MODULE: 'Dump the table of equivalents'
(*PASCAL module 1313*)

INSERT: 'Dump regions 1 to 4 of |eqtb|'
; 

INSERT: 'Dump regions 5 and 6 of |eqtb|'
; 
dump_int(par_loc); dump_int(write_loc);
 

INSERT: 'Dump the hash table'


MODULE: 'Undump the table of equivalents'
(*PASCAL module 1314*)

INSERT: 'Undump regions 1 to 6 of |eqtb|'
; 
undump(hash_base)(frozen_control_sequence)(par_loc); 
par_token:=cs_token_flag+par_loc;
 
undump(hash_base)(frozen_control_sequence)(write_loc);
 

INSERT: 'Undump the hash table'


MODULE: 'Dump regions 1 to 4 of |eqtb|'
(*PASCAL module 1315*)
k:=active_base; 
repeat j:=k; 
while j<int_base-1 do 
  begin if (equiv(j)=equiv(j+1))and(eq_type(j)=eq_type(j+1))and 
    (eq_level(j)=eq_level(j+1)) then goto found1; 
  incr(j); 
  end; 
l:=int_base; goto done1; {|j=int_base-1|} 
found1: incr(j); l:=j; 
while j<int_base-1 do 
  begin if (equiv(j)<>equiv(j+1))or(eq_type(j)<>eq_type(j+1))or 
    (eq_level(j)<>eq_level(j+1)) then goto done1; 
  incr(j); 
  end; 
done1:dump_int(l-k); 
while k<l do 
  begin dump_wd(eqtb[k]); incr(k); 
  end; 
k:=j+1; dump_int(k-l); 
until k=int_base 

MODULE: 'Dump regions 5 and 6 of |eqtb|'
(*PASCAL module 1316*)
repeat j:=k; 
while j<eqtb_size do 
  begin if eqtb[j].int=eqtb[j+1].int then goto found2; 
  incr(j); 
  end; 
l:=eqtb_size+1; goto done2; {|j=eqtb_size|} 
found2: incr(j); l:=j; 
while j<eqtb_size do 
  begin if eqtb[j].int<>eqtb[j+1].int then goto done2; 
  incr(j); 
  end; 
done2:dump_int(l-k); 
while k<l do 
  begin dump_wd(eqtb[k]); incr(k); 
  end; 
k:=j+1; dump_int(k-l); 
until k>eqtb_size 

MODULE: 'Undump regions 1 to 6 of |eqtb|'
(*PASCAL module 1317*)
k:=active_base; 
repeat undump_int(x); 
if (x<1)or(k+x>eqtb_size+1) then goto bad_fmt; 
for j:=k to k+x-1 do undump_wd(eqtb[j]); 
k:=k+x; 
undump_int(x); 
if (x<0)or(k+x>eqtb_size+1) then goto bad_fmt; 
for j:=k to k+x-1 do eqtb[j]:=eqtb[k-1]; 
k:=k+x; 
until k>eqtb_size 

MODULE: 'Dump the hash table'
(*PASCAL module 1318*)
dump_int(hash_used); cs_count:=frozen_control_sequence-1-hash_used; 
for p:=hash_base to hash_used do if text(p)<>0 then 
  begin dump_int(p); dump_hh(hash[p]); incr(cs_count); 
  end; 
for p:=hash_used+1 to undefined_control_sequence-1 do dump_hh(hash[p]); 
dump_int(cs_count);
 
print_ln; print_int(cs_count); print(' multiletter control sequences') 

MODULE: 'Undump the hash table'
(*PASCAL module 1319*)
undump(hash_base)(frozen_control_sequence)(hash_used); p:=hash_base-1; 
repeat undump(p+1)(hash_used)(p); undump_hh(hash[p]); 
until p=hash_used; 
for p:=hash_used+1 to undefined_control_sequence-1 do undump_hh(hash[p]); 
undump_int(cs_count) 

MODULE: 'Dump the font information'
(*PASCAL module 1320*)
dump_int(fmem_ptr); 
for k:=0 to fmem_ptr-1 do dump_wd(font_info[k]); 
dump_int(font_ptr); 
for k:=null_font to font_ptr do 
  
INSERT: 'Dump the array info for internal font number |k|'
; 
print_ln; print_int(fmem_ptr-7); print(' words of font info for '); 
print_int(font_ptr-font_base); print(' preloaded font'); 
if font_ptr<>font_base+1 then print_char('s') 

MODULE: 'Undump the font information'
(*PASCAL module 1321*)
undump_size(7)(font_mem_size)('font mem size')(fmem_ptr); 
for k:=0 to fmem_ptr-1 do undump_wd(font_info[k]); 
undump_size(font_base)(font_max)('font max')(font_ptr); 
for k:=null_font to font_ptr do 
  
INSERT: 'Undump the array info for internal font number |k|'


MODULE: 'Dump the array info for internal font number |k|'
(*PASCAL module 1322*)
begin dump_qqqq(font_check[k]); 
dump_int(font_size[k]); 
dump_int(font_dsize[k]); 
dump_int(font_params[k]);
 
dump_int(hyphen_char[k]); 
dump_int(skew_char[k]);
 
dump_int(font_name[k]); 
dump_int(font_area[k]);
 
dump_int(font_bc[k]); 
dump_int(font_ec[k]);
 
dump_int(char_base[k]); 
dump_int(width_base[k]); 
dump_int(height_base[k]);
 
dump_int(depth_base[k]); 
dump_int(italic_base[k]); 
dump_int(lig_kern_base[k]);
 
dump_int(kern_base[k]); 
dump_int(exten_base[k]); 
dump_int(param_base[k]);
 
dump_int(font_glue[k]);
 
dump_int(bchar_label[k]); 
dump_int(font_bchar[k]); 
dump_int(font_false_bchar[k]);
 
print_nl('\font'); print_esc(font_id_text(k)); print_char('='); 
print_file_name(font_name[k],font_area[k],''); 
if font_size[k]<>font_dsize[k] then 
  begin print(' at '); print_scaled(font_size[k]); print('pt'); 
  end; 
end 

MODULE: 'Undump the array info for internal font number |k|'
(*PASCAL module 1323*)
begin undump_qqqq(font_check[k]);
 
undump_int(font_size[k]); 
undump_int(font_dsize[k]); 
undump(min_halfword)(max_halfword)(font_params[k]);
 
undump_int(hyphen_char[k]); 
undump_int(skew_char[k]);
 
undump(0)(str_ptr)(font_name[k]); 
undump(0)(str_ptr)(font_area[k]);
 
undump(0)(255)(font_bc[k]); 
undump(0)(255)(font_ec[k]);
 
undump_int(char_base[k]); 
undump_int(width_base[k]); 
undump_int(height_base[k]);
 
undump_int(depth_base[k]); 
undump_int(italic_base[k]); 
undump_int(lig_kern_base[k]);
 
undump_int(kern_base[k]); 
undump_int(exten_base[k]); 
undump_int(param_base[k]);
 
undump(min_halfword)(lo_mem_max)(font_glue[k]);
 
undump(0)(fmem_ptr-1)(bchar_label[k]); 
undump(min_quarterword)(non_char)(font_bchar[k]); 
undump(min_quarterword)(non_char)(font_false_bchar[k]); 
end 

MODULE: 'Dump the hyphenation tables'
(*PASCAL module 1324*)
dump_int(hyph_count); 
for k:=0 to hyph_size do if hyph_word[k]<>0 then 
  begin dump_int(k); dump_int(hyph_word[k]); dump_int(hyph_list[k]); 
  end; 
print_ln; print_int(hyph_count); print(' hyphenation exception'); 
if hyph_count<>1 then print_char('s'); 
if trie_not_ready then init_trie; 
dump_int(trie_max); 
for k:=0 to trie_max do dump_hh(trie[k]); 
dump_int(trie_op_ptr); 
for k:=1 to trie_op_ptr do 
  begin dump_int(hyf_distance[k]); 
  dump_int(hyf_num[k]); 
  dump_int(hyf_next[k]); 
  end; 
print_nl('Hyphenation trie of length '); print_int(trie_max); 
(*Hyphenation trie...*) 
print(' has '); print_int(trie_op_ptr); print(' op'); 
if trie_op_ptr<>1 then print_char('s'); 
print(' out of '); print_int(trie_op_size); 
for k:=255 downto 0 do if trie_used[k]>min_quarterword then 
  begin print_nl('  '); print_int(qo(trie_used[k])); 
  print(' for language '); print_int(k); 
  dump_int(k); dump_int(qo(trie_used[k])); 
  end 

MODULE: 'Undump the hyphenation tables'
(*PASCAL module 1325*)
undump(0)(hyph_size)(hyph_count); 
for k:=1 to hyph_count do 
  begin undump(0)(hyph_size)(j); 
  undump(0)(str_ptr)(hyph_word[j]); 
  undump(min_halfword)(max_halfword)(hyph_list[j]); 
  end; 
undump_size(0)(trie_size)('trie size')(j); init trie_max:=j;tini 
for k:=0 to j do undump_hh(trie[k]); 
undump_size(0)(trie_op_size)('trie op size')(j); init trie_op_ptr:=j;tini 
for k:=1 to j do 
  begin undump(0)(63)(hyf_distance[k]); {a |small_number|} 
  undump(0)(63)(hyf_num[k]); 
  undump(min_quarterword)(max_quarterword)(hyf_next[k]); 
  end; 
init for k:=0 to 255 do trie_used[k]:=min_quarterword;tini;
 
k:=256; 
while j>0 do 
  begin undump(0)(k-1)(k); undump(1)(j)(x);init trie_used[k]:=qi(x);tini;
 
  j:=j-x; op_start[k]:=qo(j); 
  end; 
init trie_not_ready:=false tini 

MODULE: 'Dump a couple more things and the closing check word'
(*PASCAL module 1326*)
dump_int(interaction); dump_int(format_ident); dump_int(69069); 
tracing_stats:=0 

MODULE: 'Undump a couple more things and the closing check word'
(*PASCAL module 1327*)
undump(batch_mode)(error_stop_mode)(interaction); 
undump(0)(str_ptr)(format_ident); 
undump_int(x); 
if (x<>69069)or eof(fmt_file) then goto bad_fmt 

MODULE: 'Create the |format_ident|...'
(*PASCAL module 1328*)
selector:=new_string; 
print(' (preloaded format='); print(job_name); print_char(' '); 
print_int(year); print_char('.'); 
print_int(month); print_char('.'); print_int(day); print_char(')'); 
if interaction=batch_mode then selector:=log_only 
else selector:=term_and_log; 
str_room(1); 
format_ident:=make_string; 
pack_job_name(format_extension); 
while not w_open_out(fmt_file) do 
  prompt_file_name('format file name',format_extension); 
print_nl('Beginning to dump on file '); 
(*Beginning to dump...*) 
slow_print(w_make_name_string(fmt_file)); flush_string; 
print_nl(''); slow_print(format_ident) 

MODULE: 'Close the format file'
(*PASCAL module 1329*)
w_close(fmt_file) 

MODULE: 'Glob... '
(*PASCAL module 1331*)
ready_already:integer; {a sacrifice of purity for economy} 

MODULE: 'Last-minute... '
(*PASCAL module 1333*)
procedure close_files_and_terminate; 
var k:integer; {all-purpose index} 
begin 
INSERT: 'Finish the extensions'
; 
stat if tracing_stats>0 then 
INSERT: 'Output statistics about this job'
;;tats
 
wake_up_terminal; 
INSERT: 'Finish the \.{DVI} file'
; 
if log_opened then 
  begin wlog_cr; a_close(log_file); selector:=selector-2; 
  if selector=term_only then 
    begin print_nl('Transcript written on '); 
(*Transcript written...*) 
    slow_print(log_name); print_char('.'); 
    end; 
  end; 
end; 

MODULE: 'Output statistics...'
(*PASCAL module 1334*)
if log_opened then 
  begin wlog_ln(' '); 
  wlog_ln('Here is how much of TeX''s memory',' you used:'); 
(*Here is how much...*) 
  wlog(' ',str_ptr-init_str_ptr:1,' string'); 
  if str_ptr<>init_str_ptr+1 then wlog('s'); 
  wlog_ln(' out of ', max_strings-init_str_ptr:1);
 
  wlog_ln(' ',pool_ptr-init_pool_ptr:1,' string characters out of ', 
    pool_size-init_pool_ptr:1);
 
  wlog_ln(' ',lo_mem_max-mem_min+mem_end-hi_mem_min+2:1, 
    ' words of memory out of ',mem_end+1-mem_min:1);
 
  wlog_ln(' ',cs_count:1,' multiletter control sequences out of ', 
    hash_size:1);
 
  wlog(' ',fmem_ptr:1,' words of font info for ', 
    font_ptr-font_base:1,' font'); 
  if font_ptr<>font_base+1 then wlog('s'); 
  wlog_ln(', out of ',font_mem_size:1,' for ',font_max-font_base:1);
 
  wlog(' ',hyph_count:1,' hyphenation exception'); 
  if hyph_count<>1 then wlog('s'); 
  wlog_ln(' out of ',hyph_size:1);
 
  wlog_ln(' ',max_in_stack:1,'i,',max_nest_stack:1,'n,', 
    max_param_stack:1,'p,', 
    max_buf_stack+1:1,'b,', 
    max_save_stack+6:1,'s stack positions out of ', 
    stack_size:1,'i,', 
    nest_size:1,'n,', 
    param_size:1,'p,', 
    buf_size:1,'b,', 
    save_size:1,'s'); 
  end 

MODULE: 'Last-minute... '
(*PASCAL module 1335*)
procedure final_cleanup; 
label exit; 
var c:small_number; {0 for \.[\\end], 1 for \.[\\dump]} 
begin c:=cur_chr; 
if job_name=0 then open_log_file; 
while input_ptr>0 do 
  if state=token_list then end_token_listelse end_file_reading; 
while open_parens>0 do 
  begin print(' )'); decr(open_parens); 
  end; 
if cur_level>level_one then 
  begin print_nl('('); print_esc('end occurred '); 
  print('inside a group at level '); 
(*end_][\.{(\\end occurred...)}*) 
  print_int(cur_level-level_one); print_char(')'); 
  end; 
while cond_ptr<>null do 
  begin print_nl('('); print_esc('end occurred '); 
  print('when '); print_cmd_chr(if_test,cur_if); 
  if if_line<>0 then 
    begin print(' on line '); print_int(if_line); 
    end; 
  print(' was incomplete)'); 
  if_line:=if_line_field(cond_ptr); 
  cur_if:=subtype(cond_ptr); temp_ptr:=cond_ptr; 
  cond_ptr:=link(cond_ptr); free_node(temp_ptr,if_node_size); 
  end; 
if history<>spotless then 
 if ((history=warning_issued)or(interaction<error_stop_mode)) then 
  if selector=term_and_log then 
  begin selector:=term_only; 
  print_nl('(see the transcript file for additional information)'); 
(*see the transcript file...*) 
  selector:=term_and_log; 
  end; 
if c=1 then 
  begin init for c:=top_mark_code to split_bot_mark_code do 
    if cur_mark[c]<>null then delete_token_ref(cur_mark[c]); 
  if last_glue<>max_halfword then delete_glue_ref(last_glue); 
  store_fmt_file; return;tini
 
  print_nl('(\dump is performed only by INITEX)'); return; 
(*dump_][\.{\\dump...only by INITEX}*) 
  end; 
exit:end; 

MODULE: 'Last-minute... '
(*PASCAL module 1336*)
init procedure init_prim; {initialize all the primitives} 
begin no_new_control_sequence:=false; 

INSERT: 'Put each...'
; 
no_new_control_sequence:=true; 
end; 
tini 

MODULE: 'Get the first line...'
(*PASCAL module 1337*)
begin 
INSERT: 'Initialize the input routines'
; 
if (format_ident=0)or(buffer[loc]='&') then 
  begin if format_ident<>0 then initialize; {erase preloaded format} 
  if not open_fmt_file then goto final_end; 
  if not load_fmt_file then 
    begin w_close(fmt_file); goto final_end; 
    end; 
  w_close(fmt_file); 
  while (loc<limit)and(buffer[loc]=' ') do incr(loc); 
  end; 
if end_line_char_inactive then decr(limit) 
else  buffer[limit]:=end_line_char; 
fix_date_and_time;
 

INSERT: 'Compute the magic offset'
; 

INSERT: 'Initialize the print |selector|...'
; 
if (loc<limit)and(cat_code(buffer[loc])<>escape) then start_input; 
  {\.[\\input] assumed} 
end 

MODULE: 'Last-minute... '
(*PASCAL module 1338*)
debug procedure debug_help; {routine to display various things} 
label breakpoint,exit; 
var k,l,m,n:integer; 
begin loop begin wake_up_terminal; 
  print_nl('debug # (-1 to exit):'); update_terminal; 
(*debug \#*) 
  read(term_in,m); 
  if m<0 then return 
  else if m=0 then 
    begin goto breakpoint; {go to every label at least once} 
    breakpoint: m:=0; @{'BREAKPOINT'@} 
    end 
  else  begin read(term_in,n); 
    case m of 
    (*\4*)
INSERT: 'Numbered cases for |debug_help|'
; 
    othercases print('?') 
    endcases; 
    end; 
  end; 
exit:end; 
gubed 

MODULE: 'Numbered cases...'
(*PASCAL module 1339*)
1: print_word(mem[n]); {display |mem[n]| in all forms} 
2: print_int(info(n)); 
3: print_int(link(n)); 
4: print_word(eqtb[n]); 
5: print_word(font_info[n]); 
6: print_word(save_stack[n]); 
7: show_box(n); 
  {show a box, abbreviated by |show_box_depth| and |show_box_breadth|} 
8: begin breadth_max:=10000; depth_threshold:=pool_size-pool_ptr-10; 
  show_node_list(n); {show a box in its entirety} 
  end; 
9: show_token_list(n,null,1000); 
10: slow_print(n); 
11: check_mem(n>0); {check wellformedness; print new busy locations if |n>0|} 
12: search_mem(n); {look for pointers to |n|} 
13: begin read(term_in,l); print_cmd_chr(n,l); 
  end; 
14: for k:=0 to n do print(buffer[k]); 
15: begin font_in_short_display:=null_font; short_display(n); 
  end; 
16: panicking:=not panicking; 

MODULE: 'Glob... '
(*PASCAL module 1342*)
write_file:array[0..15] of alpha_file; 
write_open:array[0..17] of boolean; 

MODULE: 'Set init...'
(*PASCAL module 1343*)
for k:=0 to 17 do write_open[k]:=false; 

MODULE: 'Put each...'
(*PASCAL module 1344*)
primitive('openout',extension,open_node);
 
(*open_out_][\.{\\openout} primitive*) 
primitive('write',extension,write_node); write_loc:=cur_val;
 
(*write_][\.{\\write} primitive*) 
primitive('closeout',extension,close_node);
 
(*close_out_][\.{\\closeout} primitive*) 
primitive('special',extension,special_node);
 
(*special_][\.{\\special} primitive*) 
primitive('immediate',extension,immediate_code);
 
(*immediate_][\.{\\immediate} primitive*) 
primitive('setlanguage',extension,set_language_code);
 
(*set_language_][\.{\\setlanguage} primitive*) 

MODULE: 'Glob... '
(*PASCAL module 1345*)
write_loc:pointer; {|eqtb| address of \.[\\write]} 

MODULE: 'Cases of |print_cmd_chr|...'
(*PASCAL module 1346*)
extension: case chr_code of 
  open_node:print_esc('openout'); 
  write_node:print_esc('write'); 
  close_node:print_esc('closeout'); 
  special_node:print_esc('special'); 
  immediate_code:print_esc('immediate'); 
  set_language_code:print_esc('setlanguage'); 
  othercases print('[unknown extension!]') 
  endcases; 

MODULE: 'Cases of |main_control| that are for extensions...'
(*PASCAL module 1347*)
any_mode(extension):do_extension; 

MODULE: 'Declare act...'
(*PASCAL module 1348*)
(*\4*)
INSERT: 'Declare procedures needed in |do_extension|'
; 
procedure do_extension; 
var i,j,k:integer; {all-purpose integers} 
p,q,r:pointer; {all-purpose pointers} 
begin case cur_chr of 
open_node:
INSERT: 'Implement \.{\\openout}'
; 
write_node:
INSERT: 'Implement \.{\\write}'
; 
close_node:
INSERT: 'Implement \.{\\closeout}'
; 
special_node:
INSERT: 'Implement \.{\\special}'
; 
immediate_code:
INSERT: 'Implement \.{\\immediate}'
; 
set_language_code:
INSERT: 'Implement \.{\\setlanguage}'
; 
othercases confusion('ext1') 
(*this can''t happen ext1][\quad ext1*) 
endcases; 
end; 

MODULE: 'Declare procedures needed in |do_extension|'
(*PASCAL module 1349*)
procedure new_whatsit(s:small_number;w:small_number); 
var p:pointer; {the new node} 
begin p:=get_node(w); type(p):=whatsit_node; subtype(p):=s; 
link(tail):=p; tail:=p; 
end; 

MODULE: 'Declare procedures needed in |do_ext...'
(*PASCAL module 1350*)
procedure new_write_whatsit(w:small_number); 
begin new_whatsit(cur_chr,w); 
if w<>write_node_size then scan_four_bit_int 
else  begin scan_int; 
  if cur_val<0 then cur_val:=17 
  else if cur_val>15 then cur_val:=16; 
  end; 
write_stream(tail):=cur_val; 
end; 

MODULE: 'Implement \.{\\openout}'
(*PASCAL module 1351*)
begin new_write_whatsit(open_node_size); 
scan_optional_equals; scan_file_name;
 
open_name(tail):=cur_name; open_area(tail):=cur_area; open_ext(tail):=cur_ext; 
end 

MODULE: 'Implement \.{\\write}'
(*PASCAL module 1352*)
begin k:=cur_cs; new_write_whatsit(write_node_size);
 
cur_cs:=k; p:=scan_toks(false,false); write_tokens(tail):=def_ref; 
end 

MODULE: 'Implement \.{\\closeout}'
(*PASCAL module 1353*)
begin new_write_whatsit(write_node_size); write_tokens(tail):=null; 
end 

MODULE: 'Implement \.{\\special}'
(*PASCAL module 1354*)
begin new_whatsit(special_node,write_node_size); write_stream(tail):=null; 
p:=scan_toks(false,true); write_tokens(tail):=def_ref; 
end 

MODULE: 'Basic printing...'
(*PASCAL module 1355*)
procedure print_write_whatsit(s:str_number;p:pointer); 
begin print_esc(s); 
if write_stream(p)<16 then print_int(write_stream(p)) 
else if write_stream(p)=16 then print_char('*') 
(**\relax*) 
else print_char('-'); 
end; 

MODULE: 'Display the whatsit...'
(*PASCAL module 1356*)
case subtype(p) of 
open_node:begin print_write_whatsit('openout',p); 
  print_char('='); print_file_name(open_name(p),open_area(p),open_ext(p)); 
  end; 
write_node:begin print_write_whatsit('write',p); 
  print_mark(write_tokens(p)); 
  end; 
close_node:print_write_whatsit('closeout',p); 
special_node:begin print_esc('special'); 
  print_mark(write_tokens(p)); 
  end; 
language_node:begin print_esc('setlanguage'); 
  print_int(what_lang(p)); print(' (hyphenmin '); 
  print_int(what_lhm(p)); print_char(','); 
  print_int(what_rhm(p)); print_char(')'); 
  end; 
othercases print('whatsit?') 
endcases 

MODULE: 'Make a partial copy of the whatsit...'
(*PASCAL module 1357*)
case subtype(p) of 
open_node: begin r:=get_node(open_node_size); words:=open_node_size; 
  end; 
write_node,special_node: begin r:=get_node(write_node_size); 
  add_token_ref(write_tokens(p)); words:=write_node_size; 
  end; 
close_node,language_node: begin r:=get_node(small_node_size); 
  words:=small_node_size; 
  end; 
othercases confusion('ext2') 
(*this can''t happen ext2][\quad ext2*) 
endcases 

MODULE: 'Wipe out the whatsit...'
(*PASCAL module 1358*)
begin case subtype(p) of 
open_node: free_node(p,open_node_size); 
write_node,special_node: begin delete_token_ref(write_tokens(p)); 
  free_node(p,write_node_size); goto done; 
  end; 
close_node,language_node: free_node(p,small_node_size); 
othercases confusion('ext3') 
(*this can''t happen ext3][\quad ext3*) 
endcases;
 
goto done; 
end 

MODULE: 'Prepare to move whatsit |p| to the current page, then |goto contribute|'
(*PASCAL module 1364*)
goto contribute 

MODULE: 'Process whatsit |p| in |vert_break| loop, |goto not_found|'
(*PASCAL module 1365*)
goto not_found 

MODULE: 'Output the whatsit node |p| in a vlist'
(*PASCAL module 1366*)
out_what(p) 

MODULE: 'Output the whatsit node |p| in an hlist'
(*PASCAL module 1367*)
out_what(p) 

MODULE: 'Declare procedures needed in |hlist_out|, |vlist_out|'
(*PASCAL module 1368*)
procedure special_out(p:pointer); 
var old_setting:0..max_selector; {holds print |selector|} 
k:pool_pointer; {index into |str_pool|} 
begin synch_h; synch_v;
 
old_setting:=selector; selector:=new_string; 
show_token_list(link(write_tokens(p)),null,pool_size-pool_ptr); 
selector:=old_setting; 
str_room(1); 
if cur_length<256 then 
  begin dvi_out(xxx1); dvi_out(cur_length); 
  end 
else  begin dvi_out(xxx4); dvi_four(cur_length); 
  end; 
for k:=str_start[str_ptr] to pool_ptr-1 do dvi_out(so(str_pool[k])); 
pool_ptr:=str_start[str_ptr]; {erase the string} 
end; 

MODULE: 'Initialize table...'
(*PASCAL module 1369*)
text(end_write):='endwrite'; eq_level(end_write):=level_one; 
eq_type(end_write):=outer_call; equiv(end_write):=null; 

MODULE: 'Declare procedures needed in |hlist_out|, |vlist_out|'
(*PASCAL module 1370*)
procedure write_out(p:pointer); 
var old_setting:0..max_selector; {holds print |selector|} 
old_mode:integer; {saved |mode|} 
j:small_number; {write stream number} 
q,r:pointer; {temporary variables for list manipulation} 
begin 
INSERT: 'Expand macros in the token list   and make |link(def_ref)| point to the result'
; 
old_setting:=selector; j:=write_stream(p); 
if write_open[j] then selector:=j 
else  begin {write to the terminal if file isn't open} 
  if (j=17)and(selector=term_and_log) then selector:=log_only; 
  print_nl(''); 
  end; 
token_show(def_ref); print_ln; 
flush_list(def_ref); selector:=old_setting; 
end; 

MODULE: 'Expand macros in the token list and...'
(*PASCAL module 1371*)
q:=get_avail; info(q):=right_brace_token+'}';
 
r:=get_avail; link(q):=r; info(r):=end_write_token; ins_list(q);
 
begin_token_list(write_tokens(p),write_text);
 
q:=get_avail; info(q):=left_brace_token+'{'; ins_list(q); 
{now we're ready to scan 
  `\.\[$\langle\,$token list$\,\rangle$\.[\] \\endwrite]'} 
old_mode:=mode; mode:=0; 
  {disable \.[\\prevdepth], \.[\\spacefactor], \.[\\lastskip], \.[\\prevgraf]} 
cur_cs:=write_loc; q:=scan_toks(false,true); {expand macros, etc.} 
get_token;if cur_tok<>end_write_token then 
  
INSERT: 'Recover from an unbalanced write command'
; 
mode:=old_mode; 
end_token_list {conserve stack space} 

MODULE: 'Recover from an unbalanced write command'
(*PASCAL module 1372*)
begin print_err('Unbalanced write command'); 
(*Unbalanced write...*) 
help2('On this page there''s a \write with fewer real {''s than }''s.')
 
('I can''t handle that very well; good luck.'); error; 
repeat get_token; 
until cur_tok=end_write_token; 
end 

MODULE: 'Declare procedures needed in |hlist_out|, |vlist_out|'
(*PASCAL module 1373*)
procedure out_what(p:pointer); 
var j:small_number; {write stream number} 
begin case subtype(p) of 
open_node,write_node,close_node:
INSERT: 'Do some work that has been queued up   for \.{\\write}'
; 
special_node:special_out(p); 
language_node:do_nothing; 
othercases confusion('ext4') 
(*this can''t happen ext4][\quad ext4*) 
endcases; 
end; 

MODULE: 'Do some work that has been queued up...'
(*PASCAL module 1374*)
if not doing_leaders then 
  begin j:=write_stream(p); 
  if subtype(p)=write_node then write_out(p) 
  else  begin if write_open[j] then a_close(write_file[j]); 
    if subtype(p)=close_node then write_open[j]:=false 
    else if j<16 then 
      begin cur_name:=open_name(p); cur_area:=open_area(p); 
      cur_ext:=open_ext(p); 
      if cur_ext='' then cur_ext:='.tex'; 
      pack_cur_name; 
      while not a_open_out(write_file[j]) do 
        prompt_file_name('output file name','.tex'); 
      write_open[j]:=true; 
      end; 
    end; 
  end 

MODULE: 'Implement \.{\\immediate}'
(*PASCAL module 1375*)
begin get_x_token; 
if (cur_cmd=extension)and(cur_chr<=close_node) then 
  begin p:=tail; do_extension; {append a whatsit node} 
  out_what(tail); {do the action immediately} 
  flush_node_list(tail); tail:=p; link(p):=null; 
  end 
else back_input; 
end 

MODULE: 'Declare action...'
(*PASCAL module 1376*)
procedure fix_language; 
var l:ASCII_code; {the new current language} 
begin if language<=0 then l:=0 
else if language>255 then l:=0 
else l:=language; 
if l<>clang then 
  begin new_whatsit(language_node,small_node_size); 
  what_lang(tail):=l; clang:=l;
 
  what_lhm(tail):=norm_min(left_hyphen_min); 
  what_rhm(tail):=norm_min(right_hyphen_min); 
  end; 
end; 

MODULE: 'Implement \.{\\setlanguage}'
(*PASCAL module 1377*)
if abs(mode)<>hmode then report_illegal_case 
else begin new_whatsit(language_node,small_node_size); 
  scan_int; 
  if cur_val<=0 then clang:=0 
  else if cur_val>255 then clang:=0 
  else clang:=cur_val; 
  what_lang(tail):=clang; 
  what_lhm(tail):=norm_min(left_hyphen_min); 
  what_rhm(tail):=norm_min(right_hyphen_min); 
  end 

MODULE: 'Finish the extensions'
(*PASCAL module 1378*)
for k:=0 to 15 do if write_open[k] then a_close(write_file[k]) 

