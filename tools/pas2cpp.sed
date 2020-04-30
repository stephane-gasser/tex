#!/bin/sed -f
s/{.*}//g
s/\bbegin\b/\{/g
s/\bend\b/\}/g
s/ = / == /g
s/ := / = /g
s/ <> / != /g
s/ + /+/g
s/ - /-/g
s/};/}/g
s/\bif /if (/g
s/ then\b/)/g
