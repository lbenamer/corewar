.name "zork number 2"
.comment "I'M ALIIIIVE"

l2:		st r1, r6
		and r1, %0, r1

live:	live %1
		zjmp %:live
