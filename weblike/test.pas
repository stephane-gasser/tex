
(***PASCAL module 4***)
(*\4*)
INSERT: 'Compiler directives'

 
program TEX; {all file names are defined dynamically} 
label 
INSERT: 'Labels in the outer block'

 
const 
INSERT: 'Constants in the outer block'

 
mtype 
INSERT: 'Types in the outer block'

 
var 
INSERT: 'Global variables'

 


 
procedure initialize; {this procedure gets things started properly} 
  var 
INSERT: 'Local variables for initialization'

 
  begin 
INSERT: 'Initialize whatever \TeX\ might access'
; 
  end;

 
(*\4*)
INSERT: 'Basic printing procedures'

 
(*\4*)
INSERT: 'Error handling procedures'

 


(***PASCAL module 27***)
function a_open_in(var f:alpha_file):boolean; 
  {open a text file for input} 
begin reset(f,name_of_file,'/O'); a_open_in:=reset_OK(f); 
end; 


 
function a_open_out(var f:alpha_file):boolean; 
  {open a text file for output} 
begin rewrite(f,name_of_file,'/O'); a_open_out:=rewrite_OK(f); 
end; 


 
function b_open_in(var f:byte_file):boolean; 
  {open a binary file for input} 
begin reset(f,name_of_file,'/O'); b_open_in:=reset_OK(f); 
end; 


 
function b_open_out(var f:byte_file):boolean; 
  {open a binary file for output} 
begin rewrite(f,name_of_file,'/O'); b_open_out:=rewrite_OK(f); 
end; 


 
function w_open_in(var f:word_file):boolean; 
  {open a word file for input} 
begin reset(f,name_of_file,'/O'); w_open_in:=reset_OK(f); 
end; 


 
function w_open_out(var f:word_file):boolean; 
  {open a word file for output} 
begin rewrite(f,name_of_file,'/O'); w_open_out:=rewrite_OK(f); 
end; 


(***PASCAL module 28***)
procedure a_close(var f:alpha_file); {close a text file} 
begin close(f); 
end; 


 
procedure b_close(var f:byte_file); {close a binary file} 
begin close(f); 
end; 


 
procedure w_close(var f:word_file); {close a word file} 
begin close(f); 
end; 


(***PASCAL module 31***)
function input_ln(var f:alpha_file;bypass_eoln:boolean):boolean; 
  {inputs the next line or returns |false|} 
var last_nonblank:0..buf_size; {|last| with trailing blanks removed} 
begin if bypass_eoln then if not eof(f) then get(f); 
  {input the first character of the line into |f^|} 
last:=first; {cf.\ Matthew 19\thinspace:\thinspace30} 
if eof(f) then input_ln:=false 
else  begin last_nonblank:=first; 
  while not eoln(f) do 
    begin if last>=max_buf_stack then 
      begin max_buf_stack:=last+1; 
      if max_buf_stack=buf_size then 
        
INSERT: 'Report overflow of the input buffer, and abort'
; 
      end; 
    buffer[last]:=xord[f^]; get(f); incr(last); 
    if buffer[last-1]<>' ' then last_nonblank:=last; 
    end; 
  last:=last_nonblank; input_ln:=true; 
  end; 
end; 


