.name "zork"
.comment "just a basic living prog"

#l2:	sti	r1,%:live,%0
ld %4,r1
or r2,r1,r3
st r1,6
#	add	r1,r1,r1				
live	%1
#live:	live	%1
#	zjmp	%:live
