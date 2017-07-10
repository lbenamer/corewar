#!/bin/sh

make -C .. && cp ../asm .
N=`echo Asombra` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Kappa` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Machine-gun` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo MarineKing` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Misaka_Mikoto` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Rainbow_dash` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo THUNDER` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Varimathras` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo Wall` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo _` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo _honeybadger` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo bee_gees` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo big_feet` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo big_life` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo bigzork` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo casimir` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo champ` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo corelol` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo darksasuke` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo doge` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo dubo` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo fat_42` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo fluttershy` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo gedeon` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo helltrain` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo jinx` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo justin_bee` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo littlepuppy` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo live` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo loose` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo mandragore` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo meowluigi` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo salamahenagalabadoun` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo sam_2.0` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo seg` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo skynet` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo terminator` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo test` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo turtle` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo ultimate-surrender` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo while_fork` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo youforkmytralala` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
N=`echo zork` S=`echo $N.s` COR=`echo $N.cor` && ./asm $S && hexdump $COR > testasm && ./asm42 $S && hexdump $COR > testasm42 && diff testasm testasm42
rm *.cor