(***PASCAL module 37***)
function init_terminal:boolean; {gets the terminal input started} 
label exit; 
begin t_open_in; 
loopbegin wake_up_terminal; write(term_out,'**'); update_terminal; 
(****) 
  if not input_ln(term_in,true) then {this shouldn't happen} 
    begin write_ln(term_out); 
    write(term_out,'! End of file on the terminal... why?'); 
(*End of file on the terminal*) 
    init_terminal:=false; return; 
    end; 
  loc:=first; 
  while (loc<last)and(buffer[loc]=' ') do incr(loc); 
  if loc<last then 
    begin init_terminal:=true; 
    return; {return unless the line was all blank} 
    end; 
  write_ln(term_out,'Please type the name of your input file.'); 
  end; 
exit:end; 


(***PASCAL module 43***)
function make_string : str_number; {current string enters the pool} 
begin if str_ptr=max_strings then 
  overflow('number of strings',max_strings-init_str_ptr); 
(*TeX capacity exceeded number of strings][\quad number of strings*) 
incr(str_ptr); str_start[str_ptr]:=pool_ptr; 
make_string:=str_ptr-1; 
end; 


(***PASCAL module 45***)
function str_eq_buf(s:str_number;k:integer):boolean; 
  {test equality of strings} 
label not_found; {loop exit} 
var j: pool_pointer; {running index} 
result: boolean; {result of comparison} 
begin j:=str_start[s]; 
while j<str_start[s+1] do 
  begin if so(str_pool[j])<>buffer[k] then 
    begin result:=false; goto not_found; 
    end; 
  incr(j); incr(k); 
  end; 
result:=true; 
not_found: str_eq_buf:=result; 
end; 


(***PASCAL module 46***)
function str_eq_str(s,t:str_number):boolean; 
  {test equality of strings} 
label not_found; {loop exit} 
var j,k: pool_pointer; {running indices} 
result: boolean; {result of comparison} 
begin result:=false; 
if length(s)<>length(t) then goto not_found; 
j:=str_start[s]; k:=str_start[t]; 
while j<str_start[s+1] do 
  begin if str_pool[j]<>str_pool[k] then goto not_found; 
  incr(j); incr(k); 
  end; 
result:=true; 
not_found: str_eq_str:=result; 
end; 


(***PASCAL module 47***)
init function get_strings_started:boolean; {initializes the string pool, 
  but returns |false| if something goes wrong} 
label done,exit; 
var k,l:0..255; {small indices or counters} 
m,n:text_char; {characters input from |pool_file|} 
g:str_number; {garbage} 
a:integer; {accumulator for check sum} 
c:boolean; {check sum has been checked} 
begin pool_ptr:=0; str_ptr:=0; str_start[0]:=0; 

INSERT: 'Make the first 256 strings'
; 

INSERT: 'Read the other strings from the \.{TEX.POOL} file and return |true|,   or give an error message and return |false|'
; 
exit:end; 
tini 


(***PASCAL module 66***)
procedure print_two(n:integer); {prints two least significant digits} 
begin n:=abs(n) mod 100; print_char('0'+(n div 10)); 
print_char('0'+(n mod 10)); 
end; 


(***PASCAL module 67***)
procedure print_hex(n:integer); 
  {prints a positive integer in hexadecimal form} 
var k:0..22; {index to current digit; we assume that $0\L n<16^[22]$} 
begin k:=0; print_char(''''); 
repeat dig[k]:=n mod 16; n:=n div 16; incr(k); 
until n=0; 
print_the_digs(k); 
end; 


(***PASCAL module 69***)
procedure print_roman_int(n:integer); 
label exit; 
var j,k: pool_pointer; {mysterious indices into |str_pool|} 
u,v: nonnegative_integer; {mysterious numbers} 
begin j:=str_start['m2d5c2l5x2v5i']; v:=1000; 
loop  begin while n>=v do 
    begin print_char(so(str_pool[j])); n:=n-v; 
    end; 
  if n<=0 then return; {nonpositive input produces no output} 
  k:=j+2; u:=v div (so(str_pool[k-1])-'0'); 
  if str_pool[k-1]=si('2') then 
    begin k:=k+2; u:=u div (so(str_pool[k-1])-'0'); 
    end; 
  if n+u>=v then 
    begin print_char(so(str_pool[k])); n:=n+u; 
    end 
  else  begin j:=j+2; v:=v div (so(str_pool[j-1])-'0'); 
    end; 
  end; 
exit:end; 


(***PASCAL module 70***)
procedure print_current_string; {prints a yet-unmade string} 
var j:pool_pointer; {points to current character code} 
begin j:=str_start[str_ptr]; 
while j<pool_ptr do 
  begin print_char(so(str_pool[j])); incr(j); 
  end; 
end; 


(***PASCAL module 71***)
procedure term_input; {gets a line from the terminal} 
var k:0..buf_size; {index into |buffer|} 
begin update_terminal; {now the user sees the prompt for sure} 
if not input_ln(term_in,true) then fatal_error('End of file on the terminal!'); 
(*End of file on the terminal*) 
term_offset:=0; {the user's line ended with \<\rm return>} 
decr(selector); {prepare to echo the input} 
if last<>first then for k:=first to last-1 do print(buffer[k]); 
print_ln; incr(selector); {restore previous status} 
end; 


(***PASCAL module 91***)
procedure int_error(n:integer); 
begin print(' ('); print_int(n); print_char(')'); error; 
end; 


(***PASCAL module 92***)
procedure normalize_selector; 
begin if log_opened then selector:=term_and_log 
else selector:=term_only; 
if job_name=0 then open_log_file; 
if interaction=batch_mode then decr(selector); 
end; 


(***PASCAL module 98***)
procedure pause_for_instructions; 
begin if OK_to_interrupt then 
  begin interaction:=error_stop_mode; 
  if (selector=log_only)or(selector=no_print) then 
    incr(selector); 
  print_err('Interruption'); 
(*Interruption*) 
  help3('You rang?')
 
  ('Try to insert some instructions for me (e.g.,`I\showlists''),')
 
  ('unless you just want to quit by typing `X''.'); 
  deletions_allowed:=false; error; deletions_allowed:=true; 
  interrupt:=0; 
  end; 
end; 


(***PASCAL module 100***)
function half(x:integer):integer; 
begin if odd(x) then half:=(x+1) div 2 
else half:=x div 2; 
end; 


(***PASCAL module 102***)
function round_decimals(k:small_number) : scaled; 
  {converts a decimal fraction} 
var a:integer; {the accumulator} 
begin a:=0; 
while k>0 do 
  begin decr(k); a:=(a+dig[k]*two) div 10; 
  end; 
round_decimals:=(a+1) div 2; 
end; 


(***PASCAL module 103***)
procedure print_scaled(s:scaled); {prints scaled real, rounded to five 
  digits} 
var delta:scaled; {amount of allowable inaccuracy} 
begin if s<0 then 
  begin print_char('-'); negate(s); {print the sign, if negative} 
  end; 
print_int(s div unity); {print the integer part} 
print_char('.'); 
s:=10*(s mod unity)+5; delta:=10; 
repeat if delta>unity then s:=s+32768-50000; {round the last digit} 
print_char('0'+(s div unity)); s:=10*(s mod unity); delta:=delta*10; 
until s<=delta; 
end; 


(***PASCAL module 105***)
function mult_and_add(n:integer;x,y,max_answer:scaled):scaled; 
begin if n<0 then 
  begin negate(x); negate(n); 
  end; 
if n=0 then mult_and_add:=y 
else if ((x<=(max_answer-y) div n)and(-x<=(max_answer+y) div n)) then 
  mult_and_add:=n*x+y 
else  begin arith_error:=true; mult_and_add:=0; 
  end; 
end; 


(***PASCAL module 106***)
function x_over_n(x:scaled;n:integer):scaled; 
var negative:boolean; {should |remainder| be negated?} 
begin negative:=false; 
if n=0 then 
  begin arith_error:=true; x_over_n:=0; remainder:=x; 
  end 
else  begin if n<0 then 
    begin negate(x); negate(n); negative:=true; 
    end; 
  if x>=0 then 
    begin x_over_n:=x div n; remainder:=x mod n; 
    end 
  else  begin x_over_n:=-((-x) div n); remainder:=-((-x) mod n); 
    end; 
  end; 
if negative then negate(remainder); 
end; 


(***PASCAL module 107***)
function xn_over_d(x:scaled; n,d:integer):scaled; 
var positive:boolean; {was |x>=0|?} 
t,u,v:nonnegative_integer; {intermediate quantities} 
begin if x>=0 then positive:=true 
else  begin negate(x); positive:=false; 
  end; 
t:=(x mod 32768)*n; 
u:=(x div 32768)*n+(t div 32768); 
v:=(u mod d)*32768 + (t mod 32768); 
if u div d>=32768 then arith_error:=true 
else u:=32768*(u div d) + (v div d); 
if positive then 
  begin xn_over_d:=u; remainder:=v mod d; 
  end 
else  begin xn_over_d:=-u; remainder:=-(v mod d); 
  end; 
end; 


(***PASCAL module 108***)
function badness(t,s:scaled):halfword; {compute badness, given |t>=0|} 
var r:integer; {approximation to $\alpha t/s$, where $\alpha^3\approx 
  100\cdot2^[18]$} 
begin if t=0 then badness:=0 
else if s<=0 then badness:=inf_bad 
else  begin if t<=7230584 then  r:=(t*297) div s {$297^3=99.94\times2^[18]$} 
  else if s>=1663497 then r:=t div (s div 297) 
  else r:=t; 
  if r>1290 then badness:=inf_bad {$1290^3<2^[31]<1291^3$} 
  else badness:=(r*r*r+131072) div 262144; 
  end; {that was $r^3/2^[18]$, rounded to the nearest integer} 
end; 


(***PASCAL module 114***)
debug procedure print_word(w:memory_word); 
  {prints |w| in all ways} 
begin print_int(w.int); print_char(' ');
 
print_scaled(w.sc); print_char(' ');
 
print_scaled(round(unity*float(w.gr))); print_ln;
 
(*real multiplication*) 
print_int(w.hh.lh); print_char('='); print_int(w.hh.b0); print_char(':'); 
print_int(w.hh.b1); print_char(';'); print_int(w.hh.rh); print_char(' ');
 
print_int(w.qqqq.b0); print_char(':'); print_int(w.qqqq.b1); print_char(':'); 
print_int(w.qqqq.b2); print_char(':'); print_int(w.qqqq.b3); 
end; 
gubed 


(***PASCAL module 119***)

INSERT: 'Declare the procedure called |show_token_list|'

 

INSERT: 'Declare the procedure called |runaway|'



(***PASCAL module 120***)
function get_avail : pointer; {single-word node allocation} 
var p:pointer; {the new node being got} 
begin p:=avail; {get top location in the |avail| stack} 
if p<>null then avail:=link(avail) {and pop it off} 
else if mem_end<mem_max then {or go into virgin territory} 
  begin incr(mem_end); p:=mem_end; 
  end 
else   begin decr(hi_mem_min); p:=hi_mem_min; 
  if hi_mem_min<=lo_mem_max then 
    begin runaway; {if memory is exhausted, display possible runaway text} 
    overflow('main memory size',mem_max+1-mem_min); 
      {quit; all one-word nodes are busy} 
(*TeX capacity exceeded main memory size][\quad main memory size*) 
    end; 
  end; 
link(p):=null; {provide an oft-desired initialization of the new node} 
stat incr(dyn_used);tats;{maintain statistics} 
get_avail:=p; 
end; 


(***PASCAL module 123***)
procedure flush_list(p:pointer); {makes list of single-word nodes 
  available} 
var q,r:pointer; {list traversers} 
begin if p<>null then 
  begin r:=p; 
  repeat q:=r; r:=link(r); stat decr(dyn_used);tats
 
  until r=null; {now |q| is the last node on the list} 
  link(q):=avail; avail:=p; 
  end; 
end; 


(***PASCAL module 125***)
function get_node(s:integer):pointer; {variable-size node allocation} 
label found,exit,restart; 
var p:pointer; {the node currently under inspection} 
q:pointer; {the node physically after node |p|} 
r:integer; {the newly allocated node, or a candidate for this honor} 
t:integer; {temporary register} 
begin restart: p:=rover; {start at some free node in the ring} 
repeat 
INSERT: 'Try to allocate within node |p| and its physical successors,   and |goto found| if allocation was possible'
; 
(*inner loop*) 
p:=rlink(p); {move to the next node in the ring} 
until p=rover; {repeat until the whole list has been traversed} 
if s=1073741824 then 
  begin get_node:=max_halfword; return; 
  end; 
if lo_mem_max+2<hi_mem_min then if lo_mem_max+2<=mem_bot+max_halfword then 
  
INSERT: 'Grow more variable-size memory and |goto restart|'
; 
overflow('main memory size',mem_max+1-mem_min); 
  {sorry, nothing satisfactory is left} 
(*TeX capacity exceeded main memory size][\quad main memory size*) 
found: link(r):=null; {this node is now nonempty} 
stat var_used:=var_used+s; {maintain usage statistics} 
tats;
 
get_node:=r; 
exit:end; 


(***PASCAL module 130***)
procedure free_node(p:pointer; s:halfword); {variable-size node 
  liberation} 
var q:pointer; {|llink(rover)|} 
begin node_size(p):=s; link(p):=empty_flag; 
q:=llink(rover); llink(p):=q; rlink(p):=rover; {set both links} 
llink(rover):=p; rlink(q):=p; {insert |p| into the ring} 
stat var_used:=var_used-s;tats;{maintain statistics} 
end; 


(***PASCAL module 131***)
init procedure sort_avail; {sorts the available variable-size nodes 
  by location} 
var p,q,r: pointer; {indices into |mem|} 
old_rover:pointer; {initial |rover| setting} 
begin p:=get_node(1073741824); {merge adjacent free areas} 
p:=rlink(rover); rlink(rover):=max_halfword; old_rover:=rover; 
while p<>old_rover do 
INSERT: 'Sort \(p)|p| into the list starting at |rover|   and advance |p| to |rlink(p)|'
; 
p:=rover; 
while rlink(p)<>max_halfword do 
  begin llink(rlink(p)):=p; p:=rlink(p); 
  end; 
rlink(p):=rover; llink(rover):=p; 
end; 
tini 


(***PASCAL module 136***)
function new_null_box:pointer; {creates a new box node} 
var p:pointer; {the new node} 
begin p:=get_node(box_node_size); type(p):=hlist_node; 
subtype(p):=min_quarterword; 
width(p):=0; depth(p):=0; height(p):=0; shift_amount(p):=0; list_ptr(p):=null; 
glue_sign(p):=normal; glue_order(p):=normal; set_glue_ratio_zero(glue_set(p)); 
new_null_box:=p; 
end; 


(***PASCAL module 139***)
function new_rule:pointer; 
var p:pointer; {the new node} 
begin p:=get_node(rule_node_size); type(p):=rule_node; 
subtype(p):=0; {the |subtype| is not used} 
width(p):=null_flag; depth(p):=null_flag; height(p):=null_flag; 
new_rule:=p; 
end; 


(***PASCAL module 144***)
function new_ligature(f,c:quarterword; q:pointer):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=ligature_node; 
font(lig_char(p)):=f; character(lig_char(p)):=c; lig_ptr(p):=q; 
subtype(p):=0; new_ligature:=p; 
end; 


 
function new_lig_item(c:quarterword):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); character(p):=c; lig_ptr(p):=null; 
new_lig_item:=p; 
end; 


(***PASCAL module 145***)
function new_disc:pointer; {creates an empty |disc_node|} 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=disc_node; 
replace_count(p):=0; pre_break(p):=null; post_break(p):=null; 
new_disc:=p; 
end; 


(***PASCAL module 147***)
function new_math(w:scaled;s:small_number):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=math_node; 
subtype(p):=s; width(p):=w; new_math:=p; 
end; 


(***PASCAL module 151***)
function new_spec(p:pointer):pointer; {duplicates a glue specification} 
var q:pointer; {the new spec} 
begin q:=get_node(glue_spec_size);
 
mem[q]:=mem[p]; glue_ref_count(q):=null;
 
width(q):=width(p); stretch(q):=stretch(p); shrink(q):=shrink(p); 
new_spec:=q; 
end; 


(***PASCAL module 152***)
function new_param_glue(n:small_number):pointer; 
var p:pointer; {the new node} 
q:pointer; {the glue specification} 
begin p:=get_node(small_node_size); type(p):=glue_node; subtype(p):=n+1; 
leader_ptr(p):=null;
 
q:=
INSERT: 'Current |mem| equivalent of glue parameter number |n|'
(*@>;*)(*@>;*) 
glue_ptr(p):=q; incr(glue_ref_count(q)); 
new_param_glue:=p; 
end; 


(***PASCAL module 153***)
function new_glue(q:pointer):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=glue_node; subtype(p):=normal; 
leader_ptr(p):=null; glue_ptr(p):=q; incr(glue_ref_count(q)); 
new_glue:=p; 
end; 


(***PASCAL module 154***)
function new_skip_param(n:small_number):pointer; 
var p:pointer; {the new node} 
begin temp_ptr:=new_spec(
INSERT: 'Current |mem| equivalent of glue parameter...'
); 
p:=new_glue(temp_ptr); glue_ref_count(temp_ptr):=null; subtype(p):=n+1; 
new_skip_param:=p; 
end; 


(***PASCAL module 156***)
function new_kern(w:scaled):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=kern_node; 
subtype(p):=normal; 
width(p):=w; 
new_kern:=p; 
end; 


(***PASCAL module 158***)
function new_penalty(m:integer):pointer; 
var p:pointer; {the new node} 
begin p:=get_node(small_node_size); type(p):=penalty_node; 
subtype(p):=0; {the |subtype| is not used} 
penalty(p):=m; new_penalty:=p; 
end; 


(***PASCAL module 167***)
debug procedure check_mem(print_locs : boolean); 
label done1,done2; {loop exits} 
var p,q:pointer; {current locations of interest in |mem|} 
clobbered:boolean; {is something amiss?} 
begin for p:=mem_min to lo_mem_max do free[p]:=false; {you can probably 
  do this faster} 
for p:=hi_mem_min to mem_end do free[p]:=false; {ditto} 

INSERT: 'Check single-word |avail| list'
; 

INSERT: 'Check variable-size |avail| list'
; 

INSERT: 'Check flags of unavailable nodes'
; 
if print_locs then 
INSERT: 'Print newly busy locations'
; 
for p:=mem_min to lo_mem_max do was_free[p]:=free[p]; 
for p:=hi_mem_min to mem_end do was_free[p]:=free[p]; 
  {|was_free:=free| might be faster} 
was_mem_end:=mem_end; was_lo_max:=lo_mem_max; was_hi_min:=hi_mem_min; 
end; 
gubed 


(***PASCAL module 172***)
debug procedure search_mem(p:pointer); {look for pointers to |p|} 
var q:integer; {current position being searched} 
begin for q:=mem_min to lo_mem_max do 
  begin if link(q)=p then 
    begin print_nl('LINK('); print_int(q); print_char(')'); 
    end; 
  if info(q)=p then 
    begin print_nl('INFO('); print_int(q); print_char(')'); 
    end; 
  end; 
for q:=hi_mem_min to mem_end do 
  begin if link(q)=p then 
    begin print_nl('LINK('); print_int(q); print_char(')'); 
    end; 
  if info(q)=p then 
    begin print_nl('INFO('); print_int(q); print_char(')'); 
    end; 
  end; 

INSERT: 'Search |eqtb| for equivalents equal to |p|'
; 

INSERT: 'Search |save_stack| for equivalents that point to |p|'
; 

INSERT: 'Search |hyph_list| for pointers to |p|'
; 
end; 
gubed 


(***PASCAL module 174***)
procedure short_display(p:integer); {prints highlights of list |p|} 
var n:integer; {for replacement counts} 
begin while p>mem_min do 
  begin if is_char_node(p) then 
    begin if p<=mem_end then 
      begin if font(p)<>font_in_short_display then 
        begin if (font(p)<font_base)or(font(p)>font_max) then 
          print_char('*') 
(**\relax*) 
        else 
INSERT: 'Print the font identifier for |font(p)|'
; 
        print_char(' '); font_in_short_display:=font(p); 
        end; 
      print_ASCII(qo(character(p))); 
      end; 
    end 
  else 
INSERT: 'Print a short indication of the contents of node |p|'
; 
  p:=link(p); 
  end; 
end; 


(***PASCAL module 176***)
procedure print_font_and_char(p:integer); {prints |char_node| data} 
begin if p>mem_end then print_esc('CLOBBERED.') 
else  begin if (font(p)<font_base)or(font(p)>font_max) then print_char('*') 
(**\relax*) 
  else 
INSERT: 'Print the font identifier for |font(p)|'
; 
  print_char(' '); print_ASCII(qo(character(p))); 
  end; 
end; 


 
procedure print_mark(p:integer); {prints token list data in braces} 
begin print_char('{'); 
if (p<hi_mem_min)or(p>mem_end) then print_esc('CLOBBERED.') 
else show_token_list(link(p),null,max_print_line-10); 
print_char('}'); 
end; 


 
procedure print_rule_dimen(d:scaled); {prints dimension in rule node} 
begin if is_running(d) then print_char('*') else print_scaled(d); 
(**\relax*) 
end; 


(***PASCAL module 177***)
procedure print_glue(d:scaled;order:integer;s:str_number); 
  {prints a glue component} 
begin print_scaled(d); 
if (order<normal)or(order>filll) then print('foul') 
else if order>normal then 
  begin print('fil'); 
  while order>fil do 
    begin print_char('l'); decr(order); 
    end; 
  end 
else if s<>0 then print(s); 
end; 


(***PASCAL module 178***)
procedure print_spec(p:integer;s:str_number); 
  {prints a glue specification} 
begin if (p<mem_min)or(p>=lo_mem_max) then print_char('*') 
(**\relax*) 
else  begin print_scaled(width(p)); 
  if s<>0 then print(s); 
  if stretch(p)<>0 then 
    begin print(' plus '); print_glue(stretch(p),stretch_order(p),s); 
    end; 
  if shrink(p)<>0 then 
    begin print(' minus '); print_glue(shrink(p),shrink_order(p),s); 
    end; 
  end; 
end; 


(***PASCAL module 179***)

INSERT: 'Declare procedures needed for displaying the elements of mlists'
; 

INSERT: 'Declare the procedure called |print_skip_param|'



(***PASCAL module 182***)
procedure show_node_list(p:integer); {prints a node list symbolically} 
label exit; 
var n:integer; {the number of items already printed at this level} 
g:real; {a glue ratio, as a floating point number} 
begin if cur_length>depth_threshold then 
  begin if p>null then print(' []'); 
    {indicate that there's been some truncation} 
  return; 
  end; 
n:=0; 
while p>mem_min do 
  begin print_ln; print_current_string; {display the nesting history} 
  if p>mem_end then {pointer out of range} 
    begin print('Bad link, display aborted.'); return; 
(*Bad link...*) 
    end; 
  incr(n); if n>breadth_max then {time to stop} 
    begin print('etc.'); return; 
(*etc*) 
    end; 
  
INSERT: 'Display node |p|'
; 
  p:=link(p); 
  end; 
exit: 
end; 


(***PASCAL module 198***)
procedure show_box(p:pointer); 
begin 
INSERT: 'Assign the values |depth_threshold:=show_box_depth| and   |breadth_max:=show_box_breadth|'
; 
if breadth_max<=0 then breadth_max:=5; 
if pool_ptr+depth_threshold>=pool_size then 
  depth_threshold:=pool_size-pool_ptr-1; 
  {now there's enough room for prefix string} 
show_node_list(p); {the show starts at |p|} 
print_ln; 
end; 


(***PASCAL module 200***)
procedure delete_token_ref(p:pointer); {|p| points to the reference count 
  of a token list that is losing one reference} 
begin if token_ref_count(p)=null then flush_list(p) 
else decr(token_ref_count(p)); 
end; 


(***PASCAL module 201***)
procedure delete_glue_ref(p:pointer); {|p| points to a glue specification} 
fast_delete_glue_ref(p); 


(***PASCAL module 202***)
procedure flush_node_list(p:pointer); {erase list of nodes starting at |p|} 
label done; {go here when node |p| has been freed} 
var q:pointer; {successor to node |p|} 
begin while p<>null do 
(*inner loop*) 
  begin q:=link(p); 
  if is_char_node(p) then free_avail(p) 
  else  begin case type(p) of 
    hlist_node,vlist_node,unset_node: begin flush_node_list(list_ptr(p)); 
      free_node(p,box_node_size); goto done; 
      end; 
    rule_node: begin free_node(p,rule_node_size); goto done; 
      end; 
    ins_node: begin flush_node_list(ins_ptr(p)); 
      delete_glue_ref(split_top_ptr(p)); 
      free_node(p,ins_node_size); goto done; 
      end; 
    whatsit_node: 
INSERT: 'Wipe out the whatsit node |p| and |goto done|'
; 
    glue_node: begin fast_delete_glue_ref(glue_ptr(p)); 
      if leader_ptr(p)<>null then flush_node_list(leader_ptr(p)); 
      end; 
    kern_node,math_node,penalty_node: do_nothing; 
    ligature_node: flush_node_list(lig_ptr(p)); 
    mark_node: delete_token_ref(mark_ptr(p)); 
    disc_node: begin flush_node_list(pre_break(p)); 
      flush_node_list(post_break(p)); 
      end; 
    adjust_node: flush_node_list(adjust_ptr(p)); 
    (*\4*)
INSERT: 'Cases of |flush_node_list| that arise in mlists only'
; 
    othercases confusion('flushing') 
(*this can''t happen flushing][\quad flushing*) 
    endcases;
 
    free_node(p,small_node_size); 
    done:end; 
  p:=q; 
  end; 
end; 


(***PASCAL module 204***)
function copy_node_list(p:pointer):pointer; {makes a duplicate of the 
  node list that starts at |p| and returns a pointer to the new list} 
var h:pointer; {temporary head of copied list} 
q:pointer; {previous position in new list} 
r:pointer; {current node being fabricated for new list} 
words:0..5; {number of words remaining to be copied} 
begin h:=get_avail; q:=h; 
while p<>null do 
  begin 
INSERT: 'Make a copy of node |p| in node |r|'
; 
  link(q):=r; q:=r; p:=link(p); 
  end; 
link(q):=null; q:=link(h); free_avail(h); 
copy_node_list:=q; 
end; 


(***PASCAL module 211***)
procedure print_mode(m:integer); {prints the mode represented by |m|} 
begin if m>0 then 
  case m div (max_command+1) of 
  0:print('vertical'); 
  1:print('horizontal'); 
  2:print('display math'); 
  end 
else if m=0 then print('no') 
else  case (-m) div (max_command+1) of 
  0:print('internal vertical'); 
  1:print('restricted horizontal'); 
  2:print('math'); 
  end; 
print(' mode'); 
end; 


(***PASCAL module 216***)
procedure push_nest; {enter a new semantic level, save the old} 
begin if nest_ptr>max_nest_stack then 
  begin max_nest_stack:=nest_ptr; 
  if nest_ptr=nest_size then overflow('semantic nest size',nest_size); 
(*TeX capacity exceeded semantic nest size][\quad semantic nest size*) 
  end; 
nest[nest_ptr]:=cur_list; {stack the record} 
incr(nest_ptr); head:=get_avail; tail:=head; prev_graf:=0; mode_line:=line; 
end; 


(***PASCAL module 217***)
procedure pop_nest; {leave a semantic level, re-enter the old} 
begin free_avail(head); decr(nest_ptr); cur_list:=nest[nest_ptr]; 
end; 


(***PASCAL module 218***)
procedure print_totals; forward;(*\2*) 
procedure show_activities; 
var p:0..nest_size; {index into |nest|} 
m:-mmode..mmode; {mode} 
a:memory_word; {auxiliary} 
q,r:pointer; {for showing the current page} 
t:integer; {ditto} 
begin nest[nest_ptr]:=cur_list; {put the top level into the array} 
print_nl(''); print_ln; 
for p:=nest_ptr downto 0 do 
  begin m:=nest[p].mode_field; a:=nest[p].aux_field; 
  print_nl('### '); print_mode(m); 
  print(' entered at line '); print_int(abs(nest[p].ml_field)); 
  if m=hmode then if nest[p].pg_field <> 8585216 then 
    begin print(' (language'); print_int(nest[p].pg_field mod 0 
    print(':hyphenmin'); print_int(nest[p].pg_field div 0 
    print_char(','); print_int((nest[p].pg_field div 0 mod 0 
    print_char(')'); 
    end; 
  if nest[p].ml_field<0 then print(' (\output routine)'); 
  if p=0 then 
    begin 
INSERT: 'Show the status of the current page'
; 
    if link(contrib_head)<>null then 
      print_nl('### recent contributions:'); 
    end; 
  show_box(link(nest[p].head_field)); 
  
INSERT: 'Show the auxiliary field, |a|'
; 
  end; 
end; 


(***PASCAL module 237***)
procedure print_param(n:integer); 
begin case n of 
pretolerance_code:print_esc('pretolerance'); 
tolerance_code:print_esc('tolerance'); 
line_penalty_code:print_esc('linepenalty'); 
hyphen_penalty_code:print_esc('hyphenpenalty'); 
ex_hyphen_penalty_code:print_esc('exhyphenpenalty'); 
club_penalty_code:print_esc('clubpenalty'); 
widow_penalty_code:print_esc('widowpenalty'); 
display_widow_penalty_code:print_esc('displaywidowpenalty'); 
broken_penalty_code:print_esc('brokenpenalty'); 
bin_op_penalty_code:print_esc('binoppenalty'); 
rel_penalty_code:print_esc('relpenalty'); 
pre_display_penalty_code:print_esc('predisplaypenalty'); 
post_display_penalty_code:print_esc('postdisplaypenalty'); 
inter_line_penalty_code:print_esc('interlinepenalty'); 
double_hyphen_demerits_code:print_esc('doublehyphendemerits'); 
final_hyphen_demerits_code:print_esc('finalhyphendemerits'); 
adj_demerits_code:print_esc('adjdemerits'); 
mag_code:print_esc('mag'); 
delimiter_factor_code:print_esc('delimiterfactor'); 
looseness_code:print_esc('looseness'); 
time_code:print_esc('time'); 
day_code:print_esc('day'); 
month_code:print_esc('month'); 
year_code:print_esc('year'); 
show_box_breadth_code:print_esc('showboxbreadth'); 
show_box_depth_code:print_esc('showboxdepth'); 
hbadness_code:print_esc('hbadness'); 
vbadness_code:print_esc('vbadness'); 
pausing_code:print_esc('pausing'); 
tracing_online_code:print_esc('tracingonline'); 
tracing_macros_code:print_esc('tracingmacros'); 
tracing_stats_code:print_esc('tracingstats'); 
tracing_paragraphs_code:print_esc('tracingparagraphs'); 
tracing_pages_code:print_esc('tracingpages'); 
tracing_output_code:print_esc('tracingoutput'); 
tracing_lost_chars_code:print_esc('tracinglostchars'); 
tracing_commands_code:print_esc('tracingcommands'); 
tracing_restores_code:print_esc('tracingrestores'); 
uc_hyph_code:print_esc('uchyph'); 
output_penalty_code:print_esc('outputpenalty'); 
max_dead_cycles_code:print_esc('maxdeadcycles'); 
hang_after_code:print_esc('hangafter'); 
floating_penalty_code:print_esc('floatingpenalty'); 
global_defs_code:print_esc('globaldefs'); 
cur_fam_code:print_esc('fam'); 
escape_char_code:print_esc('escapechar'); 
default_hyphen_char_code:print_esc('defaulthyphenchar'); 
default_skew_char_code:print_esc('defaultskewchar'); 
end_line_char_code:print_esc('endlinechar'); 
new_line_char_code:print_esc('newlinechar'); 
language_code:print_esc('language'); 
left_hyphen_min_code:print_esc('lefthyphenmin'); 
right_hyphen_min_code:print_esc('righthyphenmin'); 
holding_inserts_code:print_esc('holdinginserts'); 
error_context_lines_code:print_esc('errorcontextlines'); 
othercases print('[unknown integer parameter!]') 
endcases; 
end; 


(***PASCAL module 241***)
procedure fix_date_and_time; 
begin time:=12*60; {minutes since midnight} 
day:=4; {fourth day of the month} 
month:=7; {seventh month of the year} 
year:=1776; {Anno Domini} 
end; 


(***PASCAL module 245***)
procedure begin_diagnostic; {prepare to do some tracing} 
begin old_setting:=selector; 
if (tracing_online<=0)and(selector=term_and_log) then 
  begin decr(selector); 
  if history=spotless then history:=warning_issued; 
  end; 
end; 


 
procedure end_diagnostic(blank_line:boolean); 
  {restore proper conditions after tracing} 
begin print_nl(''); 
if blank_line then print_ln; 
selector:=old_setting; 
end; 


(***PASCAL module 247***)
procedure print_length_param(n:integer); 
begin case n of 
par_indent_code:print_esc('parindent'); 
math_surround_code:print_esc('mathsurround'); 
line_skip_limit_code:print_esc('lineskiplimit'); 
hsize_code:print_esc('hsize'); 
vsize_code:print_esc('vsize'); 
max_depth_code:print_esc('maxdepth'); 
split_max_depth_code:print_esc('splitmaxdepth'); 
box_max_depth_code:print_esc('boxmaxdepth'); 
hfuzz_code:print_esc('hfuzz'); 
vfuzz_code:print_esc('vfuzz'); 
delimiter_shortfall_code:print_esc('delimitershortfall'); 
null_delimiter_space_code:print_esc('nulldelimiterspace'); 
script_space_code:print_esc('scriptspace'); 
pre_display_size_code:print_esc('predisplaysize'); 
display_width_code:print_esc('displaywidth'); 
display_indent_code:print_esc('displayindent'); 
overfull_rule_code:print_esc('overfullrule'); 
hang_indent_code:print_esc('hangindent'); 
h_offset_code:print_esc('hoffset'); 
v_offset_code:print_esc('voffset'); 
emergency_stretch_code:print_esc('emergencystretch'); 
othercases print('[unknown dimen parameter!]') 
endcases; 
end; 


(***PASCAL module 252***)
(*\4*)@<Declare the procedure called |print_cmd_chr|@>;
 
stat procedure show_eqtb(n:pointer); 
begin if n<active_base then print_char('?') {this can''t happen} 
else if n<glue_base then 
INSERT: 'Show equivalent |n|, in region 1 or 2'

else if n<local_base then 
INSERT: 'Show equivalent |n|, in region 3'

else if n<int_base then 
INSERT: 'Show equivalent |n|, in region 4'

else if n<dimen_base then 
INSERT: 'Show equivalent |n|, in region 5'

else if n<=eqtb_size then 
INSERT: 'Show equivalent |n|, in region 6'

else print_char('?'); {this can''t happen either} 
end; 
tats 


(***PASCAL module 259***)
function id_lookup(j,l:integer):pointer; {search the hash table} 
label found; {go here if you found it} 
var h:integer; {hash code} 
d:integer; {number of characters in incomplete current string} 
p:pointer; {index in |hash| array} 
k:pointer; {index in |buffer| array} 
begin 
INSERT: 'Compute the hash code |h|'
; 
p:=h+hash_base; {we start searching here; note that |0<=h<hash_prime|} 
loopbegin if text(p)>0 then if length(text(p))=l then 
    if str_eq_buf(text(p),j) then goto found; 
  if next(p)=0 then 
    begin if no_new_control_sequence then 
      p:=undefined_control_sequence 
    else 
INSERT: 'Insert a new control sequence after |p|, then make       |p| point to it'
; 
    goto found; 
    end; 
  p:=next(p); 
  end; 
found: id_lookup:=p; 
end; 


(***PASCAL module 264***)
init procedure primitive(s:str_number;c:quarterword;o:halfword); 
var k:pool_pointer; {index into |str_pool|} 
j:small_number; {index into |buffer|} 
l:small_number; {length of the string} 
begin if s<256 then cur_val:=s+single_base 
else  begin k:=str_start[s]; l:=str_start[s+1]-k; 
    {we will move |s| into the (empty) |buffer|} 
  for j:=0 to l-1 do buffer[j]:=so(str_pool[k+j]); 
  cur_val:=id_lookup(0,l); {|no_new_control_sequence| is |false|} 
  flush_string; text(cur_val):=s; {we don't want to have the string twice} 
  end; 
eq_level(cur_val):=level_one; eq_type(cur_val):=c; equiv(cur_val):=o; 
end; 
tini 


(***PASCAL module 274***)
procedure new_save_level(c:group_code); {begin a new level of grouping} 
begin check_full_save_stack; 
save_type(save_ptr):=level_boundary; save_level(save_ptr):=cur_group; 
save_index(save_ptr):=cur_boundary; 
if cur_level=max_quarterword then overflow('grouping levels', 
(*TeX capacity exceeded grouping levels][\quad grouping levels*) 
  max_quarterword-min_quarterword); 
  {quit if |(cur_level+1)| is too big to be stored in |eqtb|} 
cur_boundary:=save_ptr; incr(cur_level); incr(save_ptr); cur_group:=c; 
end; 


(***PASCAL module 275***)
procedure eq_destroy(w:memory_word); {gets ready to forget |w|} 
var q:pointer; {|equiv| field of |w|} 
begin case eq_type_field(w) of 
call,long_call,outer_call,long_outer_call: delete_token_ref(equiv_field(w)); 
glue_ref: delete_glue_ref(equiv_field(w)); 
shape_ref: begin q:=equiv_field(w); {we need to free a \.[\\parshape] block} 
  if q<>null then free_node(q,info(q)+info(q)+1); 
  end; {such a block is |2n+1| words long, where |n=info(q)|} 
box_ref: flush_node_list(equiv_field(w)); 
othercases do_nothing 
endcases; 
end; 


(***PASCAL module 276***)
procedure eq_save(p:pointer;l:quarterword); {saves |eqtb[p]|} 
begin check_full_save_stack; 
if l=level_zero then save_type(save_ptr):=restore_zero 
else  begin save_stack[save_ptr]:=eqtb[p]; incr(save_ptr); 
  save_type(save_ptr):=restore_old_value; 
  end; 
save_level(save_ptr):=l; save_index(save_ptr):=p; incr(save_ptr); 
end; 


(***PASCAL module 277***)
procedure eq_define(p:pointer;t:quarterword;e:halfword); 
  {new data for |eqtb|} 
begin if eq_level(p)=cur_level then eq_destroy(eqtb[p]) 
else if cur_level>level_one then eq_save(p,eq_level(p)); 
eq_level(p):=cur_level; eq_type(p):=t; equiv(p):=e; 
end; 


(***PASCAL module 278***)
procedure eq_word_define(p:pointer;w:integer); 
begin if xeq_level[p]<>cur_level then 
  begin eq_save(p,xeq_level[p]); xeq_level[p]:=cur_level; 
  end; 
eqtb[p].int:=w; 
end; 


(***PASCAL module 279***)
procedure geq_define(p:pointer;t:quarterword;e:halfword); 
  {global |eq_define|} 
begin eq_destroy(eqtb[p]); 
eq_level(p):=level_one; eq_type(p):=t; equiv(p):=e; 
end; 


 
procedure geq_word_define(p:pointer;w:integer); {global |eq_word_define|} 
begin eqtb[p].int:=w; xeq_level[p]:=level_one; 
end; 


(***PASCAL module 280***)
procedure save_for_after(t:halfword); 
begin if cur_level>level_one then 
  begin check_full_save_stack; 
  save_type(save_ptr):=insert_token; save_level(save_ptr):=level_zero; 
  save_index(save_ptr):=t; incr(save_ptr); 
  end; 
end; 


(***PASCAL module 281***)
(*\4*)@<Declare the procedure called |restore_trace|@>;
 
procedure back_input; forward; (*\2*) 
procedure unsave; {pops the top level off the save stack} 
label done; 
var p:pointer; {position to be restored} 
l:quarterword; {saved level, if in fullword regions of |eqtb|} 
t:halfword; {saved value of |cur_tok|} 
begin if cur_level>level_one then 
  begin decr(cur_level); 
  
INSERT: 'Clear off top level from |save_stack|'
; 
  end 
else confusion('curlevel'); {|unsave| is not used when |cur_group=bottom_level|} 
(*this can''t happen curlevel][\quad curlevel*) 
end; 


(***PASCAL module 288***)
procedure prepare_mag; 
begin if (mag_set>0)and(mag<>mag_set) then 
  begin print_err('Incompatible magnification ('); print_int(mag); 
(*Incompatible magnification*) 
  print(');'); print_nl(' the previous value will be retained'); 
  help2('I can handle only one magnification ratio per job. So I''ve')
 
  ('reverted to the magnification you used earlier on this run.');
 
  int_error(mag_set); 
  geq_word_define(int_base+mag_code,mag_set); {|mag:=mag_set|} 
  end; 
if (mag<=0)or(mag>32768) then 
  begin print_err('Illegal magnification has been changed to 1000');
 
(*Illegal magnification...*) 
  help1('The magnification ratio must be between 1 and 32768.'); 
  int_error(mag); geq_word_define(int_base+mag_code,1000); 
  end; 
mag_set:=mag; 
end; 


(***PASCAL module 295***)
procedure token_show(p:pointer); 
begin if p<>null then show_token_list(link(p),null,10000000); 
end; 


(***PASCAL module 296***)
procedure print_meaning; 
begin print_cmd_chr(cur_cmd,cur_chr); 
if cur_cmd>=call then 
  begin print_char(':'); print_ln; token_show(cur_chr); 
  end 
else if cur_cmd=top_bot_mark then 
  begin print_char(':'); print_ln; 
  token_show(cur_mark[cur_chr]); 
  end; 
end; 


(***PASCAL module 299***)
procedure show_cur_cmd_chr; 
begin begin_diagnostic; print_nl('{'); 
if mode<>shown_mode then 
  begin print_mode(mode); print(': '); shown_mode:=mode; 
  end; 
print_cmd_chr(cur_cmd,cur_chr); print_char('}'); 
end_diagnostic(false); 
end; 


(***PASCAL module 311***)
procedure show_context; {prints where the scanner is} 
label done; 
var old_setting:0..max_selector; {saved |selector| setting} 
nn:integer; {number of contexts shown so far, less one} 
bottom_line:boolean; {have we reached the final context to be shown?} 

INSERT: 'Local variables for formatting calculations'

 
begin base_ptr:=input_ptr; input_stack[base_ptr]:=cur_input; 
  {store current state} 
nn:=-1; bottom_line:=false; 
loopbegin cur_input:=input_stack[base_ptr]; {enter into the context} 
  if (state<>token_list) then 
    if (name>17) or (base_ptr=0) then bottom_line:=true; 
  if (base_ptr=input_ptr)or bottom_line or(nn<error_context_lines) then 
    
INSERT: 'Display the current context'

  else if nn=error_context_lines then 
    begin print_nl('...'); incr(nn); {omitted if |error_context_lines<0|} 
    end; 
  if bottom_line then goto done; 
  decr(base_ptr); 
  end; 
done: cur_input:=input_stack[input_ptr]; {restore original state} 
end; 


(***PASCAL module 323***)
procedure begin_token_list(p:pointer;t:quarterword); 
begin push_input; state:=token_list; start:=p; token_type:=t; 
if t>=macro then {the token list starts with a reference count} 
  begin add_token_ref(p); 
  if t=macro then param_start:=param_ptr 
  else  begin loc:=link(p); 
    if tracing_macros>1 then 
      begin begin_diagnostic; print_nl(''); 
      case t of 
      mark_text:print_esc('mark'); 
      write_text:print_esc('write'); 
      othercases print_cmd_chr(assign_toks,t-output_text+output_routine_loc) 
      endcases;
 
      print('->'); token_show(p); end_diagnostic(false); 
      end; 
    end; 
  end 
else loc:=p; 
end; 


(***PASCAL module 324***)
procedure end_token_list; {leave a token-list input level} 
begin if token_type>=backed_up then {token list to be deleted} 
  begin if token_type<=inserted then flush_list(start) 
  else  begin delete_token_ref(start); {update reference count} 
    if token_type=macro then {parameters must be flushed} 
      while param_ptr>param_start do 
        begin decr(param_ptr); 
        flush_list(param_stack[param_ptr]); 
        end; 
    end; 
  end 
else if token_type=u_template then 
  if align_state>500000 then align_state:=0 
  else fatal_error('(interwoven alignment preambles are not allowed)'); 
(*interwoven alignment preambles...*) 
pop_input; 
check_interrupt; 
end; 


(***PASCAL module 325***)
procedure back_input; {undoes one token of input} 
var p:pointer; {a token list of length one} 
begin while (state=token_list)and(loc=null)and(token_type<>v_template) do 
  end_token_list; {conserve stack space} 
p:=get_avail; info(p):=cur_tok; 
if cur_tok<right_brace_limit then 
  if cur_tok<left_brace_limit then decr(align_state) 
  else incr(align_state); 
push_input; state:=token_list; start:=p; token_type:=backed_up; 
loc:=p; {that was |back_list(p)|, without procedure overhead} 
end; 


(***PASCAL module 327***)
procedure back_error; {back up one token and call |error|} 
begin OK_to_interrupt:=false; back_input; OK_to_interrupt:=true; error; 
end; 


 
procedure ins_error; {back up one inserted token and call |error|} 
begin OK_to_interrupt:=false; back_input; token_type:=inserted; 
OK_to_interrupt:=true; error; 
end; 


(***PASCAL module 328***)
procedure begin_file_reading; 
begin if in_open=max_in_open then overflow('text input levels',max_in_open); 
(*TeX capacity exceeded text input levels][\quad text input levels*) 
if first=buf_size then overflow('buffer size',buf_size); 
(*TeX capacity exceeded buffer size][\quad buffer size*) 
incr(in_open); push_input; index:=in_open; 
line_stack[index]:=line; start:=first; state:=mid_line; 
name:=0; {|terminal_input| is now |true|} 
end; 


(***PASCAL module 329***)
procedure end_file_reading; 
begin first:=start; line:=line_stack[index]; 
if name>17 then a_close(cur_file); {forget it} 
pop_input; decr(in_open); 
end; 


(***PASCAL module 330***)
procedure clear_for_error_prompt; 
begin while (state<>token_list)and terminal_input and 
  (input_ptr>0)and(loc>limit) do end_file_reading; 
print_ln; clear_terminal; 
end; 


(***PASCAL module 336***)
procedure check_outer_validity; 
var p:pointer; {points to inserted token list} 
q:pointer; {auxiliary pointer} 
begin if scanner_status<>normal then 
  begin deletions_allowed:=false; 
  
INSERT: 'Back up an outer control sequence so that it can be reread'
; 
  if scanner_status>skipping then 
    
INSERT: 'Tell the user what has run away and try to recover'

  else  begin print_err('Incomplete '); print_cmd_chr(if_test,cur_if); 
(*Incomplete \\if...*) 
    print('; all text was ignored after line '); print_int(skip_line); 
    help3('A forbidden control sequence occurred in skipped text.')
 
    ('This kind of error happens when you say `\if...'' and forget')
 
    ('the matching `\fi''. I''ve inserted a `\fi''; this might work.'); 
    if cur_cs<>0 then cur_cs:=0 
    else help_line[2]:= 
      'The file ended while I was skipping conditional text.'; 
    cur_tok:=cs_token_flag+frozen_fi; ins_error; 
    end; 
  deletions_allowed:=true; 
  end; 
end; 


(***PASCAL module 340***)
procedure firm_up_the_line; forward; 


(***PASCAL module 341***)
procedure get_next; {sets |cur_cmd|, |cur_chr|, |cur_cs| to next token} 
label restart, {go here to get the next input token} 
  switch, {go here to eat the next character from a file} 
  reswitch, {go here to digest it again} 
  start_cs, {go here to start looking for a control sequence} 
  found, {go here when a control sequence has been found} 
  exit; {go here when the next input token has been got} 
var k:0..buf_size; {an index into |buffer|} 
t:halfword; {a token} 
cat:0..max_char_code; {|cat_code(cur_chr)|, usually} 
c,cc:ASCII_code; {constituents of a possible expanded code} 
d:2..3; {number of excess characters in an expanded code} 
begin restart: cur_cs:=0; 
if state<>token_list then 

INSERT: 'Input from external file, |goto restart| if no input found'

else 
INSERT: 'Input from token list, |goto restart| if end of list or   if a parameter needs to be expanded'
; 

INSERT: 'If an alignment entry has just ended, take appropriate action'
; 
exit:end; 


(***PASCAL module 363***)
procedure firm_up_the_line; 
var k:0..buf_size; {an index into |buffer|} 
begin limit:=last; 
if pausing>0 then if interaction>nonstop_mode then 
  begin wake_up_terminal; print_ln; 
  if start<limit then for k:=start to limit-1 do print(buffer[k]); 
  first:=limit; prompt_input('=>'); {wait for user response} 
(*=>*) 
  if last>first then 
    begin for k:=first to last-1 do {move line down in buffer} 
      buffer[k+start-first]:=buffer[k]; 
    limit:=start+last-first; 
    end; 
  end; 
end; 


(***PASCAL module 365***)
procedure get_token; {sets |cur_cmd|, |cur_chr|, |cur_tok|} 
begin no_new_control_sequence:=false; get_next; no_new_control_sequence:=true; 
(*inner loop*) 
if cur_cs=0 then cur_tok:=(cur_cmd*256)+cur_chr 
else cur_tok:=cs_token_flag+cur_cs; 
end; 


(***PASCAL module 366***)
(*\4*)@<Declare the procedure called |macro_call|@>;
 
(*\4*)
INSERT: 'Declare the procedure called |insert_relax|'
;
 
procedure pass_text; forward;(*\2*) 
procedure start_input; forward;(*\2*) 
procedure conditional; forward;(*\2*) 
procedure get_x_token; forward;(*\2*) 
procedure conv_toks; forward;(*\2*) 
procedure ins_the_toks; forward;(*\2*) 
procedure expand; 
var t:halfword; {token that is being ``expanded after''} 
p,q,r:pointer; {for list manipulation} 
j:0..buf_size; {index into |buffer|} 
cv_backup:integer; {to save the global quantity |cur_val|} 
cvl_backup,radix_backup,co_backup:small_number; 
  {to save |cur_val_level|, etc.} 
backup_backup:pointer; {to save |link(backup_head)|} 
save_scanner_status:small_number; {temporary storage of |scanner_status|} 
begin cv_backup:=cur_val; cvl_backup:=cur_val_level; radix_backup:=radix; 
co_backup:=cur_order; backup_backup:=link(backup_head); 
if cur_cmd<call then 
INSERT: 'Expand a nonmacro'

else if cur_cmd<end_template then macro_call 
else 
INSERT: 'Insert a token containing |frozen_endv|'
; 
cur_val:=cv_backup; cur_val_level:=cvl_backup; radix:=radix_backup; 
cur_order:=co_backup; link(backup_head):=backup_backup; 
end; 


(***PASCAL module 380***)
procedure get_x_token; {sets |cur_cmd|, |cur_chr|, |cur_tok|, 
  and expands macros} 
label restart,done; 
begin restart: get_next; 
(*inner loop*) 
if cur_cmd<=max_command then goto done; 
if cur_cmd>=call then 
  if cur_cmd<end_template then macro_call 
  else  begin cur_cs:=frozen_endv; cur_cmd:=endv; 
    goto done; {|cur_chr=null_list|} 
    end 
else expand; 
goto restart; 
done: if cur_cs=0 then cur_tok:=(cur_cmd*256)+cur_chr 
else cur_tok:=cs_token_flag+cur_cs; 
end; 


(***PASCAL module 381***)
procedure x_token; {|get_x_token| without the initial |get_next|} 
begin while cur_cmd>max_command do 
  begin expand; 
  get_next; 
  end; 
if cur_cs=0 then cur_tok:=(cur_cmd*256)+cur_chr 
else cur_tok:=cs_token_flag+cur_cs; 
end; 


(***PASCAL module 403***)
procedure scan_left_brace; {reads a mandatory |left_brace|} 
begin 
INSERT: 'Get the next non-blank non-relax non-call token'
; 
if cur_cmd<>left_brace then 
  begin print_err('Missing { inserted'); 
(*Missing \[
inserted*) 
  help4('A left brace was mandatory here, so I''ve put one in.')
 
    ('You might want to delete and/or insert some corrections')
 
    ('so that I will find a matching right brace soon.')
 
    ('(If you''re confused by all this, try typing `I}'' now.)'); 
  back_error; cur_tok:=left_brace_token+'{'; cur_cmd:=left_brace; 
  cur_chr:='{'; incr(align_state); 
  end; 
end; 


(***PASCAL module 405***)
procedure scan_optional_equals; 
begin  
INSERT: 'Get the next non-blank non-call token'
; 
if cur_tok<>other_token+'=' then back_input; 
end; 


(***PASCAL module 407***)
function scan_keyword(s:str_number):boolean; {look for a given string} 
label exit; 
var p:pointer; {tail of the backup list} 
q:pointer; {new node being added to the token list via |store_new_token|} 
k:pool_pointer; {index into |str_pool|} 
begin p:=backup_head; link(p):=null; k:=str_start[s]; 
while k<str_start[s+1] do 
  begin get_x_token; {recursion is possible here} 
(*recursion*) 
  if (cur_cs=0)and 
   ((cur_chr=so(str_pool[k]))or(cur_chr=so(str_pool[k])-'a'+'A')) then 
    begin store_new_token(cur_tok); incr(k); 
    end 
  else if (cur_cmd<>spacer)or(p<>backup_head) then 
    begin back_input; 
    if p<>backup_head then back_list(link(backup_head)); 
    scan_keyword:=false; return; 
    end; 
  end; 
flush_list(link(backup_head)); scan_keyword:=true; 
exit:end; 


(***PASCAL module 408***)
procedure mu_error; 
begin print_err('Incompatible glue units'); 
(*Incompatible glue units*) 
help1('I''m going to assume that 1mu=1pt when they''re mixed.'); 
error; 
end; 


(***PASCAL module 409***)
procedure scan_int; forward; {scans an integer value} 
(*\4\4*)
INSERT: 'Declare procedures that scan restricted classes of integers'
; 
(*\4\4*)
INSERT: 'Declare procedures that scan font-related stuff'



(***PASCAL module 413***)
procedure scan_something_internal(level:small_number;negative:boolean); 
  {fetch an internal parameter} 
var m:halfword; {|chr_code| part of the operand token} 
p:0..nest_size; {index into |nest|} 
begin m:=cur_chr; 
case cur_cmd of 
def_code: 
INSERT: 'Fetch a character code from some table'
; 
toks_register,assign_toks,def_family,set_font,def_font: 
INSERT: 'Fetch a token list or   font identifier, provided that |level=tok_val|'
; 
assign_int: scanned_result(eqtb[m].int)(int_val); 
assign_dimen: scanned_result(eqtb[m].sc)(dimen_val); 
assign_glue: scanned_result(equiv(m))(glue_val); 
assign_mu_glue: scanned_result(equiv(m))(mu_val); 
set_aux: 
INSERT: 'Fetch the |space_factor| or the |prev_depth|'
; 
set_prev_graf: 
INSERT: 'Fetch the |prev_graf|'
; 
set_page_int:
INSERT: 'Fetch the |dead_cycles| or the |insert_penalties|'
; 
set_page_dimen: 
INSERT: 'Fetch something on the |page_so_far|'
; 
set_shape: 
INSERT: 'Fetch the |par_shape| size'
; 
set_box_dimen: 
INSERT: 'Fetch a box dimension'
; 
char_given,math_given: scanned_result(cur_chr)(int_val); 
assign_font_dimen: 
INSERT: 'Fetch a font dimension'
; 
assign_font_int: 
INSERT: 'Fetch a font integer'
; 
register: 
INSERT: 'Fetch a register'
; 
last_item: 
INSERT: 'Fetch an item in the current node, if appropriate'
; 
othercases 
INSERT: 'Complain that \.{\\the} can''t do this; give zero result'

endcases;
 
while cur_val_level>level do 
INSERT: 'Convert \(c)|cur_val| to a lower level'
; 

INSERT: 'Fix the reference count, if any, and negate |cur_val| if |negative|'
; 
end; 


(***PASCAL module 440***)
procedure scan_int; {sets |cur_val| to an integer} 
label done; 
var negative:boolean; {should the answer be negated?} 
m:integer; {|(*$2^[31]$*) div radix|, the threshold of danger} 
d:small_number; {the digit just scanned} 
vacuous:boolean; {have no digits appeared?} 
OK_so_far:boolean; {has an error message been issued?} 
begin radix:=0; OK_so_far:=true;
 

INSERT: 'Get the next non-blank non-sign token; set |negative| appropriately'
; 
if cur_tok=alpha_token then 
INSERT: 'Scan an alphabetic character code into |cur_val|'

else if (cur_cmd>=min_internal)and(cur_cmd<=max_internal) then 
  scan_something_internal(int_val,false) 
else 
INSERT: 'Scan a numeric constant'
; 
if negative then negate(cur_val); 
end; 


(***PASCAL module 448***)
procedure scan_dimen(mu,inf,shortcut:boolean); 
  {sets |cur_val| to a dimension} 
label done, done1, done2, found, not_found, attach_fraction, attach_sign; 
var negative:boolean; {should the answer be negated?} 
f:integer; {numerator of a fraction whose denominator is $2^[16]$} 

INSERT: 'Local variables for dimension calculations'
; 
begin f:=0; arith_error:=false; cur_order:=normal; negative:=false; 
if not shortcut then 
  begin 
INSERT: 'Get the next non-blank non-sign...'
; 
  if (cur_cmd>=min_internal)and(cur_cmd<=max_internal) then 
    
INSERT: 'Fetch an internal dimension and |goto attach_sign|,       or fetch an internal integer'

  else  begin back_input; 
    if cur_tok=continental_point_token then cur_tok:=point_token; 
    if cur_tok<>point_token then scan_int 
    else  begin radix:=10; cur_val:=0; 
      end; 
    if cur_tok=continental_point_token then cur_tok:=point_token; 
    if (radix=10)and(cur_tok=point_token) then 
INSERT: 'Scan decimal fraction'
; 
    end; 
  end; 
if cur_val<0 then {in this case |f=0|} 
  begin negative := not negative; negate(cur_val); 
  end; 

INSERT: 'Scan units and set |cur_val| to $x\cdot(|cur_val|+f/2^{16})$, where there   are |x| sp per unit; |goto attach_sign| if the units are internal'
; 

INSERT: 'Scan an optional space'
; 
attach_sign: if arith_error or(abs(cur_val)>=1073741824) then 
  
INSERT: 'Report that this dimension is out of range'
; 
if negative then negate(cur_val); 
end; 


(***PASCAL module 461***)
procedure scan_glue(level:small_number); 
  {sets |cur_val| to a glue spec pointer} 
label exit; 
var negative:boolean; {should the answer be negated?} 
q:pointer; {new glue specification} 
mu:boolean; {does |level=mu_val|?} 
begin mu:=(level=mu_val); 
INSERT: 'Get the next non-blank non-sign...'
; 
if (cur_cmd>=min_internal)and(cur_cmd<=max_internal) then 
  begin scan_something_internal(level,negative); 
  if cur_val_level>=glue_val then 
    begin if cur_val_level<>level then mu_error; 
    return; 
    end; 
  if cur_val_level=int_val then scan_dimen(mu,false,true) 
  else if level=mu_val then mu_error; 
  end 
else  begin back_input; scan_dimen(mu,false,false); 
  if negative then negate(cur_val); 
  end; 

INSERT: 'Create a new glue specification whose width is |cur_val|; scan for its   stretch and shrink components'
; 
exit:end; 


(***PASCAL module 463***)
function scan_rule_spec:pointer; 
label reswitch; 
var q:pointer; {the rule node being created} 
begin q:=new_rule; {|width|, |depth|, and |height| all equal |null_flag| now} 
if cur_cmd=vrule then width(q):=default_rule 
else  begin height(q):=default_rule; depth(q):=0; 
  end; 
reswitch: if scan_keyword('width') then 
(*width*) 
  begin scan_normal_dimen; width(q):=cur_val; goto reswitch; 
  end; 
if scan_keyword('height') then 
(*height*) 
  begin scan_normal_dimen; height(q):=cur_val; goto reswitch; 
  end; 
if scan_keyword('depth') then 
(*depth*) 
  begin scan_normal_dimen; depth(q):=cur_val; goto reswitch; 
  end; 
scan_rule_spec:=q; 
end; 


(***PASCAL module 464***)
function str_toks(b:pool_pointer):pointer; 
  {changes the string |str_pool[b..pool_ptr]| to a token list} 
var p:pointer; {tail of the token list} 
q:pointer; {new node being added to the token list via |store_new_token|} 
t:halfword; {token being appended} 
k:pool_pointer; {index into |str_pool|} 
begin str_room(1); 
p:=temp_head; link(p):=null; k:=b; 
while k<pool_ptr do 
  begin t:=so(str_pool[k]); 
  if t=' ' then t:=space_token 
  else t:=other_token+t; 
  fast_store_new_token(t); 
  incr(k); 
  end; 
pool_ptr:=b; str_toks:=p; 
end; 


(***PASCAL module 465***)
function the_toks:pointer; 
var old_setting:0..max_selector; {holds |selector| setting} 
p,q,r:pointer; {used for copying a token list} 
b:pool_pointer; {base of temporary string} 
begin get_x_token; scan_something_internal(tok_val,false); 
if cur_val_level>=ident_val then 
INSERT: 'Copy the token list'

else begin old_setting:=selector; selector:=new_string; b:=pool_ptr; 
  case cur_val_level of 
  int_val:print_int(cur_val); 
  dimen_val:begin print_scaled(cur_val); print('pt'); 
    end; 
  glue_val: begin print_spec(cur_val,'pt'); delete_glue_ref(cur_val); 
    end; 
  mu_val: begin print_spec(cur_val,'mu'); delete_glue_ref(cur_val); 
    end; 
  end; {there are no other cases} 
  selector:=old_setting; the_toks:=str_toks(b); 
  end; 
end; 


(***PASCAL module 467***)
procedure ins_the_toks; 
begin link(garbage):=the_toks; ins_list(link(temp_head)); 
end; 


(***PASCAL module 470***)
procedure conv_toks; 
var old_setting:0..max_selector; {holds |selector| setting} 
c:number_code..job_name_code; {desired type of conversion} 
save_scanner_status:small_number; {|scanner_status| upon entry} 
b:pool_pointer; {base of temporary string} 
begin c:=cur_chr; 
INSERT: 'Scan the argument for command |c|'
; 
old_setting:=selector; selector:=new_string; b:=pool_ptr; 

INSERT: 'Print the result of command |c|'
; 
selector:=old_setting; link(garbage):=str_toks(b); ins_list(link(temp_head)); 
end; 


(***PASCAL module 473***)
function scan_toks(macro_def,xpand:boolean):pointer; 
label found,done,done1,done2; 
var t:halfword; {token representing the highest parameter number} 
s:halfword; {saved token} 
p:pointer; {tail of the token list being built} 
q:pointer; {new node being added to the token list via |store_new_token|} 
unbalance:halfword; {number of unmatched left braces} 
hash_brace:halfword; {possible `\.[\#\[]' 
token} 
begin if macro_def then scanner_status:=defining 
else scanner_status:=absorbing; 
warning_index:=cur_cs; def_ref:=get_avail; token_ref_count(def_ref):=null; 
p:=def_ref; hash_brace:=0; t:=zero_token; 
if macro_def then 
INSERT: 'Scan and build the parameter part of the macro definition'

else scan_left_brace; {remove the compulsory left brace} 

INSERT: 'Scan and build the body of the token list; |goto found| when finished'
; 
found: scanner_status:=normal; 
if hash_brace<>0 then store_new_token(hash_brace); 
scan_toks:=p; 
end; 


(***PASCAL module 482***)
procedure read_toks(n:integer;r:pointer); 
label done; 
var p:pointer; {tail of the token list} 
q:pointer; {new node being added to the token list via |store_new_token|} 
s:integer; {saved value of |align_state|} 
m:small_number; {stream number} 
begin scanner_status:=defining; warning_index:=r; 
def_ref:=get_avail; token_ref_count(def_ref):=null; 
p:=def_ref; {the reference count} 
store_new_token(end_match_token); 
if (n<0)or(n>15) then m:=16else m:=n; 
s:=align_state; align_state:=1000000; {disable tab marks, etc.} 
repeat 
INSERT: 'Input and store tokens from the next line of the file'
; 
until align_state=1000000; 
cur_val:=def_ref; scanner_status:=normal; align_state:=s; 
end; 


(***PASCAL module 494***)
procedure pass_text; 
label done; 
var l:integer; {level of $\.[\\if]\ldots\.[\\fi]$ nesting} 
save_scanner_status:small_number; {|scanner_status| upon entry} 
begin save_scanner_status:=scanner_status; scanner_status:=skipping; l:=0; 
skip_line:=line; 
loop  begin get_next; 
  if cur_cmd=fi_or_else then 
    begin if l=0 then goto done; 
    if cur_chr=fi_code then decr(l); 
    end 
  else if cur_cmd=if_test then incr(l); 
  end; 
done: scanner_status:=save_scanner_status; 
end; 


(***PASCAL module 497***)
procedure change_if_limit(l:small_number;p:pointer); 
label exit; 
var q:pointer; 
begin if p=cond_ptr then if_limit:=l {that's the easy case} 
else  begin q:=cond_ptr; 
  loop  begin if q=null then confusion('if'); 
(*this can''t happen if][\quad if*) 
    if link(q)=p then 
      begin type(q):=l; return; 
      end; 
    q:=link(q); 
    end; 
  end; 
exit:end; 


(***PASCAL module 498***)
procedure conditional; 
label exit,common_ending; 
var b:boolean; {is the condition true?} 
r:'<'..'>'; {relation to be evaluated} 
m,n:integer; {to be tested against the second operand} 
p,q:pointer; {for traversing token lists in \.[\\ifx] tests} 
save_scanner_status:small_number; {|scanner_status| upon entry} 
save_cond_ptr:pointer; {|cond_ptr| corresponding to this conditional} 
this_if:small_number; {type of this conditional} 
begin 
INSERT: 'Push the condition stack'
;save_cond_ptr:=cond_ptr;this_if:=cur_chr;
 

INSERT: 'Either process \.{\\ifcase} or set |b| to the value of a boolean condition'
; 
if tracing_commands>1 then 
INSERT: 'Display the value of |b|'
; 
if b then 
  begin change_if_limit(else_code,save_cond_ptr); 
  return; {wait for \.[\\else] or \.[\\fi]} 
  end; 

INSERT: 'Skip to \.{\\else} or \.{\\fi}, then |goto common_ending|'
; 
common_ending: if cur_chr=fi_code then 
INSERT: 'Pop the condition stack'

else if_limit:=fi_code; {wait for \.[\\fi]} 
exit:end; 


(***PASCAL module 515***)
procedure begin_name; 
begin area_delimiter:=0; ext_delimiter:=0; 
end; 


(***PASCAL module 516***)
function more_name(c:ASCII_code):boolean; 
begin if c=' ' then more_name:=false 
else  begin str_room(1); append_char(c); {contribute |c| to the current string} 
  if (c='>')or(c=':') then 
    begin area_delimiter:=cur_length; ext_delimiter:=0; 
    end 
  else if (c='.')and(ext_delimiter=0) then ext_delimiter:=cur_length; 
  more_name:=true; 
  end; 
end; 


(***PASCAL module 517***)
procedure end_name; 
begin if str_ptr+3>max_strings then 
  overflow('number of strings',max_strings-init_str_ptr); 
(*TeX capacity exceeded number of strings][\quad number of strings*) 
if area_delimiter=0 then cur_area:='' 
else  begin cur_area:=str_ptr; 
  str_start[str_ptr+1]:=str_start[str_ptr]+area_delimiter; incr(str_ptr); 
  end; 
if ext_delimiter=0 then 
  begin cur_ext:=''; cur_name:=make_string; 
  end 
else  begin cur_name:=str_ptr; 
  str_start[str_ptr+1]:=str_start[str_ptr]+ext_delimiter-area_delimiter-1; 
  incr(str_ptr); cur_ext:=make_string; 
  end; 
end; 


(***PASCAL module 519***)
procedure pack_file_name(n,a,e:str_number); 
var k:integer; {number of positions filled in |name_of_file|} 
c: ASCII_code; {character being packed} 
j:pool_pointer; {index into |str_pool|} 
begin k:=0; 
for j:=str_start[a] to str_start[a+1]-1 do append_to_name(so(str_pool[j])); 
for j:=str_start[n] to str_start[n+1]-1 do append_to_name(so(str_pool[j])); 
for j:=str_start[e] to str_start[e+1]-1 do append_to_name(so(str_pool[j])); 
if k<=file_name_size then name_length:=kelse name_length:=file_name_size; 
for k:=name_length+1 to file_name_size do name_of_file[k]:=' '; 
end; 


(***PASCAL module 523***)
procedure pack_buffered_name(n:small_number;a,b:integer); 
var k:integer; {number of positions filled in |name_of_file|} 
c: ASCII_code; {character being packed} 
j:integer; {index into |buffer| or |TEX_format_default|} 
begin if n+b-a+1+format_ext_length>file_name_size then 
  b:=a+file_name_size-n-1-format_ext_length; 
k:=0; 
for j:=1 to n do append_to_name(xord[TEX_format_default[j]]); 
for j:=a to b do append_to_name(buffer[j]); 
for j:=format_default_length-format_ext_length+1 to format_default_length do 
  append_to_name(xord[TEX_format_default[j]]); 
if k<=file_name_size then name_length:=kelse name_length:=file_name_size; 
for k:=name_length+1 to file_name_size do name_of_file[k]:=' '; 
end; 


(***PASCAL module 525***)
function make_name_string:str_number; 
var k:1..file_name_size; {index into |name_of_file|} 
begin if (pool_ptr+name_length>pool_size)or(str_ptr=max_strings)or 
 (cur_length>0) then 
  make_name_string:='?' 
else  begin for k:=1 to name_length do append_char(xord[name_of_file[k]]); 
  make_name_string:=make_string; 
  end; 
end; 
function a_make_name_string(var f:alpha_file):str_number; 
begin a_make_name_string:=make_name_string; 
end; 
function b_make_name_string(var f:byte_file):str_number; 
begin b_make_name_string:=make_name_string; 
end; 
function w_make_name_string(var f:word_file):str_number; 
begin w_make_name_string:=make_name_string; 
end; 


(***PASCAL module 526***)
procedure scan_file_name; 
label done; 
begin name_in_progress:=true; begin_name; 

INSERT: 'Get the next non-blank non-call...'
; 
loopbegin if (cur_cmd>other_char)or(cur_chr>255) then {not a character} 
    begin back_input; goto done; 
    end; 
  if not more_name(cur_chr) then goto done; 
  get_x_token; 
  end; 
done: end_name; name_in_progress:=false; 
end; 


(***PASCAL module 529***)
procedure pack_job_name(s:str_number); {|s = '.log'|, |'.dvi'|, or 
  |format_extension|} 
begin cur_area:=''; cur_ext:=s; 
cur_name:=job_name; pack_cur_name; 
end; 


(***PASCAL module 530***)
procedure prompt_file_name(s,e:str_number); 
label done; 
var k:0..buf_size; {index into |buffer|} 
begin if interaction=scroll_mode then wake_up_terminal; 
if s='input file name' then print_err('I can''t find file `') 
(*I can''t find file x*) 
else print_err('I can''t write on file `'); 
(*I can''t write on file x*) 
print_file_name(cur_name,cur_area,cur_ext); print('''.'); 
if e='.tex' then show_context; 
print_nl('Please type another '); print(s); 
(*Please type...*) 
if interaction<scroll_mode then 
  fatal_error('*** (job aborted, file error in nonstop mode)'); 
(*job aborted, file error...*) 
clear_terminal; prompt_input(': '); 
INSERT: 'Scan file name in the buffer'
; 
if cur_ext='' then cur_ext:=e; 
pack_cur_name; 
end; 


(***PASCAL module 534***)
procedure open_log_file; 
var old_setting:0..max_selector; {previous |selector| setting} 
k:0..buf_size; {index into |months| and |buffer|} 
l:0..buf_size; {end of first input line} 
months:packed array [1..36] of char; {abbreviations of month names} 
begin old_setting:=selector; 
if job_name=0 then job_name:='texput'; 
(*texput*) 
pack_job_name('.log'); 
while not a_open_out(log_file) do 
INSERT: 'Try to get a different log file name'
; 
log_name:=a_make_name_string(log_file); 
selector:=log_only; log_opened:=true; 

INSERT: 'Print the banner line, including the date and time'
; 
input_stack[input_ptr]:=cur_input; {make sure bottom level is in memory} 
print_nl('**'); 
(****) 
l:=input_stack[0].limit_field; {last position of first line} 
if buffer[l]=end_line_char then decr(l); 
for k:=1 to l do print(buffer[k]); 
print_ln; {now the transcript file contains the first line of input} 
selector:=old_setting+2; {|log_only| or |term_and_log|} 
end; 


(***PASCAL module 537***)
procedure start_input; {\TeX\ will \.[\\input] something} 
label done; 
begin scan_file_name; {set |cur_name| to desired file name} 
if cur_ext='' then cur_ext:='.tex'; 
pack_cur_name; 
loop  begin begin_file_reading; {set up |cur_file| and new level of input} 
  if a_open_in(cur_file) then goto done; 
  if cur_area='' then 
    begin pack_file_name(cur_name,TEX_area,cur_ext); 
    if a_open_in(cur_file) then goto done; 
    end; 
  end_file_reading; {remove the level that didn't work} 
  prompt_file_name('input file name','.tex'); 
  end; 
done: name:=a_make_name_string(cur_file); 
if job_name=0 then 
  begin job_name:=cur_name; open_log_file; 
  end; {|open_log_file| doesn't |show_context|, so |limit| 
    and |loc| needn't be set to meaningful values yet} 
if term_offset+length(name)>max_print_line-2 then print_ln 
else if (term_offset>0)or(file_offset>0) then print_char(' '); 
print_char('('); incr(open_parens); slow_print(name); update_terminal; 
state:=new_line; 
if name=str_ptr-1 then {we can conserve string pool space now} 
  begin flush_string; name:=cur_name; 
  end; 

INSERT: 'Read the first line of the new file'
; 
end; 


(***PASCAL module 560***)
function read_font_info(u:pointer;nom,aire:str_number; 
  s:scaled):internal_font_number; {input a \.[TFM] file} 
label done,bad_tfm,not_found; 
var k:font_index; {index into |font_info|} 
file_opened:boolean; {was |tfm_file| successfully opened?} 
lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np:halfword; 
  {sizes of subfiles} 
f:internal_font_number; {the new font's number} 
g:internal_font_number; {the number to return} 
a,b,c,d:eight_bits; {byte variables} 
qw:four_quarters;sw:scaled; {accumulators} 
bch_label:integer; {left boundary start location, or infinity} 
bchar:0..256; {right boundary character, or 256} 
z:scaled; {the design size or the ``at'' size} 
alpha:integer;beta:1..16; 
  {auxiliary quantities used in fixed-point multiplication} 
begin g:=null_font;
 

INSERT: 'Read and check the font data; |abort| if the \.{TFM} file is   malformed; if there''s no room for this font, say so and |goto   done|; otherwise |incr(font_ptr)| and |goto done|'
; 
bad_tfm: 
INSERT: 'Report that the font won''t be loaded'
; 
done: if file_opened then b_close(tfm_file); 
read_font_info:=g; 
end; 


(***PASCAL module 581***)
procedure char_warning(f:internal_font_number;c:eight_bits); 
begin if tracing_lost_chars>0 then 
  begin begin_diagnostic; 
  print_nl('Missing character: There is no '); 
(*Missing character*) 
  print_ASCII(c); print(' in font '); 
  slow_print(font_name[f]); print_char('!'); end_diagnostic(false); 
  end; 
end; 


(***PASCAL module 582***)
function new_character(f:internal_font_number;c:eight_bits):pointer; 
label exit; 
var p:pointer; {newly allocated node} 
begin if font_bc[f]<=c then if font_ec[f]>=c then 
  if char_exists(char_info(f)(qi(c))) then 
    begin p:=get_avail; font(p):=f; character(p):=qi(c); 
    new_character:=p; return; 
    end; 
char_warning(f,c); 
new_character:=null; 
exit:end; 


(***PASCAL module 597***)
procedure write_dvi(a,b:dvi_index); 
var k:dvi_index; 
begin for k:=a to b do write(dvi_file,dvi_buf[k]); 
end; 


(***PASCAL module 598***)
procedure dvi_swap; {outputs half of the buffer} 
begin if dvi_limit=dvi_buf_size then 
  begin write_dvi(0,half_buf-1); dvi_limit:=half_buf; 
  dvi_offset:=dvi_offset+dvi_buf_size; dvi_ptr:=0; 
  end 
else  begin write_dvi(half_buf,dvi_buf_size-1); dvi_limit:=dvi_buf_size; 
  end; 
dvi_gone:=dvi_gone+half_buf; 
end; 


(***PASCAL module 600***)
procedure dvi_four(x:integer); 
begin if x>=0 then dvi_out(x div 16777216) 
else  begin x:=x+1073741824; 
  x:=x+1073741824; 
  dvi_out((x div 16777216) + 128); 
  end; 
x:=x mod 16777216; dvi_out(x div 65536); 
x:=x mod 65536; dvi_out(x div 256); 
dvi_out(x mod 256); 
end; 


(***PASCAL module 601***)
procedure dvi_pop(l:integer); 
begin if (l=dvi_offset+dvi_ptr)and(dvi_ptr>0) then decr(dvi_ptr) 
else dvi_out(pop); 
end; 


(***PASCAL module 602***)
procedure dvi_font_def(f:internal_font_number); 
var k:pool_pointer; {index into |str_pool|} 
begin dvi_out(fnt_def1); 
dvi_out(f-font_base-1);
 
dvi_out(qo(font_check[f].b0)); 
dvi_out(qo(font_check[f].b1)); 
dvi_out(qo(font_check[f].b2)); 
dvi_out(qo(font_check[f].b3));
 
dvi_four(font_size[f]); 
dvi_four(font_dsize[f]);
 
dvi_out(length(font_area[f])); 
dvi_out(length(font_name[f])); 

INSERT: 'Output the font name whose internal number is |f|'
; 
end; 


(***PASCAL module 607***)
procedure movement(w:scaled;o:eight_bits); 
label exit,found,not_found,2,1; 
var mstate:small_number; {have we seen a |y| or |z|?} 
p,q:pointer; {current and top nodes on the stack} 
k:integer; {index into |dvi_buf|, modulo |dvi_buf_size|} 
begin q:=get_node(movement_node_size); {new node for the top of the stack} 
width(q):=w; location(q):=dvi_offset+dvi_ptr; 
if o=down1 then 
  begin link(q):=down_ptr; down_ptr:=q; 
  end 
else  begin link(q):=right_ptr; right_ptr:=q; 
  end; 

INSERT: 'Look at the other stack entries until deciding what sort of \.{DVI} command   to generate; |goto found| if node |p| is a ``hit'''''
; 

INSERT: 'Generate a |down| or |right| command for |w| and |return|'
; 
found: 
INSERT: 'Generate a |y0| or |z0| command in order to reuse a previous   appearance of~|w|'
; 
exit:end; 


(***PASCAL module 615***)
procedure prune_movements(l:integer); 
  {delete movement nodes with |location>=l|} 
label done,exit; 
var p:pointer; {node being deleted} 
begin while down_ptr<>null do 
  begin if location(down_ptr)<l then goto done; 
  p:=down_ptr; down_ptr:=link(p); free_node(p,movement_node_size); 
  end; 
done: while right_ptr<>null do 
  begin if location(right_ptr)<l then return; 
  p:=right_ptr; right_ptr:=link(p); free_node(p,movement_node_size); 
  end; 
exit:end; 


(***PASCAL module 618***)
procedure vlist_out; forward; {|hlist_out| and |vlist_out| are mutually 
  recursive} 


(***PASCAL module 619***)
(*\4*)
INSERT: 'Declare procedures needed in |hlist_out|, |vlist_out|'
(*@>
*)(*@>
*) 
procedure hlist_out; {output an |hlist_node| box} 
label reswitch, move_past, fin_rule, next_p; 
var base_line: scaled; {the baseline coordinate for this box} 
left_edge: scaled; {the left coordinate for this box} 
save_h,save_v: scaled; {what |dvi_h| and |dvi_v| should pop to} 
this_box: pointer; {pointer to containing box} 
g_order: glue_ord; {applicable order of infinity for glue} 
g_sign: normal..shrinking; {selects type of glue} 
p:pointer; {current position in the hlist} 
save_loc:integer; {\.[DVI] byte location upon entry} 
leader_box:pointer; {the leader box being replicated} 
leader_wd:scaled; {width of leader box being replicated} 
lx:scaled; {extra space between leader boxes} 
outer_doing_leaders:boolean; {were we doing leaders?} 
edge:scaled; {left edge of sub-box, or right edge of leader space} 
glue_temp:real; {glue value before rounding} 
cur_glue:real; {glue seen so far} 
cur_g:scaled; {rounded equivalent of |cur_glue| times the glue ratio} 
begin cur_g:=0; cur_glue:=float_constant(0); 
this_box:=temp_ptr; g_order:=glue_order(this_box); 
g_sign:=glue_sign(this_box); p:=list_ptr(this_box); 
incr(cur_s); 
if cur_s>0 then dvi_out(push); 
if cur_s>max_push then max_push:=cur_s; 
save_loc:=dvi_offset+dvi_ptr; base_line:=cur_v; left_edge:=cur_h; 
while p<>null do 
INSERT: 'Output node |p| for |hlist_out| and move to the next node,   maintaining the condition |cur_v=base_line|'
; 
prune_movements(save_loc); 
if cur_s>0 then dvi_pop(save_loc); 
decr(cur_s); 
end; 


(***PASCAL module 629***)
procedure vlist_out; {output a |vlist_node| box} 
label move_past, fin_rule, next_p; 
var left_edge: scaled; {the left coordinate for this box} 
top_edge: scaled; {the top coordinate for this box} 
save_h,save_v: scaled; {what |dvi_h| and |dvi_v| should pop to} 
this_box: pointer; {pointer to containing box} 
g_order: glue_ord; {applicable order of infinity for glue} 
g_sign: normal..shrinking; {selects type of glue} 
p:pointer; {current position in the vlist} 
save_loc:integer; {\.[DVI] byte location upon entry} 
leader_box:pointer; {the leader box being replicated} 
leader_ht:scaled; {height of leader box being replicated} 
lx:scaled; {extra space between leader boxes} 
outer_doing_leaders:boolean; {were we doing leaders?} 
edge:scaled; {bottom boundary of leader space} 
glue_temp:real; {glue value before rounding} 
cur_glue:real; {glue seen so far} 
cur_g:scaled; {rounded equivalent of |cur_glue| times the glue ratio} 
begin cur_g:=0; cur_glue:=float_constant(0); 
this_box:=temp_ptr; g_order:=glue_order(this_box); 
g_sign:=glue_sign(this_box); p:=list_ptr(this_box); 
incr(cur_s); 
if cur_s>0 then dvi_out(push); 
if cur_s>max_push then max_push:=cur_s; 
save_loc:=dvi_offset+dvi_ptr; left_edge:=cur_h; cur_v:=cur_v-height(this_box); 
top_edge:=cur_v; 
while p<>null do 
INSERT: 'Output node |p| for |vlist_out| and move to the next node,   maintaining the condition |cur_h=left_edge|'
; 
prune_movements(save_loc); 
if cur_s>0 then dvi_pop(save_loc); 
decr(cur_s); 
end; 


(***PASCAL module 638***)
procedure ship_out(p:pointer); {output the box |p|} 
label done; 
var page_loc:integer; {location of the current |bop|} 
j,k:0..9; {indices to first ten count registers} 
s:pool_pointer; {index into |str_pool|} 
old_setting:0..max_selector; {saved |selector| setting} 
begin if tracing_output>0 then 
  begin print_nl(''); print_ln; 
  print('Completed box being shipped out'); 
(*Completed box...*) 
  end; 
if term_offset>max_print_line-9 then print_ln 
else if (term_offset>0)or(file_offset>0) then print_char(' '); 
print_char('['); j:=9; 
while (count(j)=0)and(j>0) do decr(j); 
for k:=0 to j do 
  begin print_int(count(k)); 
  if k<j then print_char('.'); 
  end; 
update_terminal; 
if tracing_output>0 then 
  begin print_char(']'); 
  begin_diagnostic; show_box(p); end_diagnostic(true); 
  end; 

INSERT: 'Ship box |p| out'
; 
if tracing_output<=0 then print_char(']'); 
dead_cycles:=0; 
update_terminal; {progress report} 

INSERT: 'Flush the box from memory, showing statistics if requested'
; 
end; 


(***PASCAL module 645***)
procedure scan_spec(c:group_code;three_codes:boolean); 
  {scans a box specification and left brace} 
label found; 
var s:integer; {temporarily saved value} 
spec_code:exactly..additional; 
begin if three_codes then s:=saved(0); 
if scan_keyword('to') then spec_code:=exactly 
(*to*) 
else if scan_keyword('spread') then spec_code:=additional 
(*spread*) 
else  begin spec_code:=additional; cur_val:=0; 
  goto found; 
  end; 
scan_normal_dimen; 
found: if three_codes then 
  begin saved(0):=s; incr(save_ptr); 
  end; 
saved(0):=spec_code; saved(1):=cur_val; save_ptr:=save_ptr+2; 
new_save_level(c); scan_left_brace; 
end; 


(***PASCAL module 649***)
function hpack(p:pointer;w:scaled;m:small_number):pointer; 
label reswitch, common_ending, exit; 
var r:pointer; {the box node that will be returned} 
q:pointer; {trails behind |p|} 
h,d,x:scaled; {height, depth, and natural width} 
s:scaled; {shift amount} 
g:pointer; {points to a glue specification} 
o:glue_ord; {order of infinity} 
f:internal_font_number; {the font in a |char_node|} 
i:four_quarters; {font information about a |char_node|} 
hd:eight_bits; {height and depth indices for a character} 
begin last_badness:=0; r:=get_node(box_node_size); type(r):=hlist_node; 
subtype(r):=min_quarterword; shift_amount(r):=0; 
q:=r+list_offset; link(q):=p;
 
h:=0; 
INSERT: 'Clear dimensions to zero'
; 
while p<>null do 
INSERT: 'Examine node |p| in the hlist, taking account of its effect   on the dimensions of the new box, or moving it to the adjustment list;   then advance |p| to the next node'
; 
if adjust_tail<>null then link(adjust_tail):=null; 
height(r):=h; depth(r):=d;
 

INSERT: 'Determine the value of |width(r)| and the appropriate glue setting;   then |return| or |goto common_ending|'
; 
common_ending: 
INSERT: 'Finish issuing a diagnostic message       for an overfull or underfull hbox'
; 
exit: hpack:=r; 
end; 


(***PASCAL module 668***)
function vpackage(p:pointer;h:scaled;m:small_number;l:scaled): 
  pointer; 
label common_ending, exit; 
var r:pointer; {the box node that will be returned} 
w,d,x:scaled; {width, depth, and natural height} 
s:scaled; {shift amount} 
g:pointer; {points to a glue specification} 
o:glue_ord; {order of infinity} 
begin last_badness:=0; r:=get_node(box_node_size); type(r):=vlist_node; 
subtype(r):=min_quarterword; shift_amount(r):=0; 
list_ptr(r):=p;
 
w:=0; 
INSERT: 'Clear dimensions to zero'
; 
while p<>null do 
INSERT: 'Examine node |p| in the vlist, taking account of its effect   on the dimensions of the new box; then advance |p| to the next node'
; 
width(r):=w; 
if d>l then 
  begin x:=x+d-l; depth(r):=l; 
  end 
else depth(r):=d; 

INSERT: 'Determine the value of |height(r)| and the appropriate glue setting;   then |return| or |goto common_ending|'
; 
common_ending: 
INSERT: 'Finish issuing a diagnostic message       for an overfull or underfull vbox'
; 
exit: vpackage:=r; 
end; 


(***PASCAL module 679***)
procedure append_to_vlist(b:pointer); 
var d:scaled; {deficiency of space between baselines} 
p:pointer; {a new glue node} 
begin if prev_depth>ignore_depth then 
  begin d:=width(baseline_skip)-prev_depth-height(b); 
  if d<line_skip_limit then p:=new_param_glue(line_skip_code) 
  else  begin p:=new_skip_param(baseline_skip_code); 
    width(temp_ptr):=d; {|temp_ptr=glue_ptr(p)|} 
    end; 
  link(tail):=p; tail:=p; 
  end; 
link(tail):=b; tail:=b; prev_depth:=depth(b); 
end; 


(***PASCAL module 686***)
function new_noad:pointer; 
var p:pointer; 
begin p:=get_node(noad_size); 
type(p):=ord_noad; subtype(p):=normal; 
mem[nucleus(p)].hh:=empty_field; 
mem[subscr(p)].hh:=empty_field; 
mem[supscr(p)].hh:=empty_field; 
new_noad:=p; 
end; 


(***PASCAL module 688***)
function new_style(s:small_number):pointer; {create a style node} 
var p:pointer; {the new node} 
begin p:=get_node(style_node_size); type(p):=style_node; 
subtype(p):=s; width(p):=0; depth(p):=0; {the |width| and |depth| are not used} 
new_style:=p; 
end; 


(***PASCAL module 689***)
function new_choice:pointer; {create a choice node} 
var p:pointer; {the new node} 
begin p:=get_node(style_node_size); type(p):=choice_node; 
subtype(p):=0; {the |subtype| is not used} 
display_mlist(p):=null; text_mlist(p):=null; script_mlist(p):=null; 
script_script_mlist(p):=null; 
new_choice:=p; 
end; 


(***PASCAL module 693***)
procedure show_info; {the reader will kindly forgive this} 
begin show_node_list(info(temp_ptr)); 
end; 


(***PASCAL module 704***)
function fraction_rule(t:scaled):pointer; 
  {construct the bar for a fraction} 
var p:pointer; {the new node} 
begin p:=new_rule; height(p):=t; depth(p):=0; fraction_rule:=p; 
end; 


(***PASCAL module 705***)
function overbar(b:pointer;k,t:scaled):pointer; 
var p,q:pointer; {nodes being constructed} 
begin p:=new_kern(k); link(p):=b; q:=fraction_rule(t); link(q):=p; 
p:=new_kern(t); link(p):=q; overbar:=vpack(p,natural); 
end; 


(***PASCAL module 706***)
(*\4*)@<Declare subprocedures for |var_delimiter|@> 
function var_delimiter(d:pointer;s:small_number;v:scaled):pointer; 
label found,continue; 
var b:pointer; {the box that will be constructed} 
f,g: internal_font_number; {best-so-far and tentative font codes} 
c,x,y: quarterword; {best-so-far and tentative character codes} 
m,n: integer; {the number of extensible pieces} 
u: scaled; {height-plus-depth of a tentative character} 
w: scaled; {largest height-plus-depth so far} 
q: four_quarters; {character info} 
hd: eight_bits; {height-depth byte} 
r: four_quarters; {extensible pieces} 
z: small_number; {runs through font family members} 
large_attempt: boolean; {are we trying the ``large'' variant?} 
begin f:=null_font; w:=0; large_attempt:=false; 
z:=small_fam(d); x:=small_char(d); 
loop  begin 
INSERT: 'Look at the variants of |(z,x)|; set |f| and |c| whenever     a better character is found; |goto found| as soon as a     large enough variant is encountered'
; 
  if large_attempt then goto found; {there were none large enough} 
  large_attempt:=true; z:=large_fam(d); x:=large_char(d); 
  end; 
found: if f<>null_font then 
  
INSERT: 'Make variable |b| point to a box for |(f,c)|'

else  begin b:=new_null_box; 
  width(b):=null_delimiter_space; {use this width if no delimiter was found} 
  end; 
shift_amount(b):=half(height(b)-depth(b)) - axis_height(s); 
var_delimiter:=b; 
end; 


(***PASCAL module 715***)
function rebox(b:pointer;w:scaled):pointer; 
var p:pointer; {temporary register for list manipulation} 
f:internal_font_number; {font in a one-character box} 
v:scaled; {width of a character without italic correction} 
begin if (width(b)<>w)and(list_ptr(b)<>null) then 
  begin if type(b)=vlist_node then b:=hpack(b,natural); 
  p:=list_ptr(b); 
  if (is_char_node(p))and(link(p)=null) then 
    begin f:=font(p); v:=char_width(f)(char_info(f)(character(p))); 
    if v<>width(b) then link(p):=new_kern(width(b)-v); 
    end; 
  free_node(b,box_node_size); 
  b:=new_glue(ss_glue); link(b):=p; 
  while link(p)<>null do p:=link(p); 
  link(p):=new_glue(ss_glue); 
  rebox:=hpack(b,w,exactly); 
  end 
else  begin width(b):=w; rebox:=b; 
  end; 
end; 


(***PASCAL module 716***)
function math_glue(g:pointer;m:scaled):pointer; 
var p:pointer; {the new glue specification} 
n:integer; {integer part of |m|} 
f:scaled; {fraction part of |m|} 
begin n:=x_over_n(m,65536); f:=remainder;
 
if f<0 then 
  begin decr(n); f:=f+65536; 
  end; 
p:=get_node(glue_spec_size); 
width(p):=mu_mult(width(g)); {convert \.[mu] to \.[pt]} 
stretch_order(p):=stretch_order(g); 
if stretch_order(p)=normal then stretch(p):=mu_mult(stretch(g)) 
else stretch(p):=stretch(g); 
shrink_order(p):=shrink_order(g); 
if shrink_order(p)=normal then shrink(p):=mu_mult(shrink(g)) 
else shrink(p):=shrink(g); 
math_glue:=p; 
end; 


(***PASCAL module 717***)
procedure math_kern(p:pointer;m:scaled); 
var n:integer; {integer part of |m|} 
f:scaled; {fraction part of |m|} 
begin if subtype(p)=mu_glue then 
  begin n:=x_over_n(m,65536); f:=remainder;
 
  if f<0 then 
    begin decr(n); f:=f+65536; 
    end; 
  width(p):=mu_mult(width(p)); subtype(p):=explicit; 
  end; 
end; 


(***PASCAL module 718***)
procedure flush_math; 
begin flush_node_list(link(head)); flush_node_list(incompleat_noad); 
link(head):=null; tail:=head; incompleat_noad:=null; 
end; 


(***PASCAL module 720***)
procedure mlist_to_hlist; forward;(*\2*)
 
function clean_box(p:pointer;s:small_number):pointer; 
label found; 
var q:pointer; {beginning of a list to be boxed} 
save_style:small_number; {|cur_style| to be restored} 
x:pointer; {box to be returned} 
r:pointer; {temporary pointer} 
begin case math_type(p) of 
math_char: begin cur_mlist:=new_noad; mem[nucleus(cur_mlist)]:=mem[p]; 
  end; 
sub_box: begin q:=info(p); goto found; 
  end; 
sub_mlist: cur_mlist:=info(p); 
othercases begin q:=new_null_box; goto found; 
  end 
endcases;
 
save_style:=cur_style; cur_style:=s; mlist_penalties:=false;
 
mlist_to_hlist; q:=link(temp_head); {recursive call} 
cur_style:=save_style; {restore the style} 

INSERT: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
; 
found: if is_char_node(q)or(q=null) then x:=hpack(q,natural) 
  else if (link(q)=null)and(type(q)<=vlist_node)and(shift_amount(q)=0) then 
    x:=q {it's already clean} 
  else x:=hpack(q,natural); 

INSERT: 'Simplify a trivial box'
; 
clean_box:=x; 
end; 


(***PASCAL module 722***)
procedure fetch(a:pointer); {unpack the |math_char| field |a|} 
begin cur_c:=character(a); cur_f:=fam_fnt(fam(a)+cur_size); 
if cur_f=null_font then 
  
INSERT: 'Complain about an undefined family and set |cur_i| null'

else  begin if (qo(cur_c)>=font_bc[cur_f])and(qo(cur_c)<=font_ec[cur_f]) then 
    cur_i:=char_info(cur_f)(cur_c) 
  else cur_i:=null_character; 
  if not(char_exists(cur_i)) then 
    begin char_warning(cur_f,qo(cur_c)); 
    math_type(a):=empty; 
    end; 
  end; 
end; 


(***PASCAL module 726***)
(*\4*)@<Declare math construction procedures@> 
procedure mlist_to_hlist; 
label reswitch, check_dimensions, done_with_noad, done_with_node, delete_q, 
  done; 
var mlist:pointer; {beginning of the given list} 
penalties:boolean; {should penalty nodes be inserted?} 
style:small_number; {the given style} 
save_style:small_number; {holds |cur_style| during recursion} 
q:pointer; {runs through the mlist} 
r:pointer; {the most recent noad preceding |q|} 
r_type:small_number; {the |type| of noad |r|, or |op_noad| if |r=null|} 
t:small_number; {the effective |type| of noad |q| during the second pass} 
p,x,y,z: pointer; {temporary registers for list construction} 
pen:integer; {a penalty to be inserted} 
s:small_number; {the size of a noad to be deleted} 
max_h,max_d:scaled; {maximum height and depth of the list translated so far} 
delta:scaled; {offset between subscript and superscript} 
begin mlist:=cur_mlist; penalties:=mlist_penalties; 
style:=cur_style; {tuck global parameters away as local variables} 
q:=mlist; r:=null; r_type:=op_noad; max_h:=0; max_d:=0; 

INSERT: 'Set up the values of |cur_size| and |cur_mu|, based on |cur_style|'
; 
while q<>null do 
INSERT: 'Process node-or-noad |q| as much as possible in preparation     for the second pass of |mlist_to_hlist|, then move to the next     item in the mlist'
; 

INSERT: 'Convert \(a)a final |bin_noad| to an |ord_noad|'
; 

INSERT: 'Make a second pass over the mlist, removing all noads and inserting the   proper spacing and penalties'
; 
end; 


(***PASCAL module 772***)
procedure push_alignment; 
var p:pointer; {the new alignment stack node} 
begin p:=get_node(align_stack_node_size); 
link(p):=align_ptr; info(p):=cur_align; 
llink(p):=preamble; rlink(p):=cur_span; 
mem[p+2].int:=cur_loop; mem[p+3].int:=align_state; 
info(p+4):=cur_head; link(p+4):=cur_tail; 
align_ptr:=p; 
cur_head:=get_avail; 
end; 


 
procedure pop_alignment; 
var p:pointer; {the top alignment stack node} 
begin free_avail(cur_head); 
p:=align_ptr; 
cur_tail:=link(p+4); cur_head:=info(p+4); 
align_state:=mem[p+3].int; cur_loop:=mem[p+2].int; 
cur_span:=rlink(p); preamble:=llink(p); 
cur_align:=info(p); align_ptr:=link(p); 
free_node(p,align_stack_node_size); 
end; 


(***PASCAL module 774***)
(*\4*)
INSERT: 'Declare the procedure called |get_preamble_token|'
(*@>
*)(*@>
*) 
procedure align_peek; forward;(*\2*)
 
procedure normal_paragraph; forward;(*\2*)
 
procedure init_align; 
label done, done1, done2, continue; 
var save_cs_ptr:pointer; {|warning_index| value for error messages} 
p:pointer; {for short-term temporary use} 
begin save_cs_ptr:=cur_cs; {\.[\\halign] or \.[\\valign], usually} 
push_alignment; align_state:=-1000000; {enter a new alignment level} 

INSERT: 'Check for improper alignment in displayed math'
; 
push_nest; {enter a new semantic level} 

INSERT: 'Change current mode to |-vmode| for \.{\\halign}, |-hmode| for \.{\\valign}'
; 
scan_spec(align_group,false);
 

INSERT: 'Scan the preamble and record it in the |preamble| list'
; 
new_save_level(align_group); 
if every_cr<>null then begin_token_list(every_cr,every_cr_text); 
align_peek; {look for \.[\\noalign] or \.[\\omit]} 
end; 


(***PASCAL module 786***)
(*\4*)
INSERT: 'Declare the procedure called |init_span|'
(*@>
*)(*@>
*) 
procedure init_row; 
begin push_nest; mode:=(-hmode-vmode)-mode; 
if mode=-hmode then space_factor:=0 else prev_depth:=0; 
tail_append(new_glue(glue_ptr(preamble))); 
subtype(tail):=tab_skip_code+1;
 
cur_align:=link(preamble); cur_tail:=cur_head; init_span(cur_align); 
end; 


(***PASCAL module 788***)
procedure init_col; 
begin extra_info(cur_align):=cur_cmd; 
if cur_cmd=omit then align_state:=0 
else  begin back_input; begin_token_list(u_part(cur_align),u_template); 
  end; {now |align_state=1000000|} 
end; 


(***PASCAL module 791***)
function fin_col:boolean; 
label exit; 
var p:pointer; {the alignrecord after the current one} 
q,r:pointer; {temporary pointers for list manipulation} 
s:pointer; {a new span node} 
u:pointer; {a new unset box} 
w:scaled; {natural width} 
o:glue_ord; {order of infinity} 
n:halfword; {span counter} 
begin if cur_align=null then confusion('endv'); 
q:=link(cur_align);if q=null then confusion('endv'); 
(*this can''t happen endv][\quad endv*) 
if align_state<500000 then 
  fatal_error('(interwoven alignment preambles are not allowed)'); 
(*interwoven alignment preambles...*) 
p:=link(q); 

INSERT: 'If the preamble list has been traversed, check that the row has ended'
; 
if extra_info(cur_align)<>span_code then 
  begin unsave; new_save_level(align_group);
 
  
INSERT: 'Package an unset box for the current column and record its width'
; 
  
INSERT: 'Copy the tabskip glue between columns'
; 
  if extra_info(cur_align)>=cr_code then 
    begin fin_col:=true; return; 
    end; 
  init_span(p); 
  end; 
align_state:=1000000; 
INSERT: 'Get the next non-blank non-call token'
; 
cur_align:=p; 
init_col; fin_col:=false; 
exit: end; 


(***PASCAL module 799***)
procedure fin_row; 
var p:pointer; {the new unset box} 
begin if mode=-hmode then 
  begin p:=hpack(link(head),natural); 
  pop_nest; append_to_vlist(p); 
  if cur_head<>cur_tail then 
    begin link(tail):=link(cur_head); tail:=cur_tail; 
    end; 
  end 
else  begin p:=vpack(link(head),natural); pop_nest; 
  link(tail):=p; tail:=p; space_factor:=1000; 
  end; 
type(p):=unset_node; glue_stretch(p):=0; 
if every_cr<>null then begin_token_list(every_cr,every_cr_text); 
align_peek; 
end; {note that |glue_shrink(p)=0| since |glue_shrink==shift_amount|} 


(***PASCAL module 800***)
procedure do_assignments; forward;(*\2*)
 
procedure resume_after_display; forward;(*\2*)
 
procedure build_page; forward;(*\2*)
 
procedure fin_align; 
var p,q,r,s,u,v: pointer; {registers for the list operations} 
t,w:scaled; {width of column} 
o:scaled; {shift offset for unset boxes} 
n:halfword; {matching span amount} 
rule_save:scaled; {temporary storage for |overfull_rule|} 
aux_save:memory_word; {temporary storage for |aux|} 
begin if cur_group<>align_group then confusion('align1'); 
(*this can''t happen align][\quad align*) 
unsave; {that |align_group| was for individual entries} 
if cur_group<>align_group then confusion('align0'); 
unsave; {that |align_group| was for the whole alignment} 
if nest[nest_ptr-1].mode_field=mmode then o:=display_indent 
  else o:=0; 

INSERT: 'Go through the preamble list, determining the column widths and   changing the alignrecords to dummy unset boxes'
; 

INSERT: 'Package the preamble list, to determine the actual tabskip glue amounts,   and let |p| point to this prototype box'
; 

INSERT: 'Set the glue in all the unset boxes of the current list'
; 
flush_node_list(p); pop_alignment; 

INSERT: 'Insert the \(c)current list into its environment'
; 
end;
 
(*\4*)
INSERT: 'Declare the procedure called |align_peek|'



(***PASCAL module 815***)
(*\4*)@<Declare subprocedures for |line_break|@> 
procedure line_break(final_widow_penalty:integer); 
label done,done1,done2,done3,done4,done5,continue; 
var 
INSERT: 'Local variables for line breaking'
; 
begin pack_begin_line:=mode_line; {this is for over/underfull box messages} 

INSERT: 'Get ready to start line breaking'
; 

INSERT: 'Find optimal breakpoints'
; 

INSERT: 'Break the paragraph at the chosen breakpoints, justify the resulting lines to the correct widths, and append them to the current vertical list'
; 

INSERT: 'Clean up the memory by removing the break nodes'
; 
pack_begin_line:=0; 
end; 


(***PASCAL module 934***)
procedure new_hyph_exceptions; {enters new exceptions} 
label reswitch, exit, found, not_found; 
var n:0..64; {length of current word; not always a |small_number|} 
j:0..64; {an index into |hc|} 
h:hyph_pointer; {an index into |hyph_word| and |hyph_list|} 
k:str_number; {an index into |str_start|} 
p:pointer; {head of a list of hyphen positions} 
q:pointer; {used when creating a new node for list |p|} 
s,t:str_number; {strings being compared or stored} 
u,v:pool_pointer; {indices into |str_pool|} 
begin scan_left_brace; {a left brace must follow \.[\\hyphenation]} 
set_cur_lang; 

INSERT: 'Enter as many hyphenation exceptions as are listed, until coming to a right brace; then |return|'
; 
exit:end; 


(***PASCAL module 968***)
function prune_page_top(p:pointer):pointer; {adjust top after page break} 
var prev_p:pointer; {lags one step behind |p|} 
q:pointer; {temporary variable for list manipulation} 
begin prev_p:=temp_head; link(temp_head):=p; 
while p<>null do 
  case type(p) of 
  hlist_node,vlist_node,rule_node:
INSERT: 'Insert glue for |split_top_skip|     and set~|p:=null|'
; 
  whatsit_node,mark_node,ins_node: begin prev_p:=p; p:=link(prev_p); 
    end; 
  glue_node,kern_node,penalty_node: begin q:=p; p:=link(q); link(q):=null; 
    link(prev_p):=p; flush_node_list(q); 
    end; 
  othercases confusion('pruning') 
(*this can''t happen pruning][\quad pruning*) 
  endcases; 
prune_page_top:=link(temp_head); 
end; 


(***PASCAL module 970***)
function vert_break(p:pointer; h,d:scaled):pointer; 
  {finds optimum page break} 
label done,not_found,update_heights; 
var prev_p:pointer; {if |p| is a glue node, |type(prev_p)| determines 
  whether |p| is a legal breakpoint} 
q,r:pointer; {glue specifications} 
pi:integer; {penalty value} 
b:integer; {badness at a trial breakpoint} 
least_cost:integer; {the smallest badness plus penalties found so far} 
best_place:pointer; {the most recent break that leads to |least_cost|} 
prev_dp:scaled; {depth of previous box in the list} 
t:small_number; {|type| of the node following a kern} 
begin prev_p:=p; {an initial glue node is not a legal breakpoint} 
least_cost:=awful_bad; do_all_six(set_height_zero); prev_dp:=0; 
loop  begin 
INSERT: 'If node |p| is a legal breakpoint, check if this break is     the best known, and |goto done| if |p| is null or     if the page-so-far is already too full to accept more stuff'
; 
  prev_p:=p; p:=link(prev_p); 
  end; 
done: vert_break:=best_place; 
end; 


(***PASCAL module 977***)
function vsplit(n:eight_bits; h:scaled):pointer; 
  {extracts a page of height |h| from box |n|} 
label exit,done; 
var v:pointer; {the box to be split} 
p:pointer; {runs through the vlist} 
q:pointer; {points to where the break occurs} 
begin v:=box(n); 
if split_first_mark<>null then 
  begin delete_token_ref(split_first_mark); split_first_mark:=null; 
  delete_token_ref(split_bot_mark); split_bot_mark:=null; 
  end; 

INSERT: 'Dispense with trivial cases of void or bad boxes'
; 
q:=vert_break(list_ptr(v),h,split_max_depth); 

INSERT: 'Look at all the marks in nodes before the break, and set the final   link to |null| at the break'
; 
q:=prune_page_top(q); p:=list_ptr(v); free_node(v,box_node_size); 
if q=null then box(n):=null {the |eq_level| of the box stays the same} 
else box(n):=vpack(q,natural); 
vsplit:=vpackage(p,h,exactly,split_max_depth); 
exit: end; 


(***PASCAL module 985***)
procedure print_totals; 
begin print_scaled(page_total); 
print_plus(2)(''); 
print_plus(3)('fil'); 
print_plus(4)('fill'); 
print_plus(5)('filll'); 
if page_shrink<>0 then 
  begin print(' minus '); print_scaled(page_shrink); 
  end; 
end; 


(***PASCAL module 987***)
procedure freeze_page_specs(s:small_number); 
begin page_contents:=s; 
page_goal:=vsize; page_max_depth:=max_depth; 
page_depth:=0; do_all_six(set_page_so_far_zero); 
least_page_cost:=awful_bad; 
stat if tracing_pages>0 then 
  begin begin_diagnostic; 
  print_nl('%% goal height='); print_scaled(page_goal); 
(*goal height*) 
  print(', max depth='); print_scaled(page_max_depth); 
  end_diagnostic(false); 
  end;;tats;
 
end; 


(***PASCAL module 992***)
procedure box_error(n:eight_bits); 
begin error; begin_diagnostic; 
print_nl('The following box has been deleted:'); 
(*The following...deleted*) 
show_box(box(n)); end_diagnostic(true); 
flush_node_list(box(n)); box(n):=null; 
end; 


(***PASCAL module 993***)
procedure ensure_vbox(n:eight_bits); 
var p:pointer; {the box register contents} 
begin p:=box(n); 
if p<>null then if type(p)=hlist_node then 
  begin print_err('Insertions can only be added to a vbox'); 
(*Insertions can only...*) 
  help3('Tut tut: You''re trying to \insert into a')
 
    ('\box register that now contains an \hbox.')
 
    ('Proceed, and I''ll discard its present contents.'); 
  box_error(n); 
  end; 
end; 


(***PASCAL module 994***)
(*\4*)
INSERT: 'Declare the procedure called |fire_up|'
;
 
procedure build_page; {append contributions to the current page} 
label exit,done,done1,continue,contribute,update_heights; 
var p:pointer; {the node being appended} 
q,r:pointer; {nodes being examined} 
b,c:integer; {badness and cost of current page} 
pi:integer; {penalty to be added to the badness} 
n:min_quarterword..255; {insertion box number} 
delta,h,w:scaled; {sizes used for insertion calculations} 
begin if (link(contrib_head)=null)or output_active then return; 
repeat continue: p:=link(contrib_head);
 

INSERT: 'Update the values of |last_glue|, |last_penalty|, and |last_kern|'
; 

INSERT: 'Move node |p| to the current page; if it is time for a page break,   put the nodes following the break back onto the contribution list,   and |return| to the user''s output routine if there is one'
; 
until link(contrib_head)=null; 

INSERT: 'Make the contribution list empty by setting its tail to |contrib_head|'
; 
exit:end; 


(***PASCAL module 1030***)
(*\4*)
INSERT: 'Declare action procedures for use by |main_control|'
; 
(*\4*)
INSERT: 'Declare the procedure called |handle_right_brace|'
; 
procedure main_control; {governs \TeX's activities} 
label big_switch,reswitch,main_loop,main_loop_wrapup, 
  main_loop_move,main_loop_move+1,main_loop_move+2,main_loop_move_lig, 
  main_loop_lookahead,main_loop_lookahead+1, 
  main_lig_loop,main_lig_loop+1,main_lig_loop+2, 
  append_normal_space,exit; 
vart:integer; {general-purpose temporary variable} 
begin if every_job<>null then begin_token_list(every_job,every_job_text); 
big_switch: get_x_token;
 
reswitch: 
INSERT: 'Give diagnostic information, if requested'
; 
case abs(mode)+cur_cmd of 
hmode+letter,hmode+other_char,hmode+char_given: goto main_loop; 
hmode+char_num: begin scan_char_num; cur_chr:=cur_val; goto main_loop;end; 
hmode+no_boundary: begin get_x_token; 
  if (cur_cmd=letter)or(cur_cmd=other_char)or(cur_cmd=char_given)or 
   (cur_cmd=char_num) then cancel_boundary:=true; 
  goto reswitch; 
  end; 
hmode+spacer: if space_factor=1000 then goto append_normal_space 
  else app_space; 
hmode+ex_space,mmode+ex_space: goto append_normal_space; 
(*\4*)
INSERT: 'Cases of |main_control| that are not part of the inner loop'
; 
end; {of the big |case| statement} 
goto big_switch; 
main_loop:
INSERT: 'Append character |cur_chr| and the following characters (if~any)   to the current hlist in the current font; |goto reswitch| when   a non-character has been fetched'
; 
append_normal_space:
INSERT: 'Append a normal inter-word space to the current list,   then |goto big_switch|'
; 
exit:end; 


(***PASCAL module 1284***)
procedure give_err_help; 
begin token_show(err_help); 
end; 


(***PASCAL module 1303***)
(*\4*)
INSERT: 'Declare the function called |open_fmt_file|'
; 
function load_fmt_file:boolean; 
label bad_fmt,exit; 
var j,k:integer; {all-purpose indices} 
p,q: pointer; {all-purpose pointers} 
x: integer; {something undumped} 
w: four_quarters; {four ASCII codes} 
begin 
INSERT: 'Undump constants for consistency check'
; 

INSERT: 'Undump the string pool'
; 

INSERT: 'Undump the dynamic memory'
; 

INSERT: 'Undump the table of equivalents'
; 

INSERT: 'Undump the font information'
; 

INSERT: 'Undump the hyphenation tables'
; 

INSERT: 'Undump a couple more things and the closing check word'
; 
load_fmt_file:=true; return; {it worked!} 
bad_fmt: wake_up_terminal; 
  wterm_ln('(Fatal format file error; I''m stymied)'); 
(*Fatal format file error*) 
load_fmt_file:=false; 
exit:end; 


(***PASCAL module 1330***)

INSERT: 'Last-minute procedures'



(***PASCAL module 1332***)
begin {|start_here|} 
history:=fatal_error_stop; {in case we quit during initialization} 
t_open_out; {open the terminal for output} 
if ready_already=314159 then goto start_of_TEX; 

INSERT: 'Check the ``constant'''' values...'
; 
if bad>0 then 
  begin wterm_ln('Ouch---my internal constants have been clobbered!', 
    '---case ',bad:1); 
(*Ouch...clobbered*) 
  goto final_end; 
  end; 
initialize; {set global variables to their starting values} 
init if not get_strings_started then goto final_end; 
init_prim; {call |primitive| for each primitive} 
init_str_ptr:=str_ptr; init_pool_ptr:=pool_ptr; fix_date_and_time; 
tini
 
ready_already:=314159; 
start_of_TEX: 
INSERT: 'Initialize the output routines'
; 

INSERT: 'Get the first line of input and prepare to start'
; 
history:=spotless; {ready to go!} 
main_control; {come to life} 
final_cleanup; {prepare for death} 
end_of_TEX: close_files_and_terminate; 
final_end: ready_already:=0; 
end. 

