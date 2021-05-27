#!/usr/bin/env bash

declare -a energy=("2.5" "3.0" "3.5" "4.0" "4.5" "5.0" "5.5" "6.0" "6.5" "7.0" "7.5" "8.0" "8.5" "9.0" "9.5" "10.0");
declare -a alpha=("3" "5" "7" "9");
declare -a volumes=("av_1_impr_1_shFaSteelEnvelopeC1_pv_0" "av_1_impr_1_shFaSteelEnvelopeC2_pv_1"
"av_1_impr_1_shFaSteelEnvelopeC3_pv_2" "av_1_impr_1_shFaSteelEnvelopeC4_pv_3" "av_2_impr_1_flange_pv_1"
"av_2_impr_1_shFaFlange1_pv_0" "av_3_impr_1_shFaWPlateA1_pv_0" "av_3_impr_1_shFaWPlateA2_pv_1"
"av_3_impr_1_shFaWPlateA3_pv_2" "av_3_impr_1_shFaWPlateA4_pv_3"
"av_4_impr_1_shFaPbCone1_pv_0" "av_4_impr_1_shFaPbCone2_pv_1" "av_5_impr_1_shFaCompRing1_pv_0"
"av_5_impr_1_shFaCompRing2_pv_1" "av_6_impr_1_shFaMgRing1_pv_0" "av_6_impr_1_shFaMgRing2_pv_1"
"av_6_impr_1_shFaMgRing3_pv_2" "av_6_impr_1_shFaMgRing4_pv_3" "av_7_impr_1_shFaGraphiteCone1_pv_0"
"av_7_impr_1_shFaGraphiteCone2_pv_1" "av_7_impr_1_voFaConcreteCone_pv_2" "av_7_impr_1_voFaSteelCone25_pv_3"
"av_7_impr_1_voFaSteelCone31_pv_4" "av_7_impr_1_voFaSteelCone25_pv_3" "av_8_impr_1_shFaWTube1_1_pv_0" "av_8_impr_1_shFaWTube1_2_pv_1"
"av_8_impr_1_shFaWTube2_1_pv_2" "av_8_impr_1_shFaWTube2_2_pv_3" "av_8_impr_1_voFaWTube3_pv_4" "av_8_impr_1_voFaWTube4_pv_5"
"shFaGraphiteCone1" "voFaEndPlate" "voFaWTube5");




for y in "${volumes[@]}"; do
for k in "${energy[@]}"; do
  for l in "${alpha[@]}"; do
  entrada=entrada_${y}_${k}_${l}.txt
  saida=saida_${y}_${k}_${l}.txt
  if [ -f "$entrada" ]; then
    if [ -f "$saida" ]; then
      linhasE=$(awk 'END { print NR }' $entrada)
      linhasS=$(awk 'END { print NR }' $saida)
      for i in $(eval echo "{1..$linhasE}"); do
        eventE=$(echo | awk -v num=$i 'NR==num {print $1}' $entrada);
        parentE=$(echo | awk -v num=$i 'NR==num {print $2}' $entrada);
        trackE=$(echo | awk -v num=$i 'NR==num {print $3}' $entrada);
        stepE=$(echo | awk -v num=$i 'NR==num {print $4}' $entrada);
        posEX=$(echo | awk -v num=$i 'NR==num {print $6}' $entrada);
        posEY=$(echo | awk -v num=$i 'NR==num {print $7}' $entrada);
        posEZ=$(echo | awk -v num=$i 'NR==num {print $8}' $entrada);
        momEX=$(echo | awk -v num=$i 'NR==num {print $12}' $entrada);
        momEY=$(echo | awk -v num=$i 'NR==num {print $13}' $entrada);
        momEZ=$(echo | awk -v num=$i 'NR==num {print $14}' $entrada);
        volumeE=$(echo | awk -v num=$i 'NR==num {print $15}' $entrada);
      for j in $(eval echo "{1..$linhasS}"); do
        eventS=$(echo | awk -v num=$j 'NR==num {print $1}' $saida);
        parentS=$(echo | awk -v num=$j 'NR==num {print $2}' $saida);
        trackS=$(echo | awk -v num=$j 'NR==num {print $3}' $saida);
        volumeS=$(echo | awk -v num=$j 'NR==num {print $15}' $saida);
      if [[ $eventE == $eventS && $parentE == $parentS && $trackE == $trackS ]];
        then
        stepS=$(echo | awk -v num=$j 'NR==num {print $4}' $saida);
        posSX=$(echo | awk -v num=$j 'NR==num {print $9}' $saida);
        posSY=$(echo | awk -v num=$j 'NR==num {print $10}' $saida);
        posSZ=$(echo | awk -v num=$j 'NR==num {print $11}' $saida);
        momSX=$(echo | awk -v num=$i 'NR==num {print $12}' $saida);
        momSY=$(echo | awk -v num=$i 'NR==num {print $13}' $saida);
        momSZ=$(echo | awk -v num=$i 'NR==num {print $14}' $saida);
        echo "$eventE $parentE $trackE $stepE $posEX $posEY $posEZ $momEX $momEY $momEZ $stepS $posSX $posSY $posSZ $momSX $momSY $momSZ $volumeE $k $l" >> volume_entrada_saida.txt;
        fi
    done
    done
  else
    echo "$saida not found";
    fi
  else
    echo "$entrada not found";
  fi
  done
done
done
