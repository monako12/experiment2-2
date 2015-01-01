#!/bin/sh
#シェルスクリプトの要件
# 1.ETA,ALPHA,HIDDENの値として範囲内でランダムな組み合わせを選択肢
# 2.それを元にseed値を変えて10パターンの結果を得る．
# 3.FINISHのiterationの回数を抽出し，そのときのパラメータの値を一緒に表示
# 4.10パターンのiterationの平均をとる．
# 
#bp_mo_exor.cの変更
# 文字列処理を行うためにfprintfのstderrを以下のように変更した．
# fprintf(stdout,"FINISH 2: iteration = %4d, error = %.10f\n",ite,err); 
# 
export LANG=C

((eta_inte=${RANDOM}%2))
#eta_deci=`echo "scale=2; ($RANDOM*3) / 100000" | bc`
((eta_deci=${RANDOM}%100))
ETA=`expr ${eta_inte}.${eta_deci}`
sed -i -e "s:#define ETA.*:#define ETA $ETA:g" bp_mo_exor.c

#alpha_deci=`echo "scale=2; ($RANDOM*3) / 100000" | bc`
((alpha_deci=${RANDOM}%100))
ALPHA=`expr 0.$alpha_deci`
sed -i -e "s:#define ALPHA.*:#define ALPHA $ALPHA:g" bp_mo_exor.c

((HIDDEN=${RANDOM}%15+2))
sed -i -e "s:#define HIDDEN.*:#define HIDDEN $HIDDEN:g" bp_mo_exor.c

sed -i -e "s///g" bp_mo_exor.c

gcc bp_mo_exor.c -o bp_mo_exor
echo "ETA:$ETA  ALPHA:$ALPHA    HIDDEN:$HIDDEN"
./bp_mo_exor 1000 > fuga.txt 2> log.txt
./bp_mo_exor 2000 >> fuga.txt 2>> log.txt
./bp_mo_exor 3000 >> fuga.txt 2>> log.txt
./bp_mo_exor 4000 >> fuga.txt 2>> log.txt
./bp_mo_exor 5000 >> fuga.txt 2>> log.txt
./bp_mo_exor 6000 >> fuga.txt 2>> log.txt
./bp_mo_exor 7000 >> fuga.txt 2>> log.txt
./bp_mo_exor 8000 >> fuga.txt 2>> log.txt
./bp_mo_exor 9000 >> fuga.txt 2>> log.txt
./bp_mo_exor 10000 >> fuga.txt 2>> log.txt

sum=0
cat log.txt | awk '{print $5}' | tr -d "," > figures.txt 
exec < figures.txt
while read line
do
    ((sum=${sum}+${line}))
done

((avarage=${sum}/10))

cat log.txt
echo "the avarage is ${avarage}."
