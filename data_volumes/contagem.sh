##!/usr/bin/env bash

#for k in *$energy_$alpha.txt;do
declare -a energy=("2.5" "3.0" "3.5" "4.0" "4.5" "5.0" "5.5" "6.0" "6.5" "7.0" "7.5" "8.0" "8.5" "9.0" "9.5" "10.0");
declare -a alpha=("3" "5" "7" "9");
numHist=15000;
for i in "${energy[@]}"; do
  for j in "${alpha[@]}"; do
    FILE=data_${i}_${j}.txt
    echo "$FILE"
    #for FILE in verbosity*; do
    nmbMu=$(echo | grep -c "mu+" $FILE);
    nmbMuIoni=$(echo | grep -c "muIoni" $FILE);
    nmbmsc=$(echo | grep -c "msc" $FILE);
    nmbCS=$(echo | grep -c "CoulombScat" $FILE);
    nmbDecay=$(echo | grep -c "Decay" $FILE);
    nmbMuNorm=$(echo "$nmbMu/$numHist" |bc -l);
    nmbMuIoniNorm=$(echo "$nmbMuIoni/$numHist" |bc -l);
    nmbmscNorm=$(echo "$nmbmsc/$numHist" |bc -l);
    nmbCSNorm=$(echo "$nmbCS/$numHist" |bc -l);
    nmbDecayNorm=$(echo "$nmbDecay/$numHist" |bc -l);
    echo "$nmbMu $nmbMuNorm $nmbMuIoni $nmbMuIoniNorm $nmbmscNorm $nmbCSNorm $nmbDecayNorm $i $j" >> contadorMuons.txt;
  done
 done


