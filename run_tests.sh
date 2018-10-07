#!/bin/bash

FILES="anna_138_11 david_87_406 flat_1000_50 flat_1000_60 flat_1000_76 flat_300_20 flat_300_26 flat_300_28 fpsol_425_30 fpsol_451_30 fpsol_496_65 games_120_9 homer_561_13 huck_74_11 inithx_621_31 inithx_645_31 inithx_864_54 jean_80_10 le_450_15a le_450_15b le_450_15c le_450_25a le_450_25b le_450_25c le_450_25d le_450_5a le_450_5b le_450_5c le_450_5d miles_128_20 miles_128_31 miles_128_42 miles_128_73 miles_128_8 mulsol_184_31 mulsol_185_31 mulsol_186_31 mulsol_188_31 mulsol_197_49 myciel_11_4 myciel_191_8 myciel_23_5 myciel_47_6 myciel_95_7 queen_121_11 queen_169_13 queen_25_5 queen_36_7 queen_49_7 queen_64_9 queen_81_10 queen_96_12 school1 school1_nsh zeroin_206_30 zeroin_211_30 zeroin_211_49"

N_TIMES=$1

make

for f in $FILES
do
  echo "Processing $f file..."
  ./tp.out "input/$f.col" $N_TIMES	
  echo -e "\n"
done