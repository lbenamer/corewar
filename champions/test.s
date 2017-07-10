.name "charles"
.comment "il en a une grosse c bastien ki le dit"

l2: sti r1,%:live,%1
	and r1,%0,r1

live: live %42
	  zjmp %:live
	  lld  42,r5
